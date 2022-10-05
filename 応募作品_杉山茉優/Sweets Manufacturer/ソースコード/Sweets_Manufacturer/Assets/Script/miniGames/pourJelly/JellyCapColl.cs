using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// M.S
// �[���[�𒍂��Q�[���̒��������̔��菈��
public class JellyCapColl : MonoBehaviour
{
    //�[���[���I�u�W�F
    public GameObject orangeJellyObj;
    // ���������̃G�t�F�N�g
    public ParticleSystem pourEffect;
    // �X�N���v�g�ϐ�
    public JellyPourManager jellyPourManager;
    // ���������̃T�E���h
    public AudioClip soundTask;
    // �I�[�f�B�I�\�[�X
    AudioSource audioSource;
    void Start()
    {
        // ����������
        audioSource = GetComponent<AudioSource>();
    }
    private void OnTriggerEnter(Collider other)
    {
        // �������I�u�W�F�N�g�̐���7�������ǂ���
        if (jellyPourManager.pourCapCount < 7)
        {
            // �[���[���I�u�W�F���A�N�e�B�u�ɂ���
            orangeJellyObj.SetActive(true);
            // �������I�u�W�F�N�g�̐���+1����
            jellyPourManager.pourCapCount++;
            // ��̃{�b�N�X�R���C�_�[���A�N�e�B�u�ɂ���
            this.gameObject.GetComponent<BoxCollider>().enabled = false;
            // ���������̃G�t�F�N�g�𐶐�
            ParticleSystem newParticle = Instantiate(pourEffect);
            // ���������̃G�t�F�N�g���A�N�e�B�u�ɂ���
            newParticle.gameObject.SetActive(true);
            // ���������̃G�t�F�N�g�̈ʒu���Z�b�g
            newParticle.gameObject.transform.position = this.transform.position;
            // ���������̃G�t�F�N�g�̔���
            newParticle.Play();
            // ���������̃G�t�F�N�g���폜
            Destroy(newParticle.gameObject, 5.0f);
            // ���������̌��ʉ�
            audioSource.PlayOneShot(soundTask);
        }
    }
}
