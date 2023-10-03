using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Title : MonoBehaviour
{
    [Header("Fade")] public Fade fade;
    private bool StartPush = false;
    private bool goNextScene = false;
    private bool start = false;
    private bool stageselect = false;

    public void PressStart()
    {
        Debug.Log("�X�^�[�g�{�^������������");
        start = true;
        if (!StartPush)
        {
            Debug.Log("�V�[���ړ�");
            fade.StartFadeOut();
            StartPush = true;
        }
        
    }

    public void PressStageSelect()
    {
        Debug.Log("�X�^�[�g�{�^������������");
        stageselect = true;
        if (!StartPush)
        {
            Debug.Log("�V�[���ړ�");
            fade.StartFadeOut();
            Cursor.visible = true;
            Cursor.lockState = CursorLockMode.None;
            StartPush = true;
        }

    }

    private void Update()
    {
        if(!goNextScene && fade.IsFadeOutComplete())
        {
            if(start)
            {
                SceneManager.LoadScene("game1");
                goNextScene = true;
            }

            if (stageselect)
            {
                Cursor.lockState = CursorLockMode.None;
                SceneManager.LoadScene("StageSelect");
                goNextScene = true;
            }
        }
    }
}
