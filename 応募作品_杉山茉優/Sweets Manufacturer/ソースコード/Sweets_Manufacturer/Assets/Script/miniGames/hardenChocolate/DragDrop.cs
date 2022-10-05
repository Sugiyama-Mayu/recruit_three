using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// �N���b�J�[���`���R�ɓ����Q�[����
// �N���b�J�[�̃h���b�O���h���b�v�̏����v���O����
public class DragDrop : MonoBehaviour
{
    public bool startCracker;  // M.S �N���b�J�[�̈ʒu�̏������t���O
    Plane plane;
    bool isGrabbing;
    private int isTrigger;     // 0�͏������ 1�͐ݒu���� 2�͐ݒu����
    public DragDrop cracker1;
    public DragDrop cracker2;
    public DragDrop cracker3;
    public DragDrop cracker4;
    public DragDrop cracker5;
    public DragDrop cracker6;
    public DragDrop cracker7;
    public DragDrop cracker8;
    private GameObject hitObj;
    private Vector3 initialPos; // �N���b�J�[�̏����ʒu�̕ۑ��ϐ�
    public Chocodrop chocodrop;
    void Start()
    {
        initialPos = this.transform.position;       //  M.S �N���b�J�[�̏����ʒu�̕ۑ�
        startCracker = false;                       //  M.S �N���b�J�[�̈ʒu�̏������t���O��false
        plane = new Plane(Vector3.up, Vector3.up);
        isTrigger = 0;
    }
    bool crackerAllRayColl()
    {
        if(cracker1.isGrabbing == false && cracker2.isGrabbing == false 
            && cracker3.isGrabbing == false && cracker4.isGrabbing == false
            && cracker5.isGrabbing == false && cracker6.isGrabbing == false 
            && cracker7.isGrabbing == false && cracker8.isGrabbing == false)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    void Update()
    {
        // M.S �N���b�J�[�̈ʒu�������t���O��true�ŃN���b�J�[��layer��Live�Ń^�O��cracker���ǂ���
        if (startCracker == true && this.gameObject.layer == 11
            && this.gameObject.tag == "cracker")
        {
            this.transform.position = initialPos; // �N���b�J�[�̈ʒu�������ʒu�ɃZ�b�g
            startCracker = false;                 // �N���b�J�[�̈ʒu�������t���O��false
        }
        if (Input.GetMouseButton(0) && isGrabbing == false
            && crackerAllRayColl() == true)
        {
            Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);
            // �}�E�X�̈ʒu�̎擾
            Vector3 mousPos = Input.mousePosition;
            // 3D�Ȃ̂�Z���𓖂Ă͂߂�
            mousPos.z = 10.0f;
            // �}�E�X�̈ʒu��3D�̍��W�ɕύX
            Vector3 mouseWorldPos = Camera.main.ScreenToWorldPoint(mousPos);
            RaycastHit hit;
            if (Physics.Raycast(ray, out hit, Mathf.Infinity))
            {
                if (hit.collider.gameObject.layer == 11 && hit.collider.gameObject.tag == "cracker")
                {
                    hitObj = hit.collider.gameObject;
                    hitObj.transform.eulerAngles = new Vector3(90.0f, 0.0f, 0.0f);
                    // �^��ł���t���O��true
                    isGrabbing = true;
                    // M.S Y���W�ȊO���}�E�X�|�W�V�����ɂ���
                    hit.collider.transform.position = new Vector3(mouseWorldPos.x, hitObj.transform.position.y, mouseWorldPos.z);
                    // M.S �N���b�J�[�̓����蔻����^��ł���Ԃ͏���
                    hitObj.GetComponent<BoxCollider>().enabled = false;
                }
            }
        }
        if (Input.GetMouseButton(0) && isGrabbing == true)
        {
            Vector3 mousPos = Input.mousePosition;
            // 3D�Ȃ̂�Z���𓖂Ă͂߂�
            mousPos.z = 10.0f;
            // �}�E�X�̈ʒu��3D�̍��W�ɕύX
            Vector3 mouseWorldPos = Camera.main.ScreenToWorldPoint(mousPos);
            hitObj.transform.position = new Vector3(mouseWorldPos.x, hitObj.transform.position.y, mouseWorldPos.z);
        }

        if (isGrabbing == true && Input.GetMouseButtonUp(0))
        {
            if (Input.GetMouseButtonUp(0))
            {
                isGrabbing = false;
                // M.S �N���b�J�[�̓����蔻����h���b�v���ɕ���������
                hitObj.GetComponent<BoxCollider>().enabled = true;
            }
        }

    }
    public void SetIsTrigger(int change)
    {
        isTrigger = change;
    }
}
