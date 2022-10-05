using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// �C�`�S������Q�[���̃N���b�N����
// �C�`�S�ƃ}�E�X�Ƃ̓����蔻��v���O����
public class Strawpoint : MonoBehaviour
{
    Plane plane;
    bool isGrabbing;
    private bool collBerryJudge;
    Transform cube;
    private int isTrigger;     // 0�͏������ 1�͐ݒu���� 2�͐ݒu����
    public GameObject Berry;
    Rigidbody movestrawBerryRid;
    public BerryCrear berryclear;
    void Start()
    {
        plane = new Plane(Vector3.up, Vector3.up);
        collBerryJudge = false;
        movestrawBerryRid = Berry.GetComponent<Rigidbody>();
    }
    void Update()
    {
        // �}�E�X�̈ʒu�̎擾
        Vector3 mousPos = Input.mousePosition;
        // 3D�Ȃ̂�Z���𓖂Ă͂߂�
        mousPos.z = 5.0f;
        // �}�E�X�̈ʒu��3D�̍��W�ɕύX
        Ray ray = Camera.main.ScreenPointToRay(mousPos);
        RaycastHit hit = new RaycastHit();
        // Vector3 direction = new Vector3(0.0f, 0.0f, 1.0f);
        // �}�E�X�ƐڐG���Ă�����
        if (Physics.Raycast(ray, out hit))
        {
            Vector3 mouseWorldPos = Camera.main.ScreenToWorldPoint(mousPos);
            // Y��
            mouseWorldPos.y = 3.6f;
            // �}�E�X�̈ʒu�ɂ���
            this.transform.position = new Vector3(mouseWorldPos.x, mouseWorldPos.y, mouseWorldPos.z);
            // �������̓����蔻���������
            Berry.GetComponent<BoxCollider>().enabled = false;
        }
    }
    private void OnTriggerEnter(Collider other)
    {
        if (isGrabbing == false)
        {
            GameObject Chocobox;
            Chocobox = GameObject.Find("Main Camera");
            collBerryJudge = true;
            isTrigger = 2;
            Berry.layer = 10;
        }

    }
    public void SetIsTrigger(int change)
    {
        isTrigger = change;
    }
}
