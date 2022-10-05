//=============================================================================
//		�Q�c�A�N�V�����Q�[���v���O����
//		�b�Q�c�`�����P�P�S�@�@�@�@�@�@           ver 2.8        2020.2.15
//
//		�}�b�v�̏���
//																Map.h
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
#include "Dinput.h"
#include "Sprite.h"

#define   MAP_IMAGE_PATH  _T("Data/")
#define   MAP_MAX   5

//----------------------------------------------------------------------------
// �}�b�v���N���X�̒�`
// 		�n�_���W�o�w���W�A�x���W�p�A�I�_���W�o�w���W�A�x���W�p�E�E�E�E
// 		�@�����W (�J�n�ʒu����I���ʒu�Ɍ������āA��������ɖ@�����o����)
//----------------------------------------------------------------------------
class  CMapLine
{
public:
	VECTOR2 m_vStart;		// �n�_���W
	VECTOR2 m_vEnd;			// �I�_���W
	VECTOR2 m_vNormal;		// �@�����W (�J�n�ʒu����I���ʒu�Ɍ������āA��������ɖ@�����o����)

public:
	// �R���X�g���N�^
	CMapLine()
	{
		m_vStart  = VECTOR2(0, 0);
		m_vEnd    = VECTOR2(0, 0);
		m_vNormal = VECTOR2(0, 0);
	}
};
//----------------------------------------------------------------------------
// �C�x���g�}�b�v�N���X�̒�`
// 		���W�o�w���W�A�x���W�p�A�C�x���g�h�c�A�C�x���g�m��(��ނ�_���a��)�A�ėp�J�E���^
//		�C�x���g�h�c�@1:�o�b�̃X�^�[�g�ʒu�@2:�A�C�e���@3:�G
//		�C�x���g�m���@0x01 ��̐�    0x02 ���܂̓G    0x04 �I�I�J�~�̓G
//					�@0x10 �~�}��    0x20 ��
//----------------------------------------------------------------------------
class  CEvtMap
{
public:
	VECTOR2     m_vStart;		// ���W
	int         m_nEvtID;		// �C�x���g�h�c
	DWORD       m_dwEvtNo;		// �C�x���g�m��
	int         m_nCnt1;		// �ėp�J�E���^
public:
	// �R���X�g���N�^
	CEvtMap()
	{
		m_vStart     = VECTOR2(0, 0);
		m_nEvtID     = 0;
		m_dwEvtNo    = 0;
		m_nCnt1      = 0;
	}
	CEvtMap(VECTOR2 vStart, int nEvtID, DWORD dwEvtNo, int nCnt1)
	{
		m_vStart      = vStart;
		m_nEvtID      = nEvtID;
		m_dwEvtNo     = dwEvtNo;
		m_nCnt1       = nCnt1;
	}
};

class CGameMain;
//----------------------------------------------------------------------------
// �}�b�v�z��N���X�̒�`
//----------------------------------------------------------------------------
class  CMap
{ 
public:
	CGameMain*				 m_pGMain;
	TCHAR                    m_MapFileName[512]; // �}�b�v�t�@�C����    // -- 2019.3.5
	TCHAR                    m_ImageName[512];  // �}�b�v�`�b�v�C���[�W�t�@�C����
	CSpriteImage*            m_pMapImage;       // �}�b�v�`�b�v�̃X�v���C�g�C���[�W
	int                      m_nMapX;           // ��ʂ̕��@�i�}�b�v�`�b�v���������j
	int                      m_nMapY;           // ��ʂ̍����i�}�b�v�`�b�v���������j
	int                      m_nMapchipWidth;   // ��̃}�b�v�`�b�v�̕�
	int                      m_nMapchipHeight;  // ��̃}�b�v�`�b�v�̍���
	int                      m_nMapLnLength;    // �}�b�v���C���z��̗v�f��
	int                      m_nEvtMapLength;   // �C�x���g�}�b�v�z��̗v�f��
	int*                     m_MapBakTbl;	    // �}�b�v�z��@�w�i
	int*                     m_MapForTbl;	    // �}�b�v�z��@�O�i
	CMapLine*                m_MapLn;		    // �}�b�v���C���z��
	CEvtMap*                 m_EvtMap;		    // �C�x���g�}�b�v�z��

public:
	// �R���X�g���N�^
	CMap(CGameMain*	pGMain);
	void InitMap();
	BOOL  MakeERelativeFName(TCHAR* szBaseFullPath, TCHAR* szPath, TCHAR* szERelativeFName);    // -- 2019.3.5

	~CMap();
};

//----------------------------------------------------------------------------
// �}�b�v�v���V�[�W���N���X�̒�`
//----------------------------------------------------------------------------
class  CMapProc
{
protected:
	CGameMain*	m_pGMain;

	// �}�b�v�z��
	CMap* m_pMapArray[MAP_MAX];
	// �}�b�v���̕`��t���O
	BOOL  m_bDrawMapLine;
	// �}�b�v�C���[�W
	CSpriteImage* m_pBakImage;
	// �}�b�v�X�v���C�g
	CSprite*      m_pSpriteMap;
	CSprite*      m_pSpriteBak;
	CSprite*      m_pSpriteLine;

public:
	// �}�b�v��
	int   m_nMapNo;
	// �R���X�g���N�^
	CMapProc(CGameMain*	pGMain);
	~CMapProc();
	void InitMapAll();
	BOOL MapRead(TCHAR* FileName, CMap* &pMap);
	void MoveMap();
	void SetMap(int);
	void Update();
	void Update2();
	void DrawBack();
	void DrawFore();
	void DrawMapLine();
	BOOL isCollisionMoveMap(CBaseObj* obj, CMapLine* &pHitmapline);
	BOOL CheckMapcross(CMapLine map, CBaseObj* obj, VECTOR2 &hitpos);
	BOOL CheckLinecross(VECTOR2 a1, VECTOR2 a2, VECTOR2 b1, VECTOR2 b2, VECTOR2 &hitpos);
	BOOL CheckRange(float l, float r, float pt); 
	BOOL CheckMapnear(CMapLine MapLn, CBaseObj* obj, VECTOR2 &vHitpos);
	float GetDistance(CMapLine MapLn, CBaseObj* obj);
	float GetLength(VECTOR2 p1, VECTOR2 p2);
	float GetCross(VECTOR2 a, VECTOR2 b);
	float GetDot(VECTOR2 a, VECTOR2 b);

	BOOL SearchEvt(int nStart, int nEvtID, DWORD dwEvtNo, VECTOR2& vPos, int& nNext);
};
