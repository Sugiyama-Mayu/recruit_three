//=============================================================================
//		�Q�c�A�N�V�����Q�[���v���O����
//		�b�Q�c�`�����P�P�S�@�@�@�@�@�@           ver 2.8        2020.2.15
//
//		��{�v���V�[�W���E��{�I�u�W�F�N�g�N���X����
//																BaseProc.h
//=============================================================================
#pragma once
#include "GameMain.h"

class CSprite;
class CGameMain;
// --------------------------------------------------------------------------------------------------
// ��{�I�u�W�F�N�g�N���X
// 
// ���@�I�u�W�F�N�g�Ƃ́A�Q�[�����ɓo�ꂷ����̕��́A�Ⴆ�΂o�b��A����̂P�Ȃǂ��w���B
// �@�@�Ȃ��A�I�u�W�F�N�g�́A�e�v���V�[�W���̃����o�[�z��Ƃ��Đ錾����
// 
// --------------------------------------------------------------------------------------------------
class CBaseObj
{
protected:
	CGameMain*		m_pGMain;			// �Q�[�����C���N���X�@�@
	DWORD			m_dwStatus;			// �X�e�[�^�X
	DWORD			m_dwStatusSub;		// �X�e�[�^�X�T�u
	DWORD			m_dwStatusPhase;	// �X�e�[�^�X�t�F�[�Y
	BOOL			m_bActive;			// TRUE:�\��  FALSE:��\��
	CSprite*		m_pSprite;			// �X�v���C�g�I�u�W�F�N�g
	//CSprite*        m_pESprite;         // �G�̒e�C���[�W
	VECTOR2			m_vPos;				// �\���ʒu
	VECTOR2			m_vPosUp;			// �\���ʒu�@�ړ�����
	VECTOR2			m_vOf;				// �\���ʒu�@�ړ��ψ�
	float			m_fRotate;			// ��]�p�x
	VECTOR2			m_vCenter;			// ��]���S
	VECTOR2			m_vTarget;			// �ړ��ړI�n
	float			m_fJumpTime;		// �W�����v����
	VECTOR2			m_vJumpSpeed;		// �W�����v�X�s�[�h
	float			m_fScale;			// �g��k��
	float			m_fAlpha;			// �����x
	int				m_nAnimNum;			// �A�j���[�V�����v�f��(�����l�͂Q)
	int				m_nAnimIdx;			// �A�j���[�V�����C���f�b�N�X��(�C���f�b�N�X�ʒu�͂w����)
	int				m_nAnimFrm;			// �A�j���[�V�����t���[���J�E���g
	int				m_nDirIdx;			// �����A�j���[�V�����C���f�b�N�X��(�C���f�b�N�X�ʒu�͂x����)
	int				m_nFlashIdx;		// �t���b�V���A�j���[�V�����C���f�b�N�X��
	int				m_nFlashFrm;		// �t���b�V���A�j���[�V�����t���[���J�E���g
	CBaseObj*		m_pOtherObj;		// �Ԃ���������̃I�u�W�F�N�g
	int				m_nCnt1;			// �ėp�J�E���^
	int				m_nCnt2;			// �ėp�J�E���^2
	int				m_nMaxHp;			// �ő�̗�
	int				m_nHp;				// �̗�
	int				m_nMaxMp;			// �ő喂��
	int				m_nMp;				// ����
	int				m_nAtc;				// �U����

public:
	virtual			void Update() { ; }
	virtual			void Draw();

	virtual			BOOL Start() { return TRUE; }
	virtual			BOOL Start(VECTOR2 vPos) { return TRUE; }
	virtual			BOOL Start(VECTOR2 vPos, DWORD dwOwner) { return TRUE; }
	virtual			BOOL Start(VECTOR2 vPos, CBaseObj* pObj, DWORD dwOwner) { return TRUE; }

	virtual			void  ResetStatus() final;
	virtual			void  ResetAnim() final;
	virtual			int  AnimCountup() final;
	virtual			int  FlashCountup() final;
	virtual			BOOL isCollision(CBaseObj*) final;
	virtual			BOOL isCollisionClick(int nMx, int nMy) final;
	virtual			BOOL Hitcheck(CBaseObj*);

	virtual			VECTOR2 GetCenterPos();

	// �ړI�n�֌������֐�
	virtual			BOOL TargetMove( float speed);

	// �A�N�Z�X�֐�
	BOOL	GetActive() { return m_bActive; }
	void	SetActive(BOOL bActive) { m_bActive = bActive; }
	DWORD	GetStatus() { return m_dwStatus; }
	CSprite* GetSprite() { return m_pSprite; }
	VECTOR2	GetPos() { return m_vPos; }				// �\���ʒu
	void    SetPos(VECTOR2 vPos) { m_vPos = vPos; }
	VECTOR2 GetPosUp() { return m_vPosUp; }
	void    SetPosUp(VECTOR2 vPosUp) { m_vPosUp = vPosUp; }
	VECTOR2 GetOf() { return m_vOf; }
	int		GetDirIdx() { return m_nDirIdx;	}
	int		GetMaxHp() { return m_nMaxHp; }
	int		GetHp() { return m_nHp; }
	void	SetHp(int nHp) { m_nHp = nHp; }
	int		GetMaxMp() { return m_nMaxMp; }
	int		GetMp() { return m_nMp; }
	void	SetMp(int nMp) { m_nMp = nMp; }
	int		GetAtc() { return m_nAtc; }


	// �R���X�g���N�^�i���ʃI�u�W�F�N�g�̏������j
	CBaseObj(CGameMain* pGMain);
	virtual ~CBaseObj();
};

// --------------------------------------------------------------------------------------------------
// ��{�v���V�[�W���N���X
//
//   ���@�v���V�[�W���Ƃ́A�u�����̏�������ɂ܂Ƃ߂����́v�Ƃ����Ӗ�
//       �����̃I�u�W�F�N�g�≺�ʃv���V�[�W�����R���g���[������N���X�̂���
//
// --------------------------------------------------------------------------------------------------
class  CBaseProc
{
protected:
	CGameMain*		m_pGMain;				// �Q�[�����C���N���X

	// 
	// ���ʂ̃v���V�[�W���|�C���^�z��́A�v���V�[�W�����K�w�\���ɂ��ĊǗ�����Ƃ��Ɏg�p����
	// �I�u�W�F�N�g�|�C���^�z��́A�v���V�[�W���̒��ɃI�u�W�F�N�g��z�u���ĊǗ�����Ƃ��Ɏg�p����
	// ��ʓI�ɂ́A�ǂ��炩�Е��݂̂��g�p���邱��
	// 
	std::vector<CBaseProc*>  m_pProcArray;  // ���ʂ̃v���V�[�W���|�C���^�z��
	std::vector<CBaseObj*>   m_pObjArray;	// �I�u�W�F�N�g�|�C���^�z��

	int				m_nMaxwaitTime;		// �ő�҂�����
	int				m_nWaitTime;		// ���݂̑҂�����
	int				m_nStartFlag;		// �J�n�t���O

public:
	// �S�̍X�V�����i�S�Ẵv���V�[�W����I�u�W�F�N�g��ǂ݉����čX�V����������j
	virtual void	UpdateAll() final;

	// �X�V�����iUpdateAll()�̒��ŋN���B�v���V�[�W���̍X�V�����j
	virtual void    Update() { ; }

	// �����蔻��i�S�Ẵv���V�[�W����I�u�W�F�N�g��ǂ݉����ď���������j
	virtual BOOL	Hitcheck(CBaseObj*) final;

	// �A�N�Z�X�֐�
	std::vector<CBaseProc*> GetProcArrayPtr() { return m_pProcArray; } // ���ʂ̃v���V�[�W���|�C���^�z��̃A�h���X��Ԃ�
	std::vector<CBaseObj*>  GetObjArrayPtr() { return m_pObjArray; }  // �I�u�W�F�N�g�|�C���^�z��̃A�h���X��Ԃ�

	int GetStartFlag(){ return m_nStartFlag;}
	void SetStartFlag(int nFlg) { m_nStartFlag = nFlg; }

	// �R���X�g���N�^�i��{�v���V�[�W���̏������j
	CBaseProc(CGameMain* pGMain) {
		m_pGMain = pGMain;		// �Q�[�����C���N���X
		m_nMaxwaitTime = 0;		// �ő�҂�����
		m_nWaitTime = 0;		// ���݂̑҂�����
		m_nStartFlag = 0;		// �J�n�t���O	
	}
	// �f�X�g���N�^�i�v���V�[�W���ƃI�u�W�F�N�g�̉���j
	virtual         ~CBaseProc();
};


