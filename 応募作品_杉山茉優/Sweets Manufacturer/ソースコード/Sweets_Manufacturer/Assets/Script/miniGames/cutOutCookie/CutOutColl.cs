using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// M.S
// �^���������N�b�L�[�I�u�W�F�N�g�̏�������
// �N�b�L�[�̌^�����Q�[���̓����蔻��v���O����(�^�����̌�)
public class CutOutColl : MonoBehaviour
{
    // �����^�̃I�u�W�F�N�g
    public MoveCutOut moveCutOut;
    // �^���������N�b�L�[�̃I�u�W�F�N�g
    public GameObject cutOutDough;
    // �������t���O
    public bool startFlag;
    // �����ʒu
    private Vector3 initialPos;
    void Start()
    {
        // �����ʒu�ɂ��̃I�u�W�F�N�g(�^�����̌�)�̔����ʒu��ۑ�
        initialPos = this.gameObject.transform.position;
        // �������t���O��false
        startFlag = false;
    }
    void Update()
    {
        // �m�F�p:���[�v�ł��̃v���O������ʂ�����+1
        moveCutOut.cookieStampNum++;
        // �������t���O��true���ǂ���
        if(startFlag == true)
        {
            // �^�����̌����A�N�e�B�u�ɂ���
            this.gameObject.SetActive(false);
            // �������t���O��false
            startFlag = false;
            // �^���������N�b�L�[�̊p�x��������
            cutOutDough.transform.eulerAngles = new Vector3(0.0f, 180.0f, 0.0f);
            // �^���������N�b�L�[���A�N�e�B�u�ɂ���
            cutOutDough.SetActive(false);
        }
    }
    // �I�u�W�F�N�g�ƌ^�����̌����ڐG���Ă��邩
    private void OnTriggerEnter(Collider other)
    {
        // �^�����̌��������^�ƐڐG�������ǂ���
        if (other.gameObject.tag == "CutOut")
        {
            // �^�����̌��ƐڐG���Ă�����colList�ɂ��̃I�u�W�F�N�g��ǉ�
            moveCutOut.SetCutOutCol(this.gameObject);
        }
    }
}
