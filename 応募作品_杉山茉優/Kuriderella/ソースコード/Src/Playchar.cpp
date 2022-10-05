//=============================================================================
//		�Q�c�A�N�V�����Q�[���v���O����
//		�b�Q�c�`�����P�P�S�@�@�@�@�@�@           ver 2.8        2020.2.15
//
//		�v���C�L�����N�^�[�̏���
//																Playchar.cpp
//=============================================================================

#include "Playchar.h"
#include "Weapon.h"
#include "Effect.h"
#include "Map.h"

//------------------------------------------------------------------------
//
//	�o�b�v���V�[�W���̃R���X�g���N�^	
//
//   �Ȃ��A�I�u�W�F�N�g��delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
//------------------------------------------------------------------------
CPcProc::CPcProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	m_pPcObj = new CPcObj(m_pGMain);
	m_pObjArray.push_back(m_pPcObj);  // m_pObjArray�ɃI�u�W�F�N�g��o�^����

	m_nMaxPcNum  = m_nPcNum = 2;
}
// ===========================================================================
//------------------------------------------------------------------------
//
//	�o�b�I�u�W�F�N�g�̃R���X�g���N�^	
//
//  �����@CGameMain* pGMain
//
//------------------------------------------------------------------------
CPcObj::CPcObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	// �����I(����)�̃X�v���C�g
	m_pSprite = new CSprite(m_pGMain->m_pImageChar, 0, 0, 64, 64);

	m_vPos = VECTOR2(48, 721 );
	ResetStatus();
	ResetAnim();
	m_bActive = TRUE;
	m_nDirIdx = RIGHT;
	m_nHp = m_nMaxHp = 3;
	m_nMaxMp = m_nMp = 900;
	m_nAtc = 1;

	m_nShotWait = 0;
}
// ---------------------------------------------------------------------------
//
// �o�b�I�u�W�F�N�g�̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CPcObj::~CPcObj()
{
	SAFE_DELETE(m_pSprite);
}
//M.S �v���C�L�����̏�ԕω��̏���
//��  ���F�Ȃ�
//�߂�l�F�Ȃ�
void CPcObj::ChangeStatePC() {
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
		m_nMp += 5;  // Mp�̎��R����
		if (m_nMp >= m_nMaxMp) {
			m_nMp = m_nMaxMp;
		}
		if (m_pGMain->henk == 1) {
			// M.S �I�̃X�v���C�g�ɕύX
			m_pSprite = new CSprite(m_pGMain->m_pImageChar, 128, 0, 64, 64);
		}
		if (m_pGMain->hank == 1 && m_pGMain->henk == 1) {
			// M.S �I����Ƃ�̃X�v���C�g�ɕύX
			m_pSprite = new CSprite(m_pGMain->m_pImageChar, 256, 0, 64, 64);
		}
		break;
	case DAMAGE:
		if (m_pOtherObj->GetAtc() > 0)
		{
			m_nHp -= m_pOtherObj->GetAtc();	// �U�����󂯂��_���[�W
			if (m_nHp <= 0)
			{
				m_nHp = 0;
				m_dwStatus = DEAD;		// HP���O�Ȃ̂Ŏ��S��
				m_nCnt1 = 180;			// ���S�t���b�V�����̎��Ԑݒ�
			}
			else {
				m_dwStatus = FLASH;
				m_nCnt1 = 60;
			}
		}
		else {
			m_dwStatus = NORMAL;  // �U���͂Ȃ��̂Ƃ��͂�����NORMAL�ɖ߂�
		}
		break;
	case DEAD:
		m_nCnt1--;
		if (m_nCnt1 <= 0)
		{
			m_pGMain->m_pPcProc->AddPcNum(-1);	// �o�b����l���炷
			if (m_pGMain->m_pPcProc->GetPcNum() <= 0)	// �o�b���Ȃ��Ȃ����̂ŃQ�[���I�[�o�[
			{
				m_pGMain->m_dwGameStatus = GAMEOVER;
			}
			else {
				m_nHp = m_nMaxHp;
				ResetStatus();
				ResetAnim();
			}
		}
		else {
			FlashCountup();
		}
		break;
	}
}
//-----------------------------------------------------------------------------
// �o�b�I�u�W�F�N�g�̍X�V
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CPcObj::Update()
{
	CDirectInput* pDI = m_pGMain->m_pDI;
	CMapLine*  pHitmapline = NULL;
	float fSpeed     = 5;
	float fJumpPlus  = 4;

	if (!m_bActive) return;
	m_vPosUp = VECTOR2(0, 0);

	ChangeStatePC(); //M.S �v���C�L�����̏�ԕω��̏���

	// �v���C�L�����̈ړ�����
	switch (m_dwStatusSub)
	{
	case  WALK:		// ���s���̏���
		if (pDI->CheckKey(KD_DAT, DIK_RIGHT))//���L�[
		{
			m_vPosUp.x = fSpeed;
			m_nDirIdx = RIGHT;
		}
		if (pDI->CheckKey(KD_DAT, DIK_LEFT))//���L�[
		{
			m_vPosUp.x = -fSpeed;
			m_nDirIdx = LEFT;
		}
		// �W�����v�J�n
		if (pDI->CheckKey(KD_DAT, DIK_SPACE))//�X�y�[�X�L�[
		{	
			m_dwStatusSub = JUMP;
			m_vJumpSpeed.x = m_vPosUp.x;
			m_vJumpSpeed.y = -(fSpeed*2.5 + fJumpPlus);
			m_fJumpTime = 0;
			m_vPosUp.y = m_vJumpSpeed.y;
		}
		else {// ���R����
			if (pDI->CheckKey(KD_DAT, DIK_DOWN))//���L�[
			{
				m_vPosUp.y = fSpeed;
			}
			else {
				m_dwStatusSub = JUMP;
				m_vJumpSpeed.x = m_vPosUp.x;
				m_vJumpSpeed.y = fSpeed / 2;
				m_fJumpTime = 0;
				m_vPosUp.y = m_vJumpSpeed.y;
			}
		}
		break;
	case  JUMP:		// �W�����v���̏���
		if (pDI->CheckKey(KD_DAT, DIK_RIGHT))//���L�[
		{
			m_vJumpSpeed.x = fSpeed;
			m_nDirIdx = RIGHT;
		}
		if (pDI->CheckKey(KD_DAT, DIK_LEFT))//���L�[
		{
			m_vJumpSpeed.x = -fSpeed;
			m_nDirIdx = LEFT;
		}
		m_fJumpTime++;
		m_vPosUp.x = m_vJumpSpeed.x;
		m_vPosUp.y = round(m_vJumpSpeed.y + GRAVITY * m_fJumpTime);
		break;
	}
	// �V���b�g�̔���
	if (pDI->CheckKey(KD_DAT, DIK_A))
	{
		if (m_nShotWait <= 0 && m_nMp >= 300) 
		{
			m_pGMain->m_pWeaponProc->m_pWeaponShotProc->
				Start(m_vPos+VECTOR2(20, 20), this, PC);
			m_nShotWait = 10;    // ���픭�˂̃E�F�C�g���|����
			m_nMp -= 300;        // M.S MP�����炷
			if (m_nMp < 0) {    
				m_nMp = 0;
			}
		}
	}
	if (m_nShotWait > 0) m_nShotWait--;    // ���픭�˂̃E�F�C�g���J�E���g�_�E��

	// �}�b�v���Ƃ̐ڐG����ƓK�؂Ȉʒu�ւ̈ړ�
	if (m_pGMain->m_pMapProc->isCollisionMoveMap(this, pHitmapline))
	{
		if (pHitmapline && pHitmapline->m_vNormal.y <= 0)	// �}�b�v���������܂ł͂n�j
		{
			m_dwStatusSub = WALK;	// �}�b�v���ɐڐG���Ă���Ƃ��́A�W�����v����s�ɖ߂�
			m_fJumpTime = 0;
			m_vJumpSpeed.x = m_vJumpSpeed.y = 0;
		}
	}
	// �����v�Z
	m_vPos += m_vPosUp;

	AnimCountup();
	Draw();
}
