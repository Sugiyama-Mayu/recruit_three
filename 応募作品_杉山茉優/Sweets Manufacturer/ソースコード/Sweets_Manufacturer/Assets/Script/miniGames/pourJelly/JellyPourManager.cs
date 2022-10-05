using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// M.S
// �[���[�𒍂��Q�[���̃}�l�[�W���[
public class JellyPourManager : MonoBehaviour
{
    // �����I������[���[�̐�
    public int pourCapCount;
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
        pourCapCount = 0;
        audioSource = GetComponent<AudioSource>();
    }
    void Update()
    {
        // �S�Ẵ[���[�ɒ����I����Ă��邩�ǂ���
        if(pourCapCount == 6)
        {
            // �N���A�G�t�F�N�g���A�N�e�B�u�ɂ���
            clearEffect.gameObject.SetActive(true);
            // �N���A�G�t�F�N�g�𔭐�������
            clearEffect.Play();
            // �N���A�G�t�F�N�g�̍폜
            Destroy(clearEffect.gameObject, 5.0f);
            // ������x�N���A���������Ȃ��悤��pourCapCount��+1����
            pourCapCount++;
            // �[���[�𒍂��Q�[���N���A�t���O��true
            resultManager.orangePourJudge = true;
            // �~�j�Q�[���I���t���O��true
            miniGameIn.SetMinigameResult(true);
            // �N���A���ʉ��̔���
            audioSource.PlayOneShot(soundClear);
        }
        else
        {
        }
    }
}
