//=============================================================================
//		�R�c�Q�[���v���O����
//		�b�R�c�`�����P�P�Q�@�@�@�@�@�@                 ver 3.0        2021.1.11
//		�}�b�v�@�w�b�_�t�@�C��											Map.h
//=============================================================================
#pragma once
#include "GameMain.h"
#include <vector>

// --------------------------------------------------------------------
//
// �X�e�[�W�}�b�v
//
// --------------------------------------------------------------------

// �N���X�̃v���g�^�C�v�錾
class TrainLineStObj;
class TrainLineStProc;
class TrainLineSdObj;
class TrainLineSdProc;
class TrainLineCgObj;
class TrainLineCgProc;
class TrainLineStationObj;
class TrainLineStationProc;

struct STAGEMAP
{
	CFbxMesh*				m_pMesh;			// �X�^�e�B�b�N���b�V���ւ̃|�C���^
	CWave*					m_pWave;			// �g�̃��b�V���ւ̃|�C���^
	MATRIX4X4				m_mWorld;			// ���b�V���̃��[���h�}�g���b�N�X
	int						m_nMaterialFlag;	// �}�e���A���t���O�@0:�ʏ�@1:�����F�@2:�f�B�X�v���C�X�����g�}�b�s���O 3:�g
	CBBox*                  m_pBBox;            // �o�E���f�B���O�{�b�N�X

	STAGEMAP()    // �R���X�g���N�^
	{
		Init();
	}
	~STAGEMAP()    // �f�X�g���N�^
	{
		// ���̒��Ń��b�V����DELETE�����Ă͂Ȃ�Ȃ�
	}
	void Init()    // ���������\�b�h
	{
		m_pMesh = NULL;
		m_pWave = NULL;
		m_mWorld = XMMatrixIdentity();
		m_nMaterialFlag = 0;
		m_pBBox = NULL;
	}
};
// --------------------------------------------------------------------
//
// �ړ��}�b�v            �����̃v���O�������ł́A�g�p���Ȃ�
//
// --------------------------------------------------------------------
struct MOVEMAP
{
	BOOL					m_bActive;			// �ړ�Active
	CFbxMesh*				m_pMesh;			// �X�^�e�B�b�N���b�V���ւ̃|�C���^
	int						m_nMaterialFlag;	// �}�e���A���t���O�@0:�ʏ�@1:�����F�@2:�f�B�X�v���C�X�����g�}�b�s���O
	CCollision*				m_pColMesh;			// �ړ��R���W�������b�V���ւ̃|�C���^
	int						m_nMoveFlag;		// �ړ��t���O�@0:�ړ������@1:���s�ړ��@2:��]�@3:�g��k��      // -- 2019.12.30
	VECTOR3					m_vUp;				// �ړ�����
	VECTOR3					m_vMin;				// �ړ��ŏ��l
	VECTOR3					m_vMax;				// �ړ��ő�l
	int						m_nChangeFlag;		// �ړ������E�l�ɓ��B���ĕ���������ւ��Ƃ��@0:�ړ����@1:�����`�F���W
	int						m_nLoop;			// �ړ����J��Ԃ���  0:�`�F���W�̉ӏ��Œ�~���ړ��t���O��0:�ړ������ɖ߂��B 1:�ړ����J��Ԃ�  // -- 2021.2.4

	MOVEMAP()    // �R���X�g���N�^
	{
		Init();
	}
	~MOVEMAP()    // �f�X�g���N�^
	{
		// ���̒��Ń��b�V����DELETE�����Ă͂Ȃ�Ȃ�
	}
	void Init()
	{
		m_bActive = FALSE;
		m_pMesh = NULL;
		m_nMaterialFlag = 0;
		m_pColMesh = NULL;
		m_nMoveFlag = 0;
		m_vUp = VECTOR3(0, 0, 0);
		m_vMin = VECTOR3(-9999, -9999, -9999);
		m_vMax = VECTOR3(9999, 9999, 9999);
		m_nChangeFlag = 0;
		m_nLoop = 1;           // �����ݒ�̓��[�v        // -- 2021.2.4
	}
};

// --------------------------------------------------------------------
//
// �i�r�Q�[�V�����}�b�v
//
// --------------------------------------------------------------------
struct NAVIGATIONMAP
{
	VECTOR3 vMin;
	VECTOR3 vMax;
	std::vector<DWORD>  m_dwEnmID;  // �ΏۂƂȂ�G�̂h�c
	NAVIGATIONMAP()    // �R���X�g���N�^
	{
		Init();
	}
	void Init()
	{
		vMin = VECTOR3(0.0f, 0.0f, 0.0f);
		vMax = VECTOR3(0.0f, 0.0f, 0.0f);
	}
};

// --------------------------------------------------------------------    // -- 2021.2.4
//
// �C�x���g
//
// --------------------------------------------------------------------
// �C�x���g���
enum EVENTKIND
{
	eEvtKindNone = 0,
	eEvtChangeMap = 1,
	eEvtMoveMap = 2
};

struct EVENTMAP
{
	CBBox*    m_pBBox;       // �o�E���f�B���O�{�b�N�X
	int       m_nEvtCycle;   // �C�x���g�T�C�N�� 0:�C�x���g���s���Ă��Ȃ� 1:�C�x���g���s���i�g�p���Ă��Ȃ��j 2:�C�x���g�I���`�F�b�N�i�ڐG�I��������j
	EVENTKIND m_nEvtKind;    // �C�x���g�̎�� eEvtChangeMap:�}�b�v�ړ�, eEvtMoveMap:�ړ��}�b�v�̐���
	int       m_nEvtNo;      // �C�x���g�ԍ� eEvtChangeMap�̂Ƃ��͈ړ���̃}�b�v�ԍ��AeEvtMoveMap�̂Ƃ��͈ړ��}�b�v�̗v�f�ԍ�
	int       m_nEvtOpe1;    // eEvtMoveMap�̂݁B1:�ړ��}�b�v�̈ړ�Active�̎w��B2:�ړ��}�b�v�̈ړ��t���O�̎w��
	int       m_nEvtOpe2;    // eEvtMoveMap�̂݁B�ړ�Active�̂Ƃ���0:��\�� 1:�\��  �ړ��t���O�̂Ƃ��́@0:�ړ������@1:���s�ړ��@2:��]�@3:�g��k��
	int       m_nEvtKeyPush; // 0:�o�E���f�B���O�{�b�N�X�ɐڐG����ƃC�x���g�����A 1:�o�E���f�B���O�{�b�N�X�ɐڐG���āAENTER�L�[�������ƃC�x���g����

	EVENTMAP()    // �R���X�g���N�^
	{
		m_pBBox = NULL;
		m_nEvtCycle = 0;
		m_nEvtKind = eEvtKindNone;
		m_nEvtNo = 0;
		m_nEvtOpe1 = 0;
		m_nEvtOpe2 = 0;
		m_nEvtKeyPush = 0;
	}
	~EVENTMAP()    // �f�X�g���N�^
	{
		// ���̒��Ń��b�V����CBBox��DELETE�����Ă͂Ȃ�Ȃ�
	}
};

//======================================================================
// �}�b�v�@�v���V�[�W���N���X
//
// (����)�}�b�v�@�v���V�[�W���N���X�́A��{�v���V�[�W���N���X���p�����Ă��Ȃ�
// 
//======================================================================
class CMapProc
{
protected:
    // ���C���΂����Ɏg���ϐ�
	VECTOR3 mHit;  // �q�b�g�ʒu
	VECTOR3 mNor;  // �q�b�g�������̖@�����W
	CGameMain*							m_pGMain;
	DWORD								m_dwMapNo;
	BOOL								m_bActive;

	std::vector<STAGEMAP>				m_SkyMap;			// ��̃}�b�v
	std::vector<STAGEMAP>				m_StageMap;			// �X�e�[�W�̃}�b�v
	CCollision*							m_pColMesh;			// �R���W�������b�V��
	std::vector<MOVEMAP>				m_MoveMap;			// �ړ��}�b�v  *���̃v���O�������ł́A�g�p���Ȃ�
	std::vector<NAVIGATIONMAP>			m_NavMap;			// �i�r�Q�[�V�����}�b�v
	std::vector<EVENTMAP>				m_EventMap;			// �C�x���g�}�b�v    // -- 2021.2.4
	int									m_nEvtIdx;			// �C�x���g�v�f�ԍ�  // -- 2021.2.4

public:

	void Update();
	void Render();
	void Render2();
	void DestroyAll();
	void LoadMap1();
	void LoadMap2();
	void LoadMap3();
	int isCollisionMove(MATRIX4X4* pWorld, MATRIX4X4 mWorldOld, float fRadius);

	void UpdateMoveMap();
	int  SetEvent(VECTOR3 vMin, VECTOR3 vMax, MATRIX4X4 mWorld, EVENTKIND nEvtKind, int nEvtNo, int nEvtOpe1 = 0, int nEvtOpe2 = 0, int nEvtKeyPush = 0);    // -- 2021.2.4
	void UpdateEvent();                                                                           // -- 2021.2.4
	void RunEvent(EVENTMAP& EventMap);                                                             // -- 2021.2.4

	BOOL Hitcheck(CBaseObj* pObj, VECTOR3* pHit, VECTOR3* pNormal);
	BOOL Hitcheck(VECTOR3 vNow, VECTOR3 vOld, VECTOR3* pHit, VECTOR3* pNormal);
	BOOL Hitcheck(VECTOR3 vNow, VECTOR3 vOld, float fRadius, VECTOR3* pHit, VECTOR3* pNormal);    // -- 2020.12.11

	int  isCollisionMoveGravity(MATRIX4X4* pWorld, MATRIX4X4 mWorldOld, float fRadius = 0.2f);

	// �A�N�Z�X�֐�
	std::vector<NAVIGATIONMAP> GetNavMap() { return m_NavMap; }

	// �R���X�g���N�^�i�v���V�[�W���̏������j
	CMapProc(CGameMain*	m_pGMain);
	~CMapProc();
	MATRIX4X4 mMapWorldOld;    // -- 2022.1.18  ��]�O��ۑ�

	// M.S CMapProc�̂������牺�͒ǉ������ϐ��A�֐��ł�
	// M.S ��--------------------------------------------------------------------
	// �A�N�Z�X�֐�
	DWORD MapNumGet() { return m_dwMapNo; }  // �}�b�v�i���o�[�̎擾
	// �}�b�v�̈ʒu�̎擾
	MATRIX4X4 GetStageWorld() { return m_StageMap[0].m_mWorld; }
	// �e�ʂɔz�u����Ă���BBox�̈ʒu�̎擾
	MATRIX4X4 GetStageBBox(int num) { return m_pBBoxPosition[num]->m_mWorld; }

	int* MapDynamic();              // ���̓��I�����̊֐�
	int RandomNumMeth();            // �����_�������̔r�o�֐�

	void ResetNewGameMap();    // �Q�[�����[�v�����������ϐ��̃��Z�b�g������֐�
    // �}�b�v�z��L���p�̊֐�
	void lineMapSet(int oldRotateSurface);
	// �V�����ʂ̃}�b�v��ǂݍ���
	void lineMapNew(int RotateSurface);
	// �����]�����H���}�b�v�z��ɓ��邩�A�܂��������ꍇ���̔z��̍X�V
	bool SetChangeBoxJudge(int h, int v);  
	// ���������߁A���̕����ɐi�񂾎��̏c���̈ʒu�r�o
	void DecideDirection();         
	// �����ɐi�񂾎��̏c���̈ʒu�r�o
	int outStartNum(int up, int down, int left, int right, int startVertical, int startHorizontal);
	void MakeFrontBBox();       // ���ʂ̃o�E���f�B���{�b�N�X�̍쐬
	void MakeSurfaceBBox();     // �e�ʂ̃o�E���f�B���O�{�b�N�X�̍쐬
	void SetPosSurfaceBBox();   // �e�ʂ̃o�E���f�B���O�{�b�N�X�̈ʒu�Z�b�g
	void MapManRotate(MATRIX4X4 old, MATRIX4X4 mYaw);        // �e�ʂ̐l�I�u�W�F�N�g�̉�]
	void MapBBoxRotate(MATRIX4X4 old, MATRIX4X4 mYaw);       // �e�ʂ�BBox�̉�]
	bool SearchFinalPlacementSurface(int bBoxArrayNum);      // BBox���g�p���Đ��ʂ̖ʂ𒲂ׂ�֐�
	void BornStarEffect();                  // ���̓��I�z�u�\���ƃG�t�F�N�g

	// ���̉˂�����������֐�
	void BuiltStarBridge(VECTOR3 longCursol, VECTOR3 shortCursol);
	void RotateStar();                      // ���̉�]������֐�
	void JudgeSurface();                    // ���݂̑���ʃ}�b�v�𒲂ׂ�
	void GlitterEffect();                	// ���H�̃L���L���G�t�F�N�g�̕\��
	void DrawCursorGuide(int h, int v);     // �J�[�\���K�C�h�̕\��
	void PlacementStLine(int h, int v);     // ���i���H�̔z�u
	void PlacementCgLine(int h, int v);     // �����]�����H�̔z�u
	void PlacementStaLine(int h, int v);    // �w�̔z�u

	// �Ō�ɔz�u���삵���}�b�v�ʂ̕ۑ��p�֐�
	int SearchFinalPlacementSurface();
	// �z�u�����������ϊ��̐i�ޕ����Ɣz�u�\���ǂ�������
	int GetChangeNum(int h, int v, int oldH, int oldV);
	// �����]�����H�z�u���̃v���C���[���ݒn�̍X�V
	void UpadateOldHV(int oldH, int oldV, int h, int v);
	// ���̖ʂւ̔z�u�ɂȂ鎞�̔z�u�ʒu�̊Ǘ�
	bool AllowEndPlacement(bool onlyArrowJudgeFlag);
	// ����]���ɐ��ɏ���Ă���I�u�W�F�N�g�̉�]���s��
	void MapPcRotate(MATRIX4X4 old, MATRIX4X4 mYaw);
	// (�z�u����Ă��邩�Ȃǂ��l����)�ʒu�I�ɔz�u�ł��邩���f����֐�
	bool ArrowPlacementPos();

	// ���̓��I�����Ŏg�p����ϐ�
	int startMap[5][5] = { 0 };     // �����}�b�v�z��	
	int up;                     // ���̓��I�����Ŏg�������ϐ�
	int down;
	int right;
	int left;
	int startVertical;          // ���̓��I�����Ɏg�p����z��̗�
	int startHorizontal;        // ���̓��I�����Ɏg�p����z��̍s
	int ver;        // ���̓��I�����Ɏg�p����z��̗�buf
	int hori;     // ���̓��I�����Ɏg�p����z��̍sbuf
	int arrowSwitch[4] = { 0 };     // �ǂ̕������I��������̔���p�z��
	int randomNum;              //RandomNumMeth()�Ŏg�p����ϐ�

	//���H�z�u�z��}�b�v
	int lineMap1[10][10] = { 0 };       // ����p�̃}�b�v�z��
	int lineMapBuf1[10][10] = { 0 };    // ������Ԃł����瑤�̖�
	int lineMapBuf2[10][10] = { 0 };    // �����瑤�̂��̉��̖�
	int lineMapBuf3[10][10] = { 0 };    // ��ԉ��̖�
	int lineMapBuf4[10][10] = { 0 };    // lineMapBuf2�̗���
	int lineMapBuf5[10][10] = { 0 };    // �����̖�
	int lineMapBuf6[10][10] = { 0 };    // �E���̖�
	int typeChangeNum;       // �u�����Ƃ��ł���z�u���̎�ނ̎��ʐ���  1:�������H���z�u�� 2:�������H�A�����ύX���H���z�u��
	int starRotateSwitch;     // ���̉�]�����̑���ň�x�̂ݍs������
	// �J�[�\���ʒu�̕\���pBBox
	CBBox*                  m_pBBoxLine[10][10];
	int ChangeButton;                    // �z�u���̕ύX���� 0:�������H 1:�����]�����H 2:�w
	TrainLineStProc*      TrainLST;      // �c���H
	TrainLineSdProc*      TrainLSD;      // �����H
	TrainLineCgProc*      TrainLChange;  // �����؂�ւ����H
	TrainLineStationProc* TrainLStation; // �w

	// �z�u�������H��
	int     trainNumSt;  // �c���H
	int     trainNumSd;  // �����H
	int     trainNumCg;  // �����؂�ւ����H
	int     trainNumSta; // �w
	int     oldH;        // �V�����z�u�����z�u���̈ʒu(�s)
	int     oldV;        // �V�����z�u�����z�u���̈ʒu(��)
	int		LineChangeFlag;     // 0:���� 1:�� 2:�E 3:�� 4:��

	int changeNum;       // �����]�����H�̕����ϐ�1
	int aboutArrow;      // �����]�����H�̕����ϐ�2

	MATRIX4X4 mYawX;  // ����X��]�p�x�̃}�g���b�N�X
	MATRIX4X4 mYawZ;  // ����X��]�p�x�̃}�g���b�N�X

	POINT  beforePoint;  // ��]�����鑀��̍ŏ��̃}�E�X�ʒu
	POINT  afterPoint;   // ��]�����鑀��̍Ō�̃}�E�X�ʒu
	POINT  resultPoint;  // beforePoint����afterPoint���������l

	int pointArrow1; // ���̉�]�p�x�����߂邽�߂̕ϐ�
	int pointArrow2;
	int pointArrow3;
	int pointArrow4;

	float sideDegree;   // ���̉�]�p�x�̕ۑ�(����])
	float heightDegree; // ���̉�]�p�x�̕ۑ�(�c��])
	CBBox*                  m_pBBoxPosition[6];   // �e�ʂ̎��ʗpBBox

	// �e�ʂ̉�]�������ʗpBBox �Q�[����ʂ̏����ʒu����  
	//   0:�J�������琳�� 1:�J�������ʂ����O 2:���ʂ̔��� 3:1�̔��Ή�� 4:�E�� 5:����
	CBBox*                  m_pBBoxArrow1[4];    // �����ʒu:����(�v���C���[�����ʒu)
	CBBox*                  m_pBBoxArrow2[4];    // �����ʒu:��
	CBBox*                  m_pBBoxArrow3[4];    // �����ʒu:��
	CBBox*                  m_pBBoxArrow4[4];    // �����ʒu:��
	CBBox*                  m_pBBoxArrow5[4];    // �����ʒu:�E
	CBBox*                  m_pBBoxArrow6[4];    // �����ʒu:��
	// BBox�𒲂ׂ鎞�ɔ�΂����C�̈ʒu
	VECTOR3         front;
	VECTOR3         back;

	int pointArrowNum1;     // pointArrow�ϐ��̌v�Z���ʂ̕ۑ��ϐ�
	int pointArrowNum2;

	bool rotateFinish;  // ��]�I�������t���O
	int surfaceMap;     // ���ʂɂ���ʂ̐���
	bool setOk;         // �z��̏������݁A�ǂݍ��݂����Ԓʂ�ɂ���ϐ�
	int northNow;       // ����}�b�v�ʂ̉�]�����ۑ��ϐ�

	// �J�[�\���ʒu���}�b�v�z��p�ɕϊ��������̕ۑ��ϐ�
	int horiRotate; // �s
	int verRotate;  // ��

	int oldRotateSurface;        // �ۑ�����ׂ��ʂ̐����ϐ�
	int PlacementSurfaceNum;     // �Ō�ɑ��삵���}�b�v�ʂ̕ۑ��ϐ�
	bool newSurfacePlacement;    // ���̃}�b�v�ʂւ̔z�u����

	int permissionH; // ���̃}�b�v�ʂւ̔z�u���p�̃N���b�N�ʒu�ϐ�(�s)
	int permissionV; // ���̃}�b�v�ʂւ̔z�u���p�̃N���b�N�ʒu�ϐ�(��)

	// �}�b�v3�̐��̉˂����̔z�u����
	bool starBridgePermission;  // ���̉˂����z�u����
	bool starBridgeInputFlag;   // �N���b�N�������t���O
	bool NearStarCol;           // ��O�̐��ƃ}�E�X�̐ڐG�t���O
	bool frontStarCol;          // ���̐��ƃ}�E�X�̐ڐG�t���O

	// �l�I�u�W�F�N�g�̔z�u���I����Ă��邩(�r���ł͂Ȃ���)
	bool doneManPlacement;
	// �}�b�v�̉�]�ɍ��킹���I�u�W�F�N�g�̈ړ����I��������ǂ���
	bool rotateProcessDoneFlag;

	// �l�I�u�W�F�N�g�̐�������ϐ�
	int arrayHNum;  // ��
	int arrayMNum;  // ��
	int arrayLNum;  // ��

	int starBridgeLitingTime;   // ���̉˂��������点��J�E���g�ϐ�
	int starBridgePosNum;       // ���񂾂񋴂����点��ׂ̋��ړ��p�ϐ�
	bool changeButtonWithinRange;  // �z�u������H���͈͓����ǂ����̃t���O
	int surfaceMapLineJudge;           // ���݂̑���ʃ}�b�v
	bool linePlacementOkFlag;       // �z�u���������t���O

	bool SaveRotateSurfaceFlag;    // �}�b�v�ʂ̕ۑ��A�X�V�����t���O
	int* mapStarArrayBuf;                  // ���I�����������̃|�C���^
	int mapStarArray[5][5] = { 0 };        // ���I�����������̔z��
	int waitTime;                      // �������̃G�t�F�N�g�̃^�C���J�E���g
	int saveHori;        // �������̃G�t�F�N�g�Ɏg�p����z��v�f�ԍ�(�s)
	int saveVer;         // �������̃G�t�F�N�g�Ɏg�p����z��v�f�ԍ�(��)
	int starEffectOrder; // �������̃G�t�F�N�g�̃t�F�[�Y
	int starObjArrayNum; // �����������������G�t�F�N�g�̐�	
};
//------------------------------------------------
// M.S ���H�̒��ۊ��N���X�v���V�[�W��
//------------------------------------------------
class TrainLineProc {
protected:
	CGameMain*	 m_pGMain;
public:
	CFbxMesh*    m_pMesh;
	CFbxMesh*    GetMesh() { return m_pMesh; }  // ���b�V���|�C���^�̎擾
	// ���H�̏����Z�b�g
	virtual void Update(int trainNum, int v, int h) = 0; // ���������֐�
};
//------------------------------------------------
// M.S ���H�̒��ۊ��N���X�I�u�W�F
//------------------------------------------------
class TrainLineObj {
protected:
	int                 LineNum;    // ���H�̎��
public:
	CFbxMesh*           m_pMesh;
	MATRIX4X4			m_mWorld;    // ���H�̈ʒu
	MATRIX4X4			m_mWorldOld;
	MATRIX4X4           GridWorld;   // �L���L���G�t�F�N�g�̈ʒu
	int                 effectObjNum = 0;
	// ���H�̎�ޕϐ��̃Z�b�g
	virtual void SetLineNum(int value) { LineNum = value; }
	// ���H�̎�ޕϐ��̎擾
	int GetLineNum() { return LineNum; }
};
//------------------------------------------------
// M.S �����̐��H(�c)�N���X�v���V�[�W��
//------------------------------------------------
class TrainLineStProc : public TrainLineProc {
protected:
public:
	std::vector<TrainLineStObj*>   m_pTLSObjArray;  // ���H�̔z��
	// �������H�I�u�W�F(�c)�ɏ����Z�b�g
	void Update(int trainNumSt, int v, int h)override; 
	// ���H�̕`��(�S�Ă̐��H)
	void RenderLine(int trainNumSt, int trainNumSd, int TrainNumCg, int trainNumSta, CGameMain* mproc);
	TrainLineStProc(CGameMain* pGMain); // �R���X�g���N�^
	~TrainLineStProc();	// �f�X�g���N�^
};
//------------------------------------------------
// M.S �����̐��H(�c)�N���X�I�u�W�F
//------------------------------------------------
class TrainLineStObj : public TrainLineObj {
protected:
public:
	int stLineMap;  // �z�u�����ʂ̕ۑ�
	// ���b�V���̃Z�b�g
	void SetMesh(TrainLineStProc* pProc) { m_pMesh = pProc->GetMesh(); } 
	// ���H�̎�ޕϐ��̃Z�b�g
	void SetLineNum(int value) override { LineNum = value; } 
	// �R���X�g���N�^
	TrainLineStObj(CGameMain* pGMain);  
	~TrainLineStObj();	// �f�X�g���N�^
};
//------------------------------------------------
// M.S �����̐��H(��)�N���X�v���V�[�W��
//------------------------------------------------
class TrainLineSdProc : public TrainLineProc {
protected:
public:
	std::vector<TrainLineSdObj*>   m_pTLSDObjArray;  // ���H�̔z��
	// �������H�I�u�W�F(��)�ɏ����Z�b�g
	void Update(int trainNumSd, int v, int h)override;
	TrainLineSdProc(CGameMain* pGMain);  // �R���X�g���N�^
	~TrainLineSdProc();	// �f�X�g���N�^
};
//------------------------------------------------
// M.S �����̐��H(��)�N���X�I�u�W�F
//------------------------------------------------
class TrainLineSdObj : public TrainLineObj {
protected:
public:
	int sdLineMap;    // �z�u�����ʂ̕ۑ�
	// ���b�V���̃Z�b�g
	void SetMesh(TrainLineSdProc* pProc) { m_pMesh = pProc->GetMesh(); }
	// ���H�̎�ޕϐ��̃Z�b�g
	void SetLineNum(int value) override { LineNum = value; }
	TrainLineSdObj();   // �R���X�g���N�^
	~TrainLineSdObj();	// �f�X�g���N�^
};
//------------------------------------------------
// M.S �����؂�ւ����H�N���X�v���V�[�W��
//------------------------------------------------
class TrainLineCgProc :public TrainLineProc {
protected:
public:
	std::vector<TrainLineCgObj*>   m_pTCGObjArray;  // ���H�̔z��
	// �����؂�ւ����H�I�u�W�F�ɏ����Z�b�g
	void Update(int trainNumCg, int v, int h)override;
	// �R���X�g���N�^
	TrainLineCgProc(CGameMain* pGMain);
	~TrainLineCgProc();	// �f�X�g���N�^
};
//------------------------------------------------
// M.S �����؂�ւ����H�N���X�I�u�W�F
//------------------------------------------------
class TrainLineCgObj : public TrainLineObj {
protected:
public:
	int cgLineMap;  // �z�u�����ʂ̕ۑ�
	// ���b�V���̃Z�b�g
	void SetMesh(TrainLineCgProc* pProc) { m_pMesh = pProc->GetMesh(); }
	// ���H�̎�ޕϐ��̃Z�b�g
	void SetLineNum(int value) override { LineNum = value; }
	TrainLineCgObj();   // �R���X�g���N�^
	~TrainLineCgObj();	// �f�X�g���N�^
};
//------------------------------------------------
// M.S �w�N���X�v���V�[�W��
//------------------------------------------------
class TrainLineStationProc :public TrainLineProc {
protected:
public:	
	std::vector<TrainLineStationObj*>   m_pTLSTAObjArray;  // ���H�̔z��
	// �w�I�u�W�F�ɏ����Z�b�g
	void Update(int trainNumSta, int v, int h)override;
	// �R���X�g���N�^
	TrainLineStationProc(CGameMain* pGMain);
	~TrainLineStationProc();	// �f�X�g���N�^
};
//------------------------------------------------
// M.S �w�N���X�I�u�W�F
//------------------------------------------------
class TrainLineStationObj : public TrainLineObj {
protected:
public:
	int staLineMap;  // �z�u�����ʂ̕ۑ�
	// ���b�V���̃Z�b�g
	void SetMesh(TrainLineStationProc* pProc) { m_pMesh = pProc->GetMesh(); }
	// ���H�̎�ޕϐ��̃Z�b�g
	void SetLineNum(int value) override { LineNum = value; }
	TrainLineStationObj();  // �R���X�g���N�^
	~TrainLineStationObj();	// �f�X�g���N�^
};