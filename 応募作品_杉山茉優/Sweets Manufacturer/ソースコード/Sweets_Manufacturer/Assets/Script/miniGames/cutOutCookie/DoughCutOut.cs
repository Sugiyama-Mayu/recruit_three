using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// M.S
// �N�b�L�[�̌^�����Q�[���̓����蔻��v���O����(���n)
public class DoughCutOut : MonoBehaviour
{
    // �����^�̃I�u�W�F�N�g
    public MoveCutOut moveCutOut;
    // �I�u�W�F�N�g�Ɛ��n���ڐG���Ă��邩
    private void OnTriggerEnter(Collider other)
    {
        // ���n�������^�ƐڐG�������ǂ���
        if (other.gameObject.tag == "CutOut")
        {
            // �����^�ƐڐG���Ă�����colList�ɂ��̃I�u�W�F�N�g��ǉ�
            moveCutOut.SetCutOutCol(this.gameObject);
        }
    }
    void Update()
    {
        // �m�F�p:���[�v�ł��̃v���O������ʂ�����+1
        moveCutOut.cookieDoughNum++;
    }
}

