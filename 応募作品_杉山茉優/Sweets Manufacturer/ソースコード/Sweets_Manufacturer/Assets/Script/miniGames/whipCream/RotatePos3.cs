using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// M.S 
// �{�E����������Q�[���̓����蔻��3�̏���
public class RotatePos3 : MonoBehaviour
{
    // 1��]�m�F�I�u�W�F�N�g3
    public GameObject rotatePos3;
    // 1��]�m�F�I�u�W�F�N�g3�ƖA���Ċ�̓����蔻��ۑ��ϐ�
    private bool rotate3;
    // �`���R�̃{�E���������ꍇ�̃{�E���\�ʂ���]������I�u�W�F�N�g
    public GameObject chocoPlate;
    // �`���R�̃{�E�����ǂ����t���O
    public bool isChoco;
    void Start()
    {
        // ������
        rotate3 = false;
    }
    private void OnTriggerEnter(Collider other)
    {
        // �܂��A���Ċ�Ɠ������Ă��Ȃ����ǂ���
        if (rotate3 == false)
        {
            // �����蔻���ۑ�
            rotate3 = true;
            // �`���R�̃{�E�����ǂ���
            if (isChoco == true)
            {
                // �{�E���̕\�ʂ���]������
                chocoPlate.transform.Rotate(0.0f, 90.0f, 0.0f);
            }
        }
    }
    // 1��]�m�F�I�u�W�F�N�g3�̖A���Ċ�Ƃ̓����蔻��̃Q�b�^�[�A�Z�b�^�[
    // �Q�b�^�[�Fbool rotate1   true �������Ă��� false �������Ă��Ȃ�
    // �Z�b�^�[�Fbool           true �������Ă��� false �������Ă��Ȃ�
    public bool RotateTerritoryFlag
    {
        get { return rotate3; }
        set { rotate3 = value; }
    }
}
