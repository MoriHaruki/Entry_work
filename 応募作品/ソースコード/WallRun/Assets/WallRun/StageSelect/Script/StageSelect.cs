using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class StageSelect : MonoBehaviour
{
    [Header("Fade")] public Fade fade;
    private bool StartPush = false;
    private bool goNextScene = false;
    private bool game1 = false;
    private bool game2 = false;
    private bool game3 = false;

    public void PressGame1()
    {
        game1 = true;
        Debug.Log("1ボタンを押したね");

        if (!StartPush)
        {
            Debug.Log("シーン移動");
            fade.StartFadeOut();
            StartPush = true;
        }

    }

    public void PressGame2()
    {
        game2 = true;
        Debug.Log("2ボタンを押したね");

        if (!StartPush)
        {
            Debug.Log("シーン移動");
            fade.StartFadeOut();
            StartPush = true;
        }

    }

    public void PressGame3()
    {
        game3 = true;
        Debug.Log("3ボタンを押したね");

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
            Cursor.visible = true;
           
            if(game1)
            {
                Cursor.lockState = CursorLockMode.None;
                SceneManager.LoadScene("game1");
                goNextScene = true;
            }

            if (game2)
            {
                Cursor.lockState = CursorLockMode.None;
                SceneManager.LoadScene("game2");
                goNextScene = true;
            }

            if (game3)
            {
                Cursor.lockState = CursorLockMode.None;
                SceneManager.LoadScene("game3");
                goNextScene = true;
            }

        }

        if (Input.GetKeyDown(KeyCode.Escape))
            Application.Quit();
    }
}
