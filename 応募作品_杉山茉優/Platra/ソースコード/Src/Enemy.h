//=============================================================================
//		�R�c�Q�[���v���O����
//		�b�R�c�`�����P�P�Q�@�@�@�@�@�@                 ver 3.0        2021.1.11
//		�G�L�����N�^�[�@�w�b�_�t�@�C��							Enemy.h
//=============================================================================
#pragma once
#include "GameMain.h"
#include "Map.h"

// �G�̂h�c�Ɣ�����
// 
//   ID    :�G�̂h�c�B�P���珇�ԂɐU��
//   MAX   :�G�I�u�W�F�N�g�̐��B�i�����������j
//   ALLMAX:�G�̍ő�o�����B�i�������܂߂�j
// 
#define  ENM_GOLEM_ID        1
#define  ENM_GOLEM_MAX       6
#define  ENM_GOLEM_ALLMAX    6

#define  ENM_RS_ID           2
#define  ENM_RS_MAX          6
#define  ENM_RS_ALLMAX       6

#define  ENM_BD_ID           3
#define  ENM_BD_MAX          6
#define  ENM_BD_ALLMAX       6

//======================================================================
// �G�S�[�����@�I�u�W�F�N�g�N���X
//======================================================================
class CEnmGolemProc;
class CEnmGolemObj : public CBaseObj
{
protected:
	CFbxMesh*			m_pMesh;		// Fbx�X�L�����b�V��
	BASEHOLDITEM		m_nHoldItem;	// ��Ɏ��A�C�e��    // -- 2021.2.4
	VECTOR3				m_vTarget;		// �^�[�Q�b�g
	NAVIGATIONMAP		m_Nav;			// �i�r�Q�[�V�����}�b�v
	
public:
	//
	BOOL Start() override;
	void Update() override;
	void UpdateNormal();
	void UpdateDamage();
	void UpdateDead();
	void SetMesh(CEnmGolemProc* pProc);                 // -- 2021.2.4
	void SetNav(NAVIGATIONMAP  Nav) { m_Nav = Nav; }
	CEnmGolemObj(CGameMain* pGMain);	// �R���X�g���N�^
	virtual	~CEnmGolemObj();	// �f�X�g���N�^

	void OutUpPos();  // M.S �v���C�L�����Ɛl����ɂ����Ƃ���ʒu���o���֐�
	// M.S �l�I�u�W�F�N�g��`�悷��֐�
	void DoRenderHigh() { m_pMesh->Render(m_AnimStatus, m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt, 0); }
	// M.S �l�I�u�W�F�N�g�̃A�j���[�V�����̒�~�A�Đ�
	void SetPlayAnimHigh(bool set) { m_AnimStatus.playAnim = set; }

	bool doneProcess;   // M.S �z�u���Ă��邩�t���O
	bool alive;          // M.S ����ԏ����t���O
	int manSurfaceNum;	    // M.S �l�I�u�W�F�N�g������ʂ̐���
	int thisManArrayNumber; // M.S �z�u�������Ԃ̕ۑ�
	MATRIX4X4 manRotate;    // M.S �v���C�L�����̕�����������]�}�g���b�N�X
	MATRIX4X4 manRotateOld; // M.S ����������߂��}�g���b�N�X
	bool initialProcess;  // M.S �ŏ��݂̂̏����t���O
	// M.S �v���C�L�����̕�������������p�x���}�b�v�̉�]�ɍ��킹�Ē�������ϐ�
	float initialRotate; 
	// M.S 0:�܂�����ɒʉߍς݉w���H���Ȃ� 1:����ɒʉߍς݉w���H������ 3:��荞�݃A�j���[�V�����Ə������I��
	int initialDeadAnim; 
	// M.S ��ԃA�j���[�V�����̃^�C���J�E���g
	int animCount;
	// M.S ��ԃA�j���[�V�����̎���
	int saveAnimCount;
	// M.S ��]�p�x�t���O
	bool rotate0;    // M.S 0�x
	bool rotate90;   // M.S 90�x
	bool rotate180;  // M.S 180�x
	bool rotate270;  // M.S 270�x
	VECTOR3 pcPos;    // M.S �v���C�L�����̈ʒu
	VECTOR3 manPos;   // M.S �l�I�u�W�F�N�g�̈ʒu
};
// ------------------------------------
// �G�S�[�����@�v���V�[�W���N���X
// ------------------------------------
class CEnmGolemProc : public CBaseProc
{
protected:
	CFbxMesh*           m_pMesh;		// Fbx�X�L�����b�V��
	BASEHOLDITEM        m_nHoldItem;	// ��Ɏ��A�C�e��    // -- 2021.2.4	
public:
	void Update() override;
	CFbxMesh*       GetMesh() { return m_pMesh; }		// Fbx�X�L�����b�V��
	BASEHOLDITEM    GetHoldItem() { return m_nHoldItem; }	// ��Ɏ��A�C�e���̒l    // -- 2021.2.4
	CEnmGolemProc(CGameMain* pGMain);	// �R���X�g���N�^
	virtual	~CEnmGolemProc();	// �f�X�g���N�^

	// M.S �l�I�u�W�F�N�g�̃|�C���^�̎擾
	CEnmGolemObj* GetHighManObjPtr(int i) { return (CEnmGolemObj*)GetObjArrayPtr()[i]; }
	// M.S �l�I�u�W�F�N�g�̈ʒu�̃Z�b�g
	void SetWorld(MATRIX4X4 m_mWorld, int i) { m_pObjArray[i]->SetWorld(m_mWorld); }
	// M.S �l�I�u�W�F�N�g�̈ʒu�̎擾
	MATRIX4X4 GetWorld(int i) { return m_pObjArray[i]->GetWorld(); }
	void ResetPlacementMan();  // M.S �L�����̍ŏ��̔z�u�ʒu�̔r�o
	// M.S �v�f�̐������ʂ̐���
	int numH[6];          // M.S �e�ʂ̔z�u����s�������Ă���z��
	int numV[6];          // M.S �e�ʂ̔z�u����񂪓����Ă���z��
	int PlacementManMap[6] = { 0 };  // M.S �z�u�����ʂ̊m�F�z��
	int manNum;                  // M.S �z�u�ςݐl��
	bool exclusiveMan;           // M.S �z�u���t���O
	int surfaceNumTarget;        // M.S ���ׂ�ʂ̐���
	bool managementDeadProcess;  // M.S ��ԏ������t���O
};

//======================================================================
// �G�q�r�@�I�u�W�F�N�g�N���X
//======================================================================
class CEnmRSProc;
class CEnmRSObj : public CBaseObj
{
protected:
	CFbxMesh*			m_pMesh;	// Fbx�X�L�����b�V��
	BASEHOLDITEM        m_nHoldItem;	// ��Ɏ��A�C�e��
	VECTOR3				m_vTarget;	// �^�[�Q�b�g
	NAVIGATIONMAP		m_Nav;		// �i�r�Q�[�V�����}�b�v

public:
	BOOL Start() override;
	void Update() override;
	void UpdateNormal();
	void UpdateDamage();
	void UpdateDead();
	void SetMesh(CEnmRSProc* pProc);
	void SetNav(NAVIGATIONMAP  Nav) { m_Nav = Nav; }
	CEnmRSObj(CGameMain* pGMain);	// �R���X�g���N�^
	virtual	~CEnmRSObj();	// �f�X�g���N�^

	void OutUpPos();     // M.S �v���C�L�����Ɛl����ɂ����Ƃ���ʒu���o���֐�
	// M.S �l�I�u�W�F�N�g��`�悷��֐�
	void DoRenderMiddle() { m_pMesh->Render(m_AnimStatus, m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt, 0); }
	// M.S �l�I�u�W�F�N�g�̃A�j���[�V�����̒�~�A�Đ�
	void SetPlayAnimMiddle(bool set) { m_AnimStatus.playAnim = set; }

	bool doneProcess;        // M.S �z�u���Ă��邩�t���O
	bool alive;              // M.S ����ԏ����t���O
	int manSurfaceNum;       // M.S �l�I�u�W�F�N�g������ʂ̐���
	int thisManArrayNumber;  // M.S �z�u�������Ԃ̕ۑ�
	MATRIX4X4 manRotate;         // M.S �v���C�L�����̕�����������]�}�g���b�N�X
	MATRIX4X4 manRotateOld;      // M.S ����������߂��}�g���b�N�X
	bool initialProcess;  // M.S �ŏ��݂̂̏����t���O
	// M.S �v���C�L�����̕�������������p�x���}�b�v�̉�]�ɍ��킹�Ē�������ϐ�
	float initialRotate;
	// M.S 0:�܂�����ɒʉߍς݉w���H���Ȃ� 1:����ɒʉߍς݉w���H������ 3:��荞�݃A�j���[�V�����Ə������I��
	int initialDeadAnim;      
	// M.S ��ԃA�j���[�V�����̃^�C���J�E���g
	int animCount;
	// M.S ��ԃA�j���[�V�����̎���
	int saveAnimCount;
	// M.S ��]�p�x�t���O
	bool rotate0;        // M.S 0�x
	bool rotate90;       // M.S 90�x
	bool rotate180;      // M.S 180�x
	bool rotate270;      // M.S 270�x
	VECTOR3 pcPos;       // M.S �v���C�L�����̈ʒu
	VECTOR3 manPos;      // M.S �l�I�u�W�F�N�g�̈ʒu
};
// ------------------------------------
// �G�q�r�@�v���V�[�W���N���X
// ------------------------------------
class CEnmRSProc : public CBaseProc
{
protected:
	CFbxMesh*           m_pMesh;		// Fbx�X�L�����b�V��
	BASEHOLDITEM        m_nHoldItem;	// ��Ɏ��A�C�e��
public:
	void Update() override;
	CFbxMesh*       GetMesh() { return m_pMesh; }		// Fbx�X�L�����b�V��
	BASEHOLDITEM    GetHoldItem() { return m_nHoldItem; }	// ��Ɏ��A�C�e���̒l
	CEnmRSProc(CGameMain* pGMain);	// �R���X�g���N�^
	virtual	~CEnmRSProc();	// �f�X�g���N�^

	// M.S �l�I�u�W�F�N�g�̃|�C���^�̎擾
	CEnmRSObj* GetMiddleManObjPtr(int i) { return (CEnmRSObj*)GetObjArrayPtr()[i]; }
	// M.S �l�I�u�W�F�N�g�̈ʒu�̃Z�b�g
	void SetWorld(MATRIX4X4 m_mWorld, int i) { m_pObjArray[i]->SetWorld(m_mWorld); }
	// M.S �l�I�u�W�F�N�g�̈ʒu�̎擾
	MATRIX4X4 GetWorld(int i) { return m_pObjArray[i]->GetWorld(); }
	void ResetPlacementMan();  // M.S �L�����̍ŏ��̔z�u�ʒu�̔r�o

	// M.S �v�f�̐������ʂ̐���
	int numH[6];     // M.S �e�ʂ̔z�u����s�������Ă���z��
	int numV[6];     // M.S �e�ʂ̔z�u����񂪓����Ă���z��
	int PlacementManMap[6] = { 0 };    // M.S �z�u�����ʂ̊m�F�z��
	int manNum = 0;                    // M.S �z�u�ςݐl��
	bool exclusiveMan;             // M.S �z�u���t���O
	int surfaceNumTarget;          // M.S ���ׂ�ʂ̐���
	bool managementDeadProcess;    // M.S ��ԏ������t���O
};

//======================================================================
// �G�u���[�h���S���@�I�u�W�F�N�g�N���X
//======================================================================
class CEnmBdProc;
class CEnmBdObj : public CBaseObj
{
protected:
	CFbxMesh*			m_pMesh;		// Fbx�X�L�����b�V��
	BASEHOLDITEM        m_nHoldItem;	// ��Ɏ��A�C�e��    // -- 2021.2.4
	VECTOR3				m_vTarget;	// �^�[�Q�b�g
	NAVIGATIONMAP		m_Nav;		// �i�r�Q�[�V�����}�b�v

public:
	BOOL Start() override;
	void Update() override;
	void UpdateNormal();
	void UpdateDamage();
	void UpdateDead();
	void SetMesh(CEnmBdProc* pProc);    // -- 2021.2.4
	void SetNav(NAVIGATIONMAP  Nav) { m_Nav = Nav; }
	CEnmBdObj(CGameMain* pGMain);	// �R���X�g���N�^
	virtual	~CEnmBdObj();	// �f�X�g���N�^

	void OutUpPos(); // M.S �v���C�L�����Ɛl����ɂ����Ƃ���ʒu���o���֐�
	// M.S �l�I�u�W�F�N�g��`�悷��֐�
	void DoRenderLow() { m_pMesh->Render(m_AnimStatus, m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt, 0); }
	// M.S �l�I�u�W�F�N�g�̃A�j���[�V�����̒�~�A�Đ�
	void SetPlayAnimLow(bool set) { m_AnimStatus.playAnim = set; }

	bool doneProcess;      // M.S �z�u���Ă��邩�t���O
	bool alive;             // M.S ����ԏ����t���O
	int manSurfaceNum;         // M.S �l�I�u�W�F�N�g������ʂ̐���
	int thisManArrayNumber;    // M.S �z�u�������Ԃ̕ۑ�
	MATRIX4X4 manRotate;           // M.S �v���C�L�����̕�����������]�}�g���b�N�X
	MATRIX4X4 manRotateOld;        // M.S ����������߂��}�g���b�N�X

	bool initialProcess;    // M.S �ŏ��݂̂̏����t���O
	// M.S �v���C�L�����̕�������������p�x���}�b�v�̉�]�ɍ��킹�Ē�������ϐ�
	float initialRotate;
	// M.S 0:�܂�����ɒʉߍς݉w���H���Ȃ� 1:����ɒʉߍς݉w���H������ 3:��荞�݃A�j���[�V�����Ə������I��
	int initialDeadAnim;      
	// M.S ��ԃA�j���[�V�����̃^�C���J�E���g
	int animCount;
	// M.S ��ԃA�j���[�V�����̎���
	int saveAnimCount;
	// M.S ��]�p�x�t���O
	bool rotate0;    // M.S 0�x
	bool rotate90;   // M.S 90�x
	bool rotate180;  // M.S 180�x
	bool rotate270;  // M.S 270�x
	VECTOR3 pcPos;   // M.S �v���C�L�����̈ʒu
	VECTOR3 manPos;  // M.S �l�I�u�W�F�N�g�̈ʒu
	
};
// ------------------------------------
// �G�u���[�h���S���@�v���V�[�W���N���X
// ------------------------------------
class CEnmBdProc : public CBaseProc
{
protected:
	CFbxMesh*			m_pMesh;		// Fbx�X�L�����b�V��
	BASEHOLDITEM		m_nHoldItem;	// ��Ɏ��A�C�e��    // -- 2021.2.4
public:
	void Update() override;
	CFbxMesh*       GetMesh() { return m_pMesh; }		// Fbx�X�L�����b�V��
	BASEHOLDITEM    GetHoldItem() { return m_nHoldItem; }	// ��Ɏ��A�C�e���̒l    // -- 2021.2.4
	CEnmBdProc(CGameMain* pGMain);	// �R���X�g���N�^
	virtual	~CEnmBdProc();	// �f�X�g���N�^

	// M.S �l�I�u�W�F�N�g�̃|�C���^�̎擾
	CEnmBdObj* GetLowManObjPtr(int i) { return (CEnmBdObj*)GetObjArrayPtr()[i]; }
	// M.S �l�I�u�W�F�N�g�̈ʒu�̃Z�b�g
	void SetWorld(MATRIX4X4 m_mWorld, int i) { m_pObjArray[i]->SetWorld(m_mWorld); }
	// M.S �l�I�u�W�F�N�g�̈ʒu�̎擾
	MATRIX4X4 GetWorld(int i) { return m_pObjArray[i]->GetWorld(); }
	void ResetPlacementMan();   // M.S �L�����̍ŏ��̔z�u�ʒu�̔r�o

	// M.S �v�f�̐������ʂ̐���
	int numH[6];   // M.S �e�ʂ̔z�u����s�������Ă���z��
	int numV[6];   // M.S �e�ʂ̔z�u����񂪓����Ă���z��
	int PlacementManMap[6] = { 0 };   // M.S �z�u�����ʂ̊m�F�z��
	int manNum;                   // M.S �z�u�ςݐl��
	bool exclusiveMan;        // M.S �z�u���t���O
	int surfaceNumTarget;         // M.S ���ׂ�ʂ̐���
	bool managementDeadProcess;  // M.S ��ԏ������t���O
};
//======================================================================
// �G�L�����N�^�[�S�̂̃��C���v���V�[�W���N���X
//======================================================================
class CEnmProc : public CBaseProc
{
public:
	CEnmGolemProc*		m_pEnmGolemProc; // ��
	CEnmRSProc*			m_pEnmRSProc;    // ��
	CEnmBdProc*			m_pEnmBdProc;    // ��
	// M.S ��ԍ��v�l��
	int getLowMan;     // M.S ��
	int getMiddleMan;  // M.S ��
	int getHighMan;    // M.S ��
	// M.S ��̐��ł̏�Ԑl��
	int getLowStageMan;     // M.S �� 
	int getMiddleStageMan;  // M.S ��
	int getHighStageMan;    // M.S ��
	// M.S ��]�ɍ��킹�ăZ�b�g����p�x
	float rotate90angle;
	float rotate180angle;
	float rotate270angle;
	bool rotateOkFlagMan;  // M.S �}�b�v�̉�]���~�߂�t���O
public:
	void Update();
	void ResetEnmNum(CBaseProc* pProc=NULL);
	int  CountActiveEnm(CBaseProc* pProc=NULL, int nNum=0);
	CEnmProc(CGameMain* pGMain);	// �R���X�g���N�^
	virtual	~CEnmProc() { ; }	// �f�X�g���N�^
	void ResetNewGameMan();       // M.S �l�L�����ϐ��̃��Z�b�g
};

