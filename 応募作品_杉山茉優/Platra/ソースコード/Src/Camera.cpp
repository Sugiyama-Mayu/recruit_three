//=============================================================================
//		�R�c�Q�[���v���O����
//		�b�R�c�`�����P�P�Q                             ver 3.0        2021.1.11
//
//		�J��������
//
//		(���_�ύX�����E��Q����������������Ă���)
//
//																Camera.cpp
//=============================================================================
#include  "Camera.h"
#include  "Playchar.h"
#include  "Map.h"

//==========================================================================================================================
//
// �J�����v���V�[�W���̃R���X�g���N�^
//
//   �Ȃ��A�I�u�W�F�N�g��delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
// -------------------------------------------------------------------------------------------------------------------------
CCameraProc::CCameraProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	m_pObjArray.push_back(new CCameraObj(m_pGMain));  // m_pObjArray�ɃI�u�W�F�N�g��o�^����
}

// --------------------------------------------------------------------------- // -- 2020.11.19
//
// �J�����I�u�W�F�N�g�̃R���X�g���N�^
//
// ---------------------------------------------------------------------------
CCameraObj::CCameraObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	// cameraChangeSwitch 0:���̓��I������ʎ��_ 1:�d��TPS���_ 2:�d�Ԃ̘��� 3���̉˂������
	cameraChangeSwitch = 0;    
	// �J�����̈ʒu�̊�_�̈ʒu
	m_mBaseWorld = XMMatrixTranslation(0, 0, 0);
	// �}�b�v1�Ŏg�p���鐯�̓��I������ʎ��_ 
	// ��_���[���h�}�g���b�N�X����̕ψʏ����l�̐ݒ�
	// �@ ���̘��Վ��_�̂Ƃ��̊�_���[���h�}�g���b�N�X����̕ψʒl
	// �E�����_(����ꏊ)�́A�ψʋ�����m_vStarLocalLookat�ɐݒ肷��
	m_vStarLocalLookat = VECTOR3(0.0f, 0.0f, 0.0f);                // ��_�Ƃ̍���0
	//�����_����̑����ŃJ�����̈ʒu���w��
	m_vStarLocalEye.z = -35.0f;  // �ψʒ������� 
	m_vStarLocalEye.x = 0.0f;    // �ψʊp�x�w
	m_vStarLocalEye.y = 140.0f;  // �ψʊp�x�x  

	// �}�b�v2�Ŏg�p����d��TPS���_���
	// ��_���[���h�}�g���b�N�X����̕ψʏ����l�̐ݒ�
	// �@ ���H�z�u�Q�[����ʂ̂Ƃ��̊�_���[���h�}�g���b�N�X����̕ψʒl
	// �E�����_�́A�ψʋ�����m_vTrainRunLookatTPS�ɐݒ肷��
	m_vTrainRunLookatTPS = VECTOR3(0.0f, 0.0f, 0.0f);     

	//�����_����̑����ŃJ�����̈ʒu���w��
	m_vTrainRunEyeTPS.z = -4.0f;  // �ψʒ�������
	m_vTrainRunEyeTPS.x = 59.0f; // �ψʊp�x�w
	m_vTrainRunEyeTPS.y = 40.0f;   // �ψʊp�x�x

	// �}�b�v2�Ŏg�p����d�Ԃ̘��Չ��
	// ��_���[���h�}�g���b�N�X����̕ψʏ����l�̐ݒ�
	// �@ ���H�z�u�Q�[����ʂ̂Ƃ��̊�_���[���h�}�g���b�N�X����̕ψʒl
	// �E�����_�́A�ψʋ�����m_vBaseLocalLookatTPS�ɐݒ肷��
	m_vTrainStarLookat = VECTOR3(0.0f, 0.0f, 0.9f);           // �����΂߂��猩�ė��̊����o��

	//�����_����̑����ŃJ�����̈ʒu���w��
	m_vTrainStarEye.z = 0.0f;
	m_vTrainStarEye.x = 0.0f;
	m_vTrainStarEye.y = 90.0f;

	// �}�b�v4�Ŏg�p���鐯�̉˂������|������
	// ��_���[���h�}�g���b�N�X����̕ψʏ����l�̐ݒ�
	// �@���̉˂������|�����ʂ̂Ƃ��̊�_���[���h�}�g���b�N�X����̕ψʒl
	// �E�����_�́A�ψʋ�����m_vStarBridgeLookat�ɐݒ肷��
	m_vStarBridgeLookat = VECTOR3(0.0f, 0.0f, 10.0f);

	//�����_����̑����ŃJ�����̈ʒu���w��
	m_vStarBridgeEye.z = -3.0f;  // �ψʒ�������
	m_vStarBridgeEye.x = 0.0f; // �ψʊp�x�w
	m_vStarBridgeEye.y = 50.0f;   // �ψʊp�x�x

	// �J�����ψʏ����l��ݒ肷��
	SetCamBase();
}
// ---------------------------------------------------------------------------
//
// �J�����I�u�W�F�N�g�̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CCameraObj::~CCameraObj()
{
	;
}
//-----------------------------------------------------------------------------  // -- 2020.11.19
// �J�����I�u�W�F�N�g�̐���
//
//�@�o�b�̓����ɍ��킹�ăJ�����𐧌䂷��
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CCameraObj::Update()
{
	// �����_�E���_�̊�_�ƂȂ��_���[���h�}�g���b�N�X�̐ݒ�
	// ������ς���ƃJ�����̏㉺���E�ς�� 
	VECTOR3 vUpVec(0.0f, 1.0f, 0.0f);    // ����ʒu���΍��W�̏�����Ƃ���
	//M.S cameraChangeSwitch 0:���̘��Վ��_ 1:�d��TPS��� 2:�d�Ԃ̘��� 3:���̉˂������ 
	switch (cameraChangeSwitch) {
	case 0:
		m_mBaseWorld = XMMatrixTranslation(35.0f, 0.0f, -25.0f);
		break;
	case 1:
		// M.S �v���C�L�����̍��W�̎擾;
		MATRIX4X4 nowPcPos = m_pGMain->m_pPcProc->GetPcObjPtr()->GetWorld();
		// M.S m_mBaseWorld�̊�_���v���C�L�����̍��W�ɂ���;
		m_mBaseWorld = nowPcPos;
		m_vTrainRunLookatTPS = VECTOR3(0.0f, 0.0f, 0.0f);
		// M.S �v���C�L�����̈ʒu�ɍ��킹�ăJ�����̏���ʒu�����߂�
		switch (m_pGMain->m_pPcProc->GetPcObjPtr()->nowPcPosNum) {
		case 0:
			vUpVec = VECTOR3(0.0f, 1.0f, 0.0f);
			break;
		case 1:
			vUpVec = VECTOR3(0.0f, 0.0f, -1.0f);
			break;
		case 2:
			vUpVec = VECTOR3(0.0f, -1.0f, 0.0f);
			break;
		case 3:
			vUpVec = VECTOR3(0.0f, 0.0f, 1.0f);
			break;
		case 4:
			vUpVec = VECTOR3(1.0f, 0.0f, 0.0f);
			break;
		case 5:
			vUpVec = VECTOR3(-1.0f, 0.0f, 0.0f);
			break;
		}
		break;
	case 2:
		m_mBaseWorld = XMMatrixTranslation(6.0f, -65.0f, 0.0f);
		break;
	case 3:
		m_mBaseWorld = XMMatrixTranslation(0.0f, 0.0f, 0.0f);
		break;
	}
	// �J�����I�u�W�F�N�g�̈ʒu���蓮����
	// �܂��A�J���������ύX�i�s�o�r���_���e�o�r���_���j
	SetCamBase();

	// �����_�̃x�N�g�����쐬���鏈��
	// (�����_�̃��[�J�����W�Ɗ�_���[���h�}�g���b�N�X���|�����킹�A�����_�}�g���b�N�X�𓾂�)
	MATRIX4X4 mLookat = XMMatrixTranslationFromVector(m_vLocalLookat) * m_mBaseWorld;
	m_pGMain->m_vLookatPt = GetPositionVector(mLookat);    // �����_�}�g���b�N�X���璍���_�ʒu�𓾂�

	// �J�����i���_�j�x�N�g�����쐬���鏈��
	// (�J�����i���_�j�̃��[�J�����W�Ɗ�_���[���h�}�g���b�N�X���|�����킹�A���_�}�g���b�N�X�𓾂�)
	MATRIX4X4 mEye = XMMatrixTranslationFromVector(m_vLocalEye) * m_mBaseWorld;
	m_pGMain->m_vEyePt = GetPositionVector( mEye );        // ���_�}�g���b�N�X���王�_�ʒu�𓾂�

	// TPS���_�̎��A��Q����������鏈��
	if (cameraChangeSwitch == 0) EvasiveObstacle();

	// ���_�x�N�g���ƒ����_�x�N�g������J�����̃��[���h�}�g���b�N�X�𓾂�i���͎g�p���Ă��Ȃ��j
	m_mWorld = GetLookatMatrix(m_pGMain->m_vEyePt, m_pGMain->m_vLookatPt);

	// �J����(���_)�̈ʒu�A������A����ђ����_���g�p���āA������W�n�̃r���[�s����쐬
	m_pGMain->m_mView = XMMatrixLookAtLH(m_pGMain->m_vEyePt, m_pGMain->m_vLookatPt, vUpVec);
}
//-----------------------------------------------------------------------------  // -- 2020.11.19
// ��Q����������鏈��
//
// �E���_�ƒ����_�Ƃ̊Ԃɏ�Q�����������ꍇ�A���_����Q���̑O�Ɉړ����鏈��
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CCameraObj::EvasiveObstacle()
{
	VECTOR3 vHit;
	VECTOR3 vNorm;
	if (m_pGMain->m_pMapProc->Hitcheck(m_pGMain->m_vEyePt, m_pGMain->m_vLookatPt, &vHit, &vNorm))   // ��Q���Ƃ̐ڐG�`�F�b�N
	{
		MATRIX4X4 mTemp;
		mTemp = GetLookatMatrix(vHit, m_pGMain->m_vLookatPt);        // ��Q���Ƃ̐ڐG�_���璍���ʒu������}�g���b�N�X
		mTemp = XMMatrixTranslation(0.0f, 0.0f, 0.01f) * mTemp;      // ��Q���Ƃ̐ڐG�_����1cm���������Ɉړ��������_�ʒu�𓾂�
		m_pGMain->m_vEyePt = GetPositionVector(mTemp);
	}
}
//-----------------------------------------------------------------------------  // -- 2020.11.19
// �J�����I�u�W�F�N�g�̎蓮���쐧��
//
//   �J�����I�u�W�F�N�g�̈ʒu���蓮�ő��삷��
//   �܂��A�J���������ύX�i�s�o�r���_���e�o�r���_���j
//-----------------------
//   �����@�@�@�Ȃ�
//------------------------------------------------------
void	CCameraObj::ControlCam()
{
	VECTOR3 nowPcPos = GetPositionVector(m_pGMain->m_pPcProc->GetPcObjPtr()->GetWorld());
	const float fRotUp  = 1.5f;     // �p�x�ύX�̑����l
	const float fDistUp = 0.05f;    // �����ύX�̑����l
	// M.S �J�����ψʏ����l��ݒ�
	SetCamBase();
}
//----------------------------------------------------------------------------- // -- 2020.11.19
// �s�o�r�̂Ƃ��J�����ʒu�̐ݒ菈��
//
//   m_vLocalEyeRotDist.x��m_vLocalEyeRotDist.y�ɉ�]�p�x�Am_vLocalEyeRotDist.z��
//   �����_���王�_�܂ł̒��������������Ă���A
//   ���̒l�ɁA�����̉�]�Ƌ��������Z���A���̌��ʂ���ɁA�ψʒl���v�Z���A
//   ���̌��ʂ�m_vLocalEye�ɐݒ肷��
//
//   ����	float fRotY : �x��]
//			float fRotX : �w��]
//			float fDist : ����
//
//   �߂�l�@�Ȃ�
//-----------------------------------------------------------------------------
void	CCameraObj::SetLocalEyeTPS(float fRotY, float fRotX, float fDist)
{
	m_vLocalEyeRotDist.x += fRotX;
	m_vLocalEyeRotDist.y += fRotY;
	m_vLocalEyeRotDist.z += fDist;
	MATRIX4X4 mRotY = XMMatrixRotationY(XMConvertToRadians(m_vLocalEyeRotDist.y));
	MATRIX4X4 mRotX = XMMatrixRotationX(XMConvertToRadians(m_vLocalEyeRotDist.x));
	MATRIX4X4 mPos  = XMMatrixTranslation(0, 0, m_vLocalEyeRotDist.z);
	mPos = mPos * mRotX * mRotY;
	m_vLocalEye = GetPositionVector(mPos);
}
//----------------------------------------------------------------------------- // -- 2020.11.19
// �J�����ψʏ����l��ݒ肷�鏈��
//
// �@ TPS���_�̂Ƃ�
//    ���_�́A�ψʊp�x�ƕψʒ����������A��Um_vLocalEyeRotDist�ɐݒ肵�A
//    ���̌�SetLocalEyeTPS�֐��ɂ���āAm_vLocalEye�ɐݒ肷��
//    �����_�́A�ψʋ�����m_vLocalLookatTPS�ɐݒ肷��
//
// �A FPS���_�̂Ƃ�
//    ���_�́A�ψʋ�����m_vLocalEye�ɐݒ肷��
//    �����_�́A�ψʋ�����m_vLocalLookat�ɐݒ肷��
//
//   ����	�Ȃ�
//
//   �߂�l�@�Ȃ�
//-----------------------------------------------------------------------------
void	CCameraObj::SetCamBase()
{
	// �J�����ψʂ̏����l��ݒ肷��
	//M.S cameraChangeSwitch 0:���̘��Վ��_ 1:�d��TPS��� 2:�d�Ԃ̘��� 3:���̉˂������ 
	switch (cameraChangeSwitch) {
	case 0:
		m_vLocalEye = m_vStarLocalEye;          // M.S ���_ 
		m_vLocalLookat = m_vStarLocalLookat;    // M.S �����_
		break;
	case 1:
		m_vLocalEyeRotDist = m_vTrainRunEyeTPS; // M.S ���_
		m_vLocalLookat = m_vTrainRunLookatTPS;  // M.S �����_
		SetLocalEyeTPS(0, 0, 0);  
		break;
	case 2:
		m_vLocalEye = m_vTrainStarEye;          // M.S ���_
		m_vLocalLookat = m_vTrainStarLookat;    // M.S �����_
		break;
	case 3:
		m_vLocalEye = m_vStarBridgeEye;         // M.S ���_
		m_vLocalLookat = m_vStarBridgeLookat;   // M.S �����_
		break;			
	}
}