using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;
using System;
using UnityEngine.SceneManagement;
using System.ComponentModel.Design;

public class Playermove : MonoBehaviour
{
    //ライフ
    [Header("ライフ")]
    public Transform RespawnPosoton;    //リスポーン先の設定
    public int startingLife = 3;    // 初期のライフ数
    public int lifeDecrease = 1;    // ライフが減少する量
    public float deathYPosition = -10f;  // プレイヤーが到達するとライフが減少するY座標
    private int currentLife;    // 現在のライフ数
   
   
    //移動パラメータ
    [Header("移動")]
    public float walkspeed;
    public float sprintspeed;
    public float slideSpeed;
    public float wallrunSpeed;
    public float groundDrag;
    private float desiredMoveSpeed;
    private float lastDesiredMoveSpeed;
    private float moveSpeed;


    //ジャンプパラメータ
    [Header("ジャンプ")]
    public float jumpForce;     //ジャンプ力
    public float airMultiplier;
    bool readyToJump = true;

    //しゃがみパラメータ
    [Header("しゃがみ")]
    public float crouchSpeed;   //しゃがみ時のスピード
    public float crouchYScale;  //しゃがんだ時の大きさ
    private float startYscale;   //しゃがむ前のスケール

    //キーパラメータ
    [Header("キーコンフィグ")]
    public KeyCode jumpKey = KeyCode.Space;         //ジャンプ
    public KeyCode sprintKey = KeyCode.LeftShift;   //ダッシュ
    public KeyCode crouchKey = KeyCode.LeftControl; //しゃがみ

    //接地点
    [Header("接地点")]
    public float playerHeight;　//プレイヤーの身長
    public LayerMask whatIsGround;
    bool grounded;

    //斜面の処理
    [Header("斜面")]
    public float maxSlopeAngele;
    private RaycastHit slopeHit;
    private bool exitingSlope;

    public Transform orientation;

    //プレイヤー移動
    public MovementState state;
    float horizontalInput;
    float verticalInput;
    Vector3 moveDirection;
    Rigidbody rb;
    
    //プレイヤーステート
    public enum MovementState
    {
        walking,        //歩き
        sprinting,      //ダッシュ
        wallrunning,    //壁走り
        crouching,      //しゃがみ
        sliding,        //スライディング
        air             //空中
    }
    public bool sliding;
    public bool crouching;
    public bool wallrunning;

    private void Start()
    {
        rb = GetComponent<Rigidbody>();
        rb.freezeRotation = true;

        startYscale = transform.localScale.y;
       
        currentLife = startingLife;   // 初期ライフ数を設定

        Application.targetFrameRate = 300;
    }


    private void Update()
    {
        // プレイヤーのY座標が指定の値に到達したらライフを減少させる
        if (transform.position.y <= deathYPosition)
        {
            DecreaseLife();
        }

        // ground check
        grounded = Physics.Raycast(transform.position, Vector3.down, playerHeight * 0.5f + 0.2f, whatIsGround);
       
        //ジャンプ用flag
        if(grounded)
        {
            readyToJump = true;
        }

        MyInput();
        SpeedControl();
        StateHandler();

        // handle drag
        if (grounded)
            rb.drag = groundDrag;
        else
            rb.drag = 0;
        //プレイ中マウスカーソルを再表示
        if (Input.GetKeyDown(KeyCode.Escape))
            Application.Quit();

        MovePlayer();
    }

    private void OnCollisionEnter(Collision collision)
    {
        if (collision.gameObject.CompareTag("goal"))
        {
            // 接触したオブジェクトが"TargetObject"タグを持つ場合に実行する処理を記述
            Debug.Log("プレイヤーがgoalに当たったよ");
            // 今後ここに処理を追加 
            SceneManager.LoadScene("game2");
        }

        if (collision.gameObject.CompareTag("goal2"))
        {
            // 接触したオブジェクトが"TargetObject"タグを持つ場合に実行する処理を記述
            Debug.Log("プレイヤーがgoalに当たったよ");
            // 今後ここに処理を追加
            SceneManager.LoadScene("game3");
        }

        if (collision.gameObject.CompareTag("goal3"))
        {
            // 接触したオブジェクトが"TargetObject"タグを持つ場合に実行する処理を記述
            Debug.Log("プレイヤーがgoalに当たったよ");
            // 今後ここに処理を追加
            SceneManager.LoadScene("Clear");
            Cursor.visible = true;
            Cursor.lockState = CursorLockMode.None;
        }
    }


    private void MyInput()
    {
        horizontalInput = Input.GetAxisRaw("Horizontal");
        verticalInput = Input.GetAxisRaw("Vertical");

        // ジャンプ
        if (Input.GetKey(jumpKey) && readyToJump && grounded)
        {
             readyToJump = false;
            Jump();
        }

       
        //しゃがみ
        if (Input.GetKeyDown(crouchKey))
        {
            if(transform != null)
            {
                //縮小ししゃがみを表現しつつ床に着ける処理
                transform.localScale = new Vector3(transform.localScale.x, crouchYScale, transform.localScale.z);
            }
            
        }

        //しゃがみキャンセル
        if (Input.GetKeyUp(crouchKey))
        {
            if (transform != null)
            {
                //サイズを元に戻し床に着ける処理
                transform.localScale = new Vector3(transform.localScale.x, startYscale, transform.localScale.z);
            }
        }
    }

    //ライフ管理
    private void DecreaseLife()
    {
        currentLife -= lifeDecrease;    // ライフを減少させる

        if (currentLife <= 0)
        {
            // ライフが0以下になった場合の処理
            Debug.Log("ゲームオーバー");     
            SceneManager.LoadScene("GameOver");
            Cursor.visible = true;
            Cursor.lockState = CursorLockMode.None;
        }
        else
        {
            // ライフがまだ残っている場合の処理
            Debug.Log("ライフが減少しました。残りライフ: " + currentLife);
            //リスポーン
            transform.position = RespawnPosoton.position;
        }
    }


    private void StateHandler()
    {
        if(wallrunning)
        {
            state = MovementState.wallrunning;
            desiredMoveSpeed = wallrunSpeed;
        }


       else if(sliding)
        {
            state = MovementState.sliding;

            if (OnSlope() && rb.velocity.y < 0.1f)
                desiredMoveSpeed = slideSpeed;

            else
                desiredMoveSpeed = sprintspeed;
        }

       else if(Input.GetKey(crouchKey))
        {
            state = MovementState.crouching;
            desiredMoveSpeed = crouchSpeed;
        }

       else if(grounded && Input.GetKey(sprintKey))
        {
            state = MovementState.sprinting;
            desiredMoveSpeed = sprintspeed;
        }

        else if(grounded)
        {
            state = MovementState.walking;
            desiredMoveSpeed = walkspeed;
        }

        else
        {
            state = MovementState.air;
        }

        //速度が変化したかを確認
        if (Mathf.Abs(desiredMoveSpeed - lastDesiredMoveSpeed) > 4f && moveSpeed != 0)
        {
            StopAllCoroutines();
            StartCoroutine(SmoothlyLerpMoveSpeed());
        }
        else
        {
            moveSpeed = desiredMoveSpeed;
        }
        lastDesiredMoveSpeed = desiredMoveSpeed;
    }


    //下った後の減速計算
    private IEnumerator SmoothlyLerpMoveSpeed()
    {
        float time = 0;
        float difference = Math.Abs(desiredMoveSpeed - moveSpeed);
        float startValue = moveSpeed;

        while(time < difference)
        {
            moveSpeed = Mathf.Lerp(startValue, desiredMoveSpeed, time / difference);
            time += Time.deltaTime;
            yield return null;
        }

        moveSpeed = desiredMoveSpeed;
    }


    private void MovePlayer()
    {
        //移動方向を計算する
        moveDirection = (orientation.forward * verticalInput + orientation.right * horizontalInput) * Time.deltaTime;
       
        //スロープ
        if(OnSlope() && !exitingSlope)
        {
            rb.AddForce(GetSlopeMoveDirection(moveDirection) * moveSpeed * 20f, ForceMode.Force);
            
            if(rb.velocity.y > 0)
                rb.AddForce(Vector3.down * 80f, ForceMode.Force);
        }

        //地面
        if (grounded)
            rb.AddForce(moveDirection.normalized * moveSpeed * 10f, ForceMode.Force);
        
        // 空中
        else if (!grounded)
            rb.AddForce(moveDirection.normalized * moveSpeed * 10f * airMultiplier,  ForceMode.Force);


        if (!wallrunning) rb.useGravity = !OnSlope();
    }


    private void SpeedControl()
    {
        //坂道上でのスピード
        if(OnSlope() && !exitingSlope)
        {
            if (rb.velocity.magnitude > moveSpeed)
                rb.velocity = rb.velocity.normalized * moveSpeed;
        }

        //通常
        else
        {
            Vector3 flatVel = new Vector3(rb.velocity.x, 0f, rb.velocity.z);
            //必要に応じて速度を制限する
            if (flatVel.magnitude > moveSpeed)
            {
                Vector3 limitedVel = flatVel.normalized * moveSpeed;
                rb.velocity = new Vector3(limitedVel.x, rb.velocity.y, limitedVel.z);
            }
        }
    }


    private void Jump()
    {
        rb.AddForce(transform.up * jumpForce, ForceMode.Impulse);
    }

    public bool OnSlope()
   {
        if(Physics.Raycast(transform.position, Vector3.down, out slopeHit, playerHeight * 0.5f +0.3f))
        {
            float angle = Vector3.Angle(Vector3.up, slopeHit.normal);
            return angle < maxSlopeAngele && angle != 0;
        }
        return false;
   }

    public Vector3 GetSlopeMoveDirection(Vector3 direction)
    {
        return Vector3.ProjectOnPlane(direction, slopeHit.normal).normalized;
    }

}