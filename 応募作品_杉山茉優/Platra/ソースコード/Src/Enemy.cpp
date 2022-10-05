//=============================================================================
//		�R�c�Q�[���v���O����
//		�b�R�c�`�����P�P�Q�@�@�@�@�@�@                 ver 3.0        2021.1.11
//
//		�G�L�����N�^�[�̏���
//																Enemy.cpp
//=============================================================================
#include  "Enemy.h"
#include  "Playchar.h"
#include  "Weapon.h"
#include  "Map.h"
#include  "Effect.h"
#include  "BackFore.h"

#include "stdlib.h"
#include "time.h"

//============================================================================
//
// �G���C���v���V�[�W���̃R���X�g���N�^
//
//   �Ȃ��A�v���V�[�W����delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
// ---------------------------------------------------------------------------
CEnmProc::CEnmProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	m_pGMain = pGMain;

	m_pEnmGolemProc = new CEnmGolemProc(m_pGMain);     // HighMan(��)�v���V�[�W���̐���
	m_pProcArray.push_back(m_pEnmGolemProc);           // �v���V�[�W�����v���V�[�W���z��ɓo�^����

	m_pEnmRSProc = new CEnmRSProc(m_pGMain);           // MiddleMan(��)�v���V�[�W���̐���
	m_pProcArray.push_back(m_pEnmRSProc);              // �v���V�[�W�����v���V�[�W���z��ɓo�^����

	m_pEnmBdProc = new CEnmBdProc(m_pGMain);           // LowMan(��)�v���V�[�W���̐���
	m_pProcArray.push_back(m_pEnmBdProc);              // �v���V�[�W�����v���V�[�W���z��ɓo�^����

	// M.S ��]�ɍ��킹�ăZ�b�g����p�x�̕ϐ�
	rotate90angle = 270.0f;
	rotate180angle = 180.0f;
	rotate270angle = 90.0f;
	// M.S ��ԍ��v�l��
	getLowMan = 0;     // M.S ��
	getMiddleMan = 0;  // M.S ��
	getHighMan = 0;    // M.S ��
	// M.S ��̐��ł̏�Ԑl��
	getLowStageMan = 0;     // M.S �� 
	getMiddleStageMan = 0;  // M.S ��
	getHighStageMan = 0;    // M.S ��
	rotateOkFlagMan = true;  // M.S �}�b�v�̉�]���~�߂�t���O
}
//============================================================================
// �G�v���V�[�W���̍X�V
//
//�@�G�̐��𐔂��A�O�ɂȂ�����Q�[���N�����[�ɂ���
//
//   �����@�@�@�Ȃ�
//============================================================================
void	CEnmProc::Update()
{
}
//============================================================================
//
// �S�Ă̓G�v���V�[�W���̔������������l�Ƀ��Z�b�g����
// �i�ő唭����(m_nMaxNum)�𔭐���m_nNum�ɐݒ肷��
//
// ����    CBaseProc* pProc  �ΏۂƂ���v���V�[�W���B�ȗ��l��NULL
//                           NULL�̎��͎��v���V�[�W��
// �߂�l  �Ȃ�
// ---------------------------------------------------------------------------
void CEnmProc::ResetEnmNum(CBaseProc* pProc)
{
	if (pProc)   // �ΏۂƂ���v���V�[�W��
	{
		pProc->SetMaxNum();  // �ő唭����(m_nMaxNum)�𔭐���m_nNum�ɐݒ肷��

		// ���ʂ̃v���V�[�W����T�����Ă���
		for (DWORD i = 0; i < pProc->GetProcArrayPtr().size(); i++)
		{
			ResetEnmNum(pProc->GetProcArrayPtr()[i]);  // �ċA�Ăяo��
		}
	}
	else {   // ���v���V�[�W��
		SetMaxNum();  // �ő唭����(m_nMaxNum)�𔭐���m_nNum�ɐݒ肷��

		// ���ʂ̃v���V�[�W����T�����Ă���
		for (DWORD i = 0; i < m_pProcArray.size(); i++)
		{
			ResetEnmNum(m_pProcArray[i]);  // �ċA�Ăяo��
		}
	}
}
//============================================================================
//
// �S�Ă̓G�I�u�W�F�N�g�̎c���Ă���G�̐��𐔂��鏈��
// �i�c���Ă���G�̐��Ƃ́A�܂��������Ă��Ȃ���(m_nNum�̒l)�{���ݐ����Ă��鐔�̂��Ƃł���j
//
// ����    CBaseProc* pProc  �ΏۂƂ���v���V�[�W���BNULL�̎��͎��v���V�[�W���B�ȗ��l��NULL
//         int        nNum   ��ʂ̃v���V�[�W������^����ꂽ�G�̐��B�ȗ��l��0
//
// �߂�l  int �c���Ă���G�̐�
// ---------------------------------------------------------------------------
int CEnmProc::CountActiveEnm(CBaseProc* pProc, int nNum)
{

	if (pProc)   // �ΏۂƂ���v���V�[�W��
	{
		nNum += pProc->GetNum();									// �v���V�[�W�����Ɏc���Ă���G�̐��i�܂��������Ă��Ȃ����j
		for (DWORD j = 0; j < pProc->GetObjArrayPtr().size(); j++)
		{
			if (pProc->GetObjArrayPtr()[j]->GetActive()) nNum++;	// �I�u�W�F�N�g���ɂ��łɔ������Ă���G�̐��i���ݐ����Ă��鐔�j
		}

		// ���ʂ̃v���V�[�W����T�����Ă���
		for (DWORD i = 0; i < pProc->GetProcArrayPtr().size(); i++)
		{
			nNum = CountActiveEnm(pProc->GetProcArrayPtr()[i], nNum);  // �ċA�Ăяo��
		}
	}
	else {   // ���v���V�[�W��
		nNum += GetNum();											// �v���V�[�W�����Ɏc���Ă���G�̐��i�܂��������Ă��Ȃ����j
		for (DWORD j = 0; j < m_pObjArray.size(); j++)
		{
			if (m_pObjArray[j]->GetActive()) nNum++;				// �I�u�W�F�N�g���ɂ��łɔ������Ă���G�̐��i���ݐ����Ă��鐔�j
		}

		// ���ʂ̃v���V�[�W����T�����Ă���
		for (DWORD i = 0; i < m_pProcArray.size(); i++)
		{
			nNum = CountActiveEnm(m_pProcArray[i], nNum);  // �ċA�Ăяo��
		}
	}
	return nNum;
}
//M.S �Q�[���̏�����������֐�
//��  ���F�Ȃ�
//�߂�l�F�Ȃ�
void CEnmProc::ResetNewGameMan() {
	// �l�L�������̂̃��Z�b�g
	for (int i = 0; i < 6; i++) {
		// HighMan�̃��Z�b�g
		m_pGMain->m_pEnmProc->m_pEnmGolemProc->GetHighManObjPtr(i)->doneProcess = false; 
		m_pGMain->m_pEnmProc->m_pEnmGolemProc->GetHighManObjPtr(i)->alive = true;
		m_pGMain->m_pEnmProc->m_pEnmGolemProc->GetHighManObjPtr(i)->manSurfaceNum = -1;
		m_pGMain->m_pEnmProc->m_pEnmGolemProc->GetHighManObjPtr(i)->thisManArrayNumber = 0;
		m_pGMain->m_pEnmProc->m_pEnmGolemProc->GetHighManObjPtr(i)->initialProcess = true;
		m_pGMain->m_pEnmProc->m_pEnmGolemProc->GetHighManObjPtr(i)->initialRotate = 0.0f;
		m_pGMain->m_pEnmProc->m_pEnmGolemProc->GetHighManObjPtr(i)->initialDeadAnim = 0;
		m_pGMain->m_pEnmProc->m_pEnmGolemProc->GetHighManObjPtr(i)->animCount = 173;

		// MiddleMan�̃��Z�b�g
		m_pGMain->m_pEnmProc->m_pEnmRSProc->GetMiddleManObjPtr(i)->doneProcess = false;
		m_pGMain->m_pEnmProc->m_pEnmRSProc->GetMiddleManObjPtr(i)->alive = true;
		m_pGMain->m_pEnmProc->m_pEnmRSProc->GetMiddleManObjPtr(i)->manSurfaceNum = -1;
		m_pGMain->m_pEnmProc->m_pEnmRSProc->GetMiddleManObjPtr(i)->thisManArrayNumber = 0;
		m_pGMain->m_pEnmProc->m_pEnmRSProc->GetMiddleManObjPtr(i)->initialProcess = true;
		m_pGMain->m_pEnmProc->m_pEnmRSProc->GetMiddleManObjPtr(i)->initialRotate = 0.0f;
		m_pGMain->m_pEnmProc->m_pEnmRSProc->GetMiddleManObjPtr(i)->initialDeadAnim = 0;
		m_pGMain->m_pEnmProc->m_pEnmRSProc->GetMiddleManObjPtr(i)->animCount = 80;

		// LowMan�̃��Z�b�g
		m_pGMain->m_pEnmProc->m_pEnmBdProc->GetLowManObjPtr(i)->doneProcess = false;
		m_pGMain->m_pEnmProc->m_pEnmBdProc->GetLowManObjPtr(i)->alive = true;
		m_pGMain->m_pEnmProc->m_pEnmBdProc->GetLowManObjPtr(i)->manSurfaceNum = -1;
		m_pGMain->m_pEnmProc->m_pEnmBdProc->GetLowManObjPtr(i)->thisManArrayNumber = 0;
		m_pGMain->m_pEnmProc->m_pEnmBdProc->GetLowManObjPtr(i)->initialProcess = true;
		m_pGMain->m_pEnmProc->m_pEnmBdProc->GetLowManObjPtr(i)->initialRotate = 0.0f;
		m_pGMain->m_pEnmProc->m_pEnmBdProc->GetLowManObjPtr(i)->initialDeadAnim = 0;
		m_pGMain->m_pEnmProc->m_pEnmBdProc->GetLowManObjPtr(i)->animCount = 60;
	}

	for (int i = 0; i < 6; i++) {
		// �z�u�ʒu�i�[�z��̏�����
		m_pGMain->m_pEnmProc->m_pEnmGolemProc->numH[i] = 0;
		m_pGMain->m_pEnmProc->m_pEnmGolemProc->numV[i] = 0;
		m_pGMain->m_pEnmProc->m_pEnmRSProc->numH[i] = 0;
		m_pGMain->m_pEnmProc->m_pEnmRSProc->numV[i] = 0;
		m_pGMain->m_pEnmProc->m_pEnmBdProc->numH[i] = 0;
		m_pGMain->m_pEnmProc->m_pEnmBdProc->numV[i] = 0;
		// �z�u�ς݂��m�F�z��̏�����
		m_pGMain->m_pEnmProc->m_pEnmGolemProc->PlacementManMap[i] = 0;
		m_pGMain->m_pEnmProc->m_pEnmRSProc->PlacementManMap[i] = 0;
		m_pGMain->m_pEnmProc->m_pEnmBdProc->PlacementManMap[i] = 0;
	}
	// HighMan�v���V�[�W���̃��Z�b�g
	m_pGMain->m_pEnmProc->m_pEnmGolemProc->manNum = 0;
	m_pGMain->m_pEnmProc->m_pEnmGolemProc->exclusiveMan = false;
	m_pGMain->m_pEnmProc->m_pEnmGolemProc->surfaceNumTarget = 0;
	m_pGMain->m_pEnmProc->getHighStageMan = 0;
	m_pGMain->m_pEnmProc->m_pEnmGolemProc->managementDeadProcess = false;
	// MiddleMan�v���V�[�W���̃��Z�b�g
	m_pGMain->m_pEnmProc->m_pEnmRSProc->manNum = 0;
	m_pGMain->m_pEnmProc->m_pEnmRSProc->exclusiveMan = false;
	m_pGMain->m_pEnmProc->m_pEnmRSProc->surfaceNumTarget = 0;
	m_pGMain->m_pEnmProc->getMiddleStageMan = 0;
	m_pGMain->m_pEnmProc->m_pEnmRSProc->managementDeadProcess = false;
	// LowMan�v���V�[�W���̃��Z�b�g
	m_pGMain->m_pEnmProc->m_pEnmBdProc->manNum = 0;
	m_pGMain->m_pEnmProc->m_pEnmBdProc->exclusiveMan = false;
	m_pGMain->m_pEnmProc->m_pEnmBdProc->surfaceNumTarget = 0;
	m_pGMain->m_pEnmProc->getLowStageMan = 0;
	m_pGMain->m_pEnmProc->m_pEnmBdProc->managementDeadProcess = false;
}
// =====================================================================================================
// 
// �e�G�v���V�[�W�����̏���
// 
// =====================================================================================================

//============================================================================
//
// �G�S�[�����v���V�[�W���̃R���X�g���N�^
//
//   �Ȃ��A�I�u�W�F�N�g��delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
// ---------------------------------------------------------------------------
CEnmGolemProc::CEnmGolemProc(CGameMain* pGMain) : CBaseProc( pGMain)
{
	const int nWait    = 400;                   // �G����������܂ł̑҂�����
	m_dwProcID         = ENM_GOLEM_ID;          // �G�S�[������ID
	m_nNum = m_nMaxNum = ENM_GOLEM_ALLMAX;      // �G�S�[�����̍ő�o����
	// Fbx�X�L�����b�V���̐ݒ�
	m_pMesh = new CFbxMesh( m_pGMain->m_pFbxMeshCtrl, _T("Data/Char/Man/highMan_Breath.mesh"));
	m_pMesh->LoadAnimation(_T("Data/Char/Man/highMan_Breath.anmx"));
	m_pMesh->LoadAnimation(_T("Data/Char/Man/highMan_Happy.anmx"));
	m_pMesh->LoadAnimation(_T("Data/Char/Man/man_JumpingMotion.anmx"));
	m_pMesh->m_fHeightMax = 0.05f;     // �f�B�X�v���[�X�����g�}�b�s���O�̍���  // -- 2020.1.24
	m_pMesh->m_iMaxDevide = 64;
	m_nHoldItem.m_nHoldObjNo = 0;	// ��Ɏ�����̃I�u�W�F�ԍ�(�ݒ肵�Ȃ�)  // -- 2021.2.4
	for (int i = 0; i < ENM_GOLEM_MAX; i++)
	{
		m_pObjArray.push_back( new CEnmGolemObj(m_pGMain) );  // m_pObjArray�ɃI�u�W�F�N�g�𐶐�����
		m_pObjArray[i]->SetObjID(m_dwProcID);						// -- 2021.2.4
		m_pObjArray[i]->SetObjNo(i);
		((CEnmGolemObj*)m_pObjArray[i])->SetMesh(this);    // ���b�V���̃A�h���X���I�u�W�F�N�g�ɐݒ肷��   // -- 2021.2.4
	}
	m_nWaitTime = m_nMaxwaitTime = nWait;
	manNum = 0;                     // M.S �z�u�ςݐl��
	exclusiveMan = false;           // M.S �z�u���t���O
	surfaceNumTarget = 0;           // M.S ���ׂ�ʂ̐���
	managementDeadProcess = false;  // M.S ��ԏ������t���O
}
//============================================================================
//
// �G�S�[�����v���V�[�W���̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CEnmGolemProc::~CEnmGolemProc()
{
	SAFE_DELETE(m_pMesh);
}
//============================================================================
//
// �G�S�[�����I�u�W�F�N�g�̃R���X�g���N�^
//
//  ����
//  CGameMain* pGMain;		// �Q�[�����C���N���X�ւ̃|�C���^
//
// ---------------------------------------------------------------------------
CEnmGolemObj::CEnmGolemObj( CGameMain* pGMain) : CBaseObj( pGMain)
{
	const int nMaxHP = 1200;     // �̗�
	const int nAtc   = 200;      // �̂̍U����
	m_bActive = FALSE;
	m_dwStatus = NORMAL;
	m_vTarget = GetPositionVector(m_mWorld);
	// �I�u�W�F�N�g�̃o�E���f�B���O�{�b�N�X�̐ݒ�
	VECTOR3 vMin(-1.8f, -0.05f, -1.0f);
	VECTOR3 vMax(1.8f, 7.5f, 1.0f);
	m_pBBox = new CBBox(m_pGMain->m_pShader, vMin, vMax);
	m_pBBox->m_mWorld = m_mWorld;                            // -- 2021.1.11
	m_nHp = m_nMaxHp = nMaxHP;
	m_nAtc = nAtc;
	doneProcess = false;   // M.S �z�u���Ă��邩�t���O
	alive = true;          // M.S ����ԏ����t���O
	manSurfaceNum = -1;	    // M.S �l�I�u�W�F�N�g������ʂ̐���
	thisManArrayNumber = 0; // M.S �z�u�������Ԃ̕ۑ�
	initialProcess = true;  // M.S �ŏ��݂̂̏����t���O
	// M.S �v���C�L�����̕�������������p�x���}�b�v�̉�]�ɍ��킹�Ē�������ϐ�
	initialRotate = 0.0f;
	// M.S 0:�܂�����ɒʉߍς݉w���H���Ȃ� 1:����ɒʉߍς݉w���H������ 3:��荞�݃A�j���[�V�����Ə������I��
	initialDeadAnim = 0;
	// M.S ��ԃA�j���[�V�����̃^�C���J�E���g
	animCount = 173;
	// M.S ��ԃA�j���[�V�����̎���
	saveAnimCount = 173;
}
// ---------------------------------------------------------------------------
//
// �G�S�[�����I�u�W�F�N�g�̃f�X�g���N�^
//
//   �Ȃ��ACBBox��delete��CBaseObj�̃f�X�g���N�^�ōs�����ߕs�v
//
// ---------------------------------------------------------------------------
CEnmGolemObj::~CEnmGolemObj()
{
}
// ---------------------------------------------------------------------------  // -- 2021.2.4
//
// �G�S�[�����I�u�W�F�N�g�̃��b�V���|�C���^�ݒ�
//
//  CEnmGolemProc* pProc
//
// ---------------------------------------------------------------------------
void CEnmGolemObj::SetMesh(CEnmGolemProc* pProc)
{
	m_pMesh = pProc->GetMesh();					// �X�L�����b�V���̃|�C���^
	m_nHoldItem = pProc->GetHoldItem();			// ��Ɏ�����̏��𓾂�

	m_AnimStatus.SetNum(0);
	m_AnimStatus.animFrame = 0;
}
// M.S �z�u����ʒu��r�o����֐�
// ��  ���F�Ȃ�
// �߂�l�F�Ȃ�
void CEnmGolemProc::ResetPlacementMan() {
	srand(time(NULL));              // �����p�^�[���̎擾
	for (int i = 0; i < 6; i++) {
		int num = rand() % 10;  // �����_���ňʒu�擾
		int var = num;          // ver�ɐݒ�
		num = rand() % 10;      // �����_���ňʒu�擾
		int hori = num;         // hori�ɐݒ�
		for (int num = 0; num < 100; num++) {
		// �Q�[���J�n���ɑ���ł��Ȃ��悤�ɂȂ�Ȃ�(�l�܂Ȃ�)���߂ɒ���
		// �z�u����s��3�ȉ��Ȃ��ver��hori���Đݒ�
			if (i == 0 && hori <= 3) {
				int againNum = rand() % 10; 
				var = againNum;
				againNum = rand() % 10;
				hori = againNum;
			}
			else {
				break;
			}
		}
		// �z��ɔz�u����s�Ɨ���Z�b�g
		numH[i] = hori; 
		numV[i] = var;
	}
}
// ---------------------------------------------------------------------------
//
// �G�S�[�����v���V�[�W���̎�����������
//
//
// ---------------------------------------------------------------------------
void CEnmGolemProc::Update()
{
	// M.S �}�b�v������2���ǂ���
	if (m_pGMain->m_pMapProc->MapNumGet() == 2) {    
		VECTOR3 mHit;
		VECTOR3 mNor;
      	// M.S ���݂̐��H�z�u�\�̖ʂ𒲂ׂ�
		for (int i = 0; i < 6; i++) {
			// M.S ����(����z�u�\��)�����ׂ邽�߃��C���΂��ʒu�ϐ�
			MATRIX4X4 upFront = XMMatrixTranslation(0.0f, 10.0f, 0.0f);
			MATRIX4X4 upBack = XMMatrixTranslation(0.0f, 3.0f, 0.0f);
			bool nowPosSurfaceflag = m_pGMain->m_pMapProc->m_pBBoxPosition[i]->
				OBBCollisionLay(/*back*/upBack, /*front*/upFront, &mHit, &mNor);
           // M.S ���ׂ��ʂɂ܂��l��z�u���Ă��Ȃ�
		   // �z�u���̐l�I�u�W�F�N�g���Ȃ���Δz�u����
			if (nowPosSurfaceflag == true) {
				surfaceNumTarget = i;
				if ((PlacementManMap[surfaceNumTarget] == 0)
					&& (m_pGMain->m_pEnmProc->m_pEnmGolemProc->exclusiveMan == false)) {
					if (manNum < 6) {
						m_pObjArray[manNum]->Start();
						manNum++;     // M.S �z�u�ςݐl���𑫂�
					}
		    // M.S �z�u���I��������PlacementManMap�̂��̖ʂ̗v�f��1�������
					PlacementManMap[surfaceNumTarget] = 1;
					break;
				}
			}
		}
	}
}
// ---------------------------------------------------------------------------
//
// �G�S�[�����I�u�W�F�N�g�̔���
//
// ---------------------------------------------------------------------------
BOOL CEnmGolemObj::Start()
{
	// M.S �}�b�v2���܂��z�u���Ă��Ȃ��l�I�u�W�F�N�g��������
	if ((m_pGMain->m_pMapProc->MapNumGet() == 2) && (doneProcess == false)) {
		srand(time(NULL));              // M.S �����p�^�[���̎擾
		// M.S �}�b�v�̉�]�\�t���O��false
		m_pGMain->m_pMapProc->doneManPlacement = false;
		// M.S �l�I�u�W�F�N�g���쒆�t���O��true
		m_pGMain->m_pEnmProc->m_pEnmGolemProc->exclusiveMan = true;		
		// M.S ��]�p�x�t���O��������
		rotate0 = false;
		rotate90 = false;
		rotate180 = false;   
		rotate270 = false;		
		// M.S ����(����\��)�̈ʒu�̕ϐ�
		VECTOR3 frontPos = VECTOR3(0.0f, 6.0f, 0.0f);
		// M.S �z�u����ʂ̌��݂̉�]�𒲂ׂ�  
		// rotate0:0�x��] rotate90:90�x��] rotate180:180�x��] rotate270:270�x��]
		int northNow = m_pGMain->m_pPcProc->
			judgeDirection(m_pGMain->m_pEnmProc->m_pEnmGolemProc->surfaceNumTarget, frontPos, 0);
		switch (northNow) {
		case 1:
			rotate0 = true;
			break;
		case 2:
			rotate90 = true;
			break;
		case 3:
			rotate180 = true;
			break;
		case 4:
			rotate270 = true;
			break;
		}
		// M.S �l�I�u�W�F�N�g�̔z�u���Ă���l���̐�����manArrayNum�ɓ����
		int manArrayNum = m_pGMain->m_pEnmProc->m_pEnmGolemProc->manNum;
		// M.S �z�u�����̐l�I�u�W�F�N�g�Əd�Ȃ��Ă��Ȃ����A�d�Ȃ��Ă����ꍇ�ēx�����Ŕz�u�����߂�
		int investigateHori = m_pGMain->m_pEnmProc->m_pEnmGolemProc->numH[manArrayNum];
		int investigateVer = m_pGMain->m_pEnmProc->m_pEnmGolemProc->numV[manArrayNum];
		for (int i = 0; i < 100; i++) {
			if (m_pGMain->m_pMapProc->lineMap1[investigateHori][investigateVer] == 0) {
				break;
			}
			int hori = rand() % 10;
			int var = rand() % 10;
			for (int num = 0; num < 100; num++) {
				hori = rand() % 10;
				var = rand() % 10;
				// M.S �Q�[���J�n���ɑ���ł��Ȃ��悤�ɂȂ�Ȃ�(�l�܂Ȃ�)���߂ɒ���
				// M.S �����ʂłȂ��A�܂���hori��3���傫���Ȃ��
				if (manArrayNum != 0 || hori > 3) {
					// M.S �z���hori��var���Z�b�g���ă��[�v�𔲂���
					m_pGMain->m_pEnmProc->m_pEnmGolemProc->numH[manArrayNum] = hori;
					m_pGMain->m_pEnmProc->m_pEnmGolemProc->numV[manArrayNum] = var;
					// M.S investigateHori��investigateVer�ɒl���Z�b�g
					investigateHori = hori;
					investigateVer = var;
					break;
				}
			}
		}
		// M.S �}�b�v�z��ʂ̐����ƍ��W�̈ʒu�����킹�鐔�̕ϐ�
		float adjustPlusPos = 4.5f;    
		float adjustMinusPos = -4.5f;
		float yPos = 5.0f;   // M.S �z�u���鍂��(Y���W)
		// M.S �}�b�v�̉�]�ɍ��킹�Ĕz�u�ʒu�Ɖ�]��initialRotate�ɕۑ�
		if (rotate0 == true) {
			m_mWorld = XMMatrixTranslation(adjustMinusPos + 1 * investigateVer, yPos, adjustPlusPos -1 * investigateHori);
		}
		else if (rotate90 == true) {
			m_mWorld = XMMatrixTranslation(adjustPlusPos - 1 * investigateHori, yPos, adjustPlusPos - 1 * investigateVer);
			initialRotate = m_pGMain->m_pEnmProc->rotate90angle;
		}
		else if (rotate180 == true) {
			m_mWorld = XMMatrixTranslation(adjustPlusPos - 1 * investigateVer, yPos, adjustMinusPos + 1 * investigateHori);
			initialRotate = m_pGMain->m_pEnmProc->rotate180angle;
		}
		else if (rotate270 == true) {
			m_mWorld = XMMatrixTranslation(adjustMinusPos + 1 * investigateHori, yPos, adjustMinusPos + 1 * investigateVer);
			initialRotate = m_pGMain->m_pEnmProc->rotate270angle;
		}
	    m_bActive = TRUE;
	    // M.S �l�I�u�W�F�N�g�̔z�u����Ă���ʂ�ۑ�
		manSurfaceNum = m_pGMain->m_pEnmProc->m_pEnmGolemProc->surfaceNumTarget;
		// M.S �}�b�v�z����X�V
		m_pGMain->m_pMapProc->lineMap1[investigateHori][investigateVer] = 10;
		// M.S �}�b�v�̉�]�\�t���O��true
		m_pGMain->m_pMapProc->doneManPlacement = true;
		// M.S �l�I�u�W�F�N�g�̔z�u���Ă���l���̐�����ۑ�
		thisManArrayNumber = manArrayNum;
		// M.S �l�I�u�W�F�N�g���쒆�t���O��false
		m_pGMain->m_pEnmProc->m_pEnmGolemProc->exclusiveMan = false;
		// M.S �z�u�ς�
		doneProcess = true;
		return TRUE;
	}
	return FALSE;
}
// M.S �v���C�L�����̈ʒu�ɍ��킹��
// �l�I�u�W�F�N�g�ƃv���C�L��������ʂɂ���Ƃ����ʒu������
// ��  ���F�Ȃ�
// �߂�l�F�Ȃ�
void	CEnmGolemObj::OutUpPos() {
	switch (m_pGMain->m_pPcProc->GetPcObjPtr()->nowPcPosNum) {
	case 0:
		manPos = VECTOR3(manPos.x, manPos.y, manPos.z);
		pcPos = VECTOR3(pcPos.x, pcPos.y, pcPos.z);
		break;
	case 1:
		manPos = VECTOR3(manPos.x, 5.0f, manPos.y);
		pcPos = VECTOR3(pcPos.x, 5.0f, pcPos.y);
		break;
	case 2:
		manPos = VECTOR3(manPos.x, 5.0f, -1.0f * manPos.z);
		pcPos = VECTOR3(pcPos.x, 5.0f, -1.0f * pcPos.z);
		break;
	case 3:
		manPos = VECTOR3(manPos.x, 5.0f, -1.0f * manPos.y);
		pcPos = VECTOR3(pcPos.x, 5.0f, -1.0f * pcPos.y);
		break;
	case 4:
		manPos = VECTOR3(-1.0f * manPos.y, 5.0f, manPos.z);
		pcPos = VECTOR3(-1.0f * pcPos.y, 5.0f, pcPos.z);
		break;
	case 5:
		manPos = VECTOR3(manPos.y, 5.0f, manPos.z);
		pcPos = VECTOR3(pcPos.y, 5.0f, pcPos.z);
		break;
	}
}
//-----------------------------------------------------------------------------
// �G�S�[�����I�u�W�F�N�g�̐���
//
//�@�L�[�{�[�h�ƃ}�E�X�œG�𓮂���
//�@�G�̃A�j���[�V�����A�W�����v�A���R����
//�@���[���h���W�ϊ��A�}�b�v�Ƃ̐ڐG����@���̑�
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CEnmGolemObj::Update()
{
	if (!m_bActive) return;  // ��\���̂Ƃ��͏��������Ȃ�

	if (alive == true ) {
		// �ϐ��̏�����  ---------------------------------------
		m_vPosUp.x = m_vPosUp.y = m_vPosUp.z = 0.0f;
		m_vRotUp.x = m_vRotUp.y = m_vRotUp.z = 0.0f;
		m_mWorldOld = m_mWorld;  // ��O�̈ʒu
		// M.S �}�b�v�̉�]���~�߂�
		m_pGMain->m_pEnmProc->rotateOkFlagMan = false;
		// M.S �v���C�L�����Ɛl�I�u�W�F�N�g�̂���ʂ���v���Ă����ꍇ
		if ((manSurfaceNum == m_pGMain->m_pPcProc->GetPcObjPtr()->surfaceNum) 
			&& m_pGMain->m_pMapProc->MapNumGet() == 2) {
			// M.S �v���C�L�����̈ʒu���擾
			pcPos = GetPositionVector(m_pGMain->m_pPcProc->GetPcObjPtr()->GetWorld());
			// M.S �l�I�u�W�F�N�g�̈ʒu���擾
			manPos = GetPositionVector(m_mWorld);
			float plusAngle = 0.0f;  // M.S ��]�̊p�x
			// M.S ���̐l�I�u�W�F�N�g�̂���ʂ̉�]�𒲂ׂ�
			int north = m_pGMain->m_pPcProc->judgeDirection(manSurfaceNum, manPos, 1);
			// M.S ���ׂ���]�����킹��plusAngle�Ɋp�x�������
			switch (north) {  // M.S 1:��]�Ȃ� 2:�E90�x��] 3:�E180�x��] 4:�E270�x��] 
			case 1:
				break;
			case 2:
				plusAngle = m_pGMain->m_pEnmProc->rotate90angle;
				break;
			case 3:
				plusAngle = m_pGMain->m_pEnmProc->rotate180angle;
				break;
			case 4:
				plusAngle = m_pGMain->m_pEnmProc->rotate270angle;
			}
			// M.S �v���C�L�����̈ʒu�ɍ��킹��
			// �l�I�u�W�F�N�g�ƃv���C�L��������ʂɂ���Ƃ����ʒu������
			OutUpPos();
			// M.S �l�I�u�W�F�N�g���v���C�L�����������Ă���}�g���b�N�X
			MATRIX4X4 manLookWorld = GetLookatMatrix(manPos, pcPos);
			// M.S manLookWorld��Y�v�f�����o��
			MATRIX4X4 manLookRotateY = GetRotateMatrixY(manLookWorld);
			// M.S manLookRotateY��vector�i�p�x�j
			VECTOR3 manLookRotate = GetRotateVector(manLookRotateY);
			// M.S manLookRotate.y + �ʂ̉�] - �z�u���̊p�x����
			manLookRotate.y = manLookRotate.y + plusAngle - initialRotate;
			// M.S manLookRotate.y��360��菬�����Ȃ�悤�ɂ���
			for (int i = 0; i < 100; i++) {
				if (manLookRotate.y >= 360) {
					manLookRotate.y = manLookRotate.y - 360.0f;
				}
				else {
					break;
				}
			}
			// M.S manLookRotate.y(�v���C�L�����̕���������)�̉�]�}�g���b�N�X
			manRotate = XMMatrixRotationY(XMConvertToRadians(manLookRotate.y));
			if (initialProcess == true) {
				// M.S �ŏ��݂̂̏���
				m_mWorld = manRotate * m_mWorld;
				initialProcess = false;
			}
			else {
				// M.S manRotateOld�������Ė߂��Ă���manRotate�������ăv���C���[�̕�����������
				MATRIX4X4 returnManRotate = manRotateOld * m_mWorld;
				m_mWorld = manRotate * returnManRotate;
			}
			// M.S �߂���]��ۑ�
			manRotateOld = XMMatrixRotationY(XMConvertToRadians(360.0f - manLookRotate.y));
			// M.S �}�b�v�̉�]���ł���悤�ɂ���
			m_pGMain->m_pMapProc->doneManPlacement = true;
			// M.S �v���C�L�������߂Â������̃A�j���[�V�����̕ύX
			float distance = magnitude(manPos - pcPos);
			if (distance <= 2.0f && initialDeadAnim != 1) {
				m_AnimStatus.SetNum(1);
			}
			else if (initialDeadAnim == false) {
				m_AnimStatus.SetNum(0);
			}
			// M.S �w���߂��ɒu���ꂽ���̏���
			UpdateDead();
		}
		// M.S �}�b�v�̉�]���\�ɂ���
		m_pGMain->m_pEnmProc->rotateOkFlagMan = true;
		// �`�揈��  ---------------------------------------------
		// �X�L�����b�V�������_�����O
		int shineFlag = 0;    // M.S �����_�[�̎w��
		m_pMesh->Render(m_AnimStatus, m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt, shineFlag);
		// �o�E���f�B���O�{�b�N�X
		m_pBBox->m_mWorld = m_mWorld;
	}
}

//-----------------------------------------------------------------------------
// �G�S�[�����I�u�W�F�N�g�̐���
//
//�@�G���ʏ��Ԃ̂Ƃ��̏���
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CEnmGolemObj::UpdateNormal()
{
}

//-----------------------------------------------------------------------------
// �G�S�[�����I�u�W�F�N�g�̐���
//
//  �G���_���[�W��Ԃ̂Ƃ��̏���
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CEnmGolemObj::UpdateDamage()
{
	
}

//-----------------------------------------------------------------------------
// �G�S�[�����I�u�W�F�N�g�̐���
//
//  �G�����S��Ԃ̂Ƃ��̏���
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CEnmGolemObj::UpdateDead()
{
	int afterStationNum = 8;  // M.S �v���C���[���ʉߌ�̔z��ɓ����Ă��鐔��
	int humanNum = 10;        // M.S �l�L����������ꏊ�ɓ����Ă��鐔��
	int afterHumanNum = 0;    // M.S �l�L������Ԍ�ɔz��ɓ����Ă��鐔��(������)
	// M.S �z�u����Ă���l�I�u�W�F�N�g�������ꍇ
	if (doneProcess == true && alive == true) {
		// M.S �Z�����邽�߂ɍs�A���ϐ��ɓ����
		int hori = m_pGMain->m_pEnmProc->m_pEnmGolemProc->numH[thisManArrayNumber];
		int ver = m_pGMain->m_pEnmProc->m_pEnmGolemProc->numV[thisManArrayNumber];
		// M.S �}�b�v���ʂ������ꍇ�A�㉺���E�ǂ����ɉw�I�u�W�F�N�g����������
		if (m_pGMain->m_pPcProc->GetPcObjPtr()->frontFlag == true) {		
			if (m_pGMain->m_pMapProc->lineMap1[hori][ver] == humanNum
				&&(m_pGMain->m_pMapProc->lineMap1[hori + 1][ver] == afterStationNum
				|| m_pGMain->m_pMapProc->lineMap1[hori - 1][ver] == afterStationNum
				|| m_pGMain->m_pMapProc->lineMap1[hori][ver + 1] == afterStationNum
				|| m_pGMain->m_pMapProc->lineMap1[hori][ver - 1] == afterStationNum)) {
				if (initialDeadAnim == 0) {    // M.S ��ԃt�F�[�Y��0�̏ꍇ
					// M.S ��ԏ������t���O��true
					m_pGMain->m_pEnmProc->m_pEnmGolemProc->managementDeadProcess = true;
					m_AnimStatus.SetNum(2);	   // M.S ��ԃA�j���[�V�������Z�b�g
					m_AnimStatus.animFrame = m_AnimStatus.endFrame - 1; // �t���[���G���h�̈��O�ɂ���
					initialDeadAnim = 1;       // M.S ��ԃt�F�[�Y��1�ɂ���
				}
				// M.S ��ԃA�j���[�V�������I�������(animCount��0�ȉ��Ȃ��)
				else if(animCount <= 0){     
					animCount = saveAnimCount;     // M.S animCount�����Ƃɖ߂�
					initialDeadAnim = 3;           // M.S ��ԃt�F�[�Y��3�ɂ���
					// M.S HighMan(��)�̏�Ԑl����+1
					m_pGMain->m_pEnmProc->getHighStageMan++;  
					// M.S ��Ԍ�̃}�b�v�z���0�ɂ��čX�V
					m_pGMain->m_pMapProc->lineMap1[hori][ver] = afterHumanNum;
					// M.S ��ԏ������t���O��false
					m_pGMain->m_pEnmProc->m_pEnmGolemProc->managementDeadProcess = false;
					m_bActive = FALSE; 		      // M.S ��ʂɕ\�������Ȃ�
					m_pGMain->rideSound->Play();  // M.S ��Ԍ��ʉ�
					m_AnimStatus.SetNum(0);       // M.S �A�j���[�V���������ɖ߂�
					alive = false;                // M.S ����ԏ����t���O��false
				}
				animCount--;                // M.S �A�j���[�V�������鎞�Ԃ�����
			}
		}
		else {
			// M.S �}�b�v���ʈȊO�������ꍇ�A�㉺���E�ǂ����ɉw�I�u�W�F�N�g����������
			if (m_pGMain->m_pPcProc->lineMapSub[hori][ver] == humanNum
				&& (m_pGMain->m_pPcProc->lineMapSub[hori + 1][ver] == afterStationNum
				|| m_pGMain->m_pPcProc->lineMapSub[hori - 1][ver] == afterStationNum
				|| m_pGMain->m_pPcProc->lineMapSub[hori][ver + 1] == afterStationNum
				|| m_pGMain->m_pPcProc->lineMapSub[hori][ver - 1] == afterStationNum)) {
				if (initialDeadAnim == 0) {    // M.S ��ԃt�F�[�Y��0�̏ꍇ
					// M.S ��ԏ������t���O��true
					m_pGMain->m_pEnmProc->m_pEnmGolemProc->managementDeadProcess = true;
					m_AnimStatus.SetNum(2);    // M.S ��ԃA�j���[�V�������Z�b�g
					m_AnimStatus.animFrame = m_AnimStatus.endFrame - 1; // �t���[���G���h�̈��O�ɂ���
					initialDeadAnim = 1;       // M.S ��ԃt�F�[�Y��1�ɂ���
				}
				// M.S ��ԃA�j���[�V�������I�������(animCount��0�ȉ��Ȃ��)
				else if (animCount <= 0) {  
					animCount = saveAnimCount;   // M.S animCount�����Ƃɖ߂�
					initialDeadAnim = 3;         // M.S ��ԃt�F�[�Y��3�ɂ���			
					// M.S HighMan(��)�̏�Ԑl����+1	
					m_pGMain->m_pEnmProc->getHighStageMan++;      
					// M.S �}�b�v�z���0�ɂ���
					m_pGMain->m_pPcProc->lineMapSub[hori][ver] = afterHumanNum; 
					// M.S �}�b�v�z��̍X�V
					m_pGMain->m_pPcProc->lineMapSet(manSurfaceNum);   
					// M.S ��ԏ������t���O��false
					m_pGMain->m_pEnmProc->m_pEnmGolemProc->managementDeadProcess = false;
					m_bActive = FALSE; 		      // M.S ��ʂɕ\�������Ȃ�
					m_pGMain->rideSound->Play();  // M.S ��Ԍ��ʉ�
					m_AnimStatus.SetNum(0);       // M.S �A�j���[�V���������ɖ߂�
					alive = false;                // M.S ����ԏ����t���O��false
				}
				animCount--;                      // M.S �A�j���[�V�������鎞�Ԃ�����
			}
		}
	}
}

//============================================================================
//
// �G�q�r�v���V�[�W���̃R���X�g���N�^
//
//   �Ȃ��A�I�u�W�F�N�g��delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
// ---------------------------------------------------------------------------
CEnmRSProc::CEnmRSProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	const int nWait    = 500;                   // �G����������܂ł̑҂�����
	m_dwProcID         = ENM_RS_ID;             // �G�q�r��ID
	m_nNum = m_nMaxNum = ENM_RS_ALLMAX;         // �G�q�r�̍ő�o����

	// Fbx�X�L�����b�V���̐ݒ�
	m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Char/Man/MiddleMan_Idle.mesh") );
	m_pMesh->LoadAnimation(_T("Data/Char/Man/MiddleMan_Idle.anmx"), eRootAnimXZ);
	m_pMesh->LoadAnimation(_T("Data/Char/Man/MiddleMan_HappyIdle.anmx"));
	m_pMesh->LoadAnimation(_T("Data/Char/Man/MiddleMan_Jump.anmx"));
	m_pMesh->m_fHeightMax = 0.01f;
	m_pMesh->m_iMaxDevide = 8;
	m_nHoldItem.m_nHoldObjNo = 7;	// ��Ɏ�����̃I�u�W�F�ԍ�(�����ȏ�)  // -- 2021.2.4
	m_nHoldItem.m_nPosMesh = 0;		// ���̍����ʒu�̃��b�V���ԍ�
	m_nHoldItem.m_nPosBone = 48;	// ���̍����ʒu�̃{�[���ԍ�
	m_nHoldItem.m_nOffsetPos = VECTOR3(0.0f, -0.5f, 0.0f);  // ��Ɏ�����̈ʒu�I�t�Z�b�g
	m_nHoldItem.m_nOffsetRot = VECTOR3(-20.0f, -70.0f, -30.0f);  // ��Ɏ�����̊p�x�I�t�Z�b�g

	for (int i = 0; i < ENM_RS_MAX; i++)
	{
		m_pObjArray.push_back(new CEnmRSObj(m_pGMain));  // m_pObjArray�ɃI�u�W�F�N�g�𐶐�����
		m_pObjArray[i]->SetObjID(m_dwProcID);						// -- 2021.2.4
		m_pObjArray[i]->SetObjNo(i);
		((CEnmRSObj*)m_pObjArray[i])->SetMesh(this);  // ���b�V���̃A�h���X���I�u�W�F�N�g�ɐݒ肷��  // -- 2021.2.4
	}

	m_nWaitTime = m_nMaxwaitTime = nWait;
	exclusiveMan = false;         // M.S �z�u���t���O
	surfaceNumTarget = 0;          // M.S ���ׂ�ʂ̐���
	managementDeadProcess = false;  // M.S ��ԏ������t���O
}
//============================================================================
//
// �G�q�r�v���V�[�W���̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CEnmRSProc::~CEnmRSProc()
{
	SAFE_DELETE(m_pMesh);
}
//============================================================================
//
// �G�q�r�I�u�W�F�N�g�̃R���X�g���N�^
//
//  ����
//  CGameMain* pGMain;		// �Q�[�����C���N���X�ւ̃|�C���^
//
// ---------------------------------------------------------------------------
CEnmRSObj::CEnmRSObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	const int nMaxHP = 800;      // �̗�
	const int nAtc   = 150;      // �̂̍U����

	m_bActive = FALSE;
	m_dwStatus = NORMAL;

	m_vTarget = GetPositionVector(m_mWorld);

	// �o�E���f�B���O�{�b�N�X�̐ݒ�
	VECTOR3 vMin(-1.0f, -0.05f, -1.0f);
	VECTOR3 vMax(1.0f, 2.7f, 1.5f);
	m_pBBox = new CBBox(m_pGMain->m_pShader, vMin, vMax);
	m_pBBox->m_mWorld = m_mWorld;                            // -- 2021.1.11

	m_nHp = m_nMaxHp = nMaxHP;
	m_nAtc = nAtc;

	doneProcess = false;    // M.S �z�u���Ă��邩�t���O
	alive = true;           // M.S ����ԏ����t���O
	manSurfaceNum = -1;       // M.S �l�I�u�W�F�N�g������ʂ̐���
	thisManArrayNumber = 0;  // M.S �z�u�������Ԃ̕ۑ�
	initialProcess = true;  // M.S �ŏ��݂̂̏����t���O
	// M.S �v���C�L�����̕�������������p�x���}�b�v�̉�]�ɍ��킹�Ē�������ϐ�
	initialRotate = 0.0f;
	// M.S 0:�܂�����ɒʉߍς݉w���H���Ȃ� 1:����ɒʉߍς݉w���H������ 3:��荞�݃A�j���[�V�����Ə������I��
	initialDeadAnim = 0;
	// M.S ��ԃA�j���[�V�����̃^�C���J�E���g
	animCount = 80;
	// M.S ��ԃA�j���[�V�����̎���
	saveAnimCount = 80;
}
// ---------------------------------------------------------------------------
//
// �G�q�r�I�u�W�F�N�g�̃f�X�g���N�^
//
//   �Ȃ��ACBBox��delete��CBaseObj�̃f�X�g���N�^�ōs�����ߕs�v
//
// ---------------------------------------------------------------------------
CEnmRSObj::~CEnmRSObj()
{
	;
}
// ---------------------------------------------------------------------------
//
// �G�q�r�I�u�W�F�N�g�̃��b�V���|�C���^�ݒ�
//
//  CEnmRSProc* pProc
//
// ---------------------------------------------------------------------------  // -- 2021.2.4
void CEnmRSObj::SetMesh(CEnmRSProc* pProc)
{
	m_pMesh = pProc->GetMesh();					// �X�L�����b�V���̃|�C���^
	m_nHoldItem = pProc->GetHoldItem();			// ��Ɏ�����̏��𓾂�

	m_AnimStatus.SetNum(0);
	m_AnimStatus.animFrame = 0;
}
// M.S �z�u����ʒu��r�o����֐�
// ��  ���F�Ȃ�
// �߂�l�F�Ȃ�
void CEnmRSProc::ResetPlacementMan() {
	srand(time(NULL));              // �����p�^�[���̎擾
	for (int i = 0; i < 6; i++) {
		int num = rand() % 10;  // �����_���ňʒu�擾
		int var = num;          // ver�ɐݒ�
		num = rand() % 10;      // �����_���ňʒu�擾
		int hori = num;         // hori�ɐݒ�
		for (int num = 0; num < 100; num++) {
			// �Q�[���J�n���ɑ���ł��Ȃ��悤�ɂȂ�Ȃ�(�l�܂Ȃ�)���߂ɒ���
			// �z�u����s��3�ȉ��Ȃ��ver��hori���Đݒ�
			if (i == 0 && hori <= 3) {
				int againNum = rand() % 10;
				var = againNum;
				againNum = rand() % 10;
				hori = againNum;
			}
			else {
				break;
			}
		}
		// �z��ɔz�u����s�Ɨ���Z�b�g
		numH[i] = hori;
		numV[i] = var;
	}
}
// ---------------------------------------------------------------------------
//
// �G�q�r�v���V�[�W���̎�����������
//
//
// ---------------------------------------------------------------------------
void CEnmRSProc::Update()
{
	// M.S �}�b�v������2���ǂ���
	if (m_pGMain->m_pMapProc->MapNumGet() == 2) {
		VECTOR3 mHit;
		VECTOR3 mNor;
		// M.S ���݂̐��H�z�u�\�̖ʂ𒲂ׂ�
		for (int i = 0; i < 6; i++) {
			// M.S ����(����z�u�\��)�����ׂ邽�߃��C���΂��ʒu�ϐ�
			MATRIX4X4 upFront = XMMatrixTranslation(0.0f, 10.0f, 0.0f);
			MATRIX4X4 upBack = XMMatrixTranslation(0.0f, 3.0f, 0.0f);
			bool nowPosSurfaceflag = m_pGMain->m_pMapProc->m_pBBoxPosition[i]->
			  OBBCollisionLay(/*back*/upBack, /*front*/upFront, &mHit, &mNor);
			// M.S ���ׂ��ʂɂ܂��l��z�u���Ă��Ȃ�
	        // �z�u���̐l�I�u�W�F�N�g���Ȃ���Δz�u����  
			if (nowPosSurfaceflag == true) {
				surfaceNumTarget = i;
				if ((PlacementManMap[surfaceNumTarget] == 0) 
					&& (m_pGMain->m_pEnmProc->m_pEnmRSProc->exclusiveMan == false)) {
					if (manNum < 6) {
						m_pObjArray[manNum]->Start();
						manNum++;      // M.S �z�u�ςݐl���𑫂�
					}
					// M.S �z�u���I��������PlacementManMap�̂��̖ʂ̗v�f��1�������
					PlacementManMap[surfaceNumTarget] = 1;
					break;
				}
			}
		}
	}
}
// ---------------------------------------------------------------------------
//
// �G�q�r�I�u�W�F�N�g�̔���
//
// ---------------------------------------------------------------------------
BOOL CEnmRSObj::Start()
{
	// M.S �}�b�v2���܂��z�u���Ă��Ȃ��l�I�u�W�F�N�g��������
	if ((m_pGMain->m_pMapProc->MapNumGet() == 2) && (doneProcess == false)) {
		srand(time(NULL));     // M.S �����p�^�[���̎擾
		// M.S �}�b�v�̉�]�\�t���O��false
		m_pGMain->m_pMapProc->doneManPlacement = false;
		// M.S �l�I�u�W�F�N�g���쒆�t���O��true
		m_pGMain->m_pEnmProc->m_pEnmRSProc->exclusiveMan = true;
		// M.S ��]�p�x�t���O��������
		rotate0 = false;
		rotate90 = false;
		rotate180 = false;
		rotate270 = false;
		// M.S ����(����\��)�̈ʒu�̕ϐ�
		VECTOR3 frontPos = VECTOR3(0.0f, 6.0f, 0.0f);
		// M.S �z�u����ʂ̌��݂̉�]�𒲂ׂ�  
		// rotate0:0�x��] rotate90:90�x��] rotate180:180�x��] rotate270:270�x��]
		int northNow = m_pGMain->m_pPcProc->
			judgeDirection(m_pGMain->m_pEnmProc->m_pEnmGolemProc->surfaceNumTarget, frontPos, 0);
		switch (northNow) {
		case 1:
			rotate0 = true;
			break;
		case 2:
			rotate90 = true;
			break;
		case 3:
			rotate180 = true;
			break;
		case 4:
			rotate270 = true;
			break;
		}
		// M.S �l�I�u�W�F�N�g�̔z�u���Ă���l���̐�����manArrayNum�ɓ����
		int manArrayNum = m_pGMain->m_pEnmProc->m_pEnmRSProc->manNum;
		// M.S �z�u�����̐l�I�u�W�F�N�g�Əd�Ȃ��Ă��Ȃ����A�d�Ȃ��Ă����ꍇ�ēx�����Ŕz�u�����߂�
		int investigateHori = m_pGMain->m_pEnmProc->m_pEnmRSProc->numH[manArrayNum];
		int investigateVer = m_pGMain->m_pEnmProc->m_pEnmRSProc->numV[manArrayNum];
		for (int i = 0; i < 100; i++) {
			if (m_pGMain->m_pMapProc->lineMap1[investigateHori][investigateVer] == 0) {
				break;
			}
			int hori = rand() % 10;
			int var = rand() % 10;
			for (int num = 0; num < 100; num++) {
				hori = rand() % 10;
			    var = rand() % 10;
				// M.S �Q�[���J�n���ɑ���ł��Ȃ��悤�ɂȂ�Ȃ�(�l�܂Ȃ�)���߂ɒ���
			    // M.S �����ʂłȂ��A�܂���hori��3���傫���Ȃ��
				if (manArrayNum != 0 || hori > 3) {  
					// M.S �z���hori��var���Z�b�g���ă��[�v�𔲂���
					m_pGMain->m_pEnmProc->m_pEnmRSProc->numH[manArrayNum] = hori;
					m_pGMain->m_pEnmProc->m_pEnmRSProc->numV[manArrayNum] = var;
					// M.S investigateHori��investigateVer�ɒl���Z�b�g
					investigateHori = hori;
					investigateVer = var;
					break;
				}
			}
		}
		// M.S �}�b�v�z��ʂ̐����ƍ��W�̈ʒu�����킹�鐔�̕ϐ�
		float adjustPlusPos = 4.5f;
		float adjustMinusPos = -4.5f;
		float yPos = 5.0f;   // M.S �z�u���鍂��(Y���W)
		// M.S �}�b�v�̉�]�ɍ��킹�Ĕz�u�ʒu�Ɖ�]��initialRotate�ɕۑ�
		if (rotate0 == true) {
			m_mWorld = XMMatrixTranslation(adjustMinusPos + 1 * investigateVer, yPos, adjustPlusPos - 1 * investigateHori);
		}
		else if (rotate90 == true) {
			m_mWorld = XMMatrixTranslation(adjustPlusPos - 1 * investigateHori, yPos, adjustPlusPos - 1 * investigateVer);
			initialRotate = m_pGMain->m_pEnmProc->rotate90angle;;
		}
		else if (rotate180 == true) {
			m_mWorld = XMMatrixTranslation(adjustPlusPos - 1 * investigateVer, yPos, adjustMinusPos + 1 * investigateHori);
			initialRotate = m_pGMain->m_pEnmProc->rotate180angle;;
		}
		else if (rotate270 == true) {
			m_mWorld = XMMatrixTranslation(adjustMinusPos + 1 * investigateHori, yPos, adjustMinusPos + 1 * investigateVer);
			initialRotate = m_pGMain->m_pEnmProc->rotate270angle;;
		}
		m_bActive = TRUE;
		// M.S �l�I�u�W�F�N�g�̔z�u����Ă���ʂ�ۑ�
		manSurfaceNum = m_pGMain->m_pEnmProc->m_pEnmRSProc->surfaceNumTarget;
		// M.S �}�b�v�z����X�V
		m_pGMain->m_pMapProc->lineMap1[investigateHori][investigateVer] = 10;
		// M.S �}�b�v�̉�]�\�t���O��true
		m_pGMain->m_pMapProc->doneManPlacement = true;
		// M.S �l�I�u�W�F�N�g�̔z�u���Ă���l���̐�����ۑ�
		thisManArrayNumber = manArrayNum;
		// M.S �l�I�u�W�F�N�g���쒆�t���O��false
		m_pGMain->m_pEnmProc->m_pEnmRSProc->exclusiveMan = false;
		// M.S �z�u�ς�
		doneProcess = true;
		return TRUE;
	}
	return FALSE;
}
// M.S �v���C�L�����̈ʒu�ɍ��킹��
// �l�I�u�W�F�N�g�ƃv���C�L��������ʂɂ���Ƃ����ʒu������
// ��  ���F�Ȃ�
// �߂�l�F�Ȃ�
void	CEnmRSObj::OutUpPos() {
	switch (m_pGMain->m_pPcProc->GetPcObjPtr()->nowPcPosNum) {
	case 0:
		manPos = VECTOR3(manPos.x, manPos.y, manPos.z);
		pcPos = VECTOR3(pcPos.x, pcPos.y, pcPos.z);
		break;
	case 1:
		manPos = VECTOR3(manPos.x, 5.0f, manPos.y);
		pcPos = VECTOR3(pcPos.x, 5.0f, pcPos.y);
		break;
	case 2:
		manPos = VECTOR3(manPos.x, 5.0f, -1.0f * manPos.z);
		pcPos = VECTOR3(pcPos.x, 5.0f, -1.0f * pcPos.z);
		break;
	case 3:
		manPos = VECTOR3(manPos.x, 5.0f, -1.0f * manPos.y);
		pcPos = VECTOR3(pcPos.x, 5.0f, -1.0f * pcPos.y);
		break;
	case 4:
		manPos = VECTOR3(-1.0f * manPos.y, 5.0f, manPos.z);
		pcPos = VECTOR3(-1.0f * pcPos.y, 5.0f, pcPos.z);
		break;
	case 5:
		manPos = VECTOR3(manPos.y, 5.0f, manPos.z);
		pcPos = VECTOR3(pcPos.y, 5.0f, pcPos.z);
		break;
	}
}
//-----------------------------------------------------------------------------
// �G�q�r�I�u�W�F�N�g�̐���
//
//�@�L�[�{�[�h�œG�𓮂���
//�@�G�̃A�j���[�V�����A�W�����v�A���R����
//�@���[���h���W�ϊ��A�}�b�v�Ƃ̐ڐG����
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CEnmRSObj::Update()
{
	if (!m_bActive) return;  // ��\���̂Ƃ��͏��������Ȃ�
	if (alive == true ) {
		// �ϐ��̏�����  ---------------------------------------
		m_vPosUp.x = m_vPosUp.y = m_vPosUp.z = 0.0f;
		m_vRotUp.x = m_vRotUp.y = m_vRotUp.z = 0.0f;
		m_mWorldOld = m_mWorld;  // ��O�̈ʒu
		// M.S �}�b�v�̉�]���~�߂�
		m_pGMain->m_pEnmProc->rotateOkFlagMan = false;
		// M.S �v���C�L�����Ɛl�I�u�W�F�N�g�̂���ʂ���v���Ă����ꍇ
		if ((manSurfaceNum == m_pGMain->m_pPcProc->GetPcObjPtr()->surfaceNum)
			&& m_pGMain->m_pMapProc->MapNumGet() == 2) {
			// M.S �v���C�L�����̈ʒu���擾
		    pcPos = GetPositionVector(m_pGMain->m_pPcProc->GetPcObjPtr()->GetWorld());
			// M.S �l�I�u�W�F�N�g�̈ʒu���擾
			manPos = GetPositionVector(m_mWorld);
			float plusAngle = 0.0f;  // M.S ��]�̊p�x
			// M.S ���̐l�I�u�W�F�N�g�̂���ʂ̉�]�𒲂ׂ�
			int north = m_pGMain->m_pPcProc->judgeDirection(manSurfaceNum, manPos, 1);
			// M.S ���ׂ���]�����킹��plusAngle�Ɋp�x�������
			switch (north) {  // M.S 1:��]�Ȃ� 2:�E90�x��] 3:�E180�x��] 4:�E270�x��] 
			case 1:
				break;
			case 2:
				plusAngle = m_pGMain->m_pEnmProc->rotate90angle;
				break;
			case 3:
				plusAngle = m_pGMain->m_pEnmProc->rotate180angle;
				break;
			case 4:
				plusAngle = m_pGMain->m_pEnmProc->rotate270angle;
			}
			// M.S �v���C�L�����̈ʒu�ɍ��킹��
			// �l�I�u�W�F�N�g�ƃv���C�L��������ʂɂ���Ƃ����ʒu������
			OutUpPos();
			// M.S �l�I�u�W�F�N�g���v���C�L�����������Ă���}�g���b�N�X
			MATRIX4X4 manLookWorld = GetLookatMatrix(manPos, pcPos);
			// M.S manLookWorld��Y�v�f�����o��
			MATRIX4X4 manLookRotateY = GetRotateMatrixY(manLookWorld);
			// M.S manLookRotateY��vector�i�p�x�j
			VECTOR3 manLookRotate = GetRotateVector(manLookRotateY);
			// M.S manLookRotate.y + �ʂ̉�] - �z�u���̊p�x������
			manLookRotate.y = manLookRotate.y + plusAngle - initialRotate;
			// M.S manLookRotate.y��360��菬�����Ȃ�悤�ɂ���
			for (int i = 0; i < 100; i++) {
				if (manLookRotate.y >= 360) {
					manLookRotate.y = manLookRotate.y - 360.0f;
				}
				else {
					break;
				}
			}
			// M.S manLookRotate.y(�v���C�L�����̕���������)�̉�]�}�g���b�N�X
			manRotate = XMMatrixRotationY(XMConvertToRadians(manLookRotate.y));
			if (initialProcess == true) {
				// M.S �ŏ��݂̂̏���
				m_mWorld = manRotate * m_mWorld;
				initialProcess = false;
			}
			else {
				// M.S manRotateOld�������Ė߂��Ă���manRotate�������ăv���C���[�̕�����������
				MATRIX4X4 returnManRotate = manRotateOld * m_mWorld;
				m_mWorld = manRotate * returnManRotate;
			}
			// M.S �߂���]��ۑ�
			manRotateOld = XMMatrixRotationY(XMConvertToRadians(360.0f - manLookRotate.y));
			// M.S �}�b�v�̉�]���ł���悤�ɂ���
			m_pGMain->m_pMapProc->doneManPlacement = true;
			// M.S �v���C�L�������߂Â������̃A�j���[�V�����̕ύX
			float distance = magnitude(manPos - pcPos);
			if (distance <= 2.0f && initialDeadAnim != 1) {
				m_AnimStatus.SetNum(1);
			}
			else if (initialDeadAnim == false) {
				m_AnimStatus.SetNum(0);
			}
			// M.S �w���߂��ɒu���ꂽ���̏���
			UpdateDead();
		}
		// M.S �}�b�v�̉�]���\�ɂ���
		m_pGMain->m_pEnmProc->rotateOkFlagMan = true;
		// �`�揈��  ---------------------------------------------
		// �X�L�����b�V�������_�����O
		int shineFlag = 0;  // M.S �����_�[�̎w��
		m_pMesh->Render(m_AnimStatus, m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt, shineFlag);
		// �o�E���f�B���O�{�b�N�X
		m_pBBox->m_mWorld = m_mWorld;
	}
}

//-----------------------------------------------------------------------------
// �G�q�r�I�u�W�F�N�g�̐���
//
// �G���ʏ��Ԃ̂Ƃ��̏���
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CEnmRSObj::UpdateNormal()
{

}

//-----------------------------------------------------------------------------
// �G�q�r�I�u�W�F�N�g�̐���
//
// �G���_���[�W��Ԃ̂Ƃ��̏���
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CEnmRSObj::UpdateDamage()
{
	
}
//-----------------------------------------------------------------------------
// �G�q�r�I�u�W�F�N�g�̐���
//
// �G�����S��Ԃ̂Ƃ��̏���
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CEnmRSObj::UpdateDead()
{
	int afterStationNum = 8;  // M.S �v���C���[���ʉߌ�̔z��ɓ����Ă��鐔��
	int humanNum = 10;        // M.S �l�L����������ꏊ�ɓ����Ă��鐔��
	int afterHumanNum = 0;    // M.S �l�L��������Ԍ�ɔz��ɓ����Ă��鐔��(������)
	// M.S �z�u����Ă���l�I�u�W�F�N�g�������ꍇ
	if (doneProcess == true && alive == true) {
		// M.S �Z�����邽�߂ɍs�A���ϐ��ɓ����
		int hori = m_pGMain->m_pEnmProc->m_pEnmRSProc->numH[thisManArrayNumber];
		int var = m_pGMain->m_pEnmProc->m_pEnmRSProc->numV[thisManArrayNumber];	
		// M.S �}�b�v���ʂ������ꍇ�A�㉺���E�ǂ����ɉw�I�u�W�F�N�g����������
		if (m_pGMain->m_pPcProc->GetPcObjPtr()->frontFlag == true) {
			if (m_pGMain->m_pMapProc->lineMap1[hori][var] == humanNum
				&&(m_pGMain->m_pMapProc->lineMap1[hori + 1][var] == afterStationNum
				|| m_pGMain->m_pMapProc->lineMap1[hori - 1][var] == afterStationNum
				|| m_pGMain->m_pMapProc->lineMap1[hori][var + 1] == afterStationNum
				|| m_pGMain->m_pMapProc->lineMap1[hori][var - 1] == afterStationNum)) {
				if (initialDeadAnim == 0) {   // M.S ��ԃt�F�[�Y��0�̏ꍇ
					// M.S ��ԏ������t���O��true
					m_pGMain->m_pEnmProc->m_pEnmRSProc->managementDeadProcess = true;
					m_AnimStatus.SetNum(2);   // M.S ��ԃA�j���[�V�������Z�b�g
					m_AnimStatus.animFrame = m_AnimStatus.endFrame - 1; // �t���[���G���h�̈��O�ɂ���
					initialDeadAnim = 1;    // M.S ��ԃt�F�[�Y��1�ɂ���
				}
				// M.S ��ԃA�j���[�V�������I�������(animCount��0�ȉ��Ȃ��)
				else if (animCount <= 0) {   
					animCount = saveAnimCount;  // M.S animCount�����Ƃɖ߂�
					initialDeadAnim = 3;        // M.S ��ԃt�F�[�Y��3�ɂ���
					// M.S MiddleMan(��)�̏�Ԑl����+1
					m_pGMain->m_pEnmProc->getMiddleStageMan++; 
					// M.S ��Ԍ�̃}�b�v�z���0�ɂ��čX�V
					m_pGMain->m_pMapProc->lineMap1[hori][var] = afterHumanNum;
					// M.S ��ԏ������t���O��false
					m_pGMain->m_pEnmProc->m_pEnmRSProc->managementDeadProcess = false;
					m_bActive = FALSE;           // M.S ��ʂɕ\�������Ȃ�
					m_pGMain->rideSound->Play(); // M.S ��Ԍ��ʉ�
					m_AnimStatus.SetNum(0);      // M.S �A�j���[�V���������ɖ߂�
					alive = false;               // M.S ����ԏ����t���O��false
				}
				animCount--;            // M.S �A�j���[�V�������鎞�Ԃ�����
			}
		}
		else {
			// M.S �}�b�v���ʈȊO�������ꍇ�A�㉺���E�ǂ����ɉw�I�u�W�F�N�g����������
			if (m_pGMain->m_pPcProc->lineMapSub[hori][var] == humanNum
				&&(m_pGMain->m_pPcProc->lineMapSub[hori + 1][var] == afterStationNum
				|| m_pGMain->m_pPcProc->lineMapSub[hori - 1][var] == afterStationNum
				|| m_pGMain->m_pPcProc->lineMapSub[hori][var + 1] == afterStationNum
				|| m_pGMain->m_pPcProc->lineMapSub[hori][var - 1] == afterStationNum)) {
				if (initialDeadAnim == 0) {       // M.S ��ԃt�F�[�Y��0�̏ꍇ
					// M.S ��ԏ������t���O��true
					m_pGMain->m_pEnmProc->m_pEnmRSProc->managementDeadProcess = true;
					m_AnimStatus.SetNum(2);       // M.S ��ԃA�j���[�V�������Z�b�g
					m_AnimStatus.animFrame = m_AnimStatus.endFrame - 1; // �t���[���G���h�̈��O�ɂ���
					initialDeadAnim = 1;          // M.S ��ԃt�F�[�Y��1�ɂ���
				}
				// M.S ��ԃA�j���[�V�������I�������(animCount��0�ȉ��Ȃ��)
				else if (animCount <= 0) {
					animCount = saveAnimCount;    // M.S animCount�����Ƃɖ߂�
					initialDeadAnim = 3;          // M.S ��ԃt�F�[�Y��3�ɂ���
					// M.S MiddleMan(��)�̏�Ԑl����+1	
					m_pGMain->m_pEnmProc->getMiddleStageMan++; 
					// M.S �}�b�v�z���0�ɂ���
					m_pGMain->m_pPcProc->lineMapSub[hori][var] = afterHumanNum; 
					// M.S �}�b�v�z��̍X�V
					m_pGMain->m_pPcProc->lineMapSet(manSurfaceNum); 
					// M.S ��ԏ������t���O��false
					m_pGMain->m_pEnmProc->m_pEnmRSProc->managementDeadProcess = false;
					m_bActive = FALSE;            // M.S ��ʂɕ\�������Ȃ�
					m_pGMain->rideSound->Play();  // M.S ��Ԍ��ʉ�
					m_AnimStatus.SetNum(0);       // M.S �A�j���[�V���������ɖ߂�
					alive = false;                // M.S ����ԏ����t���O��false
				}
				animCount--;                      // M.S �A�j���[�V�������鎞�Ԃ�����
			}
		}
	}
}
//============================================================================
//
// �G�u���[�h���S���v���V�[�W���̃R���X�g���N�^
//
//   �Ȃ��A�I�u�W�F�N�g��delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
// ---------------------------------------------------------------------------
CEnmBdProc::CEnmBdProc(CGameMain* pGMain) : CBaseProc( pGMain)
{
	const int nWait    = 600;                   // �G����������܂ł̑҂�����
	m_dwProcID         = ENM_BD_ID;             // �G�u���[�h���S����ID
	m_nNum = m_nMaxNum = ENM_BD_ALLMAX;         // �G�u���[�h���S���̍ő�o����

	// Fbx�X�L�����b�V���̐ݒ�
	m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Char/Man/LowMan_Idle.mesh"));
	m_pMesh->LoadAnimation(_T("Data/Char/Man/LowMan_Idle.anmx"));
	m_pMesh->LoadAnimation(_T("Data/Char/Man/LowMan_HappyIdle.anmx"));
	m_pMesh->LoadAnimation(_T("Data/Char/Man/LowMan_Jump.anmx"));
	m_pMesh->m_fHeightMax = 0.05f;     // �f�B�X�v���[�X�����g�}�b�s���O�̍���  // -- 2020.1.24
	m_pMesh->m_iMaxDevide = 64;
	m_nHoldItem.m_nHoldObjNo = 4;	// ��Ɏ�����̃I�u�W�F�ԍ�(�����ȏe)  // -- 2021.2.4
	m_nHoldItem.m_nPosMesh = 0;		// ���̍����ʒu�̃��b�V���ԍ�
	m_nHoldItem.m_nPosBone = 9;		// ���̍����ʒu�̃{�[���ԍ�
	m_nHoldItem.m_nOffsetPos = VECTOR3(0.0f, 0.0f, 0.0f);  // ��Ɏ�����̈ʒu�I�t�Z�b�g
	m_nHoldItem.m_nOffsetRot = VECTOR3(0.0f, 0.0f, 0.0f);  // ��Ɏ�����̊p�x�I�t�Z�b�g

	for (int i = 0; i < ENM_BD_MAX; i++)
	{
		m_pObjArray.push_back(new CEnmBdObj(m_pGMain));  // m_pObjArray�ɃI�u�W�F�N�g�𐶐�����
		m_pObjArray[i]->SetObjID(m_dwProcID);						// -- 2021.2.4
		m_pObjArray[i]->SetObjNo(i);
		((CEnmBdObj*)m_pObjArray[i])->SetMesh( this);  // ���b�V���̃A�h���X���I�u�W�F�N�g�ɐݒ肷��
	}

	m_nWaitTime = m_nMaxwaitTime = nWait;
	manNum = 0;                     // M.S �z�u�ςݐl��
	exclusiveMan = false;           // M.S �z�u���t���O
	surfaceNumTarget = 0;           // M.S ���ׂ�ʂ̐���
	managementDeadProcess = false;  // M.S ��ԏ������t���O
}
//============================================================================
//
// �G�u���[�h���S���v���V�[�W���̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CEnmBdProc::~CEnmBdProc()
{
	SAFE_DELETE(m_pMesh);
}

//============================================================================
//
// �G�u���[�h���S���I�u�W�F�N�g�̃R���X�g���N�^
//
// ---------------------------------------------------------------------------
CEnmBdObj::CEnmBdObj(CGameMain* pGMain) : CBaseObj( pGMain)
{
	const int nMaxHP = 5000;        // �̗�
	const int nAtc   = 500;         // �̂̍U����

	m_bActive = FALSE;
	m_dwStatus = NORMAL;

	m_vTarget = GetPositionVector(m_mWorld);

	// �o�E���f�B���O�{�b�N�X�̐ݒ�
	VECTOR3 vMin(-2.8f, -0.05f, -2.0f);
	VECTOR3 vMax(2.8f, 15.0f, 2.0f);
	m_pBBox = new CBBox(m_pGMain->m_pShader, vMin, vMax);
	m_pBBox->m_mWorld = m_mWorld;                            // -- 2021.1.11

	m_nHp = m_nMaxHp = nMaxHP;
	m_nAtc = nAtc;
	doneProcess = false;       // M.S �z�u���Ă��邩�t���O
	alive = true;              // M.S ����ԏ����t���O
	manSurfaceNum = 0;         // M.S �l�I�u�W�F�N�g������ʂ̐���
	thisManArrayNumber = 0;    // M.S �z�u�������Ԃ̕ۑ�
	initialProcess = true;    // M.S �ŏ��݂̂̏����t���O
	// M.S �v���C�L�����̕�������������p�x���}�b�v�̉�]�ɍ��킹�Ē�������ϐ�
	initialRotate = 0.0f;
	// M.S 0:�܂�����ɒʉߍς݉w���H���Ȃ� 1:����ɒʉߍς݉w���H������ 3:��荞�݃A�j���[�V�����Ə������I��
	initialDeadAnim = 0;
	// M.S ��ԃA�j���[�V�����̃^�C���J�E���g
	animCount = 60;
	// M.S ��ԃA�j���[�V�����̎���
	saveAnimCount = 60;
}
// ---------------------------------------------------------------------------
//
// �G�u���[�h���S���I�u�W�F�N�g�̃f�X�g���N�^
//
//   �Ȃ��ACBBox��delete��CBaseObj�̃f�X�g���N�^�ōs�����ߕs�v
//
// ---------------------------------------------------------------------------
CEnmBdObj::~CEnmBdObj()
{
	;
}
// ---------------------------------------------------------------------------
//
// �G�u���[�h���S���I�u�W�F�N�g�̃��b�V���|�C���^�ݒ�
//
//  CEnmBdProc* pProc
//
// ---------------------------------------------------------------------------  // -- 2021.2.4
void CEnmBdObj::SetMesh(CEnmBdProc* pProc)
{
	m_pMesh = pProc->GetMesh();					// �X�L�����b�V���̃|�C���^
	m_nHoldItem = pProc->GetHoldItem();			// ��Ɏ�����̏��𓾂�

	m_AnimStatus.SetNum(0);
	m_AnimStatus.animFrame = 0;
}
// M.S �z�u����ʒu��r�o����֐�
// ��  ���F�Ȃ�
// �߂�l�F�Ȃ�
void CEnmBdProc::ResetPlacementMan() {
	srand(time(NULL));              // �����p�^�[���̎擾
	for (int i = 0; i < 6; i++) {
		int num = rand() % 10;  // �����_���ňʒu�擾
		int var = num;          // ver�ɐݒ�
		num = rand() % 10;      // �����_���ňʒu�擾
		int hori = num;         // hori�ɐݒ�
		for (int num = 0; num < 100; num++) {
			// �Q�[���J�n���ɑ���ł��Ȃ��悤�ɂȂ�Ȃ�(�l�܂Ȃ�)���߂ɒ���
			// �z�u����s��3�ȉ��Ȃ��ver��hori���Đݒ�
			if (i == 0 && hori <= 3) {
				int againNum = rand() % 10;
				var = againNum;
				againNum = rand() % 10;
				hori = againNum;
			}
			else {
				break;
			}
		}
		// �z��ɔz�u����s�Ɨ���Z�b�g
		numH[i] = hori;
		numV[i] = var;
	}
}
// ---------------------------------------------------------------------------
//
// �G�u���[�h���S���v���V�[�W���̎�����������
//
//
// ---------------------------------------------------------------------------
void CEnmBdProc::Update()
{
	// M.S �}�b�v������2���ǂ���
	if (m_pGMain->m_pMapProc->MapNumGet() == 2) {
		VECTOR3 mHit;
		VECTOR3 mNor;
		// M.S ���݂̐��H�z�u�\�̖ʂ𒲂ׂ�
		for (int i = 0; i < 6; i++) {
			// M.S ����(����z�u�\��)�����ׂ邽�߃��C���΂��ʒu�ϐ�
			MATRIX4X4 upFront = XMMatrixTranslation(0.0f, 10.0f, 0.0f);
			MATRIX4X4 upBack = XMMatrixTranslation(0.0f, 3.0f, 0.0f);
			bool nowPosSurfaceflag = m_pGMain->m_pMapProc->
				m_pBBoxPosition[i]->
				OBBCollisionLay(/*back*/upBack, /*front*/upFront, &mHit, &mNor);
			// M.S ���ׂ��ʂɂ܂��l��z�u���Ă��Ȃ�
		    // �z�u���̐l�I�u�W�F�N�g���Ȃ���Δz�u����
			if (nowPosSurfaceflag == true) {
				surfaceNumTarget = i;
				if ((PlacementManMap[surfaceNumTarget] == 0) 
					&& (m_pGMain->m_pEnmProc->m_pEnmBdProc->exclusiveMan == false)) {
					if (manNum < 6) {
						m_pObjArray[manNum]->Start();
						manNum++;      // M.S �z�u�ςݐl���𑫂�
					}
					// M.S �z�u���I��������PlacementManMap�̂��̖ʂ̗v�f��1�������
					PlacementManMap[surfaceNumTarget] = 1;
					break;
				}
			}
		}
	}
}
// ---------------------------------------------------------------------------
//
// �G�u���[�h���S���I�u�W�F�N�g�̔���
//
// ---------------------------------------------------------------------------
BOOL CEnmBdObj::Start()
{
	// M.S �}�b�v2���܂��z�u���Ă��Ȃ��l�I�u�W�F�N�g��������
	if ((m_pGMain->m_pMapProc->MapNumGet() == 2) && (doneProcess == false)) {
		srand(time(NULL));     // M.S �����p�^�[���̎擾
		// M.S �}�b�v�̉�]�\�t���O��false
		m_pGMain->m_pMapProc->doneManPlacement = false;
		// M.S �l�I�u�W�F�N�g���쒆�t���O��true
		m_pGMain->m_pEnmProc->m_pEnmBdProc->exclusiveMan = true;
		// M.S ��]�p�x�t���O��������
		rotate0 = false;
		rotate90 = false;
		rotate180 = false;
		rotate270 = false;				// M.S �z�u����ʂ̌��݂̉�]�𒲂ׂ�  
		// M.S ����(����\��)�̈ʒu�̕ϐ�
		VECTOR3 frontPos = VECTOR3(0.0f, 6.0f, 0.0f);
		// M.S �z�u����ʂ̌��݂̉�]�𒲂ׂ�  
		// rotate0:0�x��] rotate90:90�x��] rotate180:180�x��] rotate270:270�x��]
		int northNow = m_pGMain->m_pPcProc->
			judgeDirection(m_pGMain->m_pEnmProc->m_pEnmGolemProc->surfaceNumTarget, frontPos, 0);
		switch (northNow) {
		case 1:
			rotate0 = true;
			break;
		case 2:
			rotate90 = true;
			break;
		case 3:
			rotate180 = true;
			break;
		case 4:
			rotate270 = true;
			break;
		}
		// M.S �l�I�u�W�F�N�g�̔z�u���Ă���l���̐�����manArrayNum�ɓ����
		int manArrayNum = m_pGMain->m_pEnmProc->m_pEnmBdProc->manNum;
		// M.S �z�u�����̐l�I�u�W�F�N�g�Əd�Ȃ��Ă��Ȃ����A�d�Ȃ��Ă����ꍇ�ēx�����Ŕz�u�����߂�
		int investigateHori = m_pGMain->m_pEnmProc->m_pEnmBdProc->numH[manArrayNum];
		int investigateVer = m_pGMain->m_pEnmProc->m_pEnmBdProc->numV[manArrayNum];
		for (int i = 0; i < 100; i++) {
			if (m_pGMain->m_pMapProc->lineMap1[investigateHori][investigateVer] == 0) {
				break;
			}
			int hori = rand() % 10;
			int var = rand() % 10;
			for (int num = 0; num < 100; num++) {
				hori = rand() % 10;
				var = rand() % 10;
				// M.S �Q�[���J�n���ɑ���ł��Ȃ��悤�ɂȂ�Ȃ�(�l�܂Ȃ�)���߂ɒ���
				// M.S �����ʂłȂ��A�܂���hori��3���傫���Ȃ��
				if (manArrayNum != 0 || hori > 3) {
					// M.S �z���hori��var���Z�b�g���ă��[�v�𔲂���
					m_pGMain->m_pEnmProc->m_pEnmBdProc->numH[manArrayNum] = hori;
					m_pGMain->m_pEnmProc->m_pEnmBdProc->numV[manArrayNum] = var;
					// M.S investigateHori��investigateVer�ɒl���Z�b�g
					investigateHori = hori;   
					investigateVer = var;
					break;
				}
			}
		}
		// M.S �}�b�v�z��ʂ̐����ƍ��W�̈ʒu�����킹�鐔�̕ϐ�
		float adjustPlusPos = 4.5f;
		float adjustMinusPos = -4.5f;
		float yPos = 5.0f;   // M.S �z�u���鍂��(Y���W)
		// M.S �}�b�v�̉�]�ɍ��킹�Ĕz�u�ʒu�Ɖ�]��initialRotate�ɕۑ�
		if (rotate0 == true) {
			m_mWorld = XMMatrixTranslation(adjustMinusPos + 1 * investigateVer, yPos, adjustPlusPos - 1 * investigateHori);
		}
		else if (rotate90 == true) {
			m_mWorld = XMMatrixTranslation(adjustPlusPos - 1 * investigateHori, yPos, adjustPlusPos - 1 * investigateVer);
			initialRotate = m_pGMain->m_pEnmProc->rotate90angle;;
		}
		else if (rotate180 == true) {
			m_mWorld = XMMatrixTranslation(adjustPlusPos - 1 * investigateVer, yPos, adjustMinusPos + 1 * investigateHori);
			initialRotate = m_pGMain->m_pEnmProc->rotate180angle;;
		}
		else if (rotate270 == true) {
			m_mWorld = XMMatrixTranslation(adjustMinusPos + 1 * investigateHori, yPos, adjustMinusPos + 1 * investigateVer);
			initialRotate = m_pGMain->m_pEnmProc->rotate270angle;;
		}
		m_bActive = TRUE;
		// M.S �l�I�u�W�F�N�g�̔z�u����Ă���ʂ�ۑ�
		manSurfaceNum = m_pGMain->m_pEnmProc->m_pEnmBdProc->surfaceNumTarget;
		// M.S �}�b�v�z����X�V
		m_pGMain->m_pMapProc->lineMap1[investigateHori][investigateVer] = 10;
		// M.S �}�b�v�̉�]�\�t���O��true
		m_pGMain->m_pMapProc->doneManPlacement = true;
		// M.S �l�I�u�W�F�N�g�̔z�u���Ă���l���̐�����ۑ�
		thisManArrayNumber = manArrayNum;
		// M.S �l�I�u�W�F�N�g���쒆�t���O��false
		m_pGMain->m_pEnmProc->m_pEnmBdProc->exclusiveMan = false;
		// M.S �z�u�ς�
		doneProcess = true;
		return TRUE;
	}
	return FALSE;
}
// M.S �v���C�L�����̈ʒu�ɍ��킹��
// �l�I�u�W�F�N�g�ƃv���C�L��������ʂɂ���Ƃ����ʒu������
// ��  ���F�Ȃ�
// �߂�l�F�Ȃ�
void	CEnmBdObj::OutUpPos() {
	switch (m_pGMain->m_pPcProc->GetPcObjPtr()->nowPcPosNum) {
	case 0:
		manPos = VECTOR3(manPos.x, manPos.y, manPos.z);
		pcPos = VECTOR3(pcPos.x, pcPos.y, pcPos.z);
		break;
	case 1:
		manPos = VECTOR3(manPos.x, 5.0f, manPos.y);
		pcPos = VECTOR3(pcPos.x, 5.0f, pcPos.y);
		break;
	case 2:
		manPos = VECTOR3(manPos.x, 5.0f, -1.0f * manPos.z);
		pcPos = VECTOR3(pcPos.x, 5.0f, -1.0f * pcPos.z);
		break;
	case 3:
		manPos = VECTOR3(manPos.x, 5.0f, -1.0f * manPos.y);
		pcPos = VECTOR3(pcPos.x, 5.0f, -1.0f * pcPos.y);
		break;
	case 4:
		manPos = VECTOR3(-1.0f * manPos.y, 5.0f, manPos.z);
		pcPos = VECTOR3(-1.0f * pcPos.y, 5.0f, pcPos.z);
		break;
	case 5:
		manPos = VECTOR3(manPos.y, 5.0f, manPos.z);
		pcPos = VECTOR3(pcPos.y, 5.0f, pcPos.z);
		break;
	}
}
//-----------------------------------------------------------------------------
// �G�u���[�h���S���I�u�W�F�N�g�̐���
//
//�@�L�[�{�[�h�œG�𓮂���
//�@�G�̃A�j���[�V�����A�W�����v�A���R����
//�@���[���h���W�ϊ��A�}�b�v�Ƃ̐ڐG����
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CEnmBdObj::Update()
{
	if (alive == true) {
		if (!m_bActive) return;  // ��\���̂Ƃ��͏��������Ȃ�
			// �ϐ��̏�����  ---------------------------------------
		m_vPosUp.x = m_vPosUp.y = m_vPosUp.z = 0.0f;
		m_vRotUp.x = m_vRotUp.y = m_vRotUp.z = 0.0f;
		m_mWorldOld = m_mWorld;  // ��O�̈ʒu
		// M.S �}�b�v�̉�]���~�߂�
		m_pGMain->m_pEnmProc->rotateOkFlagMan = false;
		// M.S �v���C�L�����Ɛl�I�u�W�F�N�g�̂���ʂ���v���Ă����ꍇ
		if ((manSurfaceNum == m_pGMain->m_pPcProc->GetPcObjPtr()->surfaceNum) && m_pGMain->m_pMapProc->MapNumGet() == 2) {
			// M.S �v���C�L�����̈ʒu���擾
		    pcPos = GetPositionVector(m_pGMain->m_pPcProc->GetPcObjPtr()->GetWorld());
			// M.S �l�I�u�W�F�N�g�̈ʒu���擾
			manPos = GetPositionVector(m_mWorld);
			float plusAngle = 0.0f;  // M.S ��]�̊p�x
			// M.S ���̐l�I�u�W�F�N�g�̂���ʂ̉�]�𒲂ׂ�
			int north = m_pGMain->m_pPcProc->judgeDirection(manSurfaceNum, manPos, 1);
			// M.S ���ׂ���]�����킹��plusAngle�Ɋp�x�������
			switch (north) {  // M.S 1:��]�Ȃ� 2:�E90�x��] 3:�E180�x��] 4:�E270�x��] 
			case 1:
				break;
			case 2:
				plusAngle = m_pGMain->m_pEnmProc->rotate90angle;
				break;
			case 3:
				plusAngle = m_pGMain->m_pEnmProc->rotate180angle;
				break;
			case 4:
				plusAngle = m_pGMain->m_pEnmProc->rotate270angle;
			}
			// M.S �v���C�L�����̈ʒu�ɍ��킹��
			// �l�I�u�W�F�N�g�ƃv���C�L��������ʂɂ���Ƃ����ʒu������
			OutUpPos();
			// M.S �l�I�u�W�F�N�g���v���C�L�����������Ă���}�g���b�N�X
			MATRIX4X4 manLookWorld = GetLookatMatrix(manPos, pcPos);
			// M.S manLookWorld��Y�v�f�����o��
			MATRIX4X4 manLookRotateY = GetRotateMatrixY(manLookWorld);
			// M.S manLookRotateY��vector�i�p�x�j
			VECTOR3 manLookRotate = GetRotateVector(manLookRotateY);
			// M.S manLookRotate.y + �ʂ̉�] - �z�u���̊p�x������
			manLookRotate.y = manLookRotate.y + plusAngle - initialRotate;
			// M.S manLookRotate.y��360��菬�����Ȃ�悤�ɂ���
			for (int i = 0; i < 100; i++) {
				if (manLookRotate.y >= 360) {
					manLookRotate.y = manLookRotate.y - 360.0f;
				}
				else {
					break;
				}
			}
			// M.S manLookRotate.y(�v���C�L�����̕���������)�̉�]�}�g���b�N�X
			manRotate = XMMatrixRotationY(XMConvertToRadians(manLookRotate.y));
			if (initialProcess == true) {
				// M.S �ŏ��݂̂̏���
				m_mWorld = manRotate * m_mWorld;
				initialProcess = false;
			}
			else {
				// M.S manRotateOld�������Ė߂��Ă���manRotate�������ăv���C���[�̕�����������
				MATRIX4X4 returnManRotate = manRotateOld * m_mWorld;
				m_mWorld = manRotate * returnManRotate;
			}
			// M.S �߂���]��ۑ�
			manRotateOld = XMMatrixRotationY(XMConvertToRadians(360.0f - manLookRotate.y));
			// M.S �}�b�v�̉�]���ł���悤�ɂ���
			m_pGMain->m_pMapProc->doneManPlacement = true;
			// M.S �v���C�L�������߂Â������̃A�j���[�V�����̕ύX
			float distance = magnitude(manPos - pcPos);
			if (distance <= 2.0f && initialDeadAnim != 1) {
				m_AnimStatus.SetNum(1);
			}
			else if (initialDeadAnim == false) {
				m_AnimStatus.SetNum(0);
			}
			// M.S �w���߂��ɒu���ꂽ���̏���
			UpdateDead();
		}
		// M.S �}�b�v�̉�]���\�ɂ���
		m_pGMain->m_pEnmProc->rotateOkFlagMan = true;
		// �`�揈��  ---------------------------------------------
		// �X�L�����b�V�������_�����O
		int shineFlag = 0;    // M.S �����_�[�̎w��
		m_pMesh->Render(m_AnimStatus, m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt, shineFlag);
		// �o�E���f�B���O�{�b�N�X
		m_pBBox->m_mWorld = m_mWorld;
	}
}

//-----------------------------------------------------------------------------
// �G�u���[�h���S���I�u�W�F�N�g�̐���
//
// �G���ʏ��Ԃ̂Ƃ��̏���
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CEnmBdObj::UpdateNormal()
{
}

//-----------------------------------------------------------------------------
// �G�u���[�h���S���I�u�W�F�N�g�̐���
//
// �G���_���[�W��Ԃ̂Ƃ��̏���
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CEnmBdObj::UpdateDamage()
{
}
//-----------------------------------------------------------------------------
// �G�u���[�h���S���I�u�W�F�N�g�̐���
//
// �G�����S��Ԃ̂Ƃ��̏���
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CEnmBdObj::UpdateDead()
{ 
	int afterStationNum = 8;  // M.S �v���C���[���ʉߌ�̔z��ɓ����Ă��鐔��
	int humanNum = 10;        // M.S �l�L����������ꏊ�ɓ����Ă��鐔��
	int afterHumanNum = 0;    // M.S �l�L��������Ԍ�ɔz��ɓ����Ă��鐔��(������)
	// M.S �z�u����Ă���l�I�u�W�F�N�g�������ꍇ
	if (doneProcess == true && alive == true) {
		// M.S �Z�����邽�߂ɍs�A���ϐ��ɓ����
		int hori = m_pGMain->m_pEnmProc->m_pEnmBdProc->numH[thisManArrayNumber];
		int ver = m_pGMain->m_pEnmProc->m_pEnmBdProc->numV[thisManArrayNumber];
		// M.S �}�b�v���ʂ������ꍇ�A�㉺���E�ǂ����ɉw�I�u�W�F�N�g����������
		if (m_pGMain->m_pPcProc->GetPcObjPtr()->frontFlag == true) {
			if (m_pGMain->m_pMapProc->lineMap1[hori][ver] == humanNum
				&&(m_pGMain->m_pMapProc->lineMap1[hori + 1][ver] == afterStationNum
				|| m_pGMain->m_pMapProc->lineMap1[hori - 1][ver] == afterStationNum
				|| m_pGMain->m_pMapProc->lineMap1[hori][ver + 1] == afterStationNum
				|| m_pGMain->m_pMapProc->lineMap1[hori][ver - 1] == afterStationNum)) {
				if (initialDeadAnim == 0) {   // M.S ��ԃt�F�[�Y��0�̏ꍇ
					// M.S ��ԏ������t���O��true
					m_pGMain->m_pEnmProc->m_pEnmBdProc->managementDeadProcess = true;
					m_AnimStatus.SetNum(2);  // M.S ��ԃA�j���[�V�������Z�b�g
					m_AnimStatus.animFrame = m_AnimStatus.endFrame - 1; // �t���[���G���h�̈��O�ɂ���
					initialDeadAnim = 1;    // M.S ��ԃt�F�[�Y��1�ɂ���
				}
				// M.S ��ԃA�j���[�V�������I�������(animCount��0�ȉ��Ȃ��)
				else if (animCount <= 0) {
					animCount = saveAnimCount;   // M.S animCount�����Ƃɖ߂�
					initialDeadAnim = 3;         // M.S ��ԃt�F�[�Y��3�ɂ���
					// M.S lowMan(��)�̏�Ԑl����+1
					m_pGMain->m_pEnmProc->getLowStageMan++; 
					// M.S ��ԏ������t���O��false
					m_pGMain->m_pMapProc->lineMap1[hori][ver] = afterHumanNum;
					m_pGMain->m_pEnmProc->m_pEnmBdProc->managementDeadProcess = false;
					m_bActive = FALSE;           // M.S ��ʂɕ\�������Ȃ�
					m_pGMain->rideSound->Play(); // M.S ��Ԍ��ʉ�
					m_AnimStatus.SetNum(0);      // M.S �A�j���[�V���������ɖ߂�
					alive = false;               // M.S ����ԏ����t���O��false              
				}
				animCount--;          // M.S �A�j���[�V�������鎞�Ԃ�����
			}
		}
		else {
			// M.S �}�b�v���ʈȊO�������ꍇ�A�㉺���E�ǂ����ɉw�I�u�W�F�N�g����������
			if (m_pGMain->m_pPcProc->lineMapSub[hori][ver] == humanNum
				&&(m_pGMain->m_pPcProc->lineMapSub[hori + 1][ver] == afterStationNum
				|| m_pGMain->m_pPcProc->lineMapSub[hori - 1][ver] == afterStationNum
				|| m_pGMain->m_pPcProc->lineMapSub[hori][ver + 1] == afterStationNum
				|| m_pGMain->m_pPcProc->lineMapSub[hori][ver - 1] == afterStationNum)) {
				if (initialDeadAnim == 0) {      // M.S ��ԃt�F�[�Y��0�̏ꍇ
					// M.S ��ԏ������t���O��true
					m_pGMain->m_pEnmProc->m_pEnmBdProc->managementDeadProcess = true;
					m_AnimStatus.SetNum(2);      // M.S ��ԃA�j���[�V�������Z�b�g
					m_AnimStatus.animFrame = m_AnimStatus.endFrame - 1; // �t���[���G���h�̈��O�ɂ���
					initialDeadAnim = 1;         // M.S ��ԃt�F�[�Y��1�ɂ���
				}
				// M.S ��ԃA�j���[�V�������I�������(animCount��0�ȉ��Ȃ��)
				else if (animCount <= 0) {     
					animCount = saveAnimCount;   // M.S animCount�����Ƃɖ߂� 
					initialDeadAnim = 3;         // M.S ��ԃt�F�[�Y��3�ɂ���
					// M.S lowMan(��)�̏�Ԑl����+1	
					m_pGMain->m_pEnmProc->getLowStageMan++; 
					// M.S �}�b�v�z���0�ɂ���
					m_pGMain->m_pPcProc->lineMapSub[hori][ver] = afterHumanNum; 
					// M.S �}�b�v�z��̍X�V
					m_pGMain->m_pPcProc->lineMapSet(manSurfaceNum); 
					// M.S ��ԏ������t���O��false
					m_pGMain->m_pEnmProc->m_pEnmBdProc->managementDeadProcess = false;
					m_bActive = FALSE;           // M.S ��ʂɕ\�������Ȃ�
					m_pGMain->rideSound->Play(); // M.S ��Ԍ��ʉ�
					m_AnimStatus.SetNum(0);      // M.S �A�j���[�V���������ɖ߂�
					alive = false;               // M.S ����ԏ����t���O��false
				}
				animCount--;    // M.S �A�j���[�V�������鎞�Ԃ�����
			}
		}
	}
}

