//=============================================================================
//		�Q�c�A�N�V�����Q�[���v���O����
//		�b�Q�c�`�����P�P�S�@�@�@�@�@�@           ver 2.8        2020.2.15
//
//		�f�����ʂ̏���
//																Effect.cpp
//=============================================================================

#include "Effect.h"
#include "Playchar.h"
#include "Map.h"
#include <stdio.h>
#include <string>

//------------------------------------------------------------------------
//
//	�f�����ʃ��C���v���V�[�W���̃R���X�g���N�^
//
//   �Ȃ��A�v���V�[�W����delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
//------------------------------------------------------------------------
CEffectProc::CEffectProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	m_pEffectBomProc = new CEffectBomProc(m_pGMain);	// �f�����ʁE�����v���V�[�W��
	m_pProcArray.push_back(m_pEffectBomProc);     // �v���V�[�W�����v���V�[�W���z��ɓo�^����

	m_pItemProc = new CItemProc(m_pGMain);				// �A�C�e���v���V�[�W��
	m_pProcArray.push_back(m_pItemProc);		// �v���V�[�W�����v���V�[�W���z��ɓo�^����
}
//============================================================================
//   �v���V�[�W���ƃI�u�W�F�N�g��T�����S�ẴI�u�W�F�N�g���m���A�N�e�B�u�ɂ���
//   �v���V�[�W���̊J�n�t���O�����Z�b�g����
//============================================================================
void  CEffectProc::SetNonActive()
{
	//�I�u�W�F�N�g�|�C���^�z��̒T��
	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		m_pObjArray[i]->SetActive( FALSE);
	}

	// ���ʂ̃v���V�[�W���|�C���^�z��̒T��
	for (DWORD i = 0; i < m_pProcArray.size(); i++)
	{
		m_pProcArray[i]->SetStartFlag(0);				// �J�n�t���O�̃��Z�b�g
		((CEffectProc*)m_pProcArray[i])->SetNonActive();      // ���ʂ̃v���V�[�W���̏����i�ċA�����j
	}
}
// ================================================================================================================================
// 
// �e�f�����ʃv���V�[�W�����̏���
// 
// ================================================================================================================================

//------------------------------------------------------------------------
//
//	�f�����ʁE�����v���V�[�W���̃R���X�g���N�^	
//
//   �Ȃ��A�v���V�[�W����delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
//------------------------------------------------------------------------
CEffectBomProc::CEffectBomProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	for (DWORD i = 0; i < EFFECT_BOM_MAX; i++)
	{
		m_pObjArray.push_back(new CEffectBomObj(m_pGMain));	// m_pObjArray�ɉf�����ʁE�����I�u�W�F�N�g�𐶐�����
	}

}
//-----------------------------------------------------------------------------
// �f�����ʁE�����v���V�[�W���̊J�n
//
//   VECTOR2 vPos    �����ʒu
//
//   �߂�l�@�@����ɔ��� : TRUE    �������Ȃ����� : FALSE
//-----------------------------------------------------------------------------
BOOL	CEffectBomProc::Start(VECTOR2 vPos)
{
	BOOL bRet = FALSE;

	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive() )
		{
			m_pObjArray[i]->Start(vPos);	// �f�����ʁE�����̔���
			m_pGMain->m_pSeHit->Play();
			bRet = TRUE;
			break;
		}
	}

	return TRUE;
}

//------------------------------------------------------------------------
//
//	�f�����ʁE�����I�u�W�F�N�g�̃R���X�g���N�^	
//
//  �����@�Ȃ�
//
//------------------------------------------------------------------------
CEffectBomObj::CEffectBomObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageSprite, 144, 480, 64, 64);
	m_nAnimNum = 7;
}
// ---------------------------------------------------------------------------
//
// �f�����ʁE�����I�u�W�F�N�g�̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CEffectBomObj::~CEffectBomObj()
{
	SAFE_DELETE(m_pSprite);
}
//-----------------------------------------------------------------------------
// �f�����ʁE�����I�u�W�F�N�g�̊J�n
//
//   VECTOR2 vPos    �����ʒu
//
//   �߂�l�@�@TRUE
//-----------------------------------------------------------------------------
BOOL	CEffectBomObj::Start(VECTOR2 vPos)
{
	m_bActive = TRUE;
	m_dwStatus = NORMAL;
	m_dwStatusSub = STOP;
	m_dwStatusPhase = 0;

	m_vPos = vPos;	// �����ʒu

	m_nAnimIdx = 0;

	return TRUE;
}
//-----------------------------------------------------------------------------
// �f�����ʁE�����I�u�W�F�N�g�̍X�V
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CEffectBomObj::Update()
{
	if (m_bActive)
	{
		if (AnimCountup() == 1)
		{
			m_bActive = FALSE;
		}
		Draw();

	}
}
// ==============================================================================================================

// =================================================================================
//------------------------------------------------------------------------
//
//	�A�C�e���v���V�[�W���̃R���X�g���N�^	
//
//   �Ȃ��A�v���V�[�W����delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
//------------------------------------------------------------------------
CItemProc::CItemProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	for (DWORD i = 0; i < ITEM_MAX; i++)
	{
		m_pObjArray.push_back(new CItemObj(m_pGMain));	// m_pObjArray�ɃA�C�e���𐶐�����
	}
	m_nStartFlag = 0;
}
// M.S �񕜂̃A�C�e���̔���
//��  ���F�����ʒu
//�߂�l�F�Ȃ�
void	CItemProc::RaiseResque(VECTOR2 vPos) {
	for (DWORD j = 0; j < m_pObjArray.size(); j++)
	{
		if (!m_pObjArray[j]->GetActive())
		{
			m_pObjArray[j]->Start(vPos, ITEMRESQUE);
			break;
		}
	}	
}
// M.S �h�A(�o��)�̔���
//��  ���F�����ʒu
//�߂�l�F�Ȃ�
void	CItemProc::RaiseDoor(VECTOR2 vPos) {
	for (DWORD j = 0; j < m_pObjArray.size(); j++)
	{
		if (!m_pObjArray[j]->GetActive())
		{
			m_pObjArray[j]->Start(vPos, ITEMDOOR);
			break;
		}
	}
}
// M.S �┓�̔���
//��  ���F�����ʒu
//�߂�l�F�Ȃ�
void	CItemProc::RaiseSilver(VECTOR2 vPos) {
	for (DWORD j = 0; j < m_pObjArray.size(); j++)
	{
		if (!m_pObjArray[j]->GetActive())
		{
			m_pObjArray[j]->Start(vPos, ITEMSILVER);
			break;
		}
	}
}
// M.S �����̔���
//��  ���F�����ʒu
//�߂�l�F�Ȃ�
void	CItemProc::RaiseGold(VECTOR2 vPos) {
	for (DWORD j = 0; j < m_pObjArray.size(); j++)
	{
		if (!m_pObjArray[j]->GetActive())
		{
			m_pObjArray[j]->Start(vPos, ITEMGOLD);
			break;
		}
	}
}
// M.S ���̍����̔���
//��  ���F�����ʒu
//�߂�l�F�Ȃ�
void	CItemProc::RaiseVision(VECTOR2 vPos) {
	for (DWORD j = 0; j < m_pObjArray.size(); j++)
	{
		if (!m_pObjArray[j]->GetActive())
		{
			m_pObjArray[j]->Start(vPos, ITEMVISION);
			break;
		}
	}
}
// M.S �������h�A(�S�[��)�̔���
//��  ���F�����ʒu
//�߂�l�F�Ȃ�
void	CItemProc::RaiseOseti(VECTOR2 vPos) {
	for (DWORD j = 0; j < m_pObjArray.size(); j++)
	{
		if (!m_pObjArray[j]->GetActive())
		{
			m_pObjArray[j]->Start(vPos, ITEMOSETI);
			break;
		}
	}
}
// M.S �������픭��
//��  ���F�����ʒu
//�߂�l�F�Ȃ�
void	CItemProc::RaiseSt(VECTOR2 vPos) {
	for (DWORD j = 0; j < m_pObjArray.size(); j++)
	{
		if (!m_pObjArray[j]->GetActive())
		{
			m_pObjArray[j]->Start(vPos, ITEMST);
			break;
		}
	}
}
//-----------------------------------------------------------------------------
// �A�C�e���v���V�[�W���̊J�n
//
//   �߂�l�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CItemProc::Update()
{
	VECTOR2 vPos;
	int  nNext;
	if (m_nStartFlag == 0) // ���������Ă����ǂ���
	{
		// �C�x���g�}�b�v��T�����A�񕜂�ݒ肷��
		nNext = 0;
		while (nNext != -1)
		{
			// �C�x���g�}�b�v�̒T�� (EvtID:2 �A�C�e���̏o���ʒu, EvtNo:0x10 ��)
			if (m_pGMain->m_pMapProc->SearchEvt(nNext, 2, 0x10, vPos, nNext))
			{
				RaiseResque(vPos);
			}
		}
		// �C�x���g�}�b�v��T�����A�h�A(�o��)��ݒ肷��
		nNext = 0;
		while (nNext != -1)
		{
			// �C�x���g�}�b�v�̒T�� (EvtID:2 �A�C�e���̏o���ʒu,EvtNo:0x20 �h�A)
			if (m_pGMain->m_pMapProc->SearchEvt(nNext, 2, 0x20, vPos, nNext))
			{
				RaiseDoor(vPos);
			}
		}		
		// M.S �C�x���g�}�b�v��T����,�┓��ݒ肷��
		nNext = 0;
		while (nNext != -1)
		{
			// M.S �C�x���g�}�b�v�̒T�� (EvtID:2 �A�C�e���̏o���ʒu, EvtNo:0x100 �┓)
			if (m_pGMain->m_pMapProc->SearchEvt(nNext, 2, 0x100, vPos, nNext))
			{
				RaiseSilver(vPos);
			}
		}
		// M.S �C�x���g�}�b�v��T����,������ݒ肷��
		nNext = 0;
		while (nNext != -1)
		{
			// M.S �C�x���g�}�b�v�̒T�� (EvtID:2 �A�C�e���̏o���ʒu, EvtNo:0x200 ����)
			if (m_pGMain->m_pMapProc->SearchEvt(nNext, 2, 0x200, vPos, nNext))
			{
				RaiseGold(vPos);
			}
		}
		// M.S �C�x���g�}�b�v��T����,���̍�����ݒ肷��
		nNext = 0;
		while (nNext != -1)
		{
			// M.S �C�x���g�}�b�v�̒T�� (EvtID:2 �A�C�e���̏o���ʒu, EvtNo:0x400 ���̍���)
			if (m_pGMain->m_pMapProc->SearchEvt(nNext, 2, 0x400, vPos, nNext))
			{
				RaiseVision(vPos);
			}
		}
		// M.S �C�x���g�}�b�v��T����,�������h�A(�S�[��)��ݒ肷��
		nNext = 0;
		while (nNext != -1)
		{
			// �C�x���g�}�b�v�̒T�� (EvtID:2 �A�C�e���̏o���ʒu, EvtNo:0x800 �������h�A�i�S�[��))
			if (m_pGMain->m_pMapProc->SearchEvt(nNext, 2, 0x800, vPos, nNext))
			{
				RaiseOseti(vPos);
			}
		}
		// M.S �C�x���g�}�b�v��T����,�������h�A(�S�[��)��ݒ肷��
		nNext = 0;
		while (nNext != -1)
		{
			// M.S �C�x���g�}�b�v�̒T��(EvtID:2 �A�C�e���̏o���ʒu, EvtNo:0x1000 ��������)
			if (m_pGMain->m_pMapProc->SearchEvt(nNext, 2, 0x1000, vPos, nNext))
			{
				RaiseSt(vPos);
			}
		}
		m_nStartFlag = 1;  // ��񔭂�������A�����������Ȃ�
	}
}

//------------------------------------------------------------------------
//
//	�A�C�e���I�u�W�F�N�g�̃R���X�g���N�^	
//
//  �����@�Ȃ�
//
//------------------------------------------------------------------------
CItemObj::CItemObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pSprite = new CSprite(m_pGMain->m_pImageSprite);  // �A�C�e���X�v���C�g�̃X�v���C�g�����
	m_nAnimNum = 1;

}
// ---------------------------------------------------------------------------
//
// �A�C�e���I�u�W�F�N�g�̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CItemObj::~CItemObj()
{
	SAFE_DELETE(m_pSprite);
}
//-----------------------------------------------------------------------------
// �A�C�e���I�u�W�F�N�g�̊J�n
//
//   VECTOR2 vPos    �����ʒu
//   DWORD       dwNo    �A�C�e�����
//
//   �߂�l�@�@TRUE
//-----------------------------------------------------------------------------
BOOL	CItemObj::Start(VECTOR2 vPos, DWORD dwNo)
{
	ResetStatus();
	ResetAnim();
	m_bActive = TRUE;
	m_dwStatusSub = dwNo;

	m_vPos = vPos;	// �����ʒu
	m_vPosUp = VECTOR2(0, 0);
	// �X�v���C�g�̏��̃Z�b�g
	switch (m_dwStatusSub)
	{
	case  ITEMRESQUE: // M.S ��
		m_pSprite->SetSrc(0, 0, 48, 48); 	
		break;
	case  ITEMDOOR:   // M.S�h�A
		m_pSprite->SetSrc(240, 0, 48, 48); 
		break;

	case ITEMVISION:  // M.S ���̍���
		m_pSprite->SetSrc(144, 0, 48, 48);
		break;

	case ITEMGOLD:    // M.S ����
	case ITEMSILVER:  // M.S �┓
		m_pSprite->SetSrc(96, 0, 48, 48);
		break;

	case ITEMOSETI:   // M.S �������h�A�i�S�[���j
		m_pSprite->SetSrc(192, 0, 48, 48);
		break;
		
	case ITEMST:      // M.S ����
		m_pSprite->SetSrc(48, 0, 48, 48);
	}

	return TRUE;
}
//-----------------------------------------------------------------------------
// �A�C�e���I�u�W�F�N�g�̍X�V
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CItemObj::Update()
{
	if (!m_bActive) {
		return;
	}
	if (isCollision(m_pGMain->m_pPcProc->GetPcObjPtr())) // PC�Ƃ̐ڐG����
	{
		switch (m_dwStatusSub)
		{
		case  ITEMRESQUE:     // ��
			m_pGMain->m_pPcProc->GetPcObjPtr()->SetHp(m_pGMain->m_pPcProc->GetPcObjPtr()->GetMaxHp());
			m_pGMain->m_pSePower->Play();
			m_bActive = FALSE;
			break;
		case  ITEMDOOR:      // �h�A
			// M.S �^�X�N���������Ă��邩����
			if ((m_pGMain->henk == 1) && (m_pGMain->m_pMapProc->m_nMapNo == 0)) {
				doorN = 1;
			}
			if ((m_pGMain->henk == 1) && (m_pGMain->hank == 1)) {
				keyN = 1;
			}
			if ((keyN == 1) && (m_pGMain->m_pMapProc->m_nMapNo == 1)) {
				secondN = 1;
			}
			 // M.S �i�����Ă���łȂ��ƁA�h�A��ʂ�Ȃ�
			if ((doorN == 1) || (secondN == 1) || (m_pGMain->m_pMapProc->m_nMapNo == 2)
				|| (m_pGMain->m_pMapProc->m_nMapNo == 3) || (m_pGMain->m_pMapProc->m_nMapNo == 4)) {
				if ((m_pGMain->m_pPcProc->GetPcObjPtr()->GetHp() >= 1) && (m_pGMain->m_pPcProc->GetPcNum() >= 0)) {
					m_pGMain->m_pSePower->Play();
					m_pGMain->m_pMapProc->MoveMap();
					m_pGMain->m_pPcProc->AddPcNum(1);
					m_bActive = FALSE;
					doorN = 0;
					secondN = 0;
					if (m_pGMain->m_pPcProc->GetPcNum() > 2) {  // M.S �c�@��2(MAX)��葽��������-1
						m_pGMain->m_pPcProc->AddPcNum(-1);
					}
				}
			}
			break;
		case ITEMSILVER:  // M.S �┓
			m_pGMain->m_pSePower->Play();
			m_pGMain->SilverS += 1;
			m_bActive = FALSE;
			break;
		case ITEMGOLD:    // M.S ����
			m_pGMain->m_pSePower->Play();
			m_pGMain->GoldS += 1;
			m_bActive = FALSE;
			break;
		case ITEMVISION:   // M.S ���̍���
			m_pGMain->m_pSePower->Play();
			m_pGMain->VisionS += 1;
			m_bActive = FALSE;
			break;
		case  ITEMOSETI:   // M.S �������h�A�i�S�[���j
			m_pGMain->m_dwGameStatus = GAMECLEAR;
			m_pGMain->CR = 1;
			m_pGMain->m_pSePower->Play();
			m_pGMain->m_pPcProc->AddPcNum(1);
			if (m_pGMain->m_pPcProc->GetPcNum() > 2) {  // M.S �c�@��2(MAX)��葽��������-1
				m_pGMain->m_pPcProc->AddPcNum(-1);
			}
			m_bActive = FALSE;
			break;
		case ITEMST:   			// M.S �A�C�e���w���̒ǉ��F��������
			m_pGMain->transactionW = true; // M.S �ŏ��̘b
			if (pDI->CheckKey(KD_DAT, DIK_E)) {
				if ((m_pGMain->GoldS >= 1) && (m_pGMain->SilverS >= 5)) { // M.S ��������
					m_pGMain->m_pSePower->Play();
					m_pGMain->strongSSw = true;
					m_pGMain->textStr = 1;
					m_pGMain->GoldS -= 1;
					m_pGMain->SilverS -= 5;
					m_pGMain->stS = 1;
					m_bActive = false;
				}
				else if (m_pGMain->textStr != 1) {  // M.S �����Ȃ������Ƃ�
					m_pGMain->textStr = 2;
				}
			}
			break;
		}
	}
	// M.S ���틭���V�[�� ���ꂽ��ŏ��ɖ߂��A�R�����g����
	else if ((!isCollision(m_pGMain->m_pPcProc->GetPcObjPtr())) && (m_pGMain->textStr != 1)) {  
			m_pGMain->transactionW = false;
			m_pGMain->textStr = 0;
	}
	// M.S ���틭���V�[�� ��������̃R�����g����莞�Ԃŏ���
	if ((m_pGMain->textStr == 1) && (m_pGMain->transactionW == true)) {  
		m_pGMain->timekon++;    // M.S �R�����g�\�����ԃJ�E���g�𑫂�
		if (m_pGMain->timekon > 80) {
			m_pGMain->transactionW = false;
		}
	}
	AnimCountup();
	Draw();
}


