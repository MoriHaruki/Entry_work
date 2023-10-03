using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class conveyer : MonoBehaviour
{
    public bool isOn = false;    //起動確認
    public float TargetDriveSpeed = 3.0f;  //スピード
    public float CurrentSpeed { get { return _currentSpeed; } }
    public Vector3 DriveDirection => transform.right;       //向き（Z方向）

    private Animator animator;

    [SerializeField] private float forcePower = 50f; //ベルトコンベアの力 
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
            var objecSpeed = Vector3.Dot(r.velocity, DriveDirection);       //同じ方向の向きの成分を取り出す

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
            // "IsRunning"というブール型のパラメータを使ってアニメーションを制御する例
            //animator.SetBool("IsRunning", isAnim); // アニメーションを停止
            animator.enabled = isAnim;
        }
    }

}
