using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// �x���g�R���x�A�̓����̏���
public class belt : MonoBehaviour
{
    // �x���g�R���x�A�̓����𐧌䂷��ϐ�
    public bool stopBeltMove;
    public float TargetDriveSpeed = 0.0f;
    public float CurrentSpeed { get { return _currentSpeed; } }
    [SerializeField] private float _forcePower = 50f;
    public Vector3 DriveDirection = Vector3.forward;
    private float _currentSpeed = 0;
    private List<Rigidbody> _rigidbodies = new List<Rigidbody>();
    private float scroll;
    private GameObject hitObj;
    public bool hitFlag;
    public DropObj dropObj;
    public int stageNum;
    void Start()
    {
        hitFlag = false;
        stopBeltMove = false;
        DriveDirection = DriveDirection.normalized;
    }

    void FixedUpdate()
    {
        if (stopBeltMove == false)
        {
            switch (stageNum)
            {
                case 1:
                    scroll = Mathf.Repeat(Time.time * 0.065f, 1);
                    break;
                case 2:
                    scroll = Mathf.Repeat(Time.time * 0.1f, 1);
                    break;
                case 3:
                    scroll = Mathf.Repeat(Time.time * 0.2f, 1);
                    break;
                case 4:
                    scroll = Mathf.Repeat(Time.time * 0.15f, 1);
                    break;
            }

            Vector2 offset = new Vector2(scroll, 0);
            GetComponent<Renderer>().sharedMaterial.SetTextureOffset("_MainTex", offset);

            //���ł����I�u�W�F�N�g�͏�������
            _rigidbodies.RemoveAll(r => r == null);

            foreach (var r in _rigidbodies)
            {
                //���̂̈ړ����x�̃x���g�R���x�A�����̐������������o��
                var objectSpeed = Vector3.Dot(r.velocity, DriveDirection);

                //�ڕW�l�ȉ��Ȃ��������
                if (objectSpeed < Mathf.Abs(TargetDriveSpeed))
                {
                    r.AddForce(DriveDirection * _forcePower, ForceMode.Acceleration);
                }
            }
            // M.S �ڐG���Ă�����rigidBody���폜����
            // �ڐG���Ɨ��ꂽ���̂ݒǉ��ƍ폜������ƑO�̗͂��c���Ă��܂�����
            // �ڐG���펞�ǉ��ƍ폜������
            if (hitFlag == true)
            {
                var rigidBody = hitObj.GetComponent<Rigidbody>();
                _rigidbodies.Remove(rigidBody);
                hitFlag = false;
            }
        }
    }
    // M.S �ڐG����rigidBody���폜����Ă�����rigidBody��ǉ�����
    void OnCollisionStay(Collision collision)
    {
        if (hitFlag == false)
        {
            var rigidBody = collision.gameObject.GetComponent<Rigidbody>();
            _rigidbodies.Add(rigidBody);
            hitObj = collision.gameObject;  // M.S �ڐG�I�u�W�F�N�g�̕ۑ�
            hitFlag = true;
        }
    }
}