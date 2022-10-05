// ========================================================================================
//
// �X�v���C�g�̏���                                               ver 2.8        2020.2.15
//
//   �O�o�[�W�����̏����ɉ����ADrawLine ���̕`�揈���� DrawRect �l�p�̕`�揈�����������
//   Sprite.h Sprite.cpp Sprite2D.hlsli Direct3D.h ���ύX�ƂȂ��Ă���
//
// ========================================================================================

#pragma once

//�w�b�_�[�t�@�C���̃C���N���[�h
#include <stdio.h>
#include <windows.h>

#include "Main.h"
#include "Direct3D.h"
#include "Shader.h"

//
// �}�N����`
//
// �쐬����t�H���g�e�N�X�`���̍ő吔
#define  TEXT_DATA_MAX  100

//
// �X�v���C�g�p���_�̍\����
//
struct SpriteVertex
{
	VECTOR3 Pos;   //�ʒu
	VECTOR2 UV;	   //�e�N�X�`���[���W
};

//
// CSpriteImage�N���X
//
class CShader;

class CSpriteImage
{
public:
	// Direct3D11
	CDirect3D*     m_pD3D;
	CShader*       m_pShader;

	ID3D11ShaderResourceView* m_pTexture;//�e�N�X�`���[�i�p�ӂ���̂̓��\�[�X�r���[�����ł����j
	DWORD          m_dwImageWidth;
	DWORD          m_dwImageHeight;

	CSpriteImage(CShader* pShader);
	CSpriteImage(CShader* pShader, TCHAR* TName);
	~CSpriteImage();
	HRESULT Load(TCHAR* TName);
};

//
// CSprite�N���X
//
class CSprite
{
protected:
	DWORD			m_dwSrcX;
	DWORD			m_dwSrcY;
	DWORD			m_dwSrcWidth;
	DWORD			m_dwSrcHeight;
	DWORD			m_dwDestWidth;
	DWORD			m_dwDestHeight;

public:
	// Direct3D11
	CDirect3D*      m_pD3D;
	CShader*        m_pShader;

	ID3D11Buffer*   m_pVertexBufferSprite;
	ID3D11Buffer*   m_pVertexBufferLine;    // -- 2017.10.9
	ID3D11Buffer*   m_pVertexBufferRect;    // -- 2018.3.20

	CSpriteImage*   m_pImage;
	DWORD			m_ofX;
	DWORD			m_ofY;
	VECTOR4         m_vDiffuse;   // �f�B�t���[�Y�F(x:r y:g z:b w:a)�B�X�v���C�g�̂ݎg�p�B���C����l�p�`�ɂ͎g�p���Ȃ��B  // -- 2020.1.24
	int             m_nBlend;     // �u�����h�X�e�[�g  0:�ʏ� 1:���ߐF�i�����l�j 2:���Z����     // -- 2019.8.18

public:
	CSprite(CShader* pShader);
	CSprite(CSpriteImage* pImage);    // -- 2017.10.9
	CSprite(CSpriteImage* pImage, DWORD srcX, DWORD srcY, DWORD srcwidth, DWORD srcheight);
	CSprite(CSpriteImage* pImage, DWORD srcX, DWORD srcY, DWORD srcwidth, DWORD srcheight, DWORD destwidth, DWORD destheight);
	~CSprite();
	void    SetImage(CSpriteImage* pImage);    // -- 2017.10.9
	HRESULT SetSrc( DWORD srcX, DWORD srcY, DWORD srcwidth, DWORD srcheight);
	HRESULT SetSrc( DWORD srcX, DWORD srcY, DWORD srcwidth, DWORD srcheight, DWORD destwidth, DWORD destheight);
	HRESULT SetSrc( CSpriteImage* pImage, DWORD srcX, DWORD srcY, DWORD width, DWORD height);
	HRESULT SetSrc( CSpriteImage* pImage, DWORD srcX, DWORD srcY, DWORD width, DWORD height, DWORD destwidth, DWORD destheight);
	DWORD   GetSrcX() { return m_dwSrcX; }    // -- 2017.10.9
	DWORD   GetSrcY() { return m_dwSrcY; }    // -- 2017.10.9
	DWORD   GetSrcWidth() { return m_dwSrcWidth; }
	DWORD   GetSrcHeight() { return m_dwSrcHeight; }
	DWORD   GetDestWidth() { return m_dwDestWidth; }
	DWORD   GetDestHeight() { return m_dwDestHeight; }

	void    Draw(float posX, float posY);
	void    Draw(MATRIX4X4 mWorld);
	void    Draw(CSpriteImage* pImage, float posX, float posY, DWORD srcX, DWORD srcY, DWORD srcwidth, DWORD srcheight, float fAlpha = 1.0f);
	void    Draw(CSpriteImage* pImage, float posX, float posY, DWORD srcX, DWORD srcY, DWORD srcwidth, DWORD srcheight, DWORD destwidth, DWORD destheight, float fAlpha = 1.0f);
	void    Draw(CSpriteImage* pImage, MATRIX4X4 mWorld, DWORD srcX, DWORD srcY, DWORD srcwidth, DWORD srcheight, float fAlpha = 1.0f);
	void    Draw(CSpriteImage* pImage, MATRIX4X4 mWorld, DWORD srcX, DWORD srcY, DWORD srcwidth, DWORD srcheight, DWORD destwidth, DWORD destheight, float fAlpha = 1.0f);
	void    DrawLine(float StartX, float StartY, float EndX, float EndY, DWORD Width, DWORD colorABGR, float fAlpha = 1.0f);
	void    DrawRect(float posX, float posY, DWORD width, DWORD height, DWORD colorABGR, float fAlpha = 1.0f);    // -- 2018.3.20

	void    SetShader();
	void    ResetShader();


};

// ========================================================================================
//
// �t�H���g�@�e�N�X�`���[�̏���
// 
// ========================================================================================
//
// �����t�H���g�̍\����
//
struct FontData
{
	TEXTMETRIC   TM;
	GLYPHMETRICS GM;
	BYTE*        ptr;
	FontData()
	{
		ZeroMemory(this, sizeof(FontData));
	}
};

//
// �e�L�X�g�f�[�^�̍\����
//
struct TextData
{
	TCHAR*                      m_szText;           // -- 2018.12.28
	int                         m_iFontsize;
	DWORD                       m_dwColor;
	float                       m_fAlpha;
	ID3D11ShaderResourceView*	m_pResourceView; //�e�N�X�`���[���\�[�X�r���[
	ID3D11Buffer*				m_pVertexBufferFont;
	TextData()
	{
		ZeroMemory(this, sizeof(TextData));
	}
};
//
// CFontTexture�N���X
//
class CFontTexture
{
public:
	// Direct3D11
	CDirect3D*     m_pD3D;
	CShader*       m_pShader;

	TextData       m_TextData[TEXT_DATA_MAX];
	DWORD          m_Idx;       // TextData�̃C���f�b�N�X

	void Refresh();
	void Draw(float posX, float posY, TCHAR* text, int fontsize, DWORD colorABGR, float fAlpha=1.0f, TCHAR* szFontName=NULL);
	void Draw(MATRIX4X4 mWorld, TCHAR* text, int fontsize, DWORD colorABGR, float fAlpha=1.0f, TCHAR* szFontName=NULL);
	void SetShader();
	void ResetShader();
	void CreateVB(DWORD dwWidth, DWORD dwHeight);
	void CreateTex(TCHAR* text, int fontsize, DWORD colorABGR, TCHAR* szFontName);

	CFontTexture(CShader* pShader);
	~CFontTexture();

};


