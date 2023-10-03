using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Sliding : MonoBehaviour
{

    [Header("Reference")]
    public Transform orientation;
    public Transform playerObj;     //プレイヤーオブジェクト
    private Rigidbody rb;
    private Playermove pm;

    [Header("Sliding")]
    public float maxSlideTime;      //スライディング時間
    public float slideForce;        //スラディングの力
    private float slideTimer;        //スライディング時間を図るためのタイマー

    //ここはしゃがみと同じ要領
    public float slideYscale;       //スライド中のしゃがみ
    private float startYscale;


    [Header("Input")]
    public KeyCode slideKey = KeyCode.LeftControl;
    //水平移動、垂直移動用
    private float horizontalInput;
    private float verticalInput;
   

    void Start()
    {
        rb = GetComponent<Rigidbody>();
        pm = GetComponent<Playermove>();

        startYscale = playerObj.localScale.y;
    }

    void Update()
    {
        horizontalInput = Input.GetAxisRaw("Horizontal");
        verticalInput = Input.GetAxisRaw("Vertical");

        //スライディングはじめのキー
        if (Input.GetKeyDown(slideKey) && (horizontalInput != 0 || verticalInput != 0))
        {
            StartSlide();
        }


        //キーを離したら終わり
        if (Input.GetKeyUp(slideKey) && pm.sliding)
        {
            StopSlide();
        }

    }


    private void FixedUpdate()
    {
        if (pm.sliding)
            SlideingMovement();
    }


    //スライディングはじめ
    private void StartSlide()
    {
        pm.sliding = true;
        playerObj.localScale = new Vector3(playerObj.localScale.x, slideYscale, playerObj.localScale.z);
        //その場でしゃがむと宙に浮くから地面に接地させる
        rb.AddForce(Vector3.down * 5f, ForceMode.Impulse);

        slideTimer = maxSlideTime;
    }


    //スライディング中の動き
    private void SlideingMovement()
    {
        Vector3 inputDirection = orientation.forward * verticalInput + orientation.right * horizontalInput;

        //通常時のスライディング
        if(!pm.OnSlope() || rb.velocity.y > -0.1f)
        {
            rb.AddForce(inputDirection.normalized * slideForce, ForceMode.Force);
            slideTimer -= Time.deltaTime;
        }

        //斜面をスライディングして下る場合
        //（この場合は斜面を下るためタイマーを使わない）
        else
        {
            rb.AddForce(pm.GetSlopeMoveDirection(inputDirection) * slideForce, ForceMode.Force);
        }
        

        if (slideTimer <= 0)
            StopSlide();
    }


    //スライディング終わり
    private void StopSlide()
    {
        pm.sliding = false;
        playerObj.localScale = new Vector3(playerObj.localScale.x, startYscale, playerObj.localScale.z);

    }


}
