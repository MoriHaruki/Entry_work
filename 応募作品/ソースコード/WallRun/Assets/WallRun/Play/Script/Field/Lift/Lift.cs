
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Lift : MonoBehaviour
{
    public Transform liftPlatform;       // ���t�g�̃v���b�g�t�H�[����Transform
    public float moveSpeed = 2f;         // ���t�g�̈ړ����x
    public float topPosition = 4f;       // ���t�g�̍ŏ�ʒu
    public float bottomPosition = 0f;    // ���t�g�̍ŉ��ʒu

    private bool movingUp = true;        // ���t�g����Ɉړ������ǂ����̃t���O

    private void Update()
    {
        // ���t�g�̈ړ�
        MoveLift();
    }

    private void MoveLift()
    {
        // �ړ�����������
        Vector3 targetPosition = movingUp ? new Vector3(liftPlatform.position.x, topPosition, liftPlatform.position.z) :
                                            new Vector3(liftPlatform.position.x, bottomPosition, liftPlatform.position.z);

        // �v���b�g�t�H�[����ڕW�ʒu�Ɍ������Ĉړ�
        liftPlatform.position = Vector3.MoveTowards(liftPlatform.position, targetPosition, moveSpeed * Time.deltaTime);

        // �ڕW�ʒu�ɓ��B������ړ������𔽓]
        if (liftPlatform.position == targetPosition)
        {
            movingUp = !movingUp;
        }
    }
}