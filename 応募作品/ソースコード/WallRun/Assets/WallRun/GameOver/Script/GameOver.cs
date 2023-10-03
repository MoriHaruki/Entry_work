using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class GameOver : MonoBehaviour
{
    [Header("Fade")] public Fade fade;
    private bool StartPush = false;
    private bool goNextScene = false;

    //���ʉ�
    private AudioSource audioSource = null;
    [Header("�N���b�N���ʉ�")] public AudioClip clickSE;

    public void PlaySE(AudioClip clip)
    {
        if (audioSource != null)
        {
            audioSource.PlayOneShot(clip);
        }
        else
        {
            Debug.Log("�I�[�f�B�I�\�[�X���ݒ肳��ĂȂ����ݒ����������");
        }
    }

    public void PressTitle()
    {
        Debug.Log("Title�{�^������������");

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
            PlaySE(clickSE);
            Cursor.visible = true;
            Cursor.lockState = CursorLockMode.None;
            SceneManager.LoadScene("Title");
            goNextScene = true;
        }

        if (Input.GetKeyDown(KeyCode.Escape))
            Application.Quit();
    }


}
