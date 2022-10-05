//=============================================================================
//		�Q�c�A�N�V�����Q�[���v���O����
//		�b�Q�c�`�����P�P�S�@�@�@�@�@�@           ver 2.8        2020.2.15
//
//      �I�[�v�j���O�^�C�g���E�Q�[���N�����[�E�Q�[���I�[�o�[�̏���
//																Title.cpp
//=============================================================================
#include "Title.h"
#include "Playchar.h"
#include <stdio.h>
#include <string>
//============================================================================
//
// �^�C�g���v���V�[�W���̃R���X�g���N�^
//
// ---------------------------------------------------------------------------
CTitleProc::CTitleProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	m_pGMain = pGMain;
	m_pSprite = new CSprite(m_pGMain->m_pShader); // �X�v���C�g�̐���
	m_pImageTitle = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/title.png")); // �C���[�W�̃��[�h
	m_pImageClear = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/clear.png")); // �C���[�W�̃��[�h
	m_pImageOver = new CSpriteImage(m_pGMain->m_pShader, _T("Data/Image/over.png")); // �C���[�W�̃��[�h
	m_pScore = new CSprite(m_pGMain->m_pImageRank, 0, 0, 500, 70);

	m_dwCntTime = 0;
}
// ---------------------------------------------------------------------------
//
// �^�C�g���^�C�g���v���V�[�W���̃f�X�g���N�^
//
// ---------------------------------------------------------------------------
CTitleProc::~CTitleProc()
{
	SAFE_DELETE(m_pImageTitle);
	SAFE_DELETE(m_pImageClear);
	SAFE_DELETE(m_pImageOver);
	SAFE_DELETE(m_pSprite);
	SAFE_DELETE(m_pScore);
}
//------------------------------------------------------------------------
//
//	�^�C�g���̕\��	
//
//------------------------------------------------------------------------
void CTitleProc::Title()
{
	// �t���X�N���[���ɂ���(�Ȃ���1�x�������Ɩ߂��Ă��܂��̂ŁA�ēx�t���X�N���[���ɂ���)
	// �\��
	m_pSprite->Draw(m_pImageTitle, 0, 0, 0, 0, m_pImageTitle->m_dwImageWidth, m_pImageTitle->m_dwImageHeight, WINDOW_WIDTH, WINDOW_HEIGHT);
	m_pGMain->m_pFont->Draw(323, 193, _T("�I�f����"), 130, RGB(175, 238, 238), 1.0f, _T("���C���I"));
	m_pGMain->m_pFont->Draw(320, 190, _T("�I�f����"), 130, RGB(255, 165, 0), 1.0f, _T("���C���I"));
	// �t�H���g���@"�c�e������"�C"�l�r �o�S�V�b�N"�C"�l�r �S�V�b�N"�C"HGP�n�p�p�߯�ߑ�"�C"HGP�n�p�p�޼��UB"
	m_pGMain->m_pFont->Draw(WINDOW_WIDTH - 430, 270, _T("DirectX11�Ή�"), 60, RGB(0, 255, 127), 1.0f, _T("���C���I"));
	m_dwCntTime++;
	if (m_dwCntTime % 10 > 5)
	{
		m_pGMain->m_pFont->Draw(400, WINDOW_HEIGHT - 110, _T("HIT SPACE KEY!!"), 40, RGB(64, 224, 208), 1.0f, _T("HGP�n�p�p�߯�ߑ�"));
	}
	if (m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_SPACE) || m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_RETURN)
		|| m_pGMain->m_pDI->CheckJoy(KD_DAT, DIJ_A) || m_pGMain->m_pDI->CheckMouse(KD_DAT, DIM_LBUTTON)
		|| m_dwCntTime > 600)
	{
		// �T�E���h�̍Đ�
		m_pGMain->m_pBgm1->Play(AUDIO_LOOP);
		m_pGMain->m_dwGameStatus = GAMEMAIN;  // �Q�[�����C����(�J�n)
		m_dwCntTime = 0;
	}

	// M.S �ߋ��̃����L���O�̓ǂݍ���
	FILE* fIn1;
	
	fIn1 = fopen("scoreF.txt", "r");
	fscanf(fIn1, "%d %d %d", s1, s2, s3);
	fclose(fIn1);
}
//------------------------------------------------------------------------
//
//	�Q�[���N�����[�̕\��	
//
//------------------------------------------------------------------------
void CTitleProc::GameClear()
{
	// �w�i�\��
	m_pSprite->Draw(m_pImageClear, 0, 0, 0, 0, m_pImageTitle->m_dwImageWidth, m_pImageTitle->m_dwImageHeight, WINDOW_WIDTH, WINDOW_HEIGHT);
	TCHAR str[256];
	// M.S �g�[�^���X�R�A�̕\��
	_stprintf(str, _T("%d"), m_pGMain->SumP);
	m_pGMain->m_pFont->Draw(710, 203, str, 70, RGB(153, 51, 102));
	_stprintf(str, _T("%d"), m_pGMain->SumP);
	m_pGMain->m_pFont->Draw(710, 200, str, 70, RGB(255, 255, 153));

	m_pGMain->m_pFont->Draw(490, 200, _T("�X�R�A�F"), 70, RGB(255, 204, 153), 1.0f, _T("HGP�n�p�p�߯�ߑ�"));
	m_pGMain->m_pFont->Draw(403, 83, _T("GAME CLEAR"), 90, RGB(0, 0, 0), 1.0f, _T("HGP�n�p�p�߯�ߑ�"));
	m_pGMain->m_pFont->Draw(400, 80, _T("GAME CLEAR"), 90, RGB(240, 128, 128), 1.0f, _T("HGP�n�p�p�߯�ߑ�"));
	// M.S �����L���O�̘g�C���[�W�̕\��
	m_pScore->Draw(420, 300);
	m_pScore->Draw(420, 380);
	m_pScore->Draw(420, 460);
	// M.S �����L���O�̔z��̕��ёւ�
	if (m_pGMain->scoreCnt <= 0) { 	// M.S ��x�݂̂̏��� 
		// M.S �g�[�^���X�R�A�̌v�Z
		m_pGMain->CalculateScore();
		// M.S ����̃X�R�A����ʈȏォ�ǂ���
		if (m_pGMain->SumP >= s1[0]) { 
			s3[0] = s2[0];
			s2[0] = s1[0];
			s1[0] = m_pGMain->SumP;
		}
		// M.S ����̃X�R�A����ʈȏォ�ǂ���
		else if (m_pGMain->SumP >= s2[0]) {
			s3[0] = s2[0];
			s2[0] = m_pGMain->SumP;
		}
		// M.S ����̃X�R�A���O�ʈȏォ�ǂ���
		else if (m_pGMain->SumP >= s3[0]) {
			s3[0] = m_pGMain->SumP;
		}	
		// M.S ���ѕς����z���ϐ��ɓ����
		FILE* fOut;
		fOut = fopen("scoreF.txt", "w");

		char smo1[5], smo2[5], smo3[5];
		sprintf(smo1, "%d", s1[0]);
		sprintf(smo2, "%d", s2[0]);
		sprintf(smo3, "%d", s3[0]);
		// M.S �X�y�[�X�ŋ�؂��ăt�@�C���ɏ�������
		fputs(smo1,fOut);
		fputc(' ', fOut);
		fputs(smo2, fOut);
		fputc(' ', fOut);
		fputs(smo3, fOut);

		fclose(fOut);

		m_pGMain->scoreCnt++; 
	}
	// M.S �����L���O�̕\��
	_stprintf(str, _T("1��     %d" ), s1[0]);
	m_pGMain->m_pFont->Draw(520, 310, str, 50, RGB(0, 191, 255),1.0f, _T("���C���I"));
	_stprintf(str, _T("1��     %d" ), s1[0]);
	m_pGMain->m_pFont->Draw(522, 312, str, 50, RGB(255, 250, 250), 1.0f, _T("���C���I"));

	_stprintf(str, _T("2��     %d"), s2[0]);
	m_pGMain->m_pFont->Draw(520, 390, str, 50, RGB(0, 191, 255), 1.0f, _T("���C���I"));
	_stprintf(str, _T("2��     %d"), s2[0]);
	m_pGMain->m_pFont->Draw(522, 392, str, 50, RGB(255, 250, 250), 1.0f, _T("���C���I"));

	_stprintf(str, _T("3��     %d"), s3[0]);
	m_pGMain->m_pFont->Draw(520, 470, str, 50, RGB(0, 191, 255), 1.0f, _T("���C���I"));
	_stprintf(str, _T("3��     %d"), s3[0]);
	m_pGMain->m_pFont->Draw(522, 472, str, 50, RGB(255, 250, 250), 1.0f, _T("���C���I"));
	
	m_dwCntTime++;
	if (m_dwCntTime % 10 > 5)
	{
		m_pGMain->m_pFont->Draw(500, WINDOW_HEIGHT - 120, _T("HIT SPACE KEY!!"), 40, RGB(64, 224, 208), 1.0f, _T("HGP�n�p�p�߯�ߑ�"));
	}

	// ���Ԃ������Ă��āA�����������
	if (m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_SPACE) || m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_RETURN)
		|| m_pGMain->m_pDI->CheckJoy(KD_DAT, DIJ_A) || m_pGMain->m_pDI->CheckMouse(KD_DAT, DIM_LBUTTON) 
		|| m_dwCntTime > 600)
	{
		// �Q�[���̏I������
		m_pGMain->m_pBgm1->Stop();
		m_pGMain->m_dwGameStatus = GAMEEND;
		m_pGMain->scoreCnt = 0;
		m_dwCntTime = 0;
	}
}
//------------------------------------------------------------------------
//
//	�Q�[���I�[�o�[�̕\��	
//
//------------------------------------------------------------------------
void CTitleProc::GameOver()
{
	// �\��
	m_pSprite->Draw(m_pImageOver, 0, 0, 0, 0, m_pImageTitle->m_dwImageWidth, m_pImageTitle->m_dwImageHeight, WINDOW_WIDTH, WINDOW_HEIGHT);
	m_pGMain->m_pFont->Draw(423, 153, _T("GAME OVER"), 90, RGB(0, 0, 0), 1.0f, _T("HGP�n�p�p�߯�ߑ�"));
	m_pGMain->m_pFont->Draw(420, 150, _T("GAME OVER"), 90, RGB(0, 0, 255), 1.0f, _T("HGP�n�p�p�߯�ߑ�"));

	m_dwCntTime++;
	if (m_dwCntTime % 10 > 5)
	{
		m_pGMain->m_pFont->Draw(500, WINDOW_HEIGHT - 120, _T("HIT SPACE KEY!!"), 40, RGB(64, 224, 208), 1.0f, _T("HGP�n�p�p�߯�ߑ�"));
	}

	if (m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_SPACE) || m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_RETURN) ||
		m_pGMain->m_pDI->CheckJoy(KD_DAT, DIJ_A) || m_pGMain->m_pDI->CheckMouse(KD_DAT, DIM_LBUTTON) 
		|| m_dwCntTime > 600)	
	{
		// �Q�[���̏I������
		m_pGMain->m_pBgm1->Stop();
		m_pGMain->m_dwGameStatus = GAMEEND;
		m_dwCntTime = 0;
	}
}