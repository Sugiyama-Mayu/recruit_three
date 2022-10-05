using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// M.S
// �{�E����������Q�[���̉�]�������ƃN���A�������̏���
public class CollManager : MonoBehaviour
{
    // ��]��
    static int numberOfRotation;
    // �Q�[���̃N���A�����ς݃t���O
    public bool gameSuccess;
    // 1��]�̊m�F�̂��߂̃I�u�W�F�N�g
    public RotatePos1 rotatePos1;
    public RotatePos2 rotatePos2;
    public RotatePos3 rotatePos3;
    public RotatePos4 rotatePos4;
    // 1��]�̃G�t�F�N�g
    public ParticleSystem rotateEffect;
    // �N���A�G�t�F�N�g
    public ParticleSystem clearEffect;
    // �X�N���v�g�ϐ�
    public ResultManager resultManager;
    public MinigameIn miniGameIn;
    // ���ʉ�
    public AudioClip soundTask;
    public AudioClip soundClear;
    // �I�[�f�B�I�\�[�X
    AudioSource audioSource;
    // �{�[�����ʕϐ�
    // 1:cakeCreamBowl 2:chocoBowl 3:chocoCrackerBowl 4:orangeBowl 5:cookieDoughBowl
    public int thisBowlNum;   

    void Start()
    {
        // ������
        numberOfRotation = 0;
        gameSuccess = false;
        audioSource = GetComponent<AudioSource>();
    }
   
    void Update()
    {
        // �e1��]�m�F�I�u�W�F�N�g�ƖA���Ċ�̓����蔻�茋�ʂ��擾
        bool rotate1;
        bool rotate2;
        bool rotate3;
        bool rotate4;
        rotate1 = rotatePos1.RotateTerritoryFlag;
        rotate2 = rotatePos2.RotateTerritoryFlag;
        rotate3 = rotatePos3.RotateTerritoryFlag;
        rotate4 = rotatePos4.RotateTerritoryFlag;
        // ���ׂĂ�1��]�m�F�I�u�W�F�N�g�ƐڐG���Ă��邩�ǂ���
        if (rotate1 == true && rotate2 == true && rotate3 == true && rotate4 == true)
        {
            // ���̉�]����̂��߂ɖA���Ċ�Ƃ̓����蔻��̌��ʂ�߂�
            rotatePos1.RotateTerritoryFlag = false;
            rotatePos2.RotateTerritoryFlag = false;
            rotatePos3.RotateTerritoryFlag = false;
            rotatePos4.RotateTerritoryFlag = false;
            // ��]����+1����
            numberOfRotation++;
            // 1��]�G�t�F�N�g�̍쐬
            ParticleSystem newEffect = Instantiate(rotateEffect);
            // 1��]�G�t�F�N�g���A�N�e�B�u�ɂ���
            newEffect.gameObject.SetActive(true);
            // 1��]�G�t�F�N�g�̈ʒu���Z�b�g
            newEffect.gameObject.transform.position = rotateEffect.transform.position;
            // 1��]�G�t�F�N�g�𔭐�
            newEffect.Play();
            // 1��]�G�t�F�N�g���폜
            Destroy(newEffect.gameObject, 5.0f);
            // 1��]���ʉ��̍Đ�
            audioSource.PlayOneShot(soundTask);
        } 
        // 10��]�ȏサ�Ă��āA�Q�[���̃N���A���������Ă��Ȃ������ǂ���
        if (numberOfRotation >= 10 && gameSuccess == false) {
            // ��]����+1����
            numberOfRotation++;
            // �N���A�G�t�F�N�g�̍쐬
            ParticleSystem newClearEffect = Instantiate(clearEffect);
            // �N���A�G�t�F�N�g���A�N�e�B�u�ɂ���
            newClearEffect.gameObject.SetActive(true);
            // �N���A�G�t�F�N�g�̈ʒu���Z�b�g
            newClearEffect.gameObject.transform.position = clearEffect.transform.position;
            // �N���A�G�t�F�N�g�𔭐�
            newClearEffect.Play();
            // �N���A�G�t�F�N�g���폜
            Destroy(newClearEffect.gameObject, 5.0f);
            // �~�j�Q�[���̏I����ۑ�
            miniGameIn.SetMinigameResult(true);  
            // �N���A���ʉ��̍Đ�
            audioSource.PlayOneShot(soundClear);
            // �{�E���I�u�W�F�N�g�ɍ��킹�ăQ�[���N���A�̕ۑ�������
            switch (thisBowlNum)
            {
                case 1:  // [�P�[�L]�̃{�E��
                    resultManager.cakeCreamBowlJudge = true;
                    break;
                case 2:  // [�`���R�N���b�J�[]�̃`���R�̃{�E��
                    resultManager.chocoBowlJudge = true;
                    break;
                case 3:  // [�`���R�N���b�J�[]�̐��n�̃{�E��
                    resultManager.chocoCrackerBowlJudge = true;
                    break;
                case 4:  // [�[���[]�̃{�E��
                    resultManager.orangeBowlJudge = true;
                    break;
                case 5:  // [�N�b�L�[]�̃{�E��
                    resultManager.cookieDoughBowlJudge = true;
                    break;
            }
            // ���ڂ̃N���A���������Ȃ��悤�A�Q�[���N���A�����ς݂ɂ���
            gameSuccess = true;
        }
    }
    // ��]���̃Q�b�^�[
    // ��  ���F�Ȃ�
    // �߂�l�Fint numberOfRotation  ��]��
    public int GetNumberOfRotation
    {
        get { return numberOfRotation; }
    }
}
