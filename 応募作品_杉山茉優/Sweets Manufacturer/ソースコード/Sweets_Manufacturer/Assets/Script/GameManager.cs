using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// M.S 
// �`���[�g���A����{���Ȃǂ̐ݒ�
public class GameManager : MonoBehaviour
{
    public int GameStatus = 0;    // �J�����ύX����
    public int tutorialOrder = 0; // �`���[�g���A���\������
    public GameObject firstText;  // �`���[�g���A���e�L�X�g1
    public GameObject secondText; // �`���[�g���A���e�L�X�g2
    public GameObject thirdText;  // �`���[�g���A���e�L�X�g3
    public ResultManager resultManager;

    Camera cam;                     // �J����
    public Vector3 offset;          // �J�����̈ʒu�ϐ�
    public static bool hardmode;    // �n�[�h���[�hON�t���O
    private void Start()
    {
        cam = Camera.main;
        // �n�[�h���[�h�̏ꍇ�A�{���ɂ���
        if (hardmode == true)
        {
            Time.timeScale = 2;
        }
        else
        {
            Time.timeScale = 1;
        }
    }
    void Update()
    {
        // �n�[�h���[�h�ł͂Ȃ��A�X�e�[�W1�̏ꍇ
        if (hardmode != true && resultManager.nowSeceneNum == 1) {
            // �`���[�g���A���e�L�X�g�̕\��
            if (tutorialOrder == 0)
            {
                StartCoroutine("FirstText");  
            } else if (tutorialOrder == 2)
            {
                StartCoroutine("SecondText");
            } else if (tutorialOrder == 5)
            {
                StartCoroutine("ThirdText");
            }
        }       
    }    
    // �v���C���[������ʒu�ɃJ�����̈ʒu��ς���֐�
    // ��  ���F�Ȃ�
    // �߂�l�F�Ȃ�
    public void ChangeMiniGamePosCamera()
    {
        if (GameStatus == 1)
        {
            offset = new Vector3(20, 2.3f, 0.2f);
            cam.transform.position = offset;
            cam.transform.rotation = Quaternion.Euler(73, 0, 0);
        }      
    }
    // �~�j�Q�[���ʒu�ɃJ�����̈ʒu��ς���֐�
    // ��  ���F�Ȃ�
    // �߂�l�F�Ȃ�
    public void ChangeMainPosCamera()
    {
        if (GameStatus == 0)
        {
            // �ʏ펞�̃J�����̈ʒu
            offset = new Vector3(0, 9.0f, -4.0f);
            cam.transform.position = offset;
            cam.transform.rotation = Quaternion.Euler(70, 0, 0);
        }
    }
    // �`���[�g���A���e�L�X�g1�̕\��
    IEnumerator FirstText()
    {
        firstText.SetActive(true);
        tutorialOrder = 1;
        Time.timeScale = 0;
        yield return new WaitForSecondsRealtime(5.0f);
        firstText.SetActive(false);
        Time.timeScale = 1;
        tutorialOrder = 2;   
    }
    // �`���[�g���A���e�L�X�g2�̕\��
    IEnumerator SecondText()
    {
        secondText.SetActive(true);
        tutorialOrder = 3;
        Time.timeScale = 0;
        yield return new WaitForSecondsRealtime(5.0f);
        secondText.SetActive(false);
        Time.timeScale = 1;
        tutorialOrder = 4;
    }
    // �`���[�g���A���e�L�X�g3�̕\��
    IEnumerator ThirdText()
    {
        thirdText.SetActive(true);
        tutorialOrder = 6;
        Time.timeScale = 0;
        yield return new WaitForSecondsRealtime(5.0f);
        thirdText.SetActive(false);
        Time.timeScale = 1;
        tutorialOrder = 7;
    }
}
