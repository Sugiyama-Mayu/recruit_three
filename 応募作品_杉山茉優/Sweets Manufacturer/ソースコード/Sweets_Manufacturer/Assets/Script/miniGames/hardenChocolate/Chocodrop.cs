using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// �N���b�J�[���`���R�ɓ����Q�[���̃N���A�����v���O����
public class Chocodrop : MonoBehaviour
{
    public int dropcount;
    public ParticleSystem clearEffect;   // M.S �G�t�F�N�g�����Ă���ϐ�
    public ResultManager resultManager;  // M.S ResultManager�X�N���v�g������ϐ�
    public MinigameIn miniGameIn;        // M.S MinigameIn�X�N���v�g������ϐ�
    public AudioClip soundClear;         // M.S �N���A�T�E���h������ϐ�
    AudioSource audioSource;             // M.S AudioSource�̕ϐ�
    void Start()
    {
        // M.S audhioSource�̍쐬
        audioSource = GetComponent<AudioSource>();
    }
    void Update()
    {
        // �S�Ẵ^�X�N���N���A���Ă��邩�ǂ���
        if(dropcount == 8)
        {
            // M.S �N���A�G�t�F�N�g���A�N�e�B�u�ɂ���
            clearEffect.gameObject.SetActive(true);
            // M.S �N���A�G�t�F�N�g�̔���
            clearEffect.Play();
            // M.S �N���A�G�t�F�N�g�̍폜
            Destroy(clearEffect.gameObject, 0.5f);
            // �N���A�������x�s��Ȃ��悤��dropcount��+1
            dropcount++;
            // M.S �N���b�J�[���`���R�ɓ����Q�[���̃N���A�t���O��true
            resultManager.chocoHardenJudge = true;
            miniGameIn.SetMinigameResult(true);
            // M.S �N���A���ʉ��̔���
            audioSource.PlayOneShot(soundClear);
        }
    }
}
