//=============================================================================
//		�Q�c�A�N�V�����Q�[���v���O����
//		�b�Q�c�`�����P�P�S�@�@�@�@�@�@           ver 2.8        2020.2.15
//
//		�O�i�E��i����
//																BackFore.h
//=============================================================================

#pragma once

//�x����\��
#pragma warning(disable : 4005)
#pragma warning(disable : 4244)
#pragma warning(disable : 4018)

//�w�b�_�[�t�@�C���̃C���N���[�h
#include <stdio.h>
#include <windows.h>

#include "Main.h"
#include "Direct3D.h"
#include "XAudio.h"
#include "Dinput.h"
#include "Sprite.h"

//======================================================================
// �o�b�N�N���E���h�@�v���V�[�W���N���X
//
// (����)��{�v���V�[�W���N���X�͌p�����Ă��Ȃ�
//
//======================================================================
class CBackProc
{
protected:
public:
};
//======================================================================
// �t�H�A�N���E���h�@�v���V�[�W���N���X
//
// (����)��{�v���V�[�W���N���X�͌p�����Ă��Ȃ�
//
//======================================================================
class CForeProc
{
protected:
	CGameMain*		m_pGMain;
	CSprite*		m_pForegrd;
	CSprite*        ST;          // M.S ��������l���̃X�v���C�g
	CSprite*        m_pSchest;   // M.S �c�@�̃n�[�g�̃X�v���C�g
	CSprite*        m_pCMp3;      // M.S MP�̌I(1��)�̃X�v���C�g
	CSprite*        m_pCMp2;      // M.S MP�̌I(2��)�̃X�v���C�g
	CSprite*        m_pCMp1;      // M.S MP�̌I(3��)�̃X�v���C�g
public:
	void Update();
	CForeProc(CGameMain* pGMain);	// �R���X�g���N�^
	~CForeProc();
};