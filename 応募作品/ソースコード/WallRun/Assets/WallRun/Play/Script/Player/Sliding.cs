using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Sliding : MonoBehaviour
{

    [Header("Reference")]
    public Transform orientation;
    public Transform playerObj;     //�v���C���[�I�u�W�F�N�g
    private Rigidbody rb;
    private Playermove pm;

    [Header("Sliding")]
    public float maxSlideTime;      //�X���C�f�B���O����
    public float slideForce;        //�X���f�B���O�̗�
    private float slideTimer;        //�X���C�f�B���O���Ԃ�}�邽�߂̃^�C�}�[

    //�����͂��Ⴊ�݂Ɠ����v��
    public float slideYscale;       //�X���C�h���̂��Ⴊ��
    private float startYscale;


    [Header("Input")]
    public KeyCode slideKey = KeyCode.LeftControl;
    //�����ړ��A�����ړ��p
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

        //�X���C�f�B���O�͂��߂̃L�[
        if (Input.GetKeyDown(slideKey) && (horizontalInput != 0 || verticalInput != 0))
        {
            StartSlide();
        }


        //�L�[�𗣂�����I���
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


    //�X���C�f�B���O�͂���
    private void StartSlide()
    {
        pm.sliding = true;
        playerObj.localScale = new Vector3(playerObj.localScale.x, slideYscale, playerObj.localScale.z);
        //���̏�ł��Ⴊ�ނƒ��ɕ�������n�ʂɐڒn������
        rb.AddForce(Vector3.down * 5f, ForceMode.Impulse);

        slideTimer = maxSlideTime;
    }


    //�X���C�f�B���O���̓���
    private void SlideingMovement()
    {
        Vector3 inputDirection = orientation.forward * verticalInput + orientation.right * horizontalInput;

        //�ʏ펞�̃X���C�f�B���O
        if(!pm.OnSlope() || rb.velocity.y > -0.1f)
        {
            rb.AddForce(inputDirection.normalized * slideForce, ForceMode.Force);
            slideTimer -= Time.deltaTime;
        }

        //�Ζʂ��X���C�f�B���O���ĉ���ꍇ
        //�i���̏ꍇ�͎Ζʂ����邽�߃^�C�}�[���g��Ȃ��j
        else
        {
            rb.AddForce(pm.GetSlopeMoveDirection(inputDirection) * slideForce, ForceMode.Force);
        }
        

        if (slideTimer <= 0)
            StopSlide();
    }


    //�X���C�f�B���O�I���
    private void StopSlide()
    {
        pm.sliding = false;
        playerObj.localScale = new Vector3(playerObj.localScale.x, startYscale, playerObj.localScale.z);

    }


}
