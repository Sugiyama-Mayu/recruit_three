using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// M.S �N���b�J�[���`���R�ɓ����Q�[����
// �`���R�������蔻�菈���v���O����
public class ChocoDropJudge : MonoBehaviour
{
    public Chocodrop chocodrop;      // Chocodrop�X�N���v�g�̕ϐ�
    public ParticleSystem putEffect; // �`���R�ɒu�������̃G�t�F�N�g�̕ϐ�
    public AudioClip soundTask;      // �`���R�ɒu�������̌��ʉ��̕ϐ�
    public AudioSource audioSource;  // audioSource�̕ϐ�
    // �`���R�ƐڐG���Ă��邩�ǂ���
    private void OnTriggerEnter(Collider other)
    {
        // �R���W�����ƃN���b�J�[���ڐG���Ă��邩���Alayer��Live���ǂ���
        if (other.tag == "cracker" && other.gameObject.layer == 11)
        {
            // ���������N���b�J�[�̐���+1
            chocodrop.dropcount++;
            // �N���b�J�[���`���R�Ɏh�������p�x�ɂ���
            other.transform.eulerAngles = new Vector3(0.0f,0.0f,0.0f);
            // �N���b�J�[��static��true�ɂ���
            other.gameObject.isStatic = true;
            // �N���b�J�[��layer��Done�ɂ���
            other.gameObject.layer = 10;
            // �`���R�̃{�b�N�X�R���C�_�[��false�ɂ���
            this.GetComponent<BoxCollider>().enabled = false;
            // �N���b�J�[���`���R�ɒu�������̃G�t�F�N�g���A�N�e�B�u�ɂ���
            putEffect.gameObject.SetActive(true);
            // �N���b�J�[���`���R�ɒu�������̃G�t�F�N�g�𔭐�
            putEffect.Play();
            // �N���b�J�[���`���R�ɒu�������̃G�t�F�N�g���폜
            Destroy(putEffect.gameObject, 0.5f);
            // �N���b�J�[���`���R�ɒu�������̌��ʉ���炷
            audioSource.PlayOneShot(soundTask);
            // SinkCracker�R���[�`���̔���
            StartCoroutine("SinkCracker", other.gameObject);
        }
    }
    // �N���b�J�[���`���R�ɒu������̏���
    IEnumerator SinkCracker(GameObject cracker)
    {
        // 0.5�b�҂�
        yield return new WaitForSecondsRealtime(0.5f);
        // �N���b�J�[�̈ʒu�����`���R�ɒ��߂�
        cracker.transform.position -= new Vector3(0.0f, 0.5f, 0.0f);
        // �{�b�N�X�R���C�_�[��false���Ă��邪
        // �ꉞ�`���R�̔���I�u�W�F�N�g���A�N�e�B�u����
        this.gameObject.SetActive(false);
    }
}
