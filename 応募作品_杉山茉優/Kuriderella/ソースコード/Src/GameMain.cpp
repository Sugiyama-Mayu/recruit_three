//=============================================================================
//		�Q�c�A�N�V�����Q�[���v���O����
//		�b�Q�c�`�����P�P�S�@�@�@�@�@�@           ver 2.8        2020.2.15
//
//		�Q�[�����C������
//																GameMain.cpp
//=============================================================================

#include <stdio.h>
#include <string>

#include "GameMain.h"
#include "Playchar.h"
#include "Enemy.h"
#include "Weapon.h"
#include "Effect.h"
#include "BackFore.h"
#include "Map.h"
#include "Title.h"

//------------------------------------------------------------------------
//
//	�Q�[�����C���N���X�̃R���X�g���N�^	
//
//  �����@CMain*	pMain
//
//------------------------------------------------------------------------
CGameMain::CGameMain(CMain*	pMain)
{
	ZeroMemory(this, sizeof(CGameMain));
	m_pMain = pMain;
}
//------------------------------------------------------------------------
//
//	�Q�[�����C���N���X�̃f�X�g���N�^	
//
//------------------------------------------------------------------------
CGameMain::~CGameMain()
{

	SAFE_DELETE(m_pTitleProc);
	SAFE_DELETE(m_pMapProc);
	SAFE_DELETE(m_pForeProc);
	SAFE_DELETE(m_pEffectProc);
	SAFE_DELETE(m_pWeaponProc);
	SAFE_DELETE(m_pEnmProc);
	SAFE_DELETE(m_pPcProc);

	SAFE_DELETE(m_pSePower);
	SAFE_DELETE(m_pSeShot);
	SAFE_DELETE(m_pSeHit);
	SAFE_DELETE(m_pBgm1);

	SAFE_DELETE(m_pImageChar);
	SAFE_DELETE(m_pImageSprite);

	SAFE_DELETE(m_pShader);
	SAFE_DELETE(m_pFont);
	SAFE_DELETE(m_pDI);
	SAFE_DELETE(m_pXAudio);
	SAFE_DELETE(m_pD3D);

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

	// �t�H���g���X�v���C�g�p�̃V�F�[�_�[�̃Z�b�g
	// �ŏ���1�񂾂��V�F�[�_�[�̃Z�b�g������B�r���ŃV�F�[�_�[�̕ύX�͂Ȃ����߁B
	m_pFont->SetShader();

	// ----------------------------------------------------------------------------------------
	// �X�v���C�g�C���[�W�̃��[�h
	m_pImageOrange = new CSpriteImage(m_pShader, _T("Data/Image/�I�����W�g �E�B���h�E.png")); // ���j���[��ʂ̃��[�h
	m_pImageChar   = new CSpriteImage(m_pShader, _T("Data/Image/�X�v���C�g�V�[�g �L�����N�^�[Y.png"));   // �L�����N�^�[�C���[�W�̃��[�h
	m_pImageSprite = new CSpriteImage(m_pShader, _T("Data/Image/�A�C�e���X�v���C�g2.png")); // �X�v���C�g�C���[�W�̃��[�h
	m_pImageSpriteS = new CSpriteImage(m_pShader, _T("Data/Image/�A�C�e���X�v���C�g3.png"));
	m_pImageSpriteV = new CSpriteImage(m_pShader, _T("Data/Image/�A�C�e���X�v���C�g4.png"));
	m_pImageChestHeart = new CSpriteImage(m_pShader, _T("Data/Image/����Ƃ́[��.png"));  // HPMP�c�@�̃C���[�W�̕\��
	m_pWeaponImage = new CSpriteImage(m_pShader, _T("Data/Image/�e �X�v���C�g.png")); // �e�̃C���[�W�̃��[�h
	m_pImageRank = new CSpriteImage(m_pShader, _T("Data/Image/rank.png"));  // �����N�̘g

	// �v���V�[�W���̏�����
	m_pPcProc   = new CPcProc(this);
	m_pEnmProc  = new CEnmProc(this);
	m_pWeaponProc  = new CWeaponProc(this);
	m_pEffectProc  = new CEffectProc(this);
	m_pForeProc = new CForeProc(this);
	m_pMapProc  = new CMapProc(this);
	m_pTitleProc = new CTitleProc(this);

	// �T�E���h
	m_pSePower = new CXAudioSource(m_pXAudio, _T("Data/Sound/PowerUp2.wav"));
	m_pSeHit = new CXAudioSource(m_pXAudio, _T("Data/Sound/Damage.wav"), 5);
	m_pSeShot = new CXAudioSource(m_pXAudio, _T("Data/Sound/MainShot.wav"), 10);
	m_pBgm1 = new CXAudioSource(m_pXAudio, _T("Data/Sound/bgm.mp3"));

	// �Q�[���ϐ��̏�����
	m_dwGameStatus = TITLE;
	// �X�N���[�����W�̏�����
	m_vScroll = VECTOR2(0, 0);

	return S_OK;
}

//------------------------------------------------------------------------
//
//	�A�v���P�[�V�����̃��C�����[�v����	
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
	time += 1;
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

	//��ʍX�V�i�o�b�N�o�b�t�@���t�����g�o�b�t�@�Ɂj
	m_pD3D->m_pSwapChain->Present(0, 0);
}
//M.S �����̊e�X�e�[�W�ł̃R�����g�e�L�X�g�̕\��
//��  ���F�Ȃ�
//�߂�l�F�Ȃ�
void CGameMain::DrawSkyText() {
	if (ints == 1) { // �X�e�[�W1
		m_pFont->Draw(200, 140, _T("�u�X�C�N�v"), 48, RGB(255, 215, 0),
			1.0f, _T("���C���I"));
		m_pFont->Draw(200, 190, _T("�΂̃G�l�~�[�ɓ������āA�C�K���Ƃ낤�I"), 48, RGB(32, 178, 170),
			1.0f, _T("���C���I"));
	}
	if (ints == 2) { // �X�e�[�W2
		m_pFont->Draw(200, 140, _T("�u�X�C�N�v"), 48, RGB(255, 215, 0),
			1.0f, _T("���C���I"));
		m_pFont->Draw(200, 190, _T("�����ɓ������āA�ς悤�I"), 48, RGB(32, 178, 170),
			1.0f, _T("���C���I"));
	}
	if (ints == 3) { // �X�e�[�W3
		m_pFont->Draw(200, 140, _T("�u�X�C�N�v"), 48, RGB(255, 215, 0),
			1.0f, _T("���C���I"));
		m_pFont->Draw(200, 190, _T("���X�{�X���I�S���|���Ȃ��Ă�������I"), 48, RGB(32, 178, 170),
			1.0f, _T("���C���I"));
	}
	if (ints == 4) { // �X�e�[�WSP
		m_pFont->Draw(200, 140, _T("�u�X�C�N�v"), 48, RGB(255, 215, 0),
			1.0f, _T("���C���I"));
		m_pFont->Draw(200, 190, _T("SP�X�e�[�W����I"), 48, RGB(32, 178, 170),
			1.0f, _T("���C���I"));
	}
	if (ints == 5) { // ���틭���X�e�[�W
		m_pFont->Draw(200, 140, _T("�u�X�C�N�v"), 48, RGB(255, 215, 0),
			1.0f, _T("���C���I"));
		m_pFont->Draw(200, 190, _T("���틭���`�����X����I"), 48, RGB(32, 178, 170),
			1.0f, _T("���C���I"));
	}
}
//M.S ���j���[�e�L�X�g�̕\��
//��  ���F�Ȃ�
//�߂�l�F�Ȃ�
void CGameMain::DrawMenuText() {
	m_pOrangeM = new CSprite(m_pImageOrange, 0, 0, 800, 500);
	m_pOrangeM->Draw(0, 0);

	if (henk == 1) {  // �h�b�X���̓G�ƐڐG�������ǂ���
		m_pFont->Draw(600, 140, _T(":��"), 48, RGB(255, 99, 71),
			1.0f, _T("���C���I"));
	}

	if (hank == 1) {  // ���̓G�ƐڐG�������ǂ���
		m_pFont->Draw(600, 190, _T(":��"), 48, RGB(255, 99, 71),
			1.0f, _T("���C���I"));
	}

	_stprintf(str, _T("%d"), SilverS);  // �┓�̐�
	m_pFont->Draw(500, 310, str, 48, RGB(165, 42, 42));

	_stprintf(str, _T("%d"), GoldS);    // �����̐�
	m_pFont->Draw(500, 360, str, 48, RGB(165, 42, 42));

	_stprintf(str, _T("%d"), VisionS);  // ���̍����̐�
	m_pFont->Draw(500, 410, str, 48, RGB(165, 42, 42));
}
//M.S ����̋�������e�L�X�g�̕\��
//��  ���F�Ȃ�
//�߂�l�F�Ȃ�
void CGameMain::DrawWeaponTradingText() {
	if (transactionW == true) { 
		if (textStr == 0) {      // �ŏ��̃R�����g
			m_pFont->Draw(200, 100, _T("�������킪�~�����̂Ȃ�΁A"), 40, RGB(240, 230, 140),
				1.0f, _T("���C���I"));

			m_pFont->Draw(200, 150, _T("���ς�:�P,��ς�:�T �킽���̂���"), 40, RGB(240, 230, 140),
				1.0f, _T("���C���I"));

			m_pFont->Draw(200, 200, _T("����ɏ]���FE�L�["), 40, RGB(240, 230, 140),
				1.0f, _T("���C���I"));
		}
		else if (textStr == 1) {  // ������������̃R�����g
			m_pFont->Draw(200, 100, _T("���x���肶��"), 40, RGB(240, 230, 140),
				1.0f, _T("���C���I"));

		}
		else if (textStr == 2) {  // �A�C�e�������肸������ł��Ȃ����̃R�����g
			m_pFont->Draw(200, 100, _T("����Ȃ��̂���"), 40, RGB(240, 230, 140),
				1.0f, _T("���C���I"));
		}
	}
}
//M.S �������Ԃ̌v�Z
//��  ���F�Ȃ�
//�߂�l�F�Ȃ�
void CGameMain::CountGameTime() {
	int time2 = 200;         // Max��������
	int time1 = time / 100;
	timeSum = time2 - time1; // �c��̐������Ԃ��o��
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
	float ClearColor[4] = { 0,0,1,1 };// �N���A�F�쐬�@RGBA�̏�
	m_pD3D->ClearRenderTarget(ClearColor); // ��ʃN���A

	// �v���V�[�W���̍X�V
	m_pMapProc->Update();		// �}�b�v�v���V�[�W���̍X�V
	m_pEffectProc->UpdateAll();	// �f�����ʃv���V�[�W���̍X�V
	m_pEnmProc->UpdateAll();	// �G�v���V�[�W���̍X�V
	m_pPcProc->UpdateAll();		// �o�b�v���V�[�W���̍X�V

	m_pWeaponProc->UpdateAll();	// ����v���V�[�W���̍X�V


	m_pMapProc->Update2();		// �}�b�v�v���V�[�W���̍X�V2
	m_pForeProc->Update();		// �O�i�v���V�[�W���̍X�V	

	DrawSkyText();   //M.S �����̊e�X�e�[�W�ł̃R�����g�e�L�X�g�̕\��
	DrawWeaponTradingText();  //M.S ���j���[�e�L�X�g�̕\��	

	// �L�[���������ۂ̃��j���[(���V�s)�\��
	if (m_pDI->CheckKey(KD_DAT, DIK_Q)) 
	{	
		DrawMenuText();  // M.S ����̋�������e�L�X�g�̕\��
	}
	CountGameTime();     // M.S �c�萧�����Ԃ��o��
	if (timeSum <= 0) {  // M.S �������Ԃ�0�ȉ��ɂȂ�����Q�[���I�[�o�[
		m_pTitleProc->GameOver();
	}
	else {
		_stprintf(str, _T("%03d"), timeSum);   // M.S ���ԕ\��
		m_pFont->Draw(1010, 15, str, 48, RGB(255, 51, 0));  
	}
	//��ʍX�V�i�o�b�N�o�b�t�@���t�����g�o�b�t�@�Ɂj
	m_pD3D->m_pSwapChain->Present(0, 0);
}
//M.S �Q�[���N���A�̃X�R�A����
//��  ���F�Ȃ�
//�߂�l�F�Ȃ�
void CGameMain::CalculateScore() {
	// �A�C�e���̃X�R�A���o��
	int SilverSum = 30 * SilverS;  // �┓
	int GoldSum = 100 * GoldS;     // ����
	int VisionSum = 200 * VisionS; // ���̍���
	CountGameTime();   // �Q�[���N���A���̎c�萧�����Ԃ��o��
	SumP = SilverSum + GoldSum + VisionSum + timeSum;   // ���v�X�R�A�̌v�Z
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

