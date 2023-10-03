using System.Collections;
using System.Collections.Generic;
using System.Diagnostics;
using Unity.VisualScripting;
using UnityEngine;

public class WallRunning : MonoBehaviour
{
    [Header("SE�ݒ�")]
    [Header("�ǂɈ����t��������SE")] public AudioClip WallAdhesionSE;
    private AudioSource audioSource = null;


    //�Ǒ���̃p�����[�^
    [Header("�Ǒ��蒆�̃p�����[�^")]
    public LayerMask whatIsWall;    //�ǂ̐ݒ�
    public LayerMask whatIsGround;
    public float wallRunForce;      //�E�H�[���������̗�
    public float wallJumpUpForce;   //�Ǒ��蒆�̃W�����v���̒��ˏオ��
    public float wallJumpSideForce;
    public float wallClimbSpeed;
    
    //�C���v�b�g��
    [Header("�C���v�b�g�ݒ�")]
    public KeyCode jumpKey = KeyCode.Space;                 //�Ǒ��蒆�̃W�����v
    public KeyCode upwardsRunKey = KeyCode.LeftShift;       //�Ǒ��蒆��Ɉړ�
    public KeyCode downwardsRunKey = KeyCode.LeftControl;   //�Ǒ��蒆���Ɉړ��X���C�f�B���O���ł���悤�ɂ���
   
    private bool upwardsRunning;
    private bool downwardsRunning;
    private float horizontalInput;
    private float verticalInput;

    [Header("�ǂ̌��o")]
    public float wallcheckDistance;     //�E�H�[���`�F�b�N����
    public float minJumpHeight;         //�ŏ��W�����v����(�Ǒ���őO�i���Ă���Ԃ̃W�����v��)
   
    private RaycastHit leftWallhit;     //�E���̕�
    private RaycastHit rightWallhit;    //�����̕�
    private bool wallLeft;
    private bool wallRight;

   
    private bool exitingWall;
    
    //�g�����X�t�H�[��
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


    //�ǔ���
    private void CheckForWall()
    {
        //���������E�ɏo���ĕǂ����邩���m�F
        //�E�ɂ����                   
        wallRight = Physics.Raycast(transform.position, orientation.right, out rightWallhit, wallcheckDistance, whatIsWall);
        //���ɂ����
        wallLeft = Physics.Raycast(transform.position, -orientation.right, out leftWallhit, wallcheckDistance, whatIsWall);
    }

    //�v���C���[���\���ȍ����ɂ��ĕǑ�����X�^�[�g�����邩
    private bool AboveGround()
    {
        //����������������Ȃ������ꍇ��true��Ԃ�
        return !Physics.Raycast(transform.position, Vector3.down, minJumpHeight, whatIsGround);
    }


    private void StateMachine()
    {
        //�L�[�{�[�h����
        horizontalInput = Input.GetAxisRaw("Horizontal");
        verticalInput = Input.GetAxisRaw("Vertical");

        upwardsRunning = Input.GetKey(upwardsRunKey);       //�Ǒ��蒆�̏㏸
        downwardsRunning = Input.GetKey(downwardsRunKey);   //�Ǒ��蒆�̍~��

        //�����܂���E���ɑ����ǂ����邱�ƂŃX�^�[�g������
        if((wallLeft || wallRight) && verticalInput > 0 && AboveGround() && !exitingWall)
        {
            //�Ǒ���X�^�[�g
            if (!pm.wallrunning)
                StartWallRun();
            
            //�Ǒ��蒆�̃W�����v
            if (Input.GetKey(jumpKey)) WallJump();
        }

        //�Ǒ���I��
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
        //WallRun���̃X�s�[�h�͕ύX���₷�����邽��Playermove�ɐݒ肵�Ă���
        pm.wallrunning = true;
        rb.velocity = new Vector3(rb.velocity.x, 0f, rb.velocity.z);
        PlaySE(WallAdhesionSE);
    }


    private void WallRunningMovement()
    {
        //�t���O�ɉ����āA�E�ǂ܂��͍��ǂɏՓ˂����ꍇ�̖@���x�N�g����ݒ�
        Vector3 wallNormal = wallRight ? rightWallhit.normal : leftWallhit.normal;
        
        //wallNormal �ƃv���C���[�̏�����x�N�g�� transform.up �̊O�ς��v�Z���āA�ǂɑ΂���O�i�����̃x�N�g�����擾
        Vector3 wallForward = Vector3.Cross(wallNormal, transform.up);

        //�ǂ��ǂ��炩��ł��O�ɐi�߂�
        if ((orientation.forward - wallForward).magnitude > (orientation.forward - -wallForward).magnitude)
        {
            wallForward = -wallForward;
        }

        //�O�i�����̗͂�K�p
        rb.AddForce(wallForward * wallRunForce, ForceMode.Force);

        //�Ǒ��蒆�̏㉺
        if(upwardsRunning)
            rb.velocity = new Vector3(rb.velocity.x, wallClimbSpeed, rb.velocity.z);

        if (downwardsRunning)
            rb.velocity = new Vector3(rb.velocity.x, -wallClimbSpeed, rb.velocity.z);
        
        //�p�Ȃ̕ǂ̊O��
        //�v���C���[���ǂ��痣��悤�Ƃ��Ȃ�����ǂ̓����Ɉ����񂹂�i*100�j
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
       
        //�ǂ����ɂ��邩�E�ɂ��邩�ɉ����ĕǂ̖@����ۑ�
        Vector3 wallNormal = wallRight ? rightWallhit.normal : leftWallhit.normal;

        Vector3 forceToApply = transform.up * wallJumpUpForce + wallNormal * wallJumpSideForce;

        rb.velocity = new Vector3(rb.velocity.x, 0f, rb.velocity.z);
        rb.AddForce(forceToApply, ForceMode.Impulse);
    }

    //���ʉ��Đ��֐�
    public void PlaySE(AudioClip clip)
    {
        if (audioSource != null)
        {
            audioSource.PlayOneShot(clip);
        }
    }
}
