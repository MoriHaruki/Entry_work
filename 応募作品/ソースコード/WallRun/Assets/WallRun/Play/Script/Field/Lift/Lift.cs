
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Lift : MonoBehaviour
{
    public Transform liftPlatform;       // リフトのプラットフォームのTransform
    public float moveSpeed = 2f;         // リフトの移動速度
    public float topPosition = 4f;       // リフトの最上位置
    public float bottomPosition = 0f;    // リフトの最下位置

    private bool movingUp = true;        // リフトが上に移動中かどうかのフラグ

    private void Update()
    {
        // リフトの移動
        MoveLift();
    }

    private void MoveLift()
    {
        // 移動方向を決定
        Vector3 targetPosition = movingUp ? new Vector3(liftPlatform.position.x, topPosition, liftPlatform.position.z) :
                                            new Vector3(liftPlatform.position.x, bottomPosition, liftPlatform.position.z);

        // プラットフォームを目標位置に向かって移動
        liftPlatform.position = Vector3.MoveTowards(liftPlatform.position, targetPosition, moveSpeed * Time.deltaTime);

        // 目標位置に到達したら移動方向を反転
        if (liftPlatform.position == targetPosition)
        {
            movingUp = !movingUp;
        }
    }
}