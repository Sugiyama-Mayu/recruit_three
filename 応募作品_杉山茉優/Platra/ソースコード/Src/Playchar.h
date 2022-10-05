//=============================================================================
//		�R�c�Q�[���v���O����
//		�b�R�c�`�����P�P�Q�@�@�@�@�@�@                 ver 3.0        2021.1.11
//		�v���C�L�����N�^�[�@�w�b�_�t�@�C��							Playchar.h
//=============================================================================
#pragma once
#include "GameMain.h"
#include "Map.h"


//======================================================================
// �v���C�L�����N�^�[�@�I�u�W�F�N�g�N���X
//======================================================================
class CPcObj : public CBaseObj
{
protected:
	CFbxMesh*			m_pMesh;			// Fbx�X�L�����b�V��
	BASEHOLDITEM        m_nHoldItem;		// ��Ɏ�����
	float				m_fLocalRotY;		// ���[�J����(Y��)    // -- 2018.8.4
	BOOL				m_bSide;			// ���ړ����[�h       // -- 2018.8.4

	float				m_fSpeed;			// �ړ����x           // -- 2019.3.5
	float				m_fRotSpeed;		// ��]���x           // -- 2019.3.5
	float				m_fJumpSpeed;		// �W�����v���x       // -- 2019.3.5
	int                 moveTimes;          // �v���C�L�����̈ʒu�ړ��̉�
	int                 moveTimesMax;       // �P�}�X�œ�����

public:
	void Update() override;
	void UpdateNormal();       // -- 2019.3.5
	void UpdateNormalMove();   // -- 2019.3.5
	MATRIX4X4 UpdateNormalMoveKeystate(DWORD DIKey);  // -- 2021.1.10
	void UpdateNormalAttack(); // -- 2019.3.5
	void UpdateDamage();       // -- 2019.3.5
	void UpdateDead();         // -- 2019.3.5
	void SetMesh(CPcProc* pProc);
	MATRIX4X4  GetLocalMatrix();			// ���[�J�����}�g���b�N�X�𓾂�
	void SetLocalRotY(float fRotY) { m_fLocalRotY = fRotY; }   // ���[�J����(Y��)���Z�b�g����
	CFbxMesh*  GetMesh() { return m_pMesh; }
	CPcObj(CGameMain* pGMain);	// �R���X�g���N�^
	virtual	~CPcObj();
	MATRIX4X4 mPos;  // �o�b�ړ��}�g���b�N�X

	// M.S CPcObj�̂������牺�͒ǉ������ϐ��A�֐��ł�
	// M.S ��--------------------------------------------------------------------
	// ���C���΂����Ɏg���ϐ�
	VECTOR3 mHit;  // �q�b�g�ʒu
	VECTOR3 mNor;  // �q�b�g�������̖@�����W
	// �A�j���[�V�������~�A�Đ�����֐�
	void SetPlayAnim(bool set) { m_AnimStatus.playAnim = set; }
	// PC�̕`��݂̂���֐�
	void DoRender() { m_pMesh->Render(m_AnimStatus, m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt, 0); }
	// CPcObj�̃Q�[���̏�����������֐�
	void ResetNewGamePcObj();
	// �������H�̈ړ������̊֐�
	void MoveRight();    // �E�����ړ�
	void MoveLeft();     // �������ړ�
	void MoveDown();     // �������ړ�
	void MoveUp();       // ������ړ�
	// �����؂�ւ����H�̈ړ������ɍ��킹���ϐ��̃Z�b�g
	void SetUpRightChangeLineValue();   // �ォ��E�ړ�
	void SetUpLeftChangeLineValue();    // �ォ�獶�ړ�
	void SetDownRightChangeLineValue(); // ������E�ړ�
	void SetDownLeftChangeLineValue();  // �����獶�ړ�
	void SetRightUpChangeLineValue();   // �E�����ړ�
	void SetRightDownChangeLineValue(); // �E���牺�ړ�
	void SetLeftUpChangeLineValue();    // �������ړ�
	void SetLeftDownChangeLineValue();  // �����牺�ړ�
	// �����؂�ւ����H�̈ړ�����
	void MoveUpRight();    // �ォ��E�ړ�
	void MoveUpLeft();     // �ォ�獶�ړ�
	void MoveDownRight();  // ������E�ړ�
	void MoveDownLeft();   // �����獶�ړ�
	void MoveRightUp();    // �E�����ړ�
	void MoveRightDown();  // �E���牺�ړ�
	void MoveLeftUp();     // �������ړ�
	void MoveLeftDown();   // �����牺�ړ�
	// �ʂ̒[���玟�̖ʂ֍s�����̈ړ������֐�
	void MoveEdgePos1();
	void MoveEdgePos2();
	void MoveEdgePos3();
	void MoveEdgePos4();
	void MoveEdgePos5();
	void MoveEdgePos6();
	void SetEdgePos();  // MoveEdgePos���Ă�Œ[����ړ��������̈ʒu�Ɖ�]�����߂�
	// �}�b�v�ʂ̒[���玟�̖ʂֈړ����鎞�̌��ݒn�̍X�V
	void updateEdgeOldHV(int trainDirectionFlag, int oldH, int oldV, int surfaceNum);
	// �L����������ʂ̐�����ʒu�𒲂ׂ�
	int JudgeNowPcMap(VECTOR3 nowPosition, bool onlyFront);
	// upBack�AupFront�Ƀ��C���΂��A���̃��C�̏ꏊ�ɂǂ��̖ʂ�����̂����ׂ�
	int RayOrderSurfaceBBox(MATRIX4X4 upBack, MATRIX4X4 upFront);

	// �Q�[���I�[�o�[�̃A�j���t�F�[�Y
	int gameOverAnim;  
	// �v���C�L����������ʒu
	int oldHP;  // �����l��4
	int oldVP;  // �����l��4
	int changeStepNum;   //�����؂�ւ����H�̎��̈ړ��t�F�[�Y 0:�ړ� 1:��] 2:�ړ�
	// �ړ������̕ϐ� 
	int upArrow;     // ���1
	int rightArrow;  // �E��2
	int downArrow;   // ����3
	int leftArrow;   // ����4
	bool DoneMove;   	   // 1���[�v���Ɉړ����������ǂ���������ϐ�
	VECTOR3 nowPcPos;   // �v���C���L�����̈ʒu
	int nowPcPosMap;    // �v���C�L�����̈ʒu�̐���
	int nowNorth;       // �}�b�v�ʂ̉�]�̐���

   // �����؂�ւ����H
	// �z�u�ł��Ȃ��z��̏���l(upper)�A�����l(lower)(H���s�AV����)
	int lowerLimitH;
	int upperLimitH;
	int upperLimitV;
	int lowerLimitV;
	// ���H�z�u��̔z��̈ʒu
	// H�͍s�AV�͗�ANear�����Ă���̂̓v���C�L��������߂��}�X�A���Ă��Ȃ��̂͗���Ă���}�X
	int chPlacementNearH;
	int chPlacementH;
	int chPlacementNearV;
	int chPlacementV;
	int edgePos;                             // �v���C�L�������[�ɂ���Ƃ��̔z��̒l
	int rotateChar;                          // �����؂�ւ����H�̃v���C�L�����̉�]�ϐ�
	int moveValueH;      	                 // ���̐��H�܂ł̈ړ����鋗��(�s)
	int moveValueV;      	                 // ���̐��H�܂ł̈ړ����鋗��(��)
	int loopPlusMoveTimes;                   // ���[�v���Đi��ł����x��moveTimes�ɑ����ϐ�
	int changeLineNum;                       // �����؂�ւ����H�̔z��ɂ��ꂽ����
	int afterChangeLineNum;                  // �����؂�ւ����H�̒ʉߌ�ɔz��ɂ���鐔��
	float chLineMoveTimesMax;  // �ŏ��ɂ܂������i�ދ�����2�}�X���Ȃ̂�moveTimesMax * 2
	int surfaceNum;            // �v���C�L����������ʒu
	bool frontFlag;            // ���ʂɃv���C�L����������t���O  
	int nowPcPosNum;           // ���_���猩��(+Y�������-z����������Ɍ����Ă���̏��) 0:�� 1:��O 2:�� 3:1�̗� 4:�E 5:��
	MATRIX4X4 newPcPos;        // �}�b�v�̖ʂ���ʂɈړ�����ۂ̃v���C���[�ʒu�̒����p�ϐ�
	int trainDirectionFlag;    // �������Ă�������̕ۑ�

	int needRotateFlag;      // �}�b�v�̖ʂ���ʂɈړ�����ۂ̃v���C���[�ʒu�Ɋ|����ϐ��̐��̒����p�ϐ�
	MATRIX4X4 edgeRotate1;   // �}�b�v�̖ʂ���ʂɈړ�����ۂ̃v���C���[�ʒu�Ɋ|���鐔
	MATRIX4X4 edgeRotate2;
	MATRIX4X4 edgeRotate3;
	bool edgeFlag;           // �[���玟�̖ʂւ̈ړ��t���O��false

	int gameOverTime;     // �Q�[���I�[�o�[�A�j���[�V�������I�������̃J�E���g
	int animCount;        // �Q�[���I�[�o�[�A�j���[�V�����̒����J�E���g
	int startTime;        // �Q�[���J�n�܂ł̃J�E���g
	bool startTimeFlag;   // �Q�[���J�n�t���O
};

//======================================================================
// �v���C�L�����N�^�[�@�v���V�[�W���N���X
//======================================================================
class CPcProc : public CBaseProc
{
protected:
	CFbxMesh*           m_pMesh;				// Fbx�X�L�����b�V��
	BASEHOLDITEM        m_nHoldItem;			// ��Ɏ�����
	int				    m_nPcNum;

public:
	// �A�N�Z�X�֐�
	CFbxMesh*           GetMesh() { return m_pMesh; }		// Fbx�X�L�����b�V��
	BASEHOLDITEM        GetHoldItem() { return m_nHoldItem; }	// ��Ɏ��A�C�e���̒l
	CPcObj*			    GetPcObjPtr() { return (CPcObj*)GetObjArrayPtr()[0]; }//
	int				    GetPcNum() { return m_nPcNum; }
	void				AddPcNum(int Num) { m_nPcNum += Num;  }
	// �R���X�g���N�^
	CPcProc(CGameMain* pGMain);
	virtual	~CPcProc();

	// M.S ��������CPcProc�̂������牺�͎����ŏ������ϐ��A�֐��ł�
	// M.S ��--------------------------------------------------------------------
	// �Q�[���̏�����������֐�(CPcProc)
	void ResetNewGamePc();
	// ��Βl����L�����̏オ�ǂ��Ɍ����Ă���̂����ׂ�
	void JudgeAbsoluteSize(int kindNum, VECTOR3 pos);
	// ��]�̊p�x�𒲂ׂ�֐�
	int JudgeRotateSurface(int surfaceNum, VECTOR3 upBack, VECTOR3 upFront, VECTOR3 downBack,
		VECTOR3 downFront, VECTOR3 rightBack, VECTOR3 rightFront, VECTOR3 leftBack, VECTOR3 leftFront);
	// ��]�̊p�x�𒲂ׂ�֐�(������ԂŐ��ʂ̖�)
	int JudgeRotateSurfaceUp(VECTOR3 upBack, VECTOR3 upFront, VECTOR3 downBack,
		VECTOR3 downFront, VECTOR3 rightBack, VECTOR3 rightFront, VECTOR3 leftBack, VECTOR3 leftFront);
	// ��]�̊p�x�𒲂ׂ�֐�(������ԂŐ��ʂ̉��̖�)
	int JudgeRotateSurfaceUnder(VECTOR3 upBack, VECTOR3 upFront, VECTOR3 downBack,
		VECTOR3 downFront, VECTOR3 rightBack, VECTOR3 rightFront, VECTOR3 leftBack, VECTOR3 leftFront);
	// ��]�̊p�x�𒲂ׂ�֐�(������ԂŐ��ʂ̗��̖�)
	int JudgeRotateSurfaceDown(VECTOR3 upBack, VECTOR3 upFront, VECTOR3 downBack,
		VECTOR3 downFront, VECTOR3 rightBack, VECTOR3 rightFront, VECTOR3 leftBack, VECTOR3 leftFront);
	// ��]�̊p�x�𒲂ׂ�֐�(������ԂŐ��ʂ̏�̖�)
	int JudgeRotateSurfaceAbove(VECTOR3 upBack, VECTOR3 upFront, VECTOR3 downBack,
		VECTOR3 downFront, VECTOR3 rightBack, VECTOR3 rightFront, VECTOR3 leftBack, VECTOR3 leftFront);
	// ��]�̊p�x�𒲂ׂ�֐�(������ԂŐ��ʂ̉E�̖�)
	int JudgeRotateSurfaceRight(VECTOR3 upBack, VECTOR3 upFront, VECTOR3 downBack,
		VECTOR3 downFront, VECTOR3 rightBack, VECTOR3 rightFront, VECTOR3 leftBack, VECTOR3 leftFront);
	// ��]�̊p�x�𒲂ׂ�֐�(������ԂŐ��ʂ̍��̖�)
	int JudgeRotateSurfaceLeft(VECTOR3 upBack, VECTOR3 upFront, VECTOR3 downBack,
		VECTOR3 downFront, VECTOR3 rightBack, VECTOR3 rightFront, VECTOR3 leftBack, VECTOR3 leftFront);

	void lineMapSet(int oldsurfaceNum);     // �v���C�L�����������}�b�v�z���ۑ�����֐�
	void lineMapNew(int surfaceNum);        // �v���C�L����������}�b�v�z��������Ă���֐�
    // �L����������ʒu�̃}�b�v�ʂ̉�]�̊p�x�𒲂ׂ�֐�
	int judgeDirection(int surfaceNum, VECTOR3 pos, int kindNum);

	// ���C���΂����Ɏg���ϐ�
	VECTOR3 mHit;  // �q�b�g�ʒu
	VECTOR3 mNor;  // �q�b�g�������̖@�����W
	// �v���C���[������ʒu�̖ʂ̉�]�𒲂ׂ�p
	bool directrioFlag1;  // ��
	bool directrioFlag2;  // ��
	bool directrioFlag3;  // �E 
	bool directrioFlag4;  // ��
	bool xJudge;   // x���̒l�ɑΉ�����bool�ϐ�
	bool yJudge;   // y���̒l�ɑΉ�����bool�ϐ�
	bool zJudge;   // z���̒l�ɑΉ�����bool�ϐ�
	// �v���C���[�̈ʒu����̏ꍇ
	VECTOR3 upFront1;
	VECTOR3 upBack1;
	VECTOR3 downFront1;
	VECTOR3 downBack1;
	VECTOR3 rightFront1;
	VECTOR3 rightBack1;
	VECTOR3 leftFront1;
	VECTOR3 leftBack1;
	// �v���C���[�̈ʒu���^��
	VECTOR3 upFront2;
	VECTOR3 upBack2;
	VECTOR3 downFront2;
	VECTOR3 downBack2;
	VECTOR3 rightFront2;
	VECTOR3 rightBack2;
	VECTOR3 leftFront2;
	VECTOR3 leftBack2;
	// �v���C���[�̈ʒu����
	VECTOR3 upFront3;
	VECTOR3 upBack3;
	VECTOR3 downFront3;
	VECTOR3 downBack3;
	VECTOR3 rightFront3;
	VECTOR3 rightBack3;
	VECTOR3 leftFront3;
	VECTOR3 leftBack3;
	// �v���C���[�̈ʒu�����̐^��
	VECTOR3 upFront4;
	VECTOR3 upBack4;
	VECTOR3 downFront4;
	VECTOR3 downBack4;
	VECTOR3 rightFront4;
	VECTOR3 rightBack4;
	VECTOR3 leftFront4;
	VECTOR3 leftBack4;
	// �v���C���[�̈ʒu���E
	VECTOR3 upFront5;
	VECTOR3 upBack5;
	VECTOR3 downFront5;
	VECTOR3 downBack5;
	VECTOR3 rightFront5;
	VECTOR3 rightBack5;
	VECTOR3 leftFront5;
	VECTOR3 leftBack5;
	// �v���C���[�̈ʒu����
	VECTOR3 upFront6;
	VECTOR3 upBack6;
	VECTOR3 downFront6;
	VECTOR3 downBack6;
	VECTOR3 rightFront6;
	VECTOR3 rightBack6;
	VECTOR3 leftFront6;
	VECTOR3 leftBack6;
	// �ʂ̉�]��ۑ�����ϐ�
	int rotateMapNorthNow;
	// ����ʂłȂ����̃v���C���[�ړ���ۑ��A�Q�Ƃ���}�b�v�z��
	int lineMapSub[10][10] = { 0 };
	// false�Ȃ�΃}�b�v�̉�]���~�߂�
	bool rotateOkFlag;
	bool oneScreenFlag;      // 1�ʂ̂ݕ`��t���O
	bool initialStart;       // �ŏ��̃X�^�[�g����
	int trainStep;           // �ړ�����
	int NewSurfaceNum;       // �v���C�L�����������	
};

