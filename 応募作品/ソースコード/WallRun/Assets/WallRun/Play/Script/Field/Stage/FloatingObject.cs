using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;

public class FloatingObject : MonoBehaviour
{
    public Transform player;           // プレイヤーのTransform
    public float interactionDistance;  // プレイヤーとの相互作用距離
    public float fallSpeed = 5f;       // 落下速度
    public float inactive_range = -30f;
    private bool playerInRange = false; // プレイヤーが範囲内にいるか
    private bool falling = false;       // オブジェクトが落下中か
    private Rigidbody rb;              // オブジェクトのRigidbody



    private void Start()
    {
        rb = GetComponent<Rigidbody>();
        rb.useGravity = false; // 最初は重力をオフにする
    }

    private void Update()
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
        if (playerInRange && !falling)
        {
            falling = true;
            rb.useGravity = true; // 重力をオンにする
        }

        // オブジェクトが落下中かつ目標位置に到達した場合、オブジェクトを非アクティブにする
        if (falling && transform.position.y <= inactive_range)
        {
            gameObject.SetActive(false); // オブジェクトを非アクティブにする
        }
    }
}
