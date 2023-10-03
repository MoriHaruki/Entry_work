using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Bridge : MonoBehaviour
{
    public Transform target;  // 目標のオブジェクト
    public float speed = 5.0f;  // 移動速度
    private bool isMove = false;        //移動していているか

    //橋の降下
    public void MoveBridge()
    {
        if (target != null)
        {
            isMove = true;

            // 目標の位置を取得
            Vector3 targetPosition = target.position;

            // 自分の位置から目標の位置へ向かうベクトルを計算
            Vector3 moveDirection = targetPosition - transform.position;

            // ベクトルの長さを1に正規化し、速度を掛けて移動
            transform.Translate(moveDirection.normalized * speed * Time.deltaTime);

        }        
    }


    private void Update()
    {
        MoveBridge();
    }

    public bool GetIsMove() { return isMove; }	//ドアの移動状態取得
}
