using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// �C�`�S������Q�[���̃C�`�S���N���b�N�������̏����v���O����
[RequireComponent(typeof(Rigidbody))]
public class Clicktarget : MonoBehaviour
{
    Rigidbody rigidBody;
    public ParticleSystem putBerryEffect;
    public GameObject strawpoint;
    public GameObject strawafter;
    public AudioClip soundTask;
    public AudioSource audioSource;
    void Start()
    {
        rigidBody = gameObject.GetComponent<Rigidbody>();
    }
    public void OnUserAction()
    {
        GameObject Berry;
        BerryCrear Berrycrear;
        Berry = GameObject.Find("Clear");
        Berrycrear = Berry.GetComponent<BerryCrear>();
        Berrycrear.Berrycount++;
        audioSource.PlayOneShot(soundTask);                // M.S �N���b�N�O�̃C�`�S�\���������O�ɉ���炷
        strawafter.SetActive(true);
        strawpoint.SetActive(false);
        ParticleSystem newEffect = Instantiate(putBerryEffect);  // M.S �G�t�F�N�g�̍쐬
        newEffect.gameObject.SetActive(true);                    // M.S �G�t�F�N�g���A�N�e�B�u�ɂ���
        // M.S �C�`�S�̈ʒu�ɃG�t�F�N�g���Z�b�g(Y���ȊO)
        newEffect.transform.position = new Vector3(this.transform.position.x, putBerryEffect.transform.position.y, this.transform.position.z);
        newEffect.Play(); // M.S �G�t�F�N�g�̔���
        Destroy(newEffect.gameObject, 5.0f);    // M.S �G�t�F�N�g�̍폜
        Debug.Log("�C�`�S�ɐG����");
    }
}
