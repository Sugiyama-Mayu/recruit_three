using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// M.S
// �N�b�L�[�̌^���������┲���^�̓����v���O����
public class MoveCutOut : MonoBehaviour
{
    // �����^�I�u�W�F�N�g
    public GameObject CutOut;
    // �^�𔲂������̃J�E���g�ϐ�
    private int cookieCount;
    // �^�����̌��I�u�W�F�N�g
    public GameObject cutOfOut1;
    public GameObject cutOfOut2;
    public GameObject cutOfOut3;
    public GameObject cutOfOut4;
    // �^���������N�b�L�[�̃I�u�W�F�N�g
    public GameObject cutOutDough1;
    public GameObject cutOutDough2;
    public GameObject cutOutDough3;
    public GameObject cutOutDough4;
    // �N���b�N(�^����)���������ǂ����t���O
    public bool clickStamp;
    // �}�E�X�̈ʒu
    private Vector3 mouseWorldPos;
    private float adjustmentX; // �ړ��ʒu�̒���X���W
    // �Q�[���������������ǂ����t���O
    private bool doneProcess;
    // �^�����̌��̃v���O������ʂ������m�F�ϐ�
    public int cookieStampNum;
    // ���n�̃v���O������ʂ������m�F�ϐ�
    public int cookieDoughNum;
    // �͈͊O�̈�̃v���O������ʂ������m�F�ϐ�
    public int cookieRange;
    // �^�������������̃G�t�F�N�g
    public ParticleSystem cutOutEffect;
    // �^�����������̌��ʉ�
    public AudioClip soundTask;
    AudioSource audioSource;
    // �������t���O
    public bool startFlag;
    // �����^�ƐڐG�����I�u�W�F�N�g��ǉ����郊�X�g
    List<GameObject> colList = new List<GameObject>();
    // ���̈ʒu�𒴂�����N�b�L�[���폜����ʒu�ϐ�
    private float cookieDestroyPos;
    void Start()
    {
        audioSource = GetComponent<AudioSource>();
        // ����������
        InitializationProcess();
        // �^�����̌����A�N�e�B�u�ɂ���
        cutOfOut1.SetActive(false);
        cutOfOut2.SetActive(false);
        cutOfOut3.SetActive(false);
        cutOfOut4.SetActive(false);
        // �폜����ʒu�̐ݒ�;
        cookieDestroyPos = -15.0f;
        adjustmentX = 2.2f; // �ړ��ʒu�̒���X���W
    }
    void Update()
    {
        // �������t���O��true���ǂ���
        if (startFlag == true)
        {
            // ����������
            InitializationProcess();
            // colList�̗v�f�폜
            colList.Clear();
        }
        // �S�Ă̕��𔲂��Ă�����+1
        if (cookieCount == 4)
        {
            cookieCount++;
        }
        FollowMousePos(); // �}�E�X�ɍ��킹�Ĕ����^�𓮂���
        // �͈͊O�̈�A�^�����̌��A���n�̃v���O������ʂ��Ă��邩�ǂ���
        // &�N���b�N�������ǂ���
        if (cookieRange >= 4 && cookieStampNum >= cookieCount
            && cookieDoughNum >= 1 && clickStamp == true)
        {
            int colNum = 0;  // �^�������ł��Ȃ��I�u�W�F�N�g�������+1����
            bool doughColl = false;  // ���n�������true
            // colList�̗v�f������
            foreach (GameObject checkObj in colList)
            {
                if (checkObj.layer == 12) // layer��OutOfRange���ǂ���
                {
                    // �^�������ł��Ȃ��̂�colNum��+1
                    colNum++;
                }
                if (checkObj.layer == 13) // layer��WithinDough���ǂ���
                {
                    doughColl = true; // ���n�Ȃ̂�doughColl��true
                }
            }
            // colList�ɗv�f���������(�����������Ă��Ȃ�)colNum��+1
            if (colList.Count <= 0)
            {
                colNum++;
            }
            // colNum��0�ȉ���doughColl��true���ǂ���
            if (colNum <= 0 && doughColl == true)
            {
                switch (cookieCount)
                {
                    // ���ڂ̌^����
                    case 0:
                        DoFirstCutOutProcess();
                        break;
                    // ���ڂ̌^����
                    case 1:
                        DoSecondCutOutProcess();
                        break;
                    // �O��ڂ̌^����
                    case 2:
                        DoThirdCutOutProcess();
                        break;
                    // �l��ڂ̌^����
                    case 3:
                        DoFourthCutOutProcess();
                        break;
                }
            }
        }
        // �ʂ������m�F�ϐ��A�N���b�N�t���O��������
        cookieRange = 0;
        cookieStampNum = 0;
        cookieDoughNum = 0;
        clickStamp = false;
        // colList�̑S�Ă̗v�f���폜
        colList.Clear();
        // �^���������N�b�L�[�I�u�W�F�N�g1���A�N�e�B�u���ǂ���
        if (cutOutDough1.activeSelf == true)
        {
            // �^���������N�b�L�[�I�u�W�F�N�g1�̌^������̏���
            DoAfterFirstCutOutProcess();        
        }
        // �^���������N�b�L�[�I�u�W�F�N�g2���A�N�e�B�u���ǂ���
        if (cutOutDough2.activeSelf == true)
        {
            // �^���������N�b�L�[�I�u�W�F�N�g2�̌^������̏���
            DoAfterSecondCutOutProcess();
        }
        // �^���������N�b�L�[�I�u�W�F�N�g3���A�N�e�B�u���ǂ���
        if (cutOutDough3.activeSelf == true)
        {
            // �^���������N�b�L�[�I�u�W�F�N�g3�̌^������̏���
            DoAfterThirdCutOutProcess();
        }
        // �^���������N�b�L�[�I�u�W�F�N�g4���A�N�e�B�u���ǂ���
        if (cutOutDough4.activeSelf == true)
        {
            // �^���������N�b�L�[�I�u�W�F�N�g4�̌^������̏���
            DoAfterFourthCutOutProcess();
        }
    }
    // �ڐG���Ă��邩�ǂ���
    private void OnTriggerStay(Collider other)
    {
        // ���N���b�N��������
        if (Input.GetMouseButtonDown(0))
        {
            colList.Add(other.gameObject);
            // �N���b�N�t���O��true
            clickStamp = true;
        }
    }
    // ���ڂ̌^�������������̏���
    // ��  ��:�Ȃ�
    // �߂�l:�Ȃ�
    public void DoFirstCutOutProcess()
    {
        // �^�����̌��̃I�u�W�F�N�g�𔲂��^�̈ʒu�ɃZ�b�g(Y���W�ȊO)
        cutOfOut1.transform.position = new Vector3(CutOut.transform.position.x, cutOfOut1.transform.position.y, CutOut.transform.position.z);
        // �^�����̌��̃I�u�W�F�N�g���A�N�e�B�u�ɂ���
        cutOfOut1.SetActive(true);
        // �^�����G�t�F�N�g�̍쐬
        ParticleSystem newEffect = Instantiate(cutOutEffect);
        // �^�����G�t�F�N�g���A�N�e�B�u�ɂ���
        newEffect.gameObject.SetActive(true);
        // �G�t�F�N�g���^�����̌��̈ʒu�ɃZ�b�g
        newEffect.gameObject.transform.position = cutOfOut1.transform.position;
        // �G�t�F�N�g�̔���
        newEffect.Play();
        // �G�t�F�N�g�̍폜
        Destroy(newEffect.gameObject, 5.0f);
        // �^�����̉񐔂�+1
        cookieCount++;
        // �^����(�^�X�N)�̐����̌��ʉ�
        audioSource.PlayOneShot(soundTask);
        // �^���������N�b�L�[�̃I�u�W�F�N�g���A�N�e�B�u�ɂ���
        cutOutDough1.SetActive(true);
        // �^���������N�b�L�[�̃I�u�W�F�N�g���^�����̌��I�u�W�F�N�g�̈ʒu�ɃZ�b�g(Y���W�͈ȊO)
        cutOutDough1.transform.position = new Vector3(cutOfOut1.transform.position.x, cutOutDough1.transform.position.y, cutOfOut1.transform.position.z);
    }
    // ���ڂ̌^�������������̏���
    // ��  ��:�Ȃ�
    // �߂�l:�Ȃ�
    public void DoSecondCutOutProcess()
    {
        // �^�����̌��̃I�u�W�F�N�g�𔲂��^�̈ʒu�ɃZ�b�g(Y���W�ȊO)
        cutOfOut2.transform.position = new Vector3(CutOut.transform.position.x, cutOfOut2.transform.position.y, CutOut.transform.position.z);
        // �^�����̌����A�N�e�B�u�ɂ���
        cutOfOut2.SetActive(true);
        // �^�����G�t�F�N�g�̍쐬
        ParticleSystem newEffect2 = Instantiate(cutOutEffect);
        // �^�����G�t�F�N�g���A�N�e�B�u�ɂ���
        newEffect2.gameObject.SetActive(true);
        // �G�t�F�N�g���^�����̌��̈ʒu�ɃZ�b�g
        newEffect2.gameObject.transform.position = cutOfOut2.transform.position;
        // �G�t�F�N�g�̔���
        newEffect2.Play();
        // �G�t�F�N�g�̍폜
        Destroy(newEffect2.gameObject, 5.0f);
        // �^�����̉񐔂�+1
        cookieCount++;
        // �^����(�^�X�N)�̐����̌��ʉ�
        audioSource.PlayOneShot(soundTask);
        // �^���������N�b�L�[�̃I�u�W�F�N�g���A�N�e�B�u�ɂ���
        cutOutDough2.SetActive(true);
        // �^���������N�b�L�[�̃I�u�W�F�N�g���^�����̌��I�u�W�F�N�g�̈ʒu�ɃZ�b�g(Y���W�͈ȊO)
        cutOutDough2.transform.position = new Vector3(cutOfOut2.transform.position.x, cutOutDough2.transform.position.y, cutOfOut2.transform.position.z);
    }
    // �O��ڂ̌^�������������̏���
    // ��  ��:�Ȃ�
    // �߂�l:�Ȃ�
    public void DoThirdCutOutProcess()
    {
        // �^�����̌��̃I�u�W�F�N�g�𔲂��^�̈ʒu�ɃZ�b�g(Y���W�ȊO)
        cutOfOut3.transform.position = new Vector3(CutOut.transform.position.x, cutOfOut3.transform.position.y, CutOut.transform.position.z);
        // �^�����̌����A�N�e�B�u�ɂ���
        cutOfOut3.SetActive(true);
        // �^�����G�t�F�N�g�̍쐬
        ParticleSystem newEffect3 = Instantiate(cutOutEffect);
        // �^�����G�t�F�N�g���A�N�e�B�u�ɂ���
        newEffect3.gameObject.SetActive(true);
        // �G�t�F�N�g���^�����̌��̈ʒu�ɃZ�b�g
        newEffect3.gameObject.transform.position = cutOfOut3.transform.position;
        // �G�t�F�N�g�̔���
        newEffect3.Play();
        // �G�t�F�N�g�̍폜
        Destroy(newEffect3.gameObject, 5.0f);
        // �^�����̉񐔂�+
        cookieCount++;
        // �^����(�^�X�N)�̐����̌��ʉ�
        audioSource.PlayOneShot(soundTask);
        // �^���������N�b�L�[�̃I�u�W�F�N�g���A�N�e�B�u�ɂ���
        cutOutDough3.SetActive(true);
        // �^���������N�b�L�[�̃I�u�W�F�N�g���^�����̌��I�u�W�F�N�g�̈ʒu�ɃZ�b�g(Y���W�͈ȊO)
        cutOutDough3.transform.position = new Vector3(cutOfOut3.transform.position.x, cutOutDough3.transform.position.y, cutOfOut3.transform.position.z);
    }
    // �l��ڂ̌^�������������̏���
    // ��  ��:�Ȃ�
    // �߂�l:�Ȃ�
    public void DoFourthCutOutProcess()
    {
        // �^�����̌��̃I�u�W�F�N�g�𔲂��^�̈ʒu�ɃZ�b�g(Y���W�ȊO)
        cutOfOut4.transform.position = new Vector3(CutOut.transform.position.x, cutOfOut1.transform.position.y, CutOut.transform.position.z);
        // �^�����̌����A�N�e�B�u�ɂ���
        cutOfOut4.SetActive(true);
        // �^�����G�t�F�N�g�̍쐬
        ParticleSystem newEffect4 = Instantiate(cutOutEffect);
        // �^�����G�t�F�N�g���A�N�e�B�u�ɂ���
        newEffect4.gameObject.SetActive(true);
        // �G�t�F�N�g���^�����̌��̈ʒu�ɃZ�b�g
        newEffect4.gameObject.transform.position = cutOfOut4.transform.position;
        // �G�t�F�N�g�̔���
        newEffect4.Play();
        // �G�t�F�N�g�̍폜
        Destroy(newEffect4.gameObject, 5.0f);
        // �^�����̉񐔂�+1
        cookieCount++;
        // �^����(�^�X�N)�̐����̌��ʉ�
        audioSource.PlayOneShot(soundTask);
        // �^���������N�b�L�[�̃I�u�W�F�N�g���A�N�e�B�u�ɂ���
        cutOutDough4.SetActive(true);
        // �^���������N�b�L�[�̃I�u�W�F�N�g���^�����̌��I�u�W�F�N�g�̈ʒu�ɃZ�b�g(Y���W�͈ȊO
        cutOutDough4.transform.position = new Vector3(cutOfOut4.transform.position.x, cutOutDough4.transform.position.y, cutOfOut4.transform.position.z);
    }
    // �^���������N�b�L�[�I�u�W�F�N�g1�̌^������̏���
    // ��  ��:�Ȃ�
    // �߂�l:�Ȃ�
    public void DoAfterFirstCutOutProcess()
    {
        // �^���������N�b�L�[�I�u�W�F�N�g1��Z���W��cookieDestroyPos��菬�������ǂ���
        if (cutOutDough1.transform.position.z <= cookieDestroyPos)
        {
            // �^���������N�b�L�[�I�u�W�F�N�g1��Z���W��cookieDestroyPos�ɂ���
            cutOutDough1.transform.position = new Vector3(cutOfOut1.transform.position.x, cutOutDough1.transform.position.y, cookieDestroyPos);
            // �^���������N�b�L�[�I�u�W�F�N�g1���A�N�e�B�u�ɂ���
            cutOutDough1.SetActive(false);
        }
        else
        {
            // �^���������N�b�L�[�I�u�W�F�N�g1��Z���W��cookieDestroyPos�ɂȂ�܂ňړ�������
            cutOutDough1.transform.position -= new Vector3(0.0f, 0.0f, 10.0f) * Time.deltaTime;
        }
    }
    // �^���������N�b�L�[�I�u�W�F�N�g1�̌^������̏���
    // ��  ��:�Ȃ�
    // �߂�l:�Ȃ�
    public void DoAfterSecondCutOutProcess()
    {
        // �^���������N�b�L�[�I�u�W�F�N�g2��Z���W��cookieDestroyPos��菬�������ǂ���
        if (cutOutDough2.transform.position.z <= cookieDestroyPos)
        {
            // �^���������N�b�L�[�I�u�W�F�N�g2��Z���W��cookieDestroyPos�ɂ���
            cutOutDough2.transform.position = new Vector3(cutOfOut2.transform.position.x, cutOutDough2.transform.position.y, cookieDestroyPos);
            // �^���������N�b�L�[�I�u�W�F�N�g2���A�N�e�B�u�ɂ���
            cutOutDough2.SetActive(false);
        }
        else
        {
            // �^���������N�b�L�[�I�u�W�F�N�g2��Z���W��cookieDestroyPos�ɂȂ�܂ňړ�������
            cutOutDough2.transform.position -= new Vector3(0.0f, 0.0f, 10.0f) * Time.deltaTime;
        }
    }
    // �^���������N�b�L�[�I�u�W�F�N�g1�̌^������̏���
    // ��  ��:�Ȃ�
    // �߂�l:�Ȃ�
    public void DoAfterThirdCutOutProcess()
    {
        // �^���������N�b�L�[�I�u�W�F�N�g3��Z���W��cookieDestroyPos��菬�������ǂ���
        if (cutOutDough3.transform.position.z <= cookieDestroyPos)
        {
            // �^���������N�b�L�[�I�u�W�F�N�g3��Z���W��cookieDestroyPos�ɂ���
            cutOutDough3.transform.position = new Vector3(cutOfOut3.transform.position.x, cutOutDough3.transform.position.y, cookieDestroyPos);
            // �^���������N�b�L�[�I�u�W�F�N�g3���A�N�e�B�u�ɂ���
            cutOutDough3.SetActive(false);
        }
        else
        {
            // �^���������N�b�L�[�I�u�W�F�N�g3��Z���W��cookieDestroyPos�ɂȂ�܂ňړ�������
            cutOutDough3.transform.position -= new Vector3(0.0f, 0.0f, 10.0f) * Time.deltaTime;
        }
    }
    // �^���������N�b�L�[�I�u�W�F�N�g1�̌^������̏���
    // ��  ��:�Ȃ�
    // �߂�l:�Ȃ�
    public void DoAfterFourthCutOutProcess()
    {
        // �^���������N�b�L�[�I�u�W�F�N�g4��Z���W��cookieDestroyPos��菬�������ǂ���
        if (cutOutDough4.transform.position.z <= cookieDestroyPos)
        {
            // �^���������N�b�L�[�I�u�W�F�N�g4��Z���W��cookieDestroyPos�ɂ���
            cutOutDough4.transform.position = new Vector3(cutOfOut4.transform.position.x, cutOutDough4.transform.position.y, cookieDestroyPos);
            // �^���������N�b�L�[�I�u�W�F�N�g4���A�N�e�B�u�ɂ���
            cutOutDough4.SetActive(false);

        }
        else
        {
            // �^���������N�b�L�[�I�u�W�F�N�g4��Z���W��cookieDestroyPos�ɂȂ�܂ňړ�������
            cutOutDough4.transform.position -= new Vector3(0.0f, 0.0f, 10.0f) * Time.deltaTime;
        }
    }
    // colList�ɗv�f��ǉ�����֐�
    // ��  ��:�ǉ�������GameObject
    // �߂�l:�Ȃ�
    public void SetCutOutCol(GameObject setObj)
    {
        colList.Add(setObj.gameObject);

    }
    // doneProcess���Z�b�g����֐�
    // ��  ��:true��false
    // �߂�l:�Ȃ�
    public void SetDoneProcess(bool set)
    {
        doneProcess = set;
    }
    // cookieCount(�^������������)�̎擾�֐�
    // ��  ��:�Ȃ�
    // �߂�l:int �^������������
    public int GetCookieCount()
    {
        return cookieCount;
    }
    // �������p�֐�
    // ��  ��:�Ȃ�
    // �߂�l:�Ȃ�
    private void InitializationProcess()
    {
        // �ϐ���������
        cookieCount = 0;
        cookieStampNum = 0;
        cookieDoughNum = 0;
        cookieRange = 0;
        clickStamp = false;
        startFlag = false;
    }
    // �}�E�X�ɒǏ]������֐�
    // ��  ��:�Ȃ�
    // �߂�l:�Ȃ�
    private void FollowMousePos()
    {
        // �}�E�X�̈ʒu�̎擾
        Vector3 mousPos = Input.mousePosition;
        // 3D���W�ɂ������̂�Z���𓖂Ă͂߂�
        mousPos.z = 13.0f;
        // �}�E�X�̈ʒu��3D�̍��W�ɕύX�AmouseWorldPos�ɓ����
        Vector3 mouseWorldPos = Camera.main.ScreenToWorldPoint(mousPos);
        // mouseWorldPos��Y���W�𔲂��^�I�u�W�F�N�g��Y���W�ɃZ�b�g
        mouseWorldPos.y = this.gameObject.transform.position.y;
        // mouseWorldPos��Z���W�̐ݒ�
        mouseWorldPos.z = mouseWorldPos.z - adjustmentX;
        // �����^�I�u�W�F�N�g�̈ʒu���Z�b�g
        CutOut.transform.position = mouseWorldPos;
    }
}
