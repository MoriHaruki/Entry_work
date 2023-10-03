using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;

public class FloatingObject : MonoBehaviour
{
    public Transform player;           // �v���C���[��Transform
    public float interactionDistance;  // �v���C���[�Ƃ̑��ݍ�p����
    public float fallSpeed = 5f;       // �������x
    public float inactive_range = -30f;
    private bool playerInRange = false; // �v���C���[���͈͓��ɂ��邩
    private bool falling = false;       // �I�u�W�F�N�g����������
    private Rigidbody rb;              // �I�u�W�F�N�g��Rigidbody



    private void Start()
    {
        rb = GetComponent<Rigidbody>();
        rb.useGravity = false; // �ŏ��͏d�͂��I�t�ɂ���
    }

    private void Update()
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
        if (playerInRange && !falling)
        {
            falling = true;
            rb.useGravity = true; // �d�͂��I���ɂ���
        }

        // �I�u�W�F�N�g�����������ڕW�ʒu�ɓ��B�����ꍇ�A�I�u�W�F�N�g���A�N�e�B�u�ɂ���
        if (falling && transform.position.y <= inactive_range)
        {
            gameObject.SetActive(false); // �I�u�W�F�N�g���A�N�e�B�u�ɂ���
        }
    }
}
