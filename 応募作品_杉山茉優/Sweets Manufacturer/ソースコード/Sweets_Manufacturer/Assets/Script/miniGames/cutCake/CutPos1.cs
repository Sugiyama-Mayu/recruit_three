using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// M.S
// �P�[�L�̃J�b�g�̃R���W�����v���O����
public class CutPos1 : MonoBehaviour
{
    private bool cut1Flag; 
    void Start()
    {
        cut1Flag = false;
    }
    // �J�b�g�|�C���g�ƐڐG������cut1Flag��true
    private void OnTriggerEnter(Collider other)
    {
        cut1Flag = true;        
    }
    // cut1Flag�̃Q�b�^�[
    // ��  ��:bool cut1Flag
    // �߂�l:�Ȃ�
    public bool getCutFlag
    {
        get { return cut1Flag; }
    }
}
