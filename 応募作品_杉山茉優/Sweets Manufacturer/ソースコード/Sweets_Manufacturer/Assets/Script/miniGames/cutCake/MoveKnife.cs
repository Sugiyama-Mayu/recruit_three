using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// M.S
// �P�[�L�̃J�b�g�Q�[���̃i�C�t�ʒu�ړ��v���O����
public class MoveKnife : MonoBehaviour
{
    // �i�C�t�I�u�W�F�N�g�ϐ�
    public GameObject knifeObj;
    void Update()
    {
        // �}�E�X�̃|�W�V�����̎擾
        Vector3 mousePos = Input.mousePosition;
        // 3D�̏��ɂ��邽�߂̃}�E�X�̃|�W�V������Z�����l�̐ݒ�
        mousePos.z = 3.0f;
        // �}�E�X�|�W�V������3D���W�ɕϊ��AmouseWorld�ɓ����
        Vector3 mouseWorld = Camera.main.ScreenToWorldPoint(mousePos);
        // �i�C�t�I�u�W�F�N�g�̈ʒu���}�E�X�̈ʒu�֍X�V
        knifeObj.transform.position = new Vector3(mouseWorld.x, knifeObj.transform.position.y, mouseWorld.z);
    }
}
