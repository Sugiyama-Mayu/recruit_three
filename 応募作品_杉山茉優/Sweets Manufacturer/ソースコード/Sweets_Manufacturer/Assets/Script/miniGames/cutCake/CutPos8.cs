using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// M.S
// �P�[�L�̃J�b�g�̃R���W�����v���O����
public class CutPos8 : MonoBehaviour
{
    private bool cut8Flag;
    void Start()
    {
        cut8Flag = false;
    }
    // �J�b�g�|�C���g�ƐڐG������cut8Flag��true
    private void OnTriggerEnter(Collider other)
    {
        cut8Flag = true;
    }
    // cut8Flag�̃Q�b�^�[
    // ��  ��:bool cut8Flag
    // �߂�l:�Ȃ�
    public bool getCutFlag
    {
        get { return cut8Flag; }
    }
}
