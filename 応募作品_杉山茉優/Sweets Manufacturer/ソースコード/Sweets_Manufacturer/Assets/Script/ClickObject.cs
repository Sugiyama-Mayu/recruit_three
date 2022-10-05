using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// M.S
// �v���C���[�����X�N���v�g
public class ClickObject : MonoBehaviour
{
    private RaycastHit hit;
    private GameObject hitObj; // �q�b�g�����I�u�W�F�N�g
    private string hitObjName; // �q�b�g�����I�u�W�F�N�g�̖��O
    public GameObject player;  // �v���C�L�����I�u�W�F�N�g
    private bool hitObjFlag;   // �I�u�W�F�N�g��ǂ�������t���O
    private float speed;       // �v���C�L�����̈ړ��X�s�[�h
    private string hitObjTag;  // �ǂ�������I�u�W�F�N�g�̃^�O
    public GameObject mapCenter;  // �}�b�v�̒����I�u�W�F�N�g
    public Animator animatorChef; // �v���C�L�����̃A�j���[�^�[

    // �ΏۃI�u�W�F�N�g�Ƀ^�O���ݒ肳��ĂȂ���Γ����܂���B
    void Start()
    {
        hitObjFlag = false;
        speed = 3.0f;        // �����X�s�[�h
    }
    void Update()
    {
        if (hitObjFlag == true)
        {
            // �I�u�W�F�N�g���Q�[�������ς݂Ȃ�ǂ�������̂���߂�
            if (hitObj.layer == 10)
            {
                hitObjFlag = false;
            }
        }

        // �ǂ������Ă���I�u�W�F�N�g���Ȃ�������
        if (hitObjFlag == false)
        {
            // �����A�j���[�V�������~�߂�
            animatorChef.SetBool("isWalk", false);
            // ���N���b�N�ŃI�u�W�F�N�g�ƃ}�E�X���ڐG���Ă��邩
            if (Input.GetMouseButton(0))
            {
                Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);
                Vector3 direction = new Vector3(0.0f, 0.0f, 1.0f);
                // �}�E�X�ƐڐG���Ă�����
                if (Physics.Raycast(ray, out hit))
                {
                    // �ڐG�I�u�W�F�N�g�̏���ۑ�
                    hitObj = hit.collider.gameObject;
                    hitObjName = hit.collider.gameObject.name;
                    // ���C���[��Live�Ȃ��
                    // hitObjFlag��true�ɂ��A�q�b�g�����I�u�W�F�N�g�̎擾
                    if (hitObj.layer == 11 && (hitObj.tag == "CBowl" ||
                        hitObj.tag == "CCake" || hitObj.tag == "OrangeJelly" || 
                        hitObj.tag == "OBowl" || hitObj.tag == "ChocoBowl" ||
                        hitObj.tag == "ChocoHarden" || hitObj.tag == "DBowl" ||
                        hitObj.tag == "DoughCookie"))
                    {
                        hitObjFlag = true;               
                    }
                }
            }
        }

        // �I�u�W�F�N�g��ǂ�������t���O��true��������
        if (hitObjFlag == true)
        {
            // �����A�j���[�V����������
            animatorChef.SetBool("isWalk", true);
            // �I�u�W�F�N�g�����֌����p�x���擾
            Vector3 directionVector = player.transform.position - hitObj.transform.position;
            Quaternion playerRotate = Quaternion.LookRotation(directionVector);
            // �I�u�W�F�N�g�̕���������
            player.transform.eulerAngles = new Vector3(0.0f, playerRotate.eulerAngles.y, 0.0f);
            // �I�u�W�F�N�g�̕����֐i��                 
            player.transform.position += transform.forward * -1 * speed * Time.unscaledDeltaTime;
            // �I�u�W�F�N�g�̃^�O���擾
            hitObjTag = hitObj.tag;
        }      
    }
    // �I�u�W�F�N�g��ǂ�������t���O�̃Z�b�^�[
    public void SetHitObjFlag(bool judge)
    {
        hitObjFlag = judge;
    }
}