//=============================================================================
//		�Q�c�A�N�V�����Q�[���v���O����
//		�b�Q�c�`�����P�P�S�@�@�@�@�@�@           ver 2.8        2020.2.15
//
//		�f�����ʂ̏���
//																Effect.h
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

// M.S �e�A�C�e���̒ǉ�
#define  ITEMRESQUE   1           // M.S ��
#define  ITEMDOOR     2           // M.S �h�A
#define  ITEMSILVER   3           // M.S �┓
#define  ITEMGOLD     4           // M.S ����
#define  ITEMVISION   5           // M.S ���̍���
#define  ITEMOSETI    6           // M.S �������h�A
#define  ITEMST       7           // M.S ��������

#define  ITEM_MAX  50
#define  EFFECT_BOM_MAX  50
//======================================================================
// �f�����ʁE�����@�I�u�W�F�N�g�N���X
class CEffectBomObj : public CBaseObj
{
protected:
	;

public:
	BOOL Start(VECTOR2) override;

	void Update() override;

	// �R���X�g���N�^
	CEffectBomObj(CGameMain* pGMain);
	~CEffectBomObj();

};
//======================================================================
// �f�����ʁE�����@�v���V�[�W���N���X
class CEffectBomProc : public CBaseProc
{
public:
	BOOL Start(VECTOR2);

	CEffectBomProc(CGameMain* pGMain);	// �R���X�g���N�^
	~CEffectBomProc() { ; }	// �f�X�g���N�^

};
//=================================================================================================================
//======================================================================
// �A�C�e���@�I�u�W�F�N�g�N���X
class CItemObj : public CBaseObj
{
protected:
	//CDirectInput* pDI = m_pDI;
	CDirectInput* pDI = m_pGMain->m_pDI;
	int doorN, secondN, keyN = 0;
	
	
public:

	BOOL Start(VECTOR2, DWORD) override;
	void Update() override;

	// �R���X�g���N�^
	CItemObj(CGameMain* pGMain);
	~CItemObj();

};
//======================================================================
// �A�C�e���@�v���V�[�W���N���X
class CItemProc : public CBaseProc
{
public:
	// M.S �e�A�C�e���̔����֐�
	void RaiseResque(VECTOR2 vPos);  // M.S ��
	void RaiseDoor(VECTOR2 vPos);    // M.S �h�A
	void RaiseSilver(VECTOR2 vPos);  // M.S �┓
	void RaiseGold(VECTOR2 vPos);    // M.S ����
	void RaiseVision(VECTOR2 vPos);  // M.S ���̍���
	void RaiseOseti(VECTOR2 vPos);   // M.S �������h�A
	void RaiseSt(VECTOR2 vPos);      // M.S ��������

	void Update() override;
	CItemProc(CGameMain* pGMain);	// �R���X�g���N�^
	~CItemProc() { ; }	// �f�X�g���N�^
};
//=================================================================================================================
//======================================================================
// �f�����ʁ@�v���V�[�W���N���X
class CEffectProc : public CBaseProc
{
public:
	CEffectBomProc*		m_pEffectBomProc;

	CItemProc*			m_pItemProc;
	CSprite*     m_pSprite;   
public:
	void  SetNonActive();

	CEffectProc(CGameMain* pGMain);	// �R���X�g���N�^
	~CEffectProc() { ; }	// �f�X�g���N�^
};
