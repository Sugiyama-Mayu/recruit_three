using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// �X�e�[�W�Z���N�g�V�[���̔w�i�𓮂�������
public class SelectSceneScroll : MonoBehaviour
{
    void Start()
    {        
    }
    void Update()
    {
        float scroll = Mathf.Repeat(Time.time * 0.1f, 1);
        Vector2 offset = new Vector2(scroll, 0);
        GetComponent<Renderer>().sharedMaterial.SetTextureOffset("_MainTex", offset);
    }
}