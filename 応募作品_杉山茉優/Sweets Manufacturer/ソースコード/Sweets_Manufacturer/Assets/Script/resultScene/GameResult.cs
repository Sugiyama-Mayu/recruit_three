using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using System.IO;
// M.S 
// �Q�[���̌��ʏ���
public class GameResult : MonoBehaviour
{
    // �Q�[���̌��ʂ������Ă���I�u�W�F�N�g
    GameObject resultHaveObj;
    // �X�R�A�̒l
    int score;
    // �X�e�[�W�̐���
    public int sceneNum;
    // �����N
    private int rankNum;
    // �\�����郉���N�̃e�L�X�g
    public Text rankText;
    // �\������c�萧�����Ԃ̃e�L�X�g
    public Text TimeText;
    // �\������Q�[�����Ő��삵�����َq
    public GameObject resultCake;
    public GameObject resultChoco;
    public GameObject resultJelly;
    public GameObject resultCookie;
    public GameObject resultGoldCake;
    public GameObject resultGoldChoco;
    public GameObject resultGoldJelly;
    public GameObject resultGoldCookie;
    // �\������e�X�e�[�W�g���t�B�[�e�L�X�g�C���[�W
    public GameObject stage1Text;
    public GameObject stage2Text;
    public GameObject stage3Text;
    public GameObject stage4Text;
    public GameObject allText;
    // �ǂݍ��ރt�@�C���̃p�X
    string filePath;
    // �ǂݍ��񂾃t�@�C���̓��e������z��
    int[] readCollectNum = new int[17];
    // �ǂݍ��񂾎���
    int time;
    // ���̂��َq�̐���t���O
    bool cakeGold;
    bool chocoGold;
    bool jellyGold;
    bool cookieGold;
    void Start()
    {
        // ���Ԍo�߂�ʏ�ɂ���
        Time.timeScale = 1;
        // ������
        cakeGold = false;
        chocoGold = false;
        jellyGold = false;
        cookieGold = false;
        score = 0;
        // �Q�[���̌��ʂ�ǂݍ���
        resultHaveObj = GameObject.Find("moveSceneObj"); // �I�u�W�F�N�g
        score = resultHaveObj.GetComponent<ResultManager>().GetScore(); // �X�R�A
        // �X�e�[�W��
        sceneNum = resultHaveObj.GetComponent<ResultManager>().GetSceneNum();
        time = resultHaveObj.GetComponent<ResultManager>().time; // �c�莞��
        // ResultManager��OFF
        resultHaveObj.GetComponent<ResultManager>().enabled = false;
        Destroy(GameObject.Find("moveSceneObj")); // �Q�[���̌��ʃI�u�W�F�N�g�̍폜
        // ���َq�I�u�W�F���\���ɂ���
        resultCake.SetActive(false);
        resultChoco.SetActive(false);
        resultJelly.SetActive(false);
        resultCookie.SetActive(false);

        filePath = Application.dataPath + "/StreamingAssets/collectFile.txt";
        // �����ŃR���N�V�����p�̃t�@�C���̓ǂݍ���
        string[] readCollect = File.ReadAllLines(filePath);
        // �����ŃR���N�V�����p�̃t�@�C����int�ւ̕ϊ�
        for (int arrayNum = 0; arrayNum < 17; arrayNum++)
        {
            readCollectNum[arrayNum] = int.Parse(readCollect[arrayNum]);
        }
        // �e���َq�̕\���t���O�ƃt�@�C���o�^�ϐ��̕ύX����
        RegisterSweets();
        // �c�萧�����Ԃ�ۑ�
        TimeText.text = time.ToString();
        // �����N������
        RankByScore();
        // �X�e�[�W�N���A�̃t�@�C���o�^�ϐ��̕ύX����
        RegisterSRankStage();
        // �I�[���R���v���[�g�g���t�B�[�̏����𖞂����Ă��邩
        //  �̊m�F�̂��߂Ƀt�@�C����S�Č��Ă���
        for (int num = 0; num < 16; num++)
        {
            // �t�@�C���ɓo�^����Ă��邩�ǂ���
            if (readCollectNum[num] == 1)
            {
                // �S�Č��I����Ă��邩�ǂ���
                if (num >= 15)
                {
                    // �܂��t�@�C���ɓo�^����Ă��Ȃ����
                    if (readCollectNum[16] == 0)
                    {
                        // �S�ẴX�e�[�W��S�����N�N���A���t�@�C���ɏ�������
                        readCollectNum[16] = 1;
                        // �S�ẴX�e�[�W�N���A�g���t�B�[�l�����b�Z�\�W�̕\��
                        allText.SetActive(true);
                    }
                }
            }
            else
            {
                break;
            }
        }
        // ��ŏ������񂾃R���N�V�����f�[�^���t�@�C���֓���  string��int����������
        readCollect[0] = readCollectNum[0].ToString(); 
        File.WriteAllText(filePath, readCollect[0] + '\n'); // ��x�������݃f�[�^�������āA��������
        for (int i = 1; i < 17; i++)
        {
            readCollect[i] = readCollectNum[i].ToString();  
            File.AppendAllText(filePath, readCollect[i] + '\n'); // �ǋL���Ă���
        }
    }

    void Update()
    {
        // ���َq�̕\��
        // ��������Gold�t���O��true�Ȃ�΋��̂��َq��\��
        // false�Ȃ�Βʏ�̂��َq�̕\��
        switch (sceneNum)
        {
            case 1:   // �X�e�[�W��1�Ȃ��
                if (cakeGold == true)
                {
                    resultGoldCake.SetActive(true);
                }
                else
                {
                    resultCake.SetActive(true);
                }
                break;
            case 2:   // �X�e�[�W��2�Ȃ��
                if (cakeGold == true)
                {
                    resultGoldCake.SetActive(true);
                }
                else
                {
                    resultCake.SetActive(true);
                }
                if (chocoGold == true)
                {
                    resultGoldChoco.SetActive(true);
                }
                else
                {
                    resultChoco.SetActive(true);
                }
                break;
            case 3:   // �X�e�[�W��3�Ȃ��
                if (cakeGold == true)
                {
                    resultGoldCake.SetActive(true);
                }
                else
                {
                    resultCake.SetActive(true);
                }
                if (chocoGold == true)
                {
                    resultGoldChoco.SetActive(true);
                }
                else
                {
                    resultChoco.SetActive(true);
                }
                if (jellyGold == true)
                {
                    resultGoldJelly.SetActive(true);
                }
                else
                {
                    resultJelly.SetActive(true);
                }
                break;
            case 4:   // �X�e�[�W��4�Ȃ��
                if (cakeGold == true)
                {
                    resultGoldCake.SetActive(true);
                }
                else
                {
                    resultCake.SetActive(true);
                }
                if (chocoGold == true)
                {
                    resultGoldChoco.SetActive(true);
                }
                else
                {
                    resultChoco.SetActive(true);
                }
                if (jellyGold == true)
                {
                    resultGoldJelly.SetActive(true);
                }
                else
                {
                    resultJelly.SetActive(true);
                }
                if (cookieGold == true)
                {
                    resultGoldCookie.SetActive(true);
                }
                else
                {
                    resultCookie.SetActive(true);
                }
                break;
        }
    }
    // �e���َq�̕\���t���O�ƃt�@�C���o�^�ϐ��̕ύX����
    // ��  ���F�Ȃ�
    // �߂�l�F�Ȃ�
    void RegisterSweets()
    {
        // �P�[�L�̏o���V�[�����ǂ���
        if (sceneNum == 1 || sceneNum == 2 || sceneNum == 3 || sceneNum == 4)
        {
            // �~�j�Q�[���̐������ʂ���������Ă����
            if (resultHaveObj.GetComponent<ResultManager>().ResultCakeEdgeSuccess() >= 3)
            {
                // ���̃P�[�L�\���t���O��true
                cakeGold = true;
                // �܂��t�@�C���ɓo�^����Ă��Ȃ����
                if (readCollectNum[1] == 0)
                {
                    // ���̃P�[�L�R���N�V������1�ɂ���
                    readCollectNum[1] = 1;
                }
            }
            else
            {
                if (readCollectNum[0] == 0) // �܂��t�@�C���ɓo�^����Ă��Ȃ����
                {
                    readCollectNum[0] = 1; // �P�[�L�̃R���N�V������1
                }
            }
        }
        // �`���R�N���b�J�[�̏o���V�[�����ǂ���
        if (sceneNum == 2 || sceneNum == 3 || sceneNum == 4)
        {
            // �~�j�Q�[���̐������ʂ���������Ă����
            if (resultHaveObj.GetComponent<ResultManager>().ResultChocoEdgeSuccess() >= 3)
            {
                chocoGold = true; // ���̃`���R�N���b�J�[�\���t���O��true
                if (readCollectNum[3] == 0) // �܂��t�@�C���ɓo�^����Ă��Ȃ����
                {
                    // ���̃`���R�N���b�J�[�̃R���N�V������1�ɂ���
                    readCollectNum[3] = 1;
                }
            }
            else
            {
                if (readCollectNum[2] == 0) // �܂��t�@�C���ɓo�^����Ă��Ȃ����
                {
                    readCollectNum[2] = 1; // �`���R�N���b�J�[�̃R���N�V������1
                }
            }
        }
        // �[���[�̏o���V�[�����ǂ���
        if (sceneNum == 3 || sceneNum == 4)
        {
            // �~�j�Q�[���̐������ʂ���������Ă����
            if (resultHaveObj.GetComponent<ResultManager>().ResultOrangeEdgeSuccess() >= 3)
            {
                jellyGold = true; // ���̃[���[�\���t���O��true
                if (readCollectNum[5] == 0) // �܂��t�@�C���ɓo�^����Ă��Ȃ����
                {
                    readCollectNum[5] = 1; // ���̃[���[�̃R���N�V������1�ɂ���
                }
            }
            else
            {
                if (readCollectNum[4] == 0) // �܂��t�@�C���ɓo�^����Ă��Ȃ����
                {
                    readCollectNum[4] = 1; // �[���[�̃R���N�V������1
                }
            }
        }
        // �N�b�L�[�̏o���V�[�����ǂ���
        if (sceneNum == 4)
        {
            // �~�j�Q�[���̐������ʂ���������Ă����
            if (resultHaveObj.GetComponent<ResultManager>().ResultCookieEdgeSuccess() >= 3)
            {
                cookieGold = true; // ���̃N�b�L�[�\���t���O��true                
                if (readCollectNum[7] == 0) // �܂��t�@�C���ɓo�^����Ă��Ȃ����
                {
                    readCollectNum[7] = 1; // ���̃N�b�L�[�̃R���N�V������1�ɂ���
                }
            }
            else
            {
                if (readCollectNum[6] == 0) // �܂��t�@�C���ɓo�^����Ă��Ȃ����
                {
                    readCollectNum[6] = 1; // �N�b�L�[�̃R���N�V������1
                }
            }
        }
    }
    // �X�R�A���烉���N������
    // ��  ���F�Ȃ�
    // �߂�l�F�Ȃ�
    void RankByScore()
    {
        // �X�e�[�W�ƃX�R�A�ɂ���ă����N������
        // rankNum�F1��S�����N 2��A�����N 3��B�����N 4��C�����N
        if (sceneNum == 1)  // �X�e�[�W��1�Ȃ��
        {
            if (score > 240 * 3)
            {
                rankNum = 1;
            }
            else if (score > 220 * 3)
            {
                rankNum = 2;
            }
            else if (score > 200 * 3)
            {
                rankNum = 3;
            }
            else
            {
                rankNum = 4;
            }
        }
        else if (sceneNum == 2)  // �X�e�[�W��2�Ȃ��
        {
            if (score > 220 * 6)
            {
                rankNum = 1;
            }
            else if (score > 190 * 6)
            {
                rankNum = 2;
            }
            else if (score > 160 * 6)
            {
                rankNum = 3;
            }
            else
            {
                rankNum = 4;
            }
        }
        else if (sceneNum == 3) // �X�e�[�W��3�Ȃ��
        {
            if (score > 160 * 9)
            {
                rankNum = 1;
            }
            else if (score > 130 * 9)
            {
                rankNum = 2;
            }
            else if (score > 100 * 9)
            {
                rankNum = 3;
            }
            else
            {
                rankNum = 4;
            }
        }
        else if (sceneNum == 4) // �X�e�[�W��4�Ȃ��
        {
            if (score > 150 * 12)
            {
                rankNum = 1;
            }
            else if (score > 120 * 12)
            {
                rankNum = 2;
            }
            else if (score > 90 * 12)
            {
                rankNum = 3;
            }
            else
            {
                rankNum = 4;
            }
        }
        // rankNum�ɂ����rankText�ɕ\�������N��ۑ�
        switch (rankNum)
        {
            case 1:
                rankText.text = "S";
                break;
            case 2:
                rankText.text = "A";
                break;
            case 3:
                rankText.text = "B";
                break;
            case 4:
                rankText.text = "C";
                break;
        }
    }
    // �X�e�[�W�g���t�B�[�̏����𖞂����Ă���ꍇ
    // �t�@�C���o�^�ϐ��̕ύX�A�l�����b�Z�[�W�̕\��
    // ��  ���F�Ȃ�
    // �߂�l�F�Ȃ�
    void RegisterSRankStage()
    {
        switch (sceneNum)  // �X�e�[�W��
        {
            case 1:  // �X�e�[�W1��S�����N�N���A���������ǂ���
                if (cakeGold == true && rankText.text == "S" && GameManager.hardmode == false)
                {
                    // �܂��t�@�C���ɓo�^����Ă��Ȃ����
                    if (readCollectNum[8] == 0)
                    {
                        // �X�e�[�W1��S�����N�N���A���t�@�C���ɏ�������
                        readCollectNum[8] = 1;
                        // �X�e�[�W1��S�����N�N���A�g���t�B�[�l�����b�Z�\�W�̕\��
                        stage1Text.SetActive(true);
                    }
                }
                // �n�[�h���[�h�ŃX�e�[�W1��S�����N�N���A���������ǂ���
                else if (cakeGold == true && rankText.text == "S" && GameManager.hardmode == true)
                {
                    // �X�e�[�W1��S�����N�N���A���t�@�C���ɏ�������
                    if (readCollectNum[12] == 0)
                    {
                        // �n�[�h���[�h�ŃX�e�[�W1��S�����N�N���A���t�@�C���ɏ�������
                        readCollectNum[12] = 1;
                    }
                }
                break;
            case 2:  // �X�e�[�W2��S�����N�N���A���������ǂ���
                if (cakeGold == true && chocoGold == true && rankText.text == "S" && GameManager.hardmode == false)
                {
                    // �܂��t�@�C���ɓo�^����Ă��Ȃ����
                    if (readCollectNum[9] == 0)
                    {
                        // �X�e�[�W2��S�����N�N���A���t�@�C���ɏ�������
                        readCollectNum[9] = 1;
                        // �X�e�[�W2��S�����N�N���A�g���t�B�[�l�����b�Z�\�W�̕\��
                        stage2Text.SetActive(true);
                    }
                }
                // �n�[�h���[�h�ŃX�e�[�W2��S�����N�N���A���������ǂ���
                else if (cakeGold == true && chocoGold == true && rankText.text == "S" && GameManager.hardmode == true)
                {
                    // �܂��t�@�C���ɓo�^����Ă��Ȃ����
                    if (readCollectNum[13] == 0)
                    {
                        // �n�[�h���[�h�ŃX�e�[�W2��S�����N�N���A���t�@�C���ɏ�������
                        readCollectNum[13] = 1;
                    }
                }
                break;
            case 3:  // �X�e�[�W3��S�����N�N���A���������ǂ���
                if (cakeGold == true && chocoGold == true && jellyGold == true && rankText.text == "S" && GameManager.hardmode == false)
                {
                    // �܂��t�@�C���ɓo�^����Ă��Ȃ����
                    if (readCollectNum[10] == 0)
                    {
                        // �X�e�[�W3��S�����N�N���A���t�@�C���ɏ�������
                        readCollectNum[10] = 1;
                        // �X�e�[�W3��S�����N�N���A�g���t�B�[�l�����b�Z�\�W�̕\��
                        stage3Text.SetActive(true);
                    }
                }
                // �n�[�h���[�h�ŃX�e�[�W3��S�����N�N���A���������ǂ���
                else if (cakeGold == true && chocoGold == true && jellyGold == true && rankText.text == "S" && GameManager.hardmode == true)
                {
                    // �܂��t�@�C���ɓo�^����Ă��Ȃ����
                    if (readCollectNum[14] == 0)
                    {
                        // �n�[�h���[�h�ŃX�e�[�W3��S�����N�N���A���t�@�C���ɏ�������
                        readCollectNum[14] = 1;
                    }
                }
                break;
            case 4:  // �X�e�[�W4��S�����N�N���A���������ǂ���
                if (cakeGold == true && chocoGold == true && jellyGold == true && cookieGold == true && rankText.text == "S" && GameManager.hardmode == false)
                {
                    // �܂��t�@�C���ɓo�^����Ă��Ȃ����
                    if (readCollectNum[11] == 0)
                    {
                        // �X�e�[�W4��S�����N�N���A���t�@�C���ɏ�������
                        readCollectNum[11] = 1;
                        // �X�e�[�W4��S�����N�N���A�g���t�B�[�l�����b�Z�\�W�̕\��
                        stage4Text.SetActive(true);
                    }
                }
                // �n�[�h���[�h�ŃX�e�[�W4��S�����N�N���A���������ǂ���
                else if (cakeGold == true && chocoGold == true && jellyGold == true && cookieGold == true && rankText.text == "S" && GameManager.hardmode == true)
                {
                    // �܂��t�@�C���ɓo�^����Ă��Ȃ����
                    if (readCollectNum[15] == 0)
                    {
                        // �n�[�h���[�h�ŃX�e�[�W4��S�����N�N���A���t�@�C���ɏ�������
                        readCollectNum[15] = 1;
                    }
                }
                break;
        }
    }
}

