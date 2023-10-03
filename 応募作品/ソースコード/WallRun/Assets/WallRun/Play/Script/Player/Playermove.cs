using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;
using System;
using UnityEngine.SceneManagement;
using System.ComponentModel.Design;

public class Playermove : MonoBehaviour
{
    //���C�t
    [Header("���C�t")]
    public Transform RespawnPosoton;    //���X�|�[����̐ݒ�
    public int startingLife = 3;    // �����̃��C�t��
    public int lifeDecrease = 1;    // ���C�t�����������
    public float deathYPosition = -10f;  // �v���C���[�����B����ƃ��C�t����������Y���W
    private int currentLife;    // ���݂̃��C�t��
   
   
    //�ړ��p�����[�^
    [Header("�ړ�")]
    public float walkspeed;
    public float sprintspeed;
    public float slideSpeed;
    public float wallrunSpeed;
    public float groundDrag;
    private float desiredMoveSpeed;
    private float lastDesiredMoveSpeed;
    private float moveSpeed;


    //�W�����v�p�����[�^
    [Header("�W�����v")]
    public float jumpForce;     //�W�����v��
    public float airMultiplier;
    bool readyToJump = true;

    //���Ⴊ�݃p�����[�^
    [Header("���Ⴊ��")]
    public float crouchSpeed;   //���Ⴊ�ݎ��̃X�s�[�h
    public float crouchYScale;  //���Ⴊ�񂾎��̑傫��
    private float startYscale;   //���Ⴊ�ޑO�̃X�P�[��

    //�L�[�p�����[�^
    [Header("�L�[�R���t�B�O")]
    public KeyCode jumpKey = KeyCode.Space;         //�W�����v
    public KeyCode sprintKey = KeyCode.LeftShift;   //�_�b�V��
    public KeyCode crouchKey = KeyCode.LeftControl; //���Ⴊ��

    //�ڒn�_
    [Header("�ڒn�_")]
    public float playerHeight;�@//�v���C���[�̐g��
    public LayerMask whatIsGround;
    bool grounded;

    //�Ζʂ̏���
    [Header("�Ζ�")]
    public float maxSlopeAngele;
    private RaycastHit slopeHit;
    private bool exitingSlope;

    public Transform orientation;

    //�v���C���[�ړ�
    public MovementState state;
    float horizontalInput;
    float verticalInput;
    Vector3 moveDirection;
    Rigidbody rb;
    
    //�v���C���[�X�e�[�g
    public enum MovementState
    {
        walking,        //����
        sprinting,      //�_�b�V��
        wallrunning,    //�Ǒ���
        crouching,      //���Ⴊ��
        sliding,        //�X���C�f�B���O
        air             //��
    }
    public bool sliding;
    public bool crouching;
    public bool wallrunning;

    private void Start()
    {
        rb = GetComponent<Rigidbody>();
        rb.freezeRotation = true;

        startYscale = transform.localScale.y;
       
        currentLife = startingLife;   // �������C�t����ݒ�

        Application.targetFrameRate = 300;
    }


    private void Update()
    {
        // �v���C���[��Y���W���w��̒l�ɓ��B�����烉�C�t������������
        if (transform.position.y <= deathYPosition)
        {
            DecreaseLife();
        }

        // ground check
        grounded = Physics.Raycast(transform.position, Vector3.down, playerHeight * 0.5f + 0.2f, whatIsGround);
       
        //�W�����v�pflag
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
        //�v���C���}�E�X�J�[�\�����ĕ\��
        if (Input.GetKeyDown(KeyCode.Escape))
            Application.Quit();

        MovePlayer();
    }

    private void OnCollisionEnter(Collision collision)
    {
        if (collision.gameObject.CompareTag("goal"))
        {
            // �ڐG�����I�u�W�F�N�g��"TargetObject"�^�O�����ꍇ�Ɏ��s���鏈�����L�q
            Debug.Log("�v���C���[��goal�ɓ���������");
            // ���ケ���ɏ�����ǉ� 
            SceneManager.LoadScene("game2");
        }

        if (collision.gameObject.CompareTag("goal2"))
        {
            // �ڐG�����I�u�W�F�N�g��"TargetObject"�^�O�����ꍇ�Ɏ��s���鏈�����L�q
            Debug.Log("�v���C���[��goal�ɓ���������");
            // ���ケ���ɏ�����ǉ�
            SceneManager.LoadScene("game3");
        }

        if (collision.gameObject.CompareTag("goal3"))
        {
            // �ڐG�����I�u�W�F�N�g��"TargetObject"�^�O�����ꍇ�Ɏ��s���鏈�����L�q
            Debug.Log("�v���C���[��goal�ɓ���������");
            // ���ケ���ɏ�����ǉ�
            SceneManager.LoadScene("Clear");
            Cursor.visible = true;
            Cursor.lockState = CursorLockMode.None;
        }
    }


    private void MyInput()
    {
        horizontalInput = Input.GetAxisRaw("Horizontal");
        verticalInput = Input.GetAxisRaw("Vertical");

        // �W�����v
        if (Input.GetKey(jumpKey) && readyToJump && grounded)
        {
             readyToJump = false;
            Jump();
        }

       
        //���Ⴊ��
        if (Input.GetKeyDown(crouchKey))
        {
            if(transform != null)
            {
                //�k�������Ⴊ�݂�\�������ɒ����鏈��
                transform.localScale = new Vector3(transform.localScale.x, crouchYScale, transform.localScale.z);
            }
            
        }

        //���Ⴊ�݃L�����Z��
        if (Input.GetKeyUp(crouchKey))
        {
            if (transform != null)
            {
                //�T�C�Y�����ɖ߂����ɒ����鏈��
                transform.localScale = new Vector3(transform.localScale.x, startYscale, transform.localScale.z);
            }
        }
    }

    //���C�t�Ǘ�
    private void DecreaseLife()
    {
        currentLife -= lifeDecrease;    // ���C�t������������

        if (currentLife <= 0)
        {
            // ���C�t��0�ȉ��ɂȂ����ꍇ�̏���
            Debug.Log("�Q�[���I�[�o�[");     
            SceneManager.LoadScene("GameOver");
            Cursor.visible = true;
            Cursor.lockState = CursorLockMode.None;
        }
        else
        {
            // ���C�t���܂��c���Ă���ꍇ�̏���
            Debug.Log("���C�t���������܂����B�c�胉�C�t: " + currentLife);
            //���X�|�[��
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

        //���x���ω����������m�F
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


    //��������̌����v�Z
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
        //�ړ��������v�Z����
        moveDirection = (orientation.forward * verticalInput + orientation.right * horizontalInput) * Time.deltaTime;
       
        //�X���[�v
        if(OnSlope() && !exitingSlope)
        {
            rb.AddForce(GetSlopeMoveDirection(moveDirection) * moveSpeed * 20f, ForceMode.Force);
            
            if(rb.velocity.y > 0)
                rb.AddForce(Vector3.down * 80f, ForceMode.Force);
        }

        //�n��
        if (grounded)
            rb.AddForce(moveDirection.normalized * moveSpeed * 10f, ForceMode.Force);
        
        // ��
        else if (!grounded)
            rb.AddForce(moveDirection.normalized * moveSpeed * 10f * airMultiplier,  ForceMode.Force);


        if (!wallrunning) rb.useGravity = !OnSlope();
    }


    private void SpeedControl()
    {
        //�⓹��ł̃X�s�[�h
        if(OnSlope() && !exitingSlope)
        {
            if (rb.velocity.magnitude > moveSpeed)
                rb.velocity = rb.velocity.normalized * moveSpeed;
        }

        //�ʏ�
        else
        {
            Vector3 flatVel = new Vector3(rb.velocity.x, 0f, rb.velocity.z);
            //�K�v�ɉ����đ��x�𐧌�����
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