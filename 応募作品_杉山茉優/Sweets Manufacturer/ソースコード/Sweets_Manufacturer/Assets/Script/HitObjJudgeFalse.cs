using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// M.S 
// ���̃X�N���v�g���A�^�b�`����Ă���I�u�W�F�N�g�ɐG����
// �v���C���[�͒ǂ�������̂���߂�
public class HitObjJudgeFalse : MonoBehaviour
{
    public ClickObject clickObject;
    // ���[�����߂��Ă������I�u�W�F�N�g�͒ǂ�������̂���߂�
    private void OnTriggerStay(Collider other)
    {       
        if (other.gameObject.layer == 11)
        {
            clickObject.SetHitObjFlag(false);
        }
    }
}
