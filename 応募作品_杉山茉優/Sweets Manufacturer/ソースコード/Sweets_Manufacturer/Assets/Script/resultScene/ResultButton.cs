using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
// M.S
// ���U���g�V�[���ł̃{�^������
public class ResultButton : MonoBehaviour
{
    // �X�N���v�g�ϐ�
    public GameResult gameResult;
    // �^�C�g�����Ă�
    // ��  ���F�Ȃ�
    // �߂�l�F�Ȃ�
    public void CallTitle()
    {
        SceneManager.LoadScene("title");
    }
    // ���g���C����
    // ��  ���F�Ȃ�
    // �߂�l�F�Ȃ�
    public void CallRetry()
    {
        // �V�񂾃X�e�[�W�Ɠ����V�[�����Ă�
        switch (gameResult.sceneNum)
        {
            case 1:
                SceneManager.LoadScene("FirstScene");
                break;
            case 2:
                SceneManager.LoadScene("SecondScene");
                break;
            case 3:
                SceneManager.LoadScene("ThirdScene");
                break;
            case 4:
                SceneManager.LoadScene("ForthScene");
                break;
        }
    }
    // �X�e�[�W�Z���N�g���Ă�
    // ��  ���F�Ȃ�
    // �߂�l�F�Ȃ�
    public void CallStageSelect()
    {
        SceneManager.LoadScene("SelectScene");
    }
}
