using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class conveyer : MonoBehaviour
{
    public bool isOn = false;    //�N���m�F
    public float TargetDriveSpeed = 3.0f;  //�X�s�[�h
    public float CurrentSpeed { get { return _currentSpeed; } }
    public Vector3 DriveDirection => transform.right;       //�����iZ�����j

    private Animator animator;

    [SerializeField] private float forcePower = 50f; //�x���g�R���x�A�̗� 
    private bool isAnim = true;


    private float _currentSpeed = 0;
    private List<Rigidbody> _rigidbodies = new List<Rigidbody>();


    private void Start()
    {
        animator = GetComponent<Animator>();

    }

    private void OnCollisionEnter(Collision collision)
    {
        var rigidbody = collision.gameObject.GetComponent<Rigidbody>();
        _rigidbodies.Add(rigidbody);
    }


    private void OnCollisionExit(Collision collision)
    {
        var rigidbody = collision.gameObject.GetComponent<Rigidbody>();
        _rigidbodies.Remove(rigidbody);
    }

   

    private void FixedUpdate()
    {
        if(!animator.enabled)
        {
            return;
        }

        _currentSpeed = isOn ? TargetDriveSpeed : 0f;

        _rigidbodies.RemoveAll(r => r == null);

        foreach(  var r in _rigidbodies)
        {
            var objecSpeed = Vector3.Dot(r.velocity, DriveDirection);       //���������̌����̐��������o��

            if(objecSpeed < Mathf.Abs(TargetDriveSpeed))
            {
                r.transform.position += DriveDirection * forcePower * Time.deltaTime;
            }
        }
    }

    private void Update()
    {
        if (Input.GetKeyDown(KeyCode.K))
        {
            isAnim = !isAnim;
            // "IsRunning"�Ƃ����u�[���^�̃p�����[�^���g���ăA�j���[�V�����𐧌䂷���
            //animator.SetBool("IsRunning", isAnim); // �A�j���[�V�������~
            animator.enabled = isAnim;
        }
    }

}
