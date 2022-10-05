//=============================================================================
//		�Q�c�A�N�V�����Q�[���v���O����
//		�b�Q�c�`�����P�P�S�@�@�@�@�@�@           ver 2.8        2020.2.15
//
//		���C������
//																Main.h
//=============================================================================

#pragma once

//�x����\��
#pragma warning(disable : 4005)
#pragma warning(disable : 4244)
#pragma warning(disable : 4018)


//�w�b�_�[�t�@�C���̃C���N���[�h
#include <stdio.h>
#include <windows.h>

#include "resource.h"
#include "GameMain.h"


//�萔��`
//#define WINDOW_WIDTH   1920 //�E�B���h�E��
//#define WINDOW_HEIGHT  1080 //�E�B���h�E����

#define WINDOW_WIDTH   1366   //�E�B���h�E��
#define WINDOW_HEIGHT  768    //�E�B���h�E����

#define APP_NAME _T("C2DAct114 ��{�Q�c�A�N�V�����Q�[��    ver2.8")

class CGameMain;

//
//  Windows���C���N���X
//
class CMain
{
public:
	// �����o�ϐ�
	CGameMain*	   m_pGMain;		  // �Q�[�����C���N���X
	HINSTANCE      m_hInstance;
	HWND           m_hWnd;
	BOOL           m_bLoopFlag;     // ���[�v�t���O�@TRUE:���[�v�@FALSE:���[�v�I��
	double         m_MainLoopTime;    // ���[�v�X�s�[�h�@1/60Sec

	// ���\�b�h
	HRESULT InitWindow(HINSTANCE,INT,INT,INT,INT,LPCTSTR);
	LRESULT MsgProc(HWND,UINT,WPARAM,LPARAM);
	HRESULT Init();
	void    MessageLoop();
	BOOL    MessageProcess(MSG* msg);
	void    Loop();
	void    DispFps();
	void    Quit();
	CMain();
	~CMain();
};
//�֐��v���g�^�C�v�̐錾
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

