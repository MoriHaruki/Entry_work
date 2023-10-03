using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UIElements;
using static UnityEngine.GraphicsBuffer;

public class Log : MonoBehaviour
{
    public Transform target;  // �ڕW�̃I�u�W�F�N�g
    public Transform player;           // �v���C���[��Transform
    public float interactionDistance;  // �v���C���[�Ƃ̑��ݍ�p����
    public float speed = 5f;       // �������x
    private bool playerInRange = false; // �v���C���[���͈͓��ɂ��邩
   
    void Update()
    {
        // �v���C���[�Ƃ̋������v�Z
        float distanceToPlayer = Vector3.Distance(transform.position, player.position);

        // �v���C���[���͈͓��ɓ��������𔻒�
        if (distanceToPlayer <= interactionDistance)
        {
            playerInRange = true;
        }
        else
        {
            playerInRange = false;
        }

        // �v���C���[���͈͓��ɓ������ꍇ�A�I�u�W�F�N�g�𗎉�������
        if (playerInRange)
        {
            Debug.Log("�͈͓��ɓ����č쓮������");

            // �ړ��J�n���ɑ��x��ݒ�
            Vector3 direction = (target.position - transform.position).normalized;
            // �ړ������ɑ��x��K�p
            transform.position += direction * speed * Time.deltaTime;

            // �ڕW�̈ʒu�ɓ��B�����瑬�x���[���ɂ��Ĉړ��I��
            float distanceToTarget = Vector3.Distance(transform.position, target.position);
            
            if (distanceToTarget <= 0.1f) // ���B�̋��e�͈͂��L����(���B�����Ƃ��ɗh��Ă��܂��̂��ӂ�������)
            {
                speed = 0f;
                transform.position = target.position;
            }
        }
    }
}
