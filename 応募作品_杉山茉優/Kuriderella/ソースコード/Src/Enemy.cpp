//=============================================================================
//		�Q�c�A�N�V�����Q�[���v���O����
//		�b�Q�c�`�����P�P�S�@�@�@�@�@�@           ver 2.8        2020.2.15
//
//		�G�̏���
//																Enamy.cpp
//=============================================================================

#include "Enemy.h"
#include "Weapon.h"
#include "Effect.h"
#include "Playchar.h"
#include "Map.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//------------------------------------------------------------------------
//
// �G���C���v���V�[�W���̃R���X�g���N�^
//
//   �Ȃ��A�v���V�[�W����delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
//------------------------------------------------------------------------
CEnmProc::CEnmProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	m_pEnmWaterProc = new CEnmWaterProc(m_pGMain);
	m_pProcArray.push_back(m_pEnmWaterProc);   // �v���V�[�W�����v���V�[�W���z��ɓo�^����

	m_pEnmTordProc = new CEnmTordProc(m_pGMain);
	m_pProcArray.push_back(m_pEnmTordProc);   // �v���V�[�W�����v���V�[�W���z��ɓo�^����

	m_pEnmWolfProc = new CEnmWolfProc(m_pGMain);
	m_pProcArray.push_back(m_pEnmWolfProc);   // �v���V�[�W�����v���V�[�W���z��ɓo�^����

	m_pEnmFoxProc = new CEnmFoxProc(m_pGMain);
	m_pProcArray.push_back(m_pEnmFoxProc);   // �v���V�[�W�����v���V�[�W���z��ɓo�^����   

	m_pEnmDosProc = new CEnmDosProc(m_pGMain);
	m_pProcArray.push_back(m_pEnmDosProc);   // �v���V�[�W�����v���V�[�W���z��ɓo�^����

	m_pEnmSkyProc = new CEnmSkyProc(m_pGMain);
	m_pProcArray.push_back(m_pEnmSkyProc);   // �v���V�[�W�����v���V�[�W���z��ɓo�^����

	m_pEnmKingProc = new CEnmKingProc(m_pGMain);
	m_pProcArray.push_back(m_pEnmKingProc);   // �v���V�[�W�����v���V�[�W���z��ɓo�^����
}
//============================================================================
//   �G�v���V�[�W���ƃI�u�W�F�N�g��T�����S�ẴI�u�W�F�N�g���m���A�N�e�B�u�ɂ���
//   �G�v���V�[�W���̊J�n�t���O�����Z�b�g����
//============================================================================
void  CEnmProc::SetNonActive()
{
	// �G�̃I�u�W�F�N�g�|�C���^�z��̒T��
	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		m_pObjArray[i]->SetActive( FALSE);
	}
	// ���ʂ̃v���V�[�W���|�C���^�z��̒T��
	for (DWORD i = 0; i < m_pProcArray.size(); i++)
	{
		m_pProcArray[i]->SetStartFlag( 0 );				// �J�n�t���O�̃��Z�b�g
		((CEnmProc*)m_pProcArray[i])->SetNonActive();   // ���ʂ̃v���V�[�W���̏����i�ċA�����j
	}
}
// =====================================================================================================
// 
// �e�G�v���V�[�W�����̏���
// 
// =====================================================================================================
//------------------------------------------------------------------------
//
//	���̓G�v���V�[�W���̃R���X�g���N�^	
//
//   �Ȃ��A�I�u�W�F�N�g��delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
//------------------------------------------------------------------------
CEnmWaterProc::CEnmWaterProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	for (DWORD i = 0; i < ENM_WATER_MAX; i++)
	{
		m_pObjArray.push_back(new CEnmWaterObj(m_pGMain));  // m_pObjArray�ɃI�u�W�F�N�g�𐶐�����
	}
}
// ---------------------------------------------------------------------------
//
// ���̓G�v���V�[�W���̎�����������
//
//
// ---------------------------------------------------------------------------
void CEnmWaterProc::Update()
{
	VECTOR2 vPos;
	int nNext;
	// �܂������ł���ꍇ�̂ݔ���������
	if (m_nStartFlag == 0)
	{
		// �C�x���g�}�b�v��T�����A�G�̏o���ʒu��ݒ肷��
		nNext = 0;
		while (nNext != -1)
		{
			// �C�x���g�}�b�v�@ ( EvtID:3�@�G�̏o���ʒu,     �@EvtNo:0x01	���̓G  )
			if (m_pGMain->m_pMapProc->SearchEvt(nNext, 3, 0x01, vPos, nNext))
			{
				for (DWORD j = 0; j < m_pObjArray.size(); j++)
				{
					if (!m_pObjArray[j]->GetActive())
					{
						m_pObjArray[j]->Start(vPos);
						break;
					}
				}
			}
		}
		m_nStartFlag = 1;  // ��񔭂�������A�����������Ȃ�
	}
	//  (����)m_nWaitTime�̃J�E���g�_�E���́ACBaseProc�ōs���Ă���
}
//------------------------------------------------------------------------
//
//	���̓G�I�u�W�F�N�g�̃R���X�g���N�^	
//
//  �����@�Ȃ�
//
//------------------------------------------------------------------------
CEnmWaterObj::CEnmWaterObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	// M.S ���̓G�̃X�v���C�g
	m_pSprite = new CSprite(m_pGMain->m_pImageChar, 896, 0, 64, 64);
	m_fAlpha = 0.8f;
	m_vPos = VECTOR2(0, 0);
	m_nHp = m_nMaxHp = 10000;
	m_nAtc = 1;
}
// ---------------------------------------------------------------------------
//
// ���̓G�I�u�W�F�N�g�̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CEnmWaterObj::~CEnmWaterObj()
{
	SAFE_DELETE(m_pSprite);
}
//-----------------------------------------------------------------------------
// ���̓G�I�u�W�F�N�g�̊J�n
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
BOOL	CEnmWaterObj::Start(VECTOR2 vPos)
{
	m_bActive = TRUE;
	ResetStatus();
	ResetAnim();
	m_nDirIdx = RIGHT;
	m_vPos = vPos;	// �����ʒu
	m_vPosUp = VECTOR2(0, 0);
	m_nHp = m_nMaxHp;

	return TRUE;
}
//-----------------------------------------------------------------------------
// ���̓G�I�u�W�F�N�g�̍X�V
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CEnmWaterObj::Update()
{
	CMapLine* pHitmapline;
	BOOL bRet;
	if (m_bActive)
	{
		switch (m_dwStatus)
		{
		case  NORMAL:
			m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this);
			bRet = m_pGMain->m_pMapProc->isCollisionMoveMap(this, pHitmapline);
			break;
		case  DAMAGE:
			m_dwStatus = NORMAL;
			m_pGMain->hank = 1;  // M.S �v���C�L�����Ƃ̐ڐG�t���O�����Ă�		
			break;
		case  DEAD:
			m_dwStatus = NORMAL;
			break;
		}
		AnimCountup();
		Draw();
	}
}
// ===================================================================================================
//------------------------------------------------------------------------
//
//	�D�F�̓G�v���V�[�W���̃R���X�g���N�^	
//
//   �Ȃ��A�I�u�W�F�N�g��delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
//------------------------------------------------------------------------
CEnmTordProc::CEnmTordProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	for (DWORD i = 0; i < ENM_TORD_MAX; i++)
	{
		m_pObjArray.push_back(new CEnmTordObj(m_pGMain));  // m_pObjArray�ɃI�u�W�F�N�g�𐶐�����
	}
}
// ---------------------------------------------------------------------------
//
// �D�F�̓G�v���V�[�W���̎�����������
//
//
// ---------------------------------------------------------------------------
void CEnmTordProc::Update()
{
	VECTOR2 vPos;
	int nNext;
	// �܂������ł���ꍇ�̂ݔ���������
	if (m_nStartFlag == 0)
	{
		// �C�x���g�}�b�v��T�����A�G�̏o���ʒu��ݒ肷��
		nNext = 0;
		while ( nNext != -1)
		{
			// �C�x���g�}�b�v�@ ( EvtID:3�@�G�̏o���ʒu,     �@EvtNo:0x02�@�D�F�̓G  )
			if (m_pGMain->m_pMapProc->SearchEvt(nNext, 3, 0x02, vPos, nNext))
			{
				for (DWORD j = 0; j < m_pObjArray.size(); j++)
				{
					if (!m_pObjArray[j]->GetActive())
					{
						m_pObjArray[j]->Start(vPos);
						break;
					}
				}
			}
		}
		m_nStartFlag = 1;  // ��񔭂�������A�����������Ȃ�
	}
	//  (����)m_nWaitTime�̃J�E���g�_�E���́ACBaseProc�ōs���Ă���
}
//------------------------------------------------------------------------
//
//	�D�F�̓G�I�u�W�F�N�g�̃R���X�g���N�^	
//
//  �����@�Ȃ�
//
//------------------------------------------------------------------------
CEnmTordObj::CEnmTordObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	// M.S �D�F�̓G�̃X�v���C�g
	m_pSprite = new CSprite(m_pGMain->m_pImageChar, 640, 0, 64, 64);  
	m_vPos = VECTOR2(0, 0);
	m_nHp = m_nMaxHp = 1;
	m_nAtc = 1;
}
// ---------------------------------------------------------------------------
//
// �D�F�̓G�I�u�W�F�N�g�̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CEnmTordObj::~CEnmTordObj()
{
	SAFE_DELETE(m_pSprite);
}

//-----------------------------------------------------------------------------
// �D�F�̓G�I�u�W�F�N�g�̊J�n
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
BOOL	CEnmTordObj::Start(VECTOR2 vPos)
{
	m_bActive = TRUE;
	ResetStatus();
	ResetAnim();
	m_nDirIdx = LEFT;
	m_vPos = vPos;	// �����ʒu
	m_vPosUp = VECTOR2(0, 0);
	m_nHp = m_nMaxHp;

	return TRUE;
}
//-----------------------------------------------------------------------------
// �D�F�̓G�I�u�W�F�N�g�̍X�V
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CEnmTordObj::Update()
{
	CMapLine*  pHitmapline = NULL;
	float fSpeed = 1;
	BOOL bRet;
	if (m_bActive)
	{
		m_vPosUp = VECTOR2(0, 0);
		switch (m_dwStatus)
		{
		case  FLASH:
			m_nCnt1--;
			if (m_nCnt1 <= 0) {
				ResetStatus();
				ResetAnim();
			}
			else {
				FlashCountup();
			}		// break;����ꂸ���̂܂܁@NORMAL�@�̏������s��
		case  NORMAL:
			switch (m_dwStatusSub)
			{
			case  WALK:
				// ���R�ړ��̏���
				if (m_nDirIdx == RIGHT)
				{
					m_vPosUp.x = fSpeed;
				}
				else {
					m_vPosUp.x = -fSpeed;
				}
				// �}�b�v���Ƃ̐ڐG����ƓK�؂Ȉʒu�ւ̈ړ�
				bRet = m_pGMain->m_pMapProc->isCollisionMoveMap(this, pHitmapline);
				if (!bRet || (pHitmapline && pHitmapline->m_vNormal.y > -0.99f))
				{
					// �}�b�v���̒[�ɗ����̂ō��E���]
					if (m_nDirIdx == RIGHT)
					{
						m_nDirIdx = LEFT;
						m_vPosUp.x = -fSpeed;
						m_vPosUp.y = 0;
					}
					else {
						m_nDirIdx = RIGHT;
						m_vPosUp.x = fSpeed;
						m_vPosUp.y = 0;
					}
				}
				break;
			}
			// ����
			m_vPos += m_vPosUp;
			// �o�b�Ƃ̂����蔻��
			m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this);
			break;
		case  DAMAGE:
			m_nHp -= m_pOtherObj->GetAtc();
			if (m_nHp <= 0) {
				m_dwStatus = DEAD;
				m_nCnt1 = 180;
			}
			else {
				m_dwStatus = FLASH;
				m_nCnt1 = 60;
			}
			m_pGMain->m_pSeHit->Play(); // �_���[�W���ʉ�
			break;

		case  DEAD:
			m_nCnt1--;
			// DEAD�ɂȂ�A��莞�Ԃ�������\��������
			if (m_nCnt1 <= 0)
			{
				m_bActive = FALSE;
			}
			else {
				FlashCountup();
			}
			break;
		}
		AnimCountup();
		Draw();
	}
}
// ===================================================================================================

//------------------------------------------------------------------------
//
//	�ԐF�̓G�v���V�[�W���̃R���X�g���N�^	
//
//   �Ȃ��A�I�u�W�F�N�g��delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
//------------------------------------------------------------------------
CEnmWolfProc::CEnmWolfProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	for (DWORD i = 0; i < ENM_TORD_MAX; i++)
	{
		m_pObjArray.push_back(new CEnmWolfObj(m_pGMain));  // m_pObjArray�ɃI�u�W�F�N�g�𐶐�����
	}
}
// ---------------------------------------------------------------------------
//
// �ԐF�̓G�v���V�[�W���̎�����������
//
//
// ---------------------------------------------------------------------------
void CEnmWolfProc::Update()
{
	VECTOR2 vPos;
	int  nNext;
	// �܂������ł���ꍇ�̂ݔ���������
	if (m_nStartFlag == 0)
	{
		// �C�x���g�}�b�v��T�����A�G�̏o���ʒu��ݒ肷��
		nNext = 0;
		while (nNext != -1)
		{
			// �C�x���g�}�b�v�̒T�� (EvtID:3 �G�̏o���ʒu, EvtNo:0x04 �ԐF�̓G)
			if (m_pGMain->m_pMapProc->SearchEvt(nNext, 3, 0x04, vPos, nNext))
			{
				for (DWORD j = 0; j < m_pObjArray.size(); j++)
				{
					if (!m_pObjArray[j]->GetActive())
					{
						m_pObjArray[j]->Start(vPos);
						break;
					}
				}
			}
		}
		m_nStartFlag = 1;  // ��񔭂�������A�����������Ȃ�
	}
	//  (����)m_nWaitTime�̃J�E���g�_�E���́ACBaseProc�ōs���Ă���
}
//------------------------------------------------------------------------
//
//	�ԐF�̓G�I�u�W�F�N�g�̃R���X�g���N�^	
//
//  �����@�Ȃ�
//
//------------------------------------------------------------------------
CEnmWolfObj::CEnmWolfObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	// M.S �ԐF�̓G�̃X�v���C�g
	m_pSprite = new CSprite(m_pGMain->m_pImageChar, 384, 0, 64, 64);
	m_vPos = VECTOR2(0, 0);
	m_nHp = m_nMaxHp = 2;
	m_nAtc = 2;
}
// ---------------------------------------------------------------------------
//
// �ԐF�̓G�I�u�W�F�N�g�̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CEnmWolfObj::~CEnmWolfObj()
{
	SAFE_DELETE(m_pSprite);
}

//-----------------------------------------------------------------------------
// �ԐF�̓G�I�u�W�F�N�g�̊J�n
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
BOOL	CEnmWolfObj::Start(VECTOR2 vPos)
{
	m_bActive = TRUE;
	ResetStatus();
	ResetAnim();
	m_nDirIdx = LEFT;
	m_vPos = vPos;	// �����ʒu
	m_vPosUp = VECTOR2(0, 0);
	m_nHp = m_nMaxHp;

	return TRUE;
}
//-----------------------------------------------------------------------------
// �ԐF�̓G�I�u�W�F�N�g�̍X�V
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CEnmWolfObj::Update()
{
	CMapLine*  pHitmapline = NULL;
	float fSpeed = 1;
	BOOL bRet;
	if (m_bActive)
	{
		m_vPosUp = VECTOR2(0, 0);
		switch (m_dwStatus)
		{
		case  FLASH:
			m_nCnt1--;
			if (m_nCnt1 <= 0) {
				ResetStatus();
				ResetAnim();
			}
			else {
				FlashCountup();
			}		// break;����ꂸ���̂܂܁@NORMAL�@�̏������s��
		case  NORMAL:
			switch (m_dwStatusSub)
			{
			case  WALK:
				// ���R�ړ��̏���
				if (m_nDirIdx == RIGHT)
				{
					m_vPosUp.x = fSpeed;
				}
				else {
					m_vPosUp.x = -fSpeed;
				}
				// �}�b�v���Ƃ̐ڐG����ƓK�؂Ȉʒu�ւ̈ړ�
				bRet = m_pGMain->m_pMapProc->isCollisionMoveMap(this, pHitmapline);
				if (!bRet || (pHitmapline && pHitmapline->m_vNormal.y > -0.99f))
				{
					// �}�b�v���̒[�ɗ����̂ō��E���]
					if (m_nDirIdx == RIGHT)
					{
						m_nDirIdx = LEFT;
						m_vPosUp.x = -fSpeed;
						m_vPosUp.y = 0;
					}
					else {
						m_nDirIdx = RIGHT;
						m_vPosUp.x = fSpeed;
						m_vPosUp.y = 0;
					}
				}
				break;
			}
			// ����
			m_vPos += m_vPosUp;
			// �o�b�Ƃ̂����蔻��
			m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this);
			break;
		case  DAMAGE:
			m_nHp -= m_pOtherObj->GetAtc();
			if (m_nHp <= 0) {
				m_dwStatus = DEAD;
				m_nCnt1 = 180;
			}
			else {
				m_dwStatus = FLASH;
				m_nCnt1 = 60;
			}
			m_pGMain->m_pSeHit->Play();  // �_���[�W���ʉ�
			break;
		case  DEAD:
			m_nCnt1--;
			// DEAD�ɂȂ�A��莞�Ԃ�������\��������
			if (m_nCnt1 <= 0)
			{
				m_pGMain->SilverS += 1; // M.S �┓�̎擾����+1
				m_bActive = FALSE;
				// M.S �ԐF�̓G�̃X�v���C�g�ɖ߂�
				m_pSprite = new CSprite(m_pGMain->m_pImageChar, 384, 0, 64, 64);
				m_nAnimNum = 2;  // M.S �A�j���[�V��������߂�
			}
			else {
				m_nAnimNum = 1;  // M.S �擾�A�C�e���̕\���̓A�j���[�V�����Ȃ��Ȃ̂�1
				// M.S �擾�A�C�e���̉摜�ɕς���
				m_pSprite = new CSprite(m_pGMain->m_pImageSpriteS, 0, 0, 48, 48);
				FlashCountup();
			}
			break;
		}
		AnimCountup();
		Draw();
	}
}
// ===================================================================================================
//------------------------------------------------------------------------
//
//	�΂̓G�v���V�[�W���̃R���X�g���N�^	
//
//   �Ȃ��A�I�u�W�F�N�g��delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
//------------------------------------------------------------------------
CEnmFoxProc::CEnmFoxProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	for (DWORD i = 0; i < ENM_FOX_MAX; i++)				//��
	{
		m_pObjArray.push_back(new CEnmFoxObj(m_pGMain));  // m_pObjArray�ɃI�u�W�F�N�g�𐶐�����
	}
}
// ---------------------------------------------------------------------------
//
// �΂̓G�v���V�[�W���̎�����������
//
//
// ---------------------------------------------------------------------------
void CEnmFoxProc::Update()
{
	VECTOR2 vPos;
	int  nNext;
	// �܂������ł���ꍇ�̂ݔ���������
	if (m_nStartFlag == 0)
	{
		// �C�x���g�}�b�v��T�����A�G�̏o���ʒu��ݒ肷��
		nNext = 0;
		while (nNext != -1)
		{
			// �C�x���g�}�b�v�̒T�� (EvtID:3 �G�̏o���ʒu, EvtNo:0x08 �΂̓G)
			if (m_pGMain->m_pMapProc->SearchEvt(nNext, 3, 0x08, vPos, nNext))
			{
				for (DWORD j = 0; j < m_pObjArray.size(); j++)
				{
					if (!m_pObjArray[j]->GetActive())
					{
						m_pObjArray[j]->Start(vPos);
						break;
					}
				}
			}
		}

	}
	m_nStartFlag = 1;  // ��񔭂�������A�����������Ȃ�
//  (����)m_nWaitTime�̃J�E���g�_�E���́ACBaseProc�ōs���Ă���
}
//------------------------------------------------------------------------
//
//	�΂̓G�I�u�W�F�N�g�̃R���X�g���N�^	
//
//  �����@�Ȃ�
//
//------------------------------------------------------------------------
CEnmFoxObj::CEnmFoxObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	// M.S �΂̓G�̃X�v���C�g
	m_pSprite = new CSprite(m_pGMain->m_pImageChar, 512, 0, 64, 64);		
	m_vPos = VECTOR2(0, 0);
	m_nHp = m_nMaxHp = 6;						
	m_nAtc = 2;							

}
// ---------------------------------------------------------------------------
//
// �΂̓G�I�u�W�F�N�g�̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CEnmFoxObj::~CEnmFoxObj()
{
	SAFE_DELETE(m_pSprite);
}
// M.S ������0�`2�̐��ɂ���
// ��  ���Fint   num   num����0�`2�̐����o��
// �߂�l�Fint   anum  0�`2�ɕς�����
int	CEnmFoxObj::RandomNumAns(int num) {
	int anum = num % 3;
	return anum;
}
//-----------------------------------------------------------------------------
// �΂̓G�I�u�W�F�N�g�̊J�n
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
BOOL CEnmFoxObj::Start(VECTOR2 vPos)
{	
	srand(time(NULL));  // M.S �����̏�����
	num = rand() % 10;  // M.S �����̎擾�A0~9�̐����𓾂�
	returnNum = RandomNumAns(num); // M.S num��0�`2�̐��ɕς���	
	m_bActive = TRUE;
	ResetStatus();
	ResetAnim();
	m_nDirIdx = RIGHT;	// M.S ���Ό���
	m_vPos = vPos;	    // �����ʒu
	m_vPosUp = VECTOR2(0, 0);
	m_nHp = m_nMaxHp;

	return TRUE;
}
//-----------------------------------------------------------------------------
//�΂̓G�I�u�W�F�N�g�̍X�V
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CEnmFoxObj::Update()
{
	if (returnNum == 0) {
		CMapLine*  pHitmapline = NULL;
		float fSpeed = 1;
		BOOL bRet;
		if (m_bActive)
		{
			m_vPosUp = VECTOR2(0, 0);

			switch (m_dwStatus)
			{
			case  FLASH:
				m_nCnt1--;
				if (m_nCnt1 <= 0) {
					ResetStatus();
					ResetAnim();
				}
				else {
					FlashCountup();
				}		// break;����ꂸ���̂܂܁@NORMAL�@�̏������s��
			case  NORMAL:
				switch (m_dwStatusSub)
				{
				case  WALK:
					// ���R�ړ��̏���
					if (m_nDirIdx == RIGHT)
					{
						m_vPosUp.x = fSpeed;
					}
					else {
						m_vPosUp.x = -fSpeed;
					}
					// �}�b�v���Ƃ̐ڐG����ƓK�؂Ȉʒu�ւ̈ړ�
					bRet = m_pGMain->m_pMapProc->isCollisionMoveMap(this, pHitmapline);
					if (!bRet || (pHitmapline && pHitmapline->m_vNormal.y > -0.99f))
					{
						// �}�b�v���̒[�ɗ����̂ō��E���]
						if (m_nDirIdx == RIGHT)
						{
							m_nDirIdx = LEFT;
							m_vPosUp.x = -fSpeed;
							m_vPosUp.y = 0;
						}
						else {
							m_nDirIdx = RIGHT;
							m_vPosUp.x = fSpeed;
							m_vPosUp.y = 0;
						}
					}
					break;
				}
				// ����
				m_vPos += m_vPosUp;
				// �o�b�Ƃ̂����蔻��
				m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this);
				break;
			case  DAMAGE:
				m_nHp -= m_pOtherObj->GetAtc();
				if (m_nHp <= 0) {
					m_dwStatus = DEAD;
					m_nCnt1 = 180;
				}
				else {
					m_dwStatus = FLASH;
					m_nCnt1 = 60;
				}
				m_pGMain->m_pSeHit->Play();  // �_���[�W���ʉ�
				break;
			case  DEAD:
				m_nCnt1--;
				// DEAD�ɂȂ�A��莞�Ԃ�������\��������
				if (m_nCnt1 <= 0)
				{
					m_pGMain->GoldS += 1;  // M.S �����̎擾����+1
					m_bActive = FALSE;
					// M.S �΂̓G�̃X�v���C�g�ɖ߂�
					m_pSprite = new CSprite(m_pGMain->m_pImageChar, 512, 0, 64, 64);
					m_nAnimNum = 2; // M.S �A�j���[�V��������߂�
				}
				else {
					m_nAnimNum = 1;  // M.S �擾�A�C�e���̕\���̓A�j���[�V�����Ȃ��Ȃ̂�1
					// M.S �擾�A�C�e���̉摜�ɕς���
					m_pSprite = new CSprite(m_pGMain->m_pImageSpriteS, 0, 0, 48, 48);
					FlashCountup();
				}
				break;
			}
			AnimCountup();
			Draw();
		}	
    }
}	
//------------------------------------------------------------------------
//
//	�h�b�X���̓G�v���V�[�W���̃R���X�g���N�^	
//
//   �Ȃ��A�I�u�W�F�N�g��delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
//------------------------------------------------------------------------
CEnmDosProc::CEnmDosProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	for (DWORD i = 0; i < ENM_DOS_MAX; i++)
	{
		m_pObjArray.push_back(new CEnmDosObj(m_pGMain));  // m_pObjArray�ɃI�u�W�F�N�g�𐶐�����
	}
}
// ---------------------------------------------------------------------------
//
// �h�b�X���̓G�v���V�[�W���̎�����������
//
//
// ---------------------------------------------------------------------------
void CEnmDosProc::Update()
{
	VECTOR2 vPos;
	int nNext;

	// �܂������ł���ꍇ�̂ݔ���������
	if (m_nStartFlag == 0)
	{
		// �C�x���g�}�b�v��T�����A�G�̏o���ʒu��ݒ肷��
		nNext = 0;
		while (nNext != -1)
		{
			// �C�x���g�}�b�v (EvtID:3�@�G�̏o���ʒu, EvtNo:0x2000 �h�b�X���̓G)
			if (m_pGMain->m_pMapProc->SearchEvt(nNext, 3, 0x2000, vPos, nNext))
			{
				for (DWORD j = 0; j < m_pObjArray.size(); j++)
				{
					if (!m_pObjArray[j]->GetActive())
					{
						m_pObjArray[j]->Start(vPos);
						break;
					}
				}
			}
		}
		m_nStartFlag = 1;  // ��񔭂�������A�����������Ȃ�
	}
	//  (����)m_nWaitTime�̃J�E���g�_�E���́ACBaseProc�ōs���Ă���
}
//------------------------------------------------------------------------
//
//	�h�b�X���̓G�I�u�W�F�N�g�̃R���X�g���N�^	
//
//  �����@�Ȃ�
//
//------------------------------------------------------------------------
CEnmDosObj::CEnmDosObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	// M.S �h�b�X���̓G�̃X�v���C�g
	m_pSprite = new CSprite(m_pGMain->m_pImageChar, 1024, 0, 64, 64);
	m_vPos = VECTOR2(0, 0);
	m_nHp = m_nMaxHp = 10000;
	m_nAtc = 1;
}
// ---------------------------------------------------------------------------
//
// �h�b�X���̓G�I�u�W�F�N�g�̃f�X�g���N�^
//	// ---------------------------------------------------------------------------
CEnmDosObj::~CEnmDosObj()
{
	SAFE_DELETE(m_pSprite);
}
//-----------------------------------------------------------------------------
// �h�b�X���̓G�I�u�W�F�N�g�̊J�n
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
BOOL	CEnmDosObj::Start(VECTOR2 vPos)
{
	m_bActive = TRUE;
	ResetStatus();
	ResetAnim();
	m_nDirIdx = RIGHT;
	m_vPos = vPos;	// �����ʒu
	m_vPosUp = VECTOR2(0, 0);
	m_nHp = m_nMaxHp;

	return TRUE;
}
//-----------------------------------------------------------------------------
// �h�b�X���̓G�I�u�W�F�N�g�̍X�V
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CEnmDosObj::Update()
{
	CMapLine*  pHitmapline = NULL;
	float fSpeed = 1;
	BOOL bRet;
	int am = 0;
	if (m_bActive)
	{
		m_vPosUp = VECTOR2(0, 0);
		switch (m_dwStatus)
		{
		case  FLASH:
			m_nCnt1--;
			if (m_nCnt1 <= 0) {
				ResetStatus();
				ResetAnim();
			}
			else {
				FlashCountup();
			}		// break;����ꂸ���̂܂܁@NORMAL�@�̏������s��
		case  NORMAL:
			m_vPosUp.x = 0;
			m_vPosUp.y = 0;
			m_nDirIdx = RIGHT;
			bRet = m_pGMain->m_pMapProc->isCollisionMoveMap(this, pHitmapline);
			// ����
			m_vPos += m_vPosUp;
			// �o�b�Ƃ̂����蔻��
			m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this);
			break;
		case  DAMAGE:
			m_nHp -= m_pOtherObj->GetAtc();
			if (m_nHp <= 0) {
				m_dwStatus = DEAD;
				m_nCnt1 = 180;
			}
			else {
				m_dwStatus = FLASH;
				m_nCnt1 = 60;
				m_pGMain->m_pSeHit->Play();  // �_���[�W���ʉ�
				m_pGMain->henk = 1;  // M.S �v���C�L�����Ƃ̐ڐG�t���O�����Ă�
				break;
			}
		case  DEAD:
			m_nCnt1--;
			if (m_nCnt1 <= 0)
			{
				m_bActive = FALSE;
			}
			else {
				FlashCountup();
			}
			break;
		}
	}
	AnimCountup();
	Draw();
}
//------------------------------------------------------------------------
//
//	�{�X�̓G�v���V�[�W���̃R���X�g���N�^	
//
//   �Ȃ��A�I�u�W�F�N�g��delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
//------------------------------------------------------------------------
CEnmKingProc::CEnmKingProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	for (DWORD i = 0; i < ENM_KING_MAX; i++)
	{
		m_pObjArray.push_back(new CEnmKingObj(m_pGMain));  // m_pObjArray�ɃI�u�W�F�N�g�𐶐�����
	}
}
// ---------------------------------------------------------------------------
//
// �{�X�̓G�v���V�[�W���̎�����������
//
//
// ---------------------------------------------------------------------------
void CEnmKingProc::Update()
{
	VECTOR2 vPos;
	int nNext;
	// �܂������ł���ꍇ�̂ݔ���������
	if (m_nStartFlag == 0)
	{
		// �C�x���g�}�b�v��T�����A�G�̏o���ʒu��ݒ肷��
		nNext = 0;
		while (nNext != -1)
		{
			// �C�x���g�}�b�v ( EvtID:3�@�G�̏o���ʒu, EvtNo:0x40�@�{�X)
			if (m_pGMain->m_pMapProc->SearchEvt(nNext, 3, 0x40, vPos, nNext))
			{
				for (DWORD j = 0; j < m_pObjArray.size(); j++)
				{
					if (!m_pObjArray[j]->GetActive())
					{
						m_pObjArray[j]->Start(vPos);
						break;
					}
				}
			}
		}
		m_nStartFlag = 1;  // ��񔭂�������A�����������Ȃ�
	}
	//  (����)m_nWaitTime�̃J�E���g�_�E���́ACBaseProc�ōs���Ă���
}
//------------------------------------------------------------------------
//
//	�{�X�̓G�I�u�W�F�N�g�̃R���X�g���N�^	
//
//  �����@�Ȃ�
//
//------------------------------------------------------------------------
CEnmKingObj::CEnmKingObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	// M.S �{�X�̓G�̃X�v���C�g
	m_pSprite = new CSprite(m_pGMain->m_pImageChar, 768, 0, 64, 64);
	m_vPos = VECTOR2(0, 0);
	m_nHp = m_nMaxHp = 6;
	m_nAtc = 3;
}
// ---------------------------------------------------------------------------
//
// �{�X�̓G�I�u�W�F�N�g�̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CEnmKingObj::~CEnmKingObj()
{
	SAFE_DELETE(m_pSprite);
}
//-----------------------------------------------------------------------------
// �{�X�̓G�I�u�W�F�N�g�̊J�n
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
BOOL	CEnmKingObj::Start(VECTOR2 vPos)
{
	m_bActive = TRUE;
	ResetStatus();
	ResetAnim();
	m_nDirIdx = LEFT;
	m_vPos = vPos;	// �����ʒu
	m_vPosUp = VECTOR2(0, 0);
	m_nHp = m_nMaxHp;
	m_pGMain->m_nEShotWait = eWaitNum;

	return TRUE;
}
//-----------------------------------------------------------------------------
// �{�X�̓G�I�u�W�F�N�g�̍X�V
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CEnmKingObj::Update()
{
	CMapLine*  pHitmapline = NULL;
	float fSpeed = 1;
	BOOL bRet;
	VECTOR2 vPcPos;
	// M.S �v���C�L�����̈ʒu�̎擾
	vPcPos.x = m_pGMain->m_pPcProc->GetPcObjPtr()->GetPos().x;
	if (m_bActive)
	{
		m_vPosUp = VECTOR2(0, 0);
		switch (m_dwStatus)
		{
		case  FLASH:
			m_nCnt1--;
			if (m_nCnt1 <= 0) {
				ResetStatus();
				ResetAnim();
			}
			else {
				FlashCountup();
			}		// break;����ꂸ���̂܂܁@NORMAL�@�̏������s��
		case  NORMAL:
			switch (m_dwStatusSub)
			{
			case  WALK:
				// ���R�ړ��̏���
				// M.S �v���C�L�����Ǝ����̈ʒu���擾���A�v���C�L�����̕����Ɍ�����
				if (m_vPos.x > vPcPos.x)   // M.S ������X�ʒu�̕����傫���ꍇ
				{
					m_nDirIdx = LEFT;      // M.S �������֌�����
					m_vPosUp.x = -fSpeed;
				}
				else { // M.S ������X�ʒu�̕����������ꍇ
					m_nDirIdx = RIGHT;     // M.S �E�����֌�����
					m_vPosUp.x = fSpeed;
				}
				// �}�b�v���Ƃ̐ڐG����ƓK�؂Ȉʒu�ւ̈ړ�
				bRet = m_pGMain->m_pMapProc->isCollisionMoveMap(this, pHitmapline);
				if (!bRet || (pHitmapline && pHitmapline->m_vNormal.y > -0.99f))
				{
					// �}�b�v���̒[�ɗ����̂ō��E���]
					if (m_nDirIdx == RIGHT)
					{
						m_vPosUp.y = 0;
					}
					else {
						m_vPosUp.y = 0;
					}
					break;
				}
			}
			// M.S �G����PC�Ɍ������Ēe�𔭎�
			// M.S �����̌y�ʉ��̂��߉�ʊO�̏ꍇ�͔��˂��Ȃ�
			if (eWaitNum <= 0) {
				if (m_vPos.x - m_pGMain->m_vScroll.x < 0 || m_vPos.x - m_pGMain->m_vScroll.x > WINDOW_WIDTH) {
				}
				else {
					m_pGMain->m_pWeaponProc->m_pEWeaponShotProc->Start(m_vPos + VECTOR2(20, 20), this, ENM);
					eWaitNum = 40;  // M.S ���ˑ҂����Ԃ̏�����
				}
			}
			if (eWaitNum > 0) {
				eWaitNum--;
			}
			// ����
			m_vPos += m_vPosUp;
			// �o�b�Ƃ̂����蔻��
			m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this);
			break;
		case  DAMAGE:
			m_nHp -= m_pOtherObj->GetAtc();
			if (m_nHp <= 0) {
				m_dwStatus = DEAD;
				m_nCnt1 = 180;
			}
			else {
				m_dwStatus = FLASH;
				m_nCnt1 = 60;
			}
			m_pGMain->m_pSeHit->Play();  // �_���[�W���ʉ�
			break;
		case  DEAD:
			m_nCnt1--;
			// DEAD�ɂȂ�A��莞�Ԃ�������\��������
			if (m_nCnt1 <= 0)
			{
				m_pGMain->VisionS += 1;  // M.S ���̍����̎擾����+1
				m_bActive = FALSE;
				// M.S �{�X�̃X�v���C�g�ɖ߂�
				m_pSprite = new CSprite(m_pGMain->m_pImageChar, 768, 0, 64, 64);
				m_nAnimNum = 2;  // M.S �A�j���[�V��������߂�
			}
			else {
				m_nAnimNum = 1;  // M.S �擾�A�C�e���̕\���̓A�j���[�V�����Ȃ��Ȃ̂�1
				// M.S �擾�A�C�e���̉摜�ɕς���
				m_pSprite = new CSprite(m_pGMain->m_pImageSpriteV, 0, 0, 48, 48);
				FlashCountup();
			}
			break;
		}
	}
	AnimCountup();
	Draw();
}
//------------------------------------------------------------------------
//
//	�����̃v���V�[�W���̃R���X�g���N�^	
//
//   �Ȃ��A�I�u�W�F�N�g��delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
//------------------------------------------------------------------------
CEnmSkyProc::CEnmSkyProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	for (DWORD i = 0; i < ENM_SKY_MAX; i++)
	{
		m_pObjArray.push_back(new CEnmSkyObj(m_pGMain));  // m_pObjArray�ɃI�u�W�F�N�g�𐶐�����
	}
}
// ---------------------------------------------------------------------------
//
//  �����̃v���V�[�W���̎�����������
//
//
// ---------------------------------------------------------------------------
void CEnmSkyProc::Update()
{
	VECTOR2 vPos;
	int nNext;

	// �܂������ł���ꍇ�̂ݔ���������
	if (m_nStartFlag == 0)
	{
		// �C�x���g�}�b�v��T�����A�G�̏o���ʒu��ݒ肷��
		nNext = 0;
		while (nNext != -1)
		{
			// �C�x���g�}�b�v (EvtID:3�@�G�̏o���ʒu, EvtNo:0x80 ����)
			if (m_pGMain->m_pMapProc->SearchEvt(nNext, 3, 0x80, vPos, nNext))
			{
				for (DWORD j = 0; j < m_pObjArray.size(); j++)
				{
					if (!m_pObjArray[j]->GetActive())
					{
						m_pObjArray[j]->Start(vPos);
						break;
					}
				}
			}
		}
		m_nStartFlag = 1;  // ��񔭂�������A�����������Ȃ�
	}
	//  (����)m_nWaitTime�̃J�E���g�_�E���́ACBaseProc�ōs���Ă���
}
//------------------------------------------------------------------------
//
//	�����̃I�u�W�F�N�g�̃R���X�g���N�^	
//
//  �����@�Ȃ�
//
//------------------------------------------------------------------------
CEnmSkyObj::CEnmSkyObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	// M.S �����̃X�v���C�g
	m_pSprite = new CSprite(m_pGMain->m_pImageChar, 1152, 0, 64, 64);
	m_vPos = VECTOR2(0, 0);
	m_nHp = m_nMaxHp = 10000;
	m_nAtc = 0;

}
// ---------------------------------------------------------------------------
//
//  �����̃I�u�W�F�N�g�̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CEnmSkyObj::~CEnmSkyObj()
{
	SAFE_DELETE(m_pSprite);
}
//-----------------------------------------------------------------------------
// �����̃I�u�W�F�N�g�̊J�n
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
BOOL	CEnmSkyObj::Start(VECTOR2 vPos)
{
	m_bActive = TRUE;
	ResetStatus();
	ResetAnim();
	m_nDirIdx = RIGHT;
	m_vPos = vPos;	// �����ʒu
	m_vPosUp = VECTOR2(0, 0);
	m_nHp = m_nMaxHp;

	return TRUE;
}
//-----------------------------------------------------------------------------
// �����̃I�u�W�F�N�g�̍X�V
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CEnmSkyObj::Update()
{
	CMapLine* pHitmapline = NULL;
	bool bRet = false;
	bool hitCheck = false;
	if (m_bActive)
	{
		switch (m_dwStatus)
		{
		case  NORMAL:
			m_pGMain->ints = 0; // M.S ints�̏����� 
			// M.S �v���C�L�����Ƃ̓����蔻��𒲂ׂ�
			hitCheck = m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this);
			bRet = m_pGMain->m_pMapProc->isCollisionMoveMap(this, pHitmapline);
			// �}�b�v���Ƃ̐ڐG����ƓK�؂Ȉʒu�ւ̈ړ�		
		case  DAMAGE:
			if (bRet == true) {  // M.S �e�X�e�[�W�Řb�����t��ς���
				// M.S �\��������ς��邽�߂ɂ��̃X�e�[�W�ɂ����ints�ɒl������
				if (m_pGMain->m_pMapProc->m_nMapNo == 0 && hitCheck == true) {
					m_pGMain->ints = 1;
				}
				else if (m_pGMain->m_pMapProc->m_nMapNo == 1 && hitCheck == true) {
					m_pGMain->ints = 2;
				}
				else if (m_pGMain->m_pMapProc->m_nMapNo == 2 && hitCheck == true) {
					m_pGMain->ints = 3;
				}
				else if (m_pGMain->m_pMapProc->m_nMapNo == 3 && hitCheck == true) {
					m_pGMain->ints = 4;
				}
				else if (m_pGMain->m_pMapProc->m_nMapNo == 4 && hitCheck == true) {
					m_pGMain->ints = 5;
				}
			}
			m_dwStatus = NORMAL;
			break;
		case  DEAD:
			m_dwStatus = NORMAL;
			break;
		}
		AnimCountup();
		Draw();
	}
}