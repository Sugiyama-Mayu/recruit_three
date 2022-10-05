using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
// M.S
// �Q�[���N���A�A�Q�[���I�[�o�[����Ƃ��̏���
public class ResultManager : MonoBehaviour
{
    // �P�[�L�̃Q�[�������t���O
    public bool cakeCreamBowlJudge;
    public bool cakeOvenJudge;
    public bool cakeCutJudge;
    public bool cakeDecorationJudge;
    // �`���R�N���b�J�[�̃Q�[�������t���O
    public bool chocoBowlJudge;
    public bool chocoCrackerBowlJudge;
    public bool chocoHardenJudge;
    public bool chocoCoolJudge;
    // �[���[�̃Q�[�������t���O
    public bool orangeBowlJudge;
    public bool orangePourJudge;
    public bool orangePutJudge;
    public bool orangeCoolJudge;
    // �N�b�L�[�̃Q�[�������t���O
    public bool cookieDoughBowlJudge;
    public bool cookieCoolJudge;
    public bool cookieCutOutJudge;
    public bool cookieOvenJudge;
    // ���̃X�e�[�W�̐���
    public int nowSeceneNum;
    // �Q�[���N���A�t���O
    private bool callGameClear;

    public GameObject clearText; // �Q�[���N���A�e�L�X�g
    public GameObject overText;  // �Q�[���I�[�o�[�e�L�X�g
    // �X�N���v�g�ϐ�
    public TimeCount timeCount;
    public AudioScript audioScript;
    // �c�莞��
    public int time;
    // �X�e�[�W�ŗ���Ă��邨�َq�I�u�W�F
    public GameObject CakeBowl;
    public GameObject Cake;
    public GameObject ChocoBowl;
    public GameObject Choco;
    public GameObject OrangeBowl;
    public GameObject Jelly;
    public GameObject CookieDoughBowl;
    public GameObject Cookie;
    // �Q�[���N���A��Ɉ�莞�Ԍo�߂������ǂ����t���O
    private bool DoneStop;
    // �X�R�A
    private int score;
    // �v���C�L�����A�j���[�^�[
    public Animator animatorChef;
    void Start()
    {
        // ������
        cakeCreamBowlJudge = false;
        cakeOvenJudge = false;
        cakeCutJudge = false;
        cakeDecorationJudge = false;
        chocoBowlJudge = false;
        chocoCrackerBowlJudge = false;
        chocoHardenJudge = false;
        chocoCoolJudge = false;
        orangeBowlJudge = false;
        orangePourJudge = false;
        orangePutJudge = false;
        orangeCoolJudge = false;
        cookieDoughBowlJudge = false;
        cookieCoolJudge = false;
        cookieCutOutJudge = false;
        cookieOvenJudge = false;
        callGameClear = false;
        DoneStop = false;
        // ���U���g�ŃX�R�A�Ȃǂ������Ă������߂ɂ��̃I�u�W�F�͎c��
        DontDestroyOnLoad(this);
    }
    void Update()
    {
        // �c�莞�Ԃ̎擾
        time = timeCount.GetTime();
        // �Q�[���N���A���ǂ������肷��
        JudgeClear();
        // �^�C���I�[�o�[�łȂ����ǂ���
        if (TimeCount.isTimeUp == false)
        {
            // �Q�[���N���A�t���O��true���ǂ���
            if (callGameClear == true)
            {
                // �N���A�e�L�X�g��\������
                clearText.SetActive(true);
            }
        }
        else
        {
            // �Q�[���I�[�o�[BGM�ɂ���
            audioScript.SetChangeBGM(3);
            // �Q�[���I�[�o�[�e�L�X�g�̕\��
            overText.SetActive(true);
            switch (nowSeceneNum)
            {
                // ���݂̃X�e�[�W�̂��َq�̃^�O���Q�[���I�[�o�[�̃^�O�ɂ���
                // ���َq���A�N�e�B�u�ɂ���
                case 1:  // �P�[�L
                    CakeBowl.tag = "OverSweets";
                    Cake.tag = "OverSweets";
                    CakeBowl.SetActive(false);
                    Cake.SetActive(false);
                    break;
                case 2:  // �P�[�L�A�`���R�N���b�J�[
                    CakeBowl.tag = "OverSweets";
                    Cake.tag = "OverSweets";
                    ChocoBowl.tag = "OverSweets";
                    Choco.tag = "OverSweets";
                    CakeBowl.SetActive(false);
                    Cake.SetActive(false);
                    ChocoBowl.SetActive(false);
                    Choco.SetActive(false);
                    break;
                case 3:  // �P�[�L�A�`���R�N���b�J�[�A�[���[
                    CakeBowl.tag = "OverSweets";
                    Cake.tag = "OverSweets";
                    ChocoBowl.tag = "OverSweets";
                    Choco.tag = "OverSweets";
                    OrangeBowl.tag = "OverSweets";
                    Jelly.tag = "OverSweets";
                    CakeBowl.SetActive(false);
                    Cake.SetActive(false);
                    ChocoBowl.SetActive(false);
                    Choco.SetActive(false);
                    OrangeBowl.SetActive(false);
                    Jelly.SetActive(false);
                    break;
                case 4:  // �P�[�L�A�`���R�N���b�J�[�A�[���[�A�N�b�L�[
                    CakeBowl.tag = "OverSweets";
                    Cake.tag = "OverSweets";
                    ChocoBowl.tag = "OverSweets";
                    Choco.tag = "OverSweets";
                    OrangeBowl.tag = "OverSweets";
                    Jelly.tag = "OverSweets";
                    CookieDoughBowl.tag = "OverSweets";
                    Cookie.tag = "OverSweets";
                    CakeBowl.SetActive(false);
                    Cake.SetActive(false);
                    ChocoBowl.SetActive(false);
                    Choco.SetActive(false);
                    OrangeBowl.SetActive(false);
                    Jelly.SetActive(false);
                    CookieDoughBowl.SetActive(false);
                    Cookie.SetActive(false);
                    break;
            }
        }
    }
    // �Q�[�����N���A���Ă��邩���f���A�Q�[���N���A����������
    // ��  ���F�Ȃ�
    // �߂�l�F�Ȃ�
    void JudgeClear()
    {
        switch (nowSeceneNum)
        {
            // ���݂̃X�e�[�W�̂��َq�̃~�j�Q�[�����I��(�[�̃Q�[���ȊO�͐���)���Ă��邩�ǂ���
            case 1:  // �P�[�L
                if (ResultCakeGame() == true && Cake.tag == "EndSweets")
                {
                    callGameClear = true;  // �Q�[���N���A�t���O��true
                    audioScript.SetChangeBGM(2);  // �Q�[���N���ABGM�ɂ���
                    // �X�R�A���o��
                    score = timeCount.GetTime() * ResultCakeEdgeSuccess();
                    // �v���C�L�����ɃN���A�A�j���[�V������������
                    animatorChef.SetBool("isClear", true);  
                    StartCoroutine("stopTime");  // ��莞�Ԍo�߂�����
                    // ��莞�Ԍo�߂������ǂ���
                    if (DoneStop == true)
                    {
                        // �v���C�L�����̃A�j���[�V��������߂�
                        animatorChef.SetBool("isClear", false);
                        // ���U���g�V�[�����Ă�
                        SceneManager.LoadScene("ResultScene");
                    }
                }
                break;
            case 2:  // �P�[�L�A�`���R�N���b�J�[
                if (ResultCakeGame() == true && ResultChocoGame() == true 
                    && Cake.tag == "EndSweets" && Choco.tag == "EndSweets")
                {
                    callGameClear = true;  // �Q�[���N���A�t���O��true
                    audioScript.SetChangeBGM(2);  // �Q�[���N���ABGM�ɂ���
                    // �X�R�A���o��
                    score = timeCount.GetTime() * (ResultChocoEdgeSuccess()
                        + ResultCakeEdgeSuccess());
                    // �v���C�L�����ɃN���A�A�j���[�V������������
                    animatorChef.SetBool("isClear", true);  
                    StartCoroutine("stopTime");  // ��莞�Ԍo�߂�����
                    // ��莞�Ԍo�߂������ǂ���
                    if (DoneStop == true)
                    {
                        // �v���C�L�����̃A�j���[�V��������߂�
                        animatorChef.SetBool("isClear", false);
                        // ���U���g�V�[�����Ă�
                        SceneManager.LoadScene("ResultScene");
                    }
                }
                break;
            case 3:  // �P�[�L�A�`���R�N���b�J�[�A�[���[
                if (ResultCakeGame() == true && ResultChocoGame() == true 
                    && ResultOrangeGame() == true && Cake.tag == "EndSweets"
                    && Choco.tag == "EndSweets" && Jelly.tag == "EndSweets")
                {
                    callGameClear = true;  // �Q�[���N���A�t���O��true
                    audioScript.SetChangeBGM(2);  // �Q�[���N���ABGM�ɂ���
                    // �X�R�A���o��
                    score = timeCount.GetTime() * (ResultOrangeEdgeSuccess()
                        + ResultChocoEdgeSuccess() + ResultCakeEdgeSuccess());
                    // �v���C�L�����ɃN���A�A�j���[�V������������
                    animatorChef.SetBool("isClear", true); 
                    StartCoroutine("stopTime");  // ��莞�Ԍo�߂�����
                    // ��莞�Ԍo�߂������ǂ���
                    if (DoneStop == true)
                    {
                        // �v���C�L�����̃A�j���[�V��������߂�
                        animatorChef.SetBool("isClear", false);
                        // ���U���g�V�[�����Ă�
                        SceneManager.LoadScene("ResultScene");
                    }
                }
                break;
            case 4:  // �P�[�L�A�`���R�N���b�J�[�A�[���[�A�N�b�L�[
                if (ResultCakeGame() == true && ResultChocoGame() == true 
                    && ResultOrangeGame() == true && ResultCookieGame() == true
                    && Cake.tag == "EndSweets" && Choco.tag == "EndSweets" 
                    && Jelly.tag == "EndSweets" && Cookie.tag == "EndSweets")
                {
                    callGameClear = true;  // �Q�[���N���A�t���O��true
                    audioScript.SetChangeBGM(2); // �Q�[���N���ABGM�ɂ���
                    // �X�R�A���o��
                    score = timeCount.GetTime() * (ResultCookieEdgeSuccess() 
                        + ResultOrangeEdgeSuccess() + ResultChocoEdgeSuccess()
                        + ResultCakeEdgeSuccess());
                    // �v���C�L�����ɃN���A�A�j���[�V������������
                    animatorChef.SetBool("isClear", true);
                    StartCoroutine("stopTime");  // ��莞�Ԍo�߂�����
                    // ��莞�Ԍo�߂������ǂ���
                    if (DoneStop == true)
                    {
                        // �v���C�L�����̃A�j���[�V��������߂�
                        animatorChef.SetBool("isClear", false);
                        // ���U���g�V�[�����Ă�
                        SceneManager.LoadScene("ResultScene");
                    }
                }
                break;
        }
    }
    // �[�Ŕ������Ȃ��P�[�L�̃Q�[��������(�I��)���Ă��邩�ǂ������ׂ�
    // ��  ���F�Ȃ�
    // �߂�l�Fbool   true   �I�����Ă���
    //                false  �I�����Ă��Ȃ�
    private bool ResultCakeGame()
    {
        // �e�Q�[�����������Ă��邩�ǂ���
        if(cakeCreamBowlJudge == true && cakeCutJudge == true )
        {
            return true;
        }
        return false;
    }
    // �[�Ŕ�������P�[�L�̃Q�[���̐����񐔂𒲂ׂ�
    // ��  ���F�Ȃ�
    // �߂�l�Fint   edgeNum �[�Ŕ�������Q�[���̐�����+1�̐�
    public int ResultCakeEdgeSuccess()
    {
        int edgeNum = 1;
        // �������Ă�����+1���Ă���
        if (cakeOvenJudge == true)
        {
            edgeNum++;
        }
        if ( cakeDecorationJudge == true)
        {
            edgeNum++;
        }
        return edgeNum;
    }
    // �[�Ŕ������Ȃ��`���R�N���b�J�[�̃Q�[��������(�I��)���Ă��邩�ǂ������ׂ�
    // ��  ���F�Ȃ�
    // �߂�l�Fbool   true   �I�����Ă���
    //                false  �I�����Ă��Ȃ�
    private bool ResultChocoGame()
    {
        // �e�Q�[�����������Ă��邩�ǂ���
        if (chocoBowlJudge == true  && chocoHardenJudge == true )
        {
            return true;
        }
        return false;
    }
    // �[�Ŕ�������`���R�N���b�J�[�̃Q�[���̐����񐔂𒲂ׂ�
    // ��  ���F�Ȃ�
    // �߂�l�Fint   edgeNum �[�Ŕ�������Q�[���̐�����+1�̐�
    public int ResultChocoEdgeSuccess()
    {
        int edgeNum = 1;
        // �������Ă�����+1���Ă���
        if ( chocoCrackerBowlJudge == true)
        {
            edgeNum++;
        }
        if (chocoCoolJudge == true)
        {
            edgeNum++;
        }
        return edgeNum;
    }
    // �[�Ŕ������Ȃ��[���[�̃Q�[��������(�I��)���Ă��邩�ǂ������ׂ�
    // ��  ���F�Ȃ�
    // �߂�l�Fbool   true   �I�����Ă���
    //                false  �I�����Ă��Ȃ�
    private bool ResultOrangeGame()
    {
        // �e�Q�[�����������Ă��邩�ǂ���
        if (orangeBowlJudge == true && orangePutJudge == true )
        {
            return true;
        }
        return false;
    }
    // �[�Ŕ�������[���[�̃Q�[���̐����񐔂𒲂ׂ�
    // ��  ���F�Ȃ�
    // �߂�l�Fint   edgeNum �[�Ŕ�������Q�[���̐�����+1�̐�
    public int ResultOrangeEdgeSuccess()
    {
        int edgeNum = 1;
        // �������Ă�����+1���Ă���
        if (orangePourJudge == true)
        {
            edgeNum++;
        }
        if (orangeCoolJudge == true)
        {
            edgeNum++;
        }
        return edgeNum;
    }
    // �[�Ŕ������Ȃ��N�b�L�[�̃Q�[��������(�I��)���Ă��邩�ǂ������ׂ�
    // ��  ���F�Ȃ�
    // �߂�l�Fbool   true   �I�����Ă���
    //                false  �I�����Ă��Ȃ�
    private bool ResultCookieGame()
    {
        // �e�Q�[�����������Ă��邩�ǂ���
        if (cookieDoughBowlJudge == true && cookieCutOutJudge == true )
        {
            return true;
        }
        return false;

    }
    // �[�Ŕ�������N�b�L�[�̃Q�[���̐����񐔂𒲂ׂ�
    // ��  ���F�Ȃ�
    // �߂�l�Fint edgeNum   �[�Ŕ�������Q�[���̐�����+1�̐�
    public int ResultCookieEdgeSuccess()
    {
        int edgeNum = 1;
        // �������Ă�����+1���Ă���
        if ( cookieCoolJudge == true)
        {
            edgeNum++;
        }
        if (cookieOvenJudge == true)
        {
            edgeNum++;
        }
        return edgeNum;
    }
    // callGameClear�̃Q�b�^�[(�Q�[���N���A�ɂȂ������ǂ������ׂ�)
    // ��  ���F�Ȃ�
    // �߂�l�Fbool callGameClear    true  �Q�[���N���A�ɂȂ��Ă���
    //                               false �Q�[���N���A�ɂȂ��Ă��Ȃ�
    public bool GetCallGameClear()
    {
        return callGameClear;
    }
    // �X�R�A�̃Q�b�^�[
    // ��  ���F�Ȃ�
    // �߂�l�Fint score    �X�R�A�̒l
    public int GetScore()
    {
        return score;
    }
    // ���݂̃X�e�[�W���̃Q�b�^�[
    // ��  ���F�Ȃ�
    // �߂�l�Fint nowSeceneNum   ���̃X�e�[�W�̐���
    public int GetSceneNum()
    {
        return nowSeceneNum;
    }
    // ��莞�Ԍo�߂�����
    IEnumerator stopTime()
    {
        yield return new WaitForSecondsRealtime(6.0f);
        // ��莞�Ԍo�߂������t���O��true
        DoneStop = true;
    }
}
