//=============================================================================
//		�Q�c�A�N�V�����Q�[���v���O����
//		�b�Q�c�`�����P�P�S�@�@�@�@�@�@           ver 2.8        2020.2.15
//
//		�G�̏���
//																Enamy.h
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

#define  ENM_WATER_MAX  30
#define  ENM_TORD_MAX  20
#define  ENM_WOLF_MAX  20
#define  ENM_FOX_MAX  20
#define  ENM_KING_MAX 20
#define  ENM_DOS_MAX 20
#define  ENM_SKY_MAX 20
//======================================================================
// ���̓G�@�I�u�W�F�N�g�N���X
class CEnmWaterObj : public CBaseObj
{
protected:
	;
public:
	BOOL Start(VECTOR2 vPos) override;
	void Update() override;

	// �R���X�g���N�^
	CEnmWaterObj(CGameMain* pGMain);
	~CEnmWaterObj();
};
//======================================================================
// ���̓G�@�v���V�[�W���N���X
class CEnmWaterProc : public CBaseProc
{
protected:
	;
public:
	void   Update() override;

	// �R���X�g���N�^
	CEnmWaterProc(CGameMain* pGMain);
	~CEnmWaterProc() { ; }
};
//======================================================================
// �D�F�̓G�@�I�u�W�F�N�g�N���X
class CEnmTordObj : public CBaseObj
{
protected:
	;
public:
	BOOL Start(VECTOR2 vPos) override;
	void Update() override;

	// �R���X�g���N�^
	CEnmTordObj(CGameMain* pGMain);
	~CEnmTordObj();
};
//======================================================================
// �D�F�̓G�@�v���V�[�W���N���X
class CEnmTordProc : public CBaseProc
{
protected:
	;
public:
	void   Update() override;

	// �R���X�g���N�^
	CEnmTordProc(CGameMain* pGMain);
	~CEnmTordProc() { ; }
};
//======================================================================
// �ԐF�̓G�@�I�u�W�F�N�g�N���X
class CEnmWolfObj : public CBaseObj
{
protected:
	;
public:
	BOOL Start(VECTOR2 vPos) override;
	void Update() override;

	// �R���X�g���N�^
	CEnmWolfObj(CGameMain* pGMain);
	~CEnmWolfObj();
};
//======================================================================
// �ԐF�̓G�@�v���V�[�W���N���X
class CEnmWolfProc : public CBaseProc
{
protected:
	;
public:
	void   Update() override;

	// �R���X�g���N�^
	CEnmWolfProc(CGameMain* pGMain);
	~CEnmWolfProc() { ; }
};
//======================================================================
// �ΐF�̓G�@�I�u�W�F�N�g�N���X
class CEnmFoxObj : public CBaseObj
{
protected:
	;
public:
	BOOL Start(VECTOR2 vPos) override;
	void Update() override;
	int RandomNumAns(int num); // M.S ������0�`2�̐��ɂ���
	int num = 0;     // M.S �����_���ϐ�(0�`9)
	int returnNum;   // M.S num��0�`2�̒l�ɕς����ϐ�

	// �R���X�g���N�^
	CEnmFoxObj(CGameMain* pGMain);
	~CEnmFoxObj();
};
//======================================================================
// �ΐF�̓G�@�v���V�[�W���N���X
class CEnmFoxProc : public CBaseProc
{
protected:
	;
public:
	void   Update() override;

	// �R���X�g���N�^
	CEnmFoxProc(CGameMain* pGMain);
	~CEnmFoxProc() { ; }
};
//======================================================================
// M.S �h�b�X���̓G�@�I�u�W�F�N�g�N���X
class CEnmDosObj : public CBaseObj
{
protected:
	;
public:
	BOOL Start(VECTOR2 vPos) override;
	void Update() override;

	// �R���X�g���N�^
	CEnmDosObj(CGameMain* pGMain);
	~CEnmDosObj();
};
//======================================================================
// M.S �h�b�X���̓G�@�v���V�[�W���N���X
class CEnmDosProc : public CBaseProc
{
protected:
	;
public:
	void   Update() override;

	// �R���X�g���N�^
	CEnmDosProc(CGameMain* pGMain);
	~CEnmDosProc() { ; }
};
//======================================================================
// M.S �{�X�̓G�@�I�u�W�F�N�g�N���X
class CEnmKingObj : public CBaseObj
{
protected:
	;
public:
	BOOL Start(VECTOR2 vPos) override;
	void Update() override;
	int eWaitNum;  // M.S �e���ˑ҂�����

	// �R���X�g���N�^
	CEnmKingObj(CGameMain* pGMain);
	~CEnmKingObj();
};
//======================================================================
// M.S �{�X�̓G�@�v���V�[�W���N���X
class CEnmKingProc : public CBaseProc
{
protected:
	;
public:
	void   Update() override;

	// �R���X�g���N�^
	CEnmKingProc(CGameMain* pGMain);
	~CEnmKingProc() { ; }
};
//======================================================================
// M.S �����̃I�u�W�F�N�g�N���X
class CEnmSkyObj : public CBaseObj
{
protected:
	;
public:
	BOOL Start(VECTOR2 vPos) override;
	void Update() override;

	// �R���X�g���N�^
	CEnmSkyObj(CGameMain* pGMain);
	~CEnmSkyObj();
};
//======================================================================
// M.S �����̃v���V�[�W���N���X
class CEnmSkyProc : public CBaseProc
{
protected:
	;
public:
	void   Update() override;

	// �R���X�g���N�^
	CEnmSkyProc(CGameMain* pGMain);
	~CEnmSkyProc() { ; }
};
//======================================================================
// �G�L�����N�^�[�S�̂̃��C���v���V�[�W���N���X
//======================================================================
class CEnmProc : public CBaseProc
{
public:
	CEnmWaterProc*	m_pEnmWaterProc;// ���̓G�̃v���V�[�W��
	CEnmTordProc*	m_pEnmTordProc; // �D�F�̓G�̃v���V�[�W��
	CEnmWolfProc*	m_pEnmWolfProc; // �ԐF�̓G�̃v���V�[�W��
	CEnmFoxProc*	m_pEnmFoxProc;  // �ΐF�̓G�̃v���V�[�W��
	CEnmDosProc*    m_pEnmDosProc;  // M.S �h�b�X���̓G�̃v���V�[�W��
	CEnmKingProc*   m_pEnmKingProc; // M.S �{�X�̓G�̃v���V�[�W��
	CEnmSkyProc*    m_pEnmSkyProc;  // M.S �����̃v���V�[�W��
public:
	void  SetNonActive();
	CEnmProc(CGameMain* pGMain);	// �R���X�g���N�^
	~CEnmProc() { ; }
};