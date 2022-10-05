using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO;
// M.S
// �R���N�V�����V�[���̏���
public class Collect : MonoBehaviour
{
    // �R���N�V�����L�^�t�@�C���̃p�X
    string filePath;
    // �R���N�V�����L�^�t�@�C��
    public string[] collectNum;
    int[] collectNumText = new int[17];
    // �I�����Ă���I�u�W�F����
    public int collectSelectNum;
    int newSlectNum;
    // �I�����Ă����I�u�W�F����
    int oldSelectNum;
    // �E�̑I������I�u�W�F�N�g
    public GameObject cake;
    public GameObject goldCake;
    public GameObject choco;
    public GameObject goldChoco;
    public GameObject jelly;
    public GameObject goldJelly;
    public GameObject cookie;
    public GameObject goldCookie;
    public GameObject redTrophy;
    public GameObject greenTrophy;
    public GameObject yellowTrophy;
    public GameObject blueTrophy;
    public GameObject crystalTrophy;
    // ���̑傫���\�������I�u�W�F�N�g
    public GameObject cakeBig;
    public GameObject goldCakeBig;
    public GameObject chocoBig;
    public GameObject goldChocoBig;
    public GameObject jellyBig;
    public GameObject goldJellyBig;
    public GameObject cookieBig;
    public GameObject goldCookieBig;
    public GameObject redTrophyBig;
    public GameObject greenTrophyBig;
    public GameObject yellowTrophyBig;
    public GameObject blueTrophyBig;
    public GameObject crystalTrophyBig;
    // �I�u�W�F�N�g�̐����I�u�W�F
    public GameObject cakeText;
    public GameObject goldCakeText;
    public GameObject chocoText;
    public GameObject goldChocoText;
    public GameObject jellyText;
    public GameObject goldJellyText;
    public GameObject cookieText;
    public GameObject goldCookieText;
    public GameObject redTrophyText;
    public GameObject greenTrophyText;
    public GameObject yellowTrophyText;
    public GameObject blueTrophyText;
    public GameObject crystalTrophyText;
    // �܂��擾���Ă��Ȃ��\���p
    public GameObject question;
    // �O�̑I���I�u�W�F
    public GameObject oldSelectObj;
    public GameObject oldSelectObjText;
    // ���ׂẴA�C�e�������擾�t���O
    bool noOldSelectObjFlag;
    void Start()
    {
        oldSelectObj = cakeBig;
        newSlectNum = 0;
        oldSelectNum = 0;
        collectSelectNum = 0;
        noOldSelectObjFlag = true;
        // �ۑ��t�@�C���̃p�X
        filePath = Application.dataPath + "/StreamingAssets/collectFile.txt";
        // �t�@�C���̓ǂݍ���
        collectNum = File.ReadAllLines(filePath);
        // �I���ɍ��킹�ăI�u�W�F�N�g��\��������
        // �����̑I��l�̐ݒ�
        DisPlaySmallCollectItem();
        DisPlayBigCollectItem();
    }
    void Update()
    {
        newSlectNum = collectSelectNum;
        // �I���I�u�W�F����]������
        oldSelectObj.transform.Rotate(0.0f, 0.25f, 0.0f, Space.World);
        // �ʂ̃I�u�W�F�N�g��I��������
        if (newSlectNum != oldSelectNum)
        {
            // �擾�A�C�e�������邩�ǂ���
            if (noOldSelectObjFlag == false)
            {
                // �O�̑I���I�u�W�F�N�g���\��
                oldSelectObj.SetActive(false);
                oldSelectObjText.SetActive(false);
            }
            question.SetActive(false);

            oldSelectNum = newSlectNum;
            // �I���ɍ��킹�ăI�u�W�F�N�g��\��������
            // �I�𒆃I�u�W�F�N�g�̍X�V
            DisPlayBigCollectItem();
        }
    }
    // �P�[�L���I�𒆂̎��ɕ\�����鏈��
    // ��  ���F�Ȃ�
    // �߂�l�F�Ȃ�
    void DisPlayBigCake()
    {
        // �R���N�g�t�@�C���ɓo�^����Ă��邩�ǂ���
        if (collectNum[0] == "1")
        {
            cakeBig.SetActive(true);  // �I�u�W�F�N�g�̕\��
            cakeText.SetActive(true); // �����e�L�X�g�̕\��
            // �I�𒆃I�u�W�F�N�g�̕ۑ�
            oldSelectObj = cakeBig;     
            oldSelectObjText = cakeText;
            // �A�C�e�����擾���Ă���̂ŃA�C�e�����擾�t���O��false
            noOldSelectObjFlag = false; 
        }
        else
        {
            // ���擾�Ȃ̂ŁH��\��
            question.SetActive(true);
        }
    }
    // ���̃P�[�L���I�𒆂̎��ɕ\�����鏈��
    // ��  ���F�Ȃ�
    // �߂�l�F�Ȃ�
    void DisPlayBigGoldCake()
    {
        // �R���N�g�t�@�C���ɓo�^����Ă��邩�ǂ���
        if (collectNum[1] == "1")
        {
            goldCakeBig.SetActive(true);  // �I�u�W�F�N�g�̕\��
            goldCakeText.SetActive(true); // �����e�L�X�g�̕\��
            // �I�𒆃I�u�W�F�N�g�̕ۑ�
            oldSelectObj = goldCakeBig;
            oldSelectObjText = goldCakeText;
            // �A�C�e�����擾���Ă���̂ŃA�C�e�����擾�t���O��false
            noOldSelectObjFlag = false;
        }
        else
        {
            // ���擾�Ȃ̂ŁH��\��
            question.SetActive(true);
        }
    }
    // �`���R�N���b�J�[���I�𒆂̎��ɕ\�����鏈��
    // ��  ���F�Ȃ�
    // �߂�l�F�Ȃ�
    void DisPlayBigChocoCracker()
    {
        // �R���N�g�t�@�C���ɓo�^����Ă��邩�ǂ���
        if (collectNum[2] == "1")
        {
            chocoBig.SetActive(true);  // �I�u�W�F�N�g�̕\��
            chocoText.SetActive(true); // �����e�L�X�g�̕\��
            // �I�𒆃I�u�W�F�N�g�̕ۑ�
            oldSelectObj = chocoBig;
            oldSelectObjText = chocoText;
            // �A�C�e�����擾���Ă���̂ŃA�C�e�����擾�t���O��false
            noOldSelectObjFlag = false;
        }
        else
        {
            // ���擾�Ȃ̂ŁH��\��
            question.SetActive(true);
        }
    }
    // ���̃`���R�N���b�J�[���I�𒆂̎��ɕ\�����鏈��
    // ��  ���F�Ȃ�
    // �߂�l�F�Ȃ�
    void DisPlayBigGoldChocoCracker()
    {
        // �R���N�g�t�@�C���ɓo�^����Ă��邩�ǂ���
        if (collectNum[3] == "1")
        {
            goldChocoBig.SetActive(true);  // �I�u�W�F�N�g�̕\��
            goldChocoText.SetActive(true); // �����e�L�X�g�̕\��
            // �I�𒆃I�u�W�F�N�g�̕ۑ�
            oldSelectObj = goldChocoBig;
            oldSelectObjText = goldChocoText;
            // �A�C�e�����擾���Ă���̂ŃA�C�e�����擾�t���O��false
            noOldSelectObjFlag = false;
        }
        else
        {
            // ���擾�Ȃ̂ŁH��\��
            question.SetActive(true);
        }
    }
    // �[���[���I�𒆂̎��ɕ\�����鏈��
    // ��  ���F�Ȃ�
    // �߂�l�F�Ȃ�
    void DisPlayBigJelly()
    {
        // �R���N�g�t�@�C���ɓo�^����Ă��邩�ǂ���
        if (collectNum[4] == "1")
        {
            jellyBig.SetActive(true);  // �I�u�W�F�N�g�̕\��
            jellyText.SetActive(true); // �����e�L�X�g�̕\��
            // �I�𒆃I�u�W�F�N�g�̕ۑ�
            oldSelectObj = jellyBig;
            oldSelectObjText = jellyText;
            // �A�C�e�����擾���Ă���̂ŃA�C�e�����擾�t���O��false
            noOldSelectObjFlag = false;
        }
        else
        {
            // ���擾�Ȃ̂ŁH��\��
            question.SetActive(true);
        }
    }
    // ���̃[���[���I�𒆂̎��ɕ\�����鏈��
    // ��  ���F�Ȃ�
    // �߂�l�F�Ȃ�
    void DisPlayBigGoldJelly()
    {
        // �R���N�g�t�@�C���ɓo�^����Ă��邩�ǂ���
        if (collectNum[5] == "1")
        {
            goldJellyBig.SetActive(true);  // �I�u�W�F�N�g�̕\��
            goldJellyText.SetActive(true); // �����e�L�X�g�̕\��
            // �I�𒆃I�u�W�F�N�g�̕ۑ�
            oldSelectObj = goldJellyBig;
            oldSelectObjText = goldJellyText;
            // �A�C�e�����擾���Ă���̂ŃA�C�e�����擾�t���O��false
            noOldSelectObjFlag = false;
        }
        else
        {
            // ���擾�Ȃ̂ŁH��\��
            question.SetActive(true);
        }
    }
    // �N�b�L�[���I�𒆂̎��ɕ\�����鏈��
    // ��  ���F�Ȃ�
    // �߂�l�F�Ȃ�
    void DisPlayBigCookie()
    {
        // �R���N�g�t�@�C���ɓo�^����Ă��邩�ǂ���
        if (collectNum[6] == "1")
        {
            cookieBig.SetActive(true);  // �I�u�W�F�N�g�̕\��
            cookieText.SetActive(true); // �����e�L�X�g�̕\��
            // �I�𒆃I�u�W�F�N�g�̕ۑ�
            oldSelectObj = cookieBig;
            oldSelectObjText = cookieText;
            // �A�C�e�����擾���Ă���̂ŃA�C�e�����擾�t���O��false
            noOldSelectObjFlag = false;
        }
        else
        {
            // ���擾�Ȃ̂ŁH��\��
            question.SetActive(true);
        }
    }
    // ���̃N�b�L�[���I�𒆂̎��ɕ\�����鏈��
    // ��  ���F�Ȃ�
    // �߂�l�F�Ȃ�
    void DisPlayBigGoldCookie()
    {
        // �R���N�g�t�@�C���ɓo�^����Ă��邩�ǂ���
        if (collectNum[7] == "1")
        {
            goldCookieBig.SetActive(true);  // �I�u�W�F�N�g�̕\��
            goldCookieText.SetActive(true); // �����e�L�X�g�̕\��
            // �I�𒆃I�u�W�F�N�g�̕ۑ�
            oldSelectObj = goldCookieBig;
            oldSelectObjText = goldCookieText;
            // �A�C�e�����擾���Ă���̂ŃA�C�e�����擾�t���O��false
            noOldSelectObjFlag = false;
        }
        else
        {
            // ���擾�Ȃ̂ŁH��\��
            question.SetActive(true);
        }
    }
    // �X�e�[�W1�̃g���t�B�[���I�𒆂̎��ɕ\�����鏈��
    // ��  ���F�Ȃ�
    // �߂�l�F�Ȃ�
    void DisPlayBigRedTrophy()
    {
        // �R���N�g�t�@�C���ɓo�^����Ă��邩�ǂ���
        if (collectNum[8] == "1")
        {
            redTrophyBig.SetActive(true);  // �I�u�W�F�N�g�̕\��
            redTrophyText.SetActive(true); // �����e�L�X�g�̕\��
            // �I�𒆃I�u�W�F�N�g�̕ۑ�
            oldSelectObj = redTrophyBig;
            oldSelectObjText = redTrophyText;
            // �A�C�e�����擾���Ă���̂ŃA�C�e�����擾�t���O��false
            noOldSelectObjFlag = false;
        }
        else
        {
            // ���擾�Ȃ̂ŁH��\��
            question.SetActive(true);
        }
    }
    // �X�e�[�W2�̃g���t�B�[���I�𒆂̎��ɕ\�����鏈��
    // ��  ���F�Ȃ�
    // �߂�l�F�Ȃ�
    void DisPlayBigGreenTrophy()
    {
        // �R���N�g�t�@�C���ɓo�^����Ă��邩�ǂ���
        if (collectNum[9] == "1")
        {
            greenTrophyBig.SetActive(true);  // �I�u�W�F�N�g�̕\��
            greenTrophyText.SetActive(true); // �����e�L�X�g�̕\��
            // �I�𒆃I�u�W�F�N�g�̕ۑ�
            oldSelectObj = greenTrophyBig;
            oldSelectObjText = greenTrophyText;
            // �A�C�e�����擾���Ă���̂ŃA�C�e�����擾�t���O��false
            noOldSelectObjFlag = false;
        }
        else
        {
            // ���擾�Ȃ̂ŁH��\��
            question.SetActive(true);
        }
    }
    // �X�e�[�W3�̃g���t�B�[���I�𒆂̎��ɕ\�����鏈��
    // ��  ���F�Ȃ�
    // �߂�l�F�Ȃ�
    void DisPlayBigYellowTrophy()
    {
        // �R���N�g�t�@�C���ɓo�^����Ă��邩�ǂ���
        if (collectNum[10] == "1")
        {
            yellowTrophyBig.SetActive(true);  // �I�u�W�F�N�g�̕\��
            yellowTrophyText.SetActive(true); // �����e�L�X�g�̕\��
            // �I�𒆃I�u�W�F�N�g�̕ۑ�
            oldSelectObj = yellowTrophyBig;
            oldSelectObjText = yellowTrophyText;
            // �A�C�e�����擾���Ă���̂ŃA�C�e�����擾�t���O��false
            noOldSelectObjFlag = false;
        }
        else
        {
            // ���擾�Ȃ̂ŁH��\��
            question.SetActive(true);
        }
    }
    // �X�e�[�W4�̃g���t�B�[���I�𒆂̎��ɕ\�����鏈��
    // ��  ���F�Ȃ�
    // �߂�l�F�Ȃ�
    void DisPlayBigBlueTrophy()
    {
        // �R���N�g�t�@�C���ɓo�^����Ă��邩�ǂ���
        if (collectNum[11] == "1")
        {
            blueTrophyBig.SetActive(true);  // �I�u�W�F�N�g�̕\��
            blueTrophyText.SetActive(true); // �����e�L�X�g�̕\��
            // �I�𒆃I�u�W�F�N�g�̕ۑ�
            oldSelectObj = blueTrophyBig;
            oldSelectObjText = blueTrophyText;
            // �A�C�e�����擾���Ă���̂ŃA�C�e�����擾�t���O��false
            noOldSelectObjFlag = false;
        }
        else
        {
            // ���擾�Ȃ̂ŁH��\��
            question.SetActive(true);
        }
    }
    // �I�[���R���v���[�g�̃g���t�B�[���I�𒆂̎��ɕ\�����鏈��
    // ��  ���F�Ȃ�
    // �߂�l�F�Ȃ�
    void DisPlayBigCrystalTrophy()
    {
        // �R���N�g�t�@�C���ɓo�^����Ă��邩�ǂ���
        if (collectNum[16] == "1")
        {
            crystalTrophyBig.SetActive(true);     // �I�u�W�F�N�g�̕\��
            crystalTrophyText.SetActive(true); // �����e�L�X�g�̕\��
            // �I�𒆃I�u�W�F�N�g�̕ۑ�
            oldSelectObj = crystalTrophyBig;
            oldSelectObjText = crystalTrophyText;
            // �A�C�e�����擾���Ă���̂ŃA�C�e�����擾�t���O��false
            noOldSelectObjFlag = false;
        }
        else
        {
            // ���擾�Ȃ̂ŁH��\��
            question.SetActive(true);
        }
    }
    // �I���A�C�e���̕\������
    // ��  ���F�Ȃ�
    // �߂�l�F�Ȃ�
    void DisPlayBigCollectItem()
    {
        // �I���A�C�e����傫���\�������A�������\��
        switch (collectSelectNum)
        {
            case 0:
                // �P�[�L�̕\��
                DisPlayBigCake();
                break;
            case 1:
                // ���̃P�[�L�̕\��
                DisPlayBigGoldCake();
                break;
            case 2:
                // �`���R�N���b�J�[�̕\��
                DisPlayBigChocoCracker();
                break;
            case 3:
                // ���̃`���R�N���b�J�[�̕\��
                DisPlayBigGoldChocoCracker();
                break;
            case 4:
                // �[���[�̕\��
                DisPlayBigJelly();
                break;
            case 5:
                // ���̃[���[�̕\��
                DisPlayBigGoldJelly();
                break;
            case 6:
                // �N�b�L�[�̕\��
                DisPlayBigCookie();
                break;
            case 7:
                // ���̃N�b�L�[�̕\��
                DisPlayBigGoldCookie();
                break;
            case 8:
                // �X�e�[�W1�g���t�B�[�̕\��
                DisPlayBigRedTrophy();
                break;
            case 9:
                // �X�e�[�W2�g���t�B�[�̕\��
                DisPlayBigGreenTrophy();
                break;
            case 10:
                // �X�e�[�W3�g���t�B�[�̕\��
                DisPlayBigYellowTrophy();
                break;
            case 11:
                // �X�e�[�W4�g���t�B�[�̕\��
                DisPlayBigBlueTrophy();
                break;
            case 12:
                // �I�[���R���v���[�g�g���t�B�[�̕\��
                DisPlayBigCrystalTrophy();
                break;
        }
    }
    // �擾�ς݃A�C�e���̕\������
    // ��  ���F�Ȃ�
    // �߂�l�F�Ȃ�
    void DisPlaySmallCollectItem()
    {
        // ��납��擾�A�C�e����\�������Ă���
        // ��ԃR���N�V������ʂŎ�O�̃I�u�W�F�N�g��I�𒆂ɂ���
        if (collectNum[16] == "1")
        {
            // �I�[���R���v���[�g�g���t�B�[�̕\��
            crystalTrophy.SetActive(true);
            collectSelectNum = 12; // �����I��l�̐ݒ�
        }
        if (collectNum[11] == "1")
        {
            // �X�e�[�W4�g���t�B�[�̕\��
            blueTrophy.SetActive(true);
            collectSelectNum = 11; // �����I��l�̐ݒ�
        }
        if (collectNum[10] == "1")
        {
            // �X�e�[�W3�g���t�B�[�̕\��
            yellowTrophy.SetActive(true);
            collectSelectNum = 10; // �����I��l�̐ݒ�
        }
        if (collectNum[9] == "1")
        {
            // �X�e�[�W2�g���t�B�[�̕\��
            greenTrophy.SetActive(true);
            collectSelectNum = 9; // �����I��l�̐ݒ�
        }
        if (collectNum[8] == "1")
        {
            // �X�e�[�W1�g���t�B�[�̕\��
            redTrophy.SetActive(true);
            collectSelectNum = 8; // �����I��l�̐ݒ�
        }
        if (collectNum[7] == "1")
        {
            // ���̃N�b�L�[�̕\��
            goldCookie.SetActive(true);
            collectSelectNum = 7; // �����I��l�̐ݒ�
        }
        if (collectNum[6] == "1")
        {
            // �N�b�L�[�̕\��
            cookie.SetActive(true);
            collectSelectNum = 6; // �����I��l�̐ݒ�
        }
        if (collectNum[5] == "1")
        {
            // ���̃[���[�̕\��
            goldJelly.SetActive(true);
            collectSelectNum = 5; // �����I��l�̐ݒ�
        }
        if (collectNum[4] == "1")
        {
            // �[���[�̕\��
            jelly.SetActive(true);
            collectSelectNum = 4; // �����I��l�̐ݒ�
        }
        if (collectNum[3] == "1")
        {
            // ���̃`���R�N���b�J�[�̕\��
            goldChoco.SetActive(true);
            collectSelectNum = 3; // �����I��l�̐ݒ�
        }
        if (collectNum[2] == "1")
        {
            // �`���R�N���b�J�[�̕\��
            choco.SetActive(true);
            collectSelectNum = 2; // �����I��l�̐ݒ�
        }
        if (collectNum[1] == "1")
        {
            // ���̃P�[�L�̕\��
            goldCake.SetActive(true);
            collectSelectNum = 1; // �����I��l�̐ݒ�
        }
        if (collectNum[0] == "1")
        {
            // �P�[�L�̕\��
            cake.SetActive(true);
            collectSelectNum = 0; // �����I��l�̐ݒ�
        }
    }
}