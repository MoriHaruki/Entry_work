using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Fade : MonoBehaviour
{
    [Header("Fade")] public bool firstFadeInComp;

    private Image image = null;
    private int frameCount = 0; //カウント用
    private float timer = 0f;
    private bool fadeIn = false;
    private bool fadeOut = false;
    private bool compFadeIn = false;
    private bool compFadeOut = false;

    //フェードインを開始する
    public void StartFadeIn()
    {
        if(fadeIn || fadeOut)
        {
            return;
        }
        fadeIn = true;
        compFadeIn = false;
        timer = 0f;
        image.color = new Color(1, 1, 1, 1);
        image.fillAmount = 1;
        image.raycastTarget = true;
    }

    public bool IsFadeInComplete()
    {
        return compFadeIn;
    }

    //フェードアウト終了
    public void StartFadeOut()
    {
        if (fadeIn || fadeOut)
        {
            return;
        }
        fadeOut = true;
        compFadeOut = false;
        timer = 0f;
        image.color = new Color(1, 1, 1, 0);
        image.fillAmount = 0;
        image.raycastTarget = true;
    }

    //フェードアウトを確認
    public bool IsFadeOutComplete()
    {
        return compFadeOut;
    }

    // Start is called before the first frame update
    void Start()
    {
        image = GetComponent<Image>();

        if(firstFadeInComp)
        {
            FadeInComplete();
        }
        else
        {
            FadeOutComplete();
        }
    }

    // Update is called once per frame
    void Update()
    {
        //スムーズにFaedさせるため２フレーム待つ（デルタタイム）
        if(frameCount > 2)
        {
            if(fadeIn)
            {
                FadeInUpdate();
            }

            else if(fadeOut)
            {
                FadeOutUpdate();
            }
        }
        ++frameCount;
    }

    private void FadeInUpdate()
    {
        //フェード中
        if (timer < 1f)
        {
            image.color = new Color(1, 1, 1, 1 - timer);
            image.fillAmount = 1 - timer;
        }
        //フェード終了
        else
        {
            FadeInComplete();
        }
        timer += Time.deltaTime;
    }

    private void FadeOutUpdate()
    {
        if(timer < 1f)
        {
            image.color = new Color(1, 1, 1, timer);
            image.fillAmount = timer;
        }
        else
        {
            FadeOutComplete();
        }
        timer += Time.deltaTime;
    }

    private void FadeInComplete()
    {
        image.color = new Color(1, 1, 1, 0);
        image.fillAmount = 0;
        image.raycastTarget = false;
        timer = 0f;
        fadeIn = false;
        compFadeIn = true;
    }

    private void FadeOutComplete()
    {
        image.color = new Color(1, 1, 1, 1);
        image.fillAmount = 1;
        image.raycastTarget = false;
        timer = 0f;
        fadeOut = false;
        compFadeOut = true;
    }
}

