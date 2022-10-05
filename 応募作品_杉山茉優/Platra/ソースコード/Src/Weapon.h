//=============================================================================
//		�R�c�Q�[���v���O����
//		�b�R�c�`�����P�P�Q�@�@�@�@�@�@                 ver 3.0        2021.1.11
//		����@�@�@�w�b�_�t�@�C��								Weapon.h
//=============================================================================
#pragma once

#include "GameMain.h"
#include "Effect.h"

#define  LASER_MAX          20
#define  FIREBALL_MAX       50
#define  FIREBALL_FIRE_MAX  10
#define  FLAME_MAX          100
#define  FLAME_FIRE_MAX     10
#define  BALL_MAX           200
#define  SPRAY_MAX          300
#define  HOLDITEM_MAX       15

// --------------------------------------------------------------------
//����@���[�U�[�@�I�u�W�F�N�g�N���X
// --------------------------------------------------------------------
class CWeaponLaserObj : public CBaseObj
{
protected:
	CFbxMesh*                m_pMesh;			// Fbx�X�^�e�B�b�N���b�V��
	VECTOR3                  m_vTarget;			// �^�[�Q�b�g
	VECTOR3                  m_vStart;			// ���ˈʒu
	VECTOR3                  m_vEnd;			// �ŏI���B�_
	DWORD                    m_dwOwner;			// ����𔭎˂����L�����敪�iPC:PC�@ENM:�G�j

public:
	BOOL Start(MATRIX4X4, DWORD dwOwner) override;
	void Update() override;
	void Render();

	// �A�N�Z�X�֐�
	void SetMesh(CFbxMesh*  pMesh) { m_pMesh = pMesh; }

	CWeaponLaserObj(CGameMain* pGMain);	// �R���X�g���N�^
	virtual	~CWeaponLaserObj();
};
// --------------------------------------------------------------------
//����@���[�U�[�@�v���V�[�W���N���X
// --------------------------------------------------------------------
class CWeaponLaserProc : public CBaseProc
{
protected:
	CFbxMesh*          m_pMesh;			// Fbx�X�^�e�B�b�N���b�V��
public:
	BOOL Start(MATRIX4X4, DWORD dwOwner);  //����@���[�U�[�̔���
	BOOL Start(MATRIX4X4 mGun, VECTOR3 vOffset, MATRIX4X4 mOwnerWorld, DWORD dwOwner);

	CWeaponLaserProc(CGameMain* pGMain);	// �R���X�g���N�^
	virtual	~CWeaponLaserProc();
};
// --------------------------------------------------------------------
//����@�΂̋ʁ@�I�u�W�F�N�g�N���X
// --------------------------------------------------------------------
class CWeaponFireBallObj : public CBaseObj
{
protected:
	CFbxMesh*               m_pMesh;			// Fbx�X�^�e�B�b�N���b�V��
	DWORD                    m_dwOwner;
	CBillFireObj*            m_pBillFire[FIREBALL_FIRE_MAX];
public:
	BOOL Start(VECTOR3 vStart, VECTOR3 vTarget, DWORD dwOwner) override;
	void Update() override;
	void Render();

	// �A�N�Z�X�֐�
	void SetMesh(CFbxMesh*  pMesh) { m_pMesh = pMesh; }

	CWeaponFireBallObj(CGameMain* pGMain);	// �R���X�g���N�^
	virtual	~CWeaponFireBallObj();
};
// --------------------------------------------------------------------
//����@�΂̋ʁ@�v���V�[�W���N���X
// --------------------------------------------------------------------
class CWeaponFireBallProc : public CBaseProc
{
protected:
	CFbxMesh*      m_pMesh;			// Fbx�X�^�e�B�b�N���b�V��
public:
	BOOL Start(VECTOR3 vStart, VECTOR3 vTarget, DWORD dwOwner);//����@�΂̋ʂ̔���

	CWeaponFireBallProc(CGameMain* pGMain);	// �R���X�g���N�^
	virtual	~CWeaponFireBallProc();
};

// --------------------------------------------------------------------
//����@���@�I�u�W�F�N�g�N���X
// --------------------------------------------------------------------
class CWeaponSwordObj : public CBaseObj
{
protected:
	DWORD           m_dwOwner;
public:
	BOOL Start(MATRIX4X4 mMat, VECTOR3 vMin, VECTOR3 vMax, DWORD dwOwner) override;
	void Update() override;
	void Render();

	CWeaponSwordObj(CGameMain* pGMain);	// �R���X�g���N�^
	virtual	~CWeaponSwordObj();
};
// --------------------------------------------------------------------
// ����@���@�v���V�[�W���N���X
// --------------------------------------------------------------------
class CWeaponSwordProc : public CBaseProc
{
public:
	BOOL Start(MATRIX4X4 mMat, VECTOR3 vMin, VECTOR3 vMax, DWORD dwOwner);	// ���̔���
	CWeaponSwordProc(CGameMain* pGMain);	// �R���X�g���N�^
	virtual	~CWeaponSwordProc() { ; }
};

// --------------------------------------------------------------------
//����@�Ή��@�I�u�W�F�N�g�N���X
// --------------------------------------------------------------------
class CWeaponFlameObj : public CBaseObj
{
protected:
	CFbxMesh*                m_pMesh;			// Fbx�X�^�e�B�b�N���b�V��
	DWORD                    m_dwOwner;
	CBillFireObj*            m_pBillFire[FLAME_MAX];
public:
	BOOL Start(VECTOR3 vStart, VECTOR3 vTarget, DWORD dwOwner) override;
	void Update() override;
	void Render();

	// �A�N�Z�X�֐�
	void SetMesh(CFbxMesh*  pMesh) { m_pMesh = pMesh; }

	CWeaponFlameObj(CGameMain* pGMain);	// �R���X�g���N�^
	virtual	~CWeaponFlameObj();
};
// --------------------------------------------------------------------
//����@�Ή��@�v���V�[�W���N���X
// --------------------------------------------------------------------
class CWeaponFlameProc : public CBaseProc
{
protected:
	CFbxMesh*      m_pMesh;			// Fbx�X�^�e�B�b�N���b�V��
public:
	BOOL Start(VECTOR3 vStart, VECTOR3 vTarget, DWORD dwOwner);//����@�Ή��̔���

	CWeaponFlameProc(CGameMain* pGMain);	// �R���X�g���N�^
	virtual	~CWeaponFlameProc();
};

// --------------------------------------------------------------------
//����@�{�[���@�I�u�W�F�N�g�N���X
// --------------------------------------------------------------------
class CWeaponBallObj : public CBaseObj
{
protected:
	CFbxMesh*      m_pMesh;			// Fbx�X�^�e�B�b�N���b�V��
	DWORD                    m_dwOwner;
public:
	BOOL Start(MATRIX4X4 mStartWorld, DWORD dwOwner) override;
	void Update() override;
	void Render();

	// �A�N�Z�X�֐�
	void SetMesh(CFbxMesh*  pMesh) { m_pMesh = pMesh; }

	CWeaponBallObj(CGameMain* pGMain);	// �R���X�g���N�^
	virtual	~CWeaponBallObj();
};
// --------------------------------------------------------------------
//����@�{�[���v���V�[�W���N���X
// --------------------------------------------------------------------
class CWeaponBallProc : public CBaseProc
{
protected:
	CFbxMesh*      m_pMesh;			// Fbx�X�^�e�B�b�N���b�V��
public:
	BOOL Start(MATRIX4X4 mGun, VECTOR3 vOffset, MATRIX4X4 mOwnerWorld, DWORD dwOwner);  //����@�{�[���̔���

	CWeaponBallProc(CGameMain* pGMain);	// �R���X�g���N�^
	virtual	~CWeaponBallProc();
};

// --------------------------------------------------------------------
//����@�X�v���[�@�I�u�W�F�N�g�N���X
// --------------------------------------------------------------------
class CWeaponSprayObj : public CBaseObj
{
protected:
	CSprite*            m_pSprite;		// �X�v���C�g
	DWORD               m_dwOwner;
public:
	BOOL Start(MATRIX4X4 mStartWorld, DWORD dwOwner) override;
	void Update() override;
	void Render();

	// �A�N�Z�X�֐�
	void CreateSprite(CSpriteImage*  pImage);

	CWeaponSprayObj(CGameMain* pGMain);	// �R���X�g���N�^
	virtual	~CWeaponSprayObj();
};
// --------------------------------------------------------------------
//����@�X�v���[�v���V�[�W���N���X
// --------------------------------------------------------------------
class CWeaponSprayProc : public CBaseProc
{
protected:
	CSpriteImage*       m_pImage;   // �X�v���C�g�C���[�W
public:
	BOOL Start(MATRIX4X4 mGun, VECTOR3 vOffset, MATRIX4X4 mOwnerWorld, DWORD dwOwner);  //����@�{�[���̔���

	CWeaponSprayProc(CGameMain* pGMain);	// �R���X�g���N�^
	virtual	~CWeaponSprayProc();
};

// --------------------------------------------------------------------
//����@��Ɏ��A�C�e���@�I�u�W�F�N�g�N���X
// --------------------------------------------------------------------
class CWeaponHoldObj : public CBaseObj
{
protected:
	int                      m_nKindNo;			// ��Ɏ��A�C�e���̎��(1:���@2:�e)
	CFbxMesh*                m_pMesh;			// Fbx���b�V��(�v���V�[�W���ł͂Ȃ��I�u�W�F�N�g�Ƀ��b�V������������)
	VECTOR3                  m_vOffset;			// �e���܂ł̃I�t�Z�b�g�i�e�̂݁j
public:
	void Init();
	BOOL Disp(MATRIX4X4 mHold, BASEHOLDITEM HoldItem);
	void GetInfo(MATRIX4X4 mHold, BASEHOLDITEM HoldItem, MATRIX4X4& mMat, VECTOR3& vOffset);
	void GetInfo(MATRIX4X4 mHold, BASEHOLDITEM HoldItem, MATRIX4X4& mMat, VECTOR3& vMin, VECTOR3& vMax);
	CBBox* GetBBox(MATRIX4X4 mHold, BASEHOLDITEM HoldItem);

	void Update() override;
	void Render();

	int GetKind() { return m_nKindNo; }

	CWeaponHoldObj(CGameMain* pGMain);	// �R���X�g���N�^
	virtual	~CWeaponHoldObj();
};
// --------------------------------------------------------------------
//����@��Ɏ��A�C�e���@�v���V�[�W���N���X
// --------------------------------------------------------------------
class CWeaponHoldProc : public CBaseProc
{
protected:
	;
public:
	BOOL Disp(MATRIX4X4 mHold, BASEHOLDITEM HoldItem); // ����@�̕\��
	void GetInfo(MATRIX4X4 mHold, BASEHOLDITEM HoldItem, MATRIX4X4& mMat, VECTOR3& vOffset);
	void GetInfo(MATRIX4X4 mHold, BASEHOLDITEM HoldItem, MATRIX4X4& mMat, VECTOR3& vMin, VECTOR3& vMax);
	CBBox* GetBBox(MATRIX4X4 mHold, BASEHOLDITEM HoldItem);
	int GetKind(BASEHOLDITEM HoldItem) { return ((CWeaponHoldObj*)m_pObjArray[HoldItem.m_nHoldObjNo])->GetKind(); }
	CWeaponHoldProc(CGameMain* pGMain);	// �R���X�g���N�^
	virtual	~CWeaponHoldProc();
};

// ======================================================================
// ����S�̂̃��C���v���V�[�W���N���X
// ======================================================================
class CWeaponProc : public CBaseProc
{
public:
	CWeaponLaserProc*     m_pWeaponLaserProc;
	CWeaponFireBallProc*  m_pWeaponFireBallProc;
	CWeaponSwordProc*     m_pWeaponSwordProc;
	CWeaponFlameProc*     m_pWeaponFlameProc;

	CWeaponBallProc*      m_pWeaponBallProc;
	CWeaponSprayProc*     m_pWeaponSprayProc;
	CWeaponHoldProc*      m_pWeaponHoldProc;

public:
	CWeaponProc(CGameMain* pGMain);	// �R���X�g���N�^
	virtual	~CWeaponProc() { ; }
};


