using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// M.S
// �P�[�L�̃J�b�g�Q�[���v���O����
public class CutManager : MonoBehaviour
{
    // �J�b�g���ꂽ�����f�p�X�N���v�g�ϐ�
    public CutPos1 cutPos1Sc;
    public CutPos2 cutPos2Sc;
    public CutPos3 cutPos3Sc;
    public CutPos4 cutPos4Sc;
    public CutPos5 cutPos5Sc;
    public CutPos6 cutPos6Sc;
    public CutPos7 cutPos7Sc;
    public CutPos8 cutPos8Sc;

    // �J�b�g��A�j���[�V����
    public Animator animatorCakeUp;
    public Animator animatorCakeUnder;
    // �Q�[�������ۑ��ϐ�
    public bool gameSuccess;
    // ����������G�t�F�N�g
    public ParticleSystem cutEffect;
    public ParticleSystem clearEffect;
    // ���U���g�X�N���v�g�ϐ�
    public ResultManager resultManager;
    // �~�j�Q�[���X�N���v�g�ϐ�
    public MinigameIn miniGameIn;
    // ���������鉹
    public AudioClip soundTask;
    public AudioClip soundClear;
    // �I�[�f�B�I�\�[�X
    AudioSource audioSource;
    void Start()
    {// �Q�[�������ۑ��ϐ���false�ɂ���
        gameSuccess = false;
        audioSource = GetComponent<AudioSource>();
    }
    void Update()
    {
        bool cut1;
        bool cut2;
        bool cut3;
        bool cut4;
        bool cut5;
        bool cut6;
        bool cut7;
        bool cut8;
        // �S�Ẵ|�W�V�����̃J�b�g���ꂽ�����擾
        cut1 = cutPos1Sc.getCutFlag;
        cut2 = cutPos2Sc.getCutFlag;
        cut3 = cutPos3Sc.getCutFlag;
        cut4 = cutPos4Sc.getCutFlag;
        cut5 = cutPos5Sc.getCutFlag;
        cut6 = cutPos6Sc.getCutFlag;
        cut7 = cutPos7Sc.getCutFlag;
        cut8 = cutPos8Sc.getCutFlag;
        // �S�Ẵ|�W�V�������J�b�g����Ă�����
        if (cut1 == true && cut2 == true && cut3 == true         
            && cut4 == true && cut5 == true && cut6 == true 
            && cut7 == true && cut8 == true && gameSuccess == false)
        {
            // �J�b�g�G�t�F�N�g�̐���
            ParticleSystem newEffect = Instantiate(cutEffect);
            // �J�b�g�G�t�F�N�g���A�N�e�B�u
            newEffect.gameObject.SetActive(true);
            // �J�b�g�G�t�F�N�g�̃|�W�V�����̃Z�b�g
            newEffect.gameObject.transform.position = cutEffect.transform.position;
            // �J�b�g�G�t�F�N�g�̔���
            newEffect.Play();
            // �J�b�g�G�t�F�N�g�̍폜
            Destroy(newEffect.gameObject, 0.5f);
            // �J�b�g�A�j���[�V�����̔����ϐ���true
            animatorCakeUp.SetBool("separateCakeUp", true);
            animatorCakeUnder.SetBool("separateCakeUnder", true);
            // �N���A�G�t�F�N�g�̐���
            ParticleSystem newClearEffect = Instantiate(clearEffect);
            // �N���A�G�t�F�N�g���A�N�e�B�u
            newClearEffect.gameObject.SetActive(true);
            // �N���A�G�t�F�N�g�̃|�W�V�����̃Z�b�g
            newClearEffect.gameObject.transform.position = clearEffect.transform.position;
            // �N���A�G�t�F�N�g�̔���
            newClearEffect.Play();
            // �N���A�G�t�F�N�g�̍폜
            Destroy(newClearEffect.gameObject, 0.5f);
            // �Q�[�������ϐ���true
            miniGameIn.SetMinigameResult(true);
            gameSuccess = true;       
            resultManager.cakeCutJudge = true;
            // �Q�[���������ʉ���炷
            audioSource.PlayOneShot(soundClear);
        }
    }
}