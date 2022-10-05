//=============================================================================
//		�Q�c�A�N�V�����Q�[���v���O����
//		�b�Q�c�`�����P�P�S�@�@�@�@�@�@           ver 2.8        2020.2.15
//
//		�}�b�v�̏���
//																Map.cpp
//=============================================================================
#include <stdlib.h>
#include <time.h>
#include "Map.h"
#include "Playchar.h"
#include "Enemy.h"
#include "Effect.h"

// CMap�N���X   --------------------------------------------------------------------------------------------
// �R���X�g���N�^
CMap::CMap(CGameMain*	pGMain)
{
	m_pGMain = pGMain;
	m_MapFileName[0] = _T('\0');    // -- 2019.3.5
	m_ImageName[0] = _T('\0');
	m_pMapImage = NULL;
	m_nMapX = 0;
	m_nMapY = 0;
	m_nMapchipWidth = 0;
	m_nMapchipHeight = 0;
	m_nMapLnLength = 0;
	m_nEvtMapLength = 0;
	m_MapBakTbl = NULL;
	m_MapForTbl = NULL;
	m_MapLn     = NULL;
	m_EvtMap    = NULL;
}
//  �f�X�g���N�^
CMap::~CMap()
{
	SAFE_DELETE(m_pMapImage);
	SAFE_DELETE_ARRAY(m_MapBakTbl);
	SAFE_DELETE_ARRAY(m_MapForTbl);
	SAFE_DELETE_ARRAY(m_MapLn);
	SAFE_DELETE_ARRAY(m_EvtMap);
}
//------------------------------------------------------------------------
//
// CMap�N���X�̃}�b�v�̏�����
//
//------------------------------------------------------------------------
void CMap::InitMap()
{
	int i;

	TCHAR szName[256];

	MakeERelativeFName(m_MapFileName, m_ImageName, szName);  // �}�b�v�t�@�C��������}�b�v�C���[�W�̃p�X�𓾂�    // -- 2019.3.5

	m_pMapImage = new CSpriteImage(m_pGMain->m_pShader, szName);
	m_MapBakTbl = new int[m_nMapX*m_nMapY];	// �v�f�����̔z����m��
	for (i = 0; i < m_nMapX*m_nMapY; i++)
	{
		m_MapBakTbl[i] = -1;	// -1�ŏ�����
	}
	m_MapForTbl = new int[m_nMapX*m_nMapY];	// �v�f�����̔z����m��
	for (i = 0; i < m_nMapX*m_nMapY; i++)
	{
		m_MapForTbl[i] = -1;	// -1�ŏ�����
	}
}
//-----------------------------------------------------------------------------    // -- 2019.3.5
// ����(relative)�p�X�����t�H���_����̑���(ERelative)�p�X���쐬����
//
//   ����      TCHAR*  szBaseFullPath
//             TCHAR*  szPath
//             TCHAR*  szERelativeFName(Out)
//-----------------------------------------------------------------------------
BOOL    CMap::MakeERelativeFName(TCHAR* szBaseFullPath, TCHAR* szPath, TCHAR* szERelativeFName)
{
	const DWORD NUM = 20;

	TCHAR BaseDrive[256], BasePath[512], BaseFName[512], BaseExt[256];
	TCHAR Drive[256], Path[512], FName[512], Ext[256];

	TCHAR *p;
	TCHAR BasePathArray[NUM][256] = { 0 };
	TCHAR PathArray[NUM][256] = { 0 };

	int i, j, n, m, d;

	// �h���C�u�ԍ��A�p�X���A�t�@�C�����A�g���q�ɕ���
	_tsplitpath_s(szBaseFullPath, BaseDrive, sizeof(BaseDrive) / sizeof(TCHAR), BasePath, sizeof(BasePath) / sizeof(TCHAR),
		BaseFName, sizeof(BaseFName) / sizeof(TCHAR), BaseExt, sizeof(BaseExt) / sizeof(TCHAR));
	_tsplitpath_s(szPath, Drive, sizeof(Drive) / sizeof(TCHAR), Path, sizeof(Path) / sizeof(TCHAR),
		FName, sizeof(FName) / sizeof(TCHAR), Ext, sizeof(Ext) / sizeof(TCHAR));

	// �h���C�u�ԍ�������Ƃ��͊��ɐ�΃p�X�ɂȂ��Ă���
	if (Drive[0] != _T('\0'))
	{
		_tcscpy(szERelativeFName, szPath);
		return TRUE;
	}

	// �p�X�����e�t�H���_�K�w�ɕ���
	i = 0;
	p = _tcstok(BasePath, _T("/\\"));
	while (p)
	{
		_tcscpy(BasePathArray[i], p);
		i++;
		p = _tcstok(NULL, _T("/\\"));
	}
	n = i;  // �x�[�X�̊K�w��

	i = 0;
	p = _tcstok(Path, _T("/\\"));
	while (p)
	{
		_tcscpy(PathArray[i], p);
		i++;
		p = _tcstok(NULL, _T("/\\"));
	}

	//	���΃p�X��'�D'�̐�
	i = 0;
	d = 1;
	if (PathArray[i][0] == _T('.'))
	{
		for (j = 1; PathArray[i][j] != _T('\0'); j++) d++;
		i++;
	}
	else if (PathArray[i][0] == _T('\0'))
	{
		i++;
	}
	else {
		;
	}
	m = i;

	// ��t�H���_����̑��΃p�X�̍쐬
	_tcscpy(szERelativeFName, BaseDrive);
	if (BaseDrive[0] != _T('\0')) _tcscat(szERelativeFName, _T("/"));
	for (i = 0; i<n - d + 1; i++)
	{
		_tcscat(szERelativeFName, BasePathArray[i]);
		_tcscat(szERelativeFName, _T("/"));
	}
	for (; PathArray[m][0] != _T('\0'); m++)
	{
		_tcscat(szERelativeFName, PathArray[m]);
		_tcscat(szERelativeFName, _T("/"));
	}
	_tcscat(szERelativeFName, FName);
	_tcscat(szERelativeFName, Ext);

	return TRUE;
}
//  CMapProc�N���X  ---------------------------------------------------------------------------------------
//  �R���X�g���N�^
CMapProc::CMapProc(CGameMain*	pGMain)
{
	m_pGMain       = pGMain;
	m_nMapNo       = 0;
	m_bDrawMapLine = FALSE;
	for (DWORD i = 0; i < MAP_MAX; i++)
	{
		m_pMapArray[i] = NULL;
	}
	m_pBakImage   = new CSpriteImage(m_pGMain->m_pShader, _T("Data/image/aozora.png"));
	m_pSpriteMap  = new CSprite(m_pGMain->m_pShader); // �X�v���C�g�I�u�W�F�N�g�̐���
	m_pSpriteBak  = new CSprite(m_pBakImage);
	m_pSpriteLine = new CSprite(m_pGMain->m_pShader);

	InitMapAll();
}
//  �f�X�g���N�^
CMapProc::~CMapProc()
{
	for (DWORD i = 0; i < MAP_MAX; i++)
	{
		SAFE_DELETE(m_pMapArray[i]);
	}
	SAFE_DELETE(m_pSpriteMap);
	SAFE_DELETE(m_pSpriteBak);
	SAFE_DELETE(m_pSpriteLine);
	SAFE_DELETE(m_pBakImage);
}
// ----------------------------------------------------------------------
//
// �e�}�b�v�X�N���v�g�t�@�C����ǂݍ���Ń}�b�v�I�u�W�F�N�g�̍쐬
//
// -----------------------------------------------------------------------
void CMapProc::InitMapAll()
{
	// �X�e�[�W�O�@��̃X�e�[�W
	MapRead( _T("Data/Script/Map106.txt"), m_pMapArray[0]);

	// �X�e�[�W�P�@���̃X�e�[�W
	MapRead( _T("Data/Script/Map107.txt"), m_pMapArray[1]);

	// �X�e�[�W�Q�@�{�X�̃X�e�[�W
	MapRead( _T("Data/Script/Map108.txt"), m_pMapArray[2]);

	// �X�e�[�W3�@SP�X�e�[�W
	MapRead( _T("Data/Script/MapSP1.txt"), m_pMapArray[3]);

	// M.S �X�e�[�W4  ���틭���`�����X�X�e�[�W
	MapRead(_T("Data/Script/MapSW.txt"  ), m_pMapArray[4]);

	// �J�n�}�b�v�̐ݒ�
	SetMap(0);

}
// ----------------------------------------------------------------------
//
// �}�b�v�ړ��̏����@�@���ɐڐG�����Ƃ��Ă΂��
//
// ----------------------------------------------------------------------
void CMapProc::MoveMap()
{
	if (m_pGMain->i < 1) {
	int val;  // M.S �����̂���
	unsigned int now = (unsigned int)time(0);// M.S �������g���āA���틭���`�����X�X�e�[�W�̓���������
	srand(now);    // M.S ���ݎ����ŗ����p�^�[����������
	val = rand();  // M.S val�͗���
		m_pGMain->valS = val % 3; // M.S ���틭���`�����X�X�e�[�W�̏ꏊ������0�`2�ɂ���
		m_pGMain->i = 1;          // M.S ��x�̂ݏ�������
	}
	if (m_nMapNo == 0) {  // M.S ��̃X�e�[�W
		if (m_pGMain->henk == 1) {
			if (m_pGMain->valS == 0 && m_pGMain->mapSsw != true) {				
					m_pGMain->mapSsw = true;  // M.S ���틭���`�����X�X�e�[�W���Ăяo�����t���O��true
					SetMap(4);                // M.S ���틭���`�����X�X�e�[�W
					m_pGMain->m_pEnmProc->SetNonActive();	// �G��S�ď����B�G�̔����t���O�����Z�b�g����
					m_pGMain->m_pEffectProc->SetNonActive(); // �A�C�e����S�ď����B�A�C�e���̔����t���O�����Z�b�g����	
			}
			else {
				SetMap(1);	// ���̃}�b�v�͐��̃X�e�[�W
				m_pGMain->m_pEnmProc->SetNonActive();	// �G��S�ď����B�G�̔����t���O�����Z�b�g����
				m_pGMain->m_pEffectProc->SetNonActive();
			}
		}// �A�C�e����S�ď����B�A�C�e���̔����t���O�����Z�b�g����
	}
	else if (m_nMapNo == 1) {  // M.S ���̃X�e�[�W
		if (m_pGMain->valS == 1 && m_pGMain->mapSsw != true) {
			m_pGMain->mapSsw = true;  // M.S ���틭���`�����X�X�e�[�W���Ăяo�����t���O��true
			m_pGMain->mapNumP = 1;    // M.S ���틭���`�����X�X�e�[�W��̓{�X�̃X�e�[�W��
			SetMap(4);                // M.S ���틭���`�����X�X�e�[�W
			m_pGMain->m_pEnmProc->SetNonActive();	// �G��S�ď����B�G�̔����t���O�����Z�b�g����
			m_pGMain->m_pEffectProc->SetNonActive(); // �A�C�e����S�ď����B�A�C�e���̔����t���O�����Z�b�g����
		}
		else {
			SetMap(2);	// ���̃}�b�v�̓{�X�̃X�e�[�W
			m_pGMain->m_pEnmProc->SetNonActive();	// �G��S�ď����B�G�̔����t���O�����Z�b�g����
			m_pGMain->m_pEffectProc->SetNonActive();	// �A�C�e����S�ď����B�A�C�e���̔����t���O�����Z�b�g����
		}
	}
	else if (m_nMapNo == 2) {  // M.S �{�X�̃X�e�[�W
		if (m_pGMain->CR == 1) {   // M.S �������h�A(�S�[��)�Ȃ��
			m_pGMain->m_dwGameStatus = GAMECLEAR;  // �Q�[���N���A
		}
		else {
			if (m_pGMain->spP == 0) {
				SetMap(3);	// ���̃}�b�v��SP�X�e�[�W
				m_pGMain->m_pEnmProc->SetNonActive();	// �G��S�ď����B�G�̔����t���O�����Z�b�g����
				m_pGMain->m_pEffectProc->SetNonActive();
				m_pGMain->spP = 1;  // M.S SP�X�e�[�W��1�x�̂�
			}
		}
	}
	else if (m_nMapNo == 3) { // M.S SP�X�e�[�W
		if (m_pGMain->valS == 2 && m_pGMain->mapSsw != true) {
			m_pGMain->mapSsw = true;  // M.S ���틭���`�����X�X�e�[�W���Ăяo�����t���O��true
			m_pGMain->mapNumP = 1;    // M.S ���틭���`�����X�X�e�[�W��̓{�X�̃X�e�[�W��
			SetMap(4);                // M.S ���틭���`�����X�X�e�[�W��
			m_pGMain->m_pEnmProc->SetNonActive();	// �G��S�ď����B�G�̔����t���O�����Z�b�g����
			m_pGMain->m_pEffectProc->SetNonActive(); // �A�C�e����S�ď����B�A�C�e���̔����t���O�����Z�b�g����
		}
		else {
			SetMap(2);	// ���̃}�b�v�͂P
			m_pGMain->m_pEnmProc->SetNonActive();	// �G��S�ď����B�G�̔����t���O�����Z�b�g����
			m_pGMain->m_pEffectProc->SetNonActive();	// �A�C�e����S�ď����B�A�C�e���̔����t���O�����Z�b�g����
		}

	}		
	else if (m_nMapNo == 4) {   // M.S ���틭���`�����X�X�e�[�W
		if (m_pGMain->mapNumP == 0) {          // M.S ���̃X�e�[�W��
			SetMap(1);
			m_pGMain->m_pEnmProc->SetNonActive();	// �G��S�ď����B�G�̔����t���O�����Z�b�g����
			m_pGMain->m_pEffectProc->SetNonActive();// �A�C�e����S�ď����B�A�C�e���̔����t���O�����Z�b�g����
		}
		else if (m_pGMain->mapNumP == 1) {     // M.S �{�X�̃X�e�[�W��
			SetMap(2);
			m_pGMain->m_pEnmProc->SetNonActive();	// �G��S�ď����B�G�̔����t���O�����Z�b�g����
			m_pGMain->m_pEffectProc->SetNonActive();// �A�C�e����S�ď����B�A�C�e���̔����t���O�����Z�b�g����
		}
	}
}
// ----------------------------------------------------------------------
//
// �J�n�}�b�v�̐ݒ�
//
// �����@�F�@int no�@�}�b�v�ԍ�
//
// ----------------------------------------------------------------------
void CMapProc::SetMap(int no)
{
	// �J�n�}�b�v�m�n
	m_nMapNo = no;

	// �}�b�v�p�X�v���C�g�̐ݒ�
	m_pSpriteMap->SetSrc( m_pMapArray[m_nMapNo]->m_pMapImage, 0, 0, m_pMapArray[m_nMapNo]->m_nMapchipWidth, m_pMapArray[m_nMapNo]->m_nMapchipHeight);

	// �o�b�J�n�ʒu�̐ݒ�
	VECTOR2 vPos = VECTOR2(0, 0);
	for (DWORD i = 0; i < m_pMapArray[m_nMapNo]->m_nEvtMapLength; i++)
	{
		if (m_pMapArray[m_nMapNo]->m_EvtMap[i].m_nEvtID == 1 )  // �o�b�̃X�^�[�g�ʒu
		{
			vPos = m_pMapArray[m_nMapNo]->m_EvtMap[i].m_vStart;  // �o�b�̃X�^�[�g���W
			break;
		}
	}
	// �o�b�J�n�ʒu��ݒ肵�A�g�o���񕜂���
	m_pGMain->m_pPcProc->GetPcObjPtr()->SetPos( vPos);
	m_pGMain->m_pPcProc->GetPcObjPtr()->SetHp( m_pGMain->m_pPcProc->GetPcObjPtr()->GetMaxHp());
}
// ----------------------------------------------------------------------
//
// �}�b�v�̍X�V
//
// ----------------------------------------------------------------------
void  CMapProc::Update()
{
	VECTOR2 vScr;

	// �o�b�̈ʒu����X�N���[�����W��ݒ肷��
	vScr.x = m_pGMain->m_pPcProc->GetPcObjPtr()->GetPos().x + m_pGMain->m_pPcProc->GetPcObjPtr()->GetOf().x +  m_pGMain->m_pPcProc->GetPcObjPtr()->GetSprite()->GetSrcWidth() / 2 - WINDOW_WIDTH / 2;
	if (vScr.x > m_pMapArray[m_nMapNo]->m_nMapX * m_pMapArray[m_nMapNo]->m_nMapchipWidth - WINDOW_WIDTH)
		vScr.x = m_pMapArray[m_nMapNo]->m_nMapX * m_pMapArray[m_nMapNo]->m_nMapchipWidth - WINDOW_WIDTH;
	if (vScr.x < 0) vScr.x = 0;

	vScr.y = m_pGMain->m_pPcProc->GetPcObjPtr()->GetPos().y + m_pGMain->m_pPcProc->GetPcObjPtr()->GetOf().y + m_pGMain->m_pPcProc->GetPcObjPtr()->GetSprite()->GetSrcHeight() / 2 - WINDOW_HEIGHT / 2;
	if (vScr.y > m_pMapArray[m_nMapNo]->m_nMapY * m_pMapArray[m_nMapNo]->m_nMapchipHeight - WINDOW_HEIGHT)
		vScr.y = m_pMapArray[m_nMapNo]->m_nMapY * m_pMapArray[m_nMapNo]->m_nMapchipHeight - WINDOW_HEIGHT;
	if (vScr.y < 0) vScr.y = 0;

	m_pGMain->m_vScroll = vScr;			// �X�N���[�����W��ݒ�

	// �}�b�v���̕`������邩�ǂ���
	if (m_pGMain->m_pDI->CheckKey(KD_TRG, DIK_P))
	{
		if (m_bDrawMapLine)
		{
			m_bDrawMapLine = FALSE;
		}
		else {
			m_bDrawMapLine = TRUE;
		}
	}
	DrawBack();  // �w�i�}�b�v�̕`��
}
// ----------------------------------------------------------------------
//
// �}�b�v�̍X�V�Q
//
// ----------------------------------------------------------------------
void  CMapProc::Update2()
{
	DrawFore();
	if (m_bDrawMapLine) DrawMapLine();
}
// ----------------------------------------------------------------------
//
// �C�x���g�}�b�v�̒T������
//
// ����
// �@�@int         nStart;		// �T���J�n�ʒu
// �@�@int         nEvtID;		// �C�x���g�h�c
// �@�@DWORD       dwEvtNo;		// �C�x���g�m��
// �@�@VECTOR2 vPos;		// ���W(OUT)
//     int         nNext;       // ���J�n�ʒu(OUT) �ŏI�ɒB������@-1 
//
// �߂�l
//�@�@TRUE:��������  FALSE:������Ȃ�
//
// ----------------------------------------------------------------------
BOOL  CMapProc::SearchEvt( int nStart, int nEvtID, DWORD dwEvtNo, VECTOR2& vPos, int& nNext)
{
	BOOL bRet = FALSE;

	if (nStart < 0 || nStart >= m_pMapArray[m_nMapNo]->m_nEvtMapLength)
	{
		nNext = -1;
		return bRet;
	}

	for (DWORD i = nStart; i < m_pMapArray[m_nMapNo]->m_nEvtMapLength; i++)
	{
		if (m_pMapArray[m_nMapNo]->m_EvtMap[i].m_nEvtID == nEvtID &&	    // �C�x���g�}�b�v�@ID�@�G�̏o���ʒu
			m_pMapArray[m_nMapNo]->m_EvtMap[i].m_dwEvtNo & dwEvtNo)			// �C�x���g�}�b�v�@NO
		{
			vPos = m_pMapArray[m_nMapNo]->m_EvtMap[i].m_vStart;	// �����ʒu
			nNext = i + 1;  // ���̊J�n�ʒu��ݒ�
			bRet = TRUE;
			break;
		}
	}
	if (!bRet)
	{
		nNext = -1;
	}

	return bRet;
}
// ----------------------------------------------------------------------
//
// �}�b�v�̔w�i�̕`��
//
// ----------------------------------------------------------------------
void  CMapProc::DrawBack()
{

	// �X�e�[�W�w�i�̕`��i�S�����X�N���[���j�@�|�|�|�|�|�|�|�|�|�|
	VECTOR2 scr;

	scr.x = WINDOW_WIDTH  - ((int)(m_pGMain->m_vScroll.x / 2)) % WINDOW_WIDTH;
	scr.y = WINDOW_HEIGHT - ((int)(m_pGMain->m_vScroll.y / 2)) % WINDOW_HEIGHT;

	m_pSpriteBak->Draw(m_pBakImage, 0, 0, WINDOW_WIDTH - scr.x, WINDOW_HEIGHT - scr.y, scr.x, scr.y);
	m_pSpriteBak->Draw(m_pBakImage, scr.x, 0, 0, WINDOW_HEIGHT - scr.y, WINDOW_WIDTH - scr.x, scr.y);
	m_pSpriteBak->Draw(m_pBakImage, 0, scr.y, WINDOW_WIDTH - scr.x, 0, scr.x, WINDOW_HEIGHT - scr.y);
	m_pSpriteBak->Draw(m_pBakImage, scr.x, scr.y, 0, 0, WINDOW_WIDTH - scr.x, WINDOW_HEIGHT - scr.y);

	// �}�b�v�w�i�̕`��@�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|
	int x, y, no;

	for (y = 0; y < m_pMapArray[m_nMapNo]->m_nMapY; y++)
	{
		for (x = 0; x < m_pMapArray[m_nMapNo]->m_nMapX; x++)
		{
			no = m_pMapArray[m_nMapNo]->m_MapBakTbl[y*m_pMapArray[m_nMapNo]->m_nMapX + x];
			if ( no == -1)
			{
				;  		// �}�b�v�̖������͕`�悵�Ȃ�
			}else{
				m_pSpriteMap->m_ofX = no % 1000 * m_pMapArray[m_nMapNo]->m_nMapchipWidth;
				m_pSpriteMap->m_ofY = no / 1000 * m_pMapArray[m_nMapNo]->m_nMapchipHeight;
				m_pSpriteMap->Draw(x*m_pMapArray[m_nMapNo]->m_nMapchipWidth - m_pGMain->m_vScroll.x, y*m_pMapArray[m_nMapNo]->m_nMapchipHeight - m_pGMain->m_vScroll.y);
			}
		}
	}
	
}
// ----------------------------------------------------------------------
//
// �}�b�v�̑O�i�̕`��
//
// ----------------------------------------------------------------------
void  CMapProc::DrawFore()
{
	int x, y, no;

	for (y = 0; y < m_pMapArray[m_nMapNo]->m_nMapY; y++)
	{
		for (x = 0; x < m_pMapArray[m_nMapNo]->m_nMapX; x++)
		{
			no = m_pMapArray[m_nMapNo]->m_MapForTbl[y*m_pMapArray[m_nMapNo]->m_nMapX + x];
			if (no == -1)
			{
				;		// �}�b�v�̖������͕`�悵�Ȃ�
			}else {
				m_pSpriteMap->m_ofX = no % 1000 * m_pMapArray[m_nMapNo]->m_nMapchipWidth;
				m_pSpriteMap->m_ofY = no / 1000 * m_pMapArray[m_nMapNo]->m_nMapchipHeight;
				m_pSpriteMap->Draw(x*m_pMapArray[m_nMapNo]->m_nMapchipWidth - m_pGMain->m_vScroll.x, y*m_pMapArray[m_nMapNo]->m_nMapchipHeight - m_pGMain->m_vScroll.y);
			}
		}
	}
	
}
// ----------------------------------------------------------------------
//
// �}�b�v���̕`��
//
// ----------------------------------------------------------------------
void  CMapProc::DrawMapLine()
{
	int i;

	for (i = 0; i < m_pMapArray[m_nMapNo]->m_nMapLnLength; i++)
	{
		m_pSpriteLine->DrawLine(m_pMapArray[m_nMapNo]->m_MapLn[i].m_vStart.x - m_pGMain->m_vScroll.x, m_pMapArray[m_nMapNo]->m_MapLn[i].m_vStart.y - m_pGMain->m_vScroll.y,
										m_pMapArray[m_nMapNo]->m_MapLn[i].m_vEnd.x - m_pGMain->m_vScroll.x, m_pMapArray[m_nMapNo]->m_MapLn[i].m_vEnd.y - m_pGMain->m_vScroll.y, 3, RGB(255, 0, 0));
		float cx = (m_pMapArray[m_nMapNo]->m_MapLn[i].m_vStart.x + m_pMapArray[m_nMapNo]->m_MapLn[i].m_vEnd.x) / 2;
		float cy = (m_pMapArray[m_nMapNo]->m_MapLn[i].m_vStart.y + m_pMapArray[m_nMapNo]->m_MapLn[i].m_vEnd.y) / 2;
		float nx = cx + m_pMapArray[m_nMapNo]->m_MapLn[i].m_vNormal.x * 10.0f;
		float ny = cy + m_pMapArray[m_nMapNo]->m_MapLn[i].m_vNormal.y * 10.0f;
		m_pSpriteLine->DrawLine( cx - m_pGMain->m_vScroll.x, cy - m_pGMain->m_vScroll.y, nx - m_pGMain->m_vScroll.x, ny - m_pGMain->m_vScroll.y, 3, RGB(255, 0, 0));
	}
}
// ----------------------------------------------------------------------------------------
//
// �}�b�v�̐ڐG����ƓK�؂Ȉʒu�ւ̈ړ�
//
//   �@�@�}�b�v����˂������Ă��邩�`�F�b�N����
//   �A�@�}�b�v���ɋߐڂ��Ă��邩�i�L�������H������ł��邩�j�`�F�b�N����
//
//   �˂������Ă��邩�ߐڂ��Ă���Ƃ��A�����lm_vPosUp��@�������ɐH�����ݕ������A�߂��Ă��
//
//   �@�@�߂�l�F�˂������Ă��邩�ߐڂ��Ă���Ƃ��^�BpHitmapline:�ڐG�����}�b�v���̃A�h���X���Ԃ�
// ----------------------------------------------------------------------------------------
BOOL CMapProc::isCollisionMoveMap( CBaseObj* obj, CMapLine* &pHitmapline)
{
	int i, n, rw;
	BOOL bRet = FALSE;
	VECTOR2 vHitpos = VECTOR2(0,0);
	VECTOR2 vHpw = VECTOR2(0,0);
	float dist, dw;

	pHitmapline = NULL;
	dist = 999999;
	for (n = 0, i = 0; i< m_pMapArray[m_nMapNo]->m_nMapLnLength; i++) {
		rw = CheckMapcross(m_pMapArray[m_nMapNo]->m_MapLn[i], obj, vHpw);		// �@�@�}�b�v���Ƃ̓˂���������
		if (rw) {	// �˂������Ă���Ƃ�
			bRet = rw;
			dist = GetDistance(m_pMapArray[m_nMapNo]->m_MapLn[i], obj);
			n = i;
			vHitpos = vHpw;
			break;
		}
		else {
			rw = CheckMapnear(m_pMapArray[m_nMapNo]->m_MapLn[i], obj, vHpw);	// �A�@�}�b�v���Ƃ̋ߐڔ���i�L�������}�b�v���ɐH������ł��邩�j
			if (rw) {
				bRet = rw;
				dw = GetDistance(m_pMapArray[m_nMapNo]->m_MapLn[i], obj);
				if (dist > dw) {						// ��ԋ߂��}�b�v����T��
					n = i;
					dist = dw;
					vHitpos = vHpw;
				}
			}
		}
	}

	i = n;
	if (bRet) {	// �˂������Ă��邩�ߐڂ��Ă���Ƃ��A�@�������ɐH�����ݕ������A�߂��Ă��

		pHitmapline = &(m_pMapArray[m_nMapNo]->m_MapLn[i]);  // �ڐG�����}�b�v���̃A�h���X
		obj->SetPosUp( obj->GetPosUp() + VECTOR2(
			round(-(dist - obj->GetSprite()->GetSrcWidth() / 2)   * m_pMapArray[m_nMapNo]->m_MapLn[i].m_vNormal.x),
			round(-(dist - obj->GetSprite()->GetSrcHeight() / 2)  * m_pMapArray[m_nMapNo]->m_MapLn[i].m_vNormal.y)));
	}

	// �ڐG���Ă���Ƃ��݂̂Q��ڂ̃`�F�b�N���s��
	if (bRet) {
		bRet = FALSE;	// ��U�N�����[����
		dist = 999999;
		for (n = 0, i = 0; i<m_pMapArray[m_nMapNo]->m_nMapLnLength; i++) {
			rw = CheckMapcross(m_pMapArray[m_nMapNo]->m_MapLn[i], obj, vHpw);		// �}�b�v���Ƃ̓˂���������
			if (rw) {	// �˂������Ă���Ƃ�
				bRet = rw;
				dist = GetDistance(m_pMapArray[m_nMapNo]->m_MapLn[i], obj);
				n = i;
				vHitpos = vHpw;
				break;
			}
			else {
				rw = CheckMapnear(m_pMapArray[m_nMapNo]->m_MapLn[i], obj, vHpw);	// �}�b�v���Ƃ̋ߐڔ���i�L�������}�b�v���ɐH������ł��邩�j
				if (rw) {
					bRet = rw;
					dw = GetDistance(m_pMapArray[m_nMapNo]->m_MapLn[i], obj);
					if (dist > dw) {						// ��ԋ߂��}�b�v����T��
						n = i;
						dist = dw;
						vHitpos = vHpw;
					}
				}
			}
		}

		i = n;
		if (bRet) {	// �˂������Ă��邩�ߐڂ��Ă���Ƃ��Am_vPosUp��@�������ɐH�����ݕ������A�߂��Ă��

			obj->SetPosUp(obj->GetPosUp() + VECTOR2(
				round(-(dist - obj->GetSprite()->GetSrcWidth() / 2)   * m_pMapArray[m_nMapNo]->m_MapLn[i].m_vNormal.x),
				round(-(dist - obj->GetSprite()->GetSrcHeight() / 2)  * m_pMapArray[m_nMapNo]->m_MapLn[i].m_vNormal.y)));
		}
		bRet = TRUE;	// �ēx�Z�b�g����
	}

	return bRet;
}
// ----------------------------------------------------------------------------------------
//
// �}�b�v���Ƃ̓˂���������
//
// �@�߂�l�F�������Ă���Ƃ��^�B��_���W��hitpos�ɕԂ�
//
// ----------------------------------------------------------------------------------------
BOOL CMapProc::CheckMapcross(CMapLine map, CBaseObj* obj, VECTOR2 &hitpos)
{

	BOOL bRet = FALSE;

	// �����P�@���P�C���Q   �E�E�E�E�@�}�b�v��
	VECTOR2  m1 = map.m_vStart, m2 = map.m_vEnd;
	// �����Q�@�����P�C�����Q �E�E�E�@�I�u�W�F�N�g�ړ�
	VECTOR2  oj1 = obj->GetCenterPos();
	VECTOR2  oj2 = obj->GetCenterPos() + obj->GetPosUp();

	// �Q�����̌����`�F�b�N
	bRet = CheckLinecross(m1, m2, oj1, oj2, hitpos);

	return bRet;
}
// ----------------------------------------------------------------------------------------
//
// �Q�����̌����`�F�b�N
// �@�������ƒ������̌����`�F�b�N�B
//
// �@�߂�l�F�������Ă���Ƃ��^�B��_���W��hitpos�ɕԂ�
//
// ----------------------------------------------------------------------------------------
BOOL CMapProc::CheckLinecross(VECTOR2 a1, VECTOR2 a2, VECTOR2 b1, VECTOR2 b2, VECTOR2 &hitpos)
{

	BOOL bRet = FALSE;

	// ��_�@����
	VECTOR2  ap = VECTOR2(0, 0);
	float d1, d2;

	// �����̒������O�̂Ƃ�
	if ((a1.x == a2.x && a1.y == a2.y) ||
		(b1.x == b2.x && b1.x == b2.y)) {
		return bRet;
	}

	// ��_�����邩
	float dev = (a2.y - a1.y) * (b2.x - b1.x) - (a2.x - a1.x) * (b2.y - b1.y);
	if (dev == 0) {// ���s���̂Ƃ�
		return bRet;
	}

	// ��_�����߂�
	d1 = (b1.y*b2.x - b1.x*b2.y);
	d2 = (a1.y*a2.x - a1.x*a2.y);

	ap.x = d1*(a2.x - a1.x) - d2*(b2.x - b1.x);
	ap.x /= dev;
	ap.y = d1*(a2.y - a1.y) - d2*(b2.y - b1.y);
	ap.y /= dev;

	// ��_�������͈̔͂̒��ɂ��邩
	if ((CheckRange(a1.x, a2.x, ap.x) && CheckRange(a1.y, a2.y, ap.y)) &&
		(CheckRange(b1.x, b2.x, ap.x) && CheckRange(b1.y, b2.y, ap.y))) {
		bRet = TRUE;
	}

	if (bRet) {
		hitpos = ap;
	}

	return bRet;
}
// ----------------------------------------------------------------------------------------
//
// �͈̓`�F�b�N
//
// �@�߂�l�Fpt�����Ƃ��̊Ԃɓ����Ă���Ƃ��^�B
//
// ----------------------------------------------------------------------------------------
BOOL CMapProc::CheckRange(float l, float r, float pt)
{
	float low, hi;
	float mgn = 0.05f;	// �덷

	if (l <= r) {
		low = l;
		hi = r;
	}
	else {
		low = r;
		hi = l;
	}
	low -= mgn;
	hi += mgn;

	if (low <= pt && pt <= hi) {
		return TRUE;
	}
	else {
		return FALSE;
	}
}
// ----------------------------------------------------------------------------------------
//
// �}�b�v���Ƃ̋ߐڃ`�F�b�N
//
// �@�L�������}�b�v���ɐH������ł��邩�`�F�b�N�B
//
// �@�߂�l�F�H������ł���Ƃ��^�B�ڐG�ʒu��vHitpos�ɕԂ�
//
// ----------------------------------------------------------------------------------------
BOOL CMapProc::CheckMapnear(CMapLine MapLn, CBaseObj* obj, VECTOR2 &vHitpos)
{
	BOOL bRet = FALSE;

	// �@�@�L�����ƃ}�b�v���̖@�������Ƃ̐H�����݃`�F�b�N���s�� --------------------------------
	// �L�����̒��S����A�}�b�v���̖@�������ɃL�����̑傫�����̒���������
	VECTOR2  p0, p1, p2;
	p0 = obj->GetCenterPos() + obj->GetPosUp();
	p1.x = p0.x - MapLn.m_vNormal.x * obj->GetSprite()->GetSrcWidth() / 2;
	p1.y = p0.y - MapLn.m_vNormal.y * obj->GetSprite()->GetSrcHeight() / 2;
	p2.x = p0.x + MapLn.m_vNormal.x * obj->GetSprite()->GetSrcWidth() / 2;
	p2.y = p0.y + MapLn.m_vNormal.y * obj->GetSprite()->GetSrcHeight() / 2;

	// �����ƃ}�b�v���Ƃ̌����`�F�b�N
	bRet = CheckLinecross( MapLn.m_vStart,  MapLn.m_vEnd, p1, p2, vHitpos);

	// �A�@�������Ă��Ȃ��ꍇ�A�L�����Ɛ����������Ƃ̐H�����݃`�F�b�N���s��---------------------
	if (!bRet) {
		// �L�����̒��S����A�����������ɃL�����̑傫�����̒���������
		p0 = obj->GetCenterPos() + obj->GetPosUp();

		p1.x = p0.x - 0 * obj->GetSprite()->GetSrcWidth() / 2;
		p1.y = p0.y - 1 * obj->GetSprite()->GetSrcHeight() / 2;
		p2.x = p0.x + 0 * obj->GetSprite()->GetSrcWidth() / 2;
		p2.y = p0.y + 1 * obj->GetSprite()->GetSrcHeight() / 2;

		// �����ƃ}�b�v���Ƃ̌����`�F�b�N
		bRet = CheckLinecross(MapLn.m_vStart, MapLn.m_vEnd, p1, p2, vHitpos);
	}
	return bRet;
}
// ----------------------------------------------------------------------------------------
//
// �}�b�v���Ƃ̋��������߂�
//
// �@�߂�l�F �}�b�v���Ƃ̋����B�������A�@���������v���X�ƂȂ�B
//
// ----------------------------------------------------------------------------------------
float  CMapProc::GetDistance(CMapLine MapLn, CBaseObj* obj)
{
	VECTOR2  b = obj->GetCenterPos() + obj->GetPosUp() - MapLn.m_vStart;
	float len;

	// ���ς́A�x�N�g���̖@�������̋����ɂȂ�
	// (�@���̒������P�̂���)
	len = GetDot( MapLn.m_vNormal, b );

	return len;
}
// ----------------------------------------------------------------------------------------
//
// �Q�_�Ԃ̋��������߂�
//
// ----------------------------------------------------------------------------------------
float CMapProc::GetLength(VECTOR2 p1, VECTOR2 p2)
{
	return sqrtf((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
}
// ----------------------------------------------------------------------------------------
//
// �x�N�g���̊O�ς����߂�
// �i�Q�����̏ꍇ�A�O�ς̓X�J���[�l�ƂȂ�j
//
// ----------------------------------------------------------------------------------------
float CMapProc::GetCross(VECTOR2 a, VECTOR2 b)
{
	return  a.x * b.y - a.y * b.x;
}
// ----------------------------------------------------------------------------------------
//
// �x�N�g���̓��ς����߂�
//
// ----------------------------------------------------------------------------------------
float CMapProc::GetDot( VECTOR2 a, VECTOR2 b)
{
	return  a.x * b.x + a.y * b.y;
}


