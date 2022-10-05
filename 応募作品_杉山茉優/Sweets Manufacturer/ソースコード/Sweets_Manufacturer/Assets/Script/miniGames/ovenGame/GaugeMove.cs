using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
// �I�[�u���A�①�ɂ̃Q�[�W���~�߂�Q�[����
// �����Q�[�W�̋�������X�N���v�g
public class GaugeMove : MonoBehaviour
{
    public Slider gauge;
    private bool maxValue;
    public StopRedButton stopRedButton;
    void Start()
    {
        gauge.value = 0;
        maxValue = false;
    }
    void Update()
    {   
        if (stopRedButton.GetStopButton() == false)
        {
            //5�ɒB�����ꍇ�ƁA0�ɖ߂����ꍇ�̃t���O�ؑւ�
            if (gauge.value == 5)
            {
                maxValue = true;
            }

            if (gauge.value == 0)
            {
                maxValue = false;
            }

            //�t���O�ɂ��X���C�_�[�l�̑���
            if (maxValue)
            {
                gauge.value -=4.0f * Time.deltaTime;
            }
            else
            {
                gauge.value += 4.0f * Time.deltaTime;
            }
        }
    }
}

