//=============================================================================
//		�R�c�Q�[���v���O����
//		�b�R�c�`�����P�P�Q�@�@�@�@�@�@                 ver 3.0        2021.1.11
//		�O�i�E�w�i							                   BackFore.cpp
//=============================================================================
#include  "BackFore.h"
#include  "Playchar.h"
#include  "Title.h"
#include  "Enemy.h"
#include  "Effect.h"


//============================================================================
//
// �O�i�E�w�i�v���V�[�W���̃R���X�g���N�^
//
// ---------------------------------------------------------------------------
CBackForeProc::CBackForeProc(CGameMain* pGMain)
{
	m_pGMain = pGMain;
	m_pImageForegrd = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/foregrd3.png")); // �X�v���C�g�C���[�W�̃��[�h
	m_pSprite = new CSprite(m_pGMain->m_pShader); // �X�v���C�g�̐���
	m_pImageDynamicStarScene = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/platra_gameUI.png"));
	m_pImagePlacementSceneNum = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/platra_gameNum.png"));
	m_pImageStarBridgeSaving = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/Saving.png"));
	m_pImageRankingNum = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/rankingNum.png"));
	m_pImageStarBridgeButton = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/StarBridgeButton.png"));
	m_pImageRemainingStar = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/remainingStarNotification.png"));
	m_pImageLineKind = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/allLineKindDisplay.png"));
	m_pImageLinePermission = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/lineKindPermission.png"));
	m_pImageGaugeGlitter = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/tktk_Recovery_17L.png"));
	m_pImageGoalButton = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/goalButton.png"));

	// M.S �������牺�̃R���X�g���N�^�̓��e�͒ǉ����܂���
	////// ��--------------------------------------------------------------------
	// �҂����Ԃ̃J�E���g�����̏�����
    waitingDrawTime = 60;
	// �\���p�J�E���g�����ۑ��ϐ�
	initialDraw = 0;
	// �˂����������������ǂ����ۑ��ϐ�
	builtStarBridge = false;
	// �_�ŃJ�E���g����
	starBridgeSceneNext = 50;
	starBridgeSceneTime = 0;
	// �_�ł�����J�E���g�ϐ�
	buttonBlinking = 0;
	// ���̐��֍s���{�^���p�ʒu�ϐ�
	DestXStarBridgeButton = 1157;
	DestYStarBridgeButton = 253;
	nHeightScaleStarBridgeButton = 94 * 1.1f;
	nWidthScaleStarBridgeButton = 154 * 1.1f;
	// ���˂܂ł̃J�E���g�p�ϐ�
	drawWaitingNum = 0;
	// ���˂܂ł̃J�E���g�̐����Z�b�g����x�̂ݍs���ϐ�
	initialWaitingNumSet = true;
	// ���˂܂ł̃J�E���g�̉���炷�t���O
	ringTime = true;
	// �Q�[�W�̕\���ʒu
	glitterGaugeDestX = 585;
	glitterGaugeDestY = 170;
	glitterGaugenHeight = 384;
	glitterGaugenWidth = 384;
	glitterGaugenHeightScale = glitterGaugenHeight * 0.8;
	glitterGaugenWidthScale = glitterGaugenWidth * 1.75;
	glitterAnimNum = 0;
	waitTime = 0;

	doneBridgeSound = false;
}
// ---------------------------------------------------------------------------
//
// �O�i�E�w�i�v���V�[�W���̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CBackForeProc::~CBackForeProc()
{
	SAFE_DELETE(m_pImageForegrd);
	SAFE_DELETE(m_pImageDynamicStarScene);
	SAFE_DELETE(m_pImagePlacementSceneNum);
	SAFE_DELETE(m_pImageStarBridgeSaving);
	SAFE_DELETE(m_pImageRankingNum);
	SAFE_DELETE(m_pImageStarBridgeButton);
	SAFE_DELETE(m_pImageRemainingStar);
	SAFE_DELETE(m_pImageLineKind);
	SAFE_DELETE(m_pImageLinePermission);
	SAFE_DELETE(m_pImageGaugeGlitter);
	SAFE_DELETE(m_pImageGoalButton);

	SAFE_DELETE(m_pSprite);
}
//------------------------------------------------------------------------
//
//	�O�i�E�w�i�v���V�[�W���̍X�V	
//
//------------------------------------------------------------------------
void CBackForeProc::Update()
{
	if (m_pGMain->m_pMapProc->MapNumGet() == 1) {
		DrawStage1();
	}else if(m_pGMain->m_pMapProc->MapNumGet() == 2){
		DrawStage2();
	}
	else if (m_pGMain->m_pMapProc->MapNumGet() == 3) {
		DrawStage3();
	}
}
//M.S �����I������ʂ̕\��
//��  ���F�Ȃ�
//�߂�l�F�Ȃ�
void CBackForeProc::DrawStage1()
{
	// �\���ʒu�̒�`
	int DestX, DestY, nHeight, nWidth;
	// ����߂��鐯�X�̕����\�� 
	DestX = 358;
	DestY = 30;
	nWidth = 650;
	nHeight = 73;
	m_pSprite->Draw(m_pImageDynamicStarScene, DestX, DestY, 0, 0, nWidth, nHeight);
	// �o���{�^���̕\��
	DestX = 1010;
	DestY = 530;
	nWidth = 289;
	nHeight = 152;
	if (m_pGMain->m_pTitleProc->CheckMousePos(1010, 530, nWidth, nHeight) == true)
	{
		// �{�^�����N���b�N������
		m_pSprite->Draw(m_pImageDynamicStarScene, DestX, DestY, 0, 73, nWidth, nHeight);
		if (m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_SPACE) || m_pGMain->m_pDI->CheckJoy(KD_TRG, DIJ_A) || m_pGMain->m_pDI->CheckMouse(KD_TRG, DIM_LBUTTON))
		{
			// ���̃}�b�v�̓ǂݍ���
			m_pGMain->goSound->Play();
			m_pGMain->m_pMapProc->LoadMap2();
		}
	}
	else {
		m_pSprite->Draw(m_pImageDynamicStarScene, DestX, DestY, 0, 73, nWidth, nHeight, 0.5f);
	}
}
//M.S ���̉˂����Q�[�W�̕����\��
//��  ���F�Ȃ�
//�߂�l�F�Ȃ�
void CBackForeProc::DrawNextPassengersText() {
	// �\���ʒu�̒�`
	int DestX, DestY, nHeight, nWidth;
	int nWidthScale, nHeightScale;
	// ���̐��܂ł̏�Ԑl��
	DestX = 700;
	DestY = 30;
	nWidth = 638;
	nHeight = 51;
	nWidthScale = nWidth * 0.8;
	nHeightScale = nHeight * 0.8;
	m_pSprite->Draw(m_pImageDynamicStarScene, DestX, DestY, 0, 225, nWidth, nHeight, nWidthScale, nHeightScale);
}
//M.S ���̐��܂ł̏�Ԑl���̕����\��
//��  ���F�Ȃ�
//�߂�l�F�Ȃ�
void CBackForeProc::DrawNextGaugeText() {
	// �\���ʒu�̒�`
	int DestX, DestY, nHeight, nWidth;
	int nWidthScale, nHeightScale;
	DestX = 700;
	DestY = 215;
	nWidth = 483;
	nHeight = 49;
	nWidthScale = nWidth * 0.8;
	nHeightScale = nHeight * 0.8;
	m_pSprite->Draw(m_pImageDynamicStarScene, DestX, DestY, 0, 276, nWidth, nHeight, nWidthScale, nHeightScale);
}
//M.S �K�v�ȏ�Ԑl���̕\��(�摜�̐�������\��������)
//��  ���F�Ȃ�
//�߂�l�F�Ȃ�
void CBackForeProc::DrawNextNeedPassengers() {
	// �\���ʒu�̒�`
	int DestX, DestY, nHeight, nWidth;
	int nWidthScale, nHeightScale;
	DestX = 740;
	DestY = 105;
	nWidth = 90;
	nHeight = 82;
	nWidthScale = nWidth * 0.8;
	nHeightScale = nHeight * 0.8;

	// allManNum�͌��݂̐��̍��v��Ԑl��
	// �K�v�Ȑl�����Œ�ȃ����N���[�h�ƕ�����
    allManNum = m_pGMain->m_pEnmProc->getHighStageMan + m_pGMain->m_pEnmProc->getMiddleStageMan + m_pGMain->m_pEnmProc->getLowStageMan;
	int needManNum = 0;
	if (m_pGMain->m_dwGameMode == 3 && allManNum <= m_pGMain->rankPassengersSelectNum) {
		needManNum = m_pGMain->rankPassengersSelectNum - allManNum;
	}
	else if (m_pGMain->m_dwGameMode != 3 && allManNum <= m_pGMain->passengersSelectNum) {
		needManNum = m_pGMain->passengersSelectNum - allManNum;
	}
	// �֐����Ăт�����arrayNum�Ɍ���������
	int arrayNum = VariableAnalysis(needManNum);
	// arrayNum�̌������[�v����90*i�ňʒu�����炵������\�����A�Ō�ɐl�̕�����\��
	for (int i = 0; arrayNum + 1 > i; i++) {
		if (arrayNum > i) {
			// numArray�ɓ��ꂽ�������摜����\��������
			m_pSprite->Draw(m_pImagePlacementSceneNum, DestX + (90 * i), DestY, numArray[i] * 90, 0, nWidth, nHeight, nWidthScale, nHeightScale);
		}
		else {
			m_pSprite->Draw(m_pImagePlacementSceneNum, DestX + (90 * i), DestY, 900, 0, nWidth, nHeight, nWidthScale, nHeightScale);
		}
	}

}
//M.S �K�v�ȓd�Ԃ̈ړ������Q�[�W�̕\��
//��  ���F�Ȃ�
//�߂�l�F�Ȃ�
void CBackForeProc::DrawStarGauge() {
	// �\���ʒu�̒�`
	int DestX, DestY, nHeight, nWidth;
	int nWidthScale, nHeightScale;
	int maxGauge = 435;
	// �Q�[�W�̒�
	DestX = 740;
	DestY = 297;
	gaugenWidth = 435;  // �������̒l��ς���ƃQ�[�W�̕\���������ς��
	nHeight = 49;
	// �Q�[�W��max/���̐��ɕK�v�Ȉړ�����������
	// ����Ɍ��݂̈ړ������������ĕ\�����钷�����o��
	// �K�v�Ȑl�����Œ�ȃ����N���[�h�ƕ�����
	if (m_pGMain->m_dwGameMode != 3) {
		gaugenWidth = gaugenWidth / m_pGMain->lineTrainSelectNum;
	}
	else if (m_pGMain->m_dwGameMode == 3) {
		gaugenWidth = gaugenWidth / m_pGMain->rankLineTrainSelectNum;
	}
	gaugenWidth = gaugenWidth * m_pGMain->m_pPcProc->trainStep;
	// �ړ���������������Ă����max(�S�ẴQ�[�W��)�\������
	if (m_pGMain->m_dwGameMode != 3 && m_pGMain->m_pPcProc->trainStep >= m_pGMain->lineTrainSelectNum) {
		gaugenWidth = maxGauge;
	}
	else if (m_pGMain->m_dwGameMode == 3 && m_pGMain->m_pPcProc->trainStep >= m_pGMain->rankLineTrainSelectNum) {
		gaugenWidth = maxGauge;
	}
	nWidthScale = gaugenWidth * 0.85;
	nHeightScale = nHeight * 0.85;
	// �Q�[�W�̒��̕\��
	m_pSprite->Draw(m_pImageDynamicStarScene, DestX, DestY, 0, 374, gaugenWidth, nHeight, nWidthScale, nHeightScale);

	// �Q�[�W�̊O
	DestX = 740;
	DestY = 295;
	nWidth = 435;
	nHeight = 49;
	nWidthScale = nWidth * 0.85;
	nHeightScale = nHeight * 0.85;
	// �Q�[�W�̊O�̕\��
	m_pSprite->Draw(m_pImageDynamicStarScene, DestX, DestY, 0, 325, nWidth, nHeight, nWidthScale, nHeightScale);

	// max(�S�ẴQ�[�W��)�\������Ă�����L���L����\������
	if (gaugenWidth >= 435) {
		DrawGlitterGauge();
	}
}
//M.S ���˂܂ł̃J�E���g�_�E��(�摜�̐�������\��������)
//��  ���F�Ȃ�
//�߂�l�F�Ȃ�
void CBackForeProc::DrawWaitTime() {
	// �\���ʒu�̒�`
	int DestX, DestY, nHeight, nWidth;
	int nWidthScale, nHeightScale;
	DestX = 303;
	DestY = 331;
	nWidth = 39;
	nHeight = 53;
	nWidthScale = nWidth * 2.0;
	nHeightScale = nHeight * 2.0;
	int waitTimeTextWidth = 39;    // �摜�̐����̕�
	// �҂����Ԃ��Œ�ȃ����N���[�h�ƕ�����
	if (m_pGMain->m_dwGameMode != 3) {
		if (initialWaitingNumSet == true) {
			// �I������Ă���҂����Ԃ�drawWaitingNum�ɓ����
			drawWaitingNum = m_pGMain->waitingTimeSelectNum;
			initialWaitingNumSet = false;
		}
		// �҂����Ԃ𒴂��Ă��Ȃ���ΐ�����\��������
		if (initialDraw <= m_pGMain->waitingTimeSelectNum) {
			waitingDrawTime--;
			// �e�b�̍ŏ��ɉ���炷
			if (ringTime == true) {
				m_pGMain->timeCountSound->Play();
				ringTime = false;
			}
			if (waitingDrawTime > 0) {
				m_pSprite->Draw(m_pImageRankingNum, DestX, DestY, drawWaitingNum * waitTimeTextWidth, 0, nWidth, nHeight, nWidthScale, nHeightScale);
			}
			else {
				// 1�b�������特��炷
				ringTime = true;
				drawWaitingNum--;
				initialDraw++;
				waitingDrawTime = 60;
			}
		}
		else {
			// �o��������
			m_pGMain->m_pPcProc->GetPcObjPtr()->startTimeFlag = true;
		}
	}
	else if (m_pGMain->m_dwGameMode == 3) {
		if (initialWaitingNumSet == true) {
			// �����L���O�̑҂����Ԃ�drawWaitingNum�ɓ����
			drawWaitingNum = m_pGMain->rankWaitingTimeSelectNum;
			initialWaitingNumSet = false;
		}
		// �҂����Ԃ𒴂��Ă��Ȃ���ΐ�����\��������
		if (initialDraw <= m_pGMain->rankWaitingTimeSelectNum) {
			waitingDrawTime--;
			// �e�b�̍ŏ��ɉ���炷
			if (ringTime == true) {
				m_pGMain->timeCountSound->Play();
				ringTime = false;
			}
			if (waitingDrawTime > 0) {
				m_pSprite->Draw(m_pImageRankingNum, DestX, DestY, drawWaitingNum * waitTimeTextWidth, 0, nWidth, nHeight, nWidthScale, nHeightScale);
			}
			else {
				ringTime = true;
				drawWaitingNum--;
				initialDraw++;
				waitingDrawTime = 60;
			}
		}
		else {
			// �o��������
			m_pGMain->m_pPcProc->GetPcObjPtr()->startTimeFlag = true;
		}
	}
}
//M.S ���̐��֍s���{�^���̕\��
//��  ���F�Ȃ�
//�߂�l�F�Ȃ�
void CBackForeProc::DrawGoNextStarButton() {
	// �\���ʒu�̒�`
	int DestX, DestY, nHeight, nWidth;
	// ���̐��֍s���{�^���̕\��
	nWidth = 154;
	nHeight = 94;
	DestX = 1165;
	DestY = 260;
	if ((m_pGMain->m_dwGameMode != 3 && m_pGMain->m_pPcProc->trainStep >= m_pGMain->lineTrainSelectNum && m_pGMain->passengersSelectNum - allManNum <= 0)
		|| (m_pGMain->m_dwGameMode == 3 && m_pGMain->m_pPcProc->trainStep >= m_pGMain->rankLineTrainSelectNum && m_pGMain->rankPassengersSelectNum - allManNum <= 0)) {
		if (m_pGMain->m_dwGameMode == 3 && m_pGMain->rankHaveToGoStar - (m_pGMain->rankTraveledStar + 1) > 0 || m_pGMain->m_dwGameMode != 3 && m_pGMain->haveToGoStar - (m_pGMain->traveledStar + 1) > 0) {
			buttonBlinking++;
			if (m_pGMain->m_pTitleProc->CheckMousePos(DestX, DestY, nWidth, nHeight) == true)
			{
				// �J�[�\���ƐڐG���Ă���buttonBlinking��50�ȉ��Ȃ�傫���A�Ԃ��\������
				if (buttonBlinking <= 50) {
					m_pSprite->m_vDiffuse = VECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
					m_pSprite->Draw(m_pImageStarBridgeButton, DestXStarBridgeButton, DestYStarBridgeButton, 0, 0, nWidth, nHeight, nWidthScaleStarBridgeButton, nHeightScaleStarBridgeButton, 1.0f);
					m_pSprite->m_vDiffuse = VECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
				}// ����ȊO�Ȃ�傫���\������
				else if (buttonBlinking <= 100) {
					m_pSprite->Draw(m_pImageStarBridgeButton, DestXStarBridgeButton, DestYStarBridgeButton, 0, 0, nWidth, nHeight, nWidthScaleStarBridgeButton, nHeightScaleStarBridgeButton, 1.0f);
					// 100�ȏ�Ȃ�buttonBlinkin��0�ɂ���
					if (buttonBlinking >= 100) {
						buttonBlinking = 0;
					}
				}
				if (m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_SPACE) || m_pGMain->m_pDI->CheckJoy(KD_TRG, DIJ_A) || m_pGMain->m_pDI->CheckMouse(KD_TRG, DIM_LBUTTON))	//
				{
					// �N���b�N���ꂽ�玟�̃}�b�v�̓ǂݍ���
					if (m_pGMain->stopOperation == false) {
						m_pGMain->m_pMapProc->LoadMap3();
					}
				}
			}
			else {
				// �J�[�\���ƐڐG���Ă��Ȃ���Βʏ�̑傫���ŕ\��������
				if (buttonBlinking <= 50) {
					m_pSprite->m_vDiffuse = VECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
					m_pSprite->Draw(m_pImageStarBridgeButton, DestX, DestY, 0, 0, nWidth, nHeight, 1.0f);
					m_pSprite->m_vDiffuse = VECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
				}
				else if (buttonBlinking <= 100) {
					m_pSprite->Draw(m_pImageStarBridgeButton, DestX, DestY, 0, 0, nWidth, nHeight, 1.0f);
					if (buttonBlinking >= 100) {
						buttonBlinking = 0;
					}
				}
			}
		}
		else {
			// �Ō�̐��������ꍇ�A�S�[���{�^����\������
			buttonBlinking++;
			if (m_pGMain->m_pTitleProc->CheckMousePos(DestX, DestY, nWidth, nHeight) == true)
			{
				if (buttonBlinking <= 50) {
					m_pSprite->m_vDiffuse = VECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
					m_pSprite->Draw(m_pImageGoalButton, DestXStarBridgeButton, DestYStarBridgeButton, 0, 0, nWidth, nHeight, nWidthScaleStarBridgeButton, nHeightScaleStarBridgeButton, 1.0f);
					m_pSprite->m_vDiffuse = VECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
				}
				else if (buttonBlinking <= 100) {
					m_pSprite->Draw(m_pImageGoalButton, DestXStarBridgeButton, DestYStarBridgeButton, 0, 0, nWidth, nHeight, nWidthScaleStarBridgeButton, nHeightScaleStarBridgeButton, 1.0f);
					if (buttonBlinking >= 100) {
						buttonBlinking = 0;
					}
				}
				if (m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_SPACE) || m_pGMain->m_pDI->CheckJoy(KD_TRG, DIJ_A) || m_pGMain->m_pDI->CheckMouse(KD_TRG, DIM_LBUTTON))	//
				{
					// ���̃}�b�v�̓ǂݍ���
					if (m_pGMain->stopOperation == false) {
						m_pGMain->m_pMapProc->LoadMap3();
					}
				}
			}
			else {
				if (buttonBlinking <= 50) {
					m_pSprite->m_vDiffuse = VECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
					m_pSprite->Draw(m_pImageGoalButton, DestX, DestY, 0, 0, nWidth, nHeight, 1.0f);
					m_pSprite->m_vDiffuse = VECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
				}
				else if (buttonBlinking <= 100) {
					m_pSprite->Draw(m_pImageGoalButton, DestX, DestY, 0, 0, nWidth, nHeight, 1.0f);
					if (buttonBlinking >= 100) {
						buttonBlinking = 0;
					}
				}
			}
		}

	}
}
//M.S �I�𒆂̐��H�̕\���Ƃ��̐��H���z�u�\���̕\��
//��  ���F�Ȃ�
//�߂�l�F�Ȃ�
void CBackForeProc::DrawArrowLine()
{
	// �\���ʒu�̒�`
	int DestX, DestY, nHeight, nWidth;
	int DestXLineArrow, DestYLineArrow, nHeightLineArrow, nWidthLineArrow;
	DestX = 14;
	DestY = 10;
	nWidth = 377;
	nHeight = 68;
	DestXLineArrow = 331;
	DestYLineArrow = 19;
	nWidthLineArrow = 46;
	nHeightLineArrow = 46;

	switch (m_pGMain->m_pMapProc->ChangeButton) {
	case 0:  // �ʏ���H
		m_pSprite->Draw(m_pImageLineKind, DestX, DestY, 0, 0, nWidth, nHeight);
		if (m_pGMain->m_pMapProc->ArrowPlacementPos() == true) {
			m_pSprite->Draw(m_pImageLinePermission, DestXLineArrow, DestYLineArrow, 0, 0, nWidthLineArrow, nHeightLineArrow);
		}
		else {
			m_pSprite->Draw(m_pImageLinePermission, DestXLineArrow, DestYLineArrow, 46, 0, nWidthLineArrow, nHeightLineArrow);
		}
		break;
	case 1:  // �����]�����H
		m_pSprite->Draw(m_pImageLineKind, DestX, DestY, 0, 136, nWidth, nHeight);
		if (m_pGMain->m_pMapProc->typeChangeNum == 2 && m_pGMain->m_pMapProc->AllowEndPlacement(true) == false
			&& m_pGMain->m_pMapProc->changeButtonWithinRange == true && m_pGMain->m_pMapProc->ArrowPlacementPos() == true) {
			m_pSprite->Draw(m_pImageLinePermission, DestXLineArrow, DestYLineArrow, 0, 0, nWidthLineArrow, nHeightLineArrow);
		}
		else {
			m_pSprite->Draw(m_pImageLinePermission, DestXLineArrow, DestYLineArrow, 46, 0, nWidthLineArrow, nHeightLineArrow);
		}
		break;
	case 2:  // �w
		m_pSprite->Draw(m_pImageLineKind, DestX, DestY, 0, 68, nWidth, nHeight);
		if (m_pGMain->m_pMapProc->typeChangeNum == 2 && m_pGMain->m_pMapProc->AllowEndPlacement(true) == false
			&& m_pGMain->m_pMapProc->ArrowPlacementPos() == true) {
			m_pSprite->Draw(m_pImageLinePermission, DestXLineArrow, DestYLineArrow, 0, 0, nWidthLineArrow, nHeightLineArrow);
		}
		else {
			m_pSprite->Draw(m_pImageLinePermission, DestXLineArrow, DestYLineArrow, 46, 0, nWidthLineArrow, nHeightLineArrow);
		}
		break;
	}
}
//M.S ���H�z�u�Q�[����ʂ̕\��
//��  ���F�Ȃ�
//�߂�l�F�Ȃ�
void CBackForeProc::DrawStage2() {
	DrawArrowLine();
	DrawNextPassengersText();
	DrawNextGaugeText();
	DrawNextNeedPassengers();
	DrawStarGauge();
	DrawWaitTime();
	DrawGoNextStarButton();	
}
//M.S ���̉˂������������ʂ̕\��
//��  ���F�Ȃ�
//�߂�l�F�Ȃ�
void CBackForeProc::DrawStage3()
{
	// �\���ʒu�̒�`
	int DestX, DestY, nHeight, nWidth;
	// �����̕\��
	DestX = 20;
	DestY = 30;
	nWidth = 524;
	nHeight = 96;
	 m_pSprite->Draw(m_pImageDynamicStarScene, DestX, DestY, 0, 423, nWidth, nHeight);
	DestX = 901;
	DestY = 37;
	nWidth = 334;
	nHeight = 36;
	 m_pSprite->Draw(m_pImageRemainingStar, DestX, DestY, 0, 0, nWidth, nHeight);

	DestX = 1252;
	DestY = 35;
	nWidth = 39;
	nHeight = 53;
	int arrayStarNum;
	// �c��̍s���ׂ����̐��̕\��
	// �����L���O���[�h�͍s�����̐����Œ�Ȃ̂ŕ�����
	if (m_pGMain->m_dwGameMode != 3) {
		arrayStarNum = VariableAnalysis(m_pGMain->haveToGoStar - m_pGMain->traveledStar);
	}
	else if (m_pGMain->m_dwGameMode == 3) {
		arrayStarNum = VariableAnalysis(m_pGMain->rankHaveToGoStar - m_pGMain->rankTraveledStar);

	}
	// ���̐����[�v���񂵂Đ��̐��̕\��(�摜�̐�������\��������)
	for (int i = 0; arrayStarNum > i; i++) {
		m_pSprite->Draw(m_pImageRankingNum, DestX + (50 * i), DestY, numArray[i] * 39, 0, nWidth, nHeight);
	}
	if (builtStarBridge == true) {
		// �ʏ탂�[�h�̓Z�[�u�̕\��������
		if (m_pGMain->m_dwGameMode != 3) {
			DestX = 910;
			DestY = 600;
			nWidth = 429;
			nHeight = 52;
			 m_pSprite->Draw(m_pImageDynamicStarScene, DestX, DestY, 0, 519, nWidth, nHeight);
			DestX = 1090;
			DestY = 680;
			nWidth = 244;
			nHeight = 44;
			 m_pSprite->Draw(m_pImageStarBridgeSaving, DestX, DestY, 0, 0, nWidth, nHeight);
			 // �Z�[�u����炷
			if (doneBridgeSound == false) {
				doneBridgeSound = true;
				m_pGMain->saveOkSound->Play();
			}
		}
		starBridgeSceneTime++;
		// ��莞�Ԃ������玟�̉�ʂɈڂ�
		if (starBridgeSceneNext <= starBridgeSceneTime) {
			m_pGMain->m_pMapProc->LoadMap2();
			starBridgeSceneTime = 0;
		}
	}
}
//M.S �^����ꂽ�����̌�����Ԃ��AVariableAnalysisChangeNum���Ăт���
//��  ���Fint analysisObject   ���߂�������
//�߂�l�Fint                  ���߂��������̌���
int CBackForeProc::VariableAnalysis(int analysisObject)
{
	int analysisObjectKind = 0;
	if (analysisObject / 10000 != 0) {
		analysisObjectKind = 5;   // 5��
		VariableAnalysisChangeNum(analysisObject, analysisObjectKind);
		return analysisObjectKind;
	}
	else if (analysisObject / 1000 != 0) {
		analysisObjectKind = 4;   // 4��
		VariableAnalysisChangeNum(analysisObject, analysisObjectKind);
		return analysisObjectKind;
	}
	else if (analysisObject / 100 != 0) {
		analysisObjectKind = 3;   // 3��
		VariableAnalysisChangeNum(analysisObject, analysisObjectKind);
		return analysisObjectKind;
	}
	else if (analysisObject / 10 != 0) {
		analysisObjectKind = 2;   // 2��
		VariableAnalysisChangeNum(analysisObject, analysisObjectKind);
		return analysisObjectKind;
	}
	else {
		analysisObjectKind = 1;   // 1��
		VariableAnalysisChangeNum(analysisObject, analysisObjectKind);
		return analysisObjectKind;
	}
}
//M.S �����̊e���̐���z��(numArray)�ɓ���ċ��߂�
//��  ���Fint analysisObject      ���߂�������
//        int analysisObjectKind  ���߂��������̌���
//�߂�l�F�Ȃ�              
void CBackForeProc::VariableAnalysisChangeNum(int analysisObject, int analysisObjectKind)
{
	int analysisObjectNum = analysisObject;
	int arrayElementsNum = 0;
	// numArray��0�ŏ�����
	for (int i = 0; i < 5; i++) {
		numArray[i] = 0;
	}
	// �������錅-1��divideNum��10�������AanalysisObjectNum / ���̐������ďo��������numArray�ɓ����
	// analysisObjectNum����numArray�ɂ��ꂽ����*dividNum�������A���̐����Ŏ��̃��[�v������
	for (int i = analysisObjectKind; i >= 1; i--) {
		int divideNum = 1;
		for (int num = 1; num < i; num++) {
			divideNum = divideNum * 10;
		}
		numArray[arrayElementsNum] = analysisObjectNum / divideNum;
		analysisObjectNum = analysisObjectNum - numArray[arrayElementsNum] * divideNum;
		arrayElementsNum++;
	}
}
//M.S �ړ������Q�[�W��max(�S�ẴQ�[�W�\��)�ɂȂ������̃L���L���\��
//��  ���F�Ȃ�
//�߂�l�F�Ȃ�
void CBackForeProc::DrawGlitterGauge()
{
	int glitterGaugeImagePosX;
	int glitterGaugeImagePosY;
	// glitterAnimNum��10�ȏ�ɂȂ�����A�A�j���[�V�������ŏ��ɖ߂�
	if (glitterAnimNum >= 10) {
		glitterAnimNum = 0;
	}
    // glitterAnimNum�ɂ���ăX�v���C�g�̕\������ʒu�����߂�
	glitterGaugeImagePosX = glitterAnimNum / 5 * 384;
	glitterGaugeImagePosY = glitterAnimNum % 5 * 384;
	// �\��
	m_pSprite->Draw(m_pImageGaugeGlitter, glitterGaugeDestX, glitterGaugeDestY, glitterGaugeImagePosX, glitterGaugeImagePosY, glitterGaugenWidth, glitterGaugenHeight, glitterGaugenWidthScale, glitterGaugenHeightScale);//nWidthScale,nHeightScale);
	waitTime++;
    // waitTime��8�ɂȂ����玟�̃A�j���[�V�����ɕς���
	if (waitTime % 8 == 0) {
		glitterAnimNum++;
		waitTime = 0;
	}
}
