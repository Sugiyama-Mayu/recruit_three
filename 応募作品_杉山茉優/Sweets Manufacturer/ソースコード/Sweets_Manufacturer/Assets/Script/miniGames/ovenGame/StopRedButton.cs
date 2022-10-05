using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
// �I�[�u���A�N�[���Q�[���̃{�^�����~�߂�X�N���v�g
public class StopRedButton : MonoBehaviour
{
    public MoveRedPoint moveRedPoint;
    public ParticleSystem hitEffect;
    public OvenSceneManager ovenSceneManager;
    public AudioClip soundTask;
    AudioSource audioSource;
    public GameObject gauge;

    void Start()
    {
        audioSource = GetComponent<AudioSource>();
    }

    void Update()
    {
        if (Input.GetKeyDown(KeyCode.Space))
        {
            if (ovenSceneManager.GetNowGameName() == "Ovengame" && moveRedPoint.stopButton == false)
            {
                // M.S �Q�[�W�𑀍�ł���悤�ɂ���
                gauge.GetComponent<Slider>().interactable = true;
                moveRedPoint.stopButton = true;
                // M.S �{�^�����������G�t�F�N�g�̍쐬
                ParticleSystem newEffect = Instantiate(hitEffect);
                // M.S �{�^�����������G�t�F�N�g���A�N�e�B�u�ɂ���
                newEffect.gameObject.SetActive(true);
                // M.S �{�^�����������G�t�F�N�g�̈ʒu���Z�b�g
                newEffect.gameObject.transform.position = new Vector3(0.3f, 3.94f, -0.5f);
                // M.S �{�^�����������G�t�F�N�g�̔���
                newEffect.Play();
                // M.S �{�^�����������G�t�F�N�g�̍폜
                Destroy(newEffect.gameObject, 5.0f);
                // M.S �{�^�������������ʉ�
                audioSource.PlayOneShot(soundTask);

            }
            else if (ovenSceneManager.GetNowGameName() == "CoolGame" && moveRedPoint.stopButton == false)
            {
                // M.S �Q�[�W�𑀍�ł���悤�ɂ���
                gauge.GetComponent<Slider>().interactable = true;
                moveRedPoint.stopButton = true;
                // M.S �{�^�����������G�t�F�N�g�̍쐬
                ParticleSystem newEffect = Instantiate(hitEffect);
                // M.S �{�^�����������G�t�F�N�g���A�N�e�B�u�ɂ���
                newEffect.gameObject.SetActive(true);
                // M.S �{�^�����������G�t�F�N�g�̈ʒu���Z�b�g
                newEffect.gameObject.transform.position = new Vector3(0.3f, 2.41f, -0.5f);
                // M.S �{�^�����������G�t�F�N�g�̔���
                newEffect.Play();
                // M.S �{�^�����������G�t�F�N�g�̍폜
                Destroy(newEffect.gameObject, 5.0f);
                // M.S �{�^�������������ʉ�
                audioSource.PlayOneShot(soundTask);

            }
            // M.S �Q�[�W�𑀍�ł��Ȃ��悤�ɂ���
            gauge.GetComponent<Slider>().interactable = false;
            // M.S �Q�\���I���t���O��true
            ovenSceneManager.finishGame = true;
        }
    }

    public bool GetStopButton()
    {
        return moveRedPoint.stopButton;
    }
}
