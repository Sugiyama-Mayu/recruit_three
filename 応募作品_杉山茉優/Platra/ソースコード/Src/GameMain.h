//=============================================================================
//		�R�c�Q�[���v���O����
//		�b�R�c�`�����P�P�Q�@�@�@�@�@�@                 ver 3.0        2021.1.11
//
//		�Q�[���̃��C������
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
#include "Shader.h"
#include "FbxMesh.h"
#include "XAudio.h"
#include "Dinput.h"
#include "Sprite3D.h"
#include "Collision.h"
#include "Displace.h"
#include "BBox.h"
#include "BaseProc.h"
#include "MyImgui.h"

// �X�e�[�^�X�^�C�v
#define  NONE				0x00000000
#define  TITLE				0x00000001
#define  STAGEDEMO  		0x00000002
#define  GAMEMAIN			0x00000004
#define  GAMEOVER			0x00000008
#define  GAMECLEAR			0x00000010
#define  GAMEEND			0x00000020

#define  NORMAL				0x00000001
#define  WAIT				0x00000002
#define  DAMAGE				0x00000004
#define  FLASH				0x00000008
#define  DEAD				0x00000010

// �X�e�[�^�X�T�u
#define  ATTACKNONE			0x00000001
#define  ATTACKMOVE			0x00000002
#define  ATTACKLASER		0x00000004
#define  ATTACKCANNON		0x00000008
#define  ATTACKBOM			0x00000010
#define  ATTACKEARTH		0x00000020
#define  ATTACKSWORD		0x00000040
#define  ATTACKFLAME		0x00000080
#define  ATTACKWAIT			0x00000100

// �I�u�W�F�N�g�敪
#define  PC					0x00000001
#define  NPC				0x00000002
#define  ENM				0x00000004


class CMain;
class CShader;
class CSpriteImage;
class CSprite;
class CFontTexture;
class CCollision;
class CWave;
class CBBox;
class CFbxMeshCtrl;

class CBaseObj;
class CBaseProc;
class CPcProc;
class CCameraProc;
class CEnmProc;
class CMapProc;
class CWeaponProc;
class CEffectProc;
class CBackForeProc;
class CTitleProc;

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
	CFontTexture*	m_pFont;		//	�t�H���g�e�N�X�`���[
	CShader*		m_pShader;		//	�V�F�[�_�[
	CFbxMeshCtrl*	m_pFbxMeshCtrl;	// ���b�V���R���g���[���N���X    // -- 2021.2.4
	CBBox*          m_pBox;

	DWORD           m_dwGameStatus;
	
	// �J�����E���C�g�E�r���[
	VECTOR3         m_vEyePt;		//�J�����i���_�j�ʒu
	VECTOR3         m_vLookatPt;	//�����ʒu
	MATRIX4X4       m_mView;
	MATRIX4X4       m_mProj;
	VECTOR3         m_vLightDir;	//�f�B���N�V���i�����C�g�̕���

	// �v���V�[�W��
	CPcProc*		m_pPcProc;
	CCameraProc*	m_pCameraProc;
	CEnmProc*		m_pEnmProc;
	CMapProc*		m_pMapProc;
	CWeaponProc*	m_pWeaponProc;
	CEffectProc*	m_pEffectProc;
	CBackForeProc*	m_pBackForeProc;
	CTitleProc*		m_pTitleProc;

	// M.S �v���g���̃T�E���h
	CXAudioSource*   titleBgm;
	CXAudioSource*   gameBgm;
	CXAudioSource*   gameClearBgm;
	CXAudioSource*   resultBgm;
	CXAudioSource*   gameOverBgm;

	CXAudioSource*   turnThePageSound;
	CXAudioSource*   selectSound;
	CXAudioSource*   saveWarningSound;
	CXAudioSource*   bornStarSound;
	CXAudioSource*   goSound;
	CXAudioSource*   timeCountSound;
	CXAudioSource*   lineChangeSound;
	CXAudioSource*   linePlacementSound;
	CXAudioSource*   rideSound;
	CXAudioSource*   saveOkSound;
	CXAudioSource*   nextStarOkSound;
	
public:
	// ���\�b�h
	CGameMain(CMain* pMain);
	~CGameMain();

	HRESULT Init();
	void    Loop();
	void    Quit();

	void    GameMain();
	HRESULT ChangeScreenMode(int nMode=-1);    // -- 2020.1.15
	// M.S �t�@�C���̓ǂݍ��݊֐�
	void FileRead();
	// M.S �t�@�C���̏������݊֐�
	void FileWrite();
	// M.S ���ʉ����ʒ����֐�
	void SetSoundVolume();
	// M.S BGM�����ʒ����֐�
	void SetBgmVolume();

	int m_dwGameMode;
	// M.S �J�[�\���̈ʒu
	int cursolX;
	int cursolY;
	// M.S ��]�̏������s��ꂽ�t���O
	bool rotateFlag;
	bool transparentSwitch;   // M.S �v���C�L�����̓��������̔���
	int initialH;          // M.S �v���C�L�����̃}�X�̏����l(�c)
	int initialV;          // M.S �v���C�L�����̃}�X�̏����l(��)
	int lineTrainSelectNum;  // M.S �v���O�����Ŏg�p������H��
	int passengersSelectNum;  // M.S �v���O�����Ŏg�p�����Ԑl��
	int waitingTimeSelectNum; // M.S �v���O�����Ŏg�p����҂�����
	float bgmSelectNum;  // M.S �v���O�����Ŏg�p����BGM����
	float seSelectNum;   // M.S �v���O�����Ŏg�p����SE����
	int traveledStar;    // M.S �s�������̐�
	int haveToGoStar;    // M.S �s���Ȃ���΂Ȃ�Ȃ����̐�
	int starArray[25] = { 0 }; // M.S �t�@�C���ǂݍ��݁A�����o���Ɏg�p���鐯�̔z��
	int redMan;    // M.S �t�@�C���ǂݍ��݁A�����o���Ɏg�p����l��(��)
	int yellowMan; // M.S �t�@�C���ǂݍ��݁A�����o���Ɏg�p����l��(��)
	int blueMan;   // M.S �t�@�C���ǂݍ��݁A�����o���Ɏg�p����l��(��)
	int rankOne;   // M.S �t�@�C���ǂݍ��݁A�����o���Ɏg�p����1�ʂ̃X�R�A��
	int rankTwo;   // M.S �t�@�C���ǂݍ��݁A�����o���Ɏg�p����2�ʂ̃X�R�A��
	int rankThree; // M.S �t�@�C���ǂݍ��݁A�����o���Ɏg�p����3�ʂ̃X�R�A��
	int rankFour;  // M.S �t�@�C���ǂݍ��݁A�����o���Ɏg�p����4�ʂ̃X�R�A��
	int rankFive;  // M.S �t�@�C���ǂݍ��݁A�����o���Ɏg�p����5�ʂ̃X�R�A��
	bool stopOperation;  // M.S �Q�[���̏������~�߂�t���O
	
	int rankLineTrainSelectNum;   // M.S �����L���O���[�h���g�p������H��
	int rankPassengersSelectNum;  // M.S �����L���O���[�h���g�p�����Ԑl��
	int rankWaitingTimeSelectNum; // M.S �����L���O���[�h���g�p����҂�����
	int rankTraveledStar; // M.S �����L���O���[�h���g�p����s�������̐�
    int rankHaveToGoStar; // M.S �����L���O���[�h���g�p����s���Ȃ���΂Ȃ�Ȃ����̐�
	int rankRedMan;    // M.S �����L���O���[�h���g�p����l��(��)
	int rankYellowMan; // M.S �����L���O���[�h���g�p����l��(��)
	int rankBlueMan;   // M.S �����L���O���[�h���g�p����l��(��)

	bool continuationFlag; // M.S �Z�[�u�f�[�^�����邩�ǂ����t���O
	FILE* dataFileWrite;   // M.S �t�@�C���\���̂̃|�C���^
};