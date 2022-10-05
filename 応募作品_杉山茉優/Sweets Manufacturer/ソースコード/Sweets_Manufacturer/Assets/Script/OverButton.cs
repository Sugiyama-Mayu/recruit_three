using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
// M.S
// �Q�[���I�[�o�[���̃{�^������
public class OverButton : MonoBehaviour
{
    // �X�N���v�g�ϐ�
    public ResultManager resultManager;
    // �폜����I�u�W�F�N�g
    public GameObject destroyObj;
    //�^�C�g�����Ă�
    // ��  ���F�Ȃ�
    // �߂�l�F�Ȃ�
    public void CallTitle()
    {
        SceneManager.LoadScene("title");
        Destroy(destroyObj);  // �I�u�W�F�N�g���폜
    }
    // ���g���C����
    // ��  ���F�Ȃ�
    // �߂�l�F�Ȃ�
    public void CallRetry()
    {
        // �V�񂾃X�e�[�W�Ɠ����V�[�����Ă�
        switch (resultManager.nowSeceneNum)
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
        Destroy(destroyObj);  // �I�u�W�F�N�g���폜
    }
    // �X�e�[�W�Z���N�g���Ă�
    // ��  ���F�Ȃ�
    // �߂�l�F�Ȃ�
    public void CallStageSelect()
    {
        SceneManager.LoadScene("SelectScene");
        Destroy(destroyObj);  // �I�u�W�F�N�g���폜
    }
}
