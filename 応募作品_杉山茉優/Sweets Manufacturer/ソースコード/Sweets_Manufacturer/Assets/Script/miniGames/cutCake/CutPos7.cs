using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// M.S
// �P�[�L�̃J�b�g�̃R���W�����v���O����
public class CutPos7 : MonoBehaviour
{
    private bool cut7Flag;
    void Start()
    {
        cut7Flag = false;
    }
    // �J�b�g�|�C���g�ƐڐG������cut7Flag��true
    private void OnTriggerEnter(Collider other)
    {
        cut7Flag = true;
    }
    // cut7Flag�̃Q�b�^�[
    // ��  ��:bool cut7Flag
    // �߂�l:�Ȃ�
    public bool getCutFlag
    {
        get { return cut7Flag; }
    }
}
