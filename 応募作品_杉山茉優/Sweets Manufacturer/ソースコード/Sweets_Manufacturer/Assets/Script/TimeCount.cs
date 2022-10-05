using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
// M.S
// �������Ԃ̊Ǘ�
public class TimeCount : MonoBehaviour
{
    // �ʏ탂�[�h�̃^�C��
    private float time = 300.0f;
    // �c�莞�ԕ\���p�e�L�X�g
    public Text timeCountText;
    // �^�C���I�[�o�[�t���O
    static public bool isTimeUp;
    // ���U���g�V�[������Ă΂��^�C��
    int timeLeft;
    // �X�N���v�g�ϐ�
    public ResultManager resultManager;
    // �e�L�X�g�ɕ\�������鎞��
    int drawTime;
    void Start()
    {
        // ������
        isTimeUp = false;
        // �n�[�h���[�h�Ȃ�Ίe�X�e�[�W���ƂɃ^�C����ݒ�
        if (GameManager.hardmode == true)
        {
            if (resultManager.GetSceneNum() == 4)  // �X�e�[�W4
            {
                time = 420;
            }
            else if (resultManager.GetSceneNum() == 3)  // �X�e�[�W3
            {
                time = 370;
            }
            else if(resultManager.GetSceneNum() == 2)  // �X�e�[�W2
            {
                time = 370;
            }
            else if(resultManager.GetSceneNum() == 1)   // �X�e�[�W1 
            {
                time = 350;
            }
        }
    }
    void Update()
    {
        // �^�C����int�ɃL���X�g���ĕ\���p�^�C���ɂ���
        drawTime = (int)time;
        // �Q�[���N���A�ɂȂ��Ă��Ȃ����ǂ���
        if (resultManager.GetCallGameClear() == false)
        {
            // �^�C���I�[�o�[�łȂ����ǂ���
            if (0 < time)
            {
                // �^�C��������
                time -= Time.deltaTime;
                // int�ɃL���X�g�������Ԃ�\������
                timeCountText.text = drawTime.ToString();
            }
            // �^�C���I�[�o�[���ǂ���
            else if (time <= 0)
            {
                // �^�C���I�[�o�[�t���O��true
                isTimeUp = true;
                // timeLeft�ɃQ�[���I�[�o�[���̃^�C���������
                timeLeft = (int)time;
            }
        }
        else
        {
            // timeLeft�ɃQ�[���N���A���̃^�C���������
            timeLeft = (int)time;
        }
    }
    // �^�C���̃Q�b�^�[
    // ��  ���F�Ȃ�
    // �߂�l�Fint timeLeft   �c�莞��
    public int GetTime()
    {
        return timeLeft;
    }
}
