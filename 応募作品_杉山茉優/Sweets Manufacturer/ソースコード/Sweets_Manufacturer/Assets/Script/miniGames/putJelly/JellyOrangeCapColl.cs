using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// M.S
// �I�����W���[���[�ɔz�u�����Ƃ��̏���
public class JellyOrangeCapColl : MonoBehaviour
{
    // �X�N���v�g�̕ϐ�
    public JellyGameManager jellyGameManager;
    // �z�u���G�t�F�N�g
    public ParticleSystem putParticle;
    // �z�u���T�E���h
    public AudioClip soundTask;
    // �I�[�f�B�I�\�[�X
    AudioSource audioSource;
    void Start()
    {
        // ������
        audioSource = GetComponent<AudioSource>();
    }
    private void OnTriggerEnter(Collider other)
    {
        // �ڐG�������ɐڐG�I�u�W�F�N�g�̃^�O��Orange���ǂ���
        if (other.gameObject.tag == "Orange")
        {
            // �z�u���G�t�F�N�g�̐���
            ParticleSystem newParticle = Instantiate(putParticle);
            // �z�u���G�t�F�N�g���A�N�e�B�u�ɂ���
            newParticle.gameObject.SetActive(true);
            // �z�u���G�t�F�N�g�̈ʒu���Z�b�g
            newParticle.transform.position = 
                new Vector3(this.transform.position.x, putParticle.transform.position.y, this.transform.position.z);
            // �z�u���G�t�F�N�g�̔���
            newParticle.Play();
            // �z�u���G�t�F�N�g���폜
            Destroy(newParticle.gameObject, 5.0f);
            // �[���[�̃{�b�N�X�R���C�_�[���A�N�e�B�u
            this.gameObject.GetComponent<BoxCollider>().enabled = false;
            // �I�����W��Static�ɂ���
            other.gameObject.isStatic = true;
            // �I�����W�I�u�W�F�̃^�O��z�u�ς�(DoneOrange)�ɂ���
            other.gameObject.tag = "DoneOrange";
            // �I�����W�̔z�u����+1����
            jellyGameManager.putOrangeNum++;
            // �I�����W���[���[�̏�ɔz�u�������ʉ�
            audioSource.PlayOneShot(soundTask);
        }
    }
}
