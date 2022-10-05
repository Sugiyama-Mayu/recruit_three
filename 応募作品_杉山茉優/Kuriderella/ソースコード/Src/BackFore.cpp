//=============================================================================
//		�Q�c�A�N�V�����Q�[���v���O����
//		�b�Q�c�`�����P�P�S�@�@�@�@�@�@           ver 2.8        2020.2.15
//
//		�O�i�E��i����
//																BackFore.cpp
//=============================================================================

#include "GameMain.h"
#include "Playchar.h"
#include "BackFore.h"


// ========================================================================================
//
// �O�i�̏���
//
//
// ========================================================================================
//------------------------------------------------------------------------
//
//	�O�i�v���V�[�W���̃R���X�g���N�^	
//
//  �����@CGameMain* pGMain
//
//------------------------------------------------------------------------
CForeProc::CForeProc(CGameMain* pGMain)
{
	m_pGMain = pGMain;
	m_pForegrd = new CSprite(m_pGMain->m_pShader);
	// M.S �c�@�̕\���X�v���C�g
	m_pSchest = new CSprite(m_pGMain->m_pImageChestHeart, 192, 0, 64, 64);
	// M.S MP�̌I�̃X�v���C�g(3��)
	m_pCMp3 = new CSprite(m_pGMain->m_pImageChestHeart, 0, 0, 192, 64);
	// M.S MP�̌I�̃X�v���C�g(2��)
	m_pCMp2 = new CSprite(m_pGMain->m_pImageChestHeart, 0, 0, 128, 64);
	// M.S MP�̌I�̃X�v���C�g(1��)
	m_pCMp1 = new CSprite(m_pGMain->m_pImageChestHeart, 0, 0, 64, 64);
	// M.S ��������̃X�v���C�g
	ST = new CSprite(m_pGMain->m_pImageSprite, 48, 0, 48, 48);
}
// ---------------------------------------------------------------------------
//
// �O�i�v���V�[�W���̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CForeProc::~CForeProc()
{
	SAFE_DELETE(m_pForegrd);
	SAFE_DELETE(m_pSchest);  // M.S �c�@�̃n�[�g�̃X�v���C�g
	SAFE_DELETE(m_pCMp3);     // M.S MP�̌I�̃X�v���C�g(3��)
	SAFE_DELETE(m_pCMp2);     // M.S MP�̌I�̃X�v���C�g(2��)
	SAFE_DELETE(m_pCMp1);     // M.S MP�̌I�̃X�v���C�g(1��)
	SAFE_DELETE(ST);         // M.S ��������l���̃X�v���C�g
}
//-----------------------------------------------------------------------------
// �O�i�v���V�[�W���̍X�V
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CForeProc::Update()
{
	CSpriteImage* pImageFore = m_pGMain->m_pImageSprite; // ���łɓǂݍ���ł���X�v���C�g�C���[�W���g�p����

	// M.S �g�o�Ƃl�o�̕\��
	TCHAR str[256];
	_stprintf(str, _T("%d"), m_pGMain->m_pPcProc->GetPcObjPtr()->GetHp());  // M.S HP�̕\��
	m_pGMain->m_pFont->Draw(64, 14, str, 50, RGB(127, 255, 212));
	int a = m_pGMain->m_pPcProc->GetPcNum();
	// M.S �c�@�̕\��
	if (m_pGMain->m_pPcProc->GetPcNum() >= 2) {                 
		m_pSchest->Draw(115, 3);
	}
	// M.S MP�̌I�̕\��(3��)
	if (m_pGMain->m_pPcProc->GetPcObjPtr()->GetMp() >= 900 ) {  
		m_pCMp3->Draw(1125, 0);
	}	
	// M.S MP�̌I�̕\��(2��)
	else if (m_pGMain->m_pPcProc->GetPcObjPtr()->GetMp() >= 600) {
		m_pCMp2->Draw(1125, 0);
	}
	// M.S MP�̌I�̕\��(1��)
	else if (m_pGMain->m_pPcProc->GetPcObjPtr()->GetMp() >= 300) {
		m_pCMp1->Draw(1125, 0);
	}
	
	if (m_pGMain->stS == 1) {    // M.S ��������̊l���摜�\��
		ST->Draw(200, 15);
	}
}