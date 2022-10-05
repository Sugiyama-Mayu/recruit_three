//=============================================================================
//		�Q�c�A�N�V�����Q�[���v���O����
//		�b�Q�c�`�����P�P�S�@�@�@�@�@�@           ver 2.8        2020.2.15
//
//      �I�[�v�j���O�^�C�g���E�Q�[���N�����[�E�Q�[���I�[�o�[�̏���
//																Title.h
//=============================================================================

#pragma once

#include "GameMain.h"

// --------------------------------------------------------------------
// �^�C�g���@�v���V�[�W���N���X
// --------------------------------------------------------------------
class CTitleProc : public CBaseProc
{
protected:
	CGameMain*		m_pGMain;

	CSpriteImage*   m_pImageTitle;
	CSpriteImage*   m_pImageClear;
	CSpriteImage*   m_pImageOver;
	CSprite*        m_pSprite;
	CSprite*        m_pScore;  // M.S �X�R�A�g

	DWORD           m_dwCntTime;
public:
	void Title();
	void GameClear();
	void GameOver();
	CTitleProc(CGameMain* pGMain);	// �R���X�g���N�^
	~CTitleProc();

	int s1[1], s2[1], s3[1]; // M.S �����L���O�\���̂��߂̔z��
};

