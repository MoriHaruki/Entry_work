using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SavePoint : MonoBehaviour
{
    private bool isRight = false;

    void OnCollisionEnter(Collision collision)
    {
        // �Փ˂��������Tag���`�F�b�N
        if (collision.gameObject.CompareTag("Player"))
        {
            isRight = true;
            //�^�O����v����ꍇ�A���O��\��
            Debug.Log("�������Ă��܂��B");
        }
        else
        {
            isRight = false;
        }
    }

    public bool GetRight(){ return isRight; }
}
