using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// M.S
// �I�����W��z�u����Q�[���̃}�l�[�W���[
public class JellyGameManager : MonoBehaviour
{
    // �z�u�����I�����W�̐�
    public int putOrangeNum;
    // �N���A�G�t�F�N�g
    public ParticleSystem clearEffect;
    // �X�N���v�g�ϐ�
    public ResultManager resultManager;
    public MinigameIn miniGameIn;
    // �N���A�T�E���h
    public AudioClip soundClear;
    // �I�[�f�B�I�\�[�X
    AudioSource audioSource;
    void Start()
    {
        // ������
        putOrangeNum = 0;
        audioSource = GetComponent<AudioSource>();
    }
    void Update()
    {
        // �S�ẴI�����W���z�u����Ă��邩�ǂ���
        if(putOrangeNum == 6)
        {
            // �N���A�G�t�F�N�g���A�N�e�B�u�ɂ���
            clearEffect.gameObject.SetActive(true);
            // �N���A�G�t�F�N�g�̔���
            clearEffect.Play();
            // �N���A�G�t�F�N�g���폜
            Destroy(clearEffect.gameObject, 5.0f);
            // ��x�̂݃N���A�������s������putOrangeNum��+1����
            putOrangeNum++;
            // �I�����W��z�u����Q�[���N���A�t���O��true
            resultManager.orangePutJudge = true;
            // �~�j�Q�[���I���t���O��true
            miniGameIn.SetMinigameResult(true);
            // �N���A���ʉ�
            audioSource.PlayOneShot(soundClear);
        }
        else
        {
        }
    }
}
