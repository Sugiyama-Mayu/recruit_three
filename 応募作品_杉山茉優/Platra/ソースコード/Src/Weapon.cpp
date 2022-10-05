//=============================================================================
//		�R�c�Q�[���v���O����
//		�b�R�c�`�����P�P�Q�@�@�@�@�@�@                 ver 3.0        2021.1.11
//		����̏���
//															Weapon.cpp
//=============================================================================
#include  "Enemy.h"
#include  "Playchar.h"
#include  "Weapon.h"
#include  "Map.h"
#include  "Effect.h"
#include  "BackFore.h"

//=============================================================================================================================
//
// ���탁�C���v���V�[�W���̃R���X�g���N�^
//
//   �Ȃ��A�v���V�[�W����delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
// ----------------------------------------------------------------------------------------------------------------------------
CWeaponProc::CWeaponProc(CGameMain* pGMain) : CBaseProc(pGMain)
{

	m_pWeaponLaserProc = new CWeaponLaserProc(pGMain);		// ����E���[�U�[�v���V�[�W��
	m_pProcArray.push_back(m_pWeaponLaserProc);				// �v���V�[�W�����v���V�[�W���z��ɓo�^����

	m_pWeaponFireBallProc = new CWeaponFireBallProc(pGMain);	// ����E�΂̋ʃv���V�[�W��
	m_pProcArray.push_back(m_pWeaponFireBallProc);				// �v���V�[�W�����v���V�[�W���z��ɓo�^����

	m_pWeaponSwordProc = new CWeaponSwordProc(pGMain);		// ����E���v���V�[�W��
	m_pProcArray.push_back(m_pWeaponSwordProc);				// �v���V�[�W�����v���V�[�W���z��ɓo�^����

	m_pWeaponFlameProc = new CWeaponFlameProc(pGMain);		// ����E�΂����₫�v���V�[�W��
	m_pProcArray.push_back(m_pWeaponFlameProc);				// �v���V�[�W�����v���V�[�W���z��ɓo�^����

	m_pWeaponBallProc = new CWeaponBallProc(pGMain);		// ����E�{�[���v���V�[�W��
	m_pProcArray.push_back(m_pWeaponBallProc);				// �v���V�[�W�����v���V�[�W���z��ɓo�^����

	m_pWeaponSprayProc = new CWeaponSprayProc(pGMain);		// ����E�X�v���[�v���V�[�W��
	m_pProcArray.push_back(m_pWeaponSprayProc);				// �v���V�[�W�����v���V�[�W���z��ɓo�^����

	m_pWeaponHoldProc = new CWeaponHoldProc(pGMain);		// ����E��Ɏ��A�C�e���̃v���V�[�W��
	m_pProcArray.push_back(m_pWeaponHoldProc);				// �v���V�[�W�����v���V�[�W���z��ɓo�^����


}


// ================================================================================================================================
// 
// �e����v���V�[�W�����̏���
// 
// ================================================================================================================================


// ================================================================================================================================
// ---------------------------------------------------------------------------
//
// ����E���[�U�[�v���V�[�W���̃R���X�g���N�^
//
//   �Ȃ��A�I�u�W�F�N�g��delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
// ---------------------------------------------------------------------------
CWeaponLaserProc::CWeaponLaserProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	// ���[�U�[���b�V���̐ݒ�
	//m_pMesh = new CFbxMesh( m_pGMain->m_pFbxMeshCtrl, _T("Data/Item/Laser2.mesh"));

	for (int i = 0; i < LASER_MAX; i++)
	{
		m_pObjArray.push_back(new CWeaponLaserObj(m_pGMain));	// m_pObjArray�ɕ���E���[�U�[�I�u�W�F�N�g�𐶐�����
		((CWeaponLaserObj*)m_pObjArray[i])->SetMesh(m_pMesh );  // ���b�V���̃A�h���X���I�u�W�F�N�g�ɐݒ肷��
	}
}
// ---------------------------------------------------------------------------
//
// ����E���[�U�[�v���V�[�W���̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CWeaponLaserProc::~CWeaponLaserProc()
{
	SAFE_DELETE(m_pMesh);
}
// ---------------------------------------------------------------------------
//
// ����E���[�U�[�v���V�[�W���̔���
//
//  MATRIX4X4  mGun         �F�e�̈ʒu�}�g���b�N�X
//  VECTOR3 vOffset      �F�ʒu�̔�����
//  MATRIX4X4  mOwnerWorld  �F���˂���L�����̃}�g���b�N�X
//  DWORD       dwOwner      �F����𔭎˂����L�����敪�iPC:PC(�ȗ��l)�@ENM:�G�j
//
// ---------------------------------------------------------------------------
BOOL CWeaponLaserProc::Start(MATRIX4X4 mGun, VECTOR3 vOffset, MATRIX4X4 mOwnerWorld, DWORD dwOwner)
{
	// ���[�U�[�̔���
	MATRIX4X4 mLay, mOwnerRot, mOffset;
	
	mLay = GetPositionMatrix(mGun);               // �e�̈ʒu(��]����菜��)
	mOwnerRot = GetRotateMatrix(mOwnerWorld);     // ���˂���L�����̉�]�}�g���b�N�X�̂�(�ʒu����菜��)�ɂ���
	mLay = mOwnerRot * mLay;                      // �e�̈ʒu����A�L�����̕����Ŕ��˂���}�g���b�N�X�����
	mOffset = XMMatrixTranslation(vOffset.x, vOffset.y, vOffset.z);	// �ʒu�̔�����
	mLay = mOffset * mLay;

	for (int i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			m_pObjArray[i]->Start(mLay, dwOwner);	       // ����E���[�U�[�I�u�W�F�N�g�̔���
			return TRUE;
		}
	}

	return FALSE;
}

// ---------------------------------------------------------------------------
//
// ����E���[�U�[�v���V�[�W���̔���
//
//  MATRIX4X4  mWorld       �F���[�U�[�̔��ˈʒu�̃}�g���b�N�X
//  DWORD       dwOwner      �F����𔭎˂����L�����敪�iPC:PC(�ȗ��l)�@ENM:�G�j
//
// ---------------------------------------------------------------------------
BOOL CWeaponLaserProc::Start(MATRIX4X4 mWorld, DWORD dwOwner)
{
	for (int i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			m_pObjArray[i]->Start(mWorld, dwOwner);	       // ����E���[�U�[�I�u�W�F�N�g�̔���
			return TRUE;
		}
	}
	return FALSE;
}

// ---------------------------------------------------------------------------
//
// ����E���[�U�[�I�u�W�F�N�g�̃R���X�g���N�^
//
// ---------------------------------------------------------------------------
CWeaponLaserObj::CWeaponLaserObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	const int nAtc = 10;				// ���[�U�[�̍U����

	m_vTarget = VECTOR3(0, 0, 0);		// �^�[�Q�b�g
	m_vStart = VECTOR3(0, 0, 0);		// ���ˈʒu
	m_vEnd = VECTOR3(0, 0, 0);			// �ŏI���B�_

	m_bActive = FALSE;
	m_dwStatus = NORMAL;

	m_nAtc = nAtc;

	m_dwOwner = 0;


}
// ---------------------------------------------------------------------------
//
// ����E���[�U�[�I�u�W�F�N�g�̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CWeaponLaserObj::~CWeaponLaserObj()
{
	;
}

// ---------------------------------------------------------------------------
//
// ����E���[�U�[�I�u�W�F�N�g�̔���
//
//     MATRIX4X4 mStartWorld     ���[�U�[�̔��ˈʒu�̃}�g���b�N�X
//     DWORD      dwOwner         ����𔭎˂����L�����敪�iPC:PC(�ȗ��l)�@ENM:�G�j
//
//     �߂�l�@�@�Ȃ�
// ---------------------------------------------------------------------------
BOOL CWeaponLaserObj::Start(MATRIX4X4 mStartWorld, DWORD dwOwner)
{
	const float fLength = 25.0f;		// ���[�U�[�̒���

	if (m_bActive) return FALSE;

	m_bActive = TRUE;
	m_mWorldOld = mStartWorld;  // ���[�U�[�̔��ˈʒu�̃}�g���b�N�X��ۑ����Ă���

	MATRIX4X4 mScale;
	mScale = XMMatrixScaling(1.0f, 1.0f, fLength);  // ���[�U�[�̒����̊g��}�g���b�N�X���쐬����
	m_mWorld = mScale * mStartWorld;                // ���[�U�[�̔��ˈʒu���烌�[�U�[�̒����Ɋg�債���}�g���b�N�X���쐬����

	MATRIX4X4 mTrans;
	mTrans = XMMatrixTranslation(0.0f, 0.0f, fLength);
	mTrans = mTrans * mStartWorld;     // ���[�U�[�̓��B�_�̃}�g���b�N�X���쐬����

	m_vStart = GetPositionVector(m_mWorldOld);	// ���[�U�[�̔��ˈʒu
	m_vEnd = GetPositionVector(mTrans);			// ���[�U�[�̓��B�ʒu

	m_dwOwner = dwOwner;

	return TRUE;
}

// ---------------------------------------------------------------------------
//
// ����E���[�U�[�I�u�W�F�N�g�̍X�V
//
//     �����@�@�@�Ȃ�
//     �߂�l�@�@�Ȃ�
// ---------------------------------------------------------------------------
void CWeaponLaserObj::Update()
{

	if (m_bActive)
	{
		// �G��o�b�Ƃ̂����蔻��
		if ( ( m_dwOwner != ENM && m_pGMain->m_pEnmProc->Hitcheck(this, m_vEnd, m_vStart) )
			|| ( m_dwOwner != PC && m_pGMain->m_pPcProc->Hitcheck(this, m_vEnd, m_vStart)) )
		{
			m_pGMain->m_pEffectProc->m_pParticleProc->Start(m_vHitPos, m_vHitNormal);	// �p�[�e�B�N���̔���
			//m_pGMain->m_pEffectProc->m_pBillProc->Start(m_vHitPos);	// �����r���{�[�h�̔���

		}
		else {
			// �}�b�v�Ƃ̂����蔻��
			VECTOR3 vHit, vNormal;
			if (m_pGMain->m_pMapProc->Hitcheck(m_vEnd, m_vStart, &vHit, &vNormal))
			{
				m_pGMain->m_pEffectProc->m_pParticleProc->Start(vHit, vNormal);	// �p�[�e�B�N���̔���
				//m_pGMain->m_pEffectProc->m_pBillProc->Start(vHit);	// �����r���{�[�h�̔���
			}
		}

		// �����_�����O
		Render();

	}

	m_bActive = FALSE;	// �P��ł�������

}

// ---------------------------------------------------------------------------
//
// ����E���[�U�[�I�u�W�F�N�g�̃����_�����O
//
//   �A�e�����Ȃ������_�����O�@���̕�����(0,0,0)
//
//     �����@�@�@�Ȃ�
//     �߂�l�@�@�Ȃ�
// ---------------------------------------------------------------------------
void CWeaponLaserObj::Render()
{
	int shineFlag = 0;
	// ���Z�����F�̃u�����f�B���O��ݒ�
	UINT mask = 0xffffffff;
	m_pGMain->m_pD3D->m_pDeviceContext->OMSetBlendState(m_pGMain->m_pD3D->m_pBlendStateAdd, NULL, mask);
	m_pMesh->Render(m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, VECTOR3(0, 0, 0), m_pGMain->m_vEyePt, shineFlag);

	// �ʏ�̃u�����f�B���O��ݒ�
	m_pGMain->m_pD3D->m_pDeviceContext->OMSetBlendState(m_pGMain->m_pD3D->m_pBlendStateTrapen, NULL, mask);

}


// ================================================================================================================================
//============================================================================
//
// ����E�΂̋ʃv���V�[�W���̃R���X�g���N�^
//
//   �Ȃ��A�I�u�W�F�N�g��delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
// ---------------------------------------------------------------------------
CWeaponFireBallProc::CWeaponFireBallProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	// �΂̋ʃ��b�V���̐ݒ�
	//m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Item/FireBall.mesh"));

	for (int i = 0; i < FIREBALL_MAX; i++)
	{
		m_pObjArray.push_back(new CWeaponFireBallObj(m_pGMain));	// m_pObjArray�ɕ���E�΂̋ʃI�u�W�F�N�g�𐶐�����
		((CWeaponFireBallObj*)m_pObjArray[i])->SetMesh(m_pMesh);  // ���b�V���̃A�h���X���I�u�W�F�N�g�ɐݒ肷��
	}
}
//============================================================================
//
// ����E�΂̋ʃv���V�[�W���̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CWeaponFireBallProc::~CWeaponFireBallProc()
{
	SAFE_DELETE(m_pMesh);
}
// ---------------------------------------------------------------------------
//
// ����E�΂̋ʃv���V�[�W���̔���
//
//  VECTOR3 vStart       �F���ˈʒu
//  VECTOR3 vTarget      �F�ڕW�ʒu
//  DWORD       dwOwner      �F����𔭎˂����L�����敪�iPC:PC(�ȗ��l)�@ENM:�G�j
//
// ---------------------------------------------------------------------------
BOOL CWeaponFireBallProc::Start(VECTOR3 vStart, VECTOR3 vTarget, DWORD dwOwner)
{
	const int nNum = 5;      // �΂̋ʂ̐�

	int n = nNum;
	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			m_pObjArray[i]->Start(vStart, vTarget, dwOwner);	// ����E�΂̋ʃI�u�W�F�N�g
			n--;
			if (n > 0) continue;
			return TRUE;
		}
	}
	return FALSE;
}

//============================================================================
//
// ����E�΂̋ʃI�u�W�F�N�g�̃R���X�g���N�^
//
// ---------------------------------------------------------------------------
CWeaponFireBallObj::CWeaponFireBallObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	const int nAtc = 500;  // �΂̋ʂ̍U����

	m_bActive = FALSE;
	m_dwStatus = NORMAL;


	m_nAtc = nAtc;

	m_dwOwner = 0;

}
// ---------------------------------------------------------------------------
//
// ����E�΂̋ʃI�u�W�F�N�g�̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CWeaponFireBallObj::~CWeaponFireBallObj()
{
	;
}

// ---------------------------------------------------------------------------
//
// ����E�΂̋ʃI�u�W�F�N�g�̔���
//
//     VECTOR3 vStart       �F�΂̋ʂ̔��ˈʒu
//     VECTOR3 vTarget      �F�΂̋ʂ̃^�[�Q�b�g
//     DWORD       dwOwner      �F����𔭎˂����L�����敪�iPC:PC(�ȗ��l)�@ENM:�G�j
//
//     �߂�l�@�@�Ȃ�
// ---------------------------------------------------------------------------
BOOL CWeaponFireBallObj::Start(VECTOR3 vStart, VECTOR3 vTarget, DWORD dwOwner)
{
	const float fSpeed = 0.5f;		// �΂̋ʂ̑���
	const int nLifeTime = 80;		// �΂̋ʂ̎�������

	VECTOR3 vError, vError2;

	if (m_bActive) return FALSE;

	m_bActive = TRUE;

	// �^�[�Q�b�g�ʒu�ψʂ𗐐��Ō���
	vError.x = Random(-10, 10) / 10.0f;
	vError.y = Random(-5, 5)   / 10.0f;
	vError.z = Random(-10, 10) / 10.0f;

	// ���ˈʒu�ψʂ𗐐��Ō���
	vError2.x = Random(-5, 5) / 10.0f;
	vError2.y = Random(-5, 5) / 10.0f;
	vError2.z = Random(-5, 5) / 10.0f;

	vStart += vError2;
	vTarget += vError;

	m_mWorld = GetLookatMatrix(vStart, vTarget);
	m_mWorldOld = m_mWorld;

	m_vPosUp = VECTOR3(0, 0, fSpeed);

	m_nCnt1 = nLifeTime;

	m_dwOwner = dwOwner;

	// �΂̋ʂ��͂މ��̃X�^�[�g
	for (DWORD i = 0; i < FIREBALL_FIRE_MAX; i++)
	{
		m_pBillFire[i] = m_pGMain->m_pEffectProc->m_pBillFireProc->Start();
		if (m_pBillFire[i])
		{
			// ���ˈʒu�ψʂƐi�s�����𗐐��Ō���
			vError.x = Random(-3, 3) / 10.0f;
			vError.y = Random(-3, 3) / 10.0f;
			vError.z = Random(-3, 3) / 10.0f;
			m_pBillFire[i]->m_vPos = vStart + vError;
			m_pBillFire[i]->SetPosUp(vError);
		}
	}

	return TRUE;
}

// ---------------------------------------------------------------------------
//
// ����E�΂̋ʃI�u�W�F�N�g�̍X�V
//
//     �����@�@�@�Ȃ�
//     �߂�l�@�@�Ȃ�
// ---------------------------------------------------------------------------
void CWeaponFireBallObj::Update()
{

	if (m_bActive)
	{
		m_mWorldOld = m_mWorld;

		MATRIX4X4 mTran;
		mTran = XMMatrixTranslation(m_vPosUp.x, m_vPosUp.y, m_vPosUp.z);
		m_mWorld = mTran * m_mWorld;

		// �G��o�b�Ƃ̂����蔻��
		if ((m_dwOwner != ENM && m_pGMain->m_pEnmProc->Hitcheck(this, GetPositionVector(m_mWorld), GetPositionVector(m_mWorldOld))) ||
			(m_dwOwner != PC  && m_pGMain->m_pPcProc->Hitcheck(this, GetPositionVector(m_mWorld), GetPositionVector(m_mWorldOld))))
		{
			//m_pGMain->m_pEffectProc->m_pParticleProc->Start(m_vHitPos, m_vHitNormal);	// �p�[�e�B�N���̔���
			//m_pGMain->m_pEffectProc->m_pBillProc->Start(m_vHitPos);	// �����r���{�[�h�̔���
			m_bActive = FALSE;
			for (DWORD i = 0; i < FIREBALL_FIRE_MAX; i++)
			{
				if (m_pBillFire[i]) m_pBillFire[i]->SetActive(FALSE);
			}
		}
		else {
			// �}�b�v�Ƃ̂����蔻��
			VECTOR3 vHit, vNormal;
			if (m_pGMain->m_pMapProc->Hitcheck(GetPositionVector(m_mWorld), GetPositionVector(m_mWorldOld), &vHit, &vNormal))
			{
				//m_pGMain->m_pEffectProc->m_pParticleProc->Start(vHit, vNormal);	// �p�[�e�B�N���̔���
				//m_pGMain->m_pEffectProc->m_pBillProc->Start(vHit);	// �����r���{�[�h�̔���
				m_bActive = FALSE;
				for (DWORD i = 0; i < FIREBALL_FIRE_MAX; i++)
				{
					if (m_pBillFire[i]) m_pBillFire[i]->SetActive(FALSE);
				}
			}
		}

		m_nCnt1--;
		if (m_nCnt1 <= 0)
		{
			m_bActive = FALSE;
			for (DWORD i = 0; i < FIREBALL_FIRE_MAX; i++)
			{
				if (m_pBillFire[i]) m_pBillFire[i]->SetActive(FALSE);
			}
		}

		// �����_�����O
		Render();

		// �΂̋ʂ��͂މ��̍X�V
		for (DWORD i = 0; i < FIREBALL_FIRE_MAX; i++)
		{
			if (m_pBillFire[i]) m_pBillFire[i]->m_vPos = GetPositionVector(m_mWorld) + m_pBillFire[i]->GetPosUp();
		}
	}

}

// ---------------------------------------------------------------------------
//
// ����E�΂̋ʃI�u�W�F�N�g�̃����_�����O
//
//   �A�e�����Ȃ������_�����O�@���̕�����(0,0,0)
//
//     �����@�@�@�Ȃ�
//     �߂�l�@�@�Ȃ�
// ---------------------------------------------------------------------------
void CWeaponFireBallObj::Render()
{
	int shineFlag = 0;
	// �΂̋ʂ̃����_�����O
	m_pMesh->Render(m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, VECTOR3(0, 0, 0), m_pGMain->m_vEyePt, shineFlag);
}


// ===================================================================================
//============================================================================
//
// ����E���v���V�[�W���̃R���X�g���N�^
//
//   �Ȃ��A�I�u�W�F�N�g��delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
// ---------------------------------------------------------------------------
CWeaponSwordProc::CWeaponSwordProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	m_pObjArray.push_back(new CWeaponSwordObj(m_pGMain));	// ����E���I�u�W�F�N�g
}

// ---------------------------------------------------------------------------
//
// ���팕�E�v���V�[�W���̔���
//
// ---------------------------------------------------------------------------

BOOL CWeaponSwordProc::Start(MATRIX4X4 mMat, VECTOR3 vMin, VECTOR3 vMax, DWORD dwOwner)
{
	m_pObjArray[0]->Start(mMat, vMin, vMax, dwOwner);	// ����E���I�u�W�F�N�g

	return TRUE;
}


//============================================================================
//
// ����E���I�u�W�F�N�g�̃R���X�g���N�^
//
// ---------------------------------------------------------------------------
CWeaponSwordObj::CWeaponSwordObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	const int nAtc = 300;    // ���̍U����

	m_bActive = FALSE;
	m_dwStatus = NORMAL;

	// BBox�̐ݒ�(�傫���́A���ɐݒ�)
	m_pBBox = new CBBox(m_pGMain->m_pShader, VECTOR3(-0.1f, -0.1f, -0.1f), VECTOR3(0.1f, 0.1f, 0.1f));
	m_nAtc = nAtc;
	m_dwOwner = 0;
}
// ---------------------------------------------------------------------------
//
// ����E���I�u�W�F�N�g�̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CWeaponSwordObj::~CWeaponSwordObj()
{
	;
}
// ---------------------------------------------------------------------------
//
// ����E���I�u�W�F�N�g�̔����Ə����A�`��
//
//     MATRIX4X4  mMat        �F���̈ʒu
//     VECTOR3 vMin        �F�o�E���f�B���O�{�b�N�X�̍ŏ��l
//     VECTOR3 vMax        �F�o�E���f�B���O�{�b�N�X�̍ő�l
//     DWORD       dwOwner     �F����𔭎˂����L�����敪�iPC:PC(�ȗ��l)�@ENM:�G�j
//
//     �߂�l�@�@�Ȃ�
// ---------------------------------------------------------------------------
BOOL CWeaponSwordObj::Start(MATRIX4X4 mMat, VECTOR3 vMin, VECTOR3 vMax, DWORD dwOwner)
{
	m_bActive = TRUE;  // �X�^�[�g���ɕ\���J�n

	// �o�E���f�B���O�{�b�N�X�̃T�C�Y���ς���Ă�������ւ���
	if (m_pBBox->m_vMin.x != vMin.x || m_pBBox->m_vMin.y != vMin.y || m_pBBox->m_vMin.z != vMin.z
		||
		m_pBBox->m_vMax.x != vMax.x || m_pBBox->m_vMax.y != vMax.y || m_pBBox->m_vMax.z != vMax.z)
	{
		m_pBBox->InitBBox(vMin, vMax);   // �o�E���f�B���O�{�b�N�X�̑傫���ύX
	}
	m_pBBox->m_mWorld = mMat;   // �o�E���f�B���O�{�b�N�X�̃��[���h�}�g���b�N�X���Z�b�g

	m_dwOwner = dwOwner;

	// �G��o�b�Ƃ̂����蔻��
	if ((dwOwner != ENM  && m_pGMain->m_pEnmProc->Hitcheck(this, m_pBBox)) ||
		(dwOwner != PC   && m_pGMain->m_pPcProc->Hitcheck(this, m_pBBox)))
	{
		// �q�b�g�����Ƃ�
		m_pGMain->m_pEffectProc->m_pParticleProc->Start(m_vHitPos, m_vHitNormal);	// �p�[�e�B�N���̔���
		//m_pGMain->m_pEffectProc->m_pBillProc->Start(m_vHitPos);	// �����r���{�[�h�̔���
	}

	// �o�E���f�B���O�{�b�N�X�̃����_�����O
	Render();

	m_bActive = FALSE;  // �P�񏈗�������A����

	return TRUE;
}
// ---------------------------------------------------------------------------
//
// ����E���I�u�W�F�N�g�̍X�V
//
//     �����@�@�@�Ȃ�
//     �߂�l�@�@�Ȃ�
// ---------------------------------------------------------------------------
void CWeaponSwordObj::Update()
{
	;
}

// ---------------------------------------------------------------------------
//
// ����E���I�u�W�F�N�g�̃����_�����O
// (�o�E���f�B���O�{�b�N�X�̃����_�����O)
//
//     �����@�@�@�Ȃ�
//     �߂�l�@�@�Ȃ�
// ---------------------------------------------------------------------------
void CWeaponSwordObj::Render()
{

	//   �o�E���f�B���O�{�b�N�X�����_�����O
	//m_pBBox->Render(m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);

}

// ================================================================================================================================
//============================================================================
//
// ����E�Ή��v���V�[�W���̃R���X�g���N�^
//
//   �Ȃ��A�I�u�W�F�N�g��delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
// ---------------------------------------------------------------------------
CWeaponFlameProc::CWeaponFlameProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	// �Ή����b�V���̐ݒ�
	//m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Item/FireBall2.mesh"));

	for (int i = 0; i < FLAME_MAX; i++)
	{
		m_pObjArray.push_back(new CWeaponFlameObj(m_pGMain));	// m_pObjArray�ɕ���E�Ή��I�u�W�F�N�g�𐶐�����
		((CWeaponFlameObj*)m_pObjArray[i])->SetMesh(m_pMesh);  // ���b�V���̃A�h���X���I�u�W�F�N�g�ɐݒ肷��
	}
}
//============================================================================
//
// ����E�Ή��v���V�[�W���̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CWeaponFlameProc::~CWeaponFlameProc()
{
	SAFE_DELETE(m_pMesh);
}
// ---------------------------------------------------------------------------
//
// ����E�Ή��v���V�[�W���̔���
//
//  VECTOR3 vStart       �F���ˈʒu
//  VECTOR3 vTarget      �F�ڕW�ʒu
//  DWORD       dwOwner      �F����𔭎˂����L�����敪�iPC:PC(�ȗ��l)�@ENM:�G�j
//
// ---------------------------------------------------------------------------
BOOL CWeaponFlameProc::Start(VECTOR3 vStart, VECTOR3 vTarget, DWORD dwOwner)
{
	const int nNum = 5;   // �Ή��̐�

	int n = nNum;
	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			m_pObjArray[i]->Start(vStart, vTarget, dwOwner);	// ����E�Ή��I�u�W�F�N�g
			n--;
			if (n > 0) continue;
			return TRUE;
		}
	}
	return FALSE;
}

//============================================================================
//
// ����E�Ή��I�u�W�F�N�g�̃R���X�g���N�^
//
// ---------------------------------------------------------------------------
CWeaponFlameObj::CWeaponFlameObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	const int nAtc = 500;  // �U����

	m_bActive = FALSE;
	m_dwStatus = NORMAL;
	m_nAtc = nAtc;
	m_dwOwner = 0;

}
// ---------------------------------------------------------------------------
//
// ����E�Ή��I�u�W�F�N�g�̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CWeaponFlameObj::~CWeaponFlameObj()
{
	;
}

// ---------------------------------------------------------------------------
//
// ����E�Ή��I�u�W�F�N�g�̔���
//
//     VECTOR3 vStart       �F�Ή��̔��ˈʒu
//     VECTOR3 vTarget      �F�Ή��̃^�[�Q�b�g
//     DWORD   dwOwner      �F����𔭎˂����L�����敪�iPC:PC(�ȗ��l)�@ENM:�G�j
//
//     �߂�l�@�@�Ȃ�
// ---------------------------------------------------------------------------
BOOL CWeaponFlameObj::Start(VECTOR3 vStart, VECTOR3 vTarget, DWORD dwOwner)
{
	const float fSpeed = 1.0f;		// �Ή��̑���
	const int nLifeTime = 80;		// �΂̋ʂ̎�������
	VECTOR3 vError, vError2;

	if (m_bActive) return FALSE;

	m_bActive = TRUE;

	// �^�[�Q�b�g�ʒu�ψʂ𗐐��Ō���
	vError.x = Random(-10, 10) / 10.0f;
	vError.y = Random(-5, 5) / 10.0f;
	vError.z = Random(-10, 10) / 10.0f;

	// ���ˈʒu�ψʂ𗐐��Ō���
	vError2.x = Random(-5, 5) / 10.0f;
	vError2.y = Random(-5, 5) / 10.0f;
	vError2.z = Random(-5, 5) / 10.0f;

	vStart += vError2;
	vTarget += vError;

	m_mWorld = GetLookatMatrix(vStart, vTarget);
	m_mWorldOld = m_mWorld;

	m_vPosUp = VECTOR3(0, 0, fSpeed);

	m_nCnt1 = nLifeTime;

	m_dwOwner = dwOwner;

	// �Ή����͂މ��̃X�^�[�g
	for (DWORD i = 0; i < FLAME_FIRE_MAX; i++)
	{
		m_pBillFire[i] = m_pGMain->m_pEffectProc->m_pBillFireProc->Start();
		if (m_pBillFire[i])
		{
			vError.x = Random(-3, 3) / 10.0f;
			vError.y = Random(-3, 3) / 10.0f;
			vError.z = Random(-3, 3) / 10.0f;
			m_pBillFire[i]->m_vPos = vStart + vError;
			m_pBillFire[i]->SetPosUp(vError);
		}
	}

	return TRUE;
}

// ---------------------------------------------------------------------------
//
// ����E�Ή��I�u�W�F�N�g�̍X�V
//
//     �����@�@�@�Ȃ�
//     �߂�l�@�@�Ȃ�
// ---------------------------------------------------------------------------
void CWeaponFlameObj::Update()
{

	if (m_bActive)
	{
		m_mWorldOld = m_mWorld;

		MATRIX4X4 mTran;
		mTran = XMMatrixTranslation(m_vPosUp.x, m_vPosUp.y, m_vPosUp.z);
		m_mWorld = mTran * m_mWorld;

		// �G��o�b�Ƃ̂����蔻��
		if ((m_dwOwner != ENM && m_pGMain->m_pEnmProc->Hitcheck(this, GetPositionVector(m_mWorld), GetPositionVector(m_mWorldOld))) ||
			(m_dwOwner != PC  && m_pGMain->m_pPcProc->Hitcheck(this, GetPositionVector(m_mWorld), GetPositionVector(m_mWorldOld))))
		{
			//m_pGMain->m_pEffectProc->m_pBillProc->Start(m_vHitPos);	// �����r���{�[�h�̔���
			m_bActive = FALSE;
			for (DWORD i = 0; i < FLAME_MAX; i++)
			{
				if (m_pBillFire[i]) m_pBillFire[i]->SetActive(FALSE);
			}
		}
		else {
			// �}�b�v�Ƃ̂����蔻��
			VECTOR3 vHit, vNormal;
			if (m_pGMain->m_pMapProc->Hitcheck(GetPositionVector(m_mWorld), GetPositionVector(m_mWorldOld), &vHit, &vNormal))
			{
				//m_pGMain->m_pEffectProc->m_pBillProc->Start(vHit);	// �����r���{�[�h�̔���
				m_bActive = FALSE;
				for (DWORD i = 0; i < FLAME_MAX; i++)
				{
					if (m_pBillFire[i]) m_pBillFire[i]->SetActive(FALSE);
				}
			}
		}

		m_nCnt1--;
		if (m_nCnt1 <= 0)
		{
			m_bActive = FALSE;
			for (DWORD i = 0; i < FLAME_MAX; i++)
			{
				if (m_pBillFire[i]) m_pBillFire[i]->SetActive(FALSE);
			}
		}

		// �����_�����O
		Render();

		// �Ή����͂މ��̍X�V
		for (DWORD i = 0; i < FLAME_MAX; i++)
		{
			if (m_pBillFire[i]) m_pBillFire[i]->m_vPos = GetPositionVector(m_mWorld) + m_pBillFire[i]->GetPosUp();
		}
	}

}

// ---------------------------------------------------------------------------
//
// ����E�Ή��I�u�W�F�N�g�̃����_�����O
//
//   �A�e�����Ȃ������_�����O�@���̕�����(0,0,0)
//
//     �����@�@�@�Ȃ�
//     �߂�l�@�@�Ȃ�
// ---------------------------------------------------------------------------
void CWeaponFlameObj::Render()
{
	int shineFlag = 0;
	// �Ή��̃����_�����O
	m_pMesh->Render(m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, VECTOR3(0, 0, 0), m_pGMain->m_vEyePt,shineFlag);
}



// ================================================================================================================================
//============================================================================
//
// ����E�{�[���v���V�[�W���̃R���X�g���N�^
//
//   �Ȃ��A�I�u�W�F�N�g��delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
// ---------------------------------------------------------------------------
CWeaponBallProc::CWeaponBallProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	// �{�[�����b�V���̐ݒ�
	//m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Item/Mark.mesh"));

	for (int i = 0; i < BALL_MAX; i++)
	{
		m_pObjArray.push_back(new CWeaponBallObj(m_pGMain));	// m_pObjArray�ɕ���E�{�[���I�u�W�F�N�g�𐶐�����
		((CWeaponBallObj*)m_pObjArray[i])->SetMesh(m_pMesh);  // ���b�V���̃A�h���X���I�u�W�F�N�g�ɐݒ肷��
	}
}
//============================================================================
//
// ����E�{�[���v���V�[�W���̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CWeaponBallProc::~CWeaponBallProc()
{
	SAFE_DELETE(m_pMesh);
}
// ---------------------------------------------------------------------------
//
// ����E�{�[���v���V�[�W���̔���
//
//  MATRIX4X4  mGun         �F�e�̈ʒu�}�g���b�N�X
//  VECTOR3    vOffset      �F�ʒu�̔�����
//  MATRIX4X4  mOwnerWorld  �F���˂���L�����̃}�g���b�N�X
//  DWORD      dwOwner      �F����𔭎˂����L�����敪�iPC:PC(�ȗ��l)�@ENM:�G�j
//
// ---------------------------------------------------------------------------
BOOL CWeaponBallProc::Start(MATRIX4X4 mGun, VECTOR3 vOffset, MATRIX4X4 mOwnerWorld, DWORD dwOwner)
{
	MATRIX4X4 mLay, mOwnerRot, mOffset;

	mLay = GetPositionMatrix(mGun);               // �e�̈ʒu(��]����菜��)
	mOwnerRot = GetRotateMatrix(mOwnerWorld);     // ���˂���L�����̉�]�}�g���b�N�X�̂�(�ʒu����菜��)�ɂ���
	mLay = mOwnerRot * mLay;                      // �e�̈ʒu����A�L�����̕����Ŕ��˂���}�g���b�N�X�����
	mOffset = XMMatrixTranslation(vOffset.x, vOffset.y, vOffset.z);	// �ʒu�̔�����
	mLay = mOffset * mLay;

	for (int i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			m_pObjArray[i]->Start(mLay, dwOwner);	       // ����E�{�[���I�u�W�F�N�g�̔���
			return TRUE;
		}
	}
	return FALSE;
}

//============================================================================
//
// ����E�{�[���I�u�W�F�N�g�̃R���X�g���N�^
//
// ---------------------------------------------------------------------------
CWeaponBallObj::CWeaponBallObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	const int nAtc = 100;  // �U����

	m_bActive = FALSE;
	m_dwStatus = NORMAL;
	m_nAtc = nAtc;
	m_dwOwner = 0;

}
// ---------------------------------------------------------------------------
//
// ����E�{�[���I�u�W�F�N�g�̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CWeaponBallObj::~CWeaponBallObj()
{
	;
}

// ---------------------------------------------------------------------------
//
// ����E�{�[���I�u�W�F�N�g�̔���
//
//     MATRIX4X4 mStartWorld     �{�[���̔��ˈʒu�̃}�g���b�N�X
//     DWORD      dwOwner        ����𔭎˂����L�����敪�iPC:PC(�ȗ��l)�@ENM:�G�j
//
//     �߂�l�@�@�Ȃ�
// ---------------------------------------------------------------------------
BOOL CWeaponBallObj::Start(MATRIX4X4 mStartWorld, DWORD dwOwner)
{
	const float fSpeed = 0.7f;		// �{�[���̑���
	const int nLifeTime = 150;		// �{�[���̎�������

	if (m_bActive) return FALSE;

	m_bActive = TRUE;
	m_mWorld    = mStartWorld;
	m_mWorldOld = mStartWorld;

	m_vPosUp  = VECTOR3(0, 0, fSpeed);
	m_nCnt1   = nLifeTime;
	m_dwOwner = dwOwner;

	return TRUE;
}

// ---------------------------------------------------------------------------
//
// ����E�{�[���I�u�W�F�N�g�̍X�V
//
//     �����@�@�@�Ȃ�
//     �߂�l�@�@�Ȃ�
// ---------------------------------------------------------------------------
void CWeaponBallObj::Update()
{

	if (m_bActive)
	{
		m_mWorldOld = m_mWorld;

		MATRIX4X4 mTran;
		mTran = XMMatrixTranslation(m_vPosUp.x, m_vPosUp.y, m_vPosUp.z);
		m_mWorld = mTran * m_mWorld;

		// �G��o�b�Ƃ̂����蔻��
		if ((m_dwOwner != ENM && m_pGMain->m_pEnmProc->Hitcheck(this, GetPositionVector(m_mWorld), GetPositionVector(m_mWorldOld))) ||
			(m_dwOwner != PC  && m_pGMain->m_pPcProc->Hitcheck(this, GetPositionVector(m_mWorld), GetPositionVector(m_mWorldOld))))
		{
			m_pGMain->m_pEffectProc->m_pParticleProc->Start(m_vHitPos, m_vHitNormal);	// �p�[�e�B�N���̔���
			m_bActive = FALSE;
		}
		else {
			// �}�b�v�Ƃ̂����蔻��
			VECTOR3 vHit, vNormal;
			if (m_pGMain->m_pMapProc->Hitcheck(GetPositionVector(m_mWorld), GetPositionVector(m_mWorldOld), &vHit, &vNormal))
			{
				VECTOR3 vL = normalize(GetPositionVector(m_mWorld) - GetPositionVector(m_mWorldOld));  // �ړ��x�N�g���i���K���j
				VECTOR3 vN = normalize(vNormal);            // �ڐG�|���S���̖@���i���K���j
				VECTOR3 vR = (2 * dot(-vL, vN) * vN) + vL;  // ���˃x�N�g���̌���
				m_mWorldOld = m_mWorld = GetLookatMatrix(vHit, vHit+vR);  // �ڐG�_���甽�ː������}�g���b�N�X���쐬���A���[���h�}�g���b�N�X�ɑ��

				m_pGMain->m_pEffectProc->m_pParticleProc->Start(vHit, vNormal);	// �p�[�e�B�N���̔���
			}
		}

		m_nCnt1--;
		if (m_nCnt1 <= 0)
		{
			m_bActive = FALSE;
		}

		// �����_�����O
		Render();

	}
}

// ---------------------------------------------------------------------------
//
// ����E�{�[���I�u�W�F�N�g�̃����_�����O
//
//   �A�e�����Ȃ������_�����O�@���̕�����(0,0,0)
//
//     �����@�@�@�Ȃ�
//     �߂�l�@�@�Ȃ�
// ---------------------------------------------------------------------------
void CWeaponBallObj::Render()
{
	int shineFlag = 0;
	// �{�[���̃����_�����O
	m_pMesh->Render(m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt, shineFlag);
}


// ================================================================================================================================
//============================================================================
//
// ����E�X�v���[�v���V�[�W���̃R���X�g���N�^
//
//   �Ȃ��A�I�u�W�F�N�g��delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
// ---------------------------------------------------------------------------
CWeaponSprayProc::CWeaponSprayProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	// �X�v���C�g�C���[�W�̓ǂݍ���
	m_pImage = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/spray.png"));

	for (int i = 0; i < SPRAY_MAX; i++)
	{
		m_pObjArray.push_back(new CWeaponSprayObj(m_pGMain));	// m_pObjArray�ɕ���E�X�v���[�I�u�W�F�N�g�𐶐�����
		((CWeaponSprayObj*)m_pObjArray[i])->CreateSprite(m_pImage);  // �X�v���C�g���I�u�W�F�N�g�ɐݒ肷��
		m_pObjArray[i]->SetObjNo(i);
	}
}
//============================================================================
//
// ����E�X�v���[�v���V�[�W���̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CWeaponSprayProc::~CWeaponSprayProc()
{
	SAFE_DELETE(m_pImage);
}
// ---------------------------------------------------------------------------
//
// ����E�X�v���[�v���V�[�W���̔���
//
//  MATRIX4X4  mGun         �F�e�̈ʒu�}�g���b�N�X�B�}�g���b�N�X�̈ʒu�̂ݎg�p����
//  VECTOR3    vOffset      �F�ʒu�̔�����
//  MATRIX4X4  mOwnerWorld  �F���˂���L�����̃}�g���b�N�X�B�}�g���b�N�X�̊p�x�̂ݎg�p����
//  DWORD      dwOwner      �F����𔭎˂����L�����敪�iPC:PC(�ȗ��l)�@ENM:�G�j
//
// ---------------------------------------------------------------------------
BOOL CWeaponSprayProc::Start(MATRIX4X4 mGun, VECTOR3 vOffset, MATRIX4X4 mOwnerWorld, DWORD dwOwner)
{
	MATRIX4X4 mLay, mOwnerRot, mOffset;
	const int nStartMax = 30;   // ��x�ɉ����˂����邩

	mLay = GetPositionMatrix(mGun);               // �e�̈ʒu(��]����菜��)
	mOwnerRot = GetRotateMatrix(mOwnerWorld);     // ���˂���L�����̉�]�}�g���b�N�X�̂�(�ʒu����菜��)�ɂ���
	mLay = mOwnerRot * mLay;                      // �e�̈ʒu����A�L�����̕����Ŕ��˂���}�g���b�N�X�����
	mOffset = XMMatrixTranslation(vOffset.x, vOffset.y, vOffset.z);	// �ʒu�̔�����
	mLay = mOffset * mLay;

	for (int n = nStartMax, i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			m_pObjArray[i]->Start(mLay, dwOwner);	       // ����E�X�v���[�I�u�W�F�N�g�̔���
			n--;
			if (n<0)	return TRUE;
		}
	}
	return FALSE;
}

//============================================================================
//
// ����E�X�v���[�I�u�W�F�N�g�̃R���X�g���N�^
//
// ---------------------------------------------------------------------------
CWeaponSprayObj::CWeaponSprayObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	const int nAtc = 30;  // �U����

	m_bActive = FALSE;
	m_dwStatus = NORMAL;
	m_nAtc = nAtc;
	m_dwOwner = 0;

}
// ---------------------------------------------------------------------------
//
// ����E�X�v���[�I�u�W�F�N�g�̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CWeaponSprayObj::~CWeaponSprayObj()
{
	SAFE_DELETE(m_pSprite);
}

// ---------------------------------------------------------------------------
//
// ����E�X�v���[  �X�v���C�g�̐ݒ�
//
// ---------------------------------------------------------------------------
void CWeaponSprayObj::CreateSprite(CSpriteImage*  pImage)
{
	m_pSprite = new CSprite(pImage);

	// �X�v���[�̉�
	// (�\���T�C�Ywidth,Height    �X�v���C�g�ʒux,y   �X�v���C�g�T�C�Ywidth,Height)
	m_pSprite->SetSrc3D(0.5f, 0.5f, Random(0, 2) * 85, 0, 85, 85);

	//m_pSprite->m_nBlend = 2;  // ���Z�����̎w��

}

// ---------------------------------------------------------------------------
//
// ����E�X�v���[�I�u�W�F�N�g�̔���
//
//     MATRIX4X4 mStartWorld     �X�v���[�̔��ˈʒu�̃}�g���b�N�X
//     DWORD      dwOwner        ����𔭎˂����L�����敪�iPC:PC(�ȗ��l)�@ENM:�G�j
//
//     �߂�l�@�@�Ȃ�
// ---------------------------------------------------------------------------
BOOL CWeaponSprayObj::Start(MATRIX4X4 mStartWorld, DWORD dwOwner)
{
	const float fSpeed = 1.5f;		// �X�v���[�̑���
	const int nLifeTime = 10;		// �X�v���[�̎�������
	const float fRotMax = 3.0f;		// �X�v���[�̍L����p�x

	float fRotX = 0.0f, fRotY = 0.0f;

	if (m_bActive) return FALSE;

	m_bActive = TRUE;

	// ���˕������㉺���E�Ƀu������
	fRotX = (Random(0, 100) - 50) / 50.0f * fRotMax;
	fRotY = (Random(0, 100) - 50) / 50.0f * fRotMax;

	mStartWorld = XMMatrixRotationX(XMConvertToRadians(fRotX)) * XMMatrixRotationY(XMConvertToRadians(fRotY)) * mStartWorld;

	m_mWorld = mStartWorld;
	m_mWorldOld = mStartWorld;

	// ���ˑ��x�������_����
	float fSp = fSpeed * 0.7f + Random(0, 50) / 50.0f * fSpeed;

	m_vPosUp = VECTOR3(0, 0, fSp);
	m_nCnt1 = nLifeTime;
	m_dwOwner = dwOwner;

	return TRUE;
}

// ---------------------------------------------------------------------------
//
// ����E�X�v���[�I�u�W�F�N�g�̍X�V
//
//     �����@�@�@�Ȃ�
//     �߂�l�@�@�Ȃ�
// ---------------------------------------------------------------------------
void CWeaponSprayObj::Update()
{

	if (m_bActive)
	{
		m_mWorldOld = m_mWorld;

		MATRIX4X4 mTran;
		mTran = XMMatrixTranslation(m_vPosUp.x, m_vPosUp.y, m_vPosUp.z);
		m_mWorld = mTran * m_mWorld;

		// �G��o�b�Ƃ̂����蔻��
		if ((m_dwOwner != ENM && m_pGMain->m_pEnmProc->Hitcheck(this, GetPositionVector(m_mWorld), GetPositionVector(m_mWorldOld))) ||
			(m_dwOwner != PC  && m_pGMain->m_pPcProc->Hitcheck(this, GetPositionVector(m_mWorld), GetPositionVector(m_mWorldOld))))
		{
			m_pGMain->m_pEffectProc->m_pParticleProc->Start(m_vHitPos, m_vHitNormal);	// �p�[�e�B�N���̔���
			m_bActive = FALSE;
		}
		else {
			// �}�b�v�Ƃ̂����蔻��
			VECTOR3 vHit, vNormal;
			if (m_pGMain->m_pMapProc->Hitcheck(GetPositionVector(m_mWorld), GetPositionVector(m_mWorldOld), &vHit, &vNormal))
			{
				//m_pGMain->m_pEffectProc->m_pParticleProc->Start(vHit, vNormal);	// �p�[�e�B�N���̔���
				//m_pGMain->m_pSeDead->Play();// �������ʉ�
				m_bActive = FALSE;
			}
		}

		m_nCnt1--;
		if (m_nCnt1 <= 0)
		{
			m_bActive = FALSE;
		}

		// �����_�����O
		Render();

	}
}

// ---------------------------------------------------------------------------
//
// ����E�X�v���[�I�u�W�F�N�g�̃����_�����O
//
//
//     �����@�@�@�Ȃ�
//     �߂�l�@�@�Ȃ�
// ---------------------------------------------------------------------------
void CWeaponSprayObj::Render()
{

	// �X�v���[�̕`��
	m_pSprite->Draw3D(GetPositionVector(m_mWorld), m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vEyePt);


}


// ============================================================================================================================
//============================================================================
//
// ����E��Ɏ��A�C�e���v���V�[�W���̃R���X�g���N�^
//
// �E���ڍU�����镐��ł͂Ȃ��A�����\��������A�ʒu����Ԃ����肷��
//
//   ���b�V���̓v���V�[�W���ł͂Ȃ��A�I�u�W�F�N�g�œǂݍ���
//   �Ȃ��A�I�u�W�F�N�g��delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
// ---------------------------------------------------------------------------
CWeaponHoldProc::CWeaponHoldProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	for (int i = 0; i < HOLDITEM_MAX; i++)
	{
		m_pObjArray.push_back(new CWeaponHoldObj(m_pGMain));	// m_pObjArray�ɃI�u�W�F�N�g�𐶐�����
		m_pObjArray[i]->SetObjNo(i);    // �I�u�W�F�N�g�m�n���I�u�W�F�N�g�ɐݒ肷��
		((CWeaponHoldObj*)m_pObjArray[i])->Init();   // �I�u�W�F�N�g�̏�����
	}
}
// ---------------------------------------------------------------------------
//
// ����E��Ɏ��A�C�e���v���V�[�W���̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CWeaponHoldProc::~CWeaponHoldProc()
{
	;
}

// ---------------------------------------------------------------------------
//
// ����E��Ɏ��A�C�e���v���V�[�W���̏��𓾂�
//
//     MATRIX4X4  mHold       �F���̈ʒu
//     BASEHOLDITEM HoldItem  :��Ɏ�����̏��
//     MATRIX4X4& mMat        :��Ɏ�����̃}�g���b�N�X(Out)
//     VECTOR3& vMin          :�o�E���f�B���O�{�b�N�X��Min(Out)
//     VECTOR3& vMax          :�o�E���f�B���O�{�b�N�X��Max(Out)
//
//     �߂�l�@�@�Ȃ�
// ---------------------------------------------------------------------------
void  CWeaponHoldProc::GetInfo(MATRIX4X4 mHold, BASEHOLDITEM HoldItem, MATRIX4X4& mMat, VECTOR3& vMin, VECTOR3& vMax)
{
	((CWeaponHoldObj*)m_pObjArray[HoldItem.m_nHoldObjNo])->GetInfo(mHold, HoldItem, mMat, vMin, vMax);	// ����E���I�u�W�F�N�g

	return;
}
// ---------------------------------------------------------------------------
//
// ����E��Ɏ��A�C�e���v���V�[�W���̏��𓾂�
//
//     MATRIX4X4  mHold       �F���̈ʒu
//     BASEHOLDITEM HoldItem  :��Ɏ�����̏��
//     MATRIX4X4& mMat        :��Ɏ�����̃}�g���b�N�X(Out)
//     VECTOR3& vOffset       :�e���܂ł̃I�t�Z�b�g(Out)
//
//     �߂�l�@�@�Ȃ�
// ---------------------------------------------------------------------------
void  CWeaponHoldProc::GetInfo(MATRIX4X4 mHold, BASEHOLDITEM HoldItem, MATRIX4X4& mMat, VECTOR3& vOffset)
{
	((CWeaponHoldObj*)m_pObjArray[HoldItem.m_nHoldObjNo])->GetInfo(mHold, HoldItem, mMat, vOffset);	// ����E�e�I�u�W�F�N�g

	return;
}

// ---------------------------------------------------------------------------
//
// ����E��Ɏ��A�C�e���v���V�[�W���̃o�E���f�B���O�{�b�N�X�𓾂�
//
//     MATRIX4X4  mHold       �F���̈ʒu
//     BASEHOLDITEM HoldItem  :��Ɏ�����̏��
//
//     �߂�l�@�@CBBox* �o�E���f�B���O�{�b�N�X
// ---------------------------------------------------------------------------
CBBox*  CWeaponHoldProc::GetBBox(MATRIX4X4 mHold, BASEHOLDITEM HoldItem)
{
	return ((CWeaponHoldObj*)m_pObjArray[HoldItem.m_nHoldObjNo])->GetBBox(mHold, HoldItem);	// ����E���I�u�W�F�N�g
}

// ---------------------------------------------------------------------------
//
// ����E��Ɏ��A�C�e���v���V�[�W���̕\��
//
//     MATRIX4X4  mHold       �F���̈ʒu
//     BASEHOLDITEM HoldItem  :��Ɏ�����̏��
//
//     �߂�l�@�@�Ȃ�
// ---------------------------------------------------------------------------
BOOL CWeaponHoldProc::Disp(MATRIX4X4 mHold, BASEHOLDITEM HoldItem)
{

	((CWeaponHoldObj*)m_pObjArray[HoldItem.m_nHoldObjNo])->Disp(mHold, HoldItem);	// ����E���I�u�W�F�N�g

	return TRUE;
}
//============================================================================
//
// ����E��Ɏ��A�C�e���I�u�W�F�N�g�̃R���X�g���N�^
//
// �E���ڍU�����镐��ł͂Ȃ��A�����\��������A�ʒu����Ԃ����肷��
//
// ---------------------------------------------------------------------------
CWeaponHoldObj::CWeaponHoldObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_nKindNo = 0;
	m_pMesh = NULL;
	m_vOffset = VECTOR3(0.0f, 0.0f, 0.0f);   // �I�t�Z�b�g�̐ݒ�
}
//============================================================================
//
// ����E��Ɏ��A�C�e���I�u�W�F�N�g�̏�����
//
// �E���b�V���́A�v���V�[�W���ł͂Ȃ��I�u�W�F�N�g�̒��ɐݒ肷��
//
// ---------------------------------------------------------------------------
void CWeaponHoldObj::Init()
{

	switch (m_dwObjNo)
	{
	case 0:     // ���ݒ�
		m_nKindNo = 0;
		m_pMesh = NULL; // �I�u�W�F�N�g�͖���
		m_pBBox = NULL; // BBox�̐ݒ�
		m_vOffset = VECTOR3(0.0f, 0.0f, 0.0f);   // �I�t�Z�b�g�Ȃ�

	case 1:     // �����Ȍ��̐ݒ�
		m_nKindNo = 1;  // 1:��ʁ@��
		m_pMesh = NULL; // �I�u�W�F�N�g�͖���
		m_pBBox = new CBBox(m_pGMain->m_pShader, VECTOR3(-0.15f, -0.15f, -0.15f), VECTOR3(0.15f, 1.8f, 0.15f));// BBox�̐ݒ�
		m_vOffset = VECTOR3(0.0f, 0.0f, 0.0f);   // �e���܂ł̃I�t�Z�b�g�̐ݒ�
		break;

	case 2:     // ���i���{���j���b�V���̐ݒ�
		m_nKindNo = 1;  // 1:��ʁ@��
		//m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Item/Sword.mesh"));
		m_pBBox = new CBBox(m_pGMain->m_pShader, VECTOR3(-0.15f, 0.1f, -0.15f), VECTOR3(0.15f, 1.8f, 0.15f));// BBox�̐ݒ�
		m_vOffset = VECTOR3(0.0f, 0.0f, 0.0f);   // �e���܂ł̃I�t�Z�b�g�̐ݒ�
		break;

	case 3:     // ���i�\�[�h�j���b�V���̐ݒ�
		m_nKindNo = 1;  // 1:��ʁ@��
		//m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Item/Sword2.mesh"));
		m_pBBox = new CBBox(m_pGMain->m_pShader, VECTOR3(-0.15f, 0.1f, -0.15f), VECTOR3(0.15f, 1.8f, 0.15f));// BBox�̐ݒ�
		m_vOffset = VECTOR3(0.0f, 0.0f, 0.0f);   // �e���܂ł̃I�t�Z�b�g�̐ݒ�
		break;

	case 4:     // �����ȏe�̐ݒ�
		m_nKindNo = 2;  // 2:��ʁ@�e
		m_pMesh = NULL; // �I�u�W�F�N�g�͖���
		m_vOffset = VECTOR3(0.0f, 0.0f, 0.51f);   // �e���܂ł̃I�t�Z�b�g�̐ݒ�
		break;

	case 5:     // �e�i���C�t���j���b�V���̐ݒ�
		m_nKindNo = 2;  // 2:��ʁ@�e
		//m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Item/Gun.mesh"));
		m_vOffset = VECTOR3(0.0f, 0.0f, 0.51f);   // �e���܂ł̃I�t�Z�b�g�̐ݒ�
		break;

	case 6:     // �e�i�s�X�g���j���b�V���̐ݒ�
		m_nKindNo = 2;  // 2:��ʁ@�e
		//m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Item/Pistol.mesh"));
		m_vOffset = VECTOR3(0.0f, 0.07f, 0.17f);   // �e���܂ł̃I�t�Z�b�g�̐ݒ�
		break;

	case 7:     // �����ȏ��̐ݒ�
		m_nKindNo = 1;  // 1:��ʁ@��
		m_pMesh = NULL; // �I�u�W�F�N�g�͖���
		m_pBBox = new CBBox(m_pGMain->m_pShader, VECTOR3(-1.0f, -1.5f, -0.3f), VECTOR3(1.0f, 1.5f, 0.3f));// BBox�̐ݒ�
		m_vOffset = VECTOR3(0.0f, 0.0f, 0.0f);   // �e���܂ł̃I�t�Z�b�g�̐ݒ�
		break;

	default:
		m_nKindNo = 0;
		m_pMesh = NULL; // �I�u�W�F�N�g�͖���
		m_pBBox = NULL; // BBox�̐ݒ�
		m_vOffset = VECTOR3(0.0f, 0.0f, 0.0f);   // �I�t�Z�b�g�Ȃ�
		break;
	}

	m_bActive = FALSE;
	m_dwStatus = NORMAL;

}
// ---------------------------------------------------------------------------
//
// ����E��Ɏ��A�C�e���I�u�W�F�N�g�̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CWeaponHoldObj::~CWeaponHoldObj()
{
	SAFE_DELETE(m_pMesh);
}

// ---------------------------------------------------------------------------
//
// ����E��Ɏ��A�C�e���I�u�W�F�N�g�̏��𓾂�
//
//     MATRIX4X4  mHold       �F���̈ʒu
//     BASEHOLDITEM HoldItem  :��Ɏ�����̏��
//     MATRIX4X4& mMat        :��Ɏ�����̃}�g���b�N�X(Out)
//     VECTOR3& vMin          :�o�E���f�B���O�{�b�N�X��Min(Out)
//     VECTOR3& vMax          :�o�E���f�B���O�{�b�N�X��Max(Out)
//
//     �߂�l�@�@�Ȃ�
// ---------------------------------------------------------------------------
void  CWeaponHoldObj::GetInfo(MATRIX4X4 mHold, BASEHOLDITEM HoldItem, MATRIX4X4& mMat, VECTOR3& vMin, VECTOR3& vMax)
{
	// �I�t�Z�b�g�}�g���b�N�X�̌v�Z
	MATRIX4X4 mPos = XMMatrixTranslation(HoldItem.m_nOffsetPos.x, HoldItem.m_nOffsetPos.y, HoldItem.m_nOffsetPos.z);

	MATRIX4X4 mRotX = XMMatrixRotationX(XMConvertToRadians(HoldItem.m_nOffsetRot.x));
	MATRIX4X4 mRotY = XMMatrixRotationY(XMConvertToRadians(HoldItem.m_nOffsetRot.y));
	MATRIX4X4 mRotZ = XMMatrixRotationZ(XMConvertToRadians(HoldItem.m_nOffsetRot.z));

	MATRIX4X4 mOffset = mRotY * mRotX * mRotZ;
	mOffset = mOffset * mPos;

	// 
	// ���[���h�}�g���b�N�X�̌v�Z
	// 
	// �A���A���̂Ƃ�m_mWorld��m_pBBox->m_mWorld�̐ݒ�͍s���Ă��Ȃ�!!
	// 
	mMat = mOffset * mHold;     // ���̈ʒu�̃��[���h�}�g���b�N�X

	vMin = m_pBBox->m_vMin;
	vMax = m_pBBox->m_vMax;

	return;
}

// ---------------------------------------------------------------------------
//
// ����E��Ɏ��A�C�e���I�u�W�F�N�g�̏��𓾂�
//
//     MATRIX4X4  mHold       �F�e�̈ʒu
//     BASEHOLDITEM HoldItem  :��Ɏ�����̏��
//     MATRIX4X4& mMat        :��Ɏ�����̃}�g���b�N�X(Out)
//     VECTOR3& vOffset       :�e���܂ł̃I�t�Z�b�g(Out)
//
//     �߂�l�@�@�Ȃ�
// ---------------------------------------------------------------------------
void  CWeaponHoldObj::GetInfo(MATRIX4X4 mHold, BASEHOLDITEM HoldItem, MATRIX4X4& mMat, VECTOR3& vOffset)
{
	// �I�t�Z�b�g�}�g���b�N�X�̌v�Z
	MATRIX4X4 mPos = XMMatrixTranslation(HoldItem.m_nOffsetPos.x, HoldItem.m_nOffsetPos.y, HoldItem.m_nOffsetPos.z);

	MATRIX4X4 mRotX = XMMatrixRotationX(XMConvertToRadians(HoldItem.m_nOffsetRot.x));
	MATRIX4X4 mRotY = XMMatrixRotationY(XMConvertToRadians(HoldItem.m_nOffsetRot.y));
	MATRIX4X4 mRotZ = XMMatrixRotationZ(XMConvertToRadians(HoldItem.m_nOffsetRot.z));

	MATRIX4X4 mOffset = mRotY * mRotX * mRotZ;
	mOffset = mOffset * mPos;

	// ���[���h�}�g���b�N�X�̌v�Z
	// 
	// �A���A���̂Ƃ�m_mWorld�̐ݒ�͍s���Ă��Ȃ�!!
	// 
	mMat = mOffset * mHold;     // �e�̈ʒu�̃��[���h�}�g���b�N�X

	vOffset = m_vOffset;

	return;
}

// ---------------------------------------------------------------------------
//
// ����E��Ɏ��A�C�e���I�u�W�F�N�g�̃o�E���f�B���O�{�b�N�X�𓾂�
//
//     MATRIX4X4  mHold       �F���̈ʒu
//     BASEHOLDITEM HoldItem  :��Ɏ�����̏��
//
//     �߂�l�@�@CBBox* �o�E���f�B���O�{�b�N�X
// ---------------------------------------------------------------------------
CBBox* CWeaponHoldObj::GetBBox(MATRIX4X4 mHold, BASEHOLDITEM HoldItem)
{

	// �I�t�Z�b�g�}�g���b�N�X�̌v�Z
	MATRIX4X4 mPos = XMMatrixTranslation(HoldItem.m_nOffsetPos.x, HoldItem.m_nOffsetPos.y, HoldItem.m_nOffsetPos.z);

	MATRIX4X4 mRotX = XMMatrixRotationX(XMConvertToRadians(HoldItem.m_nOffsetRot.x));
	MATRIX4X4 mRotY = XMMatrixRotationY(XMConvertToRadians(HoldItem.m_nOffsetRot.y));
	MATRIX4X4 mRotZ = XMMatrixRotationZ(XMConvertToRadians(HoldItem.m_nOffsetRot.z));

	MATRIX4X4 mOffset = mRotY * mRotX * mRotZ;
	mOffset = mOffset * mPos;

	// ���[���h�}�g���b�N�X�̌v�Z
	// 
	// �A���A���̂Ƃ�m_mWorld��m_pBBox->m_mWorld�̐ݒ���s���Ă���!!
	// 
	m_mWorld = mOffset * mHold;     // ���̈ʒu�̃��[���h�}�g���b�N�X
	m_pBBox->m_mWorld = m_mWorld;   // �o�E���f�B���O�{�b�N�X�̃��[���h�}�g���b�N�X���Z�b�g

	return m_pBBox;

}


// ---------------------------------------------------------------------------
//
// ����E��Ɏ��A�C�e���I�u�W�F�N�g�̕`��
//
//     MATRIX4X4  mHold        �F�A�C�e���̈ʒu
//     VECTOR3    vPos         :�ʒu�̃I�t�Z�b�g
//     VECTOR3    vRot         :�p�x�̃I�t�Z�b�g
//
//     �߂�l�@�@�Ȃ�
// ---------------------------------------------------------------------------
BOOL CWeaponHoldObj::Disp(MATRIX4X4 mHold, BASEHOLDITEM HoldItem)
{
	m_bActive = TRUE;  // �X�^�[�g���ɕ\���J�n

	// �I�t�Z�b�g�}�g���b�N�X�̌v�Z
	MATRIX4X4 mPos = XMMatrixTranslation(HoldItem.m_nOffsetPos.x, HoldItem.m_nOffsetPos.y, HoldItem.m_nOffsetPos.z);

	MATRIX4X4 mRotX = XMMatrixRotationX(XMConvertToRadians(HoldItem.m_nOffsetRot.x));
	MATRIX4X4 mRotY = XMMatrixRotationY(XMConvertToRadians(HoldItem.m_nOffsetRot.y));
	MATRIX4X4 mRotZ = XMMatrixRotationZ(XMConvertToRadians(HoldItem.m_nOffsetRot.z));

	MATRIX4X4 mOffset = mRotY * mRotX * mRotZ;
	mOffset = mOffset * mPos;

	// ���[���h�}�g���b�N�X�̌v�Z
	m_mWorld = mOffset * mHold;     // ���̈ʒu�̃��[���h�}�g���b�N�X
	if (m_pBBox) m_pBBox->m_mWorld = m_mWorld;   // �o�E���f�B���O�{�b�N�X�̃��[���h�}�g���b�N�X���Z�b�g

	// �����_�����O
	Render();

	m_bActive = FALSE;  // �P�񏈗�������A����

	return TRUE;
}

// ---------------------------------------------------------------------------
//
// ����E��Ɏ��A�C�e���I�u�W�F�N�g�̍X�V
//
//     �����@�@�@�Ȃ�
//     �߂�l�@�@�Ȃ�
// ---------------------------------------------------------------------------
void CWeaponHoldObj::Update()
{
	;
}
// ---------------------------------------------------------------------------
//
// ����E��Ɏ��A�C�e���I�u�W�F�N�g�̕`��
//
//     �����@�@�@�Ȃ�
//     �߂�l�@�@�Ȃ�
// ---------------------------------------------------------------------------
void CWeaponHoldObj::Render()
{
	int shineFlag = 0;
	// ��Ɏ��A�C�e���̃����_�����O
	if (m_pMesh) m_pMesh->Render(m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt, shineFlag);

	// �o�E���f�B���O�{�b�N�X�����_�����O
	//if (m_pBBox) m_pBBox->Render(m_pGMain->m_mView, m_pGMain->m_mProj, VECTOR3(0, 0, 0), m_pGMain->m_vEyePt);
}
