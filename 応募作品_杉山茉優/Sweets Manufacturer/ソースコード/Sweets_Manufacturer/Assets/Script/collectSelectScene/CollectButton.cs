using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO;
using UnityEngine.SceneManagement;
// M.S
// �R���N�V�����V�[���̃{�^���A�I������
public class CollectButton : MonoBehaviour
{
    public Collect collect;
    // �P�[�L�I�u�W�F�̑I��
    // ��  ���F�Ȃ�
    // �߂�l�F�Ȃ�
    public void CakePush()
    {
        collect.collectSelectNum = 0;
    }
    // ���̃P�[�L�I�u�W�F�̑I��
    // ��  ���F�Ȃ�
    // �߂�l�F�Ȃ�
    public void GoldCakePush()
    {
        collect.collectSelectNum = 1;
    }
    // �`���R�N���b�J�[�̑I��
    // ��  ���F�Ȃ�
    // �߂�l�F�Ȃ�
    public void ChocoPush()
    {
        collect.collectSelectNum = 2;
    }
    // ���̃`���R�N���b�J�[�̑I��
    // ��  ���F�Ȃ�
    // �߂�l�F�Ȃ�
    public void GoldChocoPush()
    {
        collect.collectSelectNum = 3;
    }
    // �[���[�̑I��
    // ��  ���F�Ȃ�
    // �߂�l�F�Ȃ�
    public void JellyPush()
    {
        collect.collectSelectNum = 4;
    }
    // ���̃[���[�̑I��
    // ��  ���F�Ȃ�
    // �߂�l�F�Ȃ�
    public void GoldJellyPush()
    {
        collect.collectSelectNum = 5;
    }
    // �N�b�L�[�̑I��
    // ��  ���F�Ȃ�
    // �߂�l�F�Ȃ�
    public void CookiePush()
    {
        collect.collectSelectNum = 6;
    }
    // ���̃N�b�L�[�̑I��
    // ��  ���F�Ȃ�
    // �߂�l�F�Ȃ�
    public void GoldCookiePush()
    {
        collect.collectSelectNum = 7;
    }
    // �X�e�[�W1�g���t�B�[�̑I��
    // ��  ���F�Ȃ�
    // �߂�l�F�Ȃ�
    public void RedTrophyPush()
    {
        collect.collectSelectNum = 8;
    }
    // �X�e�[�W2�g���t�B�[�̑I��
    // ��  ���F�Ȃ�
    // �߂�l�F�Ȃ�
    public void GreenTrophyPush()
    {
        collect.collectSelectNum = 9;
    }
    // �X�e�[�W3�g���t�B�[�̑I��
    // ��  ���F�Ȃ�
    // �߂�l�F�Ȃ�
    public void YellowTrophyPush()
    {
        collect.collectSelectNum = 10;
    }
    // �X�e�[�W4�g���t�B�[�̑I��
    // ��  ���F�Ȃ�
    // �߂�l�F�Ȃ�
    public void BlueTrophyPush()
    {
        collect.collectSelectNum = 11;
    }
    // �I�[���X�e�[�W�g���t�B�[�̑I��
    // ��  ���F�Ȃ�
    // �߂�l�F�Ȃ�
    public void CrystalTrophyPush()
    {
        collect.collectSelectNum = 12;
    }
    // �R���N�V�����I�u�W�F�N�g�I���̐i�ރ{�^��
    // ��  ���F�Ȃ�
    // �߂�l�F�Ȃ�
    public void RightButtonPush()
    {
        collect.collectSelectNum++;
        if (collect.collectSelectNum > 12)
        {
            collect.collectSelectNum = 0;
        }
    }
    // �R���N�V�����I�u�W�F�N�g�I���̖߂�{�^��
    // ��  ���F�Ȃ�
    // �߂�l�F�Ȃ�
    public void LeftButtonPush()
    {
        collect.collectSelectNum--;
        if (collect.collectSelectNum < 0)
        {
            collect.collectSelectNum = 12;
        }
    }
    // �Q�[���Z���N�g�V�[���Ɉڂ�
    // ��  ���F�Ȃ�
    // �߂�l�F�Ȃ�
    public void CallGameSecen()
    {
        SceneManager.LoadScene("SelectScene");
    }
}