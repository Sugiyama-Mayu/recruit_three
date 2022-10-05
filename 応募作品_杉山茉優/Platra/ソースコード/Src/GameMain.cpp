//=============================================================================
//		�R�c�Q�[���v���O����
//		�b�R�c�`�����P�P�Q�@�@�@�@�@�@                 ver 3.0        2021.1.11
//
//		�Q�[���̃��C������
//																GameMain.cpp
//=============================================================================
#include "GameMain.h"
#include "Playchar.h"
#include "Camera.h"
#include "Enemy.h"
#include "Map.h"
#include "Weapon.h"
#include "Effect.h"
#include "BackFore.h"
#include "Title.h"

// ============================================================================================
//
// CGameMain �Q�[�����C���N���X�̏���
//
// ============================================================================================
//------------------------------------------------------------------------
//
//	�Q�[�����C���N���X�̃R���X�g���N�^	
//
//  �����@�Ȃ�
//
//------------------------------------------------------------------------
CGameMain::CGameMain(CMain*	pMain)
{
	ZeroMemory(this, sizeof(CGameMain));
	m_pMain = pMain;
	m_dwGameMode = 0;
	
	continuationFlag = false;   // M.S �Z�[�u�f�[�^�����邩�ǂ����t���O
	// M.S �J�[�\���̈ʒu
	cursolX = 0;
	cursolY = 0;
	// M.S ��]�̏������s��ꂽ�t���O
	rotateFlag = false;
	transparentSwitch = false;   // M.S �v���C�L�����̓��������̔���
	initialH = 4;          // M.S �v���C�L�����̃}�X�̏����l(�c)
	initialV = 4;          // M.S �v���C�L�����̃}�X�̏����l(��)
	lineTrainSelectNum = 30;  // M.S �v���O�����Ŏg�p������H��
	passengersSelectNum = 0;  // M.S �v���O�����Ŏg�p�����Ԑl��
	waitingTimeSelectNum = 0; // M.S �v���O�����Ŏg�p����҂�����
	bgmSelectNum = 0;  // M.S �v���O�����Ŏg�p����BGM����
	seSelectNum = 0;   // M.S �v���O�����Ŏg�p����SE����
	traveledStar = 0;    // M.S �s�������̐�
	haveToGoStar = 0;    // M.S �s���Ȃ���΂Ȃ�Ȃ����̐�
	redMan = 0;    // M.S �t�@�C���ǂݍ��݁A�����o���Ɏg�p����l��(��)
	yellowMan = 0; // M.S �t�@�C���ǂݍ��݁A�����o���Ɏg�p����l��(��)
	blueMan = 0;   // M.S �t�@�C���ǂݍ��݁A�����o���Ɏg�p����l��(��)
	rankOne = 1;   // M.S �t�@�C���ǂݍ��݁A�����o���Ɏg�p����1�ʂ̃X�R�A��
	rankTwo = 2;   // M.S �t�@�C���ǂݍ��݁A�����o���Ɏg�p����2�ʂ̃X�R�A��
	rankThree = 3; // M.S �t�@�C���ǂݍ��݁A�����o���Ɏg�p����3�ʂ̃X�R�A��
	rankFour = 4;  // M.S �t�@�C���ǂݍ��݁A�����o���Ɏg�p����4�ʂ̃X�R�A��
	rankFive = 5;  // M.S �t�@�C���ǂݍ��݁A�����o���Ɏg�p����5�ʂ̃X�R�A��
	stopOperation = false;  // M.S �Q�[���̏������~�߂�t���O

	rankLineTrainSelectNum = 0;   // M.S �����L���O���[�h���g�p������H��
	rankPassengersSelectNum = 0;  // M.S �����L���O���[�h���g�p�����Ԑl��
	rankWaitingTimeSelectNum = 0; // M.S �����L���O���[�h���g�p����҂�����
	rankTraveledStar = 0; // M.S �����L���O���[�h���g�p����s�������̐�
	rankHaveToGoStar = 0; // M.S �����L���O���[�h���g�p����s���Ȃ���΂Ȃ�Ȃ����̐�
	rankRedMan = 0;    // M.S �����L���O���[�h���g�p����l��(��)
	rankYellowMan = 0; // M.S �����L���O���[�h���g�p����l��(��)
	rankBlueMan = 0;   // M.S �����L���O���[�h���g�p����l��(��)
}
//------------------------------------------------------------------------
//
//	�Q�[�����C���N���X�̃f�X�g���N�^	
//
//------------------------------------------------------------------------
CGameMain::~CGameMain()
{
	MyImgui::ImguiQuit();          // -- 2020.11.15    // MyImgui�̏I������

	SAFE_DELETE(titleBgm);
	SAFE_DELETE(gameBgm);
	SAFE_DELETE(gameClearBgm);
	SAFE_DELETE(resultBgm);
	SAFE_DELETE(gameOverBgm);

	SAFE_DELETE(turnThePageSound);
	SAFE_DELETE(selectSound);
	SAFE_DELETE(saveWarningSound);
	SAFE_DELETE(bornStarSound);
	SAFE_DELETE(goSound);
	SAFE_DELETE(timeCountSound);
	SAFE_DELETE(lineChangeSound);
	SAFE_DELETE(linePlacementSound);
	SAFE_DELETE(rideSound);
	SAFE_DELETE(saveOkSound);
	SAFE_DELETE(nextStarOkSound);
	
	SAFE_DELETE(m_pEnmProc);
	SAFE_DELETE(m_pPcProc);
	SAFE_DELETE(m_pCameraProc);
	SAFE_DELETE(m_pMapProc);
	SAFE_DELETE(m_pWeaponProc);
	SAFE_DELETE(m_pEffectProc);
	SAFE_DELETE(m_pBackForeProc);
	SAFE_DELETE(m_pTitleProc);

	SAFE_DELETE(m_pFbxMeshCtrl);    // -- 2021.2.4
	SAFE_DELETE(m_pShader);
	SAFE_DELETE(m_pFont);
	SAFE_DELETE(m_pDI);
	SAFE_DELETE(m_pXAudio);
	SAFE_DELETE(m_pD3D);

	SAFE_DELETE(m_pBox);

	CoUninitialize();   // COM�̉��
}

//------------------------------------------------------------------------
//
//	�A�v���P�[�V�����̏���������	
//
//  �����@�Ȃ�
//
//	�߂�l HRESULT
//		S_OK	= ����
//		E_FAIL	= �ُ�
//
//------------------------------------------------------------------------
HRESULT CGameMain::Init()
{
	// �b�n�l�̏�����
	//CoInitializeEx(NULL, COINIT_MULTITHREADED);
	CoInitialize( NULL );

	// Direct3D�̏�����
	m_pD3D = new CDirect3D;
	if (FAILED(m_pD3D->InitD3D(m_pMain->m_hWnd, WINDOW_WIDTH, WINDOW_HEIGHT))) {
		MessageBox(0, _T("Direct3D���������o���܂���"), NULL, MB_OK);
		return E_FAIL;
	}
	m_pD3D->SetViewPort(false);   // M.S 1��ʂ̕\��
	// �V�F�[�_�[�̏�����
	m_pShader = new CShader(m_pD3D);
	if (FAILED(m_pShader->InitShader())) {
		MessageBox(0, _T("Shader�𐶐��E�������o���܂���"), NULL, MB_OK);
		return E_FAIL;
	}

	// XAudio2�̏�����
	m_pXAudio = new CXAudio;
	if (FAILED(m_pXAudio->InitAudio(m_pMain->m_hWnd))) {
		MessageBox(0, _T("XAudio2���������o���܂���"), NULL, MB_OK);
		return E_FAIL;
	}

	// DirectInput�̏�����
	m_pDI = new CDirectInput;
	if (FAILED(m_pDI->StartDirectInput(m_pMain->m_hInstance, m_pMain->m_hWnd, 
                    INIT_KEYBOARD | INIT_MOUSE | INIT_JOYSTICK, WINDOW_WIDTH, WINDOW_HEIGHT))) {
		MessageBox(0, _T("DirectInput���������o���܂���"), NULL, MB_OK);
		return E_FAIL;
	}

	// �t�H���g�e�N�X�`���[�̏�����
	m_pFont = new CFontTexture(m_pShader);

	// MyImgui�̏�����
	MyImgui::ImguiInit(m_pMain->m_hWnd, m_pD3D, WINDOW_WIDTH, WINDOW_HEIGHT);           // -- 2020.11.15

	// Fbx���b�V���R���g���[���N���X
	m_pFbxMeshCtrl = new CFbxMeshCtrl(m_pShader);                       // -- 2021.2.4

	// ----------------------------------------------------------------------------------------
	// �ϐ��̏�����
	m_dwGameStatus = TITLE;
	m_vLightDir = normalize( VECTOR3(0.8f, 1, -1) );  // �������W�̏����l�B���K������

	// �v���W�F�N�V�����g�����X�t�H�[���i�ˉe�ϊ��j�̏����l
	//m_mProj = XMMatrixPerspectiveFovLH((FLOAT)(XM_PI / 4), (FLOAT)WINDOW_WIDTH / (FLOAT)WINDOW_HEIGHT, 0.1f, 1000.0);
	m_mProj = XMMatrixPerspectiveFovLH(XMConvertToRadians(38.0f), (FLOAT)WINDOW_WIDTH / (FLOAT)WINDOW_HEIGHT, 0.1f, 1000.0);

	// �r���[�g�����X�t�H�[���i���_���W�ϊ��j�̏����l
	VECTOR3 vUpVec(0.0f, 1.0f, 0.0f); //����ʒu
	m_vEyePt = VECTOR3(0.0f, 1.0f, 0.0f);
	m_vLookatPt = VECTOR3(0.0f, 1.0f, 1.0f);
	m_mView = XMMatrixLookAtLH(m_vEyePt, m_vLookatPt, vUpVec);

	// �e�v���V�[�W���̏�����
	m_pPcProc = new CPcProc(this);		// �o�b�v���V�[�W��

	m_pCameraProc = new CCameraProc(this);	// �J�����v���V�[�W��

	m_pEnmProc = new CEnmProc(this);	// �G�v���V�[�W��

	m_pEffectProc = new CEffectProc(this);  // �R�c����

	m_pWeaponProc = new CWeaponProc(this);	// Weapon�v���V�[�W��

	m_pMapProc = new CMapProc(this);	// Map�v���V�[�W��

	m_pBackForeProc = new CBackForeProc(this);  // �O�i�E�w�i

	m_pTitleProc = new CTitleProc(this);  // �^�C�g���B�Q�[���N�����[�B�Q�[���I�[�o�[

	// M.S �v���g����BGM�T�E���h
	titleBgm = new CXAudioSource(m_pXAudio, _T("Data/PlatraSounds/startScene.mp3"));
	gameBgm = new CXAudioSource(m_pXAudio, _T("Data/PlatraSounds/game.mp3"));
	gameClearBgm = new CXAudioSource(m_pXAudio, _T("Data/PlatraSounds/gameClear.mp3"));
	resultBgm = new CXAudioSource(m_pXAudio, _T("Data/PlatraSounds/result.mp3"));
	gameOverBgm = new CXAudioSource(m_pXAudio, _T("Data/PlatraSounds/gameOver.mp3"));
	// M.S �v���g����SE�T�E���h
	turnThePageSound = new CXAudioSource(m_pXAudio, _T("Data/PlatraSounds/turnThePage.mp3"));
	selectSound = new CXAudioSource(m_pXAudio, _T("Data/PlatraSounds/selectButton.wav"));
	saveWarningSound = new CXAudioSource(m_pXAudio, _T("Data/PlatraSounds/saveWarning.wav"));
	bornStarSound = new CXAudioSource(m_pXAudio, _T("Data/PlatraSounds/starBorn.mp3"));
	goSound = new CXAudioSource(m_pXAudio, _T("Data/PlatraSounds/goButton.wav"));
	timeCountSound = new CXAudioSource(m_pXAudio, _T("Data/PlatraSounds/timeCount.wav"));
	lineChangeSound = new CXAudioSource(m_pXAudio, _T("Data/PlatraSounds/lineSelectButton.mp3"));
	linePlacementSound = new CXAudioSource(m_pXAudio, _T("Data/PlatraSounds/placement.wav"));
	rideSound = new CXAudioSource(m_pXAudio, _T("Data/PlatraSounds/ride.wav"));
	saveOkSound = new CXAudioSource(m_pXAudio, _T("Data/PlatraSounds/saveOk.wav"));
	nextStarOkSound = new CXAudioSource(m_pXAudio, _T("Data/PlatraSounds/nextStarOk.mp3"));
	FileRead();  // M.S �t�@�C���̓ǂݍ���
	// M.S �Z�[�u�f�[�^�����邩�ǂ���
	for (int i = 0; i < 25; i++) {
		if (starArray[i] != 0) {
			continuationFlag = true; 
			break;
		}
		else {
			continuationFlag = false;
		}
	}
	m_pTitleProc->ChangeSelect(); // M.S �I�v�V������ʂŎg�������֕ϊ�
	titleBgm->Play(AUDIO_LOOP);   // M.S ���y�Đ�
	// M.S �ǂݍ��񂾃t�@�C�����特���̃{�����[����ݒ�
	SetSoundVolume();
	SetBgmVolume();
	return S_OK;
}

//------------------------------------------------------------------------
//
//	�Q�[���̃��[�v����	
//
//  �����@�Ȃ�
//
//	�߂�l �Ȃ�
//
//------------------------------------------------------------------------
void CGameMain::Loop()
{
	m_pDI->GetInput();			// ���͏��̎擾
	m_pFont->Refresh();         // �t�H���g���̃��t���b�V��
	MyImgui::ImguiNewFrame();   // MyImgui�`��O����    // -- 2020.11.15
	if (m_pDI->CheckKey(KD_TRG, DIK_F4))  ChangeScreenMode();   // �t���X�N���[���̐؂�ւ�       // -- 2018.12.14

	switch (m_dwGameStatus)
	{
	case TITLE:				// �Q�[���J�n�^�C�g��
		m_pTitleProc->Title();
		break;

	case GAMEMAIN:			// �Q�[���又��
		GameMain();
		break;

	case GAMECLEAR:			// �Q�[���N�����[����
		m_pTitleProc->GameClear();
		break;

	case GAMEOVER:			// �Q�[���I�[�o�[����
		m_pTitleProc->GameOver();
		break;

	case GAMEEND:			// �Q�[���I��
		PostQuitMessage(0);
		break;

	}

	MyImgui::ImguiRender();      // MyImgui���`�揈��    // -- 2020.11.15

	//��ʍX�V�i�o�b�N�o�b�t�@���t�����g�o�b�t�@�Ɂj
	//m_pD3D->m_pSwapChain->Present(1, 0);                   // 60fps Vsync
	m_pD3D->m_pSwapChain->Present(0, 0);                   // Vsync�Ȃ�
}

//------------------------------------------------------------------------
//
//	�Q�[���̃��C������	
//
//  �����@�Ȃ�
//
//	�߂�l �Ȃ�
//
//------------------------------------------------------------------------
void CGameMain::GameMain()
{
	//��ʃN���A�i���ۂ͒P�F�ŉ�ʂ�h��Ԃ������j
	float ClearColor[4] = { 0,0,0,1 };// �N���A�F�쐬�@RGBA�̏�
	m_pD3D->ClearRenderTarget(ClearColor); // ��ʃN���A
	m_pD3D->SetViewPort(false);     // M.S 1��ʂ̕\��
	// M.S �}�b�v�i���o�[�ɂ���ăJ�����̈ʒu�����߂�
	switch (m_pMapProc->MapNumGet()) {
	case 1:
		m_pCameraProc->GetCameraObjPtr()->cameraChangeSwitch = 0;
		break;
	case 2:
		m_pCameraProc->GetCameraObjPtr()->cameraChangeSwitch = 2;
		break;
	case 3:
		m_pCameraProc->GetCameraObjPtr()->cameraChangeSwitch = 3;
		break;
	}
	// M.S Camera�̍X�V
	m_pCameraProc->UpdateAll();
	// Map�̍X�V
	m_pMapProc->Update();
	// �o�b�̍X�V
	m_pPcProc->UpdateAll();
	// �G�̍X�V
	m_pEnmProc->UpdateAll();
	// ����̍X�V
	m_pWeaponProc->UpdateAll();
	// �R�c���ʂ̍X�V
	m_pEffectProc->UpdateAll();
	// Map�̕`��2
	// �������̃}�b�v�I�u�W�F�N�g��`�悷�邽�߁A�僋�[�v�̍Ō�Ɏ��s
	m_pMapProc->Render2();
	// �O�i�E�w�i�̍X�V
	m_pBackForeProc->Update();
	// M.S �}�b�v�i���o�[��2(���H�z�u���)����1��ʃt���O��false�̏ꍇ
	if (m_pMapProc->MapNumGet() == 2 && m_pPcProc->oneScreenFlag == false) {
		m_pD3D->SetViewPort(true);  // ������ʂ̕\��
		// M.S ������ʂ̕`��
		m_pCameraProc->GetCameraObjPtr()->cameraChangeSwitch = 1;
		m_pCameraProc->UpdateAll();
		// M.S Map�̕`��
		m_pMapProc->Render();
		m_pMapProc->Render2();
		m_pMapProc->TrainLST->RenderLine(m_pMapProc->trainNumSt, m_pMapProc->trainNumSd,
			m_pMapProc->trainNumCg, m_pMapProc->trainNumSta, this); // M.S ���H�̕`��
		// M.S �l�L����(��)�����Ɍ���
		for (int i = 0; i < m_pEnmProc->m_pEnmGolemProc->manNum; i++) {
			// M.S �A�j���[�V�������~�߂�
			m_pEnmProc->m_pEnmGolemProc->GetHighManObjPtr(i)->SetPlayAnimHigh(false);
			// M.S �l�L��������Ԃ��Ă��Ȃ����ǂ���
			if (m_pEnmProc->m_pEnmGolemProc->GetHighManObjPtr(i)->alive == true) {
				// M.S �l�L�����̕`��
				m_pEnmProc->m_pEnmGolemProc->GetHighManObjPtr(i)->DoRenderHigh();
			}
		}
		// M.S �l�L����(��)�����Ɍ���
		for (int i = 0; i < m_pEnmProc->m_pEnmRSProc->manNum; i++) {
			// M.S �A�j���[�V�������~�߂�
			m_pEnmProc->m_pEnmRSProc->GetMiddleManObjPtr(i)->SetPlayAnimMiddle(false);
			// M.S �l�L��������Ԃ��Ă��Ȃ����ǂ���
			if (m_pEnmProc->m_pEnmRSProc->GetMiddleManObjPtr(i)->alive == true) {
				// M.S �l�L�����̕`��
				m_pEnmProc->m_pEnmRSProc->GetMiddleManObjPtr(i)->DoRenderMiddle();
			}
		}
		// M.S �l�L����(��)�����Ɍ���
		for (int i = 0; i < m_pEnmProc->m_pEnmBdProc->manNum; i++) {
			// M.S �A�j���[�V�������~�߂�
			m_pEnmProc->m_pEnmBdProc->GetLowManObjPtr(i)->SetPlayAnimLow(false);
			// M.S �l�L��������Ԃ��Ă��Ȃ����ǂ���
			if (m_pEnmProc->m_pEnmBdProc->GetLowManObjPtr(i)->alive == true) {
				// M.S �l�L�����̕`��
				m_pEnmProc->m_pEnmBdProc->GetLowManObjPtr(i)->DoRenderLow();
			}
		}
		// M.S �l�L����(��)�����Ɍ���
		for (int i = 0; i < m_pEnmProc->m_pEnmGolemProc->manNum; i++) {
			// M.S �A�j���\�V�����̍ĊJ
			m_pEnmProc->m_pEnmGolemProc->GetHighManObjPtr(i)->SetPlayAnimHigh(true);
		}
		// M.S �l�L����(��)�����Ɍ���
		for (int i = 0; i < m_pEnmProc->m_pEnmRSProc->manNum; i++) {
			// M.S �A�j���\�V�����̍ĊJ
			m_pEnmProc->m_pEnmRSProc->GetMiddleManObjPtr(i)->SetPlayAnimMiddle(true);
		}
		// M.S �l�L����(��)�����Ɍ���
		for (int i = 0; i < m_pEnmProc->m_pEnmBdProc->manNum; i++) {
			// M.S �A�j���\�V�����̍ĊJ
			m_pEnmProc->m_pEnmBdProc->GetLowManObjPtr(i)->SetPlayAnimLow(true);
		}
		// M.S �o�b�̃A�j���[�V�������~�߂�
		m_pPcProc->GetPcObjPtr()->SetPlayAnim(false);
		// M.S �o�b�̕`��
		m_pPcProc->GetPcObjPtr()->DoRender();
		// M.S ���H�̃L���L���G�t�F�N�g�̕`��
		m_pEffectProc->m_pBillProc->Render();
		// M.S �o�b�̃A�j���[�V�������ĊJ
		m_pPcProc->GetPcObjPtr()->SetPlayAnim(true);
	}
}
//------------------------------------------------------------------------
//
//	�A�v���P�[�V�����̏I������	
//
//  �����@�Ȃ�
//
//	�߂�l �Ȃ�
//
//------------------------------------------------------------------------
void CGameMain::Quit()
{
	;
}
//------------------------------------------------------------------------    // -- 2018.12.14
//
//	�E�B���h�E���[�h�ƃt���X�N���[�����[�h��؂�ւ��鏈��	
//
//  �����@���[�h  0:�E�C���h�E���[�h�@1:�t���X�N���[���@-1:���[�h�؂�ւ��i�ȗ��l�j
//
//	�߂�l �Ȃ�
//
//------------------------------------------------------------------------
HRESULT CGameMain::ChangeScreenMode(int nMode)
{
	HRESULT Ret = S_OK;
	BOOL bFullScreen;  // �t���X�N���[�����[�h���H

	//	���݂̃X�N���[�����[�h�𓾂�
	m_pD3D->m_pSwapChain->GetFullscreenState(&bFullScreen, NULL);

	switch (nMode)
	{
	case 0:    // �E�C���h�E���[�h�ɂ���
		if( bFullScreen ) Ret = m_pD3D->m_pSwapChain->SetFullscreenState(false, NULL);
		break;
	case 1:    // �t���X�N���[�����[�h�ɂ���
		if( !bFullScreen ) Ret = m_pD3D->m_pSwapChain->SetFullscreenState(true, NULL);
		break;
	default:   // ���݂̃��[�h��؂�ւ���
		if (bFullScreen)
		{
			Ret = m_pD3D->m_pSwapChain->SetFullscreenState(false, NULL);
		}
		else {
			Ret = m_pD3D->m_pSwapChain->SetFullscreenState(true, NULL);
		}
	}

	return Ret;
}
//M.S �t�@�C���փf�[�^����������
//��  ���F�Ȃ�
//�߂�l�F�Ȃ�
void CGameMain::FileWrite() {
	// �����L���O���[�h�łȂ��A�}�b�v�i���o�[��3(���̉˂������)�������ꍇ
	if (m_dwGameMode != 3 && m_pMapProc->MapNumGet() == 3) {
		// �������ݗp�ϐ��Ɋe��Ԑl��������
		redMan = m_pEnmProc->getHighMan;
		yellowMan = m_pEnmProc->getMiddleMan;
		blueMan = m_pEnmProc->getLowMan;
	}
	// �������݃��[�h�Ńt�@�C�����J��
	dataFileWrite = fopen("gameData.txt", "w");
	// ���̐��܂ł̐��H���A��Ԑl���A�҂����ԁABGM���ʁASE���ʂ���������
	fprintf(dataFileWrite, "%d,%d,%d,%f,%f\n", lineTrainSelectNum, passengersSelectNum, waitingTimeSelectNum, 
		bgmSelectNum, seSelectNum);
	// �s���������A�s���Ȃ���΂Ȃ�Ȃ���������������
	fprintf(dataFileWrite, "%d,%d\n", traveledStar, haveToGoStar);
	// ���I�����������z�����������
	for (int i = 0; i < 25; i++) {
		if (i < 24) {
		fprintf(dataFileWrite, "%d,", starArray[i]);
		}
		else {
			// �Ō�͉��s������
			fprintf(dataFileWrite, "%d\n", starArray[i]);
		}
	}
	// �e�l�̏�Ԑl������������
	fprintf(dataFileWrite, "%d,%d,%d\n", redMan, yellowMan, blueMan);
	// �����L���O�X�R�A����������
	fprintf(dataFileWrite, "%d,%d,%d,%d,%d\n", rankOne, rankTwo, rankThree, rankFour, rankFive);
	fclose(dataFileWrite);  // �t�@�C�������
}
//M.S �t�@�C���̃f�[�^��ǂݍ���
//��  ���F�Ȃ�
//�߂�l�F�Ȃ�
void CGameMain::FileRead() {
	// �ǂݍ��݃��[�h�Ńt�@�C�����J��
	dataFileWrite = fopen("gameData.txt", "r");
	// ���̐��܂ł̐��H���A��Ԑl���A�҂����ԁABGM���ʁASE���ʂ�ǂݍ���
	fscanf(dataFileWrite, "%d,%d,%d,%f,%f", &lineTrainSelectNum, &passengersSelectNum, &waitingTimeSelectNum,
		&bgmSelectNum, &seSelectNum);
	// �s���������A�s���Ȃ���΂Ȃ�Ȃ�������ǂݍ���
	fscanf(dataFileWrite, "%d,%d", &traveledStar, &haveToGoStar);
	// ���I�����������z���ǂݍ���
	fscanf(dataFileWrite, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
		&starArray[0], &starArray[1], &starArray[2], &starArray[3], &starArray[4], &starArray[5], &starArray[6],
		&starArray[7], &starArray[8], &starArray[9], &starArray[10], &starArray[11], &starArray[12], &starArray[13],
		&starArray[14], &starArray[15], &starArray[16], &starArray[17], &starArray[18], &starArray[19], &starArray[20],
		&starArray[21], &starArray[22], &starArray[23], &starArray[24]);
	// �e�l�̏�Ԑl����ǂݍ���
	fscanf(dataFileWrite, "%d,%d,%d", &redMan, &yellowMan, &blueMan);
	// �����L���O�X�R�A��ǂݍ���
	fscanf(dataFileWrite, "%d,%d,%d,%d,%d", &rankOne, &rankTwo, &rankThree, &rankFour, &rankFive);
	fclose(dataFileWrite);  // �t�@�C�������
}
//M.S ���ʉ��ɉ��ʂ�ݒ�
//��  ���F�Ȃ�
//�߂�l�F�Ȃ�
void  CGameMain::SetSoundVolume() {
	// ���ʉ��ɉ��ʂ�ݒ�
    selectSound->Volume(seSelectNum);
	turnThePageSound->Volume(seSelectNum);
	saveWarningSound->Volume(seSelectNum);
	bornStarSound->Volume(seSelectNum);
	goSound->Volume(seSelectNum);
	timeCountSound->Volume(seSelectNum);
	lineChangeSound->Volume(seSelectNum);
	linePlacementSound->Volume(seSelectNum);
	rideSound->Volume(seSelectNum);
	saveOkSound->Volume(seSelectNum);
	nextStarOkSound->Volume(seSelectNum);
}
//M.S BGM�ɉ��ʂ�ݒ�
//��  ���F�Ȃ�
//�߂�l�F�Ȃ�
void  CGameMain::SetBgmVolume() {
	// BGM�ɉ��ʂ�ݒ�
	titleBgm->Volume(bgmSelectNum);
	gameBgm->Volume(bgmSelectNum);
	gameClearBgm->Volume(bgmSelectNum);
	resultBgm->Volume(bgmSelectNum);
	gameOverBgm->Volume(bgmSelectNum);
}