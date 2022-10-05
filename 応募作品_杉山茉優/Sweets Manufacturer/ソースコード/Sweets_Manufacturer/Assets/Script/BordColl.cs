using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// M.S 
// �x���g�R���x�A�Ƀv���C���[�������������̏���
public class BordColl : MonoBehaviour
{
    // �}�b�v�̒����̈ʒu�̕ۑ��̂���
    public GameObject mapCenter;
    public GameObject playerObj;
    private ClickObject playerScript;
    private void Start()
    {
      playerScript = playerObj.GetComponent<ClickObject>();
    }   
    // �ڐG���Ă��邩�ǂ���
    private void OnCollisionStay(Collision collision)
    {   // �ڐG�����I�u�W�F�N�g���v���C�L�������ǂ���
        if (collision.gameObject.tag == "Player")
        {
            playerScript.SetHitObjFlag(false);  // �I�u�W�F�N�g��ǂ�������̂���߂�
            // ���������֌����p�x���擾
            Vector3 directionVector = playerObj.transform.position - mapCenter.transform.position;
            Quaternion playerRotate = Quaternion.LookRotation(directionVector);
            //�I�u�W�F�N�g�̒��������������Đi��
            collision.transform.eulerAngles = new Vector3(0.0f, playerRotate.eulerAngles.y, 0.0f);
            collision.transform.position += playerObj.transform.forward * -1 * 0.5f;
        }
    }
}
