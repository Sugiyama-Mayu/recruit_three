using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// M.S
// �I�����W�̈ړ��E�z�u����
public class MoveOrange : MonoBehaviour
{
    // �I�����W�I�u�W�F�N�g
    public GameObject orange;
    private RaycastHit hit;
    // ���C�Ɠ��������I�u�W�F�N�g�������ϐ�
    GameObject hitObj;
    // �}�E�X�̈ʒu
    Vector3 mouseWorldPos;
    private float adjustmentY;     // �ړ��ʒu�̒���Y���W
    private float adjustmentDownY; // �z�u�ʒu�̒���Y���W
    // �����グ���Ă���t���O
    public bool lift;
    // �I�����W�̏����ʒu
    private Vector3 initialObjPos;
    // �������t���O
    public bool startFlag;
    void Start()
    {
        // ������
        startFlag = false;
        lift = false;
        initialObjPos = this.gameObject.transform.position;
        adjustmentY = 0.8f;     // �ړ��ʒu�̒���Y���W
        adjustmentDownY = 0.5f; // �z�u�ʒu�̒���Y���W
    }
    void Update()
    {
        // �������t���O��true�ł܂��z�u����Ă��Ȃ��I�����W���ǂ���
        if (startFlag == true && this.gameObject.tag == "Orange")
        {
            // �I�����W�������ʒu�ɖ߂�
            this.transform.position = initialObjPos;
            startFlag = false;
        }
        // ���{�^�����N���b�N�������ǂ���
        if (Input.GetMouseButtonDown(0))
        {
            // �}�E�X�ʒu���烌�C���΂�
            Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);
            Vector3 direction = new Vector3(0.0f, 0.0f, 1.0f);
            // ��΂������C�ƐڐG���Ă��邩�ǂ���
            if (Physics.Raycast(ray, out hit))
            {
                // ���������I�u�W�F�N�g�̃^�O���܂��z�u����Ă��Ȃ��I�����W���ǂ���
                if (hit.collider.gameObject.tag == "Orange")
                {
                    // ���������I�u�W�F�N�g��hitObj�ɕۑ�
                    hitObj = hit.collider.gameObject;
                    // �����グ���Ă���t���O��true
                    lift = true;
                }
            }
        }
        // �J�[�\���ʒu�̎擾
        Vector3 mousPos = Input.mousePosition;
        // 3D�Ȃ̂�Z���𓖂Ă͂߂�
        mousPos.z = 7.0f;
        // �}�E�X�̈ʒu��3D�̍��W�ɕύX
        Vector3 mouseWorldPos = Camera.main.ScreenToWorldPoint(mousPos);
        // �I�����W��Y��
        mouseWorldPos.y = adjustmentY + initialObjPos.y;
        // ���{�^���������Ă��邩�ǂ���
        if (Input.GetMouseButton(0))
        {
            // �����グ���Ă��āA�܂��z�u����Ă��Ȃ��I�����W���ǂ���
            if (lift == true && hitObj.tag == "Orange")
            {
                // �����グ���Ă���I�����W�̃{�b�N�X�R���C�_�[���A�N�e�B�u�ɂ���
                hitObj.GetComponent<BoxCollider>().enabled = false;
                // �}�E�X�̈ʒu�ɃI�����W���グ��
                hit.transform.position 
                    = new Vector3(mouseWorldPos.x, mouseWorldPos.y, mouseWorldPos.z);
            }
        }
        // ���{�^���𗣂������ǂ���
        if (Input.GetMouseButtonUp(0))
        {
            // �����グ���Ă��āA�܂��z�u����Ă��Ȃ��I�����W���ǂ���
            if (lift == true && hitObj.tag == "Orange")
            {
                // �����グ���Ă���t���O��false
                lift = false;
                // �I�����W��Y��
                mouseWorldPos.y = adjustmentDownY + initialObjPos.y;
                // �I�����W��z�u����
                hitObj.transform.position 
                    = new Vector3(mouseWorldPos.x, mouseWorldPos.y, mouseWorldPos.z);
                // �I�����W�̃{�b�N�X�R���C�_�[���A�N�e�B�u�ɂ���
                hitObj.GetComponent<BoxCollider>().enabled = true;
            }
        }
    }
}
