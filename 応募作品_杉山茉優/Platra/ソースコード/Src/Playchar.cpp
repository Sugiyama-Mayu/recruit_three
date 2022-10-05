//=============================================================================
//		�R�c�Q�[���v���O����
//		�b�R�c�`�����P�P�Q�@�@�@�@�@�@                 ver 3.0        2021.1.11
//
//		�v���C�L�����N�^�[�̐���
//																Playchar.cpp
//=============================================================================
#include  "Playchar.h"
#include  "Camera.h"
#include  "BackFore.h"
#include  "Weapon.h"
#include  "Map.h"
#include  "Effect.h"
#include  "Enemy.h"
#include  "Title.h"

//============================================================================
//
// �o�b�v���V�[�W���̃R���X�g���N�^
//
//   �Ȃ��A�I�u�W�F�N�g��delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
// ---------------------------------------------------------------------------
CPcProc::CPcProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	const int nNum = 3;    // PC�̍ő�o����
	// �L�����N�^�[�@�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|
	// M.S �v���C�L�������f��
	m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Char/GalaxyTrain/trainModelCenter01.mesh")); 
	// �A�j���[�V�����ǂݍ��� 
	m_pMesh->LoadAnimation(_T("Data/Char/GalaxyTrain/trainModelCenter01.anmx"));    // M.S �ʏ�
	m_pMesh->LoadAnimation(_T("Data/Char/GalaxyTrain/trainModelCenter01.anmx"));    // M.S
	m_pMesh->LoadAnimation(_T("Data/Char/GalaxyTrain/trainModelCenter01.anmx"));    // M.S �Q�[���I�[�o�[��
	m_pMesh->LoadAnimation(_T("Data/Char/GalaxyTrain/galaxyTrain_GameOver.anmx"));  // M.S
	m_pMesh->LoadAnimation(_T("Data/Char/GalaxyTrain/galaxyTrain_InsideOut.anmx")); // M.S �Q�[���I�[�o�[��
	m_pMesh->m_fHeightMax = 0.01f;
	m_pMesh->m_iMaxDevide = 16;
	// -------------------------------------------------------------------------
	m_pObjArray.push_back(new CPcObj(m_pGMain));	// m_pObjArray�ɃI�u�W�F�N�g��o�^����
	((CPcObj*)m_pObjArray[0])->SetMesh(this);		// ���b�V���|�C���^��ݒ肷��
	m_nPcNum  =  nNum;
	// M.S �������牺�̃R���X�g���N�^�̓��e�͒ǉ����܂���
	////// ��--------------------------------------------------------------------
	// �v���C���[�̈ʒu����̏ꍇ
	upFront1 = VECTOR3(0.0f, 7.0f, 4.0f);
	upBack1 = VECTOR3(0.0f, 5.5f, 4.0f);
	downFront1 = VECTOR3(0.0f, 7.0f, -4.0f);
	downBack1 = VECTOR3(0.0f, 5.5f, -4.0f);
	rightFront1 = VECTOR3(4.0f, 7.0f, 0.0f);
	rightBack1 = VECTOR3(4.0f, 5.5f, 0.0f);
	leftFront1 = VECTOR3(-4.0f, 7.0f, 0.0f);
	leftBack1 = VECTOR3(-4.0f, 5.5f, 0.0f);
	// �v���C���[�̈ʒu���^��
	upFront2 = VECTOR3(0.0f, 4.0f, -7.0f);
	upBack2 = VECTOR3(0.0f, 4.0f, -5.5f);
	downFront2 = VECTOR3(0.0f, -4.0f, -7.0f);
	downBack2 = VECTOR3(0.0f, -4.0f, -5.5f);
	rightFront2 = VECTOR3(4.0f, 0.0f, -7.0f);
	rightBack2 = VECTOR3(4.0f, 0.0f, -5.5f);
	leftFront2 = VECTOR3(-4.0f, 0.0f, -7.0f);
	leftBack2 = VECTOR3(-4.0f, 0.0f, -5.5f);
	// �v���C���[�̈ʒu����
	upFront3 = VECTOR3(0.0f, -7.0f, -4.0f);
	upBack3 = VECTOR3(0.0f, -5.5f, -4.0f);
	downFront3 = VECTOR3(0.0f, -7.0f, 4.0f);
	downBack3 = VECTOR3(0.0f, -5.5f, 4.0f);
	rightFront3 = VECTOR3(4.0f, -7.0f, 0.0f);
	rightBack3 = VECTOR3(4.0f, -5.5f, 0.0f);
	leftFront3 = VECTOR3(-4.0f, -7.0f, 0.0f);
	leftBack3 = VECTOR3(-4.0f, -5.5f, 0.0f);
	// �v���C���[�̈ʒu�����̐^��
	upFront4 = VECTOR3(0.0f, -4.0f, 7.0f);
	upBack4 = VECTOR3(0.0f, -4.0f, 5.5f);
	downFront4 = VECTOR3(0.0f, 4.0f, 7.0f);
	downBack4 = VECTOR3(0.0f, 4.0f, 5.5f);
	rightFront4 = VECTOR3(4.0f, 0.0f, 7.0f);
	rightBack4 = VECTOR3(4.0f, 0.0f, 5.5f);
	leftFront4 = VECTOR3(-4.0f, 0.0f, 7.0f);
	leftBack4 = VECTOR3(-4.0f, 0.0f, 5.5f);
	// �v���C���[�̈ʒu���E
	upFront5 = VECTOR3(7.0f, 0.0f, 4.0f);
	upBack5 = VECTOR3(5.5f, 0.0f, 4.0f);
	downFront5 = VECTOR3(7.0f, 0.0f, -4.0f);
	downBack5 = VECTOR3(5.5f, 0.0f, -4.0f);
	rightFront5 = VECTOR3(7.0f, -4.0f, 0.0f);
	rightBack5 = VECTOR3(5.5f, -4.0f, 0.0f);
	leftFront5 = VECTOR3(7.0f, 4.0f, 0.0f);
	leftBack5 = VECTOR3(5.5f, 4.0f, 0.0f);
	// �v���C���[�̈ʒu����
	upFront6 = VECTOR3(-7.0f, 0.0f, 4.0f);
	upBack6 = VECTOR3(-5.5f, 0.0f, 4.0f);
	downFront6 = VECTOR3(-7.0f, 0.0f, -4.0f);
	downBack6 = VECTOR3(-5.5f, 0.0f, -4.0f);
	rightFront6 = VECTOR3(-7.0f, 4.0f, 0.0f);
	rightBack6 = VECTOR3(-5.5f, 4.0f, 0.0f);
	leftFront6 = VECTOR3(-7.0f, -4.0f, 0.0f);
	leftBack6 = VECTOR3(-5.5f, -4.0f, 0.0f);

	// �ʂ̉�]��ۑ�����ϐ�
	rotateMapNorthNow = 0;
	// false�Ȃ�΃}�b�v�̉�]���~�߂�
	rotateOkFlag = true;
	oneScreenFlag = false;  // 1�ʂ̂ݕ`��t���O
	initialStart = true;    // �ŏ��̃X�^�[�g����
	trainStep = 0;           // �ړ�����
	NewSurfaceNum = 0;       // �v���C�L�����������	
}
// ---------------------------------------------------------------------------
//
// �o�b�v���V�[�W���̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CPcProc::~CPcProc()
{
	SAFE_DELETE(m_pMesh);
}
//============================================================================
//
// �o�b�I�u�W�F�N�g�̃R���X�g���N�^
//
//  ����
//  CGameMain* pGMain;		// �Q�[�����C���N���X�ւ̃|�C���^
//
// ---------------------------------------------------------------------------
CPcObj::CPcObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_bActive		= TRUE;
	m_dwStatus		= NORMAL;
	m_fLocalRotY = 0.0f;                   // -- 2018.8.4
	m_bSide = TRUE;                        // -- 2018.8.4
	// m_fSpeed������10�{������moveTimesMax��10����1����΂悢�i�X�s�[�h�ύX�j
	m_fSpeed = 0.015f;    // ���̈ړ��X�s�[�h M.S
	m_fRotSpeed = 8.0f;   // ��]���x      // -- 2019.3.5
	m_fJumpSpeed = 0.2f;  // �W�����v���x  // -- 2019.3.5
	 moveTimes = 0;  
	 // ���̈ړ��X�s�[�h��0.015f�A1�ړ��̊�����1m�Ȃ̂�moveTimes��MAX66��  M.S
	 moveTimesMax = 66;      
	 oldHP = m_pGMain->initialH;           // �ŏ��̌��ݒn �s M.S
	 oldVP = m_pGMain->initialV;           // �ŏ��̌��ݒn �� M.S
	 changeStepNum = 0;       // �����؂�ւ��u���b�N�̋����̊Ǘ�
	// �o�E���f�B���O�{�b�N�X�̐ݒ�
	m_pBBox = new CBBox(m_pGMain->m_pShader, VECTOR3( -0.16f, 0.0f, -0.25f), VECTOR3(0.15f, 0.32f, 0.24f));
	m_pBBox->m_mWorld = m_mWorld;                            // -- 2021.1.11
	m_mWorldOld = m_mWorld;
	// M.S �������牺�̃R���X�g���N�^�̓��e�͒ǉ����܂���
	////// ��--------------------------------------------------------------------
	trainDirectionFlag = 1;    // �������Ă�������̕ۑ�
	upArrow = 1;     // ��
	rightArrow = 2;  // �E
	downArrow = 3;   // ��
	leftArrow = 4;   // ��
	// �Q�[���I�[�o�[�̃A�j���t�F�[�Y
	gameOverAnim = 0;
	DoneMove = false;   	   // 1���[�v���Ɉړ����������ǂ���������ϐ�
	chPlacementNearH = oldHP - 1;
	chPlacementH = oldHP - 2;
	chPlacementNearV = oldVP;
	chPlacementV = oldVP + 1;
	edgePos = 9;                             // �v���C�L�������[�ɂ���Ƃ��̔z��̒l
	rotateChar = 90.0f;                      // �����؂�ւ����H�̃v���C�L�����̉�]�ϐ�
	moveValueH = 2;      	                 // ���̐��H�܂ł̈ړ����鋗��(�s)
	moveValueV = 1;      	                 // ���̐��H�܂ł̈ړ����鋗��(��)
	loopPlusMoveTimes = 1;                   // ���[�v���Đi��ł����x��moveTimes�ɑ����ϐ�
	changeLineNum = 2;                       // �����؂�ւ����H�̔z��ɂ��ꂽ����
	afterChangeLineNum = 6;                  // �����؂�ւ����H�̒ʉߌ�ɔz��ɂ���鐔��
	chLineMoveTimesMax = moveTimesMax * 2;   // �ŏ��ɂ܂������i�ދ�����2�}�X���Ȃ̂�moveTimesMax * 2
	surfaceNum = 0;      // �v���C�L����������ʒu
	frontFlag = true;   // ���ʂɃv���C�L����������t���O  
	nowPcPosNum = 0;     // ���_���猩��(+Y�������-z����������Ɍ����Ă���̏��) 0:�� 1:��O 2:�� 3:1�̗� 4:�E 5:��
	needRotateFlag = 0;       // �}�b�v�̖ʂ���ʂɈړ�����ۂ̃v���C���[�ʒu�Ɋ|����ϐ��̐��̒����p�ϐ�
	edgeFlag = false;  // �[���玟�̖ʂւ̈ړ��t���O��false

	gameOverTime = 100;  // �Q�[���I�[�o�[�A�j���[�V�������I�������̃J�E���g
	animCount = 59;      // �Q�[���I�[�o�[�A�j���[�V�����̒����J�E���g
	startTime = 0;       // �Q�[���J�n�܂ł̃J�E���g
	startTimeFlag = false;  // �Q�[���J�n�t���O
}
// ---------------------------------------------------------------------------
//
// �o�b�I�u�W�F�N�g�̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CPcObj::~CPcObj() 
{
}
// ---------------------------------------------------------------------------
//
// �o�b�I�u�W�F�N�g�̃��b�V���|�C���^�ݒ�
//
//  CPcProc* pProc
//
// ---------------------------------------------------------------------------
void CPcObj::SetMesh(CPcProc* pProc)
{
	m_pMesh = pProc->GetMesh();					// �X�L�����b�V���̃|�C���^
	m_nHoldItem = pProc->GetHoldItem();			// ��Ɏ�����̏��𓾂�  // -- 2020.6.21
	m_AnimStatus.SetNum(0);                     // �A�j���[�V�����̃Z�b�g
	m_AnimStatus.animFrame = 0;                 // �A�j���[�V�����t���[���̃Z�b�g
}
// ---------------------------------------------------------------------------
//
// �o�b�I�u�W�F�N�g�̃��[�J�����}�g���b�N�X�𓾂�֐�
//
//  m_mWorld�̈ʒu����m_fLocalRotY�̊p�x��������
//  ���[�J�����}�g���b�N�X��Ԃ�
//
// ---------------------------------------------------------------------------
MATRIX4X4 CPcObj::GetLocalMatrix()
{
	MATRIX4X4 mPos = GetPositionMatrix(m_mWorld);
	MATRIX4X4 mRotY;

	mRotY = XMMatrixRotationY(XMConvertToRadians(m_fLocalRotY));
	mRotY = mRotY * mPos;
	return mRotY;
}
//M.S �Q�[���̏�����������֐�
//��  ���F�Ȃ�
//�߂�l�F�Ȃ�
void	CPcProc::ResetNewGamePc() {
	GetPcObjPtr()->oldHP = m_pGMain->initialH;  // 4
	GetPcObjPtr()->oldVP = m_pGMain->initialV;  // 4
	GetPcObjPtr()->changeStepNum = 0;
	GetPcObjPtr()->surfaceNum = 0;
	GetPcObjPtr()->frontFlag = true;
	GetPcObjPtr()->nowPcPosNum = 0;
	GetPcObjPtr()->trainDirectionFlag = 1;
	GetPcObjPtr()->edgeFlag = false;
	GetPcObjPtr()->ResetNewGamePcObj();
	for (int hori = 0; hori < 10; hori++) {
		for (int ver = 0; ver < 10; ver++) {
			lineMapSub[hori][ver] = { 0 };
		}
	}
	rotateMapNorthNow = 0;
	rotateOkFlag = true;
	oneScreenFlag = false;
	initialStart = true;
	trainStep = 0;
	// BackFore�̏�����
	m_pGMain->m_pBackForeProc->initialDraw = 0;
	m_pGMain->m_pBackForeProc->builtStarBridge = false;
	m_pGMain->m_pBackForeProc->initialWaitingNumSet = true;
	// Title�̏�����
	m_pGMain->m_pTitleProc->initialRankingSorting = true;
	m_pGMain->stopOperation = false;
	//  Title �Q�[���N���A�A�I�[�o�[�A���U���g�̏����T�E���h�����̏�����
	m_pGMain->m_pTitleProc->RingSound = false;
	m_pGMain->m_pTitleProc->RingResultSound = false;
}
//M.S �Q�[���̏�����������֐�
//��  ���F�Ȃ�
//�߂�l�F�Ȃ�
void	CPcObj::ResetNewGamePcObj() {
	m_fLocalRotY = 0.0f;
	moveTimes = 0;
	m_AnimStatus.playAnim = true;
	m_AnimStatus.SetNum(0);
	gameOverTime = 100;
	animCount = 59;
	startTimeFlag = false;
}
//-----------------------------------------------------------------------------
// �o�b�I�u�W�F�N�g�̍X�V
//
//�@�L�[�{�[�h�ło�b�𓮂���
//�@�o�b�̃A�j���[�V�����A�W�����v�A���R����
//�@���[���h���W�ԊҁA�}�b�v�Ƃ̐ڐG����
//�@�o�b�̍U���������s��
//
//   �����@�@�@�Ȃ�
//-----------------------------------------------------------------------------
void	CPcObj::Update()
{
	// M.S �ŏ��̃X�^�\�g���������Ă��Ȃ����ǂ���
	if (m_pGMain->m_pPcProc->initialStart == true) {
		if (m_pGMain->m_dwGameMode != 3) {      // M.S �����L���O���[�h�ȊO��������
			// M.S startTime�ɔ��˂܂ł̑҂����Ԃ�����
			startTime = m_pGMain->waitingTimeSelectNum * 60;
		}
		else if (m_pGMain->m_dwGameMode == 3) { // M.S �����L���O���[�h��������
			// M.S startTime�ɔ��˂܂ł̑҂����Ԃ�����
			startTime = m_pGMain->rankWaitingTimeSelectNum * 60;
		}
		// M.S �ŏ��̃X�^�\�g�����t���O(initialStart)��false
		m_pGMain->m_pPcProc->initialStart = false;
	}
	if (m_pGMain->transparentSwitch == true) {   // M.S �L�����N�^�[�̔�\���t���O��true���ǂ���
		m_bActive = false;   // M.S �L�����N�^�[�̕\����false
	}
	else {
		startTime--;  // M.S startTime�����炷
		// M.S �҂����Ԃ�0�ȉ����A�X�^�[�g�\�t���O��true����
		//     �l�L�����̏�ԏ������łȂ����ǂ���
		if (startTime <= 0 && startTimeFlag == true 
			&& m_pGMain->m_pEnmProc->m_pEnmGolemProc->managementDeadProcess == false
			&& m_pGMain->m_pEnmProc->m_pEnmRSProc->managementDeadProcess == false 
			&& m_pGMain->m_pEnmProc->m_pEnmBdProc->managementDeadProcess == false) {
			startTime = 0;                       // M.S startTime��0�ɂ���
			m_bActive = true;                    // M.S �L�����̕\��
			m_pGMain->m_pPcProc->rotateOkFlag = false;     // M.S �}�b�v�̉�]���~�߂�
			// ��O�̈ʒu��ۑ�
			m_mWorldOld = m_mWorld;
			UpdateNormal();  // �o�b�I�u�W�F�N�g�̍X�V �ʏ��ԁiNORMAL�j
			// �}�b�v�R���W�����Ǝ��R����
    		m_fJumpY += (0.5f*GRAVITY*0.00005f)*m_fJumpTime;	// ���R����
			m_fJumpTime += 1.0f;
			if (m_pGMain->m_pMapProc->isCollisionMoveGravity(&m_mWorld, m_mWorldOld) != 3)  // �}�b�v�R���W����
			{
				m_fJumpY = 0.0f;  // ���R�����̒�~
				m_fJumpTime = 0.0f;
			}
			//�����_�����O
			int shineFlag = 0;    // �����_�[�̎w�� M.S	
			m_pMesh->Render(m_AnimStatus, m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt, shineFlag);
			// �o�E���f�B���O�{�b�N�X
			m_pBBox->m_mWorld = m_mWorld;
			// ��Ɏ������A�C�e���̕\��������     // -- 2021.2.4
			if (m_nHoldItem.m_nHoldObjNo != 0) // ��Ɏ������A�C�e��������Ƃ�
			{
				MATRIX4X4 mHold;
				mHold = m_pMesh->GetFrameMatrices(m_AnimStatus, m_mWorld, m_nHoldItem.m_nPosBone, m_nHoldItem.m_nPosMesh);  // ��̈ʒu�̃{�[���}�g���b�N�X
				m_pGMain->m_pWeaponProc->m_pWeaponHoldProc->Disp(mHold, m_nHoldItem); // �A�C�e���\��
			}

		}  // M.S ����ȊO(��ԏ������Ȃ�)�������ꍇ
		else {
			if (frontFlag == true) {   	// M.S �L����������\�ʂɂ��邩�ǂ���
				frontFlag = false;      // M.S frontFlag��false 
			}
			// M.S nowPositionRideStop�ɃL�����̌��ݒn������
			VECTOR3 nowPositionRideStop = GetPositionVector(m_mWorld);
			// M.S �L�����̌��ݒn(��)�̎擾
			JudgeNowPcMap(nowPositionRideStop, false);
			// M.S �L����������ʃ}�b�v�̍X�V������
			m_pGMain->m_pPcProc->lineMapNew(surfaceNum);
			//�����_�����O
			int shineFlag = 0;   // �����_�[�̎w�� M.S	
			m_pMesh->Render(m_AnimStatus, m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt, shineFlag);
		}
	}
}
//-----------------------------------------------------------------------------   // -- 2019.3.5
// �o�b�I�u�W�F�N�g�̍X�V �ʏ��ԁiNORMAL�j
//
//�@�o�b�̃A�j���[�V�����A�W�����v�A���R����
//�@���[���h���W�ԊҁA�}�b�v�Ƃ̐ڐG����
//
//
//   �����@�Ȃ�
//
//-----------------------------------------------------------------------------
void	CPcObj::UpdateNormal()
{
	if (m_dwStatus == FLASH) // �o�b���_���[�W���畜�A�����Ƃ��̏���
	{
		m_nCnt1--;
		if (m_nCnt1 <= 0) m_dwStatus = NORMAL;
	}
	UpdateNormalMove();      // �o�b�I�u�W�F�N�g�̈ړ�����
	// �S�Ă̓G�̃o�E���f�B���O�{�b�N�X�Ƃ̂����蔻��
	if (m_dwStatus != FLASH) m_pGMain->m_pEnmProc->Hitcheck(this, m_pBBox);   // -- 2019.6.8
}
// M.S
// �v���C�L����������}�b�v�z��������Ă���֐�
// ��  ���Fint surfaceNum    �X�V��������(�v���C�L�����������)�̐���
// �߂�l�F�Ȃ�
void CPcProc::lineMapNew(int surfaceNum) {
	// �ʂɂ���ĕۑ�����Ă���lineMapBuf��lineMapSub�Ɏ����Ă���
	switch (surfaceNum) {
	case 0:     // �����Q�[����ʏ�Ő���
		for (int h = 0; h < 10; h++) {
			for (int v = 0; v < 10; v++) {
				lineMapSub[h][v] = m_pGMain->m_pMapProc->lineMapBuf1[h][v];
			}
		}
		break;
	case 1:     // �����Q�[����ʏ�Ő��ʂ̉�
		for (int h = 0; h < 10; h++) {
			for (int v = 0; v < 10; v++) {
				lineMapSub[h][v] = m_pGMain->m_pMapProc->lineMapBuf2[h][v];
			}
		}
		break;
	case 2:    // �����Q�[����ʏ�Ő��ʂ̗���
		for (int h = 0; h < 10; h++) {
			for (int v = 0; v < 10; v++) {
				lineMapSub[h][v] = m_pGMain->m_pMapProc->lineMapBuf3[h][v];
			}
		}
		break;
	case 3:    // �����Q�[����ʏ�Ő��ʂ̏�
		for (int h = 0; h < 10; h++) {
			for (int v = 0; v < 10; v++) {
				lineMapSub[h][v] = m_pGMain->m_pMapProc->lineMapBuf4[h][v];
			}
		}
		break;
	case 4:    // �����Q�[����ʏ�Ő��ʂ̉E
		for (int h = 0; h < 10; h++) {
			for (int v = 0; v < 10; v++) {
				lineMapSub[h][v] = m_pGMain->m_pMapProc->lineMapBuf5[h][v];
			}
		}
		break;
	case 5:   // �����Q�[����ʏ�Ő��ʂ̍�
		for (int h = 0; h < 10; h++) {
			for (int v = 0; v < 10; v++) {
				lineMapSub[h][v] = m_pGMain->m_pMapProc->lineMapBuf6[h][v];
			}
		}
		break;
	}
}
// M.S
// �v���C�L�����������}�b�v�z����L�^����֐�
// ��  ���Fint oldsurfaceNum    �v���C�L�����������ʂ̐���
// �߂�l�F�Ȃ�
void CPcProc::lineMapSet(int oldsurfaceNum) {
	// ��ɑ���}�b�v�����������Ȃ��悤�ɂ���
		// ��]�̂������̂������
	switch (oldsurfaceNum) {
	case 0:     // �����Q�[����ʏ�Ő���
		for (int h = 0; h < 10; h++) {
			for (int v = 0; v < 10; v++) {
				m_pGMain->m_pMapProc->lineMapBuf1[h][v] = lineMapSub[h][v];
			}
		}
		break;
	case 1:    // �����Q�[����ʏ�Ő��ʂ̉�
		for (int h = 0; h < 10; h++) {
			for (int v = 0; v < 10; v++) {
				m_pGMain->m_pMapProc->lineMapBuf2[h][v] = lineMapSub[h][v];
			}
		}
		break;
	case 2:    // �����Q�[����ʏ�Ő��ʂ̗���
		for (int h = 0; h < 10; h++) {
			for (int v = 0; v < 10; v++) {
				m_pGMain->m_pMapProc->lineMapBuf3[h][v] = lineMapSub[h][v];
			}
		}
		break;
	case 3:    // �����Q�[����ʏ�Ő��ʂ̏�
		for (int h = 0; h < 10; h++) {
			for (int v = 0; v < 10; v++) {
				m_pGMain->m_pMapProc->lineMapBuf4[h][v] = lineMapSub[h][v];
			}
		}
		break;
	case 4:    // �����Q�[����ʏ�Ő��ʂ̉E
		for (int h = 0; h < 10; h++) {
			for (int v = 0; v < 10; v++) {
				m_pGMain->m_pMapProc->lineMapBuf5[h][v] = lineMapSub[h][v];
			}
		}
		break;
	case 5:    // �����Q�[����ʏ�Ő��ʂ̍�
		for (int h = 0; h < 10; h++) {
			for (int v = 0; v < 10; v++) {
				m_pGMain->m_pMapProc->lineMapBuf6[h][v] = lineMapSub[h][v];
			}
		}
		break;
	}
}
// M.S
// ��Βl����L�����̏オX���AY���AZ���̂ǂ��������Ă���̂����ׂ�
// ��  ���Fint                kindNum    0�̓v���C�L�����̏ꍇ  1�͐l�L�����̏ꍇ
//       �FVector             pos        �L�����̈ʒu
// �߂�l�F�Ȃ�
void CPcProc::JudgeAbsoluteSize(int kindNum, VECTOR3 pos) {
	float upperLimit;
	float upPos = 6.0f;
	if (kindNum == 0) {
		upperLimit = 5.0f;
	}
	else if (kindNum == 1) {
		upperLimit = 4.7f;
	}
	// 100�{����int�ɃL���X�g������
	float castX = pos.x * 100.0f;
	float castY = pos.y * 100.0f;
	float castZ = pos.z * 100.0f;
	int castX1 = (int)castX;
	int castY1 = (int)castY;
	int castZ1 = (int)castZ;
	// 100����1����pos�̒l�̏������ʖ�����؂�
	castX = castX1 / 100.0f;
	castY = castY1 / 100.0f;
	castZ = castZ1 / 100.0f;
	// ��Βl�����߂�
	float x = fabsf(castX);
	float y = fabsf(castY);
	float z = fabsf(castZ);
	// x��upperLimit���傫�����ǂ���
	if (x >= upperLimit) {
		x = x - 6.0f;     
	}
	else {
		x = 100;
	}
	// y��upperLimit���傫�����ǂ���
	if (y >= upperLimit) {
		y = y - 6.0f;
	}
	else {
		y = 100;
	}
	// z��upperLimit���傫�����ǂ���
	if (z >= upperLimit) {
		z = z - 6.0f;
	}
	else {
		z = 100;
	}
	// ��Βl�����߂�
	float conmpX = fabsf(x);
	float conmpY = fabsf(y);
	float conmpZ = fabsf(z);
	// conmpX,conmpY,conmpZ���ׂĈ�ԏ������l(�����Ă��鎲)�̕ϐ���true
	if (conmpX < conmpY && conmpX < conmpZ) {
		this->xJudge = true;
	}
	else if (conmpY < conmpX && conmpY < conmpZ) {
		this->yJudge = true;
	}
	else if (conmpZ < conmpX && conmpZ < conmpY) {
		this->zJudge = true;
	}
}
// M.S
// ��]�̊p�x�𒲂ׂ�֐�
// ��  ���Fint                 surfaceNum          ���ׂ�ʂ̐���
//       �Ffloat               upBack              BBox�𒲂ׂ��̃��C�̈ʒu(��)
//       �Ffloat               upFront             BBox�𒲂ׂ��̃��C�̈ʒu(�O)
//       �Ffloat               downBack            BBox�𒲂ׂ鉺�̃��C�̈ʒu(��)
//       �Ffloat               downFront           BBox�𒲂ׂ鉺�̃��C�̈ʒu(�O)
//       �Ffloat               rightBack           BBox�𒲂ׂ�E�̃��C�̈ʒu(��)
//       �Ffloat               rightFront          BBox�𒲂ׂ�E�̃��C�̈ʒu(�O)
//       �Ffloat               leftBack            BBox�𒲂ׂ鍶�̃��C�̈ʒu(��)
//       �Ffloat               leftFront           BBox�𒲂ׂ鍶�̃��C�̈ʒu(�O)
// �߂�l�Fint                 rotateMapNorthNow   �E��] 1:��]�Ȃ� 2:+90�x��] 3:+180�x��] 4:+270�x��]
int CPcProc::JudgeRotateSurface(int surfaceNum, VECTOR3 upBack, VECTOR3 upFront,
	                           VECTOR3 downBack, VECTOR3 downFront, VECTOR3 rightBack,
	                           VECTOR3 rightFront, VECTOR3 leftBack, VECTOR3 leftFront) {
	switch (surfaceNum) {
	case 0:
		rotateMapNorthNow = JudgeRotateSurfaceUp(upBack, upFront, downBack, downFront, rightBack, rightFront, leftBack, leftFront);
		return rotateMapNorthNow;
		break;
	case 1:
		rotateMapNorthNow = JudgeRotateSurfaceUnder(upBack, upFront, downBack, downFront, rightBack, rightFront, leftBack, leftFront);
		return rotateMapNorthNow;
		break;
	case 2:
		rotateMapNorthNow = JudgeRotateSurfaceDown(upBack, upFront, downBack, downFront, rightBack, rightFront, leftBack, leftFront);
		return rotateMapNorthNow;
		break;
	case 3:
		rotateMapNorthNow = JudgeRotateSurfaceAbove(upBack, upFront, downBack, downFront, rightBack, rightFront, leftBack, leftFront);
		return rotateMapNorthNow;
		break;
	case 4:
		rotateMapNorthNow = JudgeRotateSurfaceRight(upBack, upFront, downBack, downFront, rightBack, rightFront, leftBack, leftFront);
		return rotateMapNorthNow;
		break;
	case 5:
		rotateMapNorthNow = JudgeRotateSurfaceLeft(upBack, upFront, downBack, downFront, rightBack, rightFront, leftBack, leftFront);
		return rotateMapNorthNow;
		break;
	}
	return 5;
}
// M.S
// ��]�̊p�x�𒲂ׂ�֐�(������ԂŐ��ʂ̖�)
// ��  ���FVECTOR3               upBack              BBox�𒲂ׂ��̃��C�̈ʒu(��)
//       �FVECTOR3               upFront             BBox�𒲂ׂ��̃��C�̈ʒu(�O)
//       �FVECTOR3               downBack            BBox�𒲂ׂ鉺�̃��C�̈ʒu(��)
//       �FVECTOR3               downFront           BBox�𒲂ׂ鉺�̃��C�̈ʒu(�O)
//       �FVECTOR3               rightBack           BBox�𒲂ׂ�E�̃��C�̈ʒu(��)
//       �FVECTOR3               rightFront          BBox�𒲂ׂ�E�̃��C�̈ʒu(�O)
//       �FVECTOR3               leftBack            BBox�𒲂ׂ鍶�̃��C�̈ʒu(��)
//       �FVECTOR3               leftFront           BBox�𒲂ׂ鍶�̃��C�̈ʒu(�O)
// �߂�l�Fint                 rotateMapNorthNow   �E��] 1:��]�Ȃ� 2:+90�x��] 3:+180�x��] 4:+360�x��]
int CPcProc::JudgeRotateSurfaceUp(VECTOR3 upBack, VECTOR3 upFront,VECTOR3 downBack, 
	                              VECTOR3 downFront, VECTOR3 rightBack,VECTOR3 rightFront, 
	                              VECTOR3 leftBack, VECTOR3 leftFront) {
	//�㉺���E�Ƀ��C���΂��Č��̃}�b�v����ǂꂾ����]���Ă��邩�݂�
	directrioFlag1 = m_pGMain->m_pMapProc->m_pBBoxArrow1[0]->
		OBBCollisionLay(/*back*/upBack, /*front*/upFront, &mHit, &mNor);
	directrioFlag2 = m_pGMain->m_pMapProc->m_pBBoxArrow1[0]->
		OBBCollisionLay(/*back*/downBack, /*front*/downFront, &mHit, &mNor);
	directrioFlag3 = m_pGMain->m_pMapProc->m_pBBoxArrow1[0]->
		OBBCollisionLay(/*back*/rightBack, /*front*/rightFront, &mHit, &mNor);
	directrioFlag4 = m_pGMain->m_pMapProc->m_pBBoxArrow1[0]->
		OBBCollisionLay(/*back*/leftBack, /*front*/leftFront, &mHit, &mNor);
	if (directrioFlag1 == true) {
		rotateMapNorthNow = 1;
		return rotateMapNorthNow;
	}
	else if (directrioFlag2 == true) {
		rotateMapNorthNow = 3;
		return rotateMapNorthNow;
	}
	else if (directrioFlag3 == true) {
		rotateMapNorthNow = 2;
		return rotateMapNorthNow;
	}
	else if (directrioFlag4 == true) {
		rotateMapNorthNow = 4;
		return rotateMapNorthNow;
	}
	return 5;
}
// M.S
// ��]�̊p�x�𒲂ׂ�֐�(������ԂŐ��ʂ̉��̖�)
// ��  ���FVECTOR3               upBack              BBox�𒲂ׂ��̃��C�̈ʒu(��)
//       �FVECTOR3               upFront             BBox�𒲂ׂ��̃��C�̈ʒu(�O)
//       �FVECTOR3               downBack            BBox�𒲂ׂ鉺�̃��C�̈ʒu(��)
//       �FVECTOR3               downFront           BBox�𒲂ׂ鉺�̃��C�̈ʒu(�O)
//       �FVECTOR3               rightBack           BBox�𒲂ׂ�E�̃��C�̈ʒu(��)
//       �FVECTOR3               rightFront          BBox�𒲂ׂ�E�̃��C�̈ʒu(�O)
//       �FVECTOR3               leftBack            BBox�𒲂ׂ鍶�̃��C�̈ʒu(��)
//       �FVECTOR3               leftFront           BBox�𒲂ׂ鍶�̃��C�̈ʒu(�O)
// �߂�l�Fint                 rotateMapNorthNow   �E��] 1:��]�Ȃ� 2:+90�x��] 3:+180�x��] 4:+360�x��]
int CPcProc::JudgeRotateSurfaceUnder(VECTOR3 upBack, VECTOR3 upFront, VECTOR3 downBack,
	                                 VECTOR3 downFront, VECTOR3 rightBack, VECTOR3 rightFront,
	                                 VECTOR3 leftBack, VECTOR3 leftFront) {
	directrioFlag1 = m_pGMain->m_pMapProc->m_pBBoxArrow4[0]->
		OBBCollisionLay(/*back*/upBack, /*front*/upFront, &mHit, &mNor);
	directrioFlag2 = m_pGMain->m_pMapProc->m_pBBoxArrow4[0]->
		OBBCollisionLay(/*back*/downBack, /*front*/downFront, &mHit, &mNor);
	directrioFlag3 = m_pGMain->m_pMapProc->m_pBBoxArrow4[0]->
		OBBCollisionLay(/*back*/rightBack, /*front*/rightFront, &mHit, &mNor);
	directrioFlag4 = m_pGMain->m_pMapProc->m_pBBoxArrow4[0]->
		OBBCollisionLay(/*back*/leftBack, /*front*/leftFront, &mHit, &mNor);
	if (directrioFlag1 == true) {
		rotateMapNorthNow = 1;
		return rotateMapNorthNow;
	}
	else if (directrioFlag2 == true) {
		rotateMapNorthNow = 3;
		return rotateMapNorthNow;
	}
	else if (directrioFlag3 == true) {
		rotateMapNorthNow = 2;
		return rotateMapNorthNow;
	}
	else if (directrioFlag4 == true) {
		rotateMapNorthNow = 4;
		return rotateMapNorthNow;
	}
	return 5;
}
// M.S
// ��]�̊p�x�𒲂ׂ�֐�(������ԂŐ��ʂ̗��̖�)
// ��  ���FVECTOR3               upBack              BBox�𒲂ׂ��̃��C�̈ʒu(��)
//       �FVECTOR3               upFront             BBox�𒲂ׂ��̃��C�̈ʒu(�O)
//       �FVECTOR3               downBack            BBox�𒲂ׂ鉺�̃��C�̈ʒu(��)
//       �FVECTOR3               downFront           BBox�𒲂ׂ鉺�̃��C�̈ʒu(�O)
//       �FVECTOR3               rightBack           BBox�𒲂ׂ�E�̃��C�̈ʒu(��)
//       �FVECTOR3               rightFront          BBox�𒲂ׂ�E�̃��C�̈ʒu(�O)
//       �FVECTOR3               leftBack            BBox�𒲂ׂ鍶�̃��C�̈ʒu(��)
//       �FVECTOR3               leftFront           BBox�𒲂ׂ鍶�̃��C�̈ʒu(�O)
// �߂�l�Fint                 rotateMapNorthNow  �E��] 1:��]�Ȃ� 2:+90�x��] 3:+180�x��] 4:+360�x��]
int CPcProc::JudgeRotateSurfaceDown(VECTOR3 upBack, VECTOR3 upFront, VECTOR3 downBack,
	                                VECTOR3 downFront, VECTOR3 rightBack, VECTOR3 rightFront,
	                                VECTOR3 leftBack, VECTOR3 leftFront) {
	directrioFlag1 = m_pGMain->m_pMapProc->m_pBBoxArrow3[0]->
		OBBCollisionLay(/*back*/upBack, /*front*/upFront, &mHit, &mNor);
	directrioFlag2 = m_pGMain->m_pMapProc->m_pBBoxArrow3[0]->
		OBBCollisionLay(/*back*/downBack, /*front*/downFront, &mHit, &mNor);
	directrioFlag3 = m_pGMain->m_pMapProc->m_pBBoxArrow3[0]->
		OBBCollisionLay(/*back*/rightBack, /*front*/rightFront, &mHit, &mNor);
	directrioFlag4 = m_pGMain->m_pMapProc->m_pBBoxArrow3[0]->
		OBBCollisionLay(/*back*/leftBack, /*front*/leftFront, &mHit, &mNor);
	if (directrioFlag1 == true) {
		rotateMapNorthNow = 1;
		return rotateMapNorthNow;
	}
	else if (directrioFlag2 == true) {
		rotateMapNorthNow = 3;
		return rotateMapNorthNow;
	}
	else if (directrioFlag3 == true) {
		rotateMapNorthNow = 2;
		return rotateMapNorthNow;
	}
	else if (directrioFlag4 == true) {
		rotateMapNorthNow = 4;
		return rotateMapNorthNow;
	}
	return 5;
}
// M.S
// ��]�̊p�x�𒲂ׂ�֐�(������ԂŐ��ʂ̏�̖�)
// ��  ���Fint                 upBack              BBox�𒲂ׂ��̃��C�̈ʒu(��)
//       �FVECTOR3               upFront             BBox�𒲂ׂ��̃��C�̈ʒu(�O)
//       �FVECTOR3               downBack            BBox�𒲂ׂ鉺�̃��C�̈ʒu(��)
//       �FVECTOR3               downFront           BBox�𒲂ׂ鉺�̃��C�̈ʒu(�O)
//       �FVECTOR3               rightBack           BBox�𒲂ׂ�E�̃��C�̈ʒu(��)
//       �FVECTOR3               rightFront          BBox�𒲂ׂ�E�̃��C�̈ʒu(�O)
//       �FVECTOR3               leftBack            BBox�𒲂ׂ鍶�̃��C�̈ʒu(��)
//       �FVECTOR3               leftFront           BBox�𒲂ׂ鍶�̃��C�̈ʒu(�O)
// �߂�l�Fint                 rotateMapNorthNow   �E��] 1:��]�Ȃ� 2:+90�x��] 3:+180�x��] 4:+360�x��]
int CPcProc::JudgeRotateSurfaceAbove(VECTOR3 upBack, VECTOR3 upFront, VECTOR3 downBack,
	                                 VECTOR3 downFront, VECTOR3 rightBack, VECTOR3 rightFront,
                                   	 VECTOR3 leftBack, VECTOR3 leftFront) {
	directrioFlag1 = m_pGMain->m_pMapProc->m_pBBoxArrow2[0]->
		OBBCollisionLay(/*back*/upBack, /*front*/upFront, &mHit, &mNor);
	directrioFlag2 = m_pGMain->m_pMapProc->m_pBBoxArrow2[0]->
		OBBCollisionLay(/*back*/downBack, /*front*/downFront, &mHit, &mNor);
	directrioFlag3 = m_pGMain->m_pMapProc->m_pBBoxArrow2[0]->
		OBBCollisionLay(/*back*/rightBack, /*front*/rightFront, &mHit, &mNor);
	directrioFlag4 = m_pGMain->m_pMapProc->m_pBBoxArrow2[0]->
		OBBCollisionLay(/*back*/leftBack, /*front*/leftFront, &mHit, &mNor);
	if (directrioFlag1 == true) {
		rotateMapNorthNow = 1;
		return rotateMapNorthNow;
	}
	else if (directrioFlag2 == true) {
		rotateMapNorthNow = 3;
		return rotateMapNorthNow;
	}
	else if (directrioFlag3 == true) {
		rotateMapNorthNow = 2;
		return rotateMapNorthNow;
	}
	else if (directrioFlag4 == true) {
		rotateMapNorthNow = 4;
		return rotateMapNorthNow;
	}
	return 5;
}
// M.S
// ��]�̊p�x�𒲂ׂ�֐�(������ԂŐ��ʂ̉E�̖�)
// ��  ���FVECTOR3               upBack              BBox�𒲂ׂ��̃��C�̈ʒu(��)
//       �FVECTOR3               upFront             BBox�𒲂ׂ��̃��C�̈ʒu(�O)
//       �FVECTOR3               downBack            BBox�𒲂ׂ鉺�̃��C�̈ʒu(��)
//       �FVECTOR3               downFront           BBox�𒲂ׂ鉺�̃��C�̈ʒu(�O)
//       �FVECTOR3               rightBack           BBox�𒲂ׂ�E�̃��C�̈ʒu(��)
//       �FVECTOR3               rightFront          BBox�𒲂ׂ�E�̃��C�̈ʒu(�O)
//       �FVECTOR3               leftBack            BBox�𒲂ׂ鍶�̃��C�̈ʒu(��)
//       �FVECTOR3               leftFront           BBox�𒲂ׂ鍶�̃��C�̈ʒu(�O)
// �߂�l�Fint                 rotateMapNorthNow   �E��] 1:��]�Ȃ� 2:+90�x��] 3:+180�x��] 4:+360�x��]
int CPcProc::JudgeRotateSurfaceRight(VECTOR3 upBack, VECTOR3 upFront, VECTOR3 downBack,
	                                 VECTOR3 downFront, VECTOR3 rightBack, VECTOR3 rightFront,
	                                 VECTOR3 leftBack, VECTOR3 leftFront) {
	directrioFlag1 = m_pGMain->m_pMapProc->m_pBBoxArrow5[0]->
		OBBCollisionLay(/*back*/upBack, /*front*/upFront, &mHit, &mNor);
	directrioFlag2 = m_pGMain->m_pMapProc->m_pBBoxArrow5[0]->
		OBBCollisionLay(/*back*/downBack, /*front*/downFront, &mHit, &mNor);
	directrioFlag3 = m_pGMain->m_pMapProc->m_pBBoxArrow5[0]->
		OBBCollisionLay(/*back*/rightBack, /*front*/rightFront, &mHit, &mNor);
	directrioFlag4 = m_pGMain->m_pMapProc->m_pBBoxArrow5[0]->
		OBBCollisionLay(/*back*/leftBack, /*front*/leftFront, &mHit, &mNor);
	if (directrioFlag1 == true) {
		rotateMapNorthNow = 1;
		return rotateMapNorthNow;
	}
	else if (directrioFlag2 == true) {
		rotateMapNorthNow = 3;
		return rotateMapNorthNow;
	}
	else if (directrioFlag3 == true) {
		rotateMapNorthNow = 2;
		return rotateMapNorthNow;
	}
	else if (directrioFlag4 == true) {
		rotateMapNorthNow = 4;
		return rotateMapNorthNow;
	}
	return 5;
}
// M.S
// ��]�̊p�x�𒲂ׂ�֐�(������ԂŐ��ʂ̍��̖�)
// ��  ���FVECTOR3               upBack              BBox�𒲂ׂ��̃��C�̈ʒu(��)
//       �FVECTOR3               upFront             BBox�𒲂ׂ��̃��C�̈ʒu(�O)
//       �FVECTOR3               downBack            BBox�𒲂ׂ鉺�̃��C�̈ʒu(��)
//       �FVECTOR3               downFront           BBox�𒲂ׂ鉺�̃��C�̈ʒu(�O)
//       �FVECTOR3               rightBack           BBox�𒲂ׂ�E�̃��C�̈ʒu(��)
//       �FVECTOR3               rightFront          BBox�𒲂ׂ�E�̃��C�̈ʒu(�O)
//       �FVECTOR3               leftBack            BBox�𒲂ׂ鍶�̃��C�̈ʒu(��)
//       �FVECTOR3               leftFront           BBox�𒲂ׂ鍶�̃��C�̈ʒu(�O)
// �߂�l�Fint                 rotateMapNorthNow  �E��] 1:��]�Ȃ� 2:+90�x��] 3:+180�x��] 4:+360�x��]
int CPcProc::JudgeRotateSurfaceLeft(VECTOR3 upBack, VECTOR3 upFront, VECTOR3 downBack,
	                                VECTOR3 downFront, VECTOR3 rightBack, VECTOR3 rightFront,
	                                VECTOR3 leftBack, VECTOR3 leftFront) {
	directrioFlag1 = m_pGMain->m_pMapProc->m_pBBoxArrow6[0]->
		OBBCollisionLay(/*back*/upBack, /*front*/upFront, &mHit, &mNor);
	directrioFlag2 = m_pGMain->m_pMapProc->m_pBBoxArrow6[0]->
		OBBCollisionLay(/*back*/downBack, /*front*/downFront, &mHit, &mNor);
	directrioFlag3 = m_pGMain->m_pMapProc->m_pBBoxArrow6[0]->
		OBBCollisionLay(/*back*/rightBack, /*front*/rightFront, &mHit, &mNor);
	directrioFlag4 = m_pGMain->m_pMapProc->m_pBBoxArrow6[0]->
		OBBCollisionLay(/*back*/leftBack, /*front*/leftFront, &mHit, &mNor);
	if (directrioFlag1 == true) {
		rotateMapNorthNow = 1;
		return rotateMapNorthNow;
	}
	else if (directrioFlag2 == true) {
		rotateMapNorthNow = 3;
		return rotateMapNorthNow;
	}
	else if (directrioFlag3 == true) {
		rotateMapNorthNow = 2;
		return rotateMapNorthNow;
	}
	else if (directrioFlag4 == true) {
		rotateMapNorthNow = 4;
		return rotateMapNorthNow;
	}
	return 5;
}
// M.S
// �L����������ʒu�̃}�b�v�ʂ̉�]�̊p�x�𒲂ׂ�֐�
// ��  ���Fint                surfaceNum             ���ׂ�ʂ̐���
//       �FVector             pos                    �L�����̈ʒu
//       �Fint                kindNum                0�̓v���C�L�����̏ꍇ  1�͐l�L�����̏ꍇ              
// �߂�l�Fint                rotateMapNorthNow      �E��] 1:��]�Ȃ� 2:�E90�x��] 3:�E180�x��] 4:�E270�x��]
int CPcProc::judgeDirection(int surfaceNum, VECTOR3 pos, int kindNum) {
	// ���ׂ�L�����̏�͂ǂ��Ɍ����Ă��邩���ׂ邽�߂̕ϐ�
	float charLimit = 5.5f;
	float charLimitMinus = -5.5f;
	float manLimit = 4.7f;
	float manLimitMinus = -4.7f;
	xJudge = false;           // x���̒l�ɑΉ�����bool�ϐ�
	yJudge = false;           // y���̒l�ɑΉ�����bool�ϐ�
	zJudge = false;           // z���̒l�ɑΉ�����bool�ϐ�
	// �}�b�v�ʂ̉�]�ɍ��킹��true�ɂȂ�t���O�̏�����
	directrioFlag1 = false;
	directrioFlag2 = false;
	directrioFlag3 = false;
	directrioFlag4 = false;
	// ��Βl����L�����̏オ�ǂ��Ɍ����Ă���̂����ׂ�
    // xJudge�AyJudgey�AzJudge�̂ǂꂩ��true���������̂ŁA�ǂ̎��������Ă��邩�킩��
	JudgeAbsoluteSize(kindNum, pos);
	// �}�b�v�ʎ��ʕϐ�rotateMapNorthNow �E��] 1:��]�Ȃ� 2:+90�x��] 3:+180�x��] 4:+360�x��]
	if (yJudge == true) {
		if (kindNum == 0 && pos.y >= charLimit || kindNum == 1 && pos.y >= manLimit) {           // �����Q�[����ʂŃJ�����̐���

			return JudgeRotateSurface(surfaceNum, upBack1, upFront1, downBack1, downFront1, rightBack1, rightFront1, leftBack1, leftFront1);			
		}
	}
	if (zJudge == true) {
    	if (kindNum == 0 && pos.z <= charLimitMinus || kindNum == 1 && pos.z <= manLimitMinus) { // �����Q�[����ʂŃJ�����̐��ʂ̉�
			return JudgeRotateSurface(surfaceNum, upBack2, upFront2, downBack2, downFront2, rightBack2, rightFront2, leftBack2, leftFront2);
		}
	}
	if (yJudge == true) {
    	if (kindNum == 0 && pos.y <= charLimitMinus || kindNum == 1 && pos.y <= manLimitMinus) { // �����Q�[����ʂŃJ�����̐��ʂ̗���
			return JudgeRotateSurface(surfaceNum, upBack3, upFront3, downBack3, downFront3, rightBack3, rightFront3, leftBack3, leftFront3);
		}
	}
	if (zJudge == true) {
	   if (kindNum == 0 && pos.z >= charLimit || kindNum == 1 && pos.z >= manLimit) {           // �����Q�[����ʂŃJ�����̐��ʂ̏�
		   return JudgeRotateSurface(surfaceNum, upBack4, upFront4, downBack4, downFront4, rightBack4, rightFront4, leftBack4, leftFront4);
		}
	}
	if (xJudge == true) {
		if (kindNum == 0 && pos.x >= charLimit || kindNum == 1 && pos.x >= manLimit) {          // �����Q�[����ʂŃJ�����̐��ʂ̉E
			return JudgeRotateSurface(surfaceNum, upBack5, upFront5, downBack5, downFront5, rightBack5, rightFront5, leftBack5, leftFront5);
		}
	}
	if (xJudge == true) {
		if (kindNum == 0 && pos.x <= charLimitMinus || kindNum == 1 && pos.x <= manLimitMinus) { // �����Q�[����ʂŃJ�����̐��ʂ̍�
			return JudgeRotateSurface(surfaceNum, upBack6, upFront6, downBack6, downFront6, rightBack6, rightFront6, leftBack6, leftFront6);
		}
	}
	return 5;
}
// M.S
// �}�b�v�ʂ̒[���玟�̖ʂֈړ����鎞�̌��ݒn�̍X�V
// ��  ���Fint                trainDirectionFlag            �L�������ړ����Ă������
//                                                           1�F��  2�F�E  3�F��  4�F��
//       �Fint                oldHP                         �X�V�O�̃L�����̈ʒu(�s)
//       �Fint                oldVP                         �X�V�O�̃L�����̈ʒu(��)
//       �Fint                surfaceNum                    �ړ��O�̖ʂ̐���
// �߂�l�F�Ȃ�
void CPcObj::updateEdgeOldHV(int trainDirectionFlag,int oldHP, int oldVP, int surfaceNum) {
	// �v���C�L��������[�ɂ��āA�ړ��������ゾ������
	if (oldHP == 0 && trainDirectionFlag == 1) {   
		switch (surfaceNum) {
		case 0:                   // �����Q�[����ʂŃJ�����̐���
			this->oldHP = 10;
			this->oldVP = oldVP;
			break;
		case 1:
			this->oldHP = 10;
			this->oldVP = oldVP;
			break;
		case 2:
			this->oldHP = 10;
			this->oldVP = oldVP;	
			break;
		case 3:
			this->oldHP = 10;
			this->oldVP = oldVP;
			break;
		case 4:
			this->oldHP = 9 - oldVP;
			this->oldVP = 10;
			this->trainDirectionFlag = 4;
			break;
		case 5:
			this->oldHP = oldVP;
			this->oldVP = -1;
			this->trainDirectionFlag = 2;
			break;
		}
	}// �v���C�L���������[�ɂ��āA�ړ�����������������
	else if (oldHP == 9 && trainDirectionFlag == 3) { 
		switch (surfaceNum) {
		case 0:
		    this->oldHP = -1;
			this->oldVP = oldVP;
			break;
		case 1:
		   	this->oldHP = -1;
			this->oldVP = oldVP;
			break;
		case 2:
			this->oldHP = -1;
			this->oldVP = oldVP;
			break;
		case 3:
			this->oldHP = -1;
			this->oldVP = oldVP;
			break;
		case 4:
			this->oldHP = oldVP;
			this->oldVP = 10;
			this->trainDirectionFlag = 4;
			break;
		case 5:
			this->oldHP = 9 - oldVP;
			this->oldVP = -1;
			this->trainDirectionFlag = 2;
			break;	
		}
	}// �v���C�L���������[�ɂ��āA�ړ�����������������
	else if (oldVP == 0 && trainDirectionFlag == 4) {
		switch (surfaceNum) {
		case 0:
			//if (PlacementSurfaceNum == 0) {
			this->oldHP = oldHP;
			this->oldVP = 10;
			break;
		case 1:
			this->oldHP = 10;
			this->oldVP = 9 - oldHP;
			this->trainDirectionFlag = 1;
			break;
		case 2:
			this->oldHP = 9 - oldHP;
			this->oldVP = -1;
			this->trainDirectionFlag = 2;
			break;
		case 3:
			this->oldVP = oldHP;
			this->oldHP = -1;
			this->trainDirectionFlag = 3;
			break;		
		case 4:
			this->oldHP = oldHP;
			this->oldVP = 10;
			break;
		case 5:
			this->oldHP = 9 - oldHP;
			this->oldVP = -1;
			this->trainDirectionFlag = 2;
			break;
		}
	}// �v���C�L�������E�[�ɂ��āA�ړ��������E��������
	else if (oldVP == 9 && trainDirectionFlag == 2) {
		switch (surfaceNum) {
		case 0:
			this->oldHP = oldHP;
			this->oldVP = -1;
			break;
		case 1:
			this->oldVP = oldHP;
			this->oldHP = 10;
			this->trainDirectionFlag = 1;
			break;
		case 2:
			this->oldHP = 9 - oldHP;
			this->oldVP = 10;
			this->trainDirectionFlag = 4;
			break;
		case 3:
			this->oldHP = -1;
			this->oldVP = 9 - oldHP;
			this->trainDirectionFlag = 3;
			break;
		case 4:
			this->oldHP = 9 - oldHP;
			this->oldVP = 10;
			this->trainDirectionFlag = 4;
			break;
		case 5:
			this->oldHP = oldHP;
			this->oldVP = -1;
			break;		
		}
	}
}
// M.S
// upBack�AupFront�Ƀ��C���΂��A���̃��C�̏ꏊ�ɂǂ��̖ʂ�����̂����ׂ�
// ��  ���FMATRIX4X4          upBack           ��΂����C�̏ꏊ(��)
//       �FMATRIX4X4          upFront          ��΂����C�̏ꏊ(��O)  
// �߂�l�Fint                                 ���������ʂ̐���
int CPcObj::RayOrderSurfaceBBox(MATRIX4X4 upBack, MATRIX4X4 upFront) {
	for (int i = 0; i < 6; i++) {
		// �e�ʂ�BBox�����ԂɌ��Ă����A���C�Ɠ����邩�ǂ���
		bool nowPosSurfaceflag = m_pGMain->m_pMapProc->m_pBBoxPosition[i]->OBBCollisionLay(/*back*/upBack, /*front*/upFront, &mHit, &mNor);
		// ���������炻�̖ʂ̐�����surfaceNum�ɓ����
		if (nowPosSurfaceflag == true) {
			surfaceNum = i;
			return surfaceNum;
		}
	}
	return 10;
}
// M.S
// �L����������ʂ̐�����ʒu�𒲂ׂ�
// ��  ���FVECTOR3          nowPosition           �L����������ʒu
//       �Fbool             onlyFront             true  �F����(����\��)�ɂ��邩�ǂ�������̂ݍs��
//                                                      false �F���ׂĂ̏������s��
//                                                      nowPcPosNum�ɂ̓L�����̈ʒu�̐����������Ă��܂�
//                                                      nowPcPosNum 0:�� 1:��O 2:�� 3:1�̗� 4:�E 5:��
// �߂�l�Fint                                          �L����������ʂ̐���
int CPcObj::JudgeNowPcMap(VECTOR3 nowPosition, bool onlyFront) {
	float charLimit = 5.5f;
	float charLimitMinus = -5.5f;
	m_pGMain->m_pPcProc->xJudge = false;           // x���̒l�ɑΉ�����bool�ϐ�
	m_pGMain->m_pPcProc->yJudge = false;           // y���̒l�ɑΉ�����bool�ϐ�
	m_pGMain->m_pPcProc->zJudge = false;           // z���̒l�ɑΉ�����bool�ϐ�
	// ��Βl����L�����̏オ�ǂ��Ɍ����Ă���̂����ׂ�
	// xJudge�AyJudgey�AzJudge�̂ǂꂩ��true���������̂ŁA�ǂ̎��������Ă��邩�킩��
	m_pGMain->m_pPcProc->JudgeAbsoluteSize(0, nowPosition);
	if (m_pGMain->m_pPcProc->yJudge == true) {         // �����Q�[����ʂŃJ�����̐���
		if (nowPosition.y >= charLimit) {  
				// BBox�֔�΂����C
				MATRIX4X4 upFront = XMMatrixTranslation(0.0f, 10.0f, 0.0f);  // ��O
				MATRIX4X4 upBack = XMMatrixTranslation(0.0f, 3.0f, 0.0f);    // ��
				nowPcPosNum = 0;            // �ꏊ�̒l  
				frontFlag = true;           // ���ʂɃv���C�L����������t���O��true
				if (onlyFront == true) {   	// ����(����\��)�ɂ��邩�ǂ�������̂ݍs�����ǂ���
					return 10;
				}  
				return RayOrderSurfaceBBox(upBack, upFront);  // �e�ʂ�BBox�Ƀ��C���΂��A���������ʂ̐�����Ԃ�
		}
	}
	if (m_pGMain->m_pPcProc->zJudge == true) {         // �����Q�[����ʂŃJ�����̐��ʂ̉�
		if (nowPosition.z <= charLimitMinus) {
				// BBox�֔�΂����C
				MATRIX4X4 upFront = XMMatrixTranslation(0.0f, 0.0f, -10.0f);  // ��O
				MATRIX4X4 upBack = XMMatrixTranslation(0.0f, 0.0f, -3.0f);    // ��
				nowPcPosNum = 1;          // �ꏊ�̒l 
				return RayOrderSurfaceBBox(upBack, upFront);   // �e�ʂ�BBox�Ƀ��C���΂��A���������ʂ̐�����Ԃ�
		}
	}
	if (m_pGMain->m_pPcProc->yJudge == true) {
		if (nowPosition.y <= charLimitMinus) {         // �����Q�[����ʂŃJ�����̐��ʂ̗���
				// BBox�֔�΂����C
				MATRIX4X4 upFront = XMMatrixTranslation(0.0f, -10.0f, 0.0f);  // ��O
				MATRIX4X4 upBack = XMMatrixTranslation(0.0f, -3.0f, 0.0f);    // ��
				nowPcPosNum = 2;          // �ꏊ�̒l  
				return RayOrderSurfaceBBox(upBack, upFront);   // �e�ʂ�BBox�Ƀ��C���΂��A���������ʂ̐�����Ԃ�
		}
	} 
	if (m_pGMain->m_pPcProc->zJudge == true) {
		if (nowPosition.z >= charLimit) {              // �����Q�[����ʂŃJ�����̐��ʂ̏�
				// BBox�֔�΂����C
				MATRIX4X4 upFront = XMMatrixTranslation(0.0f, 0.0f, 10.0f);   // ��O
				MATRIX4X4 upBack = XMMatrixTranslation(0.0f, 0.0f, 3.0f);     // ��
				nowPcPosNum = 3;          // �ꏊ�̒l 
				return RayOrderSurfaceBBox(upBack, upFront);   // �e�ʂ�BBox�Ƀ��C���΂��A���������ʂ̐�����Ԃ�
		}
	}
	if (m_pGMain->m_pPcProc->xJudge == true) {
		if (nowPosition.x >= charLimit) {              // �����Q�[����ʂŃJ�����̐��ʂ̉E
				// BBox�֔�΂����C
				MATRIX4X4 upFront = XMMatrixTranslation(10.0f, 0.0f, 0.0f);    // ��O
				MATRIX4X4 upBack = XMMatrixTranslation(3.0f, 0.0f, 0.0f);      // ��
				nowPcPosNum = 4;          // �ꏊ�̒l 
				return RayOrderSurfaceBBox(upBack, upFront);   // �e�ʂ�BBox�Ƀ��C���΂��A���������ʂ̐�����Ԃ�
		}
	}
	if (m_pGMain->m_pPcProc->xJudge == true) {
		if (nowPosition.x <= charLimitMinus) {         // �����Q�[����ʂŃJ�����̐��ʂ̍�
				// BBox�֔�΂����C
				MATRIX4X4 upFront = XMMatrixTranslation(-10.0f, 0.0f, 0.0f);   // ��O
				MATRIX4X4 upBack = XMMatrixTranslation(-3.0f, 0.0f, 0.0f);     // ��
				nowPcPosNum = 5;         // �ꏊ�̒l 
				return RayOrderSurfaceBBox(upBack, upFront);    // �e�ʂ�BBox�Ƀ��C���΂��A���������ʂ̐�����Ԃ�
		}
	}
	return -1;
}
// M.S
// �L�����̉E�ړ�����
// ��  ���F�Ȃ�
// �߂�l�F�Ȃ�     
void	CPcObj::MoveRight(){
	// �E�ړ�
	// �z�u�ł��Ȃ��z��̏���l(upper)�A�����l(lower)
	// H���s�AV����
	float upperLimitH = 10;
	float lowerLimitH = 0;
	float upperLimitV = 9;
	float lowerLimitV = -1;
	int moveValue = 1;      	// ���̐��H�ֈړ����鋗��
	int loopPlusMoveTimes = 1;  // ���[�v���Đi��ł����x��moveTimes�ɑ����ϐ�
	int lineNum = 1;            // �������H�̔z��ɂ��ꂽ����
	int stationNum = 3;         // �w�̔z��ɂ��ꂽ����
	int afterLineNum = 5;       // �������H�̒ʉߌ�ɔz��ɂ���鐔��
	int afterStationNum = 8;    // �w�̒ʉߌ�ɔz��ɂ���鐔��
	// �v���C�L�����̈ʒu���z�u�\�͈͂��ǂ���
	// �v���C�L�����̈ʒu���z�u�\�͈͂��ǂ���
	if (oldHP < upperLimitH && oldHP >= lowerLimitH && oldVP < upperLimitV && oldVP >= lowerLimitV) {
		if (trainDirectionFlag == rightArrow) {       // �v���C���[���E�����ɐi��ł��邩�ǂ���
			if (frontFlag == true) {         //�v���C���[�����ʂ̏ꍇ
				// �z��̌��ݒn�̗�+1�ɒ������H�܂��͉w���z�u����Ă��邩�ǂ���
				if (m_pGMain->m_pMapProc->lineMap1[oldHP][oldVP + moveValue] == lineNum
					|| m_pGMain->m_pMapProc->lineMap1[oldHP][oldVP + moveValue] == stationNum) {
					DoneMove = true;         // �ړ������t���O��true
					// ��̐��H�̈ړ����I����Ă��Ȃ����
					if (moveTimes < moveTimesMax) {
						mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed); // �ړ�������
						moveTimes += loopPlusMoveTimes;        // �ړ��ϐ�(moveTimes)��+1
					}
					// ��̐��H�̈ړ����I����Ă����
					else {
						// �z�u����Ă���I�u�W�F�N�g�����H�Ȃ��
						if (m_pGMain->m_pMapProc->lineMap1[oldHP][oldVP + moveValue] == lineNum) {
							// �z���afterLineNum������
							m_pGMain->m_pMapProc->lineMap1[oldHP][oldVP + moveValue] = afterLineNum;
						}
						// �z�u����Ă���I�u�W�F�N�g���w�Ȃ��
						else if (m_pGMain->m_pMapProc->lineMap1[oldHP][oldVP + moveValue] == stationNum) {
							// �z���afterStationNum������
							m_pGMain->m_pMapProc->lineMap1[oldHP][oldVP + moveValue] = afterStationNum;
						}
						oldVP += moveValue;                       // ���ݒn�̍X�V
						if (oldVP == upperLimitV) {                 // �ړ��オ�[�̈ʒu�Ȃ��
							edgeFlag = true;              // edgeFlag��true
						}
						moveTimes = 0;                    // �ړ��ϐ�(moveTimes)��0�ɏ�����
						trainDirectionFlag = rightArrow;           // �ړ��������E�ɂ���
						m_pGMain->m_pPcProc->trainStep++; // �ړ�����������
					}
				}
			}
			else if (frontFlag == false) {  //�v���C���[�����ʈȊO�̏ꍇ
				// �z��̌��ݒn�̗�+1�ɒ������H�܂��͉w���z�u����Ă��邩�ǂ���
				if (m_pGMain->m_pPcProc->lineMapSub[oldHP][oldVP + moveValue] == lineNum
					|| m_pGMain->m_pPcProc->lineMapSub[oldHP][oldVP + moveValue] == stationNum) {
					DoneMove = true;              // �ړ������t���O��true
					// ��̐��H�̈ړ����I����Ă��Ȃ����
					if (moveTimes < moveTimesMax) {
						mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed);  // �ړ�������
						moveTimes += loopPlusMoveTimes;     // �ړ��ϐ�(moveTimes)��+1
					}
					// ��̐��H�̈ړ����I����Ă����
					else {
						// �z�u����Ă���I�u�W�F�N�g�����H�Ȃ��
						if (m_pGMain->m_pPcProc->lineMapSub[oldHP][oldVP + moveValue] == lineNum) {
							// �z���afterLineNum������
							m_pGMain->m_pPcProc->lineMapSub[oldHP][oldVP + moveValue] = afterLineNum;
						}
						// �z�u����Ă���I�u�W�F�N�g���w�Ȃ��
						else if (m_pGMain->m_pPcProc->lineMapSub[oldHP][oldVP + moveValue] == stationNum) {
							// �z���afterStationNum������
							m_pGMain->m_pPcProc->lineMapSub[oldHP][oldVP + moveValue] = afterStationNum;
						}
						oldVP += moveValue;                         // ���ݒn�̍X�V
						if (oldVP == upperLimitV) {                 // �ړ��オ�[�̈ʒu�Ȃ��
							edgeFlag = true;              // edgeFlag��true
						}
						moveTimes = 0;                    // �ړ��ϐ�(moveTimes)��0�ɏ�����
						trainDirectionFlag = rightArrow;           // �ړ��������E�ɂ���
						m_pGMain->m_pPcProc->trainStep++; // �ړ�����������
					}
				}
			}
		}
	}
}
// M.S
// �L�����̍��ړ�����
// ��  ���F�Ȃ�
// �߂�l�F�Ȃ�   
void	CPcObj::MoveLeft() {
	// ���ړ�
	// �z�u�ł��Ȃ��z��̏���l(upper)�A�����l(lower)
	// H���s�AV����
	float upperLimitH = 10;
	float lowerLimitH = 0;
	float upperLimitV = 11;
	float lowerLimitV = 1;
	int moveValue = 1;      	// ���̐��H�ֈړ����鋗��
	int loopPlusMoveTimes = 1;  // ���[�v���Đi��ł����x��moveTimes�ɑ����ϐ�
	int lineNum = 1;            // �������H�̔z��ɂ��ꂽ����
	int stationNum = 3;         // �w�̔z��ɂ��ꂽ����
	int afterLineNum = 5;       // �������H�̒ʉߌ�ɔz��ɂ���鐔��
	int afterStationNum = 8;    // �w�̒ʉߌ�ɔz��ɂ���鐔��
	// �v���C�L�����̈ʒu���z�u�\�͈͂��ǂ���
	if (oldHP < upperLimitH && oldHP >= lowerLimitH && oldVP >= lowerLimitV && oldVP < upperLimitV) {
		if (trainDirectionFlag == leftArrow) {       // �v���C���[���������ɐi��ł��邩�ǂ���
			if (frontFlag == true) {   //�v���C���[�����ʂ̏ꍇ
				// �z��̌��ݒn�̗�-1�ɒ������H�܂��͉w���z�u����Ă��邩�ǂ���
				if (m_pGMain->m_pMapProc->lineMap1[oldHP][oldVP - moveValue] == lineNum
					|| m_pGMain->m_pMapProc->lineMap1[oldHP][oldVP - moveValue] == stationNum) {
					DoneMove = true;        // �ړ������t���O��true
					// ��̐��H�̈ړ����I����Ă��Ȃ����
					if (moveTimes < moveTimesMax) {
						mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed);  // �ړ�������
						moveTimes += loopPlusMoveTimes;     // �ړ��ϐ�(moveTimes)��+1
					}
					// ��̐��H�̈ړ����I����Ă����
					else {
						// �z�u����Ă���I�u�W�F�N�g�����H�Ȃ��
						if (m_pGMain->m_pMapProc->lineMap1[oldHP][oldVP - moveValue] == lineNum) {
							// �z���afterLineNum������
							m_pGMain->m_pMapProc->lineMap1[oldHP][oldVP - moveValue] = afterLineNum;
						}
						// �z�u����Ă���I�u�W�F�N�g���w�Ȃ��
						else if (m_pGMain->m_pMapProc->lineMap1[oldHP][oldVP - moveValue] == stationNum) {
							// �z���afterStationNum������
							m_pGMain->m_pMapProc->lineMap1[oldHP][oldVP - moveValue] = afterStationNum;
						}
						oldVP -= moveValue;                          // ���ݒn�̍X�V
						if (oldVP == lowerLimitH) {                    // �ړ��オ�[�̈ʒu�Ȃ��
							edgeFlag = true;                 // edgeFlag��true
						}
						moveTimes = 0;                       // �ړ��ϐ�(moveTimes)��0�ɏ�����
						trainDirectionFlag = leftArrow;      // �ړ����������ɂ���
						m_pGMain->m_pPcProc->trainStep++;    // �ړ�����������
					}
				}

			}
			else if (frontFlag == false) {  //�v���C���[�����ʈȊO�̏ꍇ
				// �z��̌��ݒn�̗�-1�ɒ������H�܂��͉w���z�u����Ă��邩�ǂ���
				if (m_pGMain->m_pPcProc->lineMapSub[oldHP][oldVP - moveValue] == lineNum
					|| m_pGMain->m_pPcProc->lineMapSub[oldHP][oldVP - moveValue] == stationNum) {
					DoneMove = true;          // �ړ������t���O��true
					// ��̐��H�̈ړ����I����Ă��Ȃ����
					if (moveTimes < moveTimesMax) {
						mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed);    // �ړ�������
						moveTimes += loopPlusMoveTimes;       // �ړ��ϐ�(moveTimes)��+1
					}
					// ��̐��H�̈ړ����I����Ă����
					else {
						// �z�u����Ă���I�u�W�F�N�g�����H�Ȃ��
						if (m_pGMain->m_pPcProc->lineMapSub[oldHP][oldVP - moveValue] == lineNum) {
							// �z���afterLineNum������
							m_pGMain->m_pPcProc->lineMapSub[oldHP][oldVP - moveValue] = afterLineNum;
						}
						// �z�u����Ă���I�u�W�F�N�g���w�Ȃ��
						else if (m_pGMain->m_pPcProc->lineMapSub[oldHP][oldVP - moveValue] == stationNum) {
							// �z���afterStationNum������
							m_pGMain->m_pPcProc->lineMapSub[oldHP][oldVP - moveValue] = afterStationNum;
						}
						oldVP -= moveValue;                 // ���ݒn�̍X�V
						if (oldVP == 0) {                   // �ړ��オ�[�̈ʒu�Ȃ��
							edgeFlag = true;                // edgeFlag��true
						}
						moveTimes = 0;                      // �ړ��ϐ�(moveTimes)��0�ɏ�����
						trainDirectionFlag = leftArrow;     // �ړ����������ɂ���
						m_pGMain->m_pPcProc->trainStep++;   // �ړ�����������
					}
				}
			}
		}
	}
}
// M.S
// �L�����̉��ړ�����
// ��  ���F�Ȃ�
// �߂�l�F�Ȃ�   
void	CPcObj::MoveDown() {
	// ���ړ�
	// �z�u�ł��Ȃ��z��̏���l(upper)�A�����l(lower)
	// H���s�AV����
	float upperLimitH = 9;
	float lowerLimitH = -1;
	float upperLimitV = 10;
	float lowerLimitV = 0;
	int moveValue = 1;      	// ���̐��H�ֈړ����鋗��
	int loopPlusMoveTimes = 1;  // ���[�v���Đi��ł����x��moveTimes�ɑ����ϐ�
	int lineNum = 1;            // �������H�̔z��ɂ��ꂽ����
	int stationNum = 3;         // �w�̔z��ɂ��ꂽ����
	int afterLineNum = 5;       // �������H�̒ʉߌ�ɔz��ɂ���鐔��
	int afterStationNum = 8;    // �w�̒ʉߌ�ɔz��ɂ���鐔��
	// �v���C�L�����̈ʒu���z�u�\�͈͂��ǂ���
	if (oldHP < upperLimitH && oldHP >= lowerLimitH && oldVP < upperLimitV && oldVP >= lowerLimitV) {
		if (trainDirectionFlag == downArrow) {       // �v���C���[���������ɐi��ł��邩�ǂ���
			if (frontFlag == true) {   //�v���C���[�����ʂ̏ꍇ
				// �z��̌��ݒn�̍s+1�ɒ������H�܂��͉w���z�u����Ă��邩�ǂ���
				if (m_pGMain->m_pMapProc->lineMap1[oldHP + moveValue][oldVP] == lineNum
					|| m_pGMain->m_pMapProc->lineMap1[oldHP + moveValue][oldVP] == stationNum) {
					DoneMove = true;   // �ړ������t���O��true
					// ��̐��H�̈ړ����I����Ă��Ȃ����
					if (moveTimes < moveTimesMax) {
						mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed);   // �ړ�������
						moveTimes += loopPlusMoveTimes;      // �ړ��ϐ�(moveTimes)��+1
					}
					// ��̐��H�̈ړ����I����Ă����
					else {
						// �z�u����Ă���I�u�W�F�N�g�����H�Ȃ��
						if (m_pGMain->m_pMapProc->lineMap1[oldHP + moveValue][oldVP] == lineNum) {
							// �z���afterLineNum������
							m_pGMain->m_pMapProc->lineMap1[oldHP + moveValue][oldVP] = afterLineNum;
						}
						// �z�u����Ă���I�u�W�F�N�g���w�Ȃ��
						else if (m_pGMain->m_pMapProc->lineMap1[oldHP + moveValue][oldVP] == stationNum) {
							// �z���afterStationNum������
							m_pGMain->m_pMapProc->lineMap1[oldHP + moveValue][oldVP] = afterStationNum;
						}
						oldHP += moveValue;                         // ���ݒn�̍X�V
						if (oldHP == upperLimitH) {                   // �ړ��オ�[�̈ʒu�Ȃ��
							edgeFlag = true;                // edgeFlag��true
						}
						moveTimes = 0;                      // �ړ��ϐ�(moveTimes)��0�ɏ�����
						trainDirectionFlag = downArrow;             // �ړ����������ɂ���
						m_pGMain->m_pPcProc->trainStep++;   // �ړ�����������
					}
				}
			}
			else if (frontFlag == false) {   //�v���C���[�����ʈȊO�̏ꍇ
				// �z��̌��ݒn�̗�-1�ɒ������H�܂��͉w���z�u����Ă��邩�ǂ���
				if (m_pGMain->m_pPcProc->lineMapSub[oldHP + moveValue][oldVP] == lineNum
					|| m_pGMain->m_pPcProc->lineMapSub[oldHP + moveValue][oldVP] == stationNum) {
					DoneMove = true;        // �ړ������t���O��true
					// ��̐��H�̈ړ����I����Ă��Ȃ����
					if (moveTimes < moveTimesMax) {
						mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed);   // �ړ�������
						moveTimes += loopPlusMoveTimes;     // �ړ��ϐ�(moveTimes)��+1
					}
					// ��̐��H�̈ړ����I����Ă����
					else {
						// �z�u����Ă���I�u�W�F�N�g�����H�Ȃ��
						if (m_pGMain->m_pPcProc->lineMapSub[oldHP + moveValue][oldVP] == lineNum) {
							// �z���afterLineNum������
							m_pGMain->m_pPcProc->lineMapSub[oldHP + moveValue][oldVP] = afterLineNum;
						}
						// �z�u����Ă���I�u�W�F�N�g���w�Ȃ��
						else if (m_pGMain->m_pPcProc->lineMapSub[oldHP + moveValue][oldVP] == stationNum) {
							// �z���afterStationNum������
							m_pGMain->m_pPcProc->lineMapSub[oldHP + moveValue][oldVP] = afterStationNum;
						}
						oldHP += moveValue;                        // ���ݒn�̍X�V
						if (oldHP == upperLimitH) {                  // �ړ��オ�[�̈ʒu�Ȃ��
							edgeFlag = true;               // edgeFlag��true
						}
						moveTimes = 0;                     // �ړ��ϐ�(moveTimes)��0�ɏ�����
						trainDirectionFlag = downArrow;            // �ړ����������ɂ���
						m_pGMain->m_pPcProc->trainStep++;  // �ړ�����������
					}
				}
			}
		}
	}
}
// M.S
// �L�����̏�ړ�����
// ��  ���F�Ȃ�
// �߂�l�F�Ȃ�   
void	CPcObj::MoveUp() {
	//	��ړ�
	// �z�u�ł��Ȃ��z��̏���l(upper)�A�����l(lower)
	// H���s�AV����
	float upperLimitH = 11;
	float lowerLimitH = 1;
	float upperLimitV = 10;
	float lowerLimitV = 0;
	int moveValue = 1;      	// ���̐��H�ֈړ����鋗��
	int loopPlusMoveTimes = 1;  // ���[�v���Đi��ł����x��moveTimes�ɑ����ϐ�
	int lineNum = 1;            // �������H�̔z��ɂ��ꂽ����
	int stationNum = 3;         // �w�̔z��ɂ��ꂽ����
	int afterLineNum = 5;       // �������H�̒ʉߌ�ɔz��ɂ���鐔��
	int afterStationNum = 8;    // �w�̒ʉߌ�ɔz��ɂ���鐔��
	// �v���C�L�����̈ʒu���z�u�\�͈͂��ǂ���
	if (oldHP < upperLimitH && oldHP >= lowerLimitH && oldVP < upperLimitV && oldVP >= lowerLimitV) {
		if (trainDirectionFlag == upArrow) {       // �v���C���[��������ɐi��ł��邩�ǂ���
			if (frontFlag == true) {    //�v���C���[�����ʂ̏ꍇ
				// �z��̌��ݒn�̍s-1�ɒ������H�܂��͉w���z�u����Ă��邩�ǂ���
				if (m_pGMain->m_pMapProc->lineMap1[oldHP - moveValue][oldVP] == lineNum
					|| m_pGMain->m_pMapProc->lineMap1[oldHP - moveValue][oldVP] == stationNum) {
					DoneMove = true;     // �ړ������t���O��true
					// ��̐��H�̈ړ����I����Ă��Ȃ����
					if (moveTimes < moveTimesMax) {
						mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed);    // �ړ�������
						moveTimes += loopPlusMoveTimes;       // �ړ��ϐ�(moveTimes)��+1     
					}
					// ��̐��H�̈ړ����I����Ă����
					else {
						// �z�u����Ă���I�u�W�F�N�g�����H�Ȃ��
						if (m_pGMain->m_pMapProc->lineMap1[oldHP - moveValue][oldVP] == lineNum) {
							// �z���afterLineNum������
							m_pGMain->m_pMapProc->lineMap1[oldHP - moveValue][oldVP] = afterLineNum;
						}
						// �z�u����Ă���I�u�W�F�N�g���w�Ȃ��
						else if (m_pGMain->m_pMapProc->lineMap1[oldHP - moveValue][oldVP] == stationNum) {
							// �z���afterStationNum������
							m_pGMain->m_pMapProc->lineMap1[oldHP - moveValue][oldVP] = afterStationNum;
						}
						oldHP -= moveValue;                          // ���ݒn�̍X�V
						if (oldHP == lowerLimitV) {          // �ړ��オ�[�̈ʒu�Ȃ��
							edgeFlag = true;                 // edgeFlag��true
						}
						moveTimes = 0;                       // �ړ��ϐ�(moveTimes)��0�ɏ�����
						trainDirectionFlag = upArrow;              // �ړ����������ɂ���
						m_pGMain->m_pPcProc->trainStep++;    // �ړ�����������
					}
				}
			}
			else if (frontFlag == false) {  //�v���C���[�����ʈȊO�̏ꍇ
				// �z��̌��ݒn�̗�-1�ɒ������H�܂��͉w���z�u����Ă��邩�ǂ���
				if (m_pGMain->m_pPcProc->lineMapSub[oldHP - moveValue][oldVP] == lineNum
					|| m_pGMain->m_pPcProc->lineMapSub[oldHP - moveValue][oldVP] == stationNum) {
					DoneMove = true;           // �ړ������t���O��true
					// ��̐��H�̈ړ����I����Ă��Ȃ����
					if (moveTimes < moveTimesMax) {
						mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed);   // �ړ�������
						moveTimes += loopPlusMoveTimes;      // �ړ��ϐ�(moveTimes)��+1   
					}
					// ��̐��H�̈ړ����I����Ă����
					else {
						// �z�u����Ă���I�u�W�F�N�g�����H�Ȃ��
						if (m_pGMain->m_pPcProc->lineMapSub[oldHP - moveValue][oldVP] == lineNum) {
							// �z���afterLineNum������
							m_pGMain->m_pPcProc->lineMapSub[oldHP - moveValue][oldVP] = afterLineNum;
						}
						// �z�u����Ă���I�u�W�F�N�g���w�Ȃ��
						else if (m_pGMain->m_pPcProc->lineMapSub[oldHP - moveValue][oldVP] == stationNum) {
							// �z���afterStationNum������
							m_pGMain->m_pPcProc->lineMapSub[oldHP - moveValue][oldVP] = afterStationNum;
						}
						oldHP -= moveValue;                        // ���ݒn�̍X�V
						if (oldHP == lowerLimitV) {        // �ړ��オ�[�̈ʒu�Ȃ��
							edgeFlag = true;               // edgeFlag��true
						}
						moveTimes = 0;                     // �ړ��ϐ�(moveTimes)��0�ɏ�����
						trainDirectionFlag = upArrow;            // �ړ����������ɂ���
						m_pGMain->m_pPcProc->trainStep++;  // �ړ�����������
					}
				}
			}
		}
	}
}
// M.S
// �L�����̏ォ��E�ړ��̕ϐ��̃Z�b�g
// ��  ���F�Ȃ�
// �߂�l�F�Ȃ�   
void	CPcObj::SetUpRightChangeLineValue() {
	// �z�u�ł��Ȃ��z��̏���l(upper)�A�����l(lower)(H���s�AV����)
	lowerLimitH = 0;
	upperLimitV = 10;
	// ���H�z�u��̔z��̈ʒu
	// H�͍s�AV�͗�ANear�����Ă���̂̓v���C�L��������߂��}�X�A���Ă��Ȃ��̂͗���Ă���}�X
	chPlacementNearH = oldHP - 1;
	chPlacementH = oldHP - 2;
	chPlacementNearV = oldVP;
	chPlacementV = oldVP + 1;
	edgePos = 9;                             // �v���C�L�������[�ɂ���Ƃ��̔z��̒l
	rotateChar = 90.0f;                      // �����؂�ւ����H�̃v���C�L�����̉�]�ϐ�
	moveValueH = 2;      	                   // ���̐��H�܂ł̈ړ����鋗��(�s)
	moveValueV = 1;      	                   // ���̐��H�܂ł̈ړ����鋗��(��)
	loopPlusMoveTimes = 1;                     // ���[�v���Đi��ł����x��moveTimes�ɑ����ϐ�
	changeLineNum = 2;                         // �����؂�ւ����H�̔z��ɂ��ꂽ����
	afterChangeLineNum = 6;                    // �����؂�ւ����H�̒ʉߌ�ɔz��ɂ���鐔��
	chLineMoveTimesMax = moveTimesMax * 2;   // �ŏ��ɂ܂������i�ދ�����2�}�X���Ȃ̂�moveTimesMax * 2
}
// M.S
// �L�����̏ォ�獶�ړ��̕ϐ��̃Z�b�g
// ��  ���F�Ȃ�
// �߂�l�F�Ȃ�  
void	CPcObj::SetUpLeftChangeLineValue() {
	// �z�u�ł��Ȃ��z��̏���l(upper)�A�����l(lower)(H���s�AV����)
	lowerLimitH = 0;
	lowerLimitV = 0;
	// ���H�z�u��̔z��̈ʒu
	// H�͍s�AV�͗�ANear�����Ă���̂̓v���C�L��������߂��}�X�A���Ă��Ȃ��̂͗���Ă���}�X
	chPlacementNearH = oldHP - 1;
	chPlacementH = oldHP - 2;
	chPlacementNearV = oldVP;
	chPlacementV = oldVP - 1;
	edgePos = 0;                             // �v���C�L�������[�ɂ���Ƃ��̔z��̒l
	rotateChar = 90.0f;                      // �����؂�ւ����H�̃v���C�L�����̉�]�ϐ�
	moveValueH = 2;      	                   // ���̐��H�܂ł̈ړ����鋗��(�s)
	moveValueV = 1;      	                   // ���̐��H�܂ł̈ړ����鋗��(��)
	loopPlusMoveTimes = 1;                     // ���[�v���Đi��ł����x��moveTimes�ɑ����ϐ�
	changeLineNum = 2;                         // �����؂�ւ����H�̔z��ɂ��ꂽ����
	afterChangeLineNum = 6;                    // �����؂�ւ����H�̒ʉߌ�ɔz��ɂ���鐔��
	chLineMoveTimesMax = moveTimesMax * 2;   // �ŏ��ɂ܂������i�ދ�����2�}�X���Ȃ̂�moveTimesMax * 2
}
// M.S
// �L�����̉�����E�ړ��̕ϐ��̃Z�b�g
// ��  ���F�Ȃ�
// �߂�l�F�Ȃ�  
void	CPcObj::SetDownRightChangeLineValue() {
	// �z�u�ł��Ȃ��z��̏���l(upper)�A�����l(lower)(H���s�AV����)
	upperLimitH = 10;
	upperLimitV = 10;
	// ���H�z�u��̔z��̈ʒu
	// H�͍s�AV�͗�ANear�����Ă���̂̓v���C�L��������߂��}�X�A���Ă��Ȃ��̂͗���Ă���}�X
	chPlacementNearH = oldHP + 1;
	chPlacementH = oldHP + 2;
	chPlacementNearV = oldVP;
	chPlacementV = oldVP + 1;
	edgePos = 9;                             // �v���C�L�������[�ɂ���Ƃ��̔z��̒l
	rotateChar = 90.0f;                      // �����؂�ւ����H�̃v���C�L�����̉�]�ϐ�                
	moveValueH = 2;      	                   // ���̐��H�܂ł̈ړ����鋗��(�s)
	moveValueV = 1;      	                   // ���̐��H�܂ł̈ړ����鋗��(��)
	loopPlusMoveTimes = 1;                     // ���[�v���Đi��ł����x��moveTimes�ɑ����ϐ�
	changeLineNum = 2;                         // �����؂�ւ����H�̔z��ɂ��ꂽ����
	afterChangeLineNum = 6;                    // �����؂�ւ����H�̒ʉߌ�ɔz��ɂ���鐔��
	chLineMoveTimesMax = moveTimesMax * 2;   // �ŏ��ɂ܂������i�ދ�����2�}�X���Ȃ̂�moveTimesMax * 2
}
// M.S
// �L�����̉����獶�ړ��̕ϐ��̃Z�b�g
// ��  ���F�Ȃ�
// �߂�l�F�Ȃ�  
void	CPcObj::SetDownLeftChangeLineValue() {
	// �z�u�ł��Ȃ��z��̏���l(upper)�A�����l(lower)(H���s�AV����)
	upperLimitH = 10;
	lowerLimitV = 0;
	// ���H�z�u��̔z��̈ʒu
	// H�͍s�AV�͗�ANear�����Ă���̂̓v���C�L��������߂��}�X�A���Ă��Ȃ��̂͗���Ă���}�X
	chPlacementNearH = oldHP + 1;
	chPlacementH = oldHP + 2;
	chPlacementNearV = oldVP;
	chPlacementV = oldVP - 1;
	edgePos = 0;                             // �v���C�L�������[�ɂ���Ƃ��̔z��̒l
	rotateChar = 90.0f;                      // �����؂�ւ����H�̃v���C�L�����̉�]�ϐ�
	moveValueH = 2;      	                   // ���̐��H�܂ł̈ړ����鋗��(�s)
	moveValueV = 1;      	                   // ���̐��H�܂ł̈ړ����鋗��(��)
	loopPlusMoveTimes = 1;                     // ���[�v���Đi��ł����x��moveTimes�ɑ����ϐ�
	changeLineNum = 2;                         // �����؂�ւ����H�̔z��ɂ��ꂽ����
	afterChangeLineNum = 6;                    // �����؂�ւ����H�̒ʉߌ�ɔz��ɂ���鐔��
	chLineMoveTimesMax = moveTimesMax * 2;   // �ŏ��ɂ܂������i�ދ�����2�}�X���Ȃ̂�moveTimesMax * 2
}
// M.S
// �L�����̉E�����ړ��̕ϐ��̃Z�b�g
// ��  ���F�Ȃ�
// �߂�l�F�Ȃ�  
void	CPcObj::SetRightUpChangeLineValue() {
	// �z�u�ł��Ȃ��z��̏���l(upper)�A�����l(lower)(H���s�AV����)
	upperLimitH = 10;
	lowerLimitV = 0;
	// ���H�z�u��̔z��̈ʒu
	// H�͍s�AV�͗�ANear�����Ă���̂̓v���C�L��������߂��}�X�A���Ă��Ȃ��̂͗���Ă���}�X
	chPlacementNearH = oldHP;
	chPlacementH = oldHP - 1;
	chPlacementNearV = oldVP + 1;
	chPlacementV = oldVP + 2;
	edgePos = 0;                             // �v���C�L�������[�ɂ���Ƃ��̔z��̒l
	rotateChar = 90.0f;                      // �����؂�ւ����H�̃v���C�L�����̉�]�ϐ�
	moveValueH = 1;      	                   // ���̐��H�܂ł̈ړ����鋗��(�s)
	moveValueV = 2;      	                   // ���̐��H�܂ł̈ړ����鋗��(��)
	loopPlusMoveTimes = 1;                     // ���[�v���Đi��ł����x��moveTimes�ɑ����ϐ�
	changeLineNum = 2;                         // �����؂�ւ����H�̔z��ɂ��ꂽ����
	afterChangeLineNum = 6;                    // �����؂�ւ����H�̒ʉߌ�ɔz��ɂ���鐔��
	chLineMoveTimesMax = moveTimesMax * 2;   // �ŏ��ɂ܂������i�ދ�����2�}�X���Ȃ̂�moveTimesMax * 2
}
// M.S
// �L�����̉E���牺�ړ��̕ϐ��̃Z�b�g
// ��  ���F�Ȃ�
// �߂�l�F�Ȃ�  
void	CPcObj::SetRightDownChangeLineValue() {
	// �z�u�ł��Ȃ��z��̏���l(upper)�A�����l(lower)(H���s�AV����)
	upperLimitH = 10;
	upperLimitV = 10;
	// ���H�z�u��̔z��̈ʒu
	// H�͍s�AV�͗�ANear�����Ă���̂̓v���C�L��������߂��}�X�A���Ă��Ȃ��̂͗���Ă���}�X
	chPlacementNearH = oldHP;
	chPlacementH = oldHP + 1;
	chPlacementNearV = oldVP + 1;
	chPlacementV = oldVP + 2;
	edgePos = 9;                             // �v���C�L�������[�ɂ���Ƃ��̔z��̒l
	rotateChar = 90.0f;                      // �����؂�ւ����H�̃v���C�L�����̉�]�ϐ�
	moveValueH = 1;      	                   // ���̐��H�܂ł̈ړ����鋗��(�s)
	moveValueV = 2;      	                   // ���̐��H�܂ł̈ړ����鋗��(��)
	loopPlusMoveTimes = 1;                     // ���[�v���Đi��ł����x��moveTimes�ɑ����ϐ�
	changeLineNum = 2;                         // �����؂�ւ����H�̔z��ɂ��ꂽ����
	afterChangeLineNum = 6;                    // �����؂�ւ����H�̒ʉߌ�ɔz��ɂ���鐔��
	chLineMoveTimesMax = moveTimesMax * 2;   // �ŏ��ɂ܂������i�ދ�����2�}�X���Ȃ̂�moveTimesMax * 2
}
// M.S
// �L�����̍������ړ��̕ϐ��̃Z�b�g
// ��  ���F�Ȃ�
// �߂�l�F�Ȃ�  
void	CPcObj::SetLeftUpChangeLineValue() {
	// �z�u�ł��Ȃ��z��̏���l(upper)�A�����l(lower)(H���s�AV����)
	lowerLimitH = 0;
	lowerLimitV = 0;
	// ���H�z�u��̔z��̈ʒu
	// H�͍s�AV�͗�ANear�����Ă���̂̓v���C�L��������߂��}�X�A���Ă��Ȃ��̂͗���Ă���}�X
	chPlacementNearH = oldHP;
	chPlacementH = oldHP - 1;
	chPlacementNearV = oldVP - 1;
	chPlacementV = oldVP - 2;
	edgePos = 0;                             // �v���C�L�������[�ɂ���Ƃ��̔z��̒l
	rotateChar = 90.0f;                      // �����؂�ւ����H�̃v���C�L�����̉�]�ϐ�
	moveValueH = 1;      	                   // ���̐��H�܂ł̈ړ����鋗��(�s)
	moveValueV = 2;      	                   // ���̐��H�܂ł̈ړ����鋗��(��)
	loopPlusMoveTimes = 1;                     // ���[�v���Đi��ł����x��moveTimes�ɑ����ϐ�
	changeLineNum = 2;                         // �����؂�ւ����H�̔z��ɂ��ꂽ����
	afterChangeLineNum = 6;                    // �����؂�ւ����H�̒ʉߌ�ɔz��ɂ���鐔��
	chLineMoveTimesMax = moveTimesMax * 2;   // �ŏ��ɂ܂������i�ދ�����2�}�X���Ȃ̂�moveTimesMax * 2
}
// M.S
// �L�����̍����牺�ړ��̕ϐ��̃Z�b�g
// ��  ���F�Ȃ�
// �߂�l�F�Ȃ�  
void	CPcObj::SetLeftDownChangeLineValue() {
	// �z�u�ł��Ȃ��z��̏���l(upper)�A�����l(lower)(H���s�AV����)
	upperLimitH = 10;
	lowerLimitV = 0;
	// ���H�z�u��̔z��̈ʒu
	// H�͍s�AV�͗�ANear�����Ă���̂̓v���C�L��������߂��}�X�A���Ă��Ȃ��̂͗���Ă���}�X
	chPlacementNearH = oldHP;
	chPlacementH = oldHP + 1;
	chPlacementNearV = oldVP - 1;
	chPlacementV = oldVP - 2;
	edgePos = 9;                             // �v���C�L�������[�ɂ���Ƃ��̔z��̒l
	rotateChar = 90.0f;
	moveValueH = 1;      	                   // ���̐��H�܂ł̈ړ����鋗��(�s)
	moveValueV = 2;      	                   // ���̐��H�܂ł̈ړ����鋗��(��)
	loopPlusMoveTimes = 1;                     // ���[�v���Đi��ł����x��moveTimes�ɑ����ϐ�
	changeLineNum = 2;                         // �����؂�ւ����H�̔z��ɂ��ꂽ����
	afterChangeLineNum = 6;                    // �����؂�ւ����H�̒ʉߌ�ɔz��ɂ���鐔��
	chLineMoveTimesMax = moveTimesMax * 2;   // �ŏ��ɂ܂������i�ދ�����2�}�X���Ȃ̂�moveTimesMax * 2
}
// M.S
// �L�����̕����؂�ւ����H�ړ�����(�ォ��E�ړ�)
// ��  ���F�Ȃ�
// �߂�l�F�Ȃ�   
void	CPcObj::MoveUpRight() {
	SetUpRightChangeLineValue();     // �ϐ��̒l���Z�b�g
	// �v���C�L�����̈ʒu���z�u�\�͈͂��ǂ���
	if (chPlacementH >= lowerLimitH && chPlacementV < upperLimitV) {
		if (trainDirectionFlag == upArrow) {       // �v���C���[��������ɐi��ł��邩�ǂ���
			if (frontFlag == true) {   //�v���C���[�����ʂ̏ꍇ
				if (m_pGMain->m_pMapProc->lineMap1[chPlacementNearH][chPlacementNearV] == changeLineNum &&
					m_pGMain->m_pMapProc->lineMap1[chPlacementH][chPlacementNearV] == changeLineNum &&
					m_pGMain->m_pMapProc->lineMap1[chPlacementNearH][chPlacementV] == changeLineNum &&
					m_pGMain->m_pMapProc->lineMap1[chPlacementH][chPlacementV] == changeLineNum) {
					DoneMove = true;            // �ړ������t���O��true
					// changeStepNum�Ńt�F�[�Y���ƂɈړ���������
					switch (changeStepNum) {
						// �t�F�[�Y0�F2�}�X���̒����ړ�
					case 0: // �ړ�
						if (moveTimes < chLineMoveTimesMax) {                        // �Q�}�X�ړ�
							mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed);        // �O�Ɉړ�
							moveTimes += loopPlusMoveTimes;                          // �񐔂𑫂�
						}
						else {
							moveTimes = 0;                                           // ���ݒn�̍X�V
							changeStepNum++;                                         // ���̈ړ����s��
						}
						break;
						// �t�F�[�Y1�F�v���C�L�����̉�]
					case 1:  //��]
						m_fLocalRotY += rotateChar;
						changeStepNum++;                                             //���̈ړ����s��
						break;
					case 2:
						// �t�F�[�Y2�F��]���1�}�X���̒����ړ�
						if (moveTimes < moveTimesMax) {                              // 1�}�X�ړ�
							mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed);        // �O�Ɉړ�
							moveTimes += loopPlusMoveTimes;                          // �񐔂𑫂�
						}
						else {
							moveTimes = 0;
							trainDirectionFlag = rightArrow;  // �d�Ԃ̐i��ł�������̃Z�b�g
							// �ړ��������ߔz��̐��l�ύX(�����ϊ��X�C�b�`��6)
							m_pGMain->m_pMapProc->lineMap1[chPlacementNearH][chPlacementNearV] = afterChangeLineNum;
							m_pGMain->m_pMapProc->lineMap1[chPlacementH][chPlacementNearV] = afterChangeLineNum;
							m_pGMain->m_pMapProc->lineMap1[chPlacementNearH][chPlacementV] = afterChangeLineNum;
							m_pGMain->m_pMapProc->lineMap1[chPlacementH][chPlacementV] = afterChangeLineNum;
							oldHP -= moveValueH;                                        // ���ݒn�̍X�V
							oldVP += moveValueV;
							m_pGMain->m_pPcProc->trainStep += moveValueH + moveValueV;  // �ړ������𑫂�
							if (oldVP == edgePos) {
								edgeFlag = true;
							}
							changeStepNum = 0;                          // ���̈ړ��̂��߂�changeStepNum��0�ɖ߂�
							break;
						}
					}
				}
			}
			else if (frontFlag == false) {   // ���ʈȊO
				if (m_pGMain->m_pPcProc->lineMapSub[chPlacementNearH][chPlacementNearV] == changeLineNum &&
					m_pGMain->m_pPcProc->lineMapSub[chPlacementH][chPlacementNearV] == changeLineNum &&
					m_pGMain->m_pPcProc->lineMapSub[chPlacementNearH][chPlacementV] == changeLineNum &&
					m_pGMain->m_pPcProc->lineMapSub[chPlacementH][chPlacementV] == changeLineNum) {
					DoneMove = true;
					switch (changeStepNum) {
					case 0: // �ړ�
						if (moveTimes < chLineMoveTimesMax) {                        // �Q�}�X�ړ�
							mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed);        // �O�Ɉړ�
							moveTimes += loopPlusMoveTimes;                          // �񐔂𑫂�
						}
						else {
							moveTimes = 0;
							//oldHP -= 2;                                            // ���ݒn�̍X�V
							changeStepNum++;                                         // ���̈ړ����s��
						}
						break;
					case 1:  //��]
						m_fLocalRotY += rotateChar;
						changeStepNum++;                                             //���̈ړ����s��
						break;
					case 2:
						if (moveTimes < moveTimesMax) {                              // 1�}�X�ړ�
							mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed);        // �O�Ɉړ�
							moveTimes += loopPlusMoveTimes;                          // �񐔂𑫂�
						}
						else {
							moveTimes = 0;
							trainDirectionFlag = rightArrow;   // �d�Ԃ̐i��ł�������̃Z�b�g
							// �ړ��������ߔz��̐��l�ύX(�����ϊ��X�C�b�`��6)
							m_pGMain->m_pPcProc->lineMapSub[chPlacementNearH][chPlacementNearV] = afterChangeLineNum;
							m_pGMain->m_pPcProc->lineMapSub[chPlacementH][chPlacementNearV] = afterChangeLineNum;
							m_pGMain->m_pPcProc->lineMapSub[chPlacementH][chPlacementV] = afterChangeLineNum;
							m_pGMain->m_pPcProc->lineMapSub[chPlacementNearH][chPlacementV] = afterChangeLineNum;
							oldHP -= moveValueH;                                        // ���ݒn�̍X�V
							oldVP += moveValueV;
							m_pGMain->m_pPcProc->trainStep += moveValueH + moveValueV;  // �ړ������𑫂�
							if (oldVP == edgePos) {
								edgeFlag = true;
							}
							changeStepNum = 0;                 // ���̈ړ��̂��߂�changeStepNum��0�ɖ߂�
							break;
						}
					}
				}
			}
		}
	}
}
// M.S
// �L�����̕����؂�ւ����H�ړ�����(�ォ�獶�ړ�)
// ��  ���F�Ȃ�
// �߂�l�F�Ȃ� 
void	CPcObj::MoveUpLeft() {
	SetUpLeftChangeLineValue();     // �ϐ��̒l���Z�b�g
	if (chPlacementH >= lowerLimitH && chPlacementV >= lowerLimitV) {
		if (trainDirectionFlag == upArrow) {       // �v���C���[��������ɐi��ł��邩�ǂ���
			if (frontFlag == true) {   //�v���C���[�����ʂ̏ꍇ
				if (m_pGMain->m_pMapProc->lineMap1[chPlacementNearH][chPlacementV] == changeLineNum &&
					m_pGMain->m_pMapProc->lineMap1[chPlacementH][chPlacementV] == changeLineNum &&
					m_pGMain->m_pMapProc->lineMap1[chPlacementNearH][chPlacementNearV] == changeLineNum &&
					m_pGMain->m_pMapProc->lineMap1[chPlacementH][chPlacementNearV] == changeLineNum) {
					DoneMove = true;
					switch (changeStepNum) {
					case 0: // �ړ�
						if (moveTimes < chLineMoveTimesMax) {                       // �Q�}�X�ړ�
							mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed);       // �O�Ɉړ�
							moveTimes += loopPlusMoveTimes;                         // �񐔂𑫂�
						}
						else {
							moveTimes = 0;
							changeStepNum++;                                        // ���̈ړ����s��
						}
						break;
					case 1:  //��]
						m_fLocalRotY -= rotateChar;
						changeStepNum++;                                            //���̈ړ����s��
						break;
					case 2:
						if (moveTimes < moveTimesMax) {                             // 1�}�X�ړ�
							mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed);       // �O�Ɉړ�
							moveTimes += loopPlusMoveTimes;                         // �񐔂𑫂�
						}
						else {
							moveTimes = 0;
							trainDirectionFlag = leftArrow;  // �d�Ԃ̐i��ł�������̃Z�b�g
							// �ړ��������ߔz��̐��l�ύX(�����ϊ��X�C�b�`��6)
							m_pGMain->m_pMapProc->lineMap1[chPlacementNearH][chPlacementV] = afterChangeLineNum;
							m_pGMain->m_pMapProc->lineMap1[chPlacementH][chPlacementV] = afterChangeLineNum;
							m_pGMain->m_pMapProc->lineMap1[chPlacementNearH][chPlacementNearV] = afterChangeLineNum;
							m_pGMain->m_pMapProc->lineMap1[chPlacementH][chPlacementNearV] = afterChangeLineNum;
							oldHP -= moveValueH;                                         // ���ݒn�̍X�V
							oldVP -= moveValueV;
							m_pGMain->m_pPcProc->trainStep += moveValueH + moveValueV;   // �ړ������𑫂�
							if (oldVP == edgePos) {
								edgeFlag = true;
							}
							changeStepNum = 0;                 // ���̈ړ��̂��߂�changeStepNum��0�ɖ߂�
							break;
						}
					}
				}
			}
			else if (frontFlag == false) {   // ���ʈȊO
				if (m_pGMain->m_pPcProc->lineMapSub[chPlacementNearH][chPlacementV] == changeLineNum &&
					m_pGMain->m_pPcProc->lineMapSub[chPlacementH][chPlacementV] == changeLineNum &&
					m_pGMain->m_pPcProc->lineMapSub[chPlacementNearH][oldVP] == changeLineNum &&
					m_pGMain->m_pPcProc->lineMapSub[chPlacementH][oldVP] == changeLineNum) {
					DoneMove = true;
					switch (changeStepNum) {
					case 0: // �ړ�
						if (moveTimes < moveTimesMax * 2) {                         // �Q�}�X�ړ�
							mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed);       // �O�Ɉړ�
							moveTimes += loopPlusMoveTimes;                         // �񐔂𑫂�
						}
						else {
							moveTimes = 0;
							changeStepNum++;                                        // ���̈ړ����s��
						}
						break;
					case 1:  //��]
						m_fLocalRotY -= rotateChar;
						changeStepNum++;                                            //���̈ړ����s��
						break;
					case 2:
						if (moveTimes < moveTimesMax) {                             // 1�}�X�ړ�
							mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed);       // �O�Ɉړ�
							moveTimes += loopPlusMoveTimes;                         // �񐔂𑫂�
						}
						else {
							moveTimes = 0;
							trainDirectionFlag = leftArrow;  // �d�Ԃ̐i��ł�������̃Z�b�g
							// �ړ��������ߔz��̐��l�ύX(�����ϊ��X�C�b�`��6)
							m_pGMain->m_pPcProc->lineMapSub[chPlacementNearH][chPlacementV] = afterChangeLineNum;
							m_pGMain->m_pPcProc->lineMapSub[chPlacementH][chPlacementV] = afterChangeLineNum;
							m_pGMain->m_pPcProc->lineMapSub[chPlacementNearH][oldVP] = afterChangeLineNum;
							m_pGMain->m_pPcProc->lineMapSub[chPlacementH][oldVP] = afterChangeLineNum;
							oldHP -= moveValueH;                                         // ���ݒn�̍X�V
							oldVP -= moveValueV;
							m_pGMain->m_pPcProc->trainStep += moveValueH + moveValueV;   // �ړ������𑫂�
							if (oldVP == edgePos) {
								edgeFlag = true;
							}
							changeStepNum = 0;                  // ���̈ړ��̂��߂�changeStepNum��0�ɖ߂�
							break;
						}
					}
				}
			}
		}
	}
}
// M.S
// �L�����̕����؂�ւ����H�ړ�����(������E�ړ�)
// ��  ���F�Ȃ�
// �߂�l�F�Ȃ� 
void	CPcObj::MoveDownRight() {
	SetDownRightChangeLineValue();     // �ϐ��̒l���Z�b�g
	if (chPlacementH < upperLimitH && chPlacementV < upperLimitV) {
		if (trainDirectionFlag == downArrow) {       // �v���C���[���������ɐi��ł��邩�ǂ���
			if (frontFlag == true) {   //�v���C���[�����ʂ̏ꍇ
				if (m_pGMain->m_pMapProc->lineMap1[chPlacementNearH][chPlacementNearV] == changeLineNum &&
					m_pGMain->m_pMapProc->lineMap1[chPlacementH][chPlacementNearV] == changeLineNum &&
					m_pGMain->m_pMapProc->lineMap1[chPlacementNearH][chPlacementV] == changeLineNum &&
					m_pGMain->m_pMapProc->lineMap1[chPlacementH][chPlacementV] == changeLineNum) {
					DoneMove = true;
					switch (changeStepNum) {
					case 0: // �ړ�
						if (moveTimes < chLineMoveTimesMax) {                       // �Q�}�X�ړ�
							mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed);       // �O�Ɉړ�
							moveTimes += loopPlusMoveTimes;                         // �񐔂𑫂�
						}
						else {
							moveTimes = 0;
							changeStepNum++;                                        // ���̈ړ����s��
						}
						break;
					case 1:  //��]
						m_fLocalRotY -= rotateChar;
						changeStepNum++;                                            //���̈ړ����s��
						break;
					case 2:
						if (moveTimes < moveTimesMax) {                             // 1�}�X�ړ�
							mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed);       // �O�Ɉړ�
							moveTimes += loopPlusMoveTimes;                         // �񐔂𑫂�
						}
						else {
							moveTimes = 0;
							trainDirectionFlag = rightArrow;  // �d�Ԃ̐i��ł�������̃Z�b�g
							// �ړ��������ߔz��̐��l�ύX(�����ϊ��X�C�b�`��6)
							m_pGMain->m_pMapProc->lineMap1[chPlacementNearH][chPlacementNearV] = afterChangeLineNum;
							m_pGMain->m_pMapProc->lineMap1[chPlacementH][chPlacementNearV] = afterChangeLineNum;
							m_pGMain->m_pMapProc->lineMap1[chPlacementNearH][chPlacementV] = afterChangeLineNum;
							m_pGMain->m_pMapProc->lineMap1[chPlacementH][chPlacementV] = afterChangeLineNum;
							oldHP += moveValueH;                                       // ���ݒn�̍X�V
							oldVP += moveValueV;
							m_pGMain->m_pPcProc->trainStep += moveValueH + moveValueV; // �ړ������𑫂�
							if (oldVP == edgePos) {
								edgeFlag = true;
							}
							changeStepNum = 0;                   // ���̈ړ��̂��߂�changeStepNum��0�ɖ߂�
							break;
						}
					}
				}
			}
			else if (frontFlag == false) {   // ���ʈȊO
				if (m_pGMain->m_pPcProc->lineMapSub[chPlacementNearH][chPlacementNearV] == changeLineNum &&
					m_pGMain->m_pPcProc->lineMapSub[chPlacementH][chPlacementNearV] == changeLineNum &&
					m_pGMain->m_pPcProc->lineMapSub[chPlacementNearH][chPlacementV] == changeLineNum &&
					m_pGMain->m_pPcProc->lineMapSub[chPlacementH][chPlacementV] == changeLineNum) {
					DoneMove = true;
					switch (changeStepNum) {
					case 0: // �ړ�
						if (moveTimes < chLineMoveTimesMax) {                       // �Q�}�X�ړ�
							mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed);       // �O�Ɉړ�
							moveTimes += loopPlusMoveTimes;                         // �񐔂𑫂�
						}
						else {
							moveTimes = 0;
							changeStepNum++;                                        // ���̈ړ����s��
						}
						break;
					case 1:  //��]
						m_fLocalRotY -= rotateChar;
						changeStepNum++;                                            //���̈ړ����s��
						break;
					case 2:
						if (moveTimes < moveTimesMax) {                             // 1�}�X�ړ�
							mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed);       // �O�Ɉړ�
							moveTimes += loopPlusMoveTimes;                         // �񐔂𑫂�
						}
						else {
							moveTimes = 0;
							trainDirectionFlag = rightArrow;   // �d�Ԃ̐i��ł�������̃Z�b�g
							// �ړ��������ߔz��̐��l�ύX(�����ϊ��X�C�b�`��6)
							m_pGMain->m_pPcProc->lineMapSub[chPlacementNearH][chPlacementNearV] = afterChangeLineNum;
							m_pGMain->m_pPcProc->lineMapSub[chPlacementH][chPlacementNearV] = afterChangeLineNum;
							m_pGMain->m_pPcProc->lineMapSub[chPlacementNearH][chPlacementV] = afterChangeLineNum;
							m_pGMain->m_pPcProc->lineMapSub[chPlacementH][chPlacementV] = afterChangeLineNum;
							oldHP += moveValueH;                                         // ���ݒn�̍X�V
							oldVP += moveValueV;
							m_pGMain->m_pPcProc->trainStep += moveValueH + moveValueV;   // �ړ������𑫂�
							if (oldVP == edgePos) {
								edgeFlag = true;
							}
							changeStepNum = 0;                // ���̈ړ��̂��߂�changeStepNum��0�ɖ߂�
							break;
						}
					}
				}
			}
		}
	}
}
// M.S
// �L�����̕����؂�ւ����H�ړ�����(�����獶�ړ�)
// ��  ���F�Ȃ�
// �߂�l�F�Ȃ� 
void	CPcObj::MoveDownLeft() {
	SetDownLeftChangeLineValue();     // �ϐ��̒l���Z�b�g
	if (chPlacementH < upperLimitH && chPlacementV >= lowerLimitV) {
		if (trainDirectionFlag == downArrow) {       // �v���C���[���������ɐi��ł��邩�ǂ���
			if (frontFlag == true) {   //�v���C���[�����ʂ̏ꍇ
				if (m_pGMain->m_pMapProc->lineMap1[chPlacementNearH][chPlacementV] == changeLineNum &&
					m_pGMain->m_pMapProc->lineMap1[chPlacementH][chPlacementV] == changeLineNum &&
					m_pGMain->m_pMapProc->lineMap1[chPlacementNearH][chPlacementNearV] == changeLineNum &&
					m_pGMain->m_pMapProc->lineMap1[chPlacementH][chPlacementNearV] == changeLineNum) {
					DoneMove = true;
					switch (changeStepNum) {
					case 0: // �ړ�
						if (moveTimes < chLineMoveTimesMax) {                       // �Q�}�X�ړ�
							mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed);       // �O�Ɉړ�
							moveTimes += loopPlusMoveTimes;                         // �񐔂𑫂�
						}
						else {
							moveTimes = 0;
							changeStepNum++;                                        // ���̈ړ����s��
						}
						break;
					case 1:  //��]
						m_fLocalRotY += rotateChar;
						changeStepNum++;                                            //���̈ړ����s��
						break;
					case 2:
						if (moveTimes < moveTimesMax) {                             // 1�}�X�ړ�
							mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed);       // �O�Ɉړ�
							moveTimes += loopPlusMoveTimes;                         // �񐔂𑫂�
						}
						else {
							moveTimes = 0;
							trainDirectionFlag = leftArrow;    // �d�Ԃ̐i��ł�������̃Z�b�g
							// �ړ��������ߔz��̐��l�ύX(�����ϊ��X�C�b�`��6)
							m_pGMain->m_pMapProc->lineMap1[chPlacementNearH][chPlacementV] = afterChangeLineNum;
							m_pGMain->m_pMapProc->lineMap1[chPlacementH][chPlacementV] = afterChangeLineNum;
							m_pGMain->m_pMapProc->lineMap1[chPlacementNearH][chPlacementNearV] = afterChangeLineNum;
							m_pGMain->m_pMapProc->lineMap1[chPlacementH][chPlacementNearV] = afterChangeLineNum;
							oldHP += moveValueH;                                         // ���ݒn�̍X�V
							oldVP -= moveValueV;
							m_pGMain->m_pPcProc->trainStep += moveValueH + moveValueV;   // �ړ������𑫂�
							if (oldVP == edgePos) {
								edgeFlag = true;
							}
							changeStepNum = 0;                  // ���̈ړ��̂��߂�changeStepNum��0�ɖ߂�
							break;
						}
					}
				}
			}
			else if (frontFlag == false) {   // ���ʈȊO
				if (m_pGMain->m_pPcProc->lineMapSub[chPlacementNearH][chPlacementV] == changeLineNum &&
					m_pGMain->m_pPcProc->lineMapSub[chPlacementH][chPlacementV] == changeLineNum &&
					m_pGMain->m_pPcProc->lineMapSub[chPlacementNearH][chPlacementNearV] == changeLineNum &&
					m_pGMain->m_pPcProc->lineMapSub[chPlacementH][chPlacementNearV] == changeLineNum) {
					DoneMove = true;
					switch (changeStepNum) {
					case 0: // �ړ�
						if (moveTimes < chLineMoveTimesMax) {                       // �Q�}�X�ړ�
							mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed);       // �O�Ɉړ�
							moveTimes += loopPlusMoveTimes;                         // �񐔂𑫂�
						}
						else {
							moveTimes = 0;
							changeStepNum++;                                        // ���̈ړ����s��
						}
						break;
					case 1:  //��]
						m_fLocalRotY += rotateChar;
						changeStepNum++;                                            //���̈ړ����s��
						break;
					case 2:
						if (moveTimes < moveTimesMax) {                             // 1�}�X�ړ�
							mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed);       // �O�Ɉړ�
							moveTimes += loopPlusMoveTimes;                         // �񐔂𑫂�
						}
						else {
							moveTimes = 0;
							trainDirectionFlag = leftArrow;    // �d�Ԃ̐i��ł�������̃Z�b�g
							// �ړ��������ߔz��̐��l�ύX(�����ϊ��X�C�b�`��6)
							m_pGMain->m_pPcProc->lineMapSub[chPlacementNearH][chPlacementV] = afterChangeLineNum;
							m_pGMain->m_pPcProc->lineMapSub[chPlacementH][chPlacementV] = afterChangeLineNum;
							m_pGMain->m_pPcProc->lineMapSub[chPlacementNearH][chPlacementNearV] = afterChangeLineNum;       // �ړ��������ߔz��̐��l�ύX(�����ϊ��X�C�b�`��6)
							m_pGMain->m_pPcProc->lineMapSub[chPlacementH][chPlacementNearV] = afterChangeLineNum;
							oldHP += moveValueH;                                          // ���ݒn�̍X�V
							oldVP -= moveValueV;
							m_pGMain->m_pPcProc->trainStep += moveValueH + moveValueV;    // �ړ������𑫂�
							if (oldVP == edgePos) {
								edgeFlag = true;
							}
							changeStepNum = 0;              // ���̈ړ��̂��߂�changeStepNum��0�ɖ߂�
							break;
						}
					}
				}
			}
		}
	}
}
// M.S
// �L�����̕����؂�ւ����H�ړ�����(�E�����ړ�)
// ��  ���F�Ȃ�
// �߂�l�F�Ȃ� 
void	CPcObj::MoveRightUp() {
	SetRightUpChangeLineValue();     // �ϐ��̒l���Z�b�g
	if (chPlacementH >= lowerLimitV && chPlacementV < upperLimitH) {
		if (trainDirectionFlag == rightArrow) {       // �v���C���[���E�����ɐi��ł��邩�ǂ���
			if (frontFlag == true) {   //�v���C���[�����ʂ̏ꍇ
				if (m_pGMain->m_pMapProc->lineMap1[chPlacementH][chPlacementNearV] == changeLineNum &&
					m_pGMain->m_pMapProc->lineMap1[chPlacementH][chPlacementV] == changeLineNum &&
					m_pGMain->m_pMapProc->lineMap1[chPlacementNearH][chPlacementNearV] == changeLineNum &&
					m_pGMain->m_pMapProc->lineMap1[chPlacementNearH][chPlacementV] == changeLineNum) {
					DoneMove = true;
					switch (changeStepNum) {
					case 0: // �ړ�
						if (moveTimes < chLineMoveTimesMax) {                       // �Q�}�X�ړ�
							mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed);       // �O�Ɉړ�
							moveTimes += loopPlusMoveTimes;                         // �񐔂𑫂�
						}
						else {
							moveTimes = 0;
							changeStepNum++;                                        // ���̈ړ����s��
						}
						break;
					case 1:  //��]
						m_fLocalRotY -= rotateChar;
						changeStepNum++;                                            //���̈ړ����s��
						break;
					case 2:
						if (moveTimes < moveTimesMax) {                             // 1�}�X�ړ�
							mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed);       // �O�Ɉړ�
							moveTimes += loopPlusMoveTimes;                         // �񐔂𑫂�
						}
						else {
							moveTimes = 0;
							trainDirectionFlag = upArrow;   // �d�Ԃ̐i��ł�������̃Z�b�g
							// �ړ��������ߔz��̐��l�ύX(�����ϊ��X�C�b�`��6)
							m_pGMain->m_pMapProc->lineMap1[chPlacementH][chPlacementNearV] = afterChangeLineNum;
							m_pGMain->m_pMapProc->lineMap1[chPlacementH][chPlacementV] = afterChangeLineNum;
							m_pGMain->m_pMapProc->lineMap1[chPlacementNearH][chPlacementNearV] = afterChangeLineNum;
							m_pGMain->m_pMapProc->lineMap1[chPlacementNearH][chPlacementV] = afterChangeLineNum;
							oldHP -= moveValueH;                                          // ���ݒn�̍X�V
							oldVP += moveValueV;
							m_pGMain->m_pPcProc->trainStep += moveValueH + moveValueV;    // �ړ������𑫂�
							if (oldHP == edgePos) {
								edgeFlag = true;
							}
							changeStepNum = 0;                      // ���̈ړ��̂��߂�changeStepNum��0�ɖ߂�
							break;
						}
					}
				}
			}
			else if (frontFlag == false) {   // ���ʈȊO
				if (m_pGMain->m_pPcProc->lineMapSub[chPlacementH][chPlacementNearV] == changeLineNum &&
					m_pGMain->m_pPcProc->lineMapSub[chPlacementH][chPlacementV] == changeLineNum &&
					m_pGMain->m_pPcProc->lineMapSub[chPlacementNearH][chPlacementNearV] == changeLineNum &&
					m_pGMain->m_pPcProc->lineMapSub[chPlacementNearH][chPlacementV] == changeLineNum) {
					DoneMove = true;

					switch (changeStepNum) {
					case 0: // �ړ�
						if (moveTimes < chLineMoveTimesMax) {                       // �Q�}�X�ړ�
							mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed);       // �O�Ɉړ�
							moveTimes += loopPlusMoveTimes;                         // �񐔂𑫂�
						}
						else {
							moveTimes = 0;
							changeStepNum++;                                        // ���̈ړ����s��
						}
						break;
					case 1:  //��]
						m_fLocalRotY -= rotateChar;
						changeStepNum++;                                            //���̈ړ����s��
						break;
					case 2:
						if (moveTimes < moveTimesMax) {                             // 1�}�X�ړ�
							mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed);       // �O�Ɉړ�
							moveTimes += loopPlusMoveTimes;                         // �񐔂𑫂�
						}
						else {
							moveTimes = 0;
							trainDirectionFlag = upArrow;   // �d�Ԃ̐i��ł�������̃Z�b�g
							// �ړ��������ߔz��̐��l�ύX(�����ϊ��X�C�b�`��6)
							m_pGMain->m_pPcProc->lineMapSub[chPlacementH][chPlacementNearV] = afterChangeLineNum;
							m_pGMain->m_pPcProc->lineMapSub[chPlacementH][chPlacementV] = afterChangeLineNum;
							m_pGMain->m_pPcProc->lineMapSub[chPlacementNearH][chPlacementNearV] = afterChangeLineNum;       // �ړ��������ߔz��̐��l�ύX(�����ϊ��X�C�b�`��6)
							m_pGMain->m_pPcProc->lineMapSub[chPlacementNearH][chPlacementV] = afterChangeLineNum;
							oldHP -= moveValueH;                                          // ���ݒn�̍X�V
							oldVP += moveValueV;
							m_pGMain->m_pPcProc->trainStep += moveValueH + moveValueV;    // �ړ������𑫂�
							if (oldHP == edgePos) {
								edgeFlag = true;
							}
							changeStepNum = 0;                 // ���̈ړ��̂��߂�changeStepNum��0�ɖ߂�
							break;
						}
					}
				}
			}
		}
	}

}
// M.S
// �L�����̕����؂�ւ����H�ړ�����(�E���牺�ړ�)
// ��  ���F�Ȃ�
// �߂�l�F�Ȃ� 
void	CPcObj::MoveRightDown() {
	SetRightDownChangeLineValue();     // �ϐ��̒l���Z�b�g
	if (chPlacementH < upperLimitH && chPlacementV < upperLimitV) {
		if (trainDirectionFlag == rightArrow) {       // �v���C���[���E�����ɐi��ł��邩�ǂ���
			if (frontFlag == true) {   //�v���C���[�����ʂ̏ꍇ
				if (m_pGMain->m_pMapProc->lineMap1[chPlacementNearH][chPlacementNearV] == changeLineNum &&
					m_pGMain->m_pMapProc->lineMap1[chPlacementNearH][chPlacementV] == changeLineNum &&
					m_pGMain->m_pMapProc->lineMap1[chPlacementH][chPlacementNearV] == changeLineNum &&
					m_pGMain->m_pMapProc->lineMap1[chPlacementH][chPlacementV] == changeLineNum) {
					DoneMove = true;
					switch (changeStepNum) {
					case 0: // �ړ�
						if (moveTimes < chLineMoveTimesMax) {                       // �Q�}�X�ړ�
							mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed);       // �O�Ɉړ�
							moveTimes += loopPlusMoveTimes;                         // �񐔂𑫂�
						}
						else {
							moveTimes = 0;
							changeStepNum++;                                        // ���̈ړ����s��
						}
						break;
					case 1:  //��]
						m_fLocalRotY += rotateChar;
						changeStepNum++;                                            //���̈ړ����s��
						break;
					case 2:
						if (moveTimes < moveTimesMax) {                             // 1�}�X�ړ�
							mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed);       // �O�Ɉړ�
							moveTimes += loopPlusMoveTimes;                         // �񐔂𑫂�
						}
						else {
							moveTimes = 0;
							trainDirectionFlag = downArrow;    // �d�Ԃ̐i��ł�������̃Z�b�g
							// �ړ��������ߔz��̐��l�ύX(�����ϊ��X�C�b�`��6)
							m_pGMain->m_pMapProc->lineMap1[chPlacementNearH][chPlacementNearV] = afterChangeLineNum;
							m_pGMain->m_pMapProc->lineMap1[chPlacementNearH][chPlacementV] = afterChangeLineNum;
							m_pGMain->m_pMapProc->lineMap1[chPlacementH][chPlacementNearV] = afterChangeLineNum;
							m_pGMain->m_pMapProc->lineMap1[chPlacementH][chPlacementV] = afterChangeLineNum;
							oldHP += moveValueH;                                                // ���ݒn�̍X�V
							oldVP += moveValueV;
							m_pGMain->m_pPcProc->trainStep += moveValueH + moveValueV;          // �ړ������𑫂�
							if (oldHP == edgePos) {
								edgeFlag = true;
							}
							changeStepNum = 0;                        // ���̈ړ��̂��߂�changeStepNum��0�ɖ߂�
							break;
						}
					}
				}
			}
			else if (frontFlag == false) {   // ���ʈȊO
				if (m_pGMain->m_pPcProc->lineMapSub[chPlacementNearH][chPlacementNearV] == changeLineNum &&
					m_pGMain->m_pPcProc->lineMapSub[chPlacementNearH][chPlacementV] == changeLineNum &&
					m_pGMain->m_pPcProc->lineMapSub[chPlacementH][chPlacementNearV] == changeLineNum &&
					m_pGMain->m_pPcProc->lineMapSub[chPlacementH][chPlacementV] == changeLineNum) {
					DoneMove = true;
					switch (changeStepNum) {
					case 0: // �ړ�
						if (moveTimes < chLineMoveTimesMax) {                       // �Q�}�X�ړ�
							mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed);       // �O�Ɉړ�
							moveTimes += loopPlusMoveTimes;                         // �񐔂𑫂�
						}
						else {
							moveTimes = 0;
							changeStepNum++;                                        // ���̈ړ����s��
						}
						break;
					case 1:  //��]
						m_fLocalRotY += rotateChar;
						changeStepNum++;                                            //���̈ړ����s��
						break;
					case 2:
						if (moveTimes < moveTimesMax) {                             // 1�}�X�ړ�
							mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed);       // �O�Ɉړ�
							moveTimes += loopPlusMoveTimes;                         // �񐔂𑫂�
						}
						else {
							moveTimes = 0;
							trainDirectionFlag = downArrow;     // �d�Ԃ̐i��ł�������̃Z�b�g
							// �ړ��������ߔz��̐��l�ύX(�����ϊ��X�C�b�`��6)
							m_pGMain->m_pPcProc->lineMapSub[chPlacementNearH][chPlacementNearV] = afterChangeLineNum;
							m_pGMain->m_pPcProc->lineMapSub[chPlacementNearH][chPlacementV] = afterChangeLineNum;
							m_pGMain->m_pPcProc->lineMapSub[chPlacementH][chPlacementNearV] = afterChangeLineNum;
							m_pGMain->m_pPcProc->lineMapSub[chPlacementH][chPlacementV] = afterChangeLineNum;
							oldHP += moveValueH;                                          // ���ݒn�̍X�V
							oldVP += moveValueV;
							m_pGMain->m_pPcProc->trainStep += moveValueH + moveValueV;    // �ړ������𑫂�
							if (oldHP == edgePos) {
								edgeFlag = true;
							}
							changeStepNum = 0;                        // ���̈ړ��̂��߂�changeStepNum��0�ɖ߂�
							break;
						}
					}
				}
			}
		}
	}

}
// M.S
// �L�����̕����؂�ւ����H�ړ�����(�������ړ�)
// ��  ���F�Ȃ�
// �߂�l�F�Ȃ� 
void	CPcObj::MoveLeftUp() {
	SetLeftUpChangeLineValue();     // �ϐ��̒l���Z�b�g
	if (chPlacementH >= lowerLimitH && chPlacementV >= lowerLimitV) {
		if (trainDirectionFlag == leftArrow) {       // �v���C���[���������ɐi��ł��邩�ǂ���
			if (frontFlag == true) {   //�v���C���[�����ʂ̏ꍇ
				if (m_pGMain->m_pMapProc->lineMap1[chPlacementH][chPlacementNearV] == changeLineNum &&
					m_pGMain->m_pMapProc->lineMap1[chPlacementH][chPlacementV] == changeLineNum &&
					m_pGMain->m_pMapProc->lineMap1[chPlacementNearH][chPlacementNearV] == changeLineNum &&
					m_pGMain->m_pMapProc->lineMap1[chPlacementNearH][chPlacementV] == changeLineNum) {
					DoneMove = true;
					switch (changeStepNum) {
					case 0: // �ړ�
						if (moveTimes < chLineMoveTimesMax) {                       // �Q�}�X�ړ�
							mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed);       // �O�Ɉړ�
							moveTimes += loopPlusMoveTimes;                         // �񐔂𑫂�
						}
						else {
							moveTimes = 0;
							changeStepNum++;                                        // ���̈ړ����s��
						}
						break;
					case 1:  //��]
						m_fLocalRotY += rotateChar;
						changeStepNum++;                                            //���̈ړ����s��
						break;
					case 2:
						if (moveTimes < moveTimesMax) {                             // 1�}�X�ړ�
							mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed);       // �O�Ɉړ�
							moveTimes += loopPlusMoveTimes;                         // �񐔂𑫂�
						}
						else {
							moveTimes = 0;
							trainDirectionFlag = upArrow;      // �d�Ԃ̐i��ł�������̃Z�b�g
							// �ړ��������ߔz��̐��l�ύX(�����ϊ��X�C�b�`��6)
							m_pGMain->m_pMapProc->lineMap1[chPlacementH][chPlacementNearV] = afterChangeLineNum;
							m_pGMain->m_pMapProc->lineMap1[chPlacementH][chPlacementV] = afterChangeLineNum;
							m_pGMain->m_pMapProc->lineMap1[chPlacementNearH][chPlacementNearV] = afterChangeLineNum;
							m_pGMain->m_pMapProc->lineMap1[chPlacementNearH][chPlacementV] = afterChangeLineNum;
							oldHP -= moveValueH;                                         // ���ݒn�̍X�V
							oldVP -= moveValueV;
							m_pGMain->m_pPcProc->trainStep += moveValueH + moveValueV;   // �ړ������𑫂�
							if (oldHP == edgePos) {
								edgeFlag = true;
							}
							changeStepNum = 0;                  // ���̈ړ��̂��߂�changeStepNum��0�ɖ߂�
							break;
						}
					}
				}
			}
			else if (frontFlag == false) {   // ���ʈȊO
				if (m_pGMain->m_pPcProc->lineMapSub[chPlacementH][chPlacementNearV] == changeLineNum &&
					m_pGMain->m_pPcProc->lineMapSub[chPlacementH][chPlacementV] == changeLineNum &&
					m_pGMain->m_pPcProc->lineMapSub[chPlacementNearH][chPlacementNearV] == changeLineNum &&
					m_pGMain->m_pPcProc->lineMapSub[chPlacementNearH][chPlacementV] == changeLineNum) {
					DoneMove = true;
					switch (changeStepNum) {
					case 0: // �ړ�
						if (moveTimes < chLineMoveTimesMax) {                       // �Q�}�X�ړ�
							mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed);       // �O�Ɉړ�
							moveTimes += loopPlusMoveTimes;                         // �񐔂𑫂�
						}
						else {
							moveTimes = 0;
							changeStepNum++;                                        // ���̈ړ����s��
						}
						break;
					case 1:  //��]
						m_fLocalRotY += rotateChar;
						changeStepNum++;                                            //���̈ړ����s��
						break;
					case 2:
						if (moveTimes < moveTimesMax) {                             // 1�}�X�ړ�
							mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed);       // �O�Ɉړ�
							moveTimes += loopPlusMoveTimes;                         // �񐔂𑫂�
						}
						else {
							moveTimes = 0;
							trainDirectionFlag = upArrow;        // �d�Ԃ̐i��ł�������̃Z�b�g
							// �ړ��������ߔz��̐��l�ύX(�����ϊ��X�C�b�`��6)
							m_pGMain->m_pPcProc->lineMapSub[chPlacementH][chPlacementNearV] = afterChangeLineNum;
							m_pGMain->m_pPcProc->lineMapSub[chPlacementH][chPlacementV] = afterChangeLineNum;
							m_pGMain->m_pPcProc->lineMapSub[chPlacementNearH][chPlacementNearV] = afterChangeLineNum;        // �ړ��������ߔz��̐��l�ύX(�����ϊ��X�C�b�`��6)
							m_pGMain->m_pPcProc->lineMapSub[chPlacementNearH][chPlacementV] = afterChangeLineNum;
							oldHP -= moveValueH;                                                  // ���ݒn�̍X�V
							oldVP -= moveValueV;
							m_pGMain->m_pPcProc->trainStep += moveValueH + moveValueV;            // �ړ������𑫂�
							if (oldHP == edgePos) {
								edgeFlag = true;
							}
							changeStepNum = 0;                    // ���̈ړ��̂��߂�changeStepNum��0�ɖ߂�
							break;
						}
					}
				}
			}
		}
	}

}
// M.S
// �L�����̕����؂�ւ����H�ړ�����(�����牺�ړ�)
// ��  ���F�Ȃ�
// �߂�l�F�Ȃ� 
void	CPcObj::MoveLeftDown() {
	SetLeftDownChangeLineValue();     // �ϐ��̒l���Z�b�g
	if (chPlacementH < upperLimitH && chPlacementV >= lowerLimitV) {
		if (trainDirectionFlag == leftArrow) {       // �v���C���[���������ɐi��ł��邩�ǂ���
			if (frontFlag == true) {   //�v���C���[�����ʂ̏ꍇ
				if (m_pGMain->m_pMapProc->lineMap1[chPlacementNearH][chPlacementNearV] == changeLineNum &&
					m_pGMain->m_pMapProc->lineMap1[chPlacementNearH][chPlacementV] == changeLineNum &&
					m_pGMain->m_pMapProc->lineMap1[chPlacementH][chPlacementNearV] == changeLineNum &&
					m_pGMain->m_pMapProc->lineMap1[chPlacementH][chPlacementV] == changeLineNum) {
					DoneMove = true;
					switch (changeStepNum) {
					case 0: // �ړ�
						if (moveTimes < chLineMoveTimesMax) {                       // �Q�}�X�ړ�����
							mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed);       // �O�Ɉړ�
							moveTimes += loopPlusMoveTimes;                         // �񐔂𑫂�
						}
						else {
							moveTimes = 0;
							changeStepNum++;                                        // ���̈ړ����s��
						}
						break;
					case 1:  //��]
						m_fLocalRotY -= rotateChar;
						changeStepNum++;                                            //���̈ړ����s��
						break;
					case 2:
						if (moveTimes < moveTimesMax) {                             // 1�}�X�ړ�
							mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed);       // �O�Ɉړ�
							moveTimes += loopPlusMoveTimes;                         // �񐔂𑫂�
						}
						else {
							moveTimes = 0;
							trainDirectionFlag = downArrow;        // �d�Ԃ̐i��ł�������̃Z�b�g
							// �ړ��������ߔz��̐��l�ύX(�����ϊ��X�C�b�`��6)
							m_pGMain->m_pMapProc->lineMap1[chPlacementNearH][chPlacementNearV] = afterChangeLineNum;
							m_pGMain->m_pMapProc->lineMap1[chPlacementNearH][chPlacementV] = afterChangeLineNum;
							m_pGMain->m_pMapProc->lineMap1[chPlacementH][chPlacementNearV] = afterChangeLineNum;
							m_pGMain->m_pMapProc->lineMap1[chPlacementH][chPlacementV] = afterChangeLineNum;
							oldHP += moveValueH;                                            // ���ݒn�̍X�V
							oldVP -= moveValueV;
							m_pGMain->m_pPcProc->trainStep += moveValueH + moveValueV;      // �ړ������𑫂�
							if (oldHP == edgePos) {
								edgeFlag = true;
							}
							changeStepNum = 0;                      // ���̈ړ��̂��߂�changeStepNum��0�ɖ߂�
							break;
						}
					}
				}
			}
			else if (frontFlag == false) {   // ���ʈȊO
				if (m_pGMain->m_pPcProc->lineMapSub[chPlacementNearH][chPlacementNearV] == changeLineNum &&
					m_pGMain->m_pPcProc->lineMapSub[chPlacementNearH][chPlacementV] == changeLineNum &&
					m_pGMain->m_pPcProc->lineMapSub[chPlacementH][chPlacementNearV] == changeLineNum &&
					m_pGMain->m_pPcProc->lineMapSub[chPlacementH][chPlacementV] == changeLineNum) {
					DoneMove = true;
					switch (changeStepNum) {
					case 0: // �ړ�
						if (moveTimes < chLineMoveTimesMax) {                       // �Q�}�X�ړ�
							mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed);       // �O�Ɉړ�
							moveTimes += loopPlusMoveTimes;                         // �񐔂𑫂�
						}
						else {
							moveTimes = 0;
							changeStepNum++;                                        // ���̈ړ����s��
						}
						break;
					case 1:  //��]
						m_fLocalRotY -= rotateChar;
						changeStepNum++;                                            //���̈ړ����s��
						break;
					case 2:
						if (moveTimes < moveTimesMax) {                             // 1�}�X�ړ�
							mPos = XMMatrixTranslation(0.0f, 0.0f, m_fSpeed);       // �O�Ɉړ�
							moveTimes += loopPlusMoveTimes;                         // �񐔂𑫂�
						}
						else {
							moveTimes = 0;
							trainDirectionFlag = downArrow;        // �d�Ԃ̐i��ł�������̃Z�b�g
							// �ړ��������ߔz��̐��l�ύX(�����ϊ��X�C�b�`��6)
							m_pGMain->m_pPcProc->lineMapSub[chPlacementNearH][chPlacementNearV] = afterChangeLineNum;
							m_pGMain->m_pPcProc->lineMapSub[chPlacementNearH][chPlacementV] = afterChangeLineNum;
							m_pGMain->m_pPcProc->lineMapSub[chPlacementH][chPlacementNearV] = afterChangeLineNum;     // �ړ��������ߔz��̐��l�ύX(�����ϊ��X�C�b�`��6)
							m_pGMain->m_pPcProc->lineMapSub[chPlacementH][chPlacementV] = afterChangeLineNum;
							oldHP += moveValueH;    				                      // ���ݒn�̍X�V       
							oldVP -= moveValueV;
							m_pGMain->m_pPcProc->trainStep += moveValueH + moveValueV;    // �ړ������𑫂�
							if (oldHP == edgePos) {
								edgeFlag = true;
							}
							changeStepNum = 0;                     // ���̈ړ��̂��߂�changeStepNum��0�ɖ߂�
							break;
						}
					}
				}
			}
		}
	}
}
// M.S
// �}�b�v�ʂ̒[���玟�̖ʂւ�
// �v���C�L�����̉�]�p�x�A�ʒu�����߂�֐�
// ��  ���F�Ȃ�
// �߂�l�F�Ȃ� 
void	CPcObj::MoveEdgePos1(){
	// �}�b�v�ʔz��̒[�ɂ��āA���������������̃}�b�v�ʂ��ǂ����݂ď���������
	// nowNorth 1:�}�b�v������] 2:�}�b�v��+90�x��] 3:�}�b�v��+180�x��] 4:�}�b�v��+180�x��]
	if (nowNorth == 1 && trainDirectionFlag == 1 || nowNorth == 2 && trainDirectionFlag == 4
		|| nowNorth == 3 && trainDirectionFlag == 3 || nowNorth == 4 && trainDirectionFlag == 2) {       // ������֌�����
		newPcPos = XMMatrixTranslation(nowPcPos.x, 5.5f, 6.0f);     // �ʒu
		edgeRotate1 = XMMatrixRotationX(XMConvertToRadians(90.0f)); // ��]�p�x
		needRotateFlag = 1;     // �������]�̐�
	}
	else if (nowNorth == 1 && trainDirectionFlag == 2 || nowNorth == 2 && trainDirectionFlag == 1
		|| nowNorth == 3 && trainDirectionFlag == 4 || nowNorth == 4 && trainDirectionFlag == 3) { // �E�����֌�����
		newPcPos = XMMatrixTranslation(6.0f, 5.5f, nowPcPos.z);      // �ʒu
		edgeRotate1 = XMMatrixRotationX(XMConvertToRadians(90.0f));  // ��]�p�x
		edgeRotate2 = XMMatrixRotationY(XMConvertToRadians(90.0f));  // ��]�p�x
		needRotateFlag = 2;   // �������]�̐�
	}
	else if (nowNorth == 1 && trainDirectionFlag == 3 || nowNorth == 2 && trainDirectionFlag == 2
		|| nowNorth == 3 && trainDirectionFlag == 1 || nowNorth == 4 && trainDirectionFlag == 4) { // �������֌�����
		newPcPos = XMMatrixTranslation(nowPcPos.x, 5.5f, -6.0f);     // �ʒu  
		edgeRotate1 = XMMatrixRotationX(XMConvertToRadians(90.0f));  // ��]�p�x
		edgeRotate2 = XMMatrixRotationY(XMConvertToRadians(180.0f)); // ��]�p�x
		needRotateFlag = 2;   // �������]�̐�
	}
	else if (nowNorth == 1 && trainDirectionFlag == 4 || nowNorth == 2 && trainDirectionFlag == 3
		|| nowNorth == 3 && trainDirectionFlag == 2 || nowNorth == 4 && trainDirectionFlag == 1) { // �������֌�����
		newPcPos = XMMatrixTranslation(-6.0f, 5.5f, nowPcPos.z);     // �ʒu
		edgeRotate1 = XMMatrixRotationX(XMConvertToRadians(90.0f));  // ��]�p�x
		edgeRotate2 = XMMatrixRotationY(XMConvertToRadians(270.0f)); // ��]�p�x
		needRotateFlag = 2;   // �������]�̐�
	}
}
// M.S
// �}�b�v�ʂ̒[���玟�̖ʂւ�
// �v���C�L�����̉�]�p�x�A�ʒu�����߂�֐�
// ��  ���F�Ȃ�
// �߂�l�F�Ȃ� 
void	CPcObj::MoveEdgePos2() {
	// nowPcPosNum:��΍��W����̈ʒu 0:�� 1:��O 2:�� 3:��O�� 4:�E 5:��
	//nowNorth 1:�}�b�v������] 2:�}�b�v��+90�x��] 3:�}�b�v��+180�x��] 4:�}�b�v��+180�x��]
	if (nowNorth == 1 && trainDirectionFlag == 1 || nowNorth == 2 && trainDirectionFlag == 4
		|| nowNorth == 3 && trainDirectionFlag == 3 || nowNorth == 4 && trainDirectionFlag == 2) {       // ������֌�����
		newPcPos = XMMatrixTranslation(nowPcPos.x, 6.0f, -5.5f);     // �ʒu
		needRotateFlag = 0;   // �������]�̐�
	}
	else if (nowNorth == 1 && trainDirectionFlag == 2 || nowNorth == 2 && trainDirectionFlag == 1
		|| nowNorth == 3 && trainDirectionFlag == 4 || nowNorth == 4 && trainDirectionFlag == 3) { // �E�����֌�����
		newPcPos = XMMatrixTranslation(6.0f, nowPcPos.y, -5.5f);     // �ʒu
		edgeRotate1 = XMMatrixRotationZ(XMConvertToRadians(270.0f)); // ��]�p�x
		needRotateFlag = 1;   // �������]�̐�
	}
	else if (nowNorth == 1 && trainDirectionFlag == 3 || nowNorth == 2 && trainDirectionFlag == 2
		|| nowNorth == 3 && trainDirectionFlag == 1 || nowNorth == 4 && trainDirectionFlag == 4) { // �������֌�����
		newPcPos = XMMatrixTranslation(nowPcPos.x, -6.0f, -5.5f);    // �ʒu
		edgeRotate1 = XMMatrixRotationZ(XMConvertToRadians(180.0f)); // ��]�p�x
		needRotateFlag = 1;   // �������]�̐�
	}
	else if (nowNorth == 1 && trainDirectionFlag == 4 || nowNorth == 2 && trainDirectionFlag == 3
		|| nowNorth == 3 && trainDirectionFlag == 2 || nowNorth == 4 && trainDirectionFlag == 1) {
		newPcPos = XMMatrixTranslation(-6.0f, nowPcPos.y, -5.5f);   // �ʒu
		edgeRotate1 = XMMatrixRotationZ(XMConvertToRadians(90.0f)); // ��]�p�x
		needRotateFlag = 1;   // �������]�̐�
	}
}
// M.S
// �}�b�v�ʂ̒[���玟�̖ʂւ�
// �v���C�L�����̉�]�p�x�A�ʒu�����߂�֐�
// ��  ���F�Ȃ�
// �߂�l�F�Ȃ� 
void	CPcObj::MoveEdgePos3() {
	// nowPcPosNum:��΍��W����̈ʒu 0:�� 1:��O 2:�� 3:��O�� 4:�E 5:��
	//nowNorth 1:�}�b�v������] 2:�}�b�v��+90�x��] 3:�}�b�v��+180�x��] 4:�}�b�v��+180�x��]
	if (nowNorth == 1 && trainDirectionFlag == 1 || nowNorth == 2 && trainDirectionFlag == 4
		|| nowNorth == 3 && trainDirectionFlag == 3 || nowNorth == 4 && trainDirectionFlag == 2) {       // ������֌�����
		newPcPos = XMMatrixTranslation(nowPcPos.x, -5.5f, -6.0f);    // �ʒu
		edgeRotate1 = XMMatrixRotationX(XMConvertToRadians(270.0f)); // ��]�p�x
		needRotateFlag = 1;   // �������]�̐�
	}
	else if (nowNorth == 1 && trainDirectionFlag == 2 || nowNorth == 2 && trainDirectionFlag == 1
		|| nowNorth == 3 && trainDirectionFlag == 4 || nowNorth == 4 && trainDirectionFlag == 3) { // �E�����֌�����
		newPcPos = XMMatrixTranslation(6.0f, -5.5f, nowPcPos.z);     // �ʒu
		edgeRotate1 = XMMatrixRotationX(XMConvertToRadians(270.0f)); // ��]�p�x
		edgeRotate2 = XMMatrixRotationY(XMConvertToRadians(270.0f)); // ��]�p�x
		needRotateFlag = 2;   // �������]�̐�
	}
	else if (nowNorth == 1 && trainDirectionFlag == 3 || nowNorth == 2 && trainDirectionFlag == 2
		|| nowNorth == 3 && trainDirectionFlag == 1 || nowNorth == 4 && trainDirectionFlag == 4) { // �������֌�����
		newPcPos = XMMatrixTranslation(nowPcPos.x, -5.5f, 6.0);      // �ʒu
		edgeRotate2 = XMMatrixRotationZ(XMConvertToRadians(180.0f)); // ��]�p�x
		edgeRotate1 = XMMatrixRotationX(XMConvertToRadians(90.0f));  // ��]�p�x
		needRotateFlag = 2;   // �������]�̐�
	}
	else if (nowNorth == 1 && trainDirectionFlag == 4 || nowNorth == 2 && trainDirectionFlag == 3
		|| nowNorth == 3 && trainDirectionFlag == 2 || nowNorth == 4 && trainDirectionFlag == 1) {
		newPcPos = XMMatrixTranslation(-6.0f, -5.5f, nowPcPos.z);    // �ʒu
		edgeRotate1 = XMMatrixRotationX(XMConvertToRadians(270.0f)); // ��]�p�x
		edgeRotate2 = XMMatrixRotationY(XMConvertToRadians(90.0f));  // ��]�p�x
		needRotateFlag = 2;   // �������]�̐�
	}
}
// M.S
// �}�b�v�ʂ̒[���玟�̖ʂւ�
// �v���C�L�����̉�]�p�x�A�ʒu�����߂�֐�
// ��  ���F�Ȃ�
// �߂�l�F�Ȃ� 
void	CPcObj::MoveEdgePos4() {
	// nowPcPosNum:��΍��W����̈ʒu 0:�� 1:��O 2:�� 3:��O�� 4:�E 5:��
	//nowNorth 1:�}�b�v������] 2:�}�b�v��+90�x��] 3:�}�b�v��+180�x��] 4:�}�b�v��+180�x��]
	if (nowNorth == 1 && trainDirectionFlag == 1 || nowNorth == 2 && trainDirectionFlag == 4
		|| nowNorth == 3 && trainDirectionFlag == 3 || nowNorth == 4 && trainDirectionFlag == 2) {       // ������֌�����
		newPcPos = XMMatrixTranslation(nowPcPos.x, -6.0f, 5.5f);     // �ʒu
		edgeRotate1 = XMMatrixRotationX(XMConvertToRadians(180.0f)); // ��]�p�x
		needRotateFlag = 1;    // �������]�̐�
	}
	else if (nowNorth == 1 && trainDirectionFlag == 2 || nowNorth == 2 && trainDirectionFlag == 1
		|| nowNorth == 3 && trainDirectionFlag == 4 || nowNorth == 4 && trainDirectionFlag == 3) { // �E�����֌�����
		newPcPos = XMMatrixTranslation(6.0f, nowPcPos.y, 5.5f);      // �ʒu
		edgeRotate1 = XMMatrixRotationZ(XMConvertToRadians(90.0f));  // ��]�p�x
 		edgeRotate2 = XMMatrixRotationY(XMConvertToRadians(180.0f)); // ��]�p�x
		needRotateFlag = 2;    // �������]�̐�
	}
	else if (nowNorth == 1 && trainDirectionFlag == 3 || nowNorth == 2 && trainDirectionFlag == 2
		|| nowNorth == 3 && trainDirectionFlag == 1 || nowNorth == 4 && trainDirectionFlag == 4) { // �������֌�����
		newPcPos = XMMatrixTranslation(nowPcPos.x, 6.0f, 5.5f);       // �ʒu
		edgeRotate1 = XMMatrixRotationY(XMConvertToRadians(180.0f));  // ��]�p�x
		needRotateFlag = 1;   // �������]�̐�
	}
	else if (nowNorth == 1 && trainDirectionFlag == 4 || nowNorth == 2 && trainDirectionFlag == 3
		|| nowNorth == 3 && trainDirectionFlag == 2 || nowNorth == 4 && trainDirectionFlag == 1) {
		newPcPos = XMMatrixTranslation(-6.0f, nowPcPos.y, 5.5);      // �ʒu
		edgeRotate2 = XMMatrixRotationY(XMConvertToRadians(180.0f)); // ��]�p�x
		edgeRotate1 = XMMatrixRotationZ(XMConvertToRadians(270.0f)); // ��]�p�x
		needRotateFlag = 2;   // �������]�̐�
	}
}
// M.S
// �}�b�v�ʂ̒[���玟�̖ʂւ�
// �v���C�L�����̉�]�p�x�A�ʒu�����߂�֐�
// ��  ���F�Ȃ�
// �߂�l�F�Ȃ� 
void	CPcObj::MoveEdgePos5() {
	// nowPcPosNum:��΍��W����̈ʒu 0:�� 1:��O 2:�� 3:��O�� 4:�E 5:��
	//nowNorth 1:�}�b�v������] 2:�}�b�v��+90�x��] 3:�}�b�v��+180�x��] 4:�}�b�v��+180�x��]
	if (nowNorth == 1 && trainDirectionFlag == 1 || nowNorth == 2 && trainDirectionFlag == 4
		|| nowNorth == 3 && trainDirectionFlag == 3 || nowNorth == 4 && trainDirectionFlag == 2) {       // ������֌�����
		newPcPos = XMMatrixTranslation(5.5f, nowPcPos.y, 6.0f);      // �ʒu
		edgeRotate1 = XMMatrixRotationY(XMConvertToRadians(270.0f)); // ��]�p�x
		edgeRotate2 = XMMatrixRotationX(XMConvertToRadians(90.0f));  // ��]�p�x
		needRotateFlag = 2;  // �������]�̐�
	}
	else if (nowNorth == 1 && trainDirectionFlag == 2 || nowNorth == 2 && trainDirectionFlag == 1
		|| nowNorth == 3 && trainDirectionFlag == 4 || nowNorth == 4 && trainDirectionFlag == 3) { // �E�����֌�����
		newPcPos = XMMatrixTranslation(5.5f, -6.0f, nowPcPos.z);     // �ʒu
		edgeRotate1 = XMMatrixRotationX(XMConvertToRadians(180.0f)); // ��]�p�x
		edgeRotate2 = XMMatrixRotationY(XMConvertToRadians(90.0f));  // ��]�p�x
		needRotateFlag = 2;  // �������]�̐�
	}
	else if (nowNorth == 1 && trainDirectionFlag == 3 || nowNorth == 2 && trainDirectionFlag == 2
		|| nowNorth == 3 && trainDirectionFlag == 1 || nowNorth == 4 && trainDirectionFlag == 4) { // �������֌�����
		newPcPos = XMMatrixTranslation(5.5f, nowPcPos.y, -6.0f);     // �ʒu
		edgeRotate1 = XMMatrixRotationZ(XMConvertToRadians(90.0f));  // ��]�p�x
		edgeRotate2 = XMMatrixRotationY(XMConvertToRadians(270.0f)); // ��]�p�x
		needRotateFlag = 2;  // �������]�̐�
	}
	else if (nowNorth == 1 && trainDirectionFlag == 4 || nowNorth == 2 && trainDirectionFlag == 3
		|| nowNorth == 3 && trainDirectionFlag == 2 || nowNorth == 4 && trainDirectionFlag == 1) {
		newPcPos = XMMatrixTranslation(5.5f, 6.0f, nowPcPos.z);      // �ʒu
		edgeRotate1 = XMMatrixRotationY(XMConvertToRadians(270.0f)); // ��]�p�x
		needRotateFlag = 1;  // �������]�̐�
	}
}
// M.S
// �}�b�v�ʂ̒[���玟�̖ʂւ�
// �v���C�L�����̉�]�p�x�A�ʒu�����߂�֐�
// ��  ���F�Ȃ�
// �߂�l�F�Ȃ� 
void	CPcObj::MoveEdgePos6() {
	// nowPcPosNum:��΍��W����̈ʒu 0:�� 1:��O 2:�� 3:��O�� 4:�E 5:��
    // nowNorth 1:�}�b�v������] 2:�}�b�v��+90�x��] 3:�}�b�v��+180�x��] 4:�}�b�v��+180�x��]
	if (nowNorth == 1 && trainDirectionFlag == 1 || nowNorth == 2 && trainDirectionFlag == 4
		|| nowNorth == 3 && trainDirectionFlag == 3 || nowNorth == 4 && trainDirectionFlag == 2) {       // ������֌�����
		newPcPos = XMMatrixTranslation(-5.5f, nowPcPos.y, 6.0f);     // �ʒu
		edgeRotate1 = XMMatrixRotationY(XMConvertToRadians(90.0f));  // ��]�p�x
		edgeRotate2 = XMMatrixRotationX(XMConvertToRadians(90.0f));  // ��]�p�x
		needRotateFlag = 2;  // �������]�̐�
	}
	else if (nowNorth == 1 && trainDirectionFlag == 2 || nowNorth == 2 && trainDirectionFlag == 1
		|| nowNorth == 3 && trainDirectionFlag == 4 || nowNorth == 4 && trainDirectionFlag == 3) { // �E�����֌�����
		newPcPos = XMMatrixTranslation(-5.5f, 6.0f, nowPcPos.z);     // �ʒu
		edgeRotate1 = XMMatrixRotationY(XMConvertToRadians(90.0f));  // ��]�p�x
		needRotateFlag = 1;  // �������]�̐�
	}
	else if (nowNorth == 1 && trainDirectionFlag == 3 || nowNorth == 2 && trainDirectionFlag == 2
		|| nowNorth == 3 && trainDirectionFlag == 1 || nowNorth == 4 && trainDirectionFlag == 4) { // �������֌�����
		newPcPos = XMMatrixTranslation(-5.5f, nowPcPos.y, -6.0f);     // �ʒu
		edgeRotate1 = XMMatrixRotationX(XMConvertToRadians(270.0f));  // ��]�p�x
		edgeRotate2 = XMMatrixRotationZ(XMConvertToRadians(270.0f));  // ��]�p�x
		needRotateFlag = 2;  // �������]�̐�
	}
	else if (nowNorth == 1 && trainDirectionFlag == 4 || nowNorth == 2 && trainDirectionFlag == 3
		|| nowNorth == 3 && trainDirectionFlag == 2 || nowNorth == 4 && trainDirectionFlag == 1) {
		newPcPos = XMMatrixTranslation(-5.5f, -6.0f, nowPcPos.z);     // �ʒu
		edgeRotate1 = XMMatrixRotationY(XMConvertToRadians(270.0f));  // ��]�p�x
		edgeRotate2 = XMMatrixRotationZ(XMConvertToRadians(180.0f));  // ��]�p�x
		needRotateFlag = 2;  // �������]�̐�
	}
}
// M.S
// �L�����̈ʒu����MoveEdgePos���Ă��
// �[����ړ��������̈ʒu�Ɖ�]�����߂�
// ��  ���F�Ȃ�
// �߂�l�F�Ȃ� 
void	CPcObj::SetEdgePos() {
	switch (nowPcPosNum) {   // M.S ����pc�̈ʒu
	case 0:
		MoveEdgePos1();      // M.S �v���C�L�����̈ʒu�Ɖ�]�p�x�����߂�
		break;
	case 1:
		MoveEdgePos2();      // M.S �v���C�L�����̈ʒu�Ɖ�]�p�x�����߂�
		break;
	case 2:
		MoveEdgePos3();      // M.S �v���C�L�����̈ʒu�Ɖ�]�p�x�����߂�
		break;
	case 3:
		MoveEdgePos4();      // M.S �v���C�L�����̈ʒu�Ɖ�]�p�x�����߂�
		break;
	case 4:
		MoveEdgePos5();      // M.S �v���C�L�����̈ʒu�Ɖ�]�p�x�����߂�
		break;
	case 5:
		MoveEdgePos6();      // M.S �v���C�L�����̈ʒu�Ɖ�]�p�x�����߂�
		break;
	}
}
//-----------------------------------------------------------------------------   // -- 2019.3.5
// �o�b�I�u�W�F�N�g�̈ړ�����
//
//�@�o�b�𓮂���
//�@�o�b�̃A�j���[�V�����A�W�����v�A���R����
//�@���[���h���W�Ԋ�
//
//
//   �����@�Ȃ�
//
//-----------------------------------------------------------------------------
void	CPcObj::UpdateNormalMove()
{
	mPos = XMMatrixTranslation(0.0f, 0.0f, 0.0f); // �o�b�̈ړ��}�g���b�N�X�̏�����
	m_fLocalRotY = 0;		
   if (frontFlag == true) {     // M.S ����(����\��)�ɂ���t���O��false
	 frontFlag = false;
   }
     VECTOR3 nowPosition = GetPositionVector(m_mWorld); // M.S �v���C�L�����̈ʒu
	 JudgeNowPcMap(nowPosition, false);                 // M.S �L����������ʂ𒲂ׂ�
     m_pGMain->m_pPcProc->lineMapNew(surfaceNum);       // M.S �}�b�v�z��������Ă���
	mPos = XMMatrixTranslation(0.0f, 0.0f, 0.0f);    	// ���R�����̏����l
	DoneMove = false;   	   // M.S 1���[�v���Ɉړ����������ǂ���������ϐ�
		// M.S �S�Ă̈ړ����������āA�z��ɍ��킹��������������
	MoveRight();   // M.S �L�����̉E�ړ�����   �������H�܂��͉w�̈ړ�
	MoveLeft();    // M.S �L�����̍��ړ�����
	MoveDown();    // M.S �L�����̉��ړ�����
	MoveUp();      // M.S �L�����̏�ړ�����	
	MoveUpRight();      // M.S �ォ��E�ړ� �����ϊ��X�C�b�`�̈ړ�   
	MoveUpLeft();       // M.S �ォ�獶�ړ�
	MoveDownRight();    // M.S ������E�ړ�
	MoveDownLeft();     // M.S �����獶�ړ�
	MoveRightUp();      // M.S �E�����ړ�
	MoveRightDown();    // M.S �E���牺�ړ�
	MoveLeftUp();       // M.S �������ړ�
	MoveLeftDown();     // M.S �����牺�ړ�
	if (DoneMove == false 
		&& m_pGMain->m_pEnmProc->m_pEnmGolemProc->managementDeadProcess == false
		&& m_pGMain->m_pEnmProc->m_pEnmGolemProc->managementDeadProcess == false
		&& m_pGMain->m_pEnmProc->m_pEnmGolemProc->managementDeadProcess == false
		&& edgeFlag == false) {
		UpdateDead();  // M.S 1���[�v���Ɉړ����Ă��Ȃ���ԏ������łȂ���΃Q�[���I�[�o�[
	}
	if (frontFlag == false) {
		m_pGMain->m_pPcProc->lineMapSet(surfaceNum);  // M.S ����(�����)�ɂ��Ȃ���΁A�����ʂ��X�V
	}
	if (m_fLocalRotY >= 360.0f) {  // ��]�̊p�x��360�x�𒴂��Ȃ��悤�ɂ���
		for (int i = 0; m_fLocalRotY >= 360.0f; i++) {
			m_fLocalRotY = m_fLocalRotY - 360.0f;
		}
	}
	MATRIX4X4 rotate = XMMatrixRotationY(XMConvertToRadians(m_fLocalRotY)); // �L�����̉�]�̌v�Z
	m_mWorld = mPos * rotate * m_mWorld;     // �L�������ړ�������
	// M.S �}�b�v�̖ʂ���ʂֈړ����鎞(�[�ɂ��Č������Ă�����������̖�)
	if (oldHP == 0 && trainDirectionFlag == 1 || oldHP == 9 && trainDirectionFlag == 3 
		|| oldVP == 9 && trainDirectionFlag == 2 || oldVP == 0 && trainDirectionFlag == 4) {
		// M.S ����ɐl�L���������Ȃ���Β[����ړ��̏������s��
		if (frontFlag == false && m_pGMain->m_pPcProc->lineMapSub[oldHP][oldVP] == 8 &&
			(m_pGMain->m_pPcProc->lineMapSub[oldHP + 1][oldVP] == 10 ||
				m_pGMain->m_pPcProc->lineMapSub[oldHP - 1][oldVP] == 10 ||
				m_pGMain->m_pPcProc->lineMapSub[oldHP][oldVP + 1] == 10 ||
				m_pGMain->m_pPcProc->lineMapSub[oldHP][oldVP - 1] == 10 )||
			frontFlag == true && m_pGMain->m_pMapProc->lineMap1[oldHP][oldVP] == 8 &&
			(m_pGMain->m_pMapProc->lineMap1[oldHP + 1][oldVP] == 10 ||
				m_pGMain->m_pMapProc->lineMap1[oldHP - 1][oldVP] == 10 ||
				m_pGMain->m_pMapProc->lineMap1[oldHP][oldVP + 1] == 10 ||
				m_pGMain->m_pMapProc->lineMap1[oldHP][oldVP - 1] == 10)){
		}
		else {
			if (edgeFlag == true) {    // M.S �[���玟�̖ʂւ̈ړ��t���O��true���ǂ���
				 nowPcPos = GetPositionVector(m_mWorld);  // M.S �L�����̈ʒu�̎擾
				 // M.S �v���C�L�����̂���ʂ̐����𒲂ׂ�
				 nowPcPosMap = JudgeNowPcMap(nowPcPos, false); 
				 // M.S �}�b�v�ʂ̉�]�𒲂ׂ�
				 nowNorth = m_pGMain->m_pPcProc->judgeDirection(nowPcPosMap, nowPcPos, 0);
				 SetEdgePos();    // M.S nowPcPosMap����ړ���̈ʒu�Ɖ�]�����߂�
				// M.S ���ݒn�̍X�V
				updateEdgeOldHV(trainDirectionFlag, oldHP, oldVP, nowPcPosMap);
				edgeFlag = false;  // M.S �[���玟�̖ʂւ̈ړ��t���O��false
				m_mWorld = newPcPos;   // M.S �v���C�L�����̈ʒu�̃Z�b�g
				// M.S �v���C�L�����̉�]�̃Z�b�g
				if (needRotateFlag == 1) {  
					m_mWorld = edgeRotate1 * m_mWorld; 
				}
				else if (needRotateFlag == 2) {
					m_mWorld = edgeRotate1 * edgeRotate2 * m_mWorld; 
				}
				// M.S �ړ���̃v���C�L�����̈ʒu�擾
				VECTOR3 nowPcPos2 = GetPositionVector(m_mWorld); 
				// M.S �ړ���̃v���C�L�����̂���ʂ̐����𒲂ׂ�
				m_pGMain->m_pPcProc->NewSurfaceNum = JudgeNowPcMap(nowPcPos2, false);
			}
		}
	}
	        // M.S �ړ��������I������̂ŉ�]�\�t���O��true
			m_pGMain->m_pPcProc->rotateOkFlag = true;  
}
//-----------------------------------------------------------------------------   // -- 2021.1.10
// �o�b�I�u�W�F�N�g�̈ړ������@�L�[���얈�̊e��ړ�����
//
//   �����@DWORD Key �L�[��ʁ@DirectInput�̃L�[�R�[�h
//
//   �߂�l  �ړ��}�g���b�N�X
//-----------------------------------------------------------------------------
MATRIX4X4 CPcObj::UpdateNormalMoveKeystate(DWORD DIKey)
{
	MATRIX4X4 mPos;
	
	if (m_AnimStatus.animNum == 0) m_AnimStatus.SetNum(1);
	if (m_AnimStatus.isEnd(1))     m_AnimStatus.SetNum(2);

	if (m_bSide && DIKey != DIK_W)   // �T�C�h���[�h�őO�i�ȊO�̂Ƃ�
	{
		switch (DIKey)
		{
		case DIK_S:    // ���
			// ������ς����Ɍ��
			mPos = XMMatrixTranslation(0.0f, m_fJumpY, -m_fSpeed);
			break;
		case DIK_D:    // �E
			// ������ς����ɉE�ړ�
			mPos = XMMatrixTranslation(m_fSpeed, m_fJumpY, 0.0f);
			break;
		case DIK_A:    // ��
			// ������ς����ɍ��ړ�
			mPos = XMMatrixTranslation(-m_fSpeed, m_fJumpY, 0.0f);
			break;
		}
	}
	else {
		// �i�s�����ɉ�]���Ă���O�i

		// ���[�g�{�[���A�j���[�V�������s�����ǂ������[�g�A�j���[�V�����^�C�v���m�F����
		if (m_pMesh->GetRootAnimType(m_AnimStatus.animNum) == eRootAnimNone)
		{
			// ���[�g�{�[���A�j���[�V�������s�킸�Œ�̑O�i�ړ��l
			mPos = XMMatrixTranslation(0.0f, m_fJumpY, m_fSpeed);
		}
		else {
			// ���[�g�{�[���A�j���[�V�����ł̑O�i�ړ��l
			mPos = XMMatrixTranslation(0.0f, m_fJumpY, 0.0f) * m_pMesh->GetRootAnimUpMatrices(m_AnimStatus);
		}

		// �i�s�����ɉ�]���鏈��
		// �E��]�p�x��m_vRotUp.y�ɂ���B-180�`180�x
		// �E�P��̉�]���x��m_fRotSpeed
		if (m_vRotUp.y > 180.0f)  m_vRotUp.y -= 360.0f;
		if (m_vRotUp.y < -180.0f) m_vRotUp.y += 360.0f;

		float fAngle;  // �ڕW��]�p�x
		switch (DIKey)
		{
		case DIK_W:    // �O�i
			fAngle = 0.0f;
			break;
		case DIK_S:    // ���
			if (m_vRotUp.y >= 0)  // �ŏ���]�ɂȂ�悤�ɕ��������킹��
			{
				fAngle = 180.0f;
			}
			else {
				fAngle = -180.0f;
			}
			break;
		case DIK_D:    // �E
			fAngle = 90.0f;
			if (m_vRotUp.y == -180.0f) m_vRotUp.y = 180.0f;  // �ŏ���]�ɂȂ�悤�ɕ��������킹��
			break;
		case DIK_A:    // ��
			fAngle = -90.0f;
			if (m_vRotUp.y == 180.0f) m_vRotUp.y = -180.0f;  // �ŏ���]�ɂȂ�悤�ɕ��������킹��
			break;
		}
	}
	return mPos;
}
//-----------------------------------------------------------------------------   // -- 2019.3.5
// �o�b�I�u�W�F�N�g�̍U������
//
//�@�L�[�{�[�h�^�}�E�X�ło�b�̍U���������s��
//
//
//   �����@�Ȃ�
//
//-----------------------------------------------------------------------------
void	CPcObj::UpdateNormalAttack()
{
}
//-----------------------------------------------------------------------------   // -- 2019.3.5
// �o�b�I�u�W�F�N�g�̍X�V �_���[�W��ԁiDAMAGE�j
//
//�@�_���[�W���󂯂��Ƃ��̏���
//
//
//   �����@�Ȃ�
//
//-----------------------------------------------------------------------------
void	CPcObj::UpdateDamage()
{
	MATRIX4X4 mTemp;
	const int nDeadTime = 200;    // ���S����
	const int nFlashTime = 5;      // ���G��Ԃ̎���

	m_pGMain->m_pBackForeProc->GetSprite()->DrawRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, RGB(255, 255, 255), 1.0f); // ��ʂ���u�����t���b�V��

	mTemp = XMMatrixTranslation(0, 0, -0.25f);	// �o�b�N����
	m_mWorld = mTemp * m_mWorld;

	m_nHp -= m_pHitObj->GetAtc();	// �U�����󂯂��_���[�W
	if (m_nHp <= 0)		// HP���O�Ȃ̂Ŏ��S��
	{
		m_nHp = 0;
		m_dwStatus = DEAD;		// HP���O�Ȃ̂Ŏ��S��
		m_AnimStatus.SetNum(4);	// ���S���[�V�����ɂ���
		m_nCnt1 = nDeadTime;			// ���S���Ԃ̐ݒ�
	}
	else {
		m_nCnt1 = nFlashTime;   // ���G��Ԃ̎���
		m_dwStatus = FLASH;     // �_���[�W����̕��A�������s��
	}
}
//-----------------------------------------------------------------------------   // -- 2019.3.5
// �o�b�I�u�W�F�N�g�̍X�V ���S��ԁiDEAD�j
//
//�@���S��Ԃ̂Ƃ��̏���
//
//
//   �����@�Ȃ�
//
//-----------------------------------------------------------------------------
void	CPcObj::UpdateDead()
{
	// M.S �Q�[���̏������X�g�b�v������stopOperation��true
	m_pGMain->stopOperation = true;
	if (gameOverAnim == 0) {	// M.S �Q�[���I�[�o�[�̃A�j���t�F�[�Y��0�Ȃ��
		gameOverAnim = 1;       // M.S �Q�[���I�[�o�[�̃A�j���t�F�[�Y��1����
		m_AnimStatus.SetNum(3); // M.S �Q�[���I�[�o�[�̉�]�A�j���[�V�����𔭐�		
	}
	else if(gameOverAnim == 1){  // M.S �Q�[���I�[�o�[�̃A�j���t�F�[�Y��1�Ȃ��
		animCount--;             // M.S �A�j���[�V�����J�E���g������
		// M.S animCount��0�ȉ��Ȃ��(�Q�[���I�[�o�[�̉�]�A�j���[�V�������I��������)
		if (animCount <= 0) { 
			gameOverAnim = 2; // M.S �Q�[���I�[�o�[�A�j���t�F�[�Y��2�ɂ���  
			m_AnimStatus.SetNum(4);  // M.S �Q�[���I�[�o�[�̓]���A�j���[�V�����𔭐�
		}
	}
	// M.S �Q�[���I�[�o�[�̓]���A�j���[�V�������I���A
	// M.S �Q�[���I�[�o�[�A�j���t�F�[�Y��2�Ȃ��
	if (m_AnimStatus.isEnd(4) && gameOverAnim == 2)  
	{
		m_AnimStatus.playAnim = false;	// �A�j���[�V�������~�߂�
		m_AnimStatus.animFrame = m_AnimStatus.endFrame - 1; // �t���[���G���h�̈��O�ɂ���
		gameOverAnim = 3;	// M.S �Q�[���I�[�o�[�A�j���t�F�[�Y��3�ɂ���
	}
	if (gameOverAnim == 3) // M.S �Q�[���I�[�o�[�A�j���t�F�[�Y��3�Ȃ��
	{
		--gameOverTime;    // M.S gameOverTime������
		if (gameOverTime <= 0) {   // M.S gameOverTime��0�ȉ��Ȃ��
			m_pGMain->m_pPcProc->oneScreenFlag = true;  // M.S 1�ʂ̂ݕ`��t���O��true
			m_pGMain->m_dwGameStatus = GAMEOVER;	// �Q�[���I�[�o�[��
			gameOverAnim = 0;                       // M.S �Q�[���I�[�o�[�A�j���t�F�[�Y��0�ɖ߂�          
		}
	}
}
