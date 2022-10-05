using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;
using System.IO;
// M.S
// �~�j�Q�[���̔�������
public class MinigameIn : MonoBehaviour
{
    public GameObject minigame;   // ����������~�j�Q�[��
    public GameObject honntai;    //���[���𗬂�Ă����
    public GameObject nextSweets; // ���ɗ������َq
    private bool doneMiniGame;    // �~�j�Q�[���̔����ς݃t���O
    public GameObject minigames;  // �~�j�Q�[�����W�߂��I�u�W�F�N�g
    public ClickObject clickObject; // �v���C���[�����X�N���v�g

    // �`���R�N���b�J�[�Q�[���̃N���b�J�[�I�u�W�F�N�g
    public DragDrop cracker1;
    public DragDrop cracker2;
    public DragDrop cracker3;
    public DragDrop cracker4;
    public DragDrop cracker5;
    public DragDrop cracker6;
    public DragDrop cracker7;
    public DragDrop cracker8;
    // �[���[�Q�[���̃I�����W�I�u�W�F�N�g
    public MoveOrange orange1;
    public MoveOrange orange2;
    public MoveOrange orange3;
    public MoveOrange orange4;
    public MoveOrange orange5;
    public MoveOrange orange6;
    // �N�b�L�[�Q�[���̌^�������I�u�W�F�N�g
    public CutOutColl cookieCut1;
    public CutOutColl cookieCut2;
    public CutOutColl cookieCut3;
    public CutOutColl cookieCut4;
    // �N�b�L�[�Q�[���}�l�[�W���[�̃X�N���v�g
    public MoveCutOut cookieMana;
    // �x���g�R���x�A�̃I�u�W�F�N�g
    public belt belt1;
    public belt belt2;
    public belt belt3;
    public belt belt4;
    public belt belt5;
    public belt belt6;
    public belt belt7;
    public belt belt8;
    // �~�j�Q�[���Ǘ��I�u�W�F�N�g
    public MinigameIn onlyMinigameIn;
    // �Q�[�����ɕʂ̃Q�[���𔭐������Ȃ����߂̃t���O
    //  �~�j�Q�[���Ǘ��I�u�W�F�N�g�Ŏg�p
    public bool duringPlay;
    // �X�e�[�W��
    public int sceneNum;
    // �~�j�Q�[���̍ŏ��ɕ\������Q�[�������e�L�X�g
    public GameObject miniGameText;
    // �~�j�Q�[���̏I���t���O
    private bool miniGameResult;
    void Start()
    {
        // ������
        miniGameResult = false;
        duringPlay = false;
        doneMiniGame = false;
    }
    // �~�j�Q�[���̔����R���[�`��
    public IEnumerator MinigameTimer(string tag)
    {
        // �~�j�Q�[���������ς݂łȂ��A�~�j�Q�[�����łȂ����ǂ���
        if (doneMiniGame == false && onlyMinigameIn.duringPlay == false)
        {
            // �`���R�N���b�J�[�Q�[�����ǂ���
            if(tag == "ChocoHarden")
            {
                // �`���R�N���b�J�[�Q�[���̏������t���O��true
                cracker1.startCracker = true;
                cracker2.startCracker = true;
                cracker3.startCracker = true;
                cracker4.startCracker = true;
                cracker5.startCracker = true;
                cracker6.startCracker = true;
                cracker7.startCracker = true;
                cracker8.startCracker = true;
            }
            // �[���[�Q�[�����ǂ���
            if (tag == "OrangeJelly")
            {
                // �[���[�Q�[���̏������t���O��true
                orange1.startFlag = true;
                orange2.startFlag = true;
                orange3.startFlag = true;
                orange4.startFlag = true;
                orange5.startFlag = true;
                orange6.startFlag = true;
            }
            // �N�b�L�[�Q�[�����ǂ���
            if (tag == "DoughCookie")
            {
                // �N�b�L�[�Q�[���̏������t���O��true
                cookieCut1.startFlag = true;
                cookieCut2.startFlag = true;
                cookieCut3.startFlag = true;
                cookieCut4.startFlag = true;
                cookieMana.startFlag = true;
            }
            onlyMinigameIn.duringPlay = true; // �~�j�Q�[�����t���O��true
            // �I�u�W�F�N�g��ǂ�������t���O��false
            clickObject.SetHitObjFlag(false); 
            // ���َq�I�u�W�F�̃^�O���~�j�Q�[���ς݂ɕύX
            honntai.layer = 10;
            // �x���g�R���x�A�̓������~�߂�
            MoveBeltFlag(sceneNum, true);
            // �J�����ʒu���~�j�Q�[���̈ʒu�ɂ���
            ChangeCamera(1);
            // �~�j�Q�[�����A�N�e�B�u�ɂ���
            minigames.SetActive(true);
            minigame.SetActive(true);
            // �~�j�Q�[�������e�L�X�g�̕\��
            miniGameText.SetActive(true);
            yield return new WaitForSecondsRealtime(0.8f);
            // �~�j�Q�[�������e�L�X�g�̔�\��
            miniGameText.SetActive(false);
            // �~�j�Q�[���̎���(�~�j�Q�[���ɂ���ĕ�����)
            if (tag == "CCake" || tag == "CBowl" || tag == "DBowl" 
                || tag == "OBowl" || tag == "ChocoBowl" )
            {
                yield return new WaitForSecondsRealtime(5.0f); 
            }
            else if (tag == "DoughCookie")
            {
                yield return new WaitForSecondsRealtime(7.0f);
            }
            else if (tag == "ChocoHarden" || tag == "OrangeJelly")
            {
                yield return new WaitForSecondsRealtime(10.0f);
            }
            doneMiniGame = true;  // �~�j�Q�[���𔭐��ς݂ɂ���
            if (tag == "CBowl") 
            {
                GameObject miniGameCam;
                GameManager gameManager;
                // �J�����̎擾
                miniGameCam = GameObject.Find("Main Camera");
                gameManager = miniGameCam.GetComponent<GameManager>();
                gameManager.tutorialOrder = 5;  // �`���[�g���A���t�F�[�Y��ݒ�
            }
            // �~�j�Q�[�����A�N�e�B�u�ɂ���
            minigame.SetActive(false);
            // �J�����ʒu���v���C���[������ʒu�ɂ���
            ChangeCamera(0);
            // �x���g�R���x�A�𓮂���
            MoveBeltFlag(sceneNum, false);
            // �~�j�Q�[�����I����Ă��Ȃ����ǂ���
            if(miniGameResult == false)
            {
                // �I�u�W�F�N�g���I����Ă��Ȃ���Ԃɂ���
                honntai.layer = 11;    // layer��Live�ɃZ�b�g
                doneMiniGame = false;  // �~�j�Q�[�����Ăє����������Ԃɂ���
            }
            // �~�j�Q�[�����t���O��false
            onlyMinigameIn.duringPlay = false;
        }
        yield break;   
    }
    // �[�ł̃~�j�Q�[���̔���
    public IEnumerator edgeMinigameTimer(GameObject edgeObj)
    {
        // �~�j�Q�[���������ς݂łȂ��A�~�j�Q�[�����łȂ��A�^�C���I�[�o�[(�Q�[���I�[�o�[)�łȂ����ǂ���
        if (doneMiniGame == false && onlyMinigameIn.duringPlay == false && TimeCount.isTimeUp == false)
        {
            // �I�u�W�F�N�g��ǂ�������t���O��false
            clickObject.SetHitObjFlag(false);
            onlyMinigameIn.duringPlay = true;  // �~�j�Q�[�����t���O��true
            // �x���g�R���x�A�̓������~�߂�
            MoveBeltFlag(sceneNum, true);
            GameObject miniGameCam;
            GameManager gameManager;
            // �J�����̎擾
            miniGameCam = GameObject.Find("Main Camera");
            gameManager = miniGameCam.GetComponent<GameManager>();
            // �J�����ʒu���~�j�Q�[���̈ʒu�ɂ���
            ChangeCamera(1);
            // �~�j�Q�[�����A�N�e�B�u�ɂ���
            minigames.SetActive(true);
            minigame.SetActive(true);
            // �~�j�Q�[�������e�L�X�g�̕\��
            miniGameText.SetActive(true);
            yield return new WaitForSecondsRealtime(0.8f);
            // �~�j�Q�[�������e�L�X�g�̔�\��
            miniGameText.SetActive(false);
            // �~�j�Q�[���̎���
            if (edgeObj.tag == "CCake" || edgeObj.tag == "ChocoBowl" || edgeObj.tag == "OBowl")
            {
                yield return new WaitForSecondsRealtime(5.0f);
            }
            edgeObj.tag = "EndSweets";  // �Ō�̂��َq�̃^�O�ɂ���
            doneMiniGame = true;        // �~�j�Q�[�������ς݂ɂ���
            // �~�j�Q�[�����A�N�e�B�u�ɂ���
            minigame.SetActive(false);
            // �J�����ʒu���v���C���[������ʒu�ɂ���
            ChangeCamera(0);
            // �x���g�R���x�A�𓮂���
            MoveBeltFlag(sceneNum, false);
            // �~�j�Q�[�����t���O��false
            onlyMinigameIn.duringPlay = false;
            // *�[�̃~�j�Q�[���̏ꍇ�͎��s���Ă��ēx�~�j�Q�[���𔭐������Ȃ�
            yield break;
        }
    }
    void OnTriggerStay(Collider other)
    {
        // �v���C���[�ƐڐG��
        //  �^�C���I�[�o�[(�Q�[���I�[�o�[)�łȂ���΃~�j�Q�[�����Ă�
        if (other.CompareTag("Player") && TimeCount.isTimeUp == false)
        {
            StartCoroutine("MinigameTimer", this.gameObject.tag);
        }
    }
    void Update()
    {
        // �I�u�W�F�N�g���Ō�̂��َq�^�O���ǂ���
        if(this.gameObject.tag == "EndSweets")
        {
            // �I�u�W�F�N�g���\���ɂ���
            this.gameObject.SetActive(false);
        }
        // �^�C���I�[�o�[(�Q�[���I�[�o�[)���ǂ���
        if(TimeCount.isTimeUp == true)
        {
            // �J�����ʒu���v���C�L�����̂���ʂ֖߂�
            ChangeCamera(0);
        }
    }
    // �~�j�Q�[�������ς݃t���O�̃Q�b�^�[
    // ��  ���F�Ȃ�
    // �߂�l�Fbool   true �����ς�  false �������Ă��Ȃ�
    public bool getDoneMiniGame()
    {
        return doneMiniGame;
    }
    // �~�j�Q�[�������ς݃t���O�̃Z�b�^�[
    // ��  ���Fbool   true �����ς�  false �������Ă��Ȃ�
    // �߂�l�F�Ȃ�  
    public void SetDoneMiniGame(bool set)
    {
        doneMiniGame = set;
    }
    // �~�j�Q�[���̏I���t���O�̃Z�b�^�[
    // ��  ���Fbool   true �I������  false �I�����ĂȂ�
    // �߂�l�F�Ȃ�  
    public void SetMinigameResult(bool set)
    {
        miniGameResult = set;
    }
    // �J�����ʒu���ړ�������GameStatus�ϐ��̕ύX
    // ��  ���Fint   cameraChangeNum  0 �v���C���[�̂���ʒu�ֈړ� 
    //                                1 �~�j�Q�[���ʒu�ֈړ�
    // �߂�l�F�Ȃ� 
    public void ChangeCamera(int cameraChangeNum)
    {
        GameObject miniGameCam;
        GameManager gameManager;
        // �J�����̎擾
        miniGameCam = GameObject.Find("Main Camera");
        gameManager = miniGameCam.GetComponent<GameManager>();
        // �J�����̕ύX�ϐ���ύX
        gameManager.GameStatus = cameraChangeNum;
        // �J�����ʒu��ύX
        switch (cameraChangeNum)
        {
            case 0:  // �v���C���[�̂���ʒu�ֈړ� 
                gameManager.ChangeMainPosCamera();
                break;
            case 1:  //  �~�j�Q�[���ʒu�ֈړ�
                gameManager.ChangeMiniGamePosCamera();
                break;
        }
    }
    // �x���g�R���x�A�̓����̐���
    // ��  ���Fbool   beltMove  true  �x���g�R���x�A�𓮂���
    //                          false �x���g�R���x�A���~�߂� 
    //         int    sceneNum  1�̓X�e�[�W1 2�̓X�e�[�W2 3�̓X�e�[�W3 4�̓X�e�[�W4
    // �߂�l�F�Ȃ� 
    public void MoveBeltFlag(int sceneNum, bool beltMove)
    {
        switch (sceneNum)
        {
            case 1:  // �X�e�[�W1
                belt1.stopBeltMove = beltMove;
                belt2.stopBeltMove = beltMove;
                break;
            case 2:  // �X�e�[�W2
                belt1.stopBeltMove = beltMove;
                belt2.stopBeltMove = beltMove;
                belt3.stopBeltMove = beltMove;
                belt4.stopBeltMove = beltMove;
                break;
            case 3:  // �X�e�[�W3
                belt1.stopBeltMove = beltMove;
                belt2.stopBeltMove = beltMove;
                belt3.stopBeltMove = beltMove;
                belt4.stopBeltMove = beltMove;
                belt5.stopBeltMove = beltMove;
                belt6.stopBeltMove = beltMove;
                belt7.stopBeltMove = beltMove;
                belt8.stopBeltMove = beltMove;
                break;
            case 4:  // �X�e�[�W4
                belt1.stopBeltMove = beltMove;
                belt2.stopBeltMove = beltMove;
                belt3.stopBeltMove = beltMove;
                belt4.stopBeltMove = beltMove;
                belt5.stopBeltMove = beltMove;
                belt6.stopBeltMove = beltMove;
                belt7.stopBeltMove = beltMove;
                belt8.stopBeltMove = beltMove;
                break;
        }
    }
}
