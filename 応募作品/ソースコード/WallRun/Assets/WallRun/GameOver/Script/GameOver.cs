using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class GameOver : MonoBehaviour
{
    [Header("Fade")] public Fade fade;
    private bool StartPush = false;
    private bool goNextScene = false;

    //効果音
    private AudioSource audioSource = null;
    [Header("クリック効果音")] public AudioClip clickSE;

    public void PlaySE(AudioClip clip)
    {
        if (audioSource != null)
        {
            audioSource.PlayOneShot(clip);
        }
        else
        {
            Debug.Log("オーディオソースが設定されてないぞ設定を見直しな");
        }
    }

    public void PressTitle()
    {
        Debug.Log("Titleボタンを押したね");

        if (!StartPush)
        {
            Debug.Log("シーン移動");
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
