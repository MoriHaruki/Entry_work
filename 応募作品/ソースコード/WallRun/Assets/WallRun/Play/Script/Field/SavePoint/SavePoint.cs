using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SavePoint : MonoBehaviour
{
    private bool isRight = false;

    void OnCollisionEnter(Collision collision)
    {
        // 衝突した相手のTagをチェック
        if (collision.gameObject.CompareTag("Player"))
        {
            isRight = true;
            //タグが一致する場合、ログを表示
            Debug.Log("当たっています。");
        }
        else
        {
            isRight = false;
        }
    }

    public bool GetRight(){ return isRight; }
}
