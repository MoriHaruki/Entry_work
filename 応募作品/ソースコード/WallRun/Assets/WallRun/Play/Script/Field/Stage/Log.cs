using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UIElements;
using static UnityEngine.GraphicsBuffer;

public class Log : MonoBehaviour
{
    public Transform target;  // 目標のオブジェクト
    public Transform player;           // プレイヤーのTransform
    public float interactionDistance;  // プレイヤーとの相互作用距離
    public float speed = 5f;       // 落下速度
    private bool playerInRange = false; // プレイヤーが範囲内にいるか
   
    void Update()
    {
        // プレイヤーとの距離を計算
        float distanceToPlayer = Vector3.Distance(transform.position, player.position);

        // プレイヤーが範囲内に入ったかを判定
        if (distanceToPlayer <= interactionDistance)
        {
            playerInRange = true;
        }
        else
        {
            playerInRange = false;
        }

        // プレイヤーが範囲内に入った場合、オブジェクトを落下させる
        if (playerInRange)
        {
            Debug.Log("範囲内に入って作動したよ");

            // 移動開始時に速度を設定
            Vector3 direction = (target.position - transform.position).normalized;
            // 移動方向に速度を適用
            transform.position += direction * speed * Time.deltaTime;

            // 目標の位置に到達したら速度をゼロにして移動終了
            float distanceToTarget = Vector3.Distance(transform.position, target.position);
            
            if (distanceToTarget <= 0.1f) // 到達の許容範囲を広げる(到達したときに揺れてしまうのをふせぐため)
            {
                speed = 0f;
                transform.position = target.position;
            }
        }
    }
}
