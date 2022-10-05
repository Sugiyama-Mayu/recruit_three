using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// M.S 
// �N�b�L�\�̌^�����Q�[���̃N���A����
public class CookieManager : MonoBehaviour
{
    // �N���A�G�t�F�N�g
    public ParticleSystem clearEffect;
    // �^�����I�u�W�F�N�g
    public MoveCutOut moveCutOut;
    // �X�N���v�g�̕ϐ�
    public ResultManager ResultManager;
    public MinigameIn miniGameIn;
    // �N���A�T�E���h
    public AudioClip soundClear;
    // �I�[�f�B�I�\�[�X
    AudioSource audioSource;
    // �N�b�L�[�̌^�����Q�[���N���A�����ς݃t���O
    bool doneClearProcess;
    void Start()
    {
        // ����������
        audioSource = GetComponent<AudioSource>();
        doneClearProcess = false;
    }
    void Update()
    {
        // �S�Ă̌^�������������Ă��āA�N���A���������Ă��Ȃ����ǂ���
        if (moveCutOut.GetCookieCount() == 4 && doneClearProcess == false)
        {
            // �N���A�G�t�F�N�g�̐���
            ParticleSystem newClearEffect = Instantiate(clearEffect);
            // �N���A�G�t�F�N�g���A�N�e�B�u�ɂ���
            newClearEffect.gameObject.SetActive(true);
            // �N���A�G�t�F�N�g�̈ʒu���Z�b�g
            newClearEffect.gameObject.transform.position = clearEffect.transform.position;
            // �N���A�G�t�F�N�g�𔭐�
            newClearEffect.Play();
            // �N���A�G�t�F�N�g���폜
            Destroy(newClearEffect.gameObject, 5.0f);
            // �N�b�L�\�̌^�����Q�[���N���A�t���O��true
            ResultManager.cookieCutOutJudge = true;
            // �~�j�Q�[���I���t���O��true
            miniGameIn.SetMinigameResult(true);
            // �N���A���ʉ��̔���
            audioSource.PlayOneShot(soundClear);
            // �N���A�����ς݂ɂ���
            doneClearProcess = true;
        }
    }
}