using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// �C�`�S������Q�[���̃N���A�̊Ǘ��v���O����
public class BerryCrear : MonoBehaviour
{
    public int Berrycount;
    public ParticleSystem clearEffect;
    public ResultManager resultManager;
    public MinigameIn miniGameIn;
    public AudioClip soundClear;
    AudioSource audioSource;                        // �I�[�f�B�I�\�[�X�̍쐬
    void Start()
    {
        audioSource = GetComponent<AudioSource>();  // �I�[�f�B�I�\�[�X�̍쐬
    }

    void Update()
    {
        if (Berrycount == 6)
        {
            Debug.Log("�N���A");
            clearEffect.gameObject.SetActive(true);   // M.S �G�t�F�N�g���A�N�e�B�u�ɂ���
            clearEffect.Play();                       // M.S �G�t�F�N�g�̔���
            resultManager.cakeDecorationJudge = true;
            miniGameIn.SetMinigameResult(true);
            Berrycount++;
            audioSource.PlayOneShot(soundClear);      // M.S ���̔���
        }
    }
}
