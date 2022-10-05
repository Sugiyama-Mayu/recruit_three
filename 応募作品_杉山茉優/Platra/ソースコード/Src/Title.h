//=============================================================================
//		�R�c�Q�[���v���O����
//		�b�R�c�`�����P�P�Q�@�@�@�@�@�@                 ver 3.0        2021.1.11
//		�^�C�g���@�w�b�_�t�@�C��							Title.h
//=============================================================================
#pragma once

#include "GameMain.h"


// --------------------------------------------------------------------
// �^�C�g���@�v���V�[�W���N���X
//// --------------------------------------------------------------------
class CTitleProc
{
public:
	CGameMain*		m_pGMain;
	// �g�p����C���[�W
	CSpriteImage*   m_pImageTitle;
	CSpriteImage*   m_pImageClear;
	CSpriteImage*   m_pImageOver;
	CSprite*        m_pSprite;
	CSpriteImage*   m_pImageSelect;
	CSpriteImage*   m_pImageOption;
	// M.S ��������y�[�W 
	CSpriteImage*   m_pImagePage1;
	CSpriteImage*   m_pImagePage2;
	CSpriteImage*   m_pImagePage3;
	CSpriteImage*   m_pImagePage4;
	CSpriteImage*   m_pImagePage5;
	CSpriteImage*   m_pImagePage6;
	CSpriteImage*   m_pImagePage7;
	CSpriteImage*   m_pImagePage8;
	// M.S ��������y�[�W�ړ��{�^��
	CSpriteImage*   m_pImagePageButton;
	// M.S �I�v�V�������
	CSpriteImage*   m_pImageOptionNum;
	CSpriteImage*   m_pImageOptionBackButton;
	// M.S ���U���g���
	CSpriteImage*   m_pImageResult;
	CSpriteImage*   m_pImageRanking;
	// M.S �Z�[�u���ӕ\��
	CSpriteImage*   m_pImageSaveWarning;
	CSpriteImage*   m_pImageNoSave;
	// M.S �����т����A�����L���O�m�F�{�^��
	CSpriteImage*   m_pImageGreenButton;

	DWORD           m_dwCntTime;
	DWORD           m_dwStatusPhase;
public:
	void Title();
	bool TitleTitle();
	void GameClear();
	void GameOver();
	bool CheckMousePos(int nPosX, int nPosY, int nWidth, int nHeight);
	CTitleProc(CGameMain* pGMain);	// �R���X�g���N�^
	~CTitleProc();

	// M.S �^�C�g���Z���N�g���
	bool TitleSelect();
	// M.S �����т������
	bool TitleExplanation();
	// M.S �I�v�V�������
	bool TitleOption();
	// M.S �v���O�����Ŏg�p���鐔�����I�v�V������ʂŐݒ肵�������֕ϊ�
	void ChangeSelect();
	// M.S �����L���O�m�F���
	void DrawRanking();

	// M.S �I�v�V������ʂŐݒ肵���������v���O�����Ŏg�p���鐔���ɕϊ�
	void ChangeSelectNum(int bgmOrSeNum);
	// M.S �I�v�V������ʂ̃{�^���̑I������
	void DrawSelectNum(bool judgeRange, int selectKind);
	// M.S �͂��߂����I���������̃Z�[�u�f�[�^������ƒm�点�钍�ӕ\��
	bool DrawSaveWarning();
	// M.S �Â������I���������̃Z�[�u�f�[�^���Ȃ��ƒm�点�钍�ӕ\��
	void DrawNoSaveDataWarning();
	// M.S �����т����{�^���ƃ����L���O�m�F�{�^���̕\���A�I������
	bool DrawHowToPlayRanking();
	// M.S �I�v�V������ʂ̐��H���{�^�������̕\���A�I������
	void SelectLineNum(bool judgeRange, int selectKind, int i);
	// M.S �I�v�V������ʂ̏�Ԑl���{�^�������̕\���A�I������
	void SelectPassengersNum(bool judgeRange, int selectKind, int i);
	// M.S �I�v�V������ʂ̔��˂܂ł̑҂����ԃ{�^�������̕\���A�I������
	void SelectWaitTime(bool judgeRange, int selectKind, int i);
	// M.S �I�v�V������ʂ�BGM���ʃ{�^�������̕\���A�I������
	void SelectBgm(bool judgeRange, int selectKind, int i);
	// M.S �I�v�V������ʂ�SE���ʃ{�^�������̕\���A�I������
	void SelectSe(bool judgeRange, int selectKind, int i);
    void DrawExplanationPage(int nowPage); 	// M.S �����т�����ʂ̑I�𒆃y�[�W�̕\��
	// M.S �ʏ탂�[�h�̃X�R�A�̕\��(�摜����\��������)
	void DrawManScoreNormalMode();
	// M.S �����L���O���[�h�̃X�R�A�̕\��(�摜����\��������)
	void DrawManScoreRankingMode();
	void DrawTotalScore();  // M.S �g�[�^���X�R�A�̕\��(�摜����\��������)
	void SortRanking();     // M.S �����L���O�̕��ׂ���
	void AddRanking();  	// M.S �����L���O�̒ǉ��A�\��

	int nTitleSelect;
	int linetrainNum;  // M.S ���H�̑I�𐔎�
	int passengersNum; // M.S ��Ԑl���̑I�𐔎�
	int waitingTime;   // M.S �҂����Ԃ̑I�𐔎�
	int bgmNum;        // M.S BGM���ʂ̑I�𐔎�
	int seNum;         // M.S SE���ʂ̑I�𐔎�
	int lineTrainSelect;     // M.S ���H�̑I�����萔��
	int passengersSelect;    // M.S ��Ԑl���̑I�����萔��
	int waitingTimeSelect;  // M.S �҂����Ԃ̑I�����萔��
	int bgmSelect;          // M.S BGM���ʂ̑I�����萔��
	int seSelect ;           // M.S SE���ʂ̑I�����萔��
	int selectedKindNum;     // M.S �I�v�V������ʂ̃{�^���̗�̐���

	int rankingTime;         // M.S �����L���O��ʂ̃^�C���J�E���g
	int myRanking;           // M.S �����̃����L���O
	int totalScore;          // M.S �g�[�^���X�R�A
	bool initialRankingSorting;  // M.S 1�x�̂݃����L���O���ёւ��t���O
	int totalHighManScore;       // M.S �l(��)�̏�Ԑl���X�R�A
	int totalMiddleManScore;     // M.S �l(��)�̏�Ԑl���X�R�A
	int totalLowManScore;        // M.S �l(��)�̏�Ԑl���X�R�A
	bool ScoreWriteProcess;  // M.S �t�@�C���������݃t���O
	bool saveWarningFlag;    // M.S �Z�[�u�f�[�^���钍�Ӄt���O
	bool noSaveFlag;         // M.S �Z�[�u�f�[�^�Ȃ����Ӄt���O
   int nowPage;                  // M.S ��������őI�𒆂̃y�[�W

	int gameClearCount;          // M.S �Q�[���N���A�^�C���J�E���g
	int gameOverCount;           // M.S �Q�[���I�[�o�[�^�C���J�E���g
    // M.S �Q�[���N���A�̏����T�E���h����
	bool RingSound;   // M.S �Q�[���N���A�A�Q�[���I�[�o�[�T�E���h
	bool RingResultSound;  // M.S ���U���g�T�E���h
};
