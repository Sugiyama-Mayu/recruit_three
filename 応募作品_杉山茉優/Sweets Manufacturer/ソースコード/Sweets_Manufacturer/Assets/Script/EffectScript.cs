using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// M.S
// �}�E�X�J�[�\���G�t�F�N�g�̔���
public class EffectScript : MonoBehaviour
{
    void Update()
    {
        // �}�E�X�J�[�\����3D�̈ʒu���擾
        Vector3 mousePos = Input.mousePosition;
        mousePos.z = 10.0f;
        Vector3 mousePosWorld = Camera.main.ScreenToWorldPoint(mousePos);
        // �G�t�F�N�g���}�E�X�̈ʒu�Ɉړ�
        mousePosWorld.y = 1.1f;
        this.transform.position = mousePosWorld;
    }
}
