//=============================================================================
//		�R�c�Q�[���v���O����
//		�b�R�c�`�����P�P�Q�@�@�@�@�@�@                 ver 3.0        201.1.11
//		�^�C�g���E�Q�[���N�����[�E�Q�[���I�[�o�[�̏���
//																Title.cpp
//=============================================================================
#include  "Title.h"
#include  "Map.h"
#include  "Playchar.h"
#include  "Enemy.h"
#include  "BackFore.h"

//============================================================================
//
// �^�C�g���v���V�[�W���̃R���X�g���N�^
//
// ---------------------------------------------------------------------------
CTitleProc::CTitleProc(CGameMain* pGMain)
{
	m_pGMain = pGMain;
	m_pImageTitle = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/TITLE.png")); // �C���[�W�̃��[�h
	m_pImageOption = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/option.png")); // �C���[�W�̃��[�h
	// �����т�����ʂ̃y�[�W
	m_pImagePage1 = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/explanationPage/P1.png")); // �C���[�W�̃��[�h
	m_pImagePage2 = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/explanationPage/P2.png")); // �C���[�W�̃��[�h
	m_pImagePage3 = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/explanationPage/P3.png")); // �C���[�W�̃��[�h
	m_pImagePage4 = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/explanationPage/P4.png")); // �C���[�W�̃��[�h
	m_pImagePage5 = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/explanationPage/P5.png")); // �C���[�W�̃��[�h
	m_pImagePage6 = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/explanationPage/P6.png")); // �C���[�W�̃��[�h
	m_pImagePage7 = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/explanationPage/P7.png")); // �C���[�W�̃��[�h
	m_pImagePage8 = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/explanationPage/P8.png")); // �C���[�W�̃��[�h
	// �����т�����ʂ̃y�[�W�ړ��{�^��
	m_pImagePageButton = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/explanationPage/orangeButton.png")); // �C���[�W�̃��[�h
	// �g�p����摜�̃��[�h
	m_pImageClear = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/platra_GAMECLEAR.png")); // �C���[�W�̃��[�h
	m_pImageOver  = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/platra_GAMEOVER.png")); // �C���[�W�̃��[�h
	m_pSprite = new CSprite(m_pGMain->m_pShader); // �X�v���C�g�̐���
	m_pImageSelect = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/TitleSelect.png")); // �C���[�W�̃��[�h
	m_pImageOptionNum = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/optionNumTex.png")); // �C���[�W�̃��[�h
	m_pImageOptionBackButton = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/option_BackButton.png")); // �C���[�W�̃��[�h
	m_pImageResult = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/platra_RESULT.png")); // �C���[�W�̃��[�h
	m_pImageRanking = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/platra_RANKING.png")); // �C���[�W�̃��[�h
	m_pImageSaveWarning = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/saveWarning.png")); // �C���[�W�̃��[�h
	m_pImageNoSave = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/noSaveDatapng.png")); // �C���[�W�̃��[�h
	m_pImageGreenButton = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/greenButton.png")); // �C���[�W�̃��[�h
	m_dwCntTime = 0;
	nTitleSelect = 0;

	linetrainNum = 0;      // M.S ���H�̑I�𐔎�
	passengersNum = 0;     // M.S ��Ԑl���̑I�𐔎�
	waitingTime = 0;       // M.S �҂����Ԃ̑I�𐔎�
	bgmNum = 0;            // M.S BGM���ʂ̑I�𐔎�
	seNum = 0;             // M.S SE���ʂ̑I�𐔎�
	lineTrainSelect = 0;     // M.S ���H�̑I�����萔��
	passengersSelect = 4;    // M.S ��Ԑl���̑I�����萔��
	waitingTimeSelect = 10;  // M.S �҂����Ԃ̑I�����萔��
	bgmSelect = 16;          // M.S BGM���ʂ̑I�����萔��
	seSelect = 22;           // M.S SE���ʂ̑I�����萔��
	selectedKindNum = 0;     // M.S �I�v�V������ʂ̃{�^���̗�̐���

	rankingTime = 0;               // M.S �����L���O��ʂ̃^�C���J�E���g
	myRanking = 0;                 // M.S �����̃����L���O
	totalScore = 0;                // M.S �g�[�^���X�R�A
	initialRankingSorting = true;  // M.S 1�x�̂݃����L���O���ёւ��t���O
	ScoreWriteProcess = false;  // M.S �t�@�C���������݃t���O
	saveWarningFlag = false;    // M.S �Z�[�u�f�[�^���钍�Ӄt���O
	noSaveFlag = false;         // M.S �Z�[�u�f�[�^�Ȃ����Ӄt���O
	nowPage = 0;                  // M.S ��������őI�𒆂̃y�[�W

	gameClearCount = 0;          // M.S �Q�[���N���A�^�C���J�E���g
	gameOverCount = 0;           // M.S �Q�[���I�[�o�[�^�C���J�E���g
	// M.S BGM�炷�t���O�̏�����
	RingSound = false;
	RingResultSound = false;
}
// ---------------------------------------------------------------------------
//
// �^�C�g���^�C�g���v���V�[�W���̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CTitleProc::~CTitleProc()
{
	// �g�p�����摜
	SAFE_DELETE(m_pImageTitle);
	SAFE_DELETE(m_pImageOption);
	SAFE_DELETE(m_pImageClear);
	SAFE_DELETE(m_pImageOver);
	SAFE_DELETE(m_pSprite);
	SAFE_DELETE(m_pImageSelect);
	SAFE_DELETE(m_pImageOptionNum);
	SAFE_DELETE(m_pImageOptionBackButton);
	SAFE_DELETE(m_pImageResult);
	SAFE_DELETE(m_pImageRanking);
	SAFE_DELETE(m_pImageSaveWarning);
	SAFE_DELETE(m_pImageNoSave);
	SAFE_DELETE(m_pImageGreenButton);
	// �����т�����ʂ̃y�[�W
	SAFE_DELETE(m_pImagePage1);
	SAFE_DELETE(m_pImagePage2);
	SAFE_DELETE(m_pImagePage3);
	SAFE_DELETE(m_pImagePage4);
	SAFE_DELETE(m_pImagePage5);
	SAFE_DELETE(m_pImagePage6);
	SAFE_DELETE(m_pImagePage7);
	SAFE_DELETE(m_pImagePage8);
	// �����т�����ʂ̃y�[�W�{�^��
	SAFE_DELETE(m_pImagePageButton);
}
//------------------------------------------------------------------------
//
//	�^�C�g���̕\��	
//
//------------------------------------------------------------------------
void CTitleProc::Title()
{
	switch (m_dwStatusPhase)
	{
	case 0:    // �t�F�[�Y�P  �Q�[�����[�h��I��
		//M.S �^�C�g���Z���N�g
		TitleSelect();
		break;
	case 1:    // �t�F�[�Y�Q  �Q�[���J�n���I�v�V�������	
		switch (m_pGMain->m_dwGameMode) {
		case 1:
			// M.S �͂��߂���
			// M.S �^�C�g��BGM���~�߂�
			m_pGMain->titleBgm->Stop();
			// M.S �Q�[��BGM�𗬂�
			m_pGMain->gameBgm->Play(AUDIO_LOOP);
			// M.S ���̐����ϐ��̏�����
			m_pGMain->traveledStar = 0;
			m_pGMain->haveToGoStar = 0;
			m_pGMain->starArray[25] = { 0 };
			// M.S �l�L�����̏�Ԑl���ϐ��̏�����
			m_pGMain->redMan = 0;
			m_pGMain->yellowMan = 0;
			m_pGMain->blueMan = 0;
			m_pGMain->m_pEnmProc->getHighMan = m_pGMain->redMan;
			m_pGMain->m_pEnmProc->getMiddleMan = m_pGMain->yellowMan;
			m_pGMain->m_pEnmProc->getLowMan = m_pGMain->blueMan;
			// M.S �}�b�v1�̃��[�h
			m_pGMain->m_pMapProc->LoadMap1();
			m_pGMain->m_dwGameStatus = GAMEMAIN;
			break;
		case 2:
			// M.S ��������
			// M.S �^�C�g��BGM���~�߂�
			m_pGMain->titleBgm->Stop();
			// M.S �Q�[��BGM�𗬂�
			m_pGMain->gameBgm->Play(AUDIO_LOOP);
			// M.S �t�@�C������ǂݍ��񂾏�Ԑl����ϐ��֓����
			m_pGMain->m_pEnmProc->getHighMan = m_pGMain->redMan;
			m_pGMain->m_pEnmProc->getMiddleMan = m_pGMain->yellowMan;
			m_pGMain->m_pEnmProc->getLowMan = m_pGMain->blueMan;
			// M.S �}�b�v2�̃��[�h
			m_pGMain->m_pMapProc->LoadMap2();
			m_pGMain->m_dwGameStatus = GAMEMAIN;
			break;
		case 3:
			// M.S �����L���O���[�h
			// M.S �^�C�g��BGM���~�߂�
			m_pGMain->titleBgm->Stop();
			// M.S �Q�[��BGM�𗬂�
			m_pGMain->gameBgm->Play(AUDIO_LOOP);
			// M.S �Z�[�u�f�[�^�ɏ������݁A�ǂݍ��݂��Ȃ�
			// M.S �����L���O�p�̕ϐ����g�p
			m_pGMain->rankLineTrainSelectNum = 30;
			m_pGMain->rankPassengersSelectNum = 3;
			m_pGMain->rankWaitingTimeSelectNum = 3;
			m_pGMain->rankTraveledStar = 0;
			m_pGMain->rankHaveToGoStar = 5;  // M.S 5�̐���n��
			m_pGMain->rankRedMan = 0;
			m_pGMain->rankYellowMan = 0;
			m_pGMain->rankBlueMan = 0;
			// M.S �}�b�v2�̃��[�h
			m_pGMain->m_pMapProc->LoadMap2();
			m_pGMain->m_dwGameStatus = GAMEMAIN;
			break;
		}
	case 2:
		//M.S �I�v�V�������
		TitleOption();
		break;
	case 3:
		//M.S �����L���O�m�F���
		DrawRanking();
		break;
	case 4:
		// M.S ������@�̐������
		TitleExplanation();
		break;
	}
}
bool CTitleProc::TitleTitle()
{
	BOOL bRet = FALSE;

	// �\��
	m_pSprite->Draw(m_pImageTitle, 0, 0, 0, 0, m_pImageTitle->m_dwImageWidth, m_pImageTitle->m_dwImageHeight, WINDOW_WIDTH, WINDOW_HEIGHT);

	// �t�H���g���@"_T(�c�e������")�C_T("�l�r �o�S�V�b�N")�C_T("�l�r �S�V�b�N")�C_T("HGP�n�p�p�߯�ߑ�")�C_T("HGP�n�p�p�޼��UB")
	m_pGMain->m_pFont->Draw(253, 53, _T("�R�c�A�N�V�����Q�[��"), 90, RGB(0, 0, 0), 1.0f, _T("HGP�n�p�p�߯�ߑ�"));
	m_pGMain->m_pFont->Draw(250, 50, _T("�R�c�A�N�V�����Q�[��"), 90, RGB(255, 0, 0), 1.0f, _T("HGP�n�p�p�߯�ߑ�"));

	m_pGMain->m_pFont->Draw(WINDOW_WIDTH - 200, 20, _T("C3DAct112"), 30, RGB(192, 0, 0), 1.0f, _T("HGP�n�p�p�޼��UB"));
	m_pGMain->m_pFont->Draw(WINDOW_WIDTH - 250, 130, _T("DirectX11�Ή�"), 30, RGB(0, 0, 64), 1.0f, _T("HGP�n�p�p�߯�ߑ�"));
	return bRet;
}
// M.S �I�v�V������ʂŐݒ肵���������v���O�����Ŏg�p���鐔���ɕϊ�
//��  ���Fint bgmOrSeNum 0:���ׂĂ̏��������� 1:BGM�̏����̂� 2:SE�̏����̂�
//�߂�l�F�Ȃ�
void CTitleProc::ChangeSelectNum(int bgmOrSeNum) {
	// bgmOrSeNum:0 ���ׂĂ̏��������� 1:BGM�̂� 2:SE�̂�
	// �I�v�V������ʂ̃{�^������v���O�����Ŏg�p���鐔���ւ̕ϊ�
	switch (bgmOrSeNum) {
	case 0:
		// ���H���̕ϊ�
		switch (lineTrainSelect) {
		case 0:
			m_pGMain->lineTrainSelectNum = 30;
			break;
		case 1:
			m_pGMain->lineTrainSelectNum = 50;
			break;
		case 2:
			m_pGMain->lineTrainSelectNum = 70;
			break;
		case 3:
			m_pGMain->lineTrainSelectNum = 80;
		}
		// ��Ԑl���̕ϊ�
		switch (passengersSelect) {
		case 4:
			m_pGMain->passengersSelectNum = 0;
			break;
		case 5:
			m_pGMain->passengersSelectNum = 3;
			break;
		case 6:
			m_pGMain->passengersSelectNum = 6;
			break;
		case 7:
			m_pGMain->passengersSelectNum = 9;
			break;
		case 8:
			m_pGMain->passengersSelectNum = 12;
			break;
		case 9:
			m_pGMain->passengersSelectNum = 18;
		}
		// ���˂܂ł̑҂����Ԃ̕ϊ�
		for (int i = 10; i < 16; i++) {
			if (waitingTimeSelect == i) {
				m_pGMain->waitingTimeSelectNum = i - 10;
				break;
			}
		}
		// BGM���ʂ̕ϊ�
		for (int i = 16; i < 22; i++) {
			if (bgmSelect == i) {
				m_pGMain->bgmSelectNum = (i - 16) * 0.2;
				break;
			}
		}
		// SE���ʂ̕ϊ�
		for (int i = 22; i < 28; i++) {
			if (seSelect == i) {
				m_pGMain->seSelectNum = (i - 22) * 0.2;
				break;
			}
		}
		break;
	case 1:  // BGM���ʂ̕ϊ�
		for (int i = 16; i < 22; i++) {
			if (bgmSelect == i) {
				m_pGMain->bgmSelectNum = (i - 16) * 0.2;
				break;
			}
		}
		break;
	case 2:  // SE���ʂ̕ϊ�
		for (int i = 22; i < 28; i++) {
			if (seSelect == i) {
				m_pGMain->seSelectNum = (i - 22) * 0.2;
				break;
			}
		}
		break;
	}
}
// M.S �v���O�����Ŏg�p���鐔�����I�v�V������ʂŐݒ肵�������֕ϊ�
//��  ���F�Ȃ�
//�߂�l�F�Ȃ�
void CTitleProc::ChangeSelect() {
	// ���H���̕ϊ�
	switch (m_pGMain->lineTrainSelectNum) {
	case 30:
		lineTrainSelect = 0;
		break;
	case 50:
		lineTrainSelect = 1;
		break;
	case 70:
		lineTrainSelect = 2;
		break;
	case 80:
		lineTrainSelect = 3;
	}
	// ��Ԑl���̕ϊ�
	switch (m_pGMain->passengersSelectNum) {
	case 0:
		passengersSelect = 4;
		break;
	case 3:
		passengersSelect = 5;
		break;
	case 6:
		passengersSelect = 6;
		break;
	case 9:
		passengersSelect = 7;
		break;
	case 12:
		passengersSelect = 8;
		break;
	case 18:
		passengersSelect = 9;
	}
	// ���˂܂ł̑҂����Ԃ̕ϊ�
	for (int i = 0; i < 6; i++) {
		if (m_pGMain->waitingTimeSelectNum == i) {
			waitingTimeSelect = i + 10;
			break;
		}
	}
	// BGM���ʂ̕ϊ�
	int bgmBuf = m_pGMain->bgmSelectNum * 10;
	for (int i = 0; i < 6; i++) {
		if (bgmBuf == i * 2) {
			bgmSelect = i + 16;
			break;
		}
	}
	// SE���ʂ̕ϊ�
	int seBuf = m_pGMain->seSelectNum * 10;
	for (float i = 0; i < 6; i++) {
		if (seBuf == i * 2) {
			seSelect = i + 22;
			break;
		}
	}
}
// M.S �͂��߂����I���������̃Z�[�u�f�[�^������ƒm�点�钍�ӕ\��
//��  ���F�Ȃ�
//�߂�l�Fbool true�̏ꍇ�AOK�{�^���������Q�[���J�n�ɐi��
bool CTitleProc::DrawSaveWarning() {
	bool bRet = false;               
	int saveWarningTextPosX = 373;    // �Z�[�u�f�[�^���钍�ӕ\���e�L�X�g��X�ʒu
	int saveWarningTextPosY = 182;    // �Z�[�u�f�[�^���钍�ӕ\���e�L�X�g��Y�ʒu
	int saveWarningTextWidth = 620;   // �Z�[�u�f�[�^���钍�ӕ\���e�L�X�g�̕�
	int saveWarningTextHeight = 378;  // �Z�[�u�f�[�^���钍�ӕ\���e�L�X�g�̍���
	int saveWarningOkPosX = 486;      // OK�{�^����X�ʒu
	int saveWarningOkPosY = 474;  // �{�^����Y�ʒu
	int saveWarningBackPosX = 709;    // �߂�{�^����X�ʒu
	int saveWarningBackPosY = 474;  // �{�^����Y�ʒu
	int saveWarningButtonWidth = 173; // �{�^���̕�
	int saveWarningButtonHeight = 70; // �{�^���̍���
	float lightColor = 0.5f;          // �����F�ŕ\�����铧���x
	// �Z�[�u�f�[�^���钍�ӕ\���t���O��true���ǂ���
	if (saveWarningFlag == true) {
		// �Z�[�u�f�[�^���钍�Ӄe�L�X�g�\��
		m_pSprite->Draw(m_pImageSaveWarning, saveWarningTextPosX,
			saveWarningTextPosY, 0, 0, saveWarningTextWidth, saveWarningTextHeight);
		// OK�{�^����I�𒆂��ǂ���
		if (CheckMousePos(saveWarningOkPosX, saveWarningOkPosY,
			saveWarningButtonWidth, saveWarningButtonHeight) == true)
		{
			// �I�𒆃{�^����\��
			m_pSprite->Draw(m_pImageSaveWarning, saveWarningOkPosX, saveWarningOkPosY,
				0, 378, saveWarningButtonWidth, saveWarningButtonHeight);
			// �I�𒆂łȂ��{�^�������F�ŕ\��
			m_pSprite->Draw(m_pImageSaveWarning, saveWarningBackPosX, saveWarningOkPosY,
				173, 378, saveWarningButtonWidth, saveWarningButtonHeight, lightColor);
			// ���肵�����ǂ���
			if (m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_SPACE)
				|| m_pGMain->m_pDI->CheckJoy(KD_TRG, DIJ_A)
				|| m_pGMain->m_pDI->CheckMouse(KD_TRG, DIM_LBUTTON))
			{
				m_pGMain->selectSound->Play();  // ���ʉ��̔���
				saveWarningFlag = false; // �Z�[�u�f�[�^���钍�ӕ\���t���O��false
				//noSaveFlag = false;
				m_dwStatusPhase = 1;            // �Q�[���J�n�t�F�[�Y��
				m_pGMain->m_dwGameMode = 1;     // �͂��߂���
				bRet = TRUE;  // �I��
			}
		}
		// �߂�{�^����I�𒆂��ǂ���
		else if (CheckMousePos(saveWarningBackPosX, saveWarningBackPosY,
			saveWarningButtonWidth, saveWarningButtonHeight) == true) {
			// �I�𒆃{�^����\��
			m_pSprite->Draw(m_pImageSaveWarning, saveWarningBackPosX, saveWarningBackPosY,
				173, 378, saveWarningButtonWidth, saveWarningButtonHeight);
			// �I�𒆂łȂ��{�^�������F�ŕ\��
			m_pSprite->Draw(m_pImageSaveWarning, saveWarningOkPosX, saveWarningBackPosY,
				0, 378, saveWarningButtonWidth, saveWarningButtonHeight, lightColor);
			// ���肵�����ǂ���
			if (m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_SPACE)
				|| m_pGMain->m_pDI->CheckJoy(KD_TRG, DIJ_A)
				|| m_pGMain->m_pDI->CheckMouse(KD_TRG, DIM_LBUTTON))
			{
				m_pGMain->selectSound->Play();  // ���ʉ��̔���
				saveWarningFlag = false; // �Z�[�u�f�[�^���钍�ӕ\���t���O��false
			}
		}
		else {
			// �{�^����I�����Ă��Ȃ��ꍇ�A�{�^���𔖂��F�ŕ\��
			m_pSprite->Draw(m_pImageSaveWarning, saveWarningOkPosX, saveWarningOkPosY,
				0, 378, saveWarningButtonWidth, saveWarningButtonHeight, lightColor);
			m_pSprite->Draw(m_pImageSaveWarning, saveWarningBackPosX, saveWarningBackPosY,
				173, 378, saveWarningButtonWidth, saveWarningButtonHeight, lightColor);
		}
	}
	return bRet;
}
// M.S �Â������I���������̃Z�[�u�f�[�^���Ȃ��ƒm�点�钍�ӕ\��
//��  ���F�Ȃ�
//�߂�l�F�Ȃ�
void CTitleProc::DrawNoSaveDataWarning() {
	int saveWarningTextPosX = 373;    // �Z�[�u�f�[�^�Ȃ����ӕ\���e�L�X�g��X�ʒu
	int saveWarningTextPosY = 102;    // �Z�[�u�f�[�^�Ȃ����ӕ\���e�L�X�g��Y�ʒu
	int saveWarningTextWidth = 620;   // �Z�[�u�f�[�^�Ȃ����ӕ\���e�L�X�g�̕�
	int saveWarningTextHeight = 378;  // �Z�[�u�f�[�^�Ȃ����ӕ\���e�L�X�g�̍���
	int saveWarningBackPosX = 607;    // �߂�{�^����X�ʒu
	int saveWarningBackPosY = 394;    // �߂�{�^����Y�ʒu
	int saveWarningBackWidth = 173;   // �߂�{�^���̕�
	int saveWarningBackHeight = 70;   // �߂�{�^���̍���
	float lightColor = 0.5f;          // �����F�ŕ\�����铧���x
	// �Z�[�u�f�[�^�Ȃ����ӕ\���t���O��true���ǂ���
	if (noSaveFlag == true) {
		// �Z�[�u�f�[�^�Ȃ����ӕ\���e�L�X�g�\��
		m_pSprite->Draw(m_pImageNoSave, saveWarningTextPosX, saveWarningTextPosY, 0, 0, saveWarningTextWidth, saveWarningTextHeight);
		// �߂�{�^����I�𒆂��ǂ���
		if (CheckMousePos(saveWarningBackPosX, saveWarningBackPosY, saveWarningBackWidth, saveWarningBackHeight) == true)
		{
			// �I�𒆃{�^����\��
			m_pSprite->Draw(m_pImageNoSave, saveWarningBackPosX, saveWarningBackPosY, 0, 378, saveWarningBackWidth, saveWarningBackHeight);
			// ���肵�����ǂ���
			if (m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_SPACE)
				|| m_pGMain->m_pDI->CheckJoy(KD_TRG, DIJ_A)
				|| m_pGMain->m_pDI->CheckMouse(KD_TRG, DIM_LBUTTON))
			{
				m_pGMain->selectSound->Play(); // ���ʉ��̔���
				noSaveFlag = false;  // �Z�[�u�f�[�^�Ȃ����ӕ\���t���O��false
			}
		}
		else {
			// �{�^����I�����Ă��Ȃ��ꍇ�A�{�^���𔖂��F�ŕ\��
			m_pSprite->Draw(m_pImageNoSave, saveWarningBackPosX, saveWarningBackPosY, 0, 378, saveWarningBackWidth, saveWarningBackHeight, lightColor);
		}
	}
}
// M.S �����т����{�^���ƃ����L���O�m�F�{�^���̕\���A�I������
//��  ���F�Ȃ�
//�߂�l�Fbool true�̏ꍇ�A�I��������ʂɐi��
bool CTitleProc::DrawHowToPlayRanking() {
	bool bRet = false;
	int howToPlayCursorButtonPosX = 905; // �����т����{�^���I��͈͂�X�ʒu
	int howToPlayCursorButtonPosY = 644; // �����т����{�^���I��͈͂�Y�ʒu
	int rankingCursorButtonPosX = 1130;  // �����L���O�m�F�{�^���I��͈͂�X�ʒu
	int rankingCursorButtonPosY = 644;   // �����L���O�m�F�{�^���I��͈͂�Y�ʒu
	int buttonCursorWidth = 201;         // �{�^���̑I��͈͂̕�
	int buttonCursorHeight = 101;        // �{�^���̑I��͈͂̍���
	int howToPlayButtonPosX = 893;       // �����т����{�^����X�ʒu
	int howToPlayButtonPosY = 634;       // �����т����{�^����Y�ʒu
	int rankingButtonPosX = 1118;  // �����L���O�m�F�{�^����X�ʒu
	int rankingButtonPosY = 634;   // �����L���O�m�F�{�^����Y�ʒu
	int buttonWidth = 225;               // �{�^���̕�
	int buttonHeight = 122;              // �{�^���̍���	
	float lightColor = 0.5f;             // �����F�ŕ\�����铧���x
	// �����т������[�h
	// �����т����{�^����I�����Ă��邩�ǂ���
	if (CheckMousePos(howToPlayCursorButtonPosX, howToPlayCursorButtonPosY,
		buttonCursorWidth, buttonCursorHeight) == true)
	{
		m_pSprite->
			Draw(m_pImageGreenButton, howToPlayButtonPosX, howToPlayButtonPosY,
				0, 0, buttonWidth, buttonHeight);  		// �����т����{�^����\��
		// ���肵�����ǂ���
		if (m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_SPACE) || m_pGMain->m_pDI->CheckJoy(KD_TRG, DIJ_A)
			|| m_pGMain->m_pDI->CheckMouse(KD_TRG, DIM_LBUTTON))
		{
			m_pGMain->selectSound->Play(); // �I�����ʉ�
			m_dwStatusPhase = 4; // ������@�̐������
			bRet = TRUE;  // �I��
			return bRet;
		}
	}
	else {
		// �I�����Ă��Ȃ��̂ł����т����{�^���𔖂��F�ŕ\��
		m_pSprite->
			Draw(m_pImageGreenButton, howToPlayButtonPosX, howToPlayButtonPosY,
				0, 0, buttonWidth, buttonHeight, lightColor);  	 
	}
	// �����L���O�m�F���[�h
	// �����L���O�m�F�{�^����I�����Ă��邩�ǂ���
	if (CheckMousePos(rankingCursorButtonPosX, rankingCursorButtonPosY,
		buttonCursorWidth, buttonCursorHeight) == true)
	{
		m_pSprite->
			Draw(m_pImageGreenButton, rankingButtonPosX, rankingButtonPosY,
				225, 0, buttonWidth, buttonHeight);  // �����L���O�m�F�{�^����\��
		// ���肵�����ǂ���
		if (m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_SPACE) || m_pGMain->m_pDI->CheckJoy(KD_TRG, DIJ_A)
			|| m_pGMain->m_pDI->CheckMouse(KD_TRG, DIM_LBUTTON))
		{
			m_pGMain->selectSound->Play(); // �I�����ʉ�
			m_dwStatusPhase = 3; // �����L���O�m�F���
			bRet = TRUE;  // �I��
			return bRet;
		}
	}
	else {
		// �I�����Ă��Ȃ��̂Ń����L���O�m�F�{�^���𔖂��F�ŕ\��
		m_pSprite->
			Draw(m_pImageGreenButton, rankingButtonPosX, rankingButtonPosY,
				225, 0, buttonWidth, buttonHeight, lightColor);
	}
	return bRet;
}
// M.S �^�C�g���Z���N�g��ʂ̕\���A�I������
//��  ���F�Ȃ�
//�߂�l�Fbool true �^�C�g���Z���N�g��ʂ̏I��
bool CTitleProc::TitleSelect()
{
	BOOL bRet = FALSE;
	const int nNum = 4;   // �Z���N�g�{�^���̐�
	const float fScale = 1.2f;
	// �Z���N�g�{�^����X�AY�ʒu
	const int nStartX = 502, nStartY = 384;
	// �Z���N�g�{�^���̕��A����
	const int nWidth = 362, nHeight = 95;
	// �Z���N�g�{�^���̊g�債�����A����
	const int nWidthScale = nWidth * fScale;
	const int nHeightScale = nHeight * fScale;
	// �����F�ŕ\�����铧���x
	float lightColor = 0.5f;             
	int i;
	// ��ʂ̕\��
	m_pSprite->
		Draw(m_pImageTitle, 0, 0, 0, 0, m_pImageTitle->m_dwImageWidth,
			m_pImageTitle->m_dwImageHeight, WINDOW_WIDTH, WINDOW_HEIGHT);
	// �����т����{�^���ƃ����L���O�m�F�{�^���̕\���A�I������
	bRet = DrawHowToPlayRanking();
	// �����т����{�^���������L���O�m�F�{�^���������ꂽ���ǂ���
	if (bRet == TRUE) {
		return bRet;  		// �I��
	}
	// 4�̃Z���N�g�{�^�������ɒ��ׂ�
	for (i = 0; i < nNum; i++)
	{
		// �}�E�X�J�[�\�������ׂĂ���Z���N�g�{�^�������邩�ǂ���
		if (CheckMousePos(nStartX, nStartY + (nHeight * i), nWidth, nHeight) == true)
		{
			nTitleSelect = i;   //���ׂĂ���Z���N�g�{�^���̐�����nTitleSelect�ɓ����
			break;
		}
		else {
			nTitleSelect = 10;  // �J�[�\�����ɂȂ��ꍇ
		}
	}
	// �Z���N�g�{�^���̕\��
	for (i = 0; i < nNum; i++)
	{
		if (nTitleSelect == i)
		{
			// �I�𒆂̃{�^��
			m_pSprite->Draw(m_pImageSelect, nStartX - 35, nStartY + (nHeight * i),
				0, 0 + (nHeight * i), nWidth, nHeight, nWidthScale, nHeightScale);	
		}
		else {
			// �I�����Ă��ȃ{�^��
			m_pSprite->Draw(m_pImageSelect, nStartX, nStartY + (nHeight * i),
				0, 0 + (nHeight * i), nWidth, nHeight, lightColor);
		}
	}
	// �I���L�[
	if (m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_SPACE) 
		|| m_pGMain->m_pDI->CheckJoy(KD_TRG, DIJ_A) 
		|| m_pGMain->m_pDI->CheckMouse(KD_TRG, DIM_LBUTTON)) {
		// �͂��߂��炩�Z�[�u�f�[�^�����邩�ǂ���
		if (nTitleSelect == 0 && m_pGMain->continuationFlag == true) {
			m_pGMain->saveWarningSound->Play(); // ���ӌ��ʉ�
		    saveWarningFlag = true;   // �Z�[�u�f�[�^���钍�ӕ\���t���O��true
		}
		// �Â����炩�Z�[�u�f�[�^���������ǂ���
		else if (nTitleSelect == 1 && m_pGMain->continuationFlag == false) {
			m_pGMain->saveWarningSound->Play(); // ���ӌ��ʉ�
			noSaveFlag = true;    // �Z�[�u�f�[�^�Ȃ����ӕ\���t���O��true 
		}
		else if (saveWarningFlag == false && noSaveFlag == false) {
			saveWarningFlag = false;         // ���Ӄt���O�̏�����
			noSaveFlag = false;
			// �I�v�V������I�����Ă��Ȃ��A���{�^���O��I�����Ă��Ȃ����ǂ���
			if (nTitleSelect != 3 && nTitleSelect != 10) {
				m_pGMain->selectSound->Play();   // �I�����ʉ�
				// �Q�[���J�n�t�F�[�Y��
				m_dwStatusPhase = 1;
				// �I�񂾃Q�[�����[�h��
				m_pGMain->m_dwGameMode = nTitleSelect + 1;
			}
			// �I�v�V������I���������ǂ���
			else if(nTitleSelect == 3){
				m_pGMain->selectSound->Play();   // �I�����ʉ�
				// �I�v�V������ʂ�
				m_dwStatusPhase = 2;
			}
			bRet = TRUE;  // �I��
			return bRet;
		}
	}
	bRet = DrawSaveWarning();// �Z�[�u�f�[�^���钍�ӕ\��
	// �Z�[�u�f�[�^���钍�ӕ\����OK��������A�Q�[���J�n�ɂȂ��Ă��邩�ǂ���
	if (bRet == TRUE) {
		return bRet;  		// �I��
	}
	DrawNoSaveDataWarning(); // �Z�[�u�f�[�^�Ȃ����ӕ\��
	return bRet;
}
// M.S �I�v�V������ʂ̐��H���{�^�������̕\���A�I������
//��  ���F�Ȃ�
//�߂�l�F�Ȃ�
void CTitleProc::SelectLineNum(bool judgeRange, int selectKind, int i) {
	// ���H��
	const float fScale = 1.2f; // �\���{�^���̊g��l 
	// �\���ʒu��X�AY�ʒu
	const int nStartX = 690, nStartY = 80;
	// �{�^���̕��A����
	const int nWidth = 50, nHeight = 50;
	// �g�債���{�^���̕��A����
	const int nWidthScale = nWidth * fScale;
	const int nHeightScale = nHeight * fScale;
	// �����F�ŕ\�����铧���x
	float lightColor = 0.5f;
	// �I�������肵�Ă���{�^�����ǂ���
	if (lineTrainSelect == i) {
		m_pSprite->m_vDiffuse = VECTOR4(1.0f, 0.4f, 0.3f, 1.0f);  // �\������F��ԐF�ɂ���
		m_pSprite->Draw(m_pImageOptionNum, nStartX + (i * 70), nStartY, 
			i * 50, 50, nWidth, nHeight, 1.0f);  // �F��ς��ĕ\��
		m_pSprite->m_vDiffuse = VECTOR4(1.0f, 1.0f, 1.0f, 1.0f);  // �F�����ɖ߂�
	}
	else {
		// selectKind�͑��̃I�v�V�����̗�̐�(�{�^��)�ɔ��������Ȃ�����
		// judgeRange�͌��݃J�[�\�������ǂ�������
		// �J�[�\�����ɂ��鐔��(�{�^��)���ǂ���
		if (linetrainNum == i && selectKind == 1 && judgeRange == true) {  
			m_pSprite->Draw(m_pImageOptionNum, nStartX + (i * 70), nStartY,
				i * 50, 50, nWidth, nHeight,nWidthScale, nHeightScale, 1.0f);
			// �J�[�\�������I�����Ă��邩�ǂ���
			if (m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_SPACE) || m_pGMain->m_pDI->CheckJoy(KD_TRG, DIJ_A)
				|| m_pGMain->m_pDI->CheckMouse(KD_TRG, DIM_LBUTTON))
			{
				// �I�𒆂̐����̍X�V
				lineTrainSelect = i;
				m_pGMain->selectSound->Play(); // �I�����ʉ�
			}
		}
		else {
			// �I�𒆂ł��Ȃ��J�[�\���������Ă��Ȃ������̕`��
			m_pSprite->Draw(m_pImageOptionNum, nStartX + (i * 70), nStartY, 
				i * 50, 50, nWidth, nHeight, lightColor);  // �����F�ŕ\��
		}
	}
}
// M.S �I�v�V������ʂ̏�Ԑl���{�^�������̕\���A�I������
//��  ���F�Ȃ�
//�߂�l�F�Ȃ�
void CTitleProc::SelectPassengersNum(bool judgeRange, int selectKind, int i) {
	//��Ԑl��
	const float fScale = 1.2f; // �\���{�^���̊g��l 
	// �\���ʒu��X�AY�ʒu
	const int nStartX = 690, nStartY = 80;
	// �{�^���̕��A����
	const int nWidth = 50, nHeight = 50;
	// �g�債���{�^���̕��A����
	const int nWidthScale = nWidth * fScale;
	const int nHeightScale = nHeight * fScale;
	// �����F�ŕ\�����铧���x
	float lightColor = 0.5f;
	// �I�������肵�Ă���{�^�����ǂ���
	if (passengersSelect == i) {
		m_pSprite->m_vDiffuse = VECTOR4(1.0f, 0.4f, 0.3f, 1.0f);  // �\������F��ԐF�ɂ���
		m_pSprite->Draw(m_pImageOptionNum, nStartX + ((i - 4) * 70), nStartY + 125,
			(i - 4) * 50, 0, nWidth, nHeight, 1.0f);  // �F��ς��ĕ\��
		m_pSprite->m_vDiffuse = VECTOR4(1.0f, 1.0f, 1.0f, 1.0f);  // �F�����ɖ߂�
	}
	else {
		// selectKind�͑��̃I�v�V�����̗�̐�(�{�^��)�ɔ��������Ȃ�����
		// judgeRange�͌��݃J�[�\�������ǂ�������
		// �J�[�\�����ɂ��鐔��(�{�^��)�ǂ���
		if (passengersNum == i && selectKind == 2 && judgeRange == true)
		{
			m_pSprite->Draw(m_pImageOptionNum, nStartX + ((i - 4) * 70), nStartY + 125,
				(i - 4) * 50, 0, nWidth, nHeight,nWidthScale, nHeightScale, 1.0f);
			// �J�[�\�������I�����Ă��邩�ǂ���
			if (m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_SPACE) || m_pGMain->m_pDI->CheckJoy(KD_TRG, DIJ_A) 
				|| m_pGMain->m_pDI->CheckMouse(KD_TRG, DIM_LBUTTON))	
			{
				// �I�𒆂̐����̍X�V
				passengersSelect = i;
				m_pGMain->selectSound->Play();  // �I�����ʉ�
			}
		}
		else {
			m_pSprite->Draw(m_pImageOptionNum, nStartX + ((i - 4) * 70), nStartY + 125,
				(i - 4) * 50, 0, nWidth, nHeight, lightColor);  // �����F�ŕ\��
		}
	}
}
// M.S �I�v�V������ʂ̔��˂܂ł̑҂����ԃ{�^�������̕\���A�I������
//��  ���F�Ȃ�
//�߂�l�F�Ȃ�
void CTitleProc::SelectWaitTime(bool judgeRange, int selectKind, int i) {
	// �҂�����
	const float fScale = 1.2f; // �\���{�^���̊g��l 
	// �\���ʒu��X�AY�ʒu
	const int nStartX = 690, nStartY = 80;
	// �{�^���̕��A����
	const int nWidth = 50, nHeight = 50;
	// �g�債���{�^���̕��A����
	const int nWidthScale = nWidth * fScale;
	const int nHeightScale = nHeight * fScale;
	// �����F�ŕ\�����铧���x
	float lightColor = 0.5f;
	// �I�������肵�Ă���{�^�����ǂ���
	if (waitingTimeSelect == i) { 
		m_pSprite->m_vDiffuse = VECTOR4(1.0f, 0.4f, 0.3f, 1.0f);  // �\������F��ԐF�ɂ���
		m_pSprite->Draw(m_pImageOptionNum, nStartX + ((i - 10) * 70), nStartY + 245,
			(i - 10) * 50, 100, nWidth, nHeight, 1.0f);  // �F��ς��ĕ\��
		m_pSprite->m_vDiffuse = VECTOR4(1.0f, 1.0f, 1.0f, 1.0f);  // �F�����ɖ߂�
	}
	else {
		// selectKind�͑��̃I�v�V�����̗�̐�(�{�^��)�ɔ��������Ȃ�����
		// judgeRange�͌��݃J�[�\�������ǂ�������
		// �J�[�\�����ɂ��鐔��(�{�^��)���ǂ���
		if (waitingTime == i && selectKind == 3 && judgeRange == true)
		{
			m_pSprite->Draw(m_pImageOptionNum, nStartX + ((i - 10) * 70), nStartY + 245,
				(i - 10) * 50, 100, nWidth, nHeight,nWidthScale, nHeightScale, 1.0f);
			// �J�[�\�������I�����Ă��邩�ǂ���
			if (m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_SPACE) || m_pGMain->m_pDI->CheckJoy(KD_TRG, DIJ_A)
				|| m_pGMain->m_pDI->CheckMouse(KD_TRG, DIM_LBUTTON))
			{
				// �I�𒆂̐����̍X�V
				waitingTimeSelect = i;
				m_pGMain->selectSound->Play();  // �I�����ʉ�
			}
		}
		else {
			m_pSprite->Draw(m_pImageOptionNum, nStartX + ((i - 10) * 70), nStartY + 245, 
				(i - 10) * 50, 100, nWidth, nHeight, lightColor);  // �����F�ŕ\��
		}
	}
}
// M.S �I�v�V������ʂ�BGM���ʃ{�^�������̕\���A�I������
//��  ���F�Ȃ�
//�߂�l�F�Ȃ�
void CTitleProc::SelectBgm(bool judgeRange, int selectKind, int i) {
	// BGM����
	const float fScale = 1.2f; // �\���{�^���̊g��l 
	// �\���ʒu��X�AY�ʒu
	const int nStartX = 690, nStartY = 80;
	// �{�^���̕��A����
	const int nWidth = 50, nHeight = 50;
	// �g�債���{�^���̕��A����
	const int nWidthScale = nWidth * fScale;
	const int nHeightScale = nHeight * fScale;
	// �����F�ŕ\�����铧���x
	float lightColor = 0.5f;
	// �I�������肵�Ă���{�^�����ǂ���
	if (bgmSelect == i) {
		m_pSprite->m_vDiffuse = VECTOR4(1.0f, 0.4f, 0.3f, 1.0f);  // �\������F��ԐF�ɂ���
		m_pSprite->Draw(m_pImageOptionNum, nStartX + ((i - 16) * 70), nStartY + 360,
			(i - 16) * 50, 100, nWidth, nHeight, 1.0f);  // �F��ς��ĕ\��
		m_pSprite->m_vDiffuse = VECTOR4(1.0f, 1.0f, 1.0f, 1.0f);  // �F�����ɖ߂�
	}
	else {
		// selectKind�͑��̃I�v�V�����̗�̐�(�{�^��)�ɔ��������Ȃ�����
		// judgeRange�͌��݃J�[�\�������ǂ�������
		// �J�[�\�����ɂ��鐔��(�{�^��)���ǂ���
		if (bgmNum == i && selectKind == 4 && judgeRange == true) {
			{
				m_pSprite->Draw(m_pImageOptionNum, nStartX + ((i - 16) * 70), nStartY + 360,
					(i - 16) * 50, 100, nWidth, nHeight,nWidthScale, nHeightScale, 1.0f);
				// �J�[�\�������I�����Ă��邩�ǂ���
				if (m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_SPACE) || m_pGMain->m_pDI->CheckJoy(KD_TRG, DIJ_A)
					|| m_pGMain->m_pDI->CheckMouse(KD_TRG, DIM_LBUTTON))
				{
					// �I�𒆂̐����̍X�V
					bgmSelect = i;
					// �I���������������ʐݒ�Ɏg�������ɕϊ�
					ChangeSelectNum(1);
					// ���ʂ̐ݒ�
					m_pGMain->SetBgmVolume();
					m_pGMain->selectSound->Play();  // �I�����ʉ�
				}
			}
		}
		else {
			m_pSprite->Draw(m_pImageOptionNum, nStartX + ((i - 16) * 70), nStartY + 360,
				(i - 16) * 50, 100, nWidth, nHeight, lightColor);  // �����F�ŕ\��
		}
	}
}
// M.S �I�v�V������ʂ�SE���ʃ{�^�������̕\���A�I������
//��  ���F�Ȃ�
//�߂�l�F�Ȃ�
void CTitleProc::SelectSe(bool judgeRange, int selectKind, int i) {
	// SE����
	const float fScale = 1.2f; // �\���{�^���̊g��l 
	// �\���ʒu��X�AY�ʒu
	const int nStartX = 690, nStartY = 80;
	// �{�^���̕��A����
	const int nWidth = 50, nHeight = 50;
	// �g�債���{�^���̕��A����
	const int nWidthScale = nWidth * fScale;
	const int nHeightScale = nHeight * fScale;
	// �����F�ŕ\�����铧���x
	float lightColor = 0.5f;
	// �I�������肵�Ă���{�^�����ǂ���
	if (seSelect == i) {
		m_pSprite->m_vDiffuse = VECTOR4(1.0f, 0.4f, 0.3f, 1.0f);  // �\������F��ԐF�ɂ���
		m_pSprite->Draw(m_pImageOptionNum, nStartX + ((i - 22) * 70), nStartY + 470,
			(i - 22) * 50, 100, nWidth, nHeight, 1.0f);  // �F��ς��ĕ\��
		m_pSprite->m_vDiffuse = VECTOR4(1.0f, 1.0f, 1.0f, 1.0f);  // �F�����ɖ߂�
	}
	else {
		// selectKind�͑��̃I�v�V�����̗�̐�(�{�^��)�ɔ��������Ȃ�����
		// judgeRange�͌��݃J�[�\�������ǂ�������
		// �J�[�\�����ɂ��鐔��(�{�^��)���ǂ���
		if (seNum == i && selectKind == 5 && judgeRange == true)
		{
			m_pSprite->Draw(m_pImageOptionNum, nStartX + ((i - 22) * 70), nStartY + 470,
				(i - 22) * 50, 100, nWidth, nHeight,nWidthScale, nHeightScale, 1.0f);
			// �J�[�\�������I�����Ă��邩�ǂ���
			if (m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_SPACE) || m_pGMain->m_pDI->CheckJoy(KD_TRG, DIJ_A)
				|| m_pGMain->m_pDI->CheckMouse(KD_TRG, DIM_LBUTTON))
			{
				// �I�𒆂̐����̍X�V
				seSelect = i;
				// �I���������������ʐݒ�Ɏg�������ɕϊ�
				ChangeSelectNum(2);
				// ���ʂ̐ݒ�
				m_pGMain->SetSoundVolume();
				m_pGMain->selectSound->Play();  // �I�����ʉ�
			}
		}
		else {
			m_pSprite->Draw(m_pImageOptionNum, nStartX + ((i - 22) * 70), nStartY + 470,
				(i - 22) * 50, 100, nWidth, nHeight, lightColor); // �����F�ŕ\��
		}
	}
}
// M.S �I�v�V������ʂ̃{�^���̑I������
//��  ���F�Ȃ�
//�߂�l�F�Ȃ�
void CTitleProc::DrawSelectNum(bool judgeRange, int selectKind)
{
	const int nNum = 28; // �I�v�V�����̑I���{�^���̐�
	const float fScale = 1.2f; // �\���{�^���̊g��l 
	// �\���ʒu��X�AY�ʒu
	const int nStartX = 690, nStartY = 80;
	// �{�^���̕��A����
	const int nWidth = 50, nHeight = 50;
	// �g�債���{�^���̕��A����
	const int nWidthScale = nWidth * fScale;
	const int nHeightScale = nHeight * fScale;
	int i; 
	//�I�v�V������ʂ̕`��ƑI������
	for (i = 0; i < nNum; i++)
	{
		if (i < 4) {
			SelectLineNum(judgeRange, selectKind, i);  // ���H��
		}
		else if (i < 10) {
			SelectPassengersNum(judgeRange, selectKind, i);  // ��Ԑl��
		}
		else if (i < 16) {
			SelectWaitTime(judgeRange, selectKind, i);  // �o���܂ł̑҂�����
		}
		else if (i < 22) {
			SelectBgm(judgeRange, selectKind, i);  // BGM����
		}
		else if (i < 28) {
			SelectSe(judgeRange, selectKind, i);  // SE����
		}
	}
}
// M.S �I�v�V������ʂ̕\���A�I������
//��  ���F�Ȃ�
//�߂�l�Fbool true �I�v�V������ʂ̏I��
bool CTitleProc::TitleOption()
{
	BOOL bRet = FALSE;
	const int nNum = 28;         // �z��v�f��
	const float fScale = 1.2f;   // �g��l
	// �I�v�V���������{�^����\������X�AY�ʒu
	const int nStartX = 690, nStartY = 80;  
	// �I�v�V���������{�^���̕��A����
	const int nWidth = 50, nHeight = 50;   
	// �߂�{�^����\������X�AY�ʒu
	const int nStartXBack = 586, nStartYBack = 618; 
	// �߂�{�^���̕��A����
	const int nWidthBack = 194, nHeightBack = 72;   
	// �߂�{�^���̊g�債����
	const int nWidthBackScale = nWidthBack * fScale;
	// �߂�{�^���̊g�債������
	const int nHeightBackScale = nHeightBack * fScale;
	// �����F�ŕ\�����铧���x
	float lightColor = 0.5f;
	int i;
	// ��ʕ\��
	m_pSprite->Draw(m_pImageOption, 0, 0, 0, 0, 
		m_pImageOption->m_dwImageWidth, m_pImageOption->m_dwImageHeight,WINDOW_WIDTH, WINDOW_HEIGHT);
	// �}�E�X�ɂ��I�v�V�����{�^���I��
	for (i = 0; i < nNum; i++)
	{
		if (i < 4) {       // ���H��
			if (CheckMousePos(nStartX + (i * 70), nStartY , nWidth, nHeight) == true)
			{
				linetrainNum = i;     // �}�E�X�J�[�\�����{�^�����ɂ���				
				selectedKindNum = 1;  // �I�����Ă���{�^���������̃Z�b�g
			}	
		}		
		else if (i < 10) { // ��Ԑl��
			if (CheckMousePos(nStartX + ((i - 4) * 70), nStartY + 125, nWidth, nHeight) == true)
			{
				passengersNum = i;    // �}�E�X�J�[�\�����{�^�����ɂ���		
				selectedKindNum = 2;  // �I�����Ă���{�^���������̃Z�b�g 
			}		
		}	
		else if (i < 16) { // ���˂܂ł̑҂�����
			if (CheckMousePos(nStartX + ((i - 10) * 70), nStartY + 245, nWidth, nHeight) == true)
			{
				waitingTime = i;      // �}�E�X�J�[�\�����{�^�����ɂ���		
				selectedKindNum = 3;  // �I�����Ă���{�^���������̃Z�b�g
			}	
		}
		else if (i < 22) { // BGM����
			if (CheckMousePos(nStartX + ((i - 16) * 70), nStartY + 360, nWidth, nHeight) == true)
			{
				bgmNum = i;           // �}�E�X�J�[�\�����{�^�����ɂ���		
				selectedKindNum = 4;  // �I�����Ă���{�^���������̃Z�b�g
			}			
		}
		else if (i < 28) { // SE����
			if (CheckMousePos(nStartX + ((i - 22) * 70), nStartY + 470, nWidth, nHeight) == true)
			{
				seNum = i;            // �}�E�X�J�[�\�����{�^�����ɂ���		
				selectedKindNum = 5;  // �I�����Ă���{�^���������̃Z�b�g
			}
		}
	}
	// �ǂ����̃{�^��(����)���ɃJ�[�\�������邩�ǂ���
	if (selectedKindNum != 0) {
		DrawSelectNum(true, selectedKindNum);
	}
	else {
		DrawSelectNum(false, selectedKindNum);
	}
	selectedKindNum = 0;  // selectedKindNum�̏�����
	// �I���L�[
	    // �߂�{�^����I�𒆂��ǂ���
		if (CheckMousePos(nStartXBack, nStartYBack, nWidthBack, nHeightBack) == true) {
				// �߂�{�^����\��
				m_pSprite->Draw(m_pImageOptionBackButton, nStartXBack - 15, nStartYBack, 0, 0,
					nWidthBack, nHeightBack, nWidthBackScale, nHeightBackScale); 
				// �߂�{�^����I�������肵�����ǂ���
				if (m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_SPACE) || m_pGMain->m_pDI->CheckJoy(KD_TRG, DIJ_A) 
					|| m_pGMain->m_pDI->CheckMouse(KD_TRG, DIM_LBUTTON)) {		
					m_pGMain->selectSound->Play(); // �I�����ʉ�
					ChangeSelectNum(0);            // �I�������肵���I�v�V�����̐��l�ɍX�V
					m_pGMain->FileWrite();         // �X�V���������t�@�C���ɏ�������
					m_dwStatusPhase = 0;           // �^�C�g���Z���N�g��ʂ�
					bRet = TRUE;  // �I�� 
				}
		}
		else {
			m_pSprite->Draw(m_pImageOptionBackButton, nStartXBack, nStartYBack,
				0, 0, nWidthBack, nHeightBack, lightColor); // �����F�ŕ\��
		}
	return bRet;
}
// M.S �����т�����ʂ̑I�𒆃y�[�W�̕\��
//��  ���F�Ȃ�
//�߂�l�F�Ȃ�
void CTitleProc::DrawExplanationPage(int nowPage) {
	// �I�𒆂̃y�[�W��\������
	switch (nowPage) {
	case 0:
		m_pSprite->Draw(m_pImagePage1, 0, 0, 0, 0,
			m_pImagePage1->m_dwImageWidth, m_pImagePage1->m_dwImageHeight, WINDOW_WIDTH, WINDOW_HEIGHT);
		break;
	case 1:
		m_pSprite->Draw(m_pImagePage2, 0, 0, 0, 0,
			m_pImagePage2->m_dwImageWidth, m_pImagePage2->m_dwImageHeight, WINDOW_WIDTH, WINDOW_HEIGHT);
		break;
	case 2:
		m_pSprite->Draw(m_pImagePage3, 0, 0, 0, 0,
			m_pImagePage3->m_dwImageWidth, m_pImagePage3->m_dwImageHeight, WINDOW_WIDTH, WINDOW_HEIGHT);
		break;
	case 3:
		m_pSprite->Draw(m_pImagePage4, 0, 0, 0, 0,
			m_pImagePage4->m_dwImageWidth, m_pImagePage4->m_dwImageHeight, WINDOW_WIDTH, WINDOW_HEIGHT);
		break;
	case 4:
		m_pSprite->Draw(m_pImagePage5, 0, 0, 0, 0,
			m_pImagePage5->m_dwImageWidth, m_pImagePage5->m_dwImageHeight, WINDOW_WIDTH, WINDOW_HEIGHT);
		break;
	case 5:
		m_pSprite->Draw(m_pImagePage6, 0, 0, 0, 0,
			m_pImagePage6->m_dwImageWidth, m_pImagePage6->m_dwImageHeight, WINDOW_WIDTH, WINDOW_HEIGHT);
		break;
	case 6:
		m_pSprite->Draw(m_pImagePage7, 0, 0, 0, 0,
			m_pImagePage7->m_dwImageWidth, m_pImagePage7->m_dwImageHeight, WINDOW_WIDTH, WINDOW_HEIGHT);
		break;
	case 7:
		m_pSprite->Draw(m_pImagePage8, 0, 0, 0, 0,
			m_pImagePage8->m_dwImageWidth, m_pImagePage8->m_dwImageHeight, WINDOW_WIDTH, WINDOW_HEIGHT);
		break;
	}
}
// M.S �����т�����ʂ̕\���A�I������
//��  ���F�Ȃ�
//�߂�l�Fbool true �����т�����ʂ̏I��
bool CTitleProc::TitleExplanation()
{
	BOOL bRet = FALSE;
	const int maxPage = 7;   // �ő�y�[�W��
	const int minPage = 0;   // �ŏ��y�[�W��
	// ���֐i�ރ{�^����\������X�ʒu
	int rightButtonPosX = 1297;
	// ���֐i�ރ{�^����\������Y�ʒu
	int rightButtonPosY = 657;
	// �O�֖߂�{�^����\������X�ʒu
	int leftButtonPosX = 0;
	// �O�֖߂�{�^����\������Y�ʒu
	int leftButtonPosY = 657;
	// ���ցA�O�փ{�^���̕��A����
	int buttonWidth = 69, buttonHeight = 69;
	//�߂�{�^���̊g��l
	const float fScale = 1.2f;
	// �߂�{�^����\������X�AY�ʒu
	const int nStartXBack = 1084, nStartYBack = 690;
	// �߂�{�^���̕��A����
	const int nWidthBack = 194, nHeightBack = 72;
	// �߂�{�^���̊g�債����
	const int nWidthScale = nWidthBack * fScale;
	// �߂�{�^���̊g�債������
	const int nHeightScale = nHeightBack * fScale;
	// �����F�ŕ\�����铧���x
	float lightColor = 0.5f;
	// �I�𒆂̃y�[�W��\������
	DrawExplanationPage(nowPage);
	// ���̖߂�{�^�����ɃJ�[�\�������邩�ǂ���
	if (CheckMousePos(leftButtonPosX, leftButtonPosY, buttonHeight, buttonWidth) == true)
	{
		// �{�^���̕\��
		m_pSprite->Draw(m_pImagePageButton, leftButtonPosX, leftButtonPosY,
			0, 0, buttonWidth, buttonHeight);
		// ���肵�����ǂ���
		if (m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_SPACE) || m_pGMain->m_pDI->CheckJoy(KD_TRG, DIJ_A)
			|| m_pGMain->m_pDI->CheckMouse(KD_TRG, DIM_LBUTTON)) {
			// �y�[�W�ړ��ϐ�������
			nowPage--;
			m_pGMain->turnThePageSound->Play();  // �y�[�W���߂�����ʉ�
		}
	}
	else {
		m_pSprite->Draw(m_pImagePageButton, leftButtonPosX, leftButtonPosY, 
			0, 0, buttonWidth, buttonHeight, lightColor); // �����F�Ń{�^����\��
	}
	// �E�̐i�ރ{�^�����ɃJ�[�\�������邩�ǂ���
	if (CheckMousePos(rightButtonPosX, rightButtonPosY, buttonHeight, buttonWidth) == true)
	{
		// �{�^���̕\��
		m_pSprite->Draw(m_pImagePageButton, rightButtonPosX, rightButtonPosY,
			buttonWidth, 0, buttonWidth, buttonHeight);
		// ���肵�����ǂ���
		if (m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_SPACE) || m_pGMain->m_pDI->CheckJoy(KD_TRG, DIJ_A)
			|| m_pGMain->m_pDI->CheckMouse(KD_TRG, DIM_LBUTTON)) {
			// �N���b�N������y�[�W�ړ��ϐ��𑫂�
			nowPage++;
			m_pGMain->turnThePageSound->Play();  // �y�[�W���߂�����ʉ�
		}
	}
	else {
		m_pSprite->Draw(m_pImagePageButton, rightButtonPosX, rightButtonPosY,
			buttonWidth, 0, buttonWidth, buttonHeight, lightColor);  // �����F�Ń{�^����\��
	}
	// �y�[�W�ړ��ϐ����y�[�W�ő�l���傫��������
	if (nowPage > maxPage) {
		nowPage = minPage; // �y�[�W�ړ��ϐ����y�[�W�ŏ��l�ɃZ�b�g
	}
	// �y�[�W�ړ��ϐ����y�[�W�ŏ��l��菬����������
	else if (nowPage < minPage) {
		nowPage = maxPage; // �y�[�W�ړ��ϐ����y�[�W�ő�l�ɃZ�b�g
	}
	// �I���L�[
	// �߂�{�^�����ɃJ�[�\�������邩�ǂ���
	if (CheckMousePos(nStartXBack, nStartYBack, nWidthBack, nHeightBack) == true) {
		{
			// �߂�{�^����\��
			m_pSprite->Draw(m_pImageOptionBackButton, nStartXBack - 15, nStartYBack,
				0, 0, nWidthBack, nHeightBack,nWidthScale, nHeightScale); 
			// ���肵�����ǂ���
			if (m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_SPACE) || m_pGMain->m_pDI->CheckJoy(KD_TRG, DIJ_A)
				|| m_pGMain->m_pDI->CheckMouse(KD_TRG, DIM_LBUTTON))
			{
				m_pGMain->selectSound->Play();  // �I�����ʉ�
				m_dwStatusPhase = 0;  // �^�C�g���Z���N�g��ʂ�
				bRet = TRUE;  // �I��
			}
		}
	}
	else {
		m_pSprite->Draw(m_pImageOptionBackButton, nStartXBack, nStartYBack,
			0, 0, nWidthBack, nHeightBack, lightColor); // �����F�Ń{�^����\��
	}
	return bRet;
}
// M.S �ʏ탂�[�h�̃X�R�A�̕\��(�摜�̐�������\��������)
//��  ���F�Ȃ�
//�߂�l�F�Ȃ�
void CTitleProc::DrawManScoreNormalMode() {
	int DestXHigh = 700;   // ��Ԑl��(��)�̃X�R�A�̕\���ʒuX
	int DestYHigh = 197;   // ��Ԑl��(��)�̃X�R�A�̕\���ʒuY
	int DestXMiddle = 700; // ��Ԑl��(��)�̃X�R�A�̕\���ʒuX
	int DestYMiddle = 320; // ��Ԑl��(��)�̃X�R�A�̕\���ʒuY
	int DestXLow = 700;    // ��Ԑl��(��)�̃X�R�A�̕\���ʒuX
	int DestYLow = 448;    // ��Ԑl��(��)�̃X�R�A�̕\���ʒuY
	int nWidth = 39;       // �\�����鐔���̕�
	int nHeight = 53;      // �\�����鐔���̍���
	// ��Ԑl������e�l�̃X�R�A���o��
	totalHighManScore = m_pGMain->m_pEnmProc->getHighMan * 30;
	totalMiddleManScore = m_pGMain->m_pEnmProc->getMiddleMan * 20;
	totalLowManScore = m_pGMain->m_pEnmProc->getLowMan * 10;
	// �e�l�̃X�R�A�𑫂��ăg�[�^���X�R�A���o��
	totalScore = totalHighManScore + totalMiddleManScore + totalLowManScore;
	// ��Ԑl��(��)�̃X�R�A��1�����̐������o��
	int arrayNumHigh = m_pGMain->m_pBackForeProc->VariableAnalysis(m_pGMain->m_pEnmProc->getHighMan);
	for (int i = 0; arrayNumHigh > i; i++) {  // ��Ԑl��(��)�̃X�R�A�̕\��(1������)
		// numArray�ɂ͏�Ԑl��(��)�̃X�R�A��1�����̐����������Ă���
		m_pSprite->Draw(m_pGMain->m_pBackForeProc->GetRankingNum(), DestXHigh + (i * 59), DestYHigh,
			m_pGMain->m_pBackForeProc->numArray[i] * 39, 0, nWidth, nHeight);
	}
	// ��Ԑl��(��)�̃X�R�A��1�����̐������o��
	int arrayNumMiddle = m_pGMain->m_pBackForeProc->VariableAnalysis(m_pGMain->m_pEnmProc->getMiddleMan);
	for (int i = 0; arrayNumMiddle > i; i++) {  // ��Ԑl��(��)�̃X�R�A�̕\��(1������)
		// numArray�ɂ͏�Ԑl��(��)�̃X�R�A��1�����̐����������Ă���
		m_pSprite->Draw(m_pGMain->m_pBackForeProc->GetRankingNum(), DestXMiddle + (i * 59), DestYMiddle,
			m_pGMain->m_pBackForeProc->numArray[i] * 39, 0, nWidth, nHeight);
	}
	// ��Ԑl��(��)�̃X�R�A��1�����̐������o��
	int arrayNumLow = m_pGMain->m_pBackForeProc->VariableAnalysis(m_pGMain->m_pEnmProc->getLowMan);
	for (int i = 0; arrayNumLow > i; i++) {  // ��Ԑl��(��)�̃X�R�A�̕\��(1������)
		// numArray�ɂ͏�Ԑl��(��)�̃X�R�A��1�����̐����������Ă���
		m_pSprite->Draw(m_pGMain->m_pBackForeProc->GetRankingNum(), DestXLow + (i * 59), DestYLow, 
			m_pGMain->m_pBackForeProc->numArray[i] * 39, 0, nWidth, nHeight);
	}
}
// M.S �����L���O���[�h�̃X�R�A�̕\��(�摜�̐�������\��������)
//��  ���F�Ȃ�
//�߂�l�F�Ȃ�
void CTitleProc::DrawManScoreRankingMode() {
	int DestXHigh = 700;   // ��Ԑl��(��)�̃X�R�A�̕\���ʒuX
	int DestYHigh = 197;   // ��Ԑl��(��)�̃X�R�A�̕\���ʒuY
	int DestXMiddle = 700; // ��Ԑl��(��)�̃X�R�A�̕\���ʒuX
	int DestYMiddle = 320; // ��Ԑl��(��)�̃X�R�A�̕\���ʒuY
	int DestXLow = 700;    // ��Ԑl��(��)�̃X�R�A�̕\���ʒuX
	int DestYLow = 448;    // ��Ԑl��(��)�̃X�R�A�̕\���ʒuY
	int nWidth = 39;       // �\�����鐔���̕�
	int nHeight = 53;      // �\�����鐔���̍���
	// ��Ԑl������e�l�̃X�R�A���o��
	totalHighManScore = m_pGMain->rankRedMan * 30;
	totalMiddleManScore = m_pGMain->rankYellowMan * 20;
	totalLowManScore = m_pGMain->rankBlueMan * 10;
	// �e�l�̃X�R�A�𑫂��ăg�[�^���X�R�A���o��
	totalScore = totalHighManScore + totalMiddleManScore + totalLowManScore;
	// ��Ԑl��(��)�̃X�R�A��1�����̐������o��
	int arrayNumHigh = m_pGMain->m_pBackForeProc->VariableAnalysis(m_pGMain->rankRedMan);
	for (int i = 0; arrayNumHigh > i; i++) {  // ��Ԑl��(��)�̃X�R�A�̕\��(1������)
		// numArray�ɂ͏�Ԑl��(��)�̃X�R�A��1�����̐����������Ă���
		m_pSprite->Draw(m_pGMain->m_pBackForeProc->GetRankingNum(), DestXHigh + (i * 59), DestYHigh, 
			m_pGMain->m_pBackForeProc->numArray[i] * 39, 0, nWidth, nHeight);
	}
	// ��Ԑl��(��)�̃X�R�A��1�����̐������o��
	int arrayNumMiddle = m_pGMain->m_pBackForeProc->VariableAnalysis(m_pGMain->rankYellowMan);
	for (int i = 0; arrayNumMiddle > i; i++) {  // ��Ԑl��(��)�̃X�R�A�̕\��(1������)
		// numArray�ɂ͏�Ԑl��(��)�̃X�R�A��1�����̐����������Ă���
		m_pSprite->Draw(m_pGMain->m_pBackForeProc->GetRankingNum(), DestXMiddle + (i * 59), DestYMiddle,
			m_pGMain->m_pBackForeProc->numArray[i] * 39, 0, nWidth, nHeight);
	}
	// ��Ԑl��(��)�̃X�R�A��1�����̐������o��
	int arrayNumLow = m_pGMain->m_pBackForeProc->VariableAnalysis(m_pGMain->rankBlueMan);
	for (int i = 0; arrayNumLow > i; i++) {  // ��Ԑl��(��)�̃X�R�A�̕\��(1������)
		// numArray�ɂ͏�Ԑl��(��)�̃X�R�A��1�����̐����������Ă���
		m_pSprite->Draw(m_pGMain->m_pBackForeProc->GetRankingNum(), DestXLow + (i * 59), DestYLow, 
			m_pGMain->m_pBackForeProc->numArray[i] * 39, 0, nWidth, nHeight);
	}
}
// M.S �g�[�^���X�R�A�̕\��(�摜�̐�������\��������)
//��  ���F�Ȃ�
//�߂�l�F�Ȃ�
void CTitleProc::DrawTotalScore() {
	int nWidth = 39;       // �\�����鐔���̕�
	int nHeight = 53;      // �\�����鐔���̍���
	int DestXTotal = 636;  // �\������g�[�^���X�R�A�̕\���ʒuX
	int DestYTotal = 661;  // �\������g�[�^���X�R�A�̕\���ʒuY
	// �g�[�^���X�R�A��1�����̐������o��
	int arrayTotalScore = m_pGMain->m_pBackForeProc->VariableAnalysis(totalScore);
	for (int i = 0; arrayTotalScore > i; i++) { // �g�[�^���X�R�A�̕\��(1������)
	    // numArray�ɂ̓g�[�^���X�R�A��1�����̐����������Ă���
		m_pSprite->Draw(m_pGMain->m_pBackForeProc->GetRankingNum(), DestXTotal + (i * 59), DestYTotal, 
			m_pGMain->m_pBackForeProc->numArray[i] * 39, 0, nWidth, nHeight);
	}
}
// M.S �����L���O�̕��ׂ���
// ��  ���F�Ȃ�
// �߂�l�F�Ȃ�
void CTitleProc::SortRanking() {
	// �����L���O�̐����ϐ�
	int numberOne = 1, numberTwo = 2, numberThree = 3, numberFour = 4, numberFive = 5;
	// ����̃v���C�X�R�A��1�ʂ��傫���ꍇ�̕��בւ�
	if (totalScore > m_pGMain->rankOne) {
		m_pGMain->rankFive = m_pGMain->rankFour;
		m_pGMain->rankFour = m_pGMain->rankThree;
		m_pGMain->rankThree = m_pGMain->rankTwo;
		m_pGMain->rankTwo = m_pGMain->rankOne;
		m_pGMain->rankOne = totalScore;
		myRanking = numberOne;
	}
	// ����̃v���C�X�R�A��2�ʂ��傫���ꍇ�̕��בւ�
	else if (totalScore > m_pGMain->rankTwo) {
		m_pGMain->rankFive = m_pGMain->rankFour;
		m_pGMain->rankFour = m_pGMain->rankThree;
		m_pGMain->rankThree = m_pGMain->rankTwo;
		m_pGMain->rankTwo = totalScore;
		myRanking = numberTwo;
	}
	// ����̃v���C�X�R�A��3�ʂ��傫���ꍇ�̕��בւ�
	else if (totalScore > m_pGMain->rankThree) {
		m_pGMain->rankFive = m_pGMain->rankFour;
		m_pGMain->rankFour = m_pGMain->rankThree;
		m_pGMain->rankThree = totalScore;
		myRanking = numberThree;
	}
	// ����̃v���C�X�R�A��4�ʂ��傫���ꍇ�̕��בւ�
	else if (totalScore > m_pGMain->rankFour) {
		m_pGMain->rankFive = m_pGMain->rankFour;
		m_pGMain->rankFour = totalScore;
		myRanking = numberFour;
	}
	// ����̃v���C�X�R�A��5�ʂ��傫���ꍇ�̕��בւ�
	else if (totalScore > m_pGMain->rankFive) {
		m_pGMain->rankFive = totalScore;
		myRanking = numberFive;
	}
}
// M.S �����L���O�̒ǉ��A�\��(�摜�̐�������\��������)
//��  ���F�Ȃ�
//�߂�l�F�Ȃ�
void CTitleProc::AddRanking() {
	int DestXOne = 466;     // �����L���O1�ʃX�R�A�\����X�ʒu
	int DestYOne = 216;     // �����L���O1�ʃX�R�A�\����Y�ʒu
	int DestXTwo = 466;     // �����L���O2�ʃX�R�A�\����X�ʒu
	int DestYTwo = 341;     // �����L���O2�ʃX�R�A�\����Y�ʒu
	int DestXThree = 466;   // �����L���O3�ʃX�R�A�\����X�ʒu
	int DestYThree = 463;   // �����L���O3�ʃX�R�A�\����Y�ʒu
	int DestXFour = 466;    // �����L���O4�ʃX�R�A�\����X�ʒu
	int DestYFour = 581;    // �����L���O4�ʃX�R�A�\����Y�ʒu
	int DestXFive = 466;    // �����L���O5�ʃX�R�A�\����X�ʒu
	int DestYFive = 677;    // �����L���O5�ʃX�R�A�\����Y�ʒu
	int nWidth = 39;        // �\�����郉���L���O�����̕�
	int nHeight = 53;       // �\�����郉���L���O�����̍���
	int blinkingTimeReset = 0;     // �_�ŕ\�������鎞�Ԃ̏�����
	int goAroundBlinkingTime = 60; // �_�ŕ\�������鎞�Ԃ�1����������
	int halfBlinkingTime = 30;     // �_�ŕ\�������鎞�Ԃ�������������
	float lightColor = 0.3f;       // �����F�ŕ\�����铧���x
	// �����L���O�̐����ϐ�
	int numberOne = 1, numberTwo = 2, numberThree = 3, numberFour = 4, numberFive = 5;
	// �����L���O�̕��בւ������Ă��Ȃ����ǂ���
	if (initialRankingSorting == true) {  
		SortRanking();                 // �����L���O�̕��ׂ���
		initialRankingSorting = false; // �����L���O�̕��בւ�������
	}
	// ���݂�1�ʂ̃X�R�A��1�����̐������o��
	int arrayOne = m_pGMain->m_pBackForeProc->VariableAnalysis(m_pGMain->rankOne);
	for (int i = 0; arrayOne > i; i++) {  // ���݂�1�ʂ̃X�R�A�̕\��(1������)
		if (myRanking == numberOne && rankingTime <= halfBlinkingTime) {  // ����̃v���C�����N�Ȃ��rankingTime�̓_�ŕ\��
			// numArray�ɂ͌��݂�1�ʂ̃X�R�A��1�����̐����������Ă���
			m_pSprite->Draw(m_pGMain->m_pBackForeProc->GetRankingNum(), DestXOne + (i * 59), DestYOne,
				m_pGMain->m_pBackForeProc->numArray[i] * 39, 0, nWidth, nHeight, lightColor);
		}
		else {
			m_pSprite->Draw(m_pGMain->m_pBackForeProc->GetRankingNum(), DestXOne + (i * 59), DestYOne,
				m_pGMain->m_pBackForeProc->numArray[i] * 39, 0, nWidth, nHeight);
		}
	}
	// ���݂�2�ʂ̃X�R�A��1�����̐������o��
	int arrayTwo = m_pGMain->m_pBackForeProc->VariableAnalysis(m_pGMain->rankTwo);
	for (int i = 0; arrayTwo > i; i++) {  // ���݂�2�ʂ̃X�R�A�̕\��(1������)
		if (myRanking == numberTwo && rankingTime <= halfBlinkingTime) {  // ����̃v���C�����N�Ȃ��rankingTime�̓_�ŕ\��
			// numArray�ɂ͌��݂�2�ʂ̃X�R�A��1�����̐����������Ă���
			m_pSprite->Draw(m_pGMain->m_pBackForeProc->GetRankingNum(), DestXTwo + (i * 59), DestYTwo, 
				m_pGMain->m_pBackForeProc->numArray[i] * 39, 0, nWidth, nHeight, lightColor);
		}
		else {
			m_pSprite->Draw(m_pGMain->m_pBackForeProc->GetRankingNum(), DestXTwo + (i * 59), DestYTwo,
				m_pGMain->m_pBackForeProc->numArray[i] * 39, 0, nWidth, nHeight);
		}
	}
	// ���݂�3�ʂ̃X�R�A��1�����̐������o��
	int arrayThree = m_pGMain->m_pBackForeProc->VariableAnalysis(m_pGMain->rankThree);
	for (int i = 0; arrayThree > i; i++) {  // ���݂�3�ʂ̃X�R�A�̕\��(1������)
		if (myRanking == numberThree && rankingTime <= halfBlinkingTime) {  // ����̃v���C�����N�Ȃ��rankingTime�̓_�ŕ\��
			// numArray�ɂ͌��݂�3�ʂ̃X�R�A��1�����̐����������Ă���
			m_pSprite->Draw(m_pGMain->m_pBackForeProc->GetRankingNum(), DestXThree + (i * 59), DestYThree,
				m_pGMain->m_pBackForeProc->numArray[i] * 39, 0, nWidth, nHeight, lightColor);
		}
		else {
			m_pSprite->Draw(m_pGMain->m_pBackForeProc->GetRankingNum(), DestXThree + (i * 59), DestYThree,
				m_pGMain->m_pBackForeProc->numArray[i] * 39, 0, nWidth, nHeight);
		}
	}
	// ���݂�4�ʂ̃X�R�A��1�����̐������o��
	int arrayFour = m_pGMain->m_pBackForeProc->VariableAnalysis(m_pGMain->rankFour);
	for (int i = 0; arrayFour > i; i++) {  // ���݂�4�ʂ̃X�R�A�̕\��(1������)
		if (myRanking == numberFour && rankingTime <= halfBlinkingTime) {  // ����̃v���C�����N�Ȃ��rankingTime�̓_�ŕ\��
			// numArray�ɂ͌��݂�4�ʂ̃X�R�A��1�����̐����������Ă���
			m_pSprite->Draw(m_pGMain->m_pBackForeProc->GetRankingNum(), DestXFour + (i * 59), DestYFour,
				m_pGMain->m_pBackForeProc->numArray[i] * 39, 0, nWidth, nHeight, lightColor);
		}
		else {
			m_pSprite->Draw(m_pGMain->m_pBackForeProc->GetRankingNum(), DestXFour + (i * 59), DestYFour, 
				m_pGMain->m_pBackForeProc->numArray[i] * 39, 0, nWidth, nHeight);
		}
	}
	// ���݂�5�ʂ̃X�R�A��1�����̐������o��
	int arrayFive = m_pGMain->m_pBackForeProc->VariableAnalysis(m_pGMain->rankFive);
	for (int i = 0; arrayFive > i; i++) {  // ���݂�5�ʂ̃X�R�A�̕\��(1������)
		if (myRanking == numberFive && rankingTime <= halfBlinkingTime) {  // ����̃v���C�����N�Ȃ��rankingTime�̓_�ŕ\��
			// numArray�ɂ͌��݂�5�ʂ̃X�R�A��1�����̐����������Ă���
			m_pSprite->Draw(m_pGMain->m_pBackForeProc->GetRankingNum(), DestXFive + (i * 59), DestYFive,
				m_pGMain->m_pBackForeProc->numArray[i] * 39, 0, nWidth, nHeight, lightColor);
		}
		else {
			m_pSprite->Draw(m_pGMain->m_pBackForeProc->GetRankingNum(), DestXFive + (i * 59), DestYFive,
				m_pGMain->m_pBackForeProc->numArray[i] * 39, 0, nWidth, nHeight);
		}
	} // �_�ŕ\��������ꍇ�ɕK�v�ɂȂ�ϐ��̏���(30���Ƃɓ_�ł�������)
	if (rankingTime <= goAroundBlinkingTime) {
		rankingTime++;
	}
	else {
		rankingTime = blinkingTimeReset;
	}
}
//------------------------------------------------------------------------
//
//	�Q�[���N�����[�̕\��	
//
//------------------------------------------------------------------------
void CTitleProc::GameClear()
{
	m_pGMain->m_pD3D->SetViewPort(false);  // M.S 1��ʂ̕\��
	gameClearCount++;      //�Q�[���N���A�\�����Ԃ̃J�E���g
	// M.S �Q�[���N���A��ʏ���
	if (gameClearCount <= 250) {
		// M.S �N���ABGM��炵�Ă��Ȃ��ꍇ
		if (RingSound == false) {
			m_pGMain->gameBgm->Stop();  // M.S �Q�[��BGM���~�߂�
			m_pGMain->gameClearBgm->Play(AUDIO_LOOP); // M.S �N���ABGM��炷
			RingSound = true;  // M.S �N���ABGM��炵��
		}
		// �Q�[���N���A��ʂ̕\��
		m_pSprite->Draw(m_pImageClear, 0, 0, 0, 0, m_pImageTitle->m_dwImageWidth,
			m_pImageTitle->m_dwImageHeight, WINDOW_WIDTH, WINDOW_HEIGHT);
	}
	// M.S ���U���g��ʏ���
	else if (gameClearCount > 250 && gameClearCount <= 600) {
		// M.S ���U���g��ʂ̕\��
		m_pSprite->Draw(m_pImageResult, 0, 0, 0, 0, m_pImageTitle->m_dwImageWidth,
			m_pImageTitle->m_dwImageHeight, WINDOW_WIDTH, WINDOW_HEIGHT);
		// M.S ���U���gBGM��炵�Ă��Ȃ��ꍇ
		if (RingResultSound == false) {
			m_pGMain->gameClearBgm->Stop();  // M.S �N���ABGM���~�߂�
			m_pGMain->resultBgm->Play(AUDIO_LOOP); // M.S ���U���gBGM��炷
			RingResultSound = true;  // M.S ���U���gBGM��炵��
		}
		// M.S �����L���O���[�h���ǂ���
		if (m_pGMain->m_dwGameMode == 3) {
			DrawManScoreRankingMode(); // M.S �e�l�X�R�A�\��
		}
		else {
			DrawManScoreNormalMode(); // M.S �e�l�X�R�A�\��	
		}
		DrawTotalScore(); // �g�[�^���X�R�A�̕\��
	}
	// M.S �����L���O��ʏ���  �w�莞�ԂŃ����L���O���[�h�̏ꍇ
	else if (gameClearCount > 500 && gameClearCount <= 700 && m_pGMain->m_dwGameMode == 3) {
		// M.S �����L���O��ʂ̕\��
		m_pSprite->Draw(m_pImageRanking, 0, 0, 0, 0, m_pImageTitle->m_dwImageWidth,
			m_pImageTitle->m_dwImageHeight, WINDOW_WIDTH, WINDOW_HEIGHT);
		// M.S �����L���O�̒ǉ�
		AddRanking();
		// M.S �����L���O���t�@�C���ɏ�������ł��Ȃ��ꍇ
		if (ScoreWriteProcess == false) {
			m_pGMain->FileWrite(); // M.S �t�@�C���ɏ�������
			ScoreWriteProcess = true; // M.S �������񂾃t���O��true
		}
	}
	// M.S �Q�[���I������  �����L���O���[�h�Ƃ��̑��̃��[�h�Ŏw�莞�Ԃ𕪂���
	else if (gameClearCount > 700 || gameClearCount > 600 && gameClearCount <= 700
		&& (m_pGMain->m_dwGameMode == 1 || m_pGMain->m_dwGameMode == 2)) {
		m_pGMain->resultBgm->Stop();  // M.S ���U���gBGM���~�߂�
		// M.S �ʏ탂�[�h�̏ꍇ
		if (m_pGMain->m_dwGameMode == 1 || m_pGMain->m_dwGameMode == 2) {
			// M.S �Z�[�u�f�[�^�̏�����
			m_pGMain->traveledStar = 0;             // M.S �s�������̐�
			m_pGMain->haveToGoStar = 0;             // M.S �s���ׂ����̐�
			m_pGMain->m_pEnmProc->getHighMan = 0;   // M.S ��Ԑl��(��)
			m_pGMain->m_pEnmProc->getMiddleMan = 0; // M.S ��Ԑl��(��)
			m_pGMain->m_pEnmProc->getLowMan = 0;    // M.S ��Ԑl��(��)
			m_pGMain->redMan = 0;     // M.S �t�@�C���ɏ������ޏ�Ԑl��(��)
			m_pGMain->yellowMan = 0;  // M.S �t�@�C���ɏ������ޏ�Ԑl��(��)
			m_pGMain->blueMan = 0;    // M.S �t�@�C���ɏ������ޏ�Ԑl��(��)
			for (int i = 0; i < 25; i++) {
				m_pGMain->starArray[i] = 0; // M.S �����������̔z��
			}
			m_pGMain->FileWrite();  // M.S �t�@�C���ɏ�������
		}
		// M.S ������
		myRanking = 0;        // M.S ���ʕϐ� 
		rankingTime = 0;      // M.S �����L���O���ԃJ�E���g
		gameClearCount = 0;   // M.S �N���A
		ScoreWriteProcess = false;  // M.S �t�@�C���ւ̏������݃t���O
		m_pGMain->m_pPcProc->oneScreenFlag = false; // M.S 1��ʕ`��t���O
		m_pGMain->m_dwGameStatus = GAMEEND; // �Q�[���I����
	}
}
//------------------------------------------------------------------------
//
//	�Q�[���I�[�o�[�̕\��	
//
//------------------------------------------------------------------------
void CTitleProc::GameOver()
{
	// M.S 1��ʂ݂̂̕`��֕ύX
	m_pGMain->m_pD3D->SetViewPort(false);  // 1��ʂ̕\��
	// �Q�[���I�[�o�[��ʕ\��
	m_pSprite->Draw(m_pImageOver, 0, 0, 0, 0, m_pImageTitle->m_dwImageWidth, m_pImageTitle->m_dwImageHeight, WINDOW_WIDTH, WINDOW_HEIGHT);
	// M.S �Q�[���I�[�o�[BGM��炵�Ă��Ȃ����ǂ���
	if (RingSound == false) {
		m_pGMain->gameBgm->Stop();                // M.S �Q�[����BGM���~�߂�
		m_pGMain->gameOverBgm->Play(AUDIO_LOOP);  // M.S �Q�[���I�[�o�[BGM��炷
		RingSound = true;   // M.S �Q�[���I�[�o�[BGM��炵�ς�(RingSouund��true)�ɂ���
	}
	// M.S �Q�[���I�[�o�[�̏I�����Ԃ�+1
	gameOverCount++;
	// M.S ����܂���gameOverCount��400���傫�����ǂ���
	if (m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_SPACE) || m_pGMain->m_pDI->CheckJoy(KD_DAT, DIJ_A)
		|| m_pGMain->m_pDI->CheckMouse(KD_DAT, DIM_LBUTTON) || gameOverCount > 400 )
	{
		m_pGMain->gameOverBgm->Stop();       // M.S �Q�[���I�[�o�[BGM���~�߂�
		m_pGMain->m_dwGameStatus = GAMEEND;  // M.S �Q�[���̏I��
		// M.S 1��1��ʂ̂ݕ`��t���O��false�AgameOverCount��0�ɂ���
		m_pGMain->m_pPcProc->oneScreenFlag = false; // M.S 1��ʕ\���t���O��false
		gameOverCount = 0;   // M.S �Q�[���I�[�o�[���ԃJ�E���g�̏�����
	}
}
//------------------------------------------------------------------------
//
// �}�E�X�J�[�\�����w�肵����`���ɂ��邩�ǂ����𔻒肷��
//
// ����  int nPosX,  int nPosY     ��`������W
//       int nWidth, int nHeight   ��`�̕��ƍ���
//
// �߂�l  BOOL  TRUE:��`���ɂ���    FALSE:��`���ɖ���
//
//------------------------------------------------------------------------
bool CTitleProc::CheckMousePos(int nPosX, int nPosY, int nWidth, int nHeight)
{
	POINT MPos = m_pGMain->m_pDI->GetMousePos();
	if (MPos.x >= nPosX && MPos.x <= nPosX + nWidth &&
		MPos.y >= nPosY && MPos.y <= nPosY + nHeight)
	{
		return TRUE;  // ��`���ɂ���
	}
	else {
		return FALSE;  // ��`���ɖ���
	}
}
// M.S �����L���O�m�F��ʂ̕\��(�摜�̐�������\��������)
//��  ���F�Ȃ�
//�߂�l�F�Ȃ�
void CTitleProc::DrawRanking()
{
	m_pGMain->m_pD3D->SetViewPort(false);   // 1��ʂ̕\��
	// �����L���O�m�F��ʂ̕\��
	m_pSprite->Draw(m_pImageRanking, 0, 0, 0, 0, m_pImageTitle->m_dwImageWidth, 
		m_pImageTitle->m_dwImageHeight, WINDOW_WIDTH, WINDOW_HEIGHT);
	int DestXHigh = 700;   // ��Ԑl��(��)�̃X�R�A�̕\���ʒuX
	int DestYHigh = 197;   // ��Ԑl��(��)�̃X�R�A�̕\���ʒuY
	int DestXMiddle = 700; // ��Ԑl��(��)�̃X�R�A�̕\���ʒuX
	int DestYMiddle = 320; // ��Ԑl��(��)�̃X�R�A�̕\���ʒuY
	int DestXLow = 700;    // ��Ԑl��(��)�̃X�R�A�̕\���ʒuX
	int DestYLow = 448;    // ��Ԑl��(��)�̃X�R�A�̕\���ʒuY
	int nWidth = 39;       // �\�����鐔���̕�
	int nHeight = 53;      // �\�����鐔���̍���
	int DestXTotal = 636;  // �\������g�[�^���X�R�A�̕\���ʒuX
	int DestYTotal = 661;  // �\������g�[�^���X�R�A�̕\���ʒuY
	int DestXOne = 466;     // �����L���O1�ʃX�R�A�\����X�ʒu
	int DestYOne = 216;     // �����L���O1�ʃX�R�A�\����Y�ʒu
	int DestXTwo = 466;     // �����L���O2�ʃX�R�A�\����X�ʒu
	int DestYTwo = 341;     // �����L���O2�ʃX�R�A�\����Y�ʒu
	int DestXThree = 466;   // �����L���O3�ʃX�R�A�\����X�ʒu
	int DestYThree = 463;   // �����L���O3�ʃX�R�A�\����Y�ʒu
	int DestXFour = 466;    // �����L���O4�ʃX�R�A�\����X�ʒu
	int DestYFour = 581;    // �����L���O4�ʃX�R�A�\����Y�ʒu
	int DestXFive = 466;    // �����L���O5�ʃX�R�A�\����X�ʒu
	int DestYFive = 677;    // �����L���O5�ʃX�R�A�\����Y�ʒu
	int nStartXBack = 1178; // �߂�{�^����\������X�ʒu
	int nStartYBack = 688;  // �߂�{�^����\������Y�ʒu
	int nWidthBack = 173;  	// �߂�{�^���̕�
	int nHeightBack = 70;   // �߂�{�^���̍���
	float lightColor = 0.5f;  // �����F�ŕ\�����铧���x
	// ���݂�1�ʂ̃X�R�A��1�����̐������o��
	int arrayOne = m_pGMain->m_pBackForeProc->VariableAnalysis(m_pGMain->rankOne); 
	for (int i = 0; arrayOne > i; i++) { // ���݂�1�ʂ̃X�R�A�̕\��(1������)
			// numArray�ɂ͌��݂�1�ʂ̃X�R�A��1�����̐����������Ă���
			m_pSprite->Draw(m_pGMain->m_pBackForeProc->GetRankingNum(), DestXOne + (i * 59), DestYOne,
				m_pGMain->m_pBackForeProc->numArray[i] * 39, 0, nWidth, nHeight);
	}
	// ���݂�2�ʂ̃X�R�A��1�����̐������o��
	int arrayTwo = m_pGMain->m_pBackForeProc->VariableAnalysis(m_pGMain->rankTwo);
	for (int i = 0; arrayTwo > i; i++) { // ���݂�2�ʂ̃X�R�A�̕\��(1������)
			// numArray�ɂ͌��݂�2�ʂ̃X�R�A��1�����̐����������Ă���
			m_pSprite->Draw(m_pGMain->m_pBackForeProc->GetRankingNum(), DestXTwo + (i * 59), DestYTwo, 
				m_pGMain->m_pBackForeProc->numArray[i] * 39, 0, nWidth, nHeight);
	}
	// ���݂�3�ʂ̃X�R�A��1�����̐������o��
	int arrayThree = m_pGMain->m_pBackForeProc->VariableAnalysis(m_pGMain->rankThree);
	for (int i = 0; arrayThree > i; i++) { // ���݂�3�ʂ̃X�R�A�̕\��(1������)
			// numArray�ɂ͌��݂�3�ʂ̃X�R�A��1�����̐����������Ă���
			m_pSprite->Draw(m_pGMain->m_pBackForeProc->GetRankingNum(), DestXThree + (i * 59), DestYThree,
				m_pGMain->m_pBackForeProc->numArray[i] * 39, 0, nWidth, nHeight);
	}
	// ���݂�4�ʂ̃X�R�A��1�����̐������o��
	int arrayFour = m_pGMain->m_pBackForeProc->VariableAnalysis(m_pGMain->rankFour);
	for (int i = 0; arrayFour > i; i++) { // ���݂�4�ʂ̃X�R�A�̕\��(1������)
			// numArray�ɂ͌��݂�4�ʂ̃X�R�A��1�����̐����������Ă���
			m_pSprite->Draw(m_pGMain->m_pBackForeProc->GetRankingNum(), DestXFour + (i * 59), DestYFour, 
				m_pGMain->m_pBackForeProc->numArray[i] * 39, 0, nWidth, nHeight);
	}
	// ���݂�5�ʂ̃X�R�A��1�����̐������o��
	int arrayFive = m_pGMain->m_pBackForeProc->VariableAnalysis(m_pGMain->rankFive);
	for (int i = 0; arrayFive > i; i++) { // ���݂�5�ʂ̃X�R�A�̕\��(1������)
			// numArray�ɂ͌��݂�5�ʂ̃X�R�A��1�����̐����������Ă���
			m_pSprite->Draw(m_pGMain->m_pBackForeProc->GetRankingNum(), DestXFive + (i * 59), DestYFive,
				m_pGMain->m_pBackForeProc->numArray[i] * 39, 0, nWidth, nHeight);
	}
	// �߂�{�^�����ɃJ�[�\�������邩�ǂ���
	if (CheckMousePos(nStartXBack, nStartYBack, nWidthBack, nHeightBack) == true) {
		// �߂�{�^����\��
		m_pSprite->Draw(m_pImageSaveWarning, nStartXBack, nStartYBack, 
			173, 378, nWidthBack, nHeightBack);
		// �߂�{�^�������肵�����ǂ���
		if (m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_SPACE) || m_pGMain->m_pDI->CheckJoy(KD_TRG, DIJ_A)
			|| m_pGMain->m_pDI->CheckMouse(KD_TRG, DIM_LBUTTON)) {
			m_dwStatusPhase = 0; // �^�C�g���Z���N�g��
			m_pGMain->selectSound->Play(); // �I�����ʉ�
		}
	}
	else {
		m_pSprite->Draw(m_pImageSaveWarning, nStartXBack, nStartYBack,
			173, 378, nWidthBack, nHeightBack, lightColor); // �߂�{�^���𔖂��F�ŕ\��
	}
}