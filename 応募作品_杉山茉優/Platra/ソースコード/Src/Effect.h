//=============================================================================
//		�R�c�Q�[���v���O����
//		�b�R�c�`�����P�P�Q                             ver 3.0        2021.1.11
//
//		�G�t�F�N�g�̏���
//										2021.1.11					Effect.h
//=============================================================================

#pragma once
#include "GameMain.h"

#define  PARTICLE_MAX   50
#define  BILLBOARD_MAX  1000
#define  BILLFIRE_MAX   500
#define  BILLSTART_MAX  30

class CDirect3D;
// ========================================================================================
//
//	�p�[�e�B�N��
//�i�|�C���g�X�v���C�g�Ńp�[�e�B�N���������j
//
// ========================================================================================
//
// �p�[�e�B�N���\����
//
struct PART
{
	VECTOR3 Pos;
	VECTOR3 Dir;
	float       Speed;
	int         BirthFrame;
	PART()
	{
		ZeroMemory(this, sizeof(PART));
	}
};
//
// ���_�̍\����
//
struct PARTICLE_VERTEX
{
	VECTOR3 Pos; //�ʒu
};
struct BILLBOARD_VERTEX
{
	VECTOR3 Pos; //�ʒu
	VECTOR2 UV; //�e�N�X�`���[���W
};

// -----------------------------------------------------------------------------
//	�p�[�e�B�N���̃I�u�W�F�N�g�N���X
//�i�|�C���g�X�v���C�g�Ńp�[�e�B�N���������j
//
// ----------------------------------------------------------------------------
class CParticleObj : public CBaseObj
{
protected:
	// 
	CDirect3D*	   m_pD3D;
	CShader*       m_pShader;
	FLOAT          m_fAlpha;
	float          m_fSize;  // �p�[�e�B�N���̃T�C�Y // -- 2018.8.23
	int            m_MaxParticle;
	VECTOR3        m_vEmitPos;
	PART*          m_pPartArray;
	int            m_Frame;
	int            m_FrameEnd;
	float          m_fSpeed;  // �p�[�e�B�N���̈ړ��X�s�[�h
	int            m_iBarthFrame;     // �p�[�e�B�N���̈ړ��J�n�܂ł̍ő�҂����ԁi�����_���j

	ID3D11Buffer*  m_pVertexBuffer;
	ID3D11ShaderResourceView* m_pTexture;//�e�N�X�`���[�i�p�[�e�B�N���v���V�[�W���̃e�N�X�`���A�h���X���Z�b�g���邾���j

public:	
	// 
	CParticleObj(CGameMain*  pGMain, int MaxParticle );
	virtual	~CParticleObj();

	void Init(int MaxParticle);
	HRESULT SetSrc();

	BOOL Start(VECTOR3 vEmitPos, VECTOR3 vNormal = VECTOR3(0.0f,0.0f,0.0f)) override;
	void Update() override;
	void Render();
	void RenderParticle(MATRIX4X4 W, MATRIX4X4 V, MATRIX4X4 P);  // -- 2017.8.25

	void SetTexture(ID3D11ShaderResourceView* pTexture) { m_pTexture = pTexture; }

};
// ========================================================================================
//
//	�p�[�e�B�N���̃v���V�[�W���N���X
//
// ========================================================================================
class CParticleProc : public CBaseProc
{
protected:
	ID3D11ShaderResourceView* m_pTexture;  //�e�N�X�`���[�i�p�ӂ���̂̓��\�[�X�r���[�����ł����j
public:
	BOOL Start(VECTOR3 vEmitPos, VECTOR3 vNormal = VECTOR3(0.0f, 0.0f, 0.0f));
	CParticleProc(CGameMain* pGMain);	// �R���X�g���N�^
	~CParticleProc();	// �f�X�g���N�^
};
// ========================================================================================
//
//	�r���{�[�h(���H�̃L���L��)
//
// ========================================================================================
// ------------------------------------------------------------------------
//	�r���{�[�h�̃I�u�W�F�N�g�N���X
//
// ------------------------------------------------------------------------
class CBillboardObj : public CBaseObj
{
protected:
	float			m_fDestWidth;
	float			m_fDestHeight;
	DWORD			m_dwSrcX;
	DWORD			m_dwSrcY;
	DWORD			m_dwSrcWidth;
	DWORD			m_dwSrcHeight;
public:

	// 
	CDirect3D*	   m_pD3D;
	CShader*       m_pShader;
	VECTOR3        m_vPos;
	VECTOR2        m_vUVOffset;
	VECTOR2        m_vUVScale;  // -- 2019.7.17
	DWORD          m_dwNumX;
	DWORD          m_dwNumY;
	DWORD          m_dwFrame;
	FLOAT          m_fAlpha;
	DWORD          m_dwImageWidth;
	DWORD          m_dwImageHeight;

	ID3D11Buffer*  m_pVertexBuffer;
	ID3D11ShaderResourceView* m_pTexture;//�e�N�X�`���[�i�r���{�[�h�v���V�[�W���̃e�N�X�`���A�h���X���Z�b�g���邾���j
	CFbxMesh*      m_pMesh;    //���b�V���i�r���{�[�h�v���V�[�W���̃��b�V���A�h���X���Z�b�g���邾���j  // -- 2019.7.17

public:
	CBillboardObj(CGameMain* pGMain);
	virtual	~CBillboardObj();

	void Init();
	HRESULT SetSrc( float fDestWidth, float fDestHeight, DWORD dwSrcX, DWORD dwSrcY, DWORD dwSrcWidth, DWORD dwSrcHeight, DWORD dwNumX, DWORD dwNumY);
	DWORD   GetSrcWidth()  {return m_dwSrcWidth;}
	DWORD   GetSrcHeight() {return m_dwSrcHeight;}
	float   GetDestWidth()  {return m_fDestWidth;}
	float   GetDestHeight() {return m_fDestHeight;}

	BOOL Start(VECTOR3 vPos) override;
	void Update() override;
	BOOL Render();
	void RenderMesh();

	bool drawFlag;   // false�ŃG�t�F�N�g������
};
// ========================================================================================
//
//	�r���{�[�h�̃v���V�[�W���N���X(���H�̃L���L��)
//
// ========================================================================================
class CBillboardProc : public CBaseProc
{
protected:
	ID3D11ShaderResourceView* m_pTexture;  //�e�N�X�`���[�i�p�ӂ���̂̓��\�[�X�r���[�����ł����j
	DWORD m_dwImageWidth;
	DWORD m_dwImageHeight;
	CFbxMesh* m_pMesh;  // �����r���{�[�h�X�^�e�B�b�N���b�V��  // -- 2019.7.17
public:
	// M.S �G�t�F�N�g�I�u�W�F�N�g�̃|�C���^�̎擾
	CBillboardObj* GetBillboardLineGlitterObjPtr(int i) { return (CBillboardObj*)GetObjArrayPtr()[i]; }//
	BOOL Start(VECTOR3 vPos);
	HRESULT Load(TCHAR* szFName);
	CBillboardProc(CGameMain* pGMain);	// �R���X�g���N�^
	virtual	~CBillboardProc();	// �f�X�g���N�^
	void Render();        // M.S �A�j���[�V�������~�߂ĕ`��
	bool onlyRenderFlag;  // M.S �`��݂̂���t���O
};
// ========================================================================================
//
//	�r���{�[�h�@�����₫
//
// ========================================================================================
// ------------------------------------------------------------------------
//	�r���{�[�h�@�����₫�̃I�u�W�F�N�g�N���X
//
// ------------------------------------------------------------------------
class CBillFireObj : public CBaseObj
{
protected:
	float			m_fDestWidth;
	float			m_fDestHeight;
	DWORD			m_dwSrcX;
	DWORD			m_dwSrcY;
	DWORD			m_dwSrcWidth;
	DWORD			m_dwSrcHeight;

public:
	// 
	CDirect3D*	   m_pD3D;
	CShader*       m_pShader;
	VECTOR3        m_vPos;
	VECTOR2        m_vUVOffset;
	BOOL           m_bAuto;
	DWORD          m_dwNumX;
	DWORD          m_dwNumY;
	DWORD          m_dwFrame;
	FLOAT          m_fAlpha;
	DWORD          m_dwImageWidth;
	DWORD          m_dwImageHeight;

	ID3D11Buffer*  m_pVertexBuffer;
	ID3D11ShaderResourceView* m_pTexture;//�e�N�X�`���[�i�r���{�[�h�����₫�v���V�[�W���̃e�N�X�`���A�h���X���Z�b�g���邾���j
public:
	CBillFireObj(CGameMain* pGMain);
	virtual	~CBillFireObj();

	void Init();
	HRESULT SetSrc(float fDestWidth, float fDestHeight, DWORD dwSrcX, DWORD dwSrcY, DWORD dwSrcWidth, DWORD dwSrcHeight, DWORD dwNumX, DWORD dwNumY);
	DWORD   GetSrcWidth() { return m_dwSrcWidth; }
	DWORD   GetSrcHeight() { return m_dwSrcHeight; }

	BOOL Start(VECTOR3 vPos) override;
	void Update() override;
	BOOL Render();
};
// ========================================================================================
//
//	�r���{�[�h�@�����₫�̃v���V�[�W���N���X
//
// ========================================================================================
class CBillFireProc : public CBaseProc
{
protected:
	ID3D11ShaderResourceView* m_pTexture;  //�e�N�X�`���[�i�p�ӂ���̂̓��\�[�X�r���[�����ł����j
	DWORD m_dwImageWidth;
	DWORD m_dwImageHeight;
public:
	BOOL Start(VECTOR3 vPos);
	CBillFireObj* Start();
	HRESULT Load(TCHAR* szFName);
	CBillFireProc(CGameMain* pGMain);	// �R���X�g���N�^
	virtual	~CBillFireProc();	// �f�X�g���N�^
};
// ========================================================================================
//
//	M.S �r���{�[�h(�������G�t�F�N�g)
//
// ========================================================================================
// ------------------------------------------------------------------------
//	M.S �r���{�[�h�̃I�u�W�F�N�g�N���X
//
// ------------------------------------------------------------------------
class CBillboardBornStarObj : public CBaseObj
{
protected:
	float			m_fDestWidth;
	float			m_fDestHeight;
	DWORD			m_dwSrcX;
	DWORD			m_dwSrcY;
	DWORD			m_dwSrcWidth;
	DWORD			m_dwSrcHeight;
public:

	CDirect3D*	   m_pD3D;
	CShader*       m_pShader;
	VECTOR3        m_vPos;
	VECTOR2        m_vUVOffset;
	VECTOR2        m_vUVScale;  // -- 2019.7.17
	DWORD          m_dwNumX;
	DWORD          m_dwNumY;
	DWORD          m_dwFrame;
	FLOAT          m_fAlpha;
	DWORD          m_dwImageWidth;
	DWORD          m_dwImageHeight;

	ID3D11Buffer*  m_pVertexBuffer;
	ID3D11ShaderResourceView* m_pTexture;//�e�N�X�`���[�i�r���{�[�h�v���V�[�W���̃e�N�X�`���A�h���X���Z�b�g���邾���j
	CFbxMesh*      m_pMesh;    //���b�V���i�r���{�[�h�v���V�[�W���̃��b�V���A�h���X���Z�b�g���邾���j  // -- 2019.7.17

public:
	CBillboardBornStarObj(CGameMain* pGMain);
	virtual	~CBillboardBornStarObj();

	void Init();
	HRESULT SetSrc(float fDestWidth, float fDestHeight, DWORD dwSrcX, DWORD dwSrcY, DWORD dwSrcWidth, DWORD dwSrcHeight, DWORD dwNumX, DWORD dwNumY);
	DWORD   GetSrcWidth() { return m_dwSrcWidth; }
	DWORD   GetSrcHeight() { return m_dwSrcHeight; }
	float   GetDestWidth() { return m_fDestWidth; }
	float   GetDestHeight() { return m_fDestHeight; }

	BOOL Start(VECTOR3 vPos) override;
	void Update() override;
	BOOL Render();
	void RenderMesh();
};
// ========================================================================================
//
//	M.S �f�������̃v���V�[�W���N���X(�������G�t�F�N�g)
//
// ========================================================================================
class CBillboardBornStarProc : public CBaseProc
{
protected:
	ID3D11ShaderResourceView* m_pTexture;  //�e�N�X�`���[�i�p�ӂ���̂̓��\�[�X�r���[�����ł����j
	DWORD m_dwImageWidth;
	DWORD m_dwImageHeight;
	CFbxMesh* m_pMesh;  // �����r���{�[�h�X�^�e�B�b�N���b�V��  // -- 2019.7.17
public:
	BOOL Start(VECTOR3 vPos);
	HRESULT Load(TCHAR* szFName);
	CBillboardBornStarProc(CGameMain* pGMain);	// �R���X�g���N�^
	virtual	~CBillboardBornStarProc();	// �f�X�g���N�^
};
// ========================================================================================
//
//	�G�t�F�N�g�S�̂̃��C���v���V�[�W���N���X
//
// ========================================================================================
class CEffectProc : public CBaseProc
{
public:
	CParticleProc*		m_pParticleProc;
	CBillboardProc*		m_pBillProc;         //���H�̃L���L��
	CBillFireProc*		m_pBillFireProc;     //�����₫
	CBillboardBornStarProc* m_pBillStarProc; //M.S �������G�t�F�N�g
public:
	CEffectProc(CGameMain* pGMain);	// �R���X�g���N�^
	virtual	~CEffectProc() { ; }
};

