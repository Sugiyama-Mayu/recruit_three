using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// M.S
// �f�B�|�W�b�^�[�̈ړ�����
public class MoveDipositor : MonoBehaviour
{
    // �f�B�|�W�b�^�[�I�u�W�F�N�g
    public GameObject dipositor;
    private float adjustmentX; // �ړ��ʒu�̒���X���W
    private float adjustmentY; // �ړ��ʒu�̒���Z���W
    private void Start()
    {
        adjustmentX = 5.0f; // �ړ��ʒu�̒���X���W
        adjustmentY = 4.0f; // �ړ��ʒu�̒���Z���W
    }
    void Update()
    {
        // �f�B�|�W�b�^�[�̃{�b�N�X�R���C�_�[���A�N�e�B�u�ɂ���
        dipositor.GetComponent<BoxCollider>().enabled = false;
        // �}�E�X�̈ʒu�̎擾
        Vector3 mousPos = Input.mousePosition;
        // 3D�Ȃ̂�Z���𓖂Ă͂߂�
        mousPos.z = 8.0f;
        // �}�E�X�̈ʒu��3D�̍��W�ɕύX
        Vector3 mouseWorldPos = Camera.main.ScreenToWorldPoint(mousPos);
        // �f�B�|�W�b�^�[�̈ʒu�̒���
        mouseWorldPos.y = this.gameObject.transform.position.y;
        mouseWorldPos.x = mouseWorldPos.x + adjustmentX;
        mouseWorldPos.z = mouseWorldPos.z + adjustmentY;
        // �}�E�X�̈ʒu�Ƀf�B�|�W�b�^�[��u��
        dipositor.transform.position = mouseWorldPos;

        // ���{�^���������Ă��邩�ǂ���
        if (Input.GetMouseButton(0))
        {
            // �f�B�|�W�b�^�[�̃{�b�N�X�R���C�_�[���A�N�e�B�u�ɂ���
            dipositor.GetComponent<BoxCollider>().enabled = true;
        }
    }
}
