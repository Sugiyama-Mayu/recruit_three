using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// M.S
// �P�[�L�̃J�b�g�̃R���W�����v���O����
public class CutPos5 : MonoBehaviour
{
    private bool cut5Flag;
    void Start()
    {
        cut5Flag = false;
    }
    // �J�b�g�|�C���g�ƐڐG������cut5Flag��true
    private void OnTriggerEnter(Collider other)
    {
        cut5Flag = true;
    }
    // cut5Flag�̃Q�b�^�[
    // ��  ��:bool cut5Flag
    // �߂�l:�Ȃ�
    public bool getCutFlag
    {
        get { return cut5Flag; }
    }
}
