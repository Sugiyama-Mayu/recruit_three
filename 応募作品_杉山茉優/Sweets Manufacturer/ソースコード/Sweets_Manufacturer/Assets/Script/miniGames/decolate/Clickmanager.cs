using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// �C�`�S������Q�[���̃C�`�S���N���b�N�̊Ǘ��v���O����
public class Clickmanager : MonoBehaviour
{
    public string BerryTag = "StrawBerry";
    public BerryCrear berryClear;
    void Start()
    {
    }
    void Update()
    {
        if (Input.GetMouseButtonDown(0))
        {
            Ray ray = new Ray();
            RaycastHit hit = new RaycastHit();
            ray = Camera.main.ScreenPointToRay(Input.mousePosition);
            //�}�E�X�N���b�N�����ꏊ����Ray���΂��A�I�u�W�F�N�g�������true 
            if (Physics.Raycast(ray.origin, ray.direction, out hit, Mathf.Infinity))
            {
                if (hit.collider.gameObject.CompareTag(BerryTag) && berryClear.Berrycount < 7)
                {
                    hit.collider.gameObject.GetComponent<Clicktarget>().OnUserAction();
                }
            }
        }
    }
}
