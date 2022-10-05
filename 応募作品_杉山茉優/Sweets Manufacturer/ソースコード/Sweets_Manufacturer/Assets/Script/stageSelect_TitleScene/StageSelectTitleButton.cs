using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;
// M.S
// �X�e�[�W�Z���N�g�V�[���ƃ^�C�g���V�[���ł̃{�^������
public class StageSelectTitleButton : MonoBehaviour
{
    // �ʏ탂�[�h�ƃn�[�h���[�h�̐؂�ւ��{�^��
    public Button modeChangeButton;
    void Start()
    {
        // �n�[�h���[�h�ɂȂ��Ă�����
        if(GameManager.hardmode == true)
        {
            // �{�^���̐F���V�A���ɂ���
            modeChangeButton.GetComponent<Image>().color = Color.cyan;
        }
    }
    // �Z���N�g�V�[�����Ă�
    // ��  ���F�Ȃ�
    // �߂�l�F�Ȃ�
    public void CallGameSecen()
    {
        SceneManager.LoadScene("SelectScene");
    }
    // �Q�[���̏I��
    // ��  ���F�Ȃ�
    // �߂�l�F�Ȃ�
    public void ExitGame()
    {
        Application.Quit();
    }
    // �X�e�[�W1���Ă�
    // ��  ���F�Ȃ�
    // �߂�l�F�Ȃ�
    public void CallMainGame1()
    {
        SceneManager.LoadScene("FirstScene");
    }
    // �X�e�[�W2���Ă�
    // ��  ���F�Ȃ�
    // �߂�l�F�Ȃ�
    public void CallMainGame2()
    {
        SceneManager.LoadScene("SecondScene");
    }
    // �X�e�[�W3���Ă�
    // ��  ���F�Ȃ�
    // �߂�l�F�Ȃ�
    public void CallMainGame3()
    {
        SceneManager.LoadScene("ThirdScene");
    }
    // �X�e�[�W4���Ă�
    // ��  ���F�Ȃ�
    // �߂�l�F�Ȃ�
    public void CallMainGame4()
    {
        SceneManager.LoadScene("ForthScene");
    }
    // �R���N�V�����V�[�����Ă�
    // ��  ���F�Ȃ�
    // �߂�l�F�Ȃ�
    public void CallPictreBook()
    {
        SceneManager.LoadScene("Collect");
    }
    // �ʏ탂�[�h�E�n�[�h���[�h�̐؂�ւ�
    // ��  ���F�Ȃ�
    // �߂�l�F�Ȃ�
    public void ChangeMode()
    {
        // �n�[�h���[�h���ǂ���
        if(GameManager.hardmode == true)
        {
            // �ʏ탂�[�h�ɂ���
            GameManager.hardmode = false;
            // �{�^���̐F��
            modeChangeButton.GetComponent<Image>().color = Color.white;
        }
        else
        {
            // �n�[�h���[�h�ɂ���
            GameManager.hardmode = true;
            // �{�^���̐F���V�A��
            modeChangeButton.GetComponent<Image>().color = Color.cyan;
        }
    }
}
