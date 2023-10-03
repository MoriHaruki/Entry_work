using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Clear : MonoBehaviour
{
    [Header("Fade")] public Fade fade;
    private bool StartPush = false;
    private bool goNextScene = false;

    public void PressClear()
    {
        Debug.Log("�X�^�[�g�{�^������������");

        if (!StartPush)
        {
            Debug.Log("�V�[���ړ�");
            fade.StartFadeOut();
            StartPush = true;
        }
    }

    private void Update()
    {
        if (!goNextScene && fade.IsFadeOutComplete())
        {
            Cursor.visible = true;
            Cursor.lockState = CursorLockMode.None;
            SceneManager.LoadScene("Title");
            goNextScene = true;
        }

        if (Input.GetKeyDown(KeyCode.Escape))
            Application.Quit();
    }
}