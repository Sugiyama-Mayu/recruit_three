//=============================================================================
//		�Q�c�A�N�V�����Q�[���v���O����
//		�b�Q�c�`�����P�P�S�@�@�@�@�@�@           ver 2.8        2020.2.15
//
//      ����̏���
//																Weapon.h
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

#define  WEAPON_SHOT_MAX  200
#define  WEAPON_ESHOT_MAX 200
//======================================================================
// (PC)����E�V���b�g�@�I�u�W�F�N�g�N���X
class CWeaponShotObj : public CBaseObj
{
protected:
	DWORD  m_dwOwner;

public:
	BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwOwner) override;
	void Update() override;

	// �R���X�g���N�^
	CWeaponShotObj(CGameMain* pGMain);
	~CWeaponShotObj();
};
//======================================================================
// (PC)����E�V���b�g�@�v���V�[�W���N���X
class CWeaponShotProc : public CBaseProc
{
public:
	BOOL Start( VECTOR2, CBaseObj* pObj, DWORD dwOwner);

	CWeaponShotProc(CGameMain* pGMain);	// �R���X�g���N�^
	~CWeaponShotProc() { ; }
};
//======================================================================
// M.S (�G)����E�V���b�g�@�I�u�W�F�N�g�N���X
class CEWeaponShotObj : public CBaseObj
{
protected:
	DWORD  m_dwOwner;
	bool bRet;

public:
	BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwOwner) override;
	void Update() override;
	
	// �R���X�g���N�^
	CEWeaponShotObj(CGameMain* pGMain);
	~CEWeaponShotObj();
};
//======================================================================
// M.S (�G)����E�V���b�g�@�v���V�[�W���N���X
class CEWeaponShotProc : public CBaseProc
{
public:
	BOOL Start(VECTOR2, CBaseObj* pObj, DWORD dwOwner);

	CEWeaponShotProc(CGameMain* pGMain);	// �R���X�g���N�^
	~CEWeaponShotProc() { ; }
};
//======================================================================
// ����S�̂̃��C���v���V�[�W���N���X
//======================================================================
class CWeaponProc : public CBaseProc
{
public:
	CWeaponShotProc*	m_pWeaponShotProc;  // PC�̕���v���V�[�W��
	CEWeaponShotProc*   m_pEWeaponShotProc; // M.S �G�̕���v���V�[�W��

public:
	CWeaponProc(CGameMain* pGMain);	// �R���X�g���N�^
	~CWeaponProc() { ; }
};
