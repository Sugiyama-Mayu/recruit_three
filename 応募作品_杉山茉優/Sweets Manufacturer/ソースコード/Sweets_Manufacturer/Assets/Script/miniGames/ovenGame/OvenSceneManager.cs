using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

// �I�[�u���A�①�ɂ̃Q�[�W���~�߂�Q�[���̐���X�N���v�g
public class OvenSceneManager : MonoBehaviour
{
    // �Q�[���������ǂ����̕ϐ�
    public bool ovenSuccess;
    public bool coolSuccess;
    private DropObj dropObjScript;
    private GameObject moveSceneObj;
    private string nowGameName;
    public ParticleSystem clearEffect;
    private bool doneFinishProcess;
    public bool finishGame;
    public AudioClip soundClear;
    AudioSource audioSource;
    public GameObject ovenText;
    public GameObject coolText;

    void Start()
    {
        audioSource = GetComponent<AudioSource>();
        doneFinishProcess = false;
        finishGame = false;
        // M.S �Q�[���̎��s�R���[�`�����Ă�
        if (this.gameObject.name == "Ovengame")
        {
            ovenSuccess = false;
            StartCoroutine("OvenGame");
        }
        else if(this.gameObject.name == "CoolGame")
        {
            coolSuccess = false;
            StartCoroutine("CoolGame");
        }
        nowGameName = this.gameObject.name;
    }
    // �Q�[���V�[���̃I�u�W�F�N�g�̃A�N�e�B�u����̃R���[�`��
    public IEnumerator OvenGame()
    {
        Debug.Log("oven");
       //mainscene��moveSceneObj���Ă�
       moveSceneObj = GameObject.Find("moveSceneObj");
      var mainSceneObj = moveSceneObj.GetComponent<DropObj>();
        // mainScene�̃I�u�W�F�N�g��false�ɂ���B
       mainSceneObj.sceneTogether.SetActive(false);
       moveSceneObj.SetActive(true);
        // M.S �e�L�X�g�̕\��
        ovenText.SetActive(true);
        yield return new WaitForSecondsRealtime(2.0f);
        ovenText.SetActive(false);
        // �~�j�Q�[���̎���
        yield return new WaitForSecondsRealtime(4.0f);
        if (ovenSuccess == true)
        {
            // M.S�N���A�G�t�F�N�g�̍쐬
            ParticleSystem newClearEffect = Instantiate(clearEffect);
            // M.S�N���A�G�t�F�N�g�̈ʒu�̃Z�b�g
            newClearEffect.transform.position = new Vector3(0.0f, 4.19f, -0.53f);
            // M.S�N���A�G�t�F�N�g���A�N�e�B�u�ɂ���
            newClearEffect.gameObject.SetActive(true);
            // M.S�N���A�G�t�F�N�g�̔���
            newClearEffect.Play();
            // M.S�N���A�G�t�F�N�g�̍폜
            Destroy(newClearEffect.gameObject, 5.0f);
            // M.S�N���A���ʉ�
            audioSource.PlayOneShot(soundClear);
        }
        yield return new WaitForSecondsRealtime(1.0f);
        // �Q�[���I����AmainScene�̃I�u�W�F�N�g��true�ɂ���
        mainSceneObj.sceneTogether.SetActive(true);
        // mainScene�̃~�j�Q�[����false�����锻���true
        DropObj.moveScene = true;
        mainSceneObj.returnGamejudge = ovenSuccess;
        // M.S OvenScene�̃A�����[�h
        SceneManager.UnloadSceneAsync("OvenScene");
         yield break;
    }

    public IEnumerator CoolGame()
    {
        Debug.Log("cool");
        //mainscene��moveSceneObj���Ă�
        moveSceneObj = GameObject.Find("moveSceneObj");
     var mainSceneObj = moveSceneObj.GetComponent<DropObj>();
        // mainScene�̃I�u�W�F�N�g��false�ɂ���B
      mainSceneObj.sceneTogether.SetActive(false);
     moveSceneObj.SetActive(true);
        // M.S �e�L�X�g�̕\��
        coolText.SetActive(true);
        yield return new WaitForSecondsRealtime(2.0f);
        coolText.SetActive(false);
        // �~�j�Q�[���̎���
        yield return new WaitForSecondsRealtime(4.0f);
        if (coolSuccess == true)
        {
            // M.S�N���A�G�t�F�N�g�̍쐬
            ParticleSystem newClearEffect = Instantiate(clearEffect);
            // M.S�N���A�G�t�F�N�g�̈ʒu�̃Z�b�g
            newClearEffect.transform.position = new Vector3(0.0f, 2.51f, -0.533f);
            // M.S�N���A�G�t�F�N�g���A�N�e�B�u�ɂ���
            newClearEffect.gameObject.SetActive(true);
            // M.S�N���A�G�t�F�N�g�̔���
            newClearEffect.Play();
            // M.S�N���A�G�t�F�N�g�̍폜
            Destroy(newClearEffect.gameObject, 5.0f);
            // M.S�N���A���ʉ�
            audioSource.PlayOneShot(soundClear);
        }
        yield return new WaitForSecondsRealtime(1.0f);
        // �Q�[���I����AmainScene�̃I�u�W�F�N�g��true�ɂ���
       mainSceneObj.sceneTogether.SetActive(true);
        // mainScene�̃~�j�Q�[����false�����锻���true
        DropObj.moveScene = true;
       mainSceneObj.returnGamejudge = coolSuccess;
        // M.S CoolScene�̃A�����[�h
        SceneManager.UnloadSceneAsync("CoolScene");
        yield break;
    }

    // �I�[�u���Q�[���̐����A�s����������ϐ�
    // ��  ���Fbool judge   true ����  false �s����
    // �߂�l�F�Ȃ�
    public void setOvenGameSuccess(bool judge){
        ovenSuccess = judge;
    }
    // �N�[���Q�[���̐����A�s����������ϐ�
    // ��  ���Fbool judge  true ����  false �s����
    // �߂�l�F�Ȃ�
    public void setCoolGameSuccess(bool judge)
    {
        coolSuccess = judge;
    }
    // M.S ���݃v���C���̃Q�[��(�V�[��)���̎擾
    // ��  ���F�Ȃ�
    // �߂�l�F�Ȃ�
    public string GetNowGameName()
    {
        return nowGameName;
    }
}
