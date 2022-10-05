using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// M.S
// �{�E����������Q�[���̖A���Ċ�̈ړ�
public class MoveWhisk : MonoBehaviour
{
    // �A���Ċ�̃I�u�W�F�N�g
    public GameObject whisk;
    // �A���Ċ�̏����ʒu
    private Vector3 initialPos;
    void Start()
    {
        // �A���Ċ�̏����ʒu�̕ۑ�
        initialPos = this.gameObject.transform.position;
    }
    private void Update()
    {
        // ���N���b�N��������
        if (Input.GetMouseButton(0))
        {
            // �}�E�X�̈ʒu�̎擾
            Vector3 mousPos = Input.mousePosition;
            // 3D�Ȃ̂�Z���𓖂Ă͂߂�
            mousPos.z = 5.0f;
            // �}�E�X�̈ʒu��3D�̍��W�ɕύX
            Vector3 mouseWorldPos = Camera.main.ScreenToWorldPoint(mousPos);
            // �A���Ċ��Y���W�������ʒu��Y���W�ɂ���
            mouseWorldPos.y = initialPos.y;
            // �}�E�X�̈ʒu�ɖA���Ċ��u��
            whisk.transform.position =
                new Vector3(mouseWorldPos.x, mouseWorldPos.y, mouseWorldPos.z);
        }
    }
}
