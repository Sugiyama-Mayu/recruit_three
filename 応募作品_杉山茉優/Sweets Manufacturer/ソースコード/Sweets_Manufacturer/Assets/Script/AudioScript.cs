using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// M.S
// �Q�[���v���C��(�x���g�R���x�A���)��BGM�̊Ǘ�
public class AudioScript : MonoBehaviour
{
    public GameObject soundClearBGM;  // �N���ABGM
    public GameObject soundOverBGM;   // �Q�[���I�[�o�[BGM
    public GameObject soundBGM;       // �Q�[����BGM
    // ����BGM�𑀍삷��ϐ� 1�F�Q�[����BGM 2�F�N���ABGM 3�F�Q�[���I�[�o�[BGM
    int audioNum;  
    void Start()
    {
        audioNum = 1;  // �ŏ��̓Q�[����BGM
    }
    void Update()
    {
        if(audioNum == 1) {     // �Q�[����BGM
            soundBGM.SetActive(true);
            soundClearBGM.SetActive(false);
            soundOverBGM.SetActive(false);
            audioNum = 0;
        }
        else if(audioNum == 2) // �N���ABGM
        {
            soundClearBGM.SetActive(true);
            soundOverBGM.SetActive(false);
            soundBGM.SetActive(false);
            audioNum = 0;
        }
        else if(audioNum == 3) // �Q�[���I�[�o�[BGM
        {
            soundOverBGM.SetActive(true);
            soundClearBGM.SetActive(false);
            soundBGM.SetActive(false);
            audioNum = 0;
        }
    }
    // BGM�̕ύX�ϐ��̃Z�b�g
    // ��  ���Fint   num  1�F�Q�[����BGM 2�F�N���ABGM 3�F�Q�[���I�[�o�[BGM
    // �߂�l�F�Ȃ�
    public void SetChangeBGM(int num)
    {
        audioNum = num;
    }
}
