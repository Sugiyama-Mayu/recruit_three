using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// M.S
// �P�[�L�̃J�b�g�̃R���W�����v���O����
public class CutPos4 : MonoBehaviour
{
    private bool cut4Flag;
    void Start()
    {
        cut4Flag = false;
    }
    // �J�b�g�|�C���g�ƐڐG������cut4Flag��true
    private void OnTriggerEnter(Collider other)
    {
        cut4Flag = true;
    }
    // cut4Flag�̃Q�b�^�[
    // ��  ��:bool cut4Flag
    // �߂�l:�Ȃ�    
    public bool getCutFlag
    {
        get { return cut4Flag; }
    }
}
