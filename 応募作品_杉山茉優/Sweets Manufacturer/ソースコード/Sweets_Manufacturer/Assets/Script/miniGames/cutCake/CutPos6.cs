using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// M.S
// �P�[�L�̃J�b�g�̃R���W�����v���O����
public class CutPos6 : MonoBehaviour
{
    private bool cut6Flag;
    void Start()
    {
        cut6Flag = false;
    }
    // �J�b�g�|�C���g�ƐڐG������cut6Flag��true
    private void OnTriggerEnter(Collider other)
    {
        cut6Flag = true;
    }
    // cut6Flag�̃Q�b�^�[
    // ��  ��:bool cut6Flag
    // �߂�l:�Ȃ�
    public bool getCutFlag
    {
        get { return cut6Flag; }
    }
}
