using System.Collections;
using System.Collections.Generic;
using System.Diagnostics;
using Unity.VisualScripting;
using UnityEngine;

public class WallRunning : MonoBehaviour
{
    [Header("SE設定")]
    [Header("壁に引っ付いた時のSE")] public AudioClip WallAdhesionSE;
    private AudioSource audioSource = null;


    //壁走りのパラメータ
    [Header("壁走り中のパラメータ")]
    public LayerMask whatIsWall;    //壁の設定
    public LayerMask whatIsGround;
    public float wallRunForce;      //ウォールラン中の力
    public float wallJumpUpForce;   //壁走り中のジャンプ時の跳ね上がり
    public float wallJumpSideForce;
    public float wallClimbSpeed;
    
    //インプット類
    [Header("インプット設定")]
    public KeyCode jumpKey = KeyCode.Space;                 //壁走り中のジャンプ
    public KeyCode upwardsRunKey = KeyCode.LeftShift;       //壁走り中上に移動
    public KeyCode downwardsRunKey = KeyCode.LeftControl;   //壁走り中下に移動スライディングもできるようにする
   
    private bool upwardsRunning;
    private bool downwardsRunning;
    private float horizontalInput;
    private float verticalInput;

    [Header("壁の検出")]
    public float wallcheckDistance;     //ウォールチェック距離
    public float minJumpHeight;         //最小ジャンプ高さ(壁走りで前進している間のジャンプ力)
   
    private RaycastHit leftWallhit;     //右側の壁
    private RaycastHit rightWallhit;    //左側の壁
    private bool wallLeft;
    private bool wallRight;

   
    private bool exitingWall;
    
    //トランスフォーム
    [Header("Reference")]
    public Transform orientation;
    private Playermove pm;
    private Rigidbody rb;

    private void Start()
    {
        rb = GetComponent<Rigidbody>();
        pm = GetComponent<Playermove>();
        audioSource = GetComponent<AudioSource>();
    }

    private void Update()
    {
        CheckForWall();
        StateMachine();
    }

    private void FixedUpdate()
    {
        if (pm.wallrunning)
            WallRunningMovement();
    }


    //壁判定
    private void CheckForWall()
    {
        //光線を左右に出して壁があるかを確認
        //右にある壁                   
        wallRight = Physics.Raycast(transform.position, orientation.right, out rightWallhit, wallcheckDistance, whatIsWall);
        //左にある壁
        wallLeft = Physics.Raycast(transform.position, -orientation.right, out leftWallhit, wallcheckDistance, whatIsWall);
    }

    //プレイヤーが十分な高さにいて壁走りをスタートさせるか
    private bool AboveGround()
    {
        //光線が何も当たらなかった場合にtrueを返す
        return !Physics.Raycast(transform.position, Vector3.down, minJumpHeight, whatIsGround);
    }


    private void StateMachine()
    {
        //キーボード入力
        horizontalInput = Input.GetAxisRaw("Horizontal");
        verticalInput = Input.GetAxisRaw("Vertical");

        upwardsRunning = Input.GetKey(upwardsRunKey);       //壁走り中の上昇
        downwardsRunning = Input.GetKey(downwardsRunKey);   //壁走り中の降下

        //左側またわ右側に走れる壁があることでスタートさせる
        if((wallLeft || wallRight) && verticalInput > 0 && AboveGround() && !exitingWall)
        {
            //壁走りスタート
            if (!pm.wallrunning)
                StartWallRun();
            
            //壁走り中のジャンプ
            if (Input.GetKey(jumpKey)) WallJump();
        }

        //壁走り終了
        else if(exitingWall)
        {
            if (pm.wallrunning)
                StopWallRun();

            exitingWall = false;
        }

        else
        {
            if (pm.wallrunning)
                StopWallRun();
        }
    }


    private void StartWallRun()
    {
        //WallRun中のスピードは変更しやすくするためPlayermoveに設定している
        pm.wallrunning = true;
        rb.velocity = new Vector3(rb.velocity.x, 0f, rb.velocity.z);
        PlaySE(WallAdhesionSE);
    }


    private void WallRunningMovement()
    {
        //フラグに応じて、右壁または左壁に衝突した場合の法線ベクトルを設定
        Vector3 wallNormal = wallRight ? rightWallhit.normal : leftWallhit.normal;
        
        //wallNormal とプレイヤーの上向きベクトル transform.up の外積を計算して、壁に対する前進方向のベクトルを取得
        Vector3 wallForward = Vector3.Cross(wallNormal, transform.up);

        //壁をどちらからでも前に進める
        if ((orientation.forward - wallForward).magnitude > (orientation.forward - -wallForward).magnitude)
        {
            wallForward = -wallForward;
        }

        //前進方向の力を適用
        rb.AddForce(wallForward * wallRunForce, ForceMode.Force);

        //壁走り中の上下
        if(upwardsRunning)
            rb.velocity = new Vector3(rb.velocity.x, wallClimbSpeed, rb.velocity.z);

        if (downwardsRunning)
            rb.velocity = new Vector3(rb.velocity.x, -wallClimbSpeed, rb.velocity.z);
        
        //湾曲の壁の外側
        //プレイヤーが壁から離れようとしない限り壁の内側に引き寄せる（*100）
        if (!(wallLeft && horizontalInput > 0) && !(wallRight && horizontalInput < 0))
            rb.AddForce(-wallNormal * 100, ForceMode.Force);
    }


    private void StopWallRun()
    {
        pm.wallrunning = false;
    }

    private void WallJump()
    {
        exitingWall = true;
       
        //壁が左にあるか右にあるかに応じて壁の法線を保存
        Vector3 wallNormal = wallRight ? rightWallhit.normal : leftWallhit.normal;

        Vector3 forceToApply = transform.up * wallJumpUpForce + wallNormal * wallJumpSideForce;

        rb.velocity = new Vector3(rb.velocity.x, 0f, rb.velocity.z);
        rb.AddForce(forceToApply, ForceMode.Impulse);
    }

    //効果音再生関数
    public void PlaySE(AudioClip clip)
    {
        if (audioSource != null)
        {
            audioSource.PlayOneShot(clip);
        }
    }
}
