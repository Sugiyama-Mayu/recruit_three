using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// M.S 
// �{�E����������Q�[���̓����蔻��4�̏���
public class RotatePos4 : MonoBehaviour
{
    // 1��]�m�F�I�u�W�F�N�g4
    public GameObject rotatePos4;
    // 1��]�m�F�I�u�W�F�N�g4�ƖA���Ċ�̓����蔻��ۑ��ϐ�
    private bool rotate4;
    // �`���R�̃{�E���������ꍇ�̃{�E���\�ʂ���]������I�u�W�F�N�g
    public GameObject chocoPlate;
    // �`���R�̃{�E�����ǂ����t���O
    public bool isChoco;
    void Start()
    {
        // ������
        rotate4 = false;
    }
    private void OnTriggerEnter(Collider other)
    {
        // �܂��A���Ċ�Ɠ������Ă��Ȃ����ǂ���
        if (rotate4 == false)
        {
            // �����蔻���ۑ�
            rotate4 = true;
            // �`���R�̃{�E�����ǂ���
            if (isChoco == true)
            {
                // �{�E���̕\�ʂ���]������
                chocoPlate.transform.Rotate(0.0f, 90.0f, 0.0f);
            }
        }
    }
    // 1��]�m�F�I�u�W�F�N�g4�̖A���Ċ�Ƃ̓����蔻��̃Q�b�^�[�A�Z�b�^�[
    // �Q�b�^�[�Fbool rotate1   true �������Ă��� false �������Ă��Ȃ�
    // �Z�b�^�[�Fbool           true �������Ă��� false �������Ă��Ȃ�
    public bool RotateTerritoryFlag
    {
        get { return rotate4; }
        set { rotate4 = value; }
    }
}
