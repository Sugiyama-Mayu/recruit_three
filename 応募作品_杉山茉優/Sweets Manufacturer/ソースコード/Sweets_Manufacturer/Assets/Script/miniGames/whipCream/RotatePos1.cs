using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// M.S 
// �{�E����������Q�[���̓����蔻��1�̏���
public class RotatePos1 : MonoBehaviour
{
    // 1��]�m�F�I�u�W�F�N�g1
    public GameObject rotatePos1;
    // 1��]�m�F�I�u�W�F�N�g1�ƖA���Ċ�̓����蔻��ۑ��ϐ�
    private bool rotate1;
    // �`���R�̃{�E���������ꍇ�̃{�E���\�ʂ���]������I�u�W�F�N�g
    public GameObject chocoPlate;
    // �`���R�̃{�E�����ǂ����t���O
    public bool isChoco;
    void Start()
    {
        // ������
        rotate1 = false;
    }   
    private void OnTriggerEnter(Collider other)
    {
        // �܂��A���Ċ�Ɠ������Ă��Ȃ����ǂ���
        if (rotate1 == false)
        {
            // �����蔻���ۑ�
            rotate1 = true;
            // �`���R�̃{�E�����ǂ���
            if (isChoco == true)
            {
                // �{�E���̕\�ʂ���]������
                chocoPlate.transform.Rotate(0.0f, 90.0f, 0.0f);
            }
        }
    }
    // 1��]�m�F�I�u�W�F�N�g1�̖A���Ċ�Ƃ̓����蔻��̃Q�b�^�[�A�Z�b�^�[
    // �Q�b�^�[�Fbool rotate1   true �������Ă��� false �������Ă��Ȃ�
    // �Z�b�^�[�Fbool           true �������Ă��� false �������Ă��Ȃ�
    public bool RotateTerritoryFlag
    {
        get { return rotate1; }
        set { rotate1 = value; }
    }
}