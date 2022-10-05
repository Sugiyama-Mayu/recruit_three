//=============================================================================
//		�Q�c�A�N�V�����Q�[���v���O����
//		�b�Q�c�`�����P�P�S�@�@�@�@�@�@           ver 2.8        2020.2.15
//
//		�Q�[�����C������
//																GameMain.h
//=============================================================================

#pragma once

//�x����\��
#pragma warning(disable : 4005)
#pragma warning(disable : 4244)
#pragma warning(disable : 4018)


//�w�b�_�[�t�@�C���̃C���N���[�h
#include <stdio.h>
#include <windows.h>
#include <vector>

#include "Main.h"
#include "Direct3D.h"
#include "XAudio.h"
#include "Shader.h"
#include "Dinput.h"
#include "Sprite.h"
#include "BaseProc.h"

// �X�e�[�^�X�^�C�v
#define  NONE				0x00000000
#define  TITLE				0x00000001
#define  STAGEDEMO  		0x00000002
#define  GAMEMAIN			0x00000004
#define  GAMEOVER			0x00000008
#define  GAMECLEAR			0x00000010
#define  GAMEEND			0x00000020

#define  NORMAL				0x00000001
#define  STANBY				0x00000002
#define  CATCH				0x00000004
#define  ATTACK				0x00000008
#define  DAMAGE				0x00000010
#define  DEAD				0x00000020
#define  FLASH				0x00000040
#define  WALK				0x00000080
#define  JUMP				0x00000100
#define  RAND				0x00000200
#define  STOP				0x00000400

// �X�e�[�^�X�T�u
#define  ATTACKNONE			0x00000001
#define  ATTACKMOVE			0x00000002
#define  ATTACKLASER		0x00000004
#define  ATTACKCANNON		0x00000008
#define  ATTACKBOM			0x00000010
#define  ATTACKEARTH		0x00000020

// �I�u�W�F�N�g�敪
#define  PC					0x00000001
#define  NPC				0x00000002
#define  ENM				0x00000004

// �����iDirIdx�j
#define  UP					0
#define  RIGHT				1
#define  DOWN				2
#define  LEFT				3

#define  GRAVITY  1.0

class CMain;
class CShader;
class CSpriteImage;
class CSprite;
class CFontTexture;
class CBaseObj;
class CBaseProc;
class CPcProc;
class CEnmProc;
class CWeaponProc;
class CWeaponEProc;
class CEffectProc;
class CForeProc;
class CMapProc;
class CTitleProc;
class CBaseProc;

// --------------------------------------------------------------------------------------------------
//  �Q�[�����C���N���X
// --------------------------------------------------------------------------------------------------
class CGameMain
{
public:
	// �����o�ϐ�
	CMain*			m_pMain;		// ���C���N���X
	CDirect3D*		m_pD3D;			//	Direct3D�I�u�W�F�N�g
	CXAudio*		m_pXAudio;		//	XAudio�I�u�W�F�N�g
	CDirectInput*	m_pDI;			//	DirectInputD�I�u�W�F�N�g
	CShader*		m_pShader;		//	�V�F�[�_�[
	CFontTexture*	m_pFont;		//	�t�H���g�e�N�X�`���[

	DWORD			m_dwGameStatus;
	VECTOR2			m_vScroll;

	TCHAR str[256];  // M.S �e�L�X�g�\���Ɏg�p����ϐ�
	int SilverS = 0; // M.S �┓�̐�
	int GoldS = 0;   // M.S �����̐�
	int VisionS = 0; // M.S ���̍����̐�
	float sabun;  // M.S �v���C�L�����̕����֒e��łʒu�̍���
	int time;     // M.S �Q�[�����ԃJ�E���g
	int SumP = 0; // M.S �g�[�^���X�R�A
	int ints = 0; // M.S �����̃R�����g�̎�ނ𕪂���ϐ� 
	int timeSum;  // M.S �c��̐�������
	int henk;     // M.S �h�b�X���̓G�Ƃ̐ڐG�t���O
	int hank;     // M.S ���̓G�Ƃ̐ڐG�t���O
	short textStr = 0;  // M.S ���틭���R�����g�̎�ނ𕪂���ϐ�
	int CR = 0;         // M.S �Q�[���N���A�t���O
	int m_nEShotWait = 10; // M.S �e�̑҂�����
	bool mapSsw;           // M.S �}�b�v�ړ����t���O
	int spP = 0;           // M.S SP�X�e�[�W���Ăт������t���O
	int mapNumP = 0;       // M.S ���틭���`�����X�X�e�[�W��֍s���}�b�v�ϐ�
	int valS = 0;          // M.S ���틭���`�����X�X�e�[�W�̏ꏊ����
	int i = 0;             // M.S ��x�̂ݕ��틭���`�����X�X�e�[�W�̏ꏊ�����r�o����������t���O
	short stS = 0;         // M.S ���틭���������t���O
	bool strongSSw = false; // M.S ���킪��������Ă��邩�ǂ����t���O
	bool transactionW;  // M.S ���틭������R�����g�̕\���t���O
	int timekon = 1;    // M.S ���틭������R�����g�\������
	short scoreCnt = 0; // M.S �X�R�A�̕\�����ёւ�����x�݂̂���

	// �v���V�[�W��
	CPcProc*		m_pPcProc;
	CEnmProc*		m_pEnmProc;
	CWeaponProc*	m_pWeaponProc;
	CWeaponEProc*	m_pWeaponEProc;
	CEffectProc*	m_pEffectProc;
	CForeProc*		m_pForeProc;
	CMapProc*		m_pMapProc;
	CTitleProc*		m_pTitleProc;

	// �T�E���h
	CXAudioSource*  m_pSeShot;
	CXAudioSource*  m_pSeHit;
	CXAudioSource*  m_pSePower;
	CXAudioSource*  m_pBgm1;

	// �X�v���C�g
	CSpriteImage*   m_pImageChar;
	CSpriteImage*   m_pImageSprite;
	CSpriteImage*   m_pImageChestHeart;
	CSpriteImage*   m_pImageOrange;
	CSprite*        m_pOrangeM;
	CSpriteImage*   m_pWeaponImage;
	CSpriteImage*   m_pImageSpriteS;
	CSpriteImage*   m_pImageSpriteV;
	CSpriteImage*   m_pImageRank;
	
	CDirectInput* pDI = m_pDI;
public:
	// ���\�b�h
	CGameMain(CMain* pMain);
	~CGameMain();

	void DrawSkyText();           // M.S �����̊e�X�e�[�W�ł̃R�����g�e�L�X�g�̕\��
	void DrawMenuText();          // M.S ���j���[�e�L�X�g�̕\��
	void DrawWeaponTradingText(); // M.S ����̋�������e�L�X�g�̕\��
	void CountGameTime();         // M.S �������Ԃ̌v�Z
	void CalculateScore();        // M.S �X�R�A�̌v�Z
	HRESULT Init();
	void    Loop();
	void    GameMain();
	void    Quit();

	HRESULT ChangeScreenMode(int nMode=-1);    // -- 2020.1.15

};

