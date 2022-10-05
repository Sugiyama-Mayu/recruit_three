using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
// M.S 
// ���َq���x���g�R���x�A�̒[�ɒ��������̃Q�[���̔�����
// ���َq���x���g�R���x�A�̊J�n�ʒu�Ɉړ�����
public class DropObj : MonoBehaviour
{
    // ����������~�j�Q�[��
    public GameObject minigame1;
    public GameObject minigame2;
    public GameObject minigame3;
    public GameObject minigame4;
    public GameObject minigame5;
    public GameObject minigame6;
    public GameObject minigame7;
    public GameObject minigame8;
    public GameObject minigame9;
    public GameObject minigame10;
    public GameObject minigame11;

    // �ޗ��I�u�W�F�N�g�̔z�u�ʒu
    public GameObject fOneLinePos;  // �X�e�[�W1

    public GameObject sOneLinePos;  // �X�e�[�W2
    public GameObject sTwoLinePos;

    public GameObject tOneLinePos;  // �X�e�[�W3
    public GameObject tTwoLinePos;
    public GameObject tThreeLinePos;

    public GameObject foOneLinePos; // �X�e�[�W4
    public GameObject foTwoLinePos;
    public GameObject foThreeLinePos;
    public GameObject foFourLinePos;

    public DropObj onlyDropObj;

    // ���[����
    private int laneCount;
    // �V�[�����̃��[���̐�
    public int laneMax;
    public static bool moveScene;
    // ���ɔz�u���郌�[������
    public int nextLaneNum;
    // �V�[���ɂ���I�u�W�F�N�g�̂܂Ƃ܂�
    public GameObject sceneTogether;
    // �e���َq�̍Ō�ɒ[�Ŕ�������Q�[��
    public MinigameIn cakeDecorationMinigame;
    public MinigameIn hardenChocolateMinigame;
    public MinigameIn crackerChocolateMinigame;
    public MinigameIn orangePourMinigame;
    // �~�j�Q�[���Ǘ��I�u�W�F�N�g
    public MinigameIn onlyMinigameIn;
    // ���U���g�Ǘ��I�u�W�F�N�g
    public ResultManager resultManager;
    // �I�[�u���A�①�ɃQ�[���̃Q�[������
    public bool returnGamejudge;

    private bool DoneSceneMoveSweets;
    // �ڐG�������َq�I�u�W�F�N�g
    private GameObject edgeSweetObj;
    private void Start()
    {
        // ������
        DoneSceneMoveSweets = false;
        returnGamejudge = false;
        moveScene = false;
        laneCount = 0;
    }
    private void Update()
    {
        // �V�[�����ړ������ĂȂ̂��ǂ���
        if (moveScene == true && DoneSceneMoveSweets == true)
        {   // �I�[�u���Q�[���A�①�ɃQ�[���̌��ʂ�ۑ���
            // �Ō�̂��َq�̏ꍇ�AEndSweets�^�O������
            DoneSceneMoveSweets = false;
            if (edgeSweetObj.tag == "CBowl")  // [�P�[�L]�̃{�E��
            {
                // �~�j�Q�[���̌��ʂ�ۑ�
                resultManager.cakeOvenJudge = onlyDropObj.returnGamejudge;
            }        
            else if (edgeSweetObj.tag == "ChocoHarden") // [�`���R�N���b�J�[]�̌ł߂�`���R
            {
                // �~�j�Q�[���̌��ʂ�ۑ�
                resultManager.chocoCoolJudge = onlyDropObj.returnGamejudge;
                edgeSweetObj.tag = "EndSweets";
            }
            else if (edgeSweetObj.tag == "OrangeJelly") // [�[���[]�̃[���[
            {
                // �~�j�Q�[���̌��ʂ�ۑ�
                resultManager.orangeCoolJudge = onlyDropObj.returnGamejudge;
                edgeSweetObj.tag = "EndSweets";
            }
            else if (edgeSweetObj.tag == "DBowl") // [�N�b�L�[]�̃{�E��
            {
                // �~�j�Q�[���̌��ʂ�ۑ�
                resultManager.cookieCoolJudge = onlyDropObj.returnGamejudge;
            }
            else if (edgeSweetObj.tag == "DoughCookie") // [�N�b�L�[]�̐��n
            {
                // �~�j�Q�[���̌��ʂ�ۑ�
                resultManager.cookieOvenJudge = onlyDropObj.returnGamejudge;
                edgeSweetObj.tag = "EndSweets";
            }
            // �~�j�Q�[���̕\��������
            switch (laneMax) {
                case 1:
                    minigame1.SetActive(false);
                    minigame2.SetActive(false);
                    minigame3.SetActive(false);
                    break;
                case 2:
                    minigame1.SetActive(false);
                    minigame2.SetActive(false);
                    minigame3.SetActive(false);
                    minigame4.SetActive(false);
                    minigame5.SetActive(false);
                    minigame6.SetActive(false);
                    break;
                case 3:
                    minigame1.SetActive(false);
                    minigame2.SetActive(false);
                    minigame3.SetActive(false);
                    minigame4.SetActive(false);
                    minigame5.SetActive(false);
                    minigame6.SetActive(false);
                    minigame7.SetActive(false);
                    minigame8.SetActive(false);
                    minigame9.SetActive(false);
                    break;
                case 4:
                    minigame1.SetActive(false);
                    minigame2.SetActive(false);
                    minigame3.SetActive(false);
                    minigame4.SetActive(false);
                    minigame5.SetActive(false);
                    minigame6.SetActive(false);
                    minigame7.SetActive(false);
                    minigame8.SetActive(false);
                    minigame9.SetActive(false);
                    minigame10.SetActive(false);
                    minigame11.SetActive(false);
                    break;                   
            }
            // �~�j�Q�[�����t���O��false
            onlyMinigameIn.duringPlay = false;
            moveScene = false;
        }
    }
    // �[�ł̃~�j�Q�[���̔���
    IEnumerator OccurrenceEdgeMinigame(GameObject edgeObj)
    {
        // ���َq�ɂ���Ĕ�������~�j�Q�[���𕪂���
        // �~�j�Q�[���ɂ���Ă̓V�[�����Ă�
        if (edgeObj.tag == "CBowl")   // [�P�[�L]�̃{�E��
        {
            // ���َq�I�u�W�F�N�g�̕ۑ�
            edgeSweetObj = edgeObj;
            // �V�[���ړ��t���O��true
            DoneSceneMoveSweets = true;
            SceneManager.LoadScene("OvenScene", LoadSceneMode.Additive);
        }
        else if (edgeObj.tag == "CCake") // [�P�[�L]�̃P�[�L
        {
            // �~�j�Q�[���̌Ăяo��
            cakeDecorationMinigame.StartCoroutine("edgeMinigameTimer", edgeObj);
        }
        else if (edgeObj.tag == "ChocoBowl") // [�`���R�N���b�J�[]�̃{�E��
        {
            // �~�j�Q�[���̌Ăяo��
            crackerChocolateMinigame.StartCoroutine("edgeMinigameTimer", edgeObj);
        }
        else if (edgeObj.tag == "ChocoHarden") // [�`���R�N���b�J�[]�̌ł߂�`���R
        {
            // ���َq�I�u�W�F�N�g�̕ۑ�
            edgeSweetObj = edgeObj;
            // �V�[���ړ��t���O��true
            DoneSceneMoveSweets = true;
            // �V�[��(�~�j�Q�[��)�̌Ăяo��
            SceneManager.LoadScene("CoolScene", LoadSceneMode.Additive);
        }
        else if (edgeObj.tag == "OrangeJelly") // [�[���[]�̃[���[
        {
            // ���َq�I�u�W�F�N�g�̕ۑ�
            edgeSweetObj = edgeObj;
            // �V�[���ړ��t���O��true
            DoneSceneMoveSweets = true;
            // �V�[��(�~�j�Q�[��)�̌Ăяo��
            SceneManager.LoadScene("CoolScene", LoadSceneMode.Additive);
        }
        else if (edgeObj.tag == "OBowl")  // [�[���[]�̃{�E��
        {
            // �~�j�Q�[���̌Ăяo��
            orangePourMinigame.StartCoroutine("edgeMinigameTimer", edgeObj);
        }
        else if (edgeObj.tag == "DBowl")  // [�N�b�L�[]�̃{�E��
        {
            // ���َq�I�u�W�F�N�g�̕ۑ�
            edgeSweetObj = edgeObj;
            // �V�[���ړ��t���O��true
            DoneSceneMoveSweets = true;
            // �V�[��(�~�j�Q�[��)�̌Ăяo��
            SceneManager.LoadScene("CoolScene", LoadSceneMode.Additive);
        }
        else if (edgeObj.tag == "DoughCookie")  // [�N�b�L�[]�̐��n
        {
            // ���َq�I�u�W�F�N�g�̕ۑ�
            edgeSweetObj = edgeObj;
            // �V�[���ړ��t���O��true
            DoneSceneMoveSweets = true;
            // �V�[��(�~�j�Q�[��)�̌Ăяo��
            SceneManager.LoadScene("OvenScene", LoadSceneMode.Additive);
        }
        yield break;
    }
    // 1�̃��[���̎��A�[�ɍޗ�(���َq)�I�u�W�F�N�g���ڐG�����ۂ̏���
    // ��  ���FGameObject collSweets  �ڐG�����I�u�W�F�N�g
    //         MinigameIn collObj     �ڐG�����I�u�W�F�N�g��MinigameIn�X�N���v�g
    // �߂�l�F�Ȃ�
    void CollSweetsLaneNumberOf1(GameObject collSweets, MinigameIn collObj)
    {
        // �ڐG�������̂��Q�[���ς݂�������
        if (collSweets.tag == "CBowl" && collSweets.layer == 10)
        {
            // �[�܂ŗ����̂ŃQ�[�����Ăт���
            StartCoroutine("OccurrenceEdgeMinigame", collSweets.gameObject);
            // ���̂��َq���\���ɂ��A���̂��َq��\������
            collSweets.SetActive(false);
            collObj.nextSweets.SetActive(true);
            // �x���g�R���x�A�̊J�n�ʒu�ɂ��َq���ړ�
            collObj.nextSweets.transform.position = fOneLinePos.transform.position;
            onlyMinigameIn.duringPlay = true;

        }
        else if (collSweets.tag == "CCake" && collSweets.layer == 10)
        {
            // �[�܂ŗ����̂ŃQ�[�����Ăт���
            // �Ō�̂��َq�Ȃ̂ŗ����Ȃ�
            StartCoroutine("OccurrenceEdgeMinigame", collSweets.gameObject);
            onlyMinigameIn.duringPlay = true;
        }
        else
        {
            // �Q�[���ς݂łȂ���΁A�I�u�W�F�N�g�̈ʒu���x���g�R���x�A�̊J�n�ʒu�Ɉړ�
            collSweets.transform.position = fOneLinePos.transform.position;

        }
    }
    // 2�̃��[���̎��A�[�ɍޗ�(���َq)�I�u�W�F�N�g���ڐG�����ۂ̏���
    // ��  ���FGameObject collSweets  �ڐG�����I�u�W�F�N�g
    //         MinigameIn collObj     �ڐG�����I�u�W�F�N�g��MinigameIn�X�N���v�g
    // �߂�l�F�Ȃ�
    void CollSweetsLaneNumberOf2(GameObject collSweets, MinigameIn collObj)
    {
        // �ڐG�������̂��Q�[���ς݂�������
        if ((collSweets.tag == "CBowl" || collSweets.tag == "ChocoBowl") && collSweets.layer == 10)
        {
            // �[�܂ŗ����̂ŃQ�[�����Ăт���
            StartCoroutine("OccurrenceEdgeMinigame", collSweets.gameObject);
            // ���̂��َq���\���ɂ��A���̂��َq��\������
            collSweets.SetActive(false);
            collObj.nextSweets.SetActive(true);
            // ���ԂɃx���g�R���x�A�̊J�n�ʒu�Ɉړ�
            if (onlyDropObj.nextLaneNum == 0)
            {
                collObj.nextSweets.transform.position = sOneLinePos.transform.position;
                onlyDropObj.nextLaneNum++;
                onlyMinigameIn.duringPlay = true;
            }
            else if (onlyDropObj.nextLaneNum == 1)
            {
                collObj.nextSweets.transform.position = sTwoLinePos.transform.position;
                onlyDropObj.nextLaneNum = 0;
                onlyMinigameIn.duringPlay = true;
            }
        }
        else if ((collSweets.tag == "CCake" || collSweets.tag == "ChocoHarden") && collSweets.layer == 10)
        {
            // �[�܂ŗ����̂ŃQ�[�����Ăт���
            // �Ō�̂��َq�Ȃ̂ŗ����Ȃ�
            StartCoroutine("OccurrenceEdgeMinigame", collSweets.gameObject);
            onlyMinigameIn.duringPlay = true;
        }
        else
        {
            // �Q�[���ς݂łȂ���΁A�I�u�W�F�N�g�̈ʒu���x���g�R���x�A�̊J�n�ʒu�Ɉړ�
            if (onlyDropObj.nextLaneNum == 0)
            {
                collSweets.transform.position = sOneLinePos.transform.position;
                onlyDropObj.nextLaneNum++;
            }
            else if (onlyDropObj.nextLaneNum == 1)
            {
                collSweets.transform.position = sTwoLinePos.transform.position;
                onlyDropObj.nextLaneNum = 0;
            }
        }
    }
    // 3�̃��[���̎��A�[�ɍޗ�(���َq)�I�u�W�F�N�g���ڐG�����ۂ̏���
    // ��  ���FGameObject collSweets  �ڐG�����I�u�W�F�N�g
    //         MinigameIn collObj     �ڐG�����I�u�W�F�N�g��MinigameIn�X�N���v�g
    // �߂�l�F�Ȃ�
    void CollSweetsLaneNumberOf3(GameObject collSweets, MinigameIn collObj)
    {
        // �ڐG�������̂��Q�[���ς݂�������
        if ((collSweets.tag == "CBowl" || collSweets.tag == "ChocoBowl" || collSweets.tag == "OBowl") && collSweets.layer == 10)
        {
            // �[�܂ŗ����̂ŃQ�[�����Ăт���
            StartCoroutine("OccurrenceEdgeMinigame", collSweets.gameObject);
            // ���̂��َq���\���ɂ��A���̂��َq��\������
            collSweets.SetActive(false);
            collObj.nextSweets.SetActive(true);
            // ���ԂɃx���g�R���x�A�̊J�n�ʒu�Ɉړ�
            if (onlyDropObj.nextLaneNum == 0)
            {
                collObj.nextSweets.transform.position = tOneLinePos.transform.position;
                onlyDropObj.nextLaneNum++;
                onlyMinigameIn.duringPlay = true;
            }
            else if (onlyDropObj.nextLaneNum == 1)
            {
                collObj.nextSweets.transform.position = tTwoLinePos.transform.position;
                onlyDropObj.nextLaneNum++;
                onlyMinigameIn.duringPlay = true;
            }
            else if (onlyDropObj.nextLaneNum == 2)
            {
                collObj.nextSweets.transform.position = tThreeLinePos.transform.position;
                onlyDropObj.nextLaneNum = 0;
                onlyMinigameIn.duringPlay = true;
            }
        }
        else if ((collSweets.tag == "CCake" || collSweets.tag == "ChocoHarden" || collSweets.tag == "OrangeJelly") && collSweets.layer == 10)
        {
            // �[�܂ŗ����̂ŃQ�[�����Ăт���
            // �Ō�̂��َq�Ȃ̂ŗ����Ȃ�
            StartCoroutine("OccurrenceEdgeMinigame", collSweets.gameObject);
            onlyMinigameIn.duringPlay = true;
        }
        else
        {
            // �Q�[���ς݂łȂ���΁A�I�u�W�F�N�g�̈ʒu���x���g�R���x�A�̊J�n�ʒu�Ɉړ�
            if (onlyDropObj.nextLaneNum == 0)
            {
                collSweets.transform.position = tOneLinePos.transform.position;
                onlyDropObj.nextLaneNum++;

            }
            else if (onlyDropObj.nextLaneNum == 1)
            {
                collSweets.transform.position = tTwoLinePos.transform.position;
                onlyDropObj.nextLaneNum++;

            }
            else if (onlyDropObj.nextLaneNum == 2)
            {
                collSweets.transform.position = tThreeLinePos.transform.position;
                onlyDropObj.nextLaneNum = 0;

            }
        }
    }
    // 4�̃��[���̎��A�[�ɍޗ�(���َq)�I�u�W�F�N�g���ڐG�����ۂ̏���
    // ��  ���FGameObject collSweets  �ڐG�����I�u�W�F�N�g
    //         MinigameIn collObj     �ڐG�����I�u�W�F�N�g��MinigameIn�X�N���v�g
    // �߂�l�F�Ȃ�
    void CollSweetsLaneNumberOf4(GameObject collSweets, MinigameIn collObj)
    {
        // �ڐG�������̂��Q�[���ς݂�������
        if ((collSweets.tag == "CBowl" || collSweets.tag == "ChocoBowl" || collSweets.tag == "OBowl" || collSweets.tag == "DBowl") && collSweets.layer == 10)
        {
            // �[�܂ŗ����̂ŃQ�[�����Ăт���
            StartCoroutine("OccurrenceEdgeMinigame", collSweets.gameObject);
            // ���̂��َq���\���ɂ��A���̂��َq��\������
            collSweets.SetActive(false);
            collObj.nextSweets.SetActive(true);
            // ���ԂɃx���g�R���x�A�̊J�n�ʒu�Ɉړ�
            if (onlyDropObj.nextLaneNum == 0)
            {
                collObj.nextSweets.transform.position = foOneLinePos.transform.position;
                onlyDropObj.nextLaneNum++;
                onlyMinigameIn.duringPlay = true;

            }
            else if (onlyDropObj.nextLaneNum == 1)
            {
                collObj.nextSweets.transform.position = foTwoLinePos.transform.position;
                onlyDropObj.nextLaneNum++;
                onlyMinigameIn.duringPlay = true;

            }
            else if (onlyDropObj.nextLaneNum == 2)
            {
                collObj.nextSweets.transform.position = foThreeLinePos.transform.position;
                onlyDropObj.nextLaneNum++;
                onlyMinigameIn.duringPlay = true;

            }
            else if (onlyDropObj.nextLaneNum == 3)
            {
                collObj.nextSweets.transform.position = foFourLinePos.transform.position;
                onlyDropObj.nextLaneNum = 0;
                onlyMinigameIn.duringPlay = true;
            }
        }
        else if ((collSweets.tag == "CCake" || collSweets.tag == "ChocoHarden" || collSweets.tag == "OrangeJelly" || collSweets.tag == "DoughCookie") && collSweets.layer == 10)
        {
            // �[�܂ŗ����̂ŃQ�[�����Ăт���
            // �Ō�̂��َq�Ȃ̂ŗ����Ȃ�
            StartCoroutine("OccurrenceEdgeMinigame", collSweets.gameObject);
            onlyMinigameIn.duringPlay = true;
        }
        else
        {
            // �Q�[���ς݂łȂ���΁A�I�u�W�F�N�g�̈ʒu���x���g�R���x�A�̊J�n�ʒu�Ɉړ�
            if (onlyDropObj.nextLaneNum == 0)
            {
                collSweets.transform.position = foOneLinePos.transform.position;
                onlyDropObj.nextLaneNum++;
            }
            else if (onlyDropObj.nextLaneNum == 1)
            {
                collSweets.transform.position = foTwoLinePos.transform.position;
                onlyDropObj.nextLaneNum++;
            }
            else if (onlyDropObj.nextLaneNum == 2)
            {
                collSweets.transform.position = foThreeLinePos.transform.position;
                onlyDropObj.nextLaneNum++;
            }
            else if (onlyDropObj.nextLaneNum == 3)
            {
                collSweets.transform.position = foFourLinePos.transform.position;
                onlyDropObj.nextLaneNum = 0;
            }
        }
    }
    // �[�̃R���W�����{�b�N�X�ɐڐG������
    private void OnTriggerEnter(Collider other)
    {
        // �~�j�Q�[�����łȂ����ǂ���
        if (onlyMinigameIn.duringPlay == false) { 
        // �����_���ɐ������o��
           int randomNum = Random.Range(0, laneMax);
        // �ڐG�����I�u�W�F�N�g�̏���ǂݍ���
        GameObject collSweets = GameObject.Find(other.name);
        MinigameIn collObj = other.GetComponent<MinigameIn>();
        // ���Ԃ�҂�
        StartCoroutine("StopNextShed");
            if (laneMax == 1)       // �x���g�R���x�A��1�� 
            {
                CollSweetsLaneNumberOf1(collSweets, collObj); // �ڐG�����̌Ăяo��
            }
            else if (laneMax == 2)  // �x���g�R���x�A��2��
            {
                CollSweetsLaneNumberOf2(collSweets, collObj); // �ڐG�����̌Ăяo��
            }
            else if (laneMax == 3)  // �x���g�R���x�A��3��
            {
                CollSweetsLaneNumberOf3(collSweets, collObj); // �ڐG�����̌Ăяo��
            }
            else if (laneMax == 4)  // �x���g�R���x�A��4��
            {
                CollSweetsLaneNumberOf4(collSweets, collObj); // �ڐG�����̌Ăяo��
            }
        }
        // ���َq�ɂ������Ă����͂�������
        other.gameObject.GetComponent<Rigidbody>().velocity = Vector3.zero;
        other.gameObject.GetComponent<Rigidbody>().angularVelocity = Vector3.zero;
    }
    // �҂����Ԃ̔���
    IEnumerator StopNextShed()
    {
        yield return new WaitForSecondsRealtime(3.0f);
    }
}