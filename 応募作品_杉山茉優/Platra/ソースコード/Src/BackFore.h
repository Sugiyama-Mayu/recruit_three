//=============================================================================
//		�R�c�Q�[���v���O����
//		�b�R�c�`�����P�P�Q�@�@�@�@�@�@                 ver 3.0     BackFore.h
//=============================================================================
#pragma once
#include "GameMain.h"


// --------------------------------------------------------------------
// �O�i�E�w�i�@�v���V�[�W���N���X
// 
// (����)��{�v���V�[�W���N���X�͌p�����Ă��Ȃ�
// --------------------------------------------------------------------
class CBackForeProc 
{
protected:
	CGameMain*		m_pGMain;
	CSprite*        m_pSprite;
	// �X�v���C�g�C���[�W�̕ϐ�
	CSpriteImage*   m_pImageForegrd;
	CSpriteImage*   m_pImageDynamicStarScene;  // M.S �Q�[������UI
	CSpriteImage*   m_pImagePlacementSceneNum; // M.S �Q�[�����̐����C���[�W
	CSpriteImage*   m_pImageStarBridgeSaving;  // M.S �Z�[�u�e�L�X�g�C���[�W
	CSpriteImage*   m_pImageRankingNum;        // M.S �����L���O�����C���[�W
	CSpriteImage*   m_pImageStarBridgeButton;  // M.S ���̉˂�����������{�^���C���[�W
	CSpriteImage*   m_pImageRemainingStar;     // M.S �c��̐��̐��e�L�X�g�C���[�W
	CSpriteImage*   m_pImageLineKind;          // M.S �I�𒆂̐��H�̎�ރe�L�X�g�C���[�W
	CSpriteImage*   m_pImageLinePermission;    // M.S �z�u����(�Z�~)�C���[�W
	// M.S �ړ������𖞂������ꍇ�̃G�t�F�N�g�C���[�W
	CSpriteImage*   m_pImageGaugeGlitter;      
	CSpriteImage*   m_pImageGoalButton;        // M.S �S�[���{�^���C���[�W

public:
	void			Update();
	CSpriteImage*   GetImage() { return m_pImageForegrd; }
	CSprite*        GetSprite() { return m_pSprite; }
	CBackForeProc(CGameMain* pGMain);	// �R���X�g���N�^
	~CBackForeProc();
	// M.S CBackForeProc�̂������牺�͒ǉ������ϐ��A�֐��ł�
	// M.S ��--------------------------------------------------------------------
	// �����L���O�p�C���[�W�̃Q�b�^�[
	CSpriteImage* GetRankingNum() { return m_pImageRankingNum; }
	// ���������ŕ����ĕۑ����邽�߂̊֐�
	int VariableAnalysis(int analysisObject);
	void VariableAnalysisChangeNum(int analysisObject, int analysisObjectKind);
	// �L���L���\���֐�
	void DrawGlitterGauge();
	// ���̉˂����Q�[�W�̕����\��
	void DrawNextPassengersText();
	// ���̐��܂ł̏�Ԑl���̕����\��
	void DrawNextGaugeText();
	// �K�v�ȏ�Ԑl���̕\��
	void DrawNextNeedPassengers();
	// �K�v�ȓd�Ԃ̈ړ������Q�[�W�̕\��
	void DrawStarGauge();
	// ���˂܂ł̃J�E���g�_�E��
	void DrawWaitTime();
	// ���̐��֍s���{�^���̕\��
	void DrawGoNextStarButton();
	// �I�𒆂̐��H�̕\���Ƃ��̐��H���z�u�\���̕\��
	void DrawArrowLine();
	// �e�X�e�[�W�̕\���֐�
	void DrawStage1();
	void DrawStage2();
	void DrawStage3();

	int numArray[5] = { 0 };    // ���������ŕ����ĕۑ�����z��
	// �҂����Ԃ̃J�E���g�����̏�����
	int waitingDrawTime;
	// �\���p�J�E���g�����ۑ��ϐ�
	int initialDraw;
	// �˂����������������ǂ����ۑ��ϐ�
	bool builtStarBridge;
	// �_�ŃJ�E���g����
	int starBridgeSceneNext;
	int starBridgeSceneTime;
	// �_�ł�����J�E���g�ϐ�
	int buttonBlinking;
	// ���̐��֍s���{�^���p�ʒu�ϐ�
	int DestXStarBridgeButton;
	int DestYStarBridgeButton;
	int nHeightScaleStarBridgeButton;
	int nWidthScaleStarBridgeButton;
	// ���˂܂ł̃J�E���g�p�ϐ�
	int drawWaitingNum;
	// ���˂܂ł̃J�E���g�̐����Z�b�g����x�̂ݍs���ϐ�
	bool initialWaitingNumSet;
	// ���˂܂ł̃J�E���g�̉���炷�t���O
	bool ringTime;    
	// �L���L���p�ʒu�ϐ�
	int glitterGaugeDestX;
	int glitterGaugeDestY;
	int glitterGaugenHeight;
	int glitterGaugenWidth;
	int glitterGaugenWidthScale;
	int glitterGaugenHeightScale;
	int glitterAnimNum;
	// �Z�[�u������x�炷���߂̕ϐ�
	bool doneBridgeSound;
	// ���̃V�[���̏�Ԑl��
	int allManNum;
	// �Q�[�W�̕�
	int gaugenWidth;
	// �L���L���̃A�j���[�V�����p�J�E���g�ϐ�
	int waitTime;
};

