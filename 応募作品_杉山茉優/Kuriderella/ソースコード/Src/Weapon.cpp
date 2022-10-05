//=============================================================================
//		�Q�c�A�N�V�����Q�[���v���O����
//		�b�Q�c�`�����P�P�S�@�@�@�@�@�@           ver 2.8        2020.2.15
//
//      ����̏���
//																Weapon.cpp
//=============================================================================

#include "Weapon.h"
#include "Playchar.h"
#include "Enemy.h"
#include "Map.h"

//=============================================================================================================================
//
// ���탁�C���v���V�[�W���̃R���X�g���N�^
//
//   �Ȃ��A�v���V�[�W����delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
// ----------------------------------------------------------------------------------------------------------------------------
CWeaponProc::CWeaponProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	m_pWeaponShotProc = new CWeaponShotProc(m_pGMain);	// (PC)����E�V���b�g�v���V�[�W��
	m_pProcArray.push_back(m_pWeaponShotProc);     // �v���V�[�W�����v���V�[�W���z��ɓo�^����

	m_pEWeaponShotProc = new CEWeaponShotProc(m_pGMain); // (�G)����E�V���b�g�v���V�[�W��
	m_pProcArray.push_back(m_pEWeaponShotProc);     // �v���V�[�W�����v���V�[�W���z��ɓo�^����
} 
// ================================================================================================================================
// 
// �e�G�v���V�[�W�����̏���
// 
// ================================================================================================================================
//------------------------------------------------------------------------
//
//	����E�V���b�g�v���V�[�W���̃R���X�g���N�^	
//
//   �Ȃ��A�v���V�[�W����delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
//------------------------------------------------------------------------
CEWeaponShotProc::CEWeaponShotProc(CGameMain* pGMain) : CBaseProc(pGMain) //�G
{
	// ����E�V���b�g
	for (DWORD i = 0; i < WEAPON_ESHOT_MAX; i++)
	{
		m_pObjArray.push_back(new CEWeaponShotObj(m_pGMain)); // m_pObjArray�ɕ���E�V���b�g�I�u�W�F�N�g�𐶐�����
	}
	m_nWaitTime = m_nMaxwaitTime = 8;
}
CWeaponShotProc::CWeaponShotProc(CGameMain* pGMain) : CBaseProc(pGMain) //PC
{
	// ����E�V���b�g
	for (DWORD i = 0; i < WEAPON_SHOT_MAX; i++)
	{
		m_pObjArray.push_back(new CWeaponShotObj(m_pGMain)); // m_pObjArray�ɕ���E�V���b�g�I�u�W�F�N�g�𐶐�����
	}
	m_nWaitTime = m_nMaxwaitTime = 8;
}
//-----------------------------------------------------------------------------
BOOL CEWeaponShotProc::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner) //�G
{
	BOOL bRet = FALSE;
	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{			
				m_pObjArray[i]->Start(vPos, pObj, dwOwner);	// ����̔���
				m_pGMain->m_pSeHit->Play();
				bRet = TRUE;		
			break;
		}
	}
	if (bRet) m_pGMain->m_pSeShot->Play();

	//  (����)m_nWaitTime�̃J�E���g�_�E���́ACBaseProc�ōs���Ă���
	return bRet;
}
BOOL CWeaponShotProc::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner) //PC
{
	BOOL bRet = FALSE;
	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			m_pObjArray[i]->Start(vPos, pObj, dwOwner);	// ����̔���
			m_pGMain->m_pSeHit->Play();
			bRet = TRUE;
			break;
		}
	}
	if (bRet) m_pGMain->m_pSeShot->Play();

	//  (����)m_nWaitTime�̃J�E���g�_�E���́ACBaseProc�ōs���Ă���
	return bRet;
}
//------------------------------------------------------------------------
//
//	����E�V���b�g�I�u�W�F�N�g�̃R���X�g���N�^	
//
//  �����@�Ȃ�
//
//------------------------------------------------------------------------
CEWeaponShotObj::CEWeaponShotObj(CGameMain* pGMain) : CBaseObj(pGMain) //�G
{
	m_pSprite = new CSprite(m_pGMain->m_pWeaponImage, 0, 64, 32, 32); // ����摜
	m_nAnimNum = 8;
	m_nAtc = 1;
}
CWeaponShotObj::CWeaponShotObj(CGameMain* pGMain) : CBaseObj(pGMain) //PC
{
	m_pSprite = new CSprite(m_pGMain->m_pWeaponImage, 0, 32, 32, 32); // ����摜
	m_nAnimNum = 8;
	m_nAtc = 2;
}
// ---------------------------------------------------------------------------
//
// ����E�V���b�g�I�u�W�F�N�g�̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CEWeaponShotObj::~CEWeaponShotObj() //�G
{
	SAFE_DELETE(m_pSprite);
}
CWeaponShotObj::~CWeaponShotObj() //PC
{
	SAFE_DELETE(m_pSprite);
}
//-----------------------------------------------------------------------------
// ����E�V���b�g�I�u�W�F�N�g�̊J�n
//
//   VECTOR2 vPos    �����ʒu
//   CBaseObj*   pObj    ���ˌ��̃I�u�W�F�N�g
//   DWORD       dwOwner ���ˌ��̃I�u�W�F�N�g�敪
//
//   �߂�l�@�@TRUE
//-----------------------------------------------------------------------------
BOOL CEWeaponShotObj::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner) //�G
{
	float fSpeed = 8;	// �e�̑���
	m_bActive = TRUE;
	ResetStatus();
	ResetAnim();
	m_dwOwner = dwOwner;
	m_vPos = vPos;	// �����ʒu
	m_vPosUp = VECTOR2(0, 0);

	// M.S �v���C�L�����̈ʒu�ƒe��łʒu�̍���(X��)�����߂�
	VECTOR2 vPcPos;
	vPcPos.x = m_pGMain->m_pPcProc->GetPcObjPtr()->GetPos().x;
	m_pGMain->sabun = vPcPos.x - m_vPos.x;
	// M.S ��������v���C�L�����̕����֒e��ł�
	if (m_pGMain->sabun > 0) {
		m_vPosUp = VECTOR2(fSpeed, 0);
	}
	else {
		m_vPosUp = VECTOR2(-fSpeed, 0);
	}
	return TRUE;
}
BOOL CWeaponShotObj::Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner) //PC
{
	float fSpeed = 8;	// �e�̑���
	m_bActive = TRUE;
	ResetStatus();
	ResetAnim();
	m_dwOwner = dwOwner;
	m_vPos = vPos;	// �����ʒu
	m_vPosUp = VECTOR2(0, 0);

	if (m_pGMain->strongSSw == true) { // M.S ���킪��������Ă��邩�ǂ���
		m_pSprite = new CSprite(m_pGMain->m_pWeaponImage, 0, 0, 32, 32);
		m_nAtc = 3;
	}
	switch (pObj->GetDirIdx())
	{
	case UP:
		m_vPosUp = VECTOR2(0, -fSpeed);
		break;
	case DOWN:
		m_vPosUp = VECTOR2(0, fSpeed);
		break;
	case RIGHT:
		m_vPosUp = VECTOR2(fSpeed, 0);
		break;
	case LEFT:
		m_vPosUp = VECTOR2(-fSpeed, 0);
		break;
	}
	return TRUE;
}
//-----------------------------------------------------------------------------
// ����E�V���b�g�I�u�W�F�N�g�̍X�V
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
void CEWeaponShotObj::Update() //�G
{
	CMapLine*  pHitmapline = NULL;
	if (m_bActive)
	{
		switch (m_dwStatus)
		{
		case  NORMAL:
			m_pGMain->m_pPcProc->Hitcheck((CBaseObj*)this);
			BOOL swE;
			swE = m_pGMain->m_pMapProc->isCollisionMoveMap(this, pHitmapline);
			if (swE == TRUE) {
				m_bActive = FALSE;
			}
			if (m_vPos.x - m_pGMain->m_vScroll.x < 0 || m_vPos.x - m_pGMain->m_vScroll.x > WINDOW_WIDTH ||
				m_vPos.y - m_pGMain->m_vScroll.y < 0 || m_vPos.y - m_pGMain->m_vScroll.y > WINDOW_HEIGHT) {	// ��ʊO�֏o���̂ŏ���
				m_bActive = FALSE;
			}
			break;
		case  DAMAGE:
			m_bActive = FALSE;
			break;
		}
		m_vPos += m_vPosUp;
		AnimCountup();
		Draw();
	}
}
void CWeaponShotObj::Update() //PC
{
	CMapLine*  pHitmapline = NULL;
	BOOL swP;

	if (m_bActive)
	{
		switch (m_dwStatus)
		{
		case  NORMAL:
			m_pGMain->m_pEnmProc->Hitcheck((CBaseObj*)this);
			swP = m_pGMain->m_pMapProc->isCollisionMoveMap(this, pHitmapline);
			if (swP == TRUE) {
				m_bActive = FALSE;
			}
			if (m_vPos.x - m_pGMain->m_vScroll.x < 0 || m_vPos.x - m_pGMain->m_vScroll.x > WINDOW_WIDTH ||
				m_vPos.y - m_pGMain->m_vScroll.y < 0 || m_vPos.y - m_pGMain->m_vScroll.y > WINDOW_HEIGHT) {	// ��ʊO�֏o���̂ŏ���
				m_bActive = FALSE;
			}
			break;
		case  DAMAGE:
			m_bActive = FALSE;
			break;
		}
		m_vPos += m_vPosUp;
		AnimCountup();
		Draw();
	}
}
