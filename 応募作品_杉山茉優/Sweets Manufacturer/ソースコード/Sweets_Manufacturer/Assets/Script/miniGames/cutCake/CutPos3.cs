using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// M.S
// �P�[�L�̃J�b�g�̃R���W�����v���O����
public class CutPos3 : MonoBehaviour
{
    private bool cut3Flag;
    void Start()
    {
        cut3Flag = false;
    }
    // �J�b�g�|�C���g�ƐڐG������cut3Flag��true
    private void OnTriggerEnter(Collider other)
    {
        cut3Flag = true;
    }
    // cut3Flag�̃Q�b�^�[
    // ��  ��:bool cut3Flag
    // �߂�l:�Ȃ�
    public bool getCutFlag
    {
        get { return cut3Flag; }
    }
}
