using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Bridge : MonoBehaviour
{
    public Transform target;  // �ڕW�̃I�u�W�F�N�g
    public float speed = 5.0f;  // �ړ����x
    private bool isMove = false;        //�ړ����Ă��Ă��邩

    //���̍~��
    public void MoveBridge()
    {
        if (target != null)
        {
            isMove = true;

            // �ڕW�̈ʒu���擾
            Vector3 targetPosition = target.position;

            // �����̈ʒu����ڕW�̈ʒu�֌������x�N�g�����v�Z
            Vector3 moveDirection = targetPosition - transform.position;

            // �x�N�g���̒�����1�ɐ��K�����A���x���|���Ĉړ�
            transform.Translate(moveDirection.normalized * speed * Time.deltaTime);

        }        
    }


    private void Update()
    {
        MoveBridge();
    }

    public bool GetIsMove() { return isMove; }	//�h�A�̈ړ���Ԏ擾
}
