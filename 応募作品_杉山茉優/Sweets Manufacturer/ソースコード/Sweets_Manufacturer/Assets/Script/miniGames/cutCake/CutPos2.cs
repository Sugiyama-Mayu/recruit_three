using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// M.S
// �P�[�L�̃J�b�g�̃R���W�����v���O����
public class CutPos2 : MonoBehaviour
{
    private bool cut2Flag;
    void Start()
    {
        cut2Flag = false;
    }
    // �J�b�g�|�C���g�ƐڐG������cut2Flag��true
    private void OnTriggerEnter(Collider other)
    {
        cut2Flag = true;
    }
    // cut2Flag�̃Q�b�^�[
    // ��  ��:bool cut2Flag
    // �߂�l:�Ȃ�
    public bool getCutFlag{
    get { return cut2Flag; }
    }
}
