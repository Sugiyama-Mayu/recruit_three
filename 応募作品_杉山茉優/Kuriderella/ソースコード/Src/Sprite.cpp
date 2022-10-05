// ========================================================================================
//
// �X�v���C�g�̏���                                        ver ver 2.8        2020.2.15
//
//   �O�o�[�W�����̏����ɉ����ADrawLine ���̕`�揈���� DrawRect �l�p�̕`�揈�����������
//   Sprite.h Sprite.cpp Sprite2D.hlsli Direct3D.h ���ύX�ƂȂ��Ă���
//
// ========================================================================================

#include "Sprite.h"

//------------------------------------------------------------------------
//
//	�X�v���C�g�C���[�W�̃R���X�g���N�^	
//
//  �����@CShader* pShader
//
//------------------------------------------------------------------------
CSpriteImage::CSpriteImage(CShader* pShader)
{
	ZeroMemory(this, sizeof(CSpriteImage));
	m_pShader = pShader;
	m_pD3D = pShader->m_pD3D;
}
//------------------------------------------------------------------------
//
//	�X�v���C�g�C���[�W�̃R���X�g���N�^	
//
//	CShader* pShader
//  TCHAR*   TName  �X�v���C�g�t�@�C����
//
//------------------------------------------------------------------------
CSpriteImage::CSpriteImage(CShader* pShader, TCHAR* TName)
{
	ZeroMemory(this, sizeof(CSpriteImage));
	m_pShader = pShader;
	m_pD3D = pShader->m_pD3D;
	Load(TName);
}
//------------------------------------------------------------------------
//
//	�X�v���C�g�C���[�W�̃f�X�g���N�^	
//
//------------------------------------------------------------------------
CSpriteImage::~CSpriteImage()
{
	SAFE_RELEASE(m_pTexture);
}


//------------------------------------------------------------------------
//	�X�v���C�g�C���[�W�̓ǂݍ���	
//
//	�w�肵���X�v���C�g�t�@�C�����̃C���[�W��ǂݍ���
//
//  TCHAR*   TName  �X�v���C�g�t�@�C����
//
//	�߂�l HRESULT
//		S_OK	= ����
//		E_FAIL	= �t�@�C������������Ȃ�
//------------------------------------------------------------------------
HRESULT CSpriteImage::Load(TCHAR* TName)
{
	if (FAILED (m_pD3D->CreateShaderResourceViewFromFile(TName, &m_pTexture, m_dwImageWidth, m_dwImageHeight)))
	{
		MessageBox(0, _T("�X�v���C�g�@�e�N�X�`���[��ǂݍ��߂܂���"), TName, MB_OK);
		return E_FAIL;
	}
	return S_OK;
}

//------------------------------------------------------------------------
//
//	�X�v���C�g�̃R���X�g���N�^	
//
//  �����@CShader* pShader
//
//------------------------------------------------------------------------
CSprite::CSprite(CShader* pShader)
{
	ZeroMemory(this, sizeof(CSprite));
	m_pShader = pShader;
	m_pD3D = pShader->m_pD3D;
	m_vDiffuse = VECTOR4(1,1,1,1);    // -- 2020.1.24
	m_nBlend = 1;
}
//------------------------------------------------------------------------
//                                                         // -- 2017.10.9
//	�X�v���C�g�̃R���X�g���N�^	
//
//  ����
//  CSpriteImage* pImage      �X�v���C�g�C���[�W�|�C���^
//
//------------------------------------------------------------------------
CSprite::CSprite(CSpriteImage* pImage)
{
	ZeroMemory(this, sizeof(CSprite));
	m_pShader = pImage->m_pShader;
	m_pD3D = pImage->m_pD3D;
	m_vDiffuse = VECTOR4(1,1,1,1);    // -- 2020.1.24
	m_nBlend = 1;
	m_pImage = pImage;

}
//------------------------------------------------------------------------
//
//	�X�v���C�g�̃R���X�g���N�^	
//
//  CSpriteImage* pImage      �X�v���C�g�C���[�W�|�C���^
//  DWORD         srcX        �p�^�[���̍���@�w���W
//  DWORD         srcY        �p�^�[���̍���@�x���W
//  DWORD         srcwidth    �p�^�[���̕�
//  DWORD         srcheight   �p�^�[���̍���
//
//------------------------------------------------------------------------
CSprite::CSprite(CSpriteImage* pImage, DWORD srcX, DWORD srcY, DWORD srcwidth, DWORD srcheight)
{
	ZeroMemory(this, sizeof(CSprite));
	m_pShader = pImage->m_pShader;
	m_pD3D = pImage->m_pD3D;
	m_vDiffuse = VECTOR4(1,1,1,1);    // -- 2020.1.24
	m_nBlend = 1;
	SetSrc(pImage, srcX, srcY, srcwidth, srcheight, srcwidth, srcheight);
}
//------------------------------------------------------------------------
//
//	�X�v���C�g�̃R���X�g���N�^	
//
//  CSpriteImage* pImage      �X�v���C�g�C���[�W�|�C���^
//  DWORD         srcX        �p�^�[���̍���@�w���W
//  DWORD         srcY        �p�^�[���̍���@�x���W
//  DWORD         srcwidth    �p�^�[���̕�
//  DWORD         srcheight   �p�^�[���̍���
//  DWORD         destwidth   �\���̕�
//  DWORD         destheight  �\���̍���
//
//------------------------------------------------------------------------
CSprite::CSprite(CSpriteImage* pImage, DWORD srcX, DWORD srcY, DWORD srcwidth, DWORD srcheight, DWORD destwidth, DWORD destheight)
{
	ZeroMemory(this, sizeof(CSprite));
	m_pShader = pImage->m_pShader;
	m_pD3D = pImage->m_pD3D;
	m_vDiffuse = VECTOR4(1,1,1,1);    // -- 2020.1.24
	m_nBlend = 1;
	SetSrc(pImage, srcX, srcY, srcwidth, srcheight, destwidth, destheight);
}
//------------------------------------------------------------------------
//
//	�X�v���C�g�̃f�X�g���N�^	
//
//------------------------------------------------------------------------
CSprite::~CSprite()
{
	SAFE_RELEASE(m_pVertexBufferSprite);
	SAFE_RELEASE(m_pVertexBufferLine);
	SAFE_RELEASE(m_pVertexBufferRect);
}

//------------------------------------------------------------------------
//                                                         // -- 2017.10.9
//	�X�v���C�g�̃C���[�W��ݒ肷��	
//
//  CSpriteImage* pImage      �X�v���C�g�C���[�W�|�C���^
//
//------------------------------------------------------------------------
void   CSprite::SetImage(CSpriteImage* pImage)
{
	m_pImage = pImage;
}
//------------------------------------------------------------------------
//
//	�X�v���C�g�̃C���[�W��ʒu�A�傫���̏���ݒ肷��	
//
//  CSpriteImage* pImage      �X�v���C�g�C���[�W�|�C���^
//  DWORD         srcX        �p�^�[���̍���@�w���W
//  DWORD         srcY        �p�^�[���̍���@�x���W
//  DWORD         srcwidth    �p�^�[���̕�
//  DWORD         srcheight   �p�^�[���̍���
//
//	�߂�l HRESULT
//		S_OK	= ����
//		E_FAIL	= �ُ�
//
//------------------------------------------------------------------------
HRESULT CSprite::SetSrc(CSpriteImage* pImage, DWORD srcX, DWORD srcY, DWORD srcwidth, DWORD srcheight)
{
	m_pImage = pImage;
	return  SetSrc(srcX, srcY, srcwidth, srcheight, srcwidth, srcheight);
}
//------------------------------------------------------------------------
//
//	�X�v���C�g�̃C���[�W��ʒu�A�傫���̏���ݒ肷��	
//
//  CSpriteImage* pImage      �X�v���C�g�C���[�W�|�C���^
//  DWORD         srcX        �p�^�[���̍���@�w���W
//  DWORD         srcY        �p�^�[���̍���@�x���W
//  DWORD         srcwidth    �p�^�[���̕�
//  DWORD         srcheight   �p�^�[���̍���
//  DWORD         destwidth   �\���̕�
//  DWORD         destheight  �\���̍���
//
//	�߂�l HRESULT
//		S_OK	= ����
//		E_FAIL	= �ُ�
//
//------------------------------------------------------------------------
HRESULT CSprite::SetSrc(CSpriteImage* pImage, DWORD srcX, DWORD srcY, DWORD srcwidth, DWORD srcheight, DWORD destwidth, DWORD destheight)
{
	m_pImage   = pImage;
	return  SetSrc( srcX, srcY, srcwidth, srcheight, destwidth, destheight);
}
//------------------------------------------------------------------------
//
//	�X�v���C�g�̃C���[�W��ʒu�A�傫���̏���ݒ肷��	
//
//  DWORD         srcX        �p�^�[���̍���@�w���W
//  DWORD         srcY        �p�^�[���̍���@�x���W
//  DWORD         srcwidth    �p�^�[���̕�
//  DWORD         srcheight   �p�^�[���̍���
//
//	�߂�l HRESULT
//		S_OK	= ����
//		E_FAIL	= �ُ�
//
//------------------------------------------------------------------------
HRESULT CSprite::SetSrc(DWORD srcX, DWORD srcY, DWORD srcwidth, DWORD srcheight)
{
	return  SetSrc( srcX, srcY, srcwidth, srcheight, srcwidth, srcheight);
}
//------------------------------------------------------------------------
//
//	�X�v���C�g�̃C���[�W��ʒu�A�傫���̏���ݒ肷��	
//
//  DWORD         srcX        �p�^�[���̍���@�w���W
//  DWORD         srcY        �p�^�[���̍���@�x���W
//  DWORD         srcwidth    �p�^�[���̕�
//  DWORD         srcheight   �p�^�[���̍���
//  DWORD         destwidth   �\���̕�
//  DWORD         destheight  �\���̍���
//
//	�߂�l HRESULT
//		S_OK	= ����
//		E_FAIL	= �ُ�
//
//------------------------------------------------------------------------
HRESULT CSprite::SetSrc( DWORD srcX, DWORD srcY, DWORD srcwidth, DWORD srcheight, DWORD destwidth, DWORD destheight )
{
	// �X�v���C�g�p�̔|���S�����쐬���A�o�[�e�b�N�X�o�b�t�@���쐬����
	m_dwSrcX   = srcX;
	m_dwSrcY   = srcY;
	m_dwSrcWidth  = srcwidth;
	m_dwSrcHeight = srcheight;
	m_dwDestWidth  = destwidth;
	m_dwDestHeight = destheight;

	//�o�[�e�b�N�X�o�b�t�@�[�쐬
	//�C�����邱�ƁBz�l���P�ȏ�ɂ��Ȃ��B�N���b�v��Ԃ�z=1�͍ł������Ӗ�����B���������ĕ`�悳��Ȃ��B
	SpriteVertex vertices[]=
	{
		VECTOR3(               0,     (float)m_dwDestHeight, 0), VECTOR2((float)m_dwSrcX/m_pImage->m_dwImageWidth,                (float)(m_dwSrcY + m_dwSrcHeight)/m_pImage->m_dwImageHeight),    //���_1  ����
		VECTOR3(               0,                         0, 0), VECTOR2((float)m_dwSrcX/m_pImage->m_dwImageWidth,                (float)m_dwSrcY/m_pImage->m_dwImageHeight),                      //���_2�@����
		VECTOR3((float)m_dwDestWidth, (float)m_dwDestHeight, 0), VECTOR2((float)(m_dwSrcX+m_dwSrcWidth)/m_pImage->m_dwImageWidth, (float)(m_dwSrcY+m_dwSrcHeight)/m_pImage->m_dwImageHeight),      //���_3�@�E��
		VECTOR3((float)m_dwDestWidth,                     0, 0), VECTOR2((float)(m_dwSrcX+m_dwSrcWidth)/m_pImage->m_dwImageWidth, (float)m_dwSrcY/m_pImage->m_dwImageHeight),                      //���_4�@�E��
	};

	// �o�[�e�b�N�X�o�b�t�@�����łɍ쐬�ς݂��ǂ����`�F�b�N����
	if (m_pVertexBufferSprite == NULL)
	{
		// �V�K�쐬����
		D3D11_BUFFER_DESC bd = { 0 };
		//bd.Usage          = D3D11_USAGE_DEFAULT;
		bd.Usage            = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth        = sizeof(SpriteVertex) * 4;
		bd.BindFlags        = D3D11_BIND_VERTEX_BUFFER;
		//bd.CPUAccessFlags = 0;
		bd.CPUAccessFlags   = D3D11_CPU_ACCESS_WRITE;
		bd.MiscFlags        = 0;

		D3D11_SUBRESOURCE_DATA InitData = { 0 };
		InitData.pSysMem = vertices;
		if (FAILED(m_pD3D->m_pDevice->CreateBuffer(&bd, &InitData, &m_pVertexBufferSprite)))
		{
			MessageBox(0, _T("Sprite.cpp �o�[�e�b�N�X�o�b�t�@�[�쐬���s"), NULL, MB_OK);
			return E_FAIL;
		}
	} else {
		
		// ���łɍ쐬�ς݂̂��߁A�o�[�e�b�N�X�o�b�t�@�̏�������������
		D3D11_MAPPED_SUBRESOURCE msr = { 0 };
		if (SUCCEEDED(m_pD3D->m_pDeviceContext->Map(m_pVertexBufferSprite, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr)))
		{
			memcpy( msr.pData, vertices, sizeof(SpriteVertex) * 4 ); // 4���_���R�s�[
			m_pD3D->m_pDeviceContext->Unmap(m_pVertexBufferSprite, 0);
		}
	}

	return S_OK;
}

//------------------------------------------------------------------------
//
//	�X�v���C�g����ʂɃ����_�����O
//
//  CSpriteImage* pImage      �X�v���C�g�C���[�W�|�C���^
//  float         posX        �\���ʒu�̍���@�w���W
//  float         posY        �\���ʒu�̍���@�x���W
//  DWORD         srcX        �p�^�[���̍���@�w���W
//  DWORD         srcY        �p�^�[���̍���@�x���W
//  DWORD         srcwidth    �p�^�[���̕�
//  DWORD         srcheight   �p�^�[���̍���
//  float         fAlpha      �����x
//
//	�߂�l  �Ȃ�
//
//------------------------------------------------------------------------
void  CSprite::Draw(CSpriteImage* pImage, float posX, float posY, DWORD srcX, DWORD srcY, DWORD srcwidth, DWORD srcheight, float fAlpha)
{
	SetSrc(pImage, srcX, srcY, srcwidth, srcheight);
	m_ofX = 0;
	m_ofY = 0;
	m_vDiffuse.w = fAlpha;    // -- 2020.1.24
	Draw( posX, posY );
}
//------------------------------------------------------------------------
//
//	�X�v���C�g����ʂɃ����_�����O
//
//  CSpriteImage* pImage      �X�v���C�g�C���[�W�|�C���^
//  float         posX        �\���ʒu�̍���@�w���W
//  float         posY        �\���ʒu�̍���@�x���W
//  DWORD         srcX        �p�^�[���̍���@�w���W
//  DWORD         srcY        �p�^�[���̍���@�x���W
//  DWORD         srcwidth    �p�^�[���̕�
//  DWORD         srcheight   �p�^�[���̍���
//  DWORD         destwidth   �\���̕�
//  DWORD         destheight  �\���̍���
//  float         fAlpha      �����x
//
//	�߂�l  �Ȃ�
//
//------------------------------------------------------------------------
void  CSprite::Draw(CSpriteImage* pImage, float posX, float posY, DWORD srcX, DWORD srcY, DWORD srcwidth, DWORD srcheight, DWORD destwidth, DWORD destheight, float fAlpha)
{
	SetSrc(pImage, srcX, srcY, srcwidth,srcheight, destwidth, destheight);
	m_ofX = 0;
	m_ofY = 0;
	m_vDiffuse.w = fAlpha;    // -- 2020.1.24
	Draw(posX, posY);
}
//------------------------------------------------------------------------
//
//	�X�v���C�g����ʂɃ����_�����O
//
//  CSpriteImage* pImage      �X�v���C�g�C���[�W�|�C���^
//  MATRIX4X4    mWorld      �\���ʒu�̃��[���h�}�g���b�N�X
//  DWORD         srcX        �p�^�[���̍���@�w���W
//  DWORD         srcY        �p�^�[���̍���@�x���W
//  DWORD         srcwidth    �p�^�[���̕�
//  DWORD         srcheight   �p�^�[���̍���
//  float         fAlpha      �����x
//
//	�߂�l  �Ȃ�
//
//------------------------------------------------------------------------
void  CSprite::Draw(CSpriteImage* pImage, MATRIX4X4 mWorld, DWORD srcX, DWORD srcY, DWORD srcwidth, DWORD srcheight, float fAlpha)
{
	SetSrc(pImage, srcX, srcY, srcwidth, srcheight);
	m_ofX = 0;
	m_ofY = 0;
	m_vDiffuse.w = fAlpha;    // -- 2020.1.24
	Draw( mWorld );
}
//------------------------------------------------------------------------
//
//	�X�v���C�g����ʂɃ����_�����O
//
//  CSpriteImage* pImage      �X�v���C�g�C���[�W�|�C���^
//  MATRIX4X4    mWorld      �\���ʒu�̃��[���h�}�g���b�N�X
//  DWORD         srcX        �p�^�[���̍���@�w���W
//  DWORD         srcY        �p�^�[���̍���@�x���W
//  DWORD         srcwidth    �p�^�[���̕�
//  DWORD         srcheight   �p�^�[���̍���
//  DWORD         destwidth   �\���̕�
//  DWORD         destheight  �\���̍���
//  float         fAlpha      �����x
//
//	�߂�l  �Ȃ�
//
//------------------------------------------------------------------------
void  CSprite::Draw(CSpriteImage* pImage, MATRIX4X4 mWorld, DWORD srcX, DWORD srcY, DWORD srcwidth, DWORD srcheight, DWORD destwidth, DWORD destheight, float fAlpha)
{
	SetSrc(pImage, srcX, srcY, srcwidth, srcheight, destwidth, destheight);
	m_ofX = 0;
	m_ofY = 0;
	m_vDiffuse.w = fAlpha;    // -- 2020.1.24
	Draw( mWorld );
}
//------------------------------------------------------------------------
//
//	�X�v���C�g����ʂɃ����_�����O
//
//  float         posX     �\���ʒu�̍���@�w���W
//  float         posY     �\���ʒu�̍���@�x���W
//
//	�߂�l  �Ȃ�
//
//------------------------------------------------------------------------
void CSprite::Draw(float posX, float posY)
{
	MATRIX4X4 mWorld;

	mWorld = XMMatrixTranslation(posX, posY, 0.0f);
	Draw(mWorld);
}
//------------------------------------------------------------------------
//
//	�X�v���C�g����ʂɃ����_�����O�@�T�u�֐�
//
//  MATRIX4X4    mWorld   �\���ʒu�̃��[���h�}�g���b�N�X
//
//	�߂�l  �Ȃ�
//
//------------------------------------------------------------------------
void CSprite::Draw(MATRIX4X4 mWorld)
{

	//�o�[�e�b�N�X�o�b�t�@�[���Z�b�g
	UINT stride = sizeof( SpriteVertex );
	UINT offset = 0;
	m_pD3D->m_pDeviceContext->IASetVertexBuffers( 0, 1, &m_pVertexBufferSprite, &stride, &offset );

	//�V�F�[�_�[�̃R���X�^���g�o�b�t�@�[�Ɋe��f�[�^��n��
	D3D11_MAPPED_SUBRESOURCE pData = { 0 };
	CONSTANT_BUFFER_SPRITE   cb;
	if( SUCCEEDED( m_pD3D->m_pDeviceContext->Map( m_pShader->m_pConstantBufferSprite2D, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData ) ) )
	{

		//���[���h�s���n��
		cb.mW = XMMatrixTranspose( mWorld );

		//�r���[�|�[�g�T�C�Y��n���i�N���C�A���g�̈�̉��Əc�j
		cb.ViewPortWidth  = m_pD3D->m_dwWindowWidth;
		cb.ViewPortHeight = m_pD3D->m_dwWindowHeight;
		cb.vUVOffset.x    = (float)m_ofX / m_pImage->m_dwImageWidth;
		cb.vUVOffset.y    = (float)m_ofY / m_pImage->m_dwImageHeight;
		cb.vColor = m_vDiffuse;                                         // -- 2020.1.24
		cb.vMatInfo       = VECTOR4(1,0,0,0);  // �e�N�X�`���L��
		memcpy_s( pData.pData, pData.RowPitch, (void*)( &cb), sizeof( cb ) );
		m_pD3D->m_pDeviceContext->Unmap(m_pShader->m_pConstantBufferSprite2D, 0 );
	}

	//�e�N�X�`���[���V�F�[�_�[�ɓn��
	m_pD3D->m_pDeviceContext->PSSetShaderResources(0,1,&m_pImage->m_pTexture);

	// �u�����f�B���O��ݒ�    // -- 2020.2.15
	UINT mask = 0xffffffff;
	if (m_nBlend == 2)
	{
		// 2:���Z�����̃u�����f�B���O��ݒ�
		m_pD3D->m_pDeviceContext->OMSetBlendState(m_pD3D->m_pBlendStateAdd, NULL, mask);
	}

	//�v���~�e�B�u�������_�����O
	m_pD3D->m_pDeviceContext->Draw(4,0);

	// �u�����f�B���O�ݒ��߂�    // -- 2020.2.15
	if (m_nBlend == 2)
	{
		// ���ߐF�̃u�����f�B���O�ɖ߂�
		m_pD3D->m_pDeviceContext->OMSetBlendState(m_pD3D->m_pBlendStateTrapen, NULL, mask);
	}


}
//------------------------------------------------------------------------
//
//	���C������ʂɃ����_�����O�@�T�u�֐�
//
//  �i�Ȃ��A�F�ⓧ���x��m_vDiffuse���g�p���Ă��Ȃ��B�����ɂ�钼�ڎw��ł���j
//
//  float StartX     ���C���`��@�J�n�w���W
//  float StartY     ���C���`��@�J�n�x���W
//  float EndX       ���C���`��@�I���w���W
//  float EndY       ���C���`��@�I���x���W
//  DWORD Width      ���C���̑����i�P�ȏ�j
//  DWORD colorABGR  �����F�@colorABGR�́AABGR�̎w��B��F���F��(0x00ffffff)   ������RGB(1,1,1)
//  const float& fAlpha     �����x�i�ȗ��l��1.0f�j
//
//	�߂�l  �Ȃ�
//
//------------------------------------------------------------------------
void CSprite::DrawLine(float StartX, float StartY, float EndX, float EndY, DWORD Width, DWORD colorABGR, float fAlpha )
{

	// ������ʂ͈͓̔��ɓ����Ă��Ȃ�������`�悵�Ȃ�
	if ((StartX < 0 && EndX < 0) || (StartY < 0 && EndY < 0) ||
		(StartX > WINDOW_WIDTH  && EndX > WINDOW_WIDTH) || (StartY > WINDOW_HEIGHT && EndY > WINDOW_HEIGHT))
	{
		return;
	}

	// ���|���S���o�[�e�b�N�X�o�b�t�@�[�쐬
	SpriteVertex vertices[] =
	{
		{ VECTOR3(StartX, StartY, 0), VECTOR2(0,0) },    //���_1
		{ VECTOR3(EndX,     EndY, 0), VECTOR2(0,0) }     //���_2
	};

	// �o�[�e�b�N�X�o�b�t�@�����łɍ쐬�ς݂��ǂ����`�F�b�N����
	if (m_pVertexBufferLine == NULL)
	{
		// �V�K�쐬����
		D3D11_BUFFER_DESC bd = { 0 };
		//bd.Usage          = D3D11_USAGE_DEFAULT;
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(SpriteVertex)*2;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		//bd.CPUAccessFlags = 0;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		bd.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA InitData = { 0 };
		InitData.pSysMem = vertices;
		if (FAILED(m_pD3D->m_pDevice->CreateBuffer(&bd, &InitData, &m_pVertexBufferLine)))
		{
			MessageBox(0, _T("Sprite.cpp �o�[�e�b�N�X�o�b�t�@�[LINE �쐬���s"), NULL, MB_OK);
			return;
		}
	}
	else {

		// ���łɍ쐬�ς݂̂��߁A�o�[�e�b�N�X�o�b�t�@�̏�������������
		D3D11_MAPPED_SUBRESOURCE msr = { 0 };
		if (SUCCEEDED(m_pD3D->m_pDeviceContext->Map(m_pVertexBufferLine, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr)))
		{
			memcpy(msr.pData, vertices, sizeof(SpriteVertex) * 2); // 2���_���R�s�[
			m_pD3D->m_pDeviceContext->Unmap(m_pVertexBufferLine, 0);
		}
	}

	VECTOR4 color;
	color.x = ((colorABGR & 0x000000ff) >> 0)  / (float)255;  // R
	color.y = ((colorABGR & 0x0000ff00) >> 8)  / (float)255;  // G
	color.z = ((colorABGR & 0x00ff0000) >> 16) / (float)255;  // B
	color.w = fAlpha;                                         // A

	//�o�[�e�b�N�X�o�b�t�@�[���Z�b�g
	UINT stride = sizeof(SpriteVertex);
	UINT offset = 0;
	m_pD3D->m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBufferLine, &stride, &offset);

	//�v���~�e�B�u�E�g�|���W�[���Z�b�g
	m_pD3D->m_pDeviceContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_LINELIST );
	//�e�N�X�`���[�Ȃ����V�F�[�_�[�ɓn��
	ID3D11ShaderResourceView* Nothing[1] = { 0 };
	m_pD3D->m_pDeviceContext->PSSetShaderResources(0, 1, Nothing);

	//���[���h�s��
	MATRIX4X4 mWorld;

	// �����̖@�������߂�
	// (���̑����������Â炵�ĕ`�悷�邽�߂ɂ��̕`����������߂邽��)
	VECTOR2 vNrm, vDif = VECTOR2(EndX-StartX, EndY-StartY), vLen;
	vNrm.x = vDif.y;
	vNrm.y = vDif.x * -1;

	vLen = XMVector2Length(vNrm);
	vNrm.x = vNrm.x / vLen.x;
	vNrm.y = vNrm.y / vLen.x;

	if (Width < 1) Width = 1;

	// ���̕������`����J��Ԃ�
	for (DWORD i = 0; i < Width; i++)
	{
		// ���[���h�s��̏�����
		mWorld = XMMatrixIdentity();

		// ���̑������Â炵�ĕ\�����邽�߂̏���
		if (i % 2 == 0)
		{
			mWorld._41 = vNrm.x*0.8*i*0.5;
			mWorld._42 = vNrm.y*0.8*i*0.5;
		}
		else {
			mWorld._41 = -vNrm.x*0.8*i*0.5;
			mWorld._42 = -vNrm.y*0.8*i*0.5;
		}

		//�V�F�[�_�[�̃R���X�^���g�o�b�t�@�[�Ɋe��f�[�^��n��
		D3D11_MAPPED_SUBRESOURCE pData = { 0 };
		CONSTANT_BUFFER_SPRITE     cb;
		if (SUCCEEDED(m_pD3D->m_pDeviceContext->Map(m_pShader->m_pConstantBufferSprite2D, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
		{
			//���[���h�s���n��
			cb.mW = XMMatrixTranspose(mWorld);

			//�r���[�|�[�g�T�C�Y��n���i�N���C�A���g�̈�̉��Əc�j
			cb.ViewPortWidth = m_pD3D->m_dwWindowWidth;
			cb.ViewPortHeight = m_pD3D->m_dwWindowHeight;
			cb.vUVOffset.x = 0;
			cb.vUVOffset.y = 0;
			cb.vColor = color;
			cb.vMatInfo = VECTOR4(0, 0, 0, 0);  // �e�N�X�`���Ȃ�
			memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(cb));
			m_pD3D->m_pDeviceContext->Unmap(m_pShader->m_pConstantBufferSprite2D, 0);
		}
		//�v���~�e�B�u�������_�����O
		m_pD3D->m_pDeviceContext->Draw(2, 0);

	}

	//�v���~�e�B�u�E�g�|���W�[���Z�b�g
	m_pD3D->m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);


}

//------------------------------------------------------------------------
//                                                         // -- 2018.3.20
//	�l�p�`����ʂɃ����_�����O�@�T�u�֐�
//
//  �i�Ȃ��A�F�ⓧ���x��m_vDiffuse���g�p���Ă��Ȃ��B�����ɂ�钼�ڎw��ł���j
//
//  float posX       �l�p�`�`��@�J�n�w���W
//  float posY       �l�p�`�`��@�J�n�x���W
//  DWORD width      �l�p�`�̕�
//  DWORD height     �l�p�`�̍���
//  DWORD colorABGR  �`��F�@colorABGR�́AABGR�̎w��B��F���F��(0x00ffffff)   ������RGB(1,1,1)
//  float fAlpha     �����x�i�ȗ��l��1.0f�j
//
//	�߂�l  �Ȃ�
//
//------------------------------------------------------------------------
void  CSprite::DrawRect(float posX, float posY, DWORD width, DWORD height, DWORD colorABGR, float fAlpha)
{

	// �o�[�e�b�N�X�o�b�t�@�[�쐬
	SpriteVertex vertices[] =
	{
		{VECTOR3(0, (float)height, 0),             VECTOR2(0,0)},      //���_1  ����
		{VECTOR3(0, 0, 0),                         VECTOR2(0,0)},      //���_2�@����
		{VECTOR3((float)width,  (float)height, 0), VECTOR2(0,0)},      //���_3�@�E��
		{VECTOR3((float)width, 0, 0),              VECTOR2(0,0)},      //���_4�@�E��
	};

	// �o�[�e�b�N�X�o�b�t�@�����łɍ쐬�ς݂��ǂ����`�F�b�N����
	if (m_pVertexBufferRect == NULL)
	{
		// �V�K�쐬����
		D3D11_BUFFER_DESC bd = { 0 };
		//bd.Usage          = D3D11_USAGE_DEFAULT;
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(SpriteVertex) * 4; // 4���_��
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		//bd.CPUAccessFlags = 0;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		bd.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA InitData = { 0 };
		InitData.pSysMem = vertices;
		if (FAILED(m_pD3D->m_pDevice->CreateBuffer(&bd, &InitData, &m_pVertexBufferRect)))
		{
			MessageBox(0, _T("Sprite.cpp �o�[�e�b�N�X�o�b�t�@�[RECT �쐬���s"), NULL, MB_OK);
			return;
		}
	}
	else {

		// ���łɍ쐬�ς݂̂��߁A�o�[�e�b�N�X�o�b�t�@�̏�������������
		D3D11_MAPPED_SUBRESOURCE msr = { 0 };
		if (SUCCEEDED(m_pD3D->m_pDeviceContext->Map(m_pVertexBufferRect, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr)))
		{
			memcpy(msr.pData, vertices, sizeof(SpriteVertex) * 4); // 4���_���R�s�[
			m_pD3D->m_pDeviceContext->Unmap(m_pVertexBufferRect, 0);
		}
	}

	VECTOR4 color;
	color.x = ((colorABGR & 0x000000ff) >> 0) / (float)255;  // R
	color.y = ((colorABGR & 0x0000ff00) >> 8) / (float)255;  // G
	color.z = ((colorABGR & 0x00ff0000) >> 16) / (float)255;  // B
	color.w = fAlpha;                                         // A

	//�o�[�e�b�N�X�o�b�t�@�[���Z�b�g
	UINT stride = sizeof(SpriteVertex);
	UINT offset = 0;
	m_pD3D->m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBufferRect, &stride, &offset);

	//�v���~�e�B�u�E�g�|���W�[���Z�b�g
	m_pD3D->m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//�e�N�X�`���[�Ȃ����V�F�[�_�[�ɓn��
	ID3D11ShaderResourceView* Nothing[1] = { 0 };
	m_pD3D->m_pDeviceContext->PSSetShaderResources(0, 1, Nothing);

	//�V�F�[�_�[�̃R���X�^���g�o�b�t�@�[�Ɋe��f�[�^��n��
	D3D11_MAPPED_SUBRESOURCE pData = { 0 };
	CONSTANT_BUFFER_SPRITE     cb;
	if (SUCCEEDED(m_pD3D->m_pDeviceContext->Map(m_pShader->m_pConstantBufferSprite2D, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{
		//���[���h�s���n��
		cb.mW = XMMatrixTranspose(XMMatrixTranslation(posX, posY, 0.0f));

		//�r���[�|�[�g�T�C�Y��n���i�N���C�A���g�̈�̉��Əc�j
		cb.ViewPortWidth = m_pD3D->m_dwWindowWidth;
		cb.ViewPortHeight = m_pD3D->m_dwWindowHeight;
		cb.vUVOffset.x = 0;
		cb.vUVOffset.y = 0;
		cb.vColor = color;
		cb.vMatInfo = VECTOR4(0, 0, 0, 0);  // �e�N�X�`���Ȃ�
		memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(cb));
		m_pD3D->m_pDeviceContext->Unmap(m_pShader->m_pConstantBufferSprite2D, 0);
	}
	//�v���~�e�B�u�������_�����O
	m_pD3D->m_pDeviceContext->Draw(4, 0);

}

//------------------------------------------------------------------------
//
//	�`��O�ɃV�F�[�_�[�����Z�b�g
//
//  �����@�@�Ȃ�
//
//	�߂�l  �Ȃ�
//
//------------------------------------------------------------------------
void CSprite::SetShader()
{

	//�g�p����V�F�[�_�[�̃Z�b�g
	m_pD3D->m_pDeviceContext->VSSetShader(m_pShader->m_pSprite2D_VS, NULL, 0);
	m_pD3D->m_pDeviceContext->PSSetShader(m_pShader->m_pSprite2D_PS, NULL, 0);


	//���̃R���X�^���g�o�b�t�@�[���ǂ̃V�F�[�_�[�Ŏg����
	m_pD3D->m_pDeviceContext->VSSetConstantBuffers(0, 1, &m_pShader->m_pConstantBufferSprite2D);
	m_pD3D->m_pDeviceContext->PSSetConstantBuffers(0, 1, &m_pShader->m_pConstantBufferSprite2D);
	//���_�C���v�b�g���C�A�E�g���Z�b�g
	m_pD3D->m_pDeviceContext->IASetInputLayout(m_pShader->m_pSprite2D_VertexLayout);

	//�v���~�e�B�u�E�g�|���W�[���Z�b�g
	m_pD3D->m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �T���v���[���Z�b�g
	m_pD3D->m_pDeviceContext->PSSetSamplers(0, 1, &m_pD3D->m_pSampleLinear);

	// �u�����f�B���O��ݒ�            // -- 2020.2.15
	UINT mask = 0xffffffff;
	// ���ߐF�̃u�����f�B���O��ݒ�
	m_pD3D->m_pDeviceContext->OMSetBlendState(m_pD3D->m_pBlendStateTrapen, NULL, mask);

	// Z�o�b�t�@�𖳌���
	m_pD3D->SetZBuffer(FALSE);              // -- 2019.4.19

}
//------------------------------------------------------------------------
//
//	�`���ɃV�F�[�_�[�������Z�b�g
//
//  �����@�@�Ȃ�
//
//	�߂�l  �Ȃ�
//
//------------------------------------------------------------------------
void CSprite::ResetShader()
{

	// Z�o�b�t�@��L����
	m_pD3D->SetZBuffer(TRUE);              // -- 2019.4.19


	// ���ߐF�̃u�����f�B���O�ɖ߂�        // -- 2020.2.15
	UINT mask = 0xffffffff;
	m_pD3D->m_pDeviceContext->OMSetBlendState(m_pD3D->m_pBlendStateTrapen, NULL, mask);


}


// ========================================================================================
//
// �t�H���g�e�N�X�`���[�̏���
//
//
// ========================================================================================
//------------------------------------------------------------------------
//
//	�t�H���g�e�N�X�`���[�̃R���X�g���N�^	
//
//  �����@CShader* pShader
//
//------------------------------------------------------------------------
CFontTexture::CFontTexture(CShader* pShader)
{
	ZeroMemory(this, sizeof(CFontTexture));
	m_pShader = pShader;
	m_pD3D = pShader->m_pD3D;
	m_Idx = 0;
	for (DWORD i = 0; i < TEXT_DATA_MAX; i++)
	{
		m_TextData[i].m_fAlpha = 1.0f;
	}

	/*
	// �����Œǉ������t�H���g���ꎞ�I�Ɏg����悤�ɂ���
	// �v���O�������I������ƃt�H���g�͍폜�����
	DESIGNVECTOR design;
	if (AddFontResourceEx(
	TEXT("Fonts/�ǉ��t�H���g��.ttf"),
	FR_PRIVATE,
	&design) == NULL)
	{
	MessageBox(0, _T("Sprite.cpp �t�H���g�̒ǉ��Ɏ��s���܂���"), _T(""), MB_OK);
	}
	*/

}
//------------------------------------------------------------------------
//
//	�t�H���g�e�N�X�`���[�̃f�X�g���N�^	
//
//------------------------------------------------------------------------
CFontTexture::~CFontTexture()
{

	/*
	// �ǉ������t�H���g���������
	DESIGNVECTOR design;
	if (RemoveFontResourceEx(
	TEXT("Fonts/�ǉ��t�H���g��.ttf"),
	FR_PRIVATE,
	&design) == NULL)
	{
	MessageBox(0, _T("Sprite.cpp �t�H���g�̉���Ɏ��s���܂���"), _T(""), MB_OK);
	}
	*/

	for (DWORD i = 0; i < TEXT_DATA_MAX; i++)
	{
		SAFE_DELETE_ARRAY(m_TextData[i].m_szText);
		SAFE_RELEASE(m_TextData[i].m_pResourceView);
		SAFE_RELEASE(m_TextData[i].m_pVertexBufferFont);
	}
}
//------------------------------------------------------------------------
// �e�L�X�g���̃��t���b�V��
// 
// �@�@�\������e�L�X�g�̏��́A��s�Â�TextData�֕ۑ������
// �@�@���̃��t���b�V���́A���C�����[�v�̐擪�ōs���K�v������
//
//  �����@�@�Ȃ�
//
//	�߂�l  �Ȃ�
//
//------------------------------------------------------------------------
void CFontTexture::Refresh()
{
	m_Idx = 0;
}
//------------------------------------------------------------------------
//
//	�e�L�X�g�\���p�̃o�[�e�b�N�X�o�b�t�@�[�쐬�B
//	�P�s���̑傫�����m�ۂ���
//
//  DWORD dwWidth    �\�����i�P�s���̑傫���j
//  DWORD dwHeight   �\�������i�P�����̍����j
//
//	�߂�l  �Ȃ�
//
//------------------------------------------------------------------------
void CFontTexture::CreateVB(DWORD dwWidth, DWORD dwHeight)
{
 
// �o�[�e�b�N�X�o�b�t�@�[�쐬���ɋC�����邱�ƁB
// z�l���P�ȏ�ɂ��Ȃ����ƁB�N���b�v��Ԃ�z=1�͍ł������Ӗ�����B���������ĕ`�悳��Ȃ��B
	SpriteVertex vertices[] =
	{
		VECTOR3(             0, (float)dwHeight, 0), VECTOR2(0,  1),      //���_1  ����
		VECTOR3(             0,               0, 0), VECTOR2(0,  0),      //���_2�@����
		VECTOR3((float)dwWidth, (float)dwHeight, 0), VECTOR2(1,  1),      //���_3�@�E��
		VECTOR3((float)dwWidth,               0, 0), VECTOR2(1,  0)       //���_4�@�E��
	};

	// �o�[�e�b�N�X�o�b�t�@�����łɍ쐬�ς݂��ǂ����`�F�b�N����
	if (m_TextData[m_Idx].m_pVertexBufferFont == NULL)
	{
		// �V�K�쐬����
		D3D11_BUFFER_DESC bd = { 0 };
		//bd.Usage          = D3D11_USAGE_DEFAULT;
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(SpriteVertex) * 4;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		//bd.CPUAccessFlags = 0;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		bd.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA InitData = { 0 };
		InitData.pSysMem = vertices;
		if (FAILED(m_pD3D->m_pDevice->CreateBuffer(&bd, &InitData, &m_TextData[m_Idx].m_pVertexBufferFont)))
		{
			MessageBox(0, _T("Sprite.cpp �o�[�e�b�N�X�o�b�t�@�[�쐬���s"), NULL, MB_OK);
			return;
		}
	}else {

		// ���łɍ쐬�ς݂̂��߁A�o�[�e�b�N�X�o�b�t�@�̏�������������
		D3D11_MAPPED_SUBRESOURCE msr = { 0 };
		if (SUCCEEDED(m_pD3D->m_pDeviceContext->Map(m_TextData[m_Idx].m_pVertexBufferFont, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr)))
		{
			memcpy( msr.pData, vertices, sizeof(SpriteVertex) * 4 ); // 4���_���R�s�[
			m_pD3D->m_pDeviceContext->Unmap(m_TextData[m_Idx].m_pVertexBufferFont, 0);
		}
	}

}

//------------------------------------------------------------------------
//
//	�e�L�X�g�̕`��
//
//	�E���W�w��̏������̏ꍇ
//
//  float posX         �\���ʒu�@����@�w���W
//  float posY         �\���ʒu�@����@�x���W
//  TCHAR* szText       �\������e�L�X�g
//  int fontsize       �t�H���g�T�C�Y
//  DWORD colorABGR    �����F�@colorABGR�́AABGR�̎w��B��F���F��(0x00ffffff)
//  float fAlpha       �����x�i�ȗ��j
//  TCHAR* szFontName   �t�H���g���i�ȗ��j
//
//	�߂�l  �Ȃ�
//
//------------------------------------------------------------------------ 
void CFontTexture::Draw(float posX, float posY, TCHAR* szText, int fontsize, DWORD colorABGR, float fAlpha, TCHAR* szFontName)
{
	MATRIX4X4 mWorld;
	mWorld = XMMatrixTranslation(posX, posY, 0.0f);

	Draw( mWorld, szText, fontsize, colorABGR, fAlpha, szFontName);
}

//------------------------------------------------------------------------
//
//	�e�L�X�g�̕`��
//
//	�E���[���h�}�g���b�N�X�̏������̏ꍇ
//
//  MATRIX4X4 mWorld  �\���ʒu�@����@���[���h�}�g���b�N�X
//  TCHAR* szText       �\������e�L�X�g
//  int fontsize       �t�H���g�T�C�Y
//  DWORD colorABGR    �����F�@colorABGR�́AABGR�̎w��B��F���F��(0x00ffffff)
//  float fAlpha       �����x�i�ȗ��j
//  TCHAR* szFontName   �t�H���g���i�ȗ��j
//
//	�߂�l  �Ȃ�
//
//------------------------------------------------------------------------ 
void CFontTexture::Draw(MATRIX4X4 mWorld, TCHAR* szText, int fontsize, DWORD colorABGR, float fAlpha, TCHAR* szFontName)
{
	// �����񂪂Ȃ��Ƃ��͕`�悵�Ȃ�
	if (szText[0] == _T('\0')) return;         // -- 2017.11.22

	//
	// �O��܂ł́u�������F�A�T�C�Y�v���P��ʕ��E��������m_TextData�z��ɓ����Ă���̂�
	// �쐬�f�[�^������Ɠ������ǂ����`�F�b�N����
	//
	// �@�@����̏ꍇ�́A���łɍ쐬�ς݂̃t�H���g�e�N�X�`���[���g�p����
	// �A�@�����񂪈قȂ�ꍇ�̂݁A�t�H���g�e�N�X�`���[�̐������s��
	// �@�@�i�t�H���g�e�N�X�`���[�̐��������͔��ɏd�������Ȃ̂Łj

	if (m_TextData[m_Idx].m_szText == NULL || _tcscmp(m_TextData[m_Idx].m_szText, szText) != 0 ||
		m_TextData[m_Idx].m_iFontsize != fontsize || m_TextData[m_Idx].m_dwColor != colorABGR || m_TextData[m_Idx].m_fAlpha != fAlpha)  // �쐬�ς݂̕�����Ɠ��ꂩ�H
	{
		// �����񓙂ɕύX�̂������Ƃ�
		SAFE_DELETE_ARRAY(m_TextData[m_Idx].m_szText);
		m_TextData[m_Idx].m_szText = new TCHAR[_tcslen(szText)+1];  // TCHAR�́A�P�������Q�o�C�g  // -- 2018.12.28
		_tcscpy_s(m_TextData[m_Idx].m_szText, _tcslen(szText)+1, szText);    // ������̕ۑ�                           // -- 2018.12.28
		m_TextData[m_Idx].m_iFontsize = fontsize;		// �t�H���g�T�C�Y��ۑ�
		m_TextData[m_Idx].m_dwColor = colorABGR;		// �F��ۑ�
		m_TextData[m_Idx].m_fAlpha  = fAlpha;		    // �����x��ۑ�

		// �t�H���g�e�N�X�`���[�̍쐬
		CreateTex(szText, fontsize, colorABGR, szFontName);
	}

	// �o���オ�����e�N�X�`�����g���ĕ`����s��

	//�o�[�e�b�N�X�o�b�t�@�[���Z�b�g
	UINT stride = sizeof(SpriteVertex);
	UINT offset = 0;
	m_pD3D->m_pDeviceContext->IASetVertexBuffers(0, 1, &m_TextData[m_Idx].m_pVertexBufferFont, &stride, &offset);

	//�V�F�[�_�[�̃R���X�^���g�o�b�t�@�[�Ɋe��f�[�^��n��
	D3D11_MAPPED_SUBRESOURCE pData = { 0 };
	CONSTANT_BUFFER_SPRITE     cb;
	if (SUCCEEDED(m_pD3D->m_pDeviceContext->Map(m_pShader->m_pConstantBufferSprite2D, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{

		//���[���h�s���n��
		cb.mW = XMMatrixTranspose(mWorld);

		//�r���[�|�[�g�T�C�Y��n���i�N���C�A���g�̈�̉��Əc�j
		cb.ViewPortWidth = m_pD3D->m_dwWindowWidth;
		cb.ViewPortHeight = m_pD3D->m_dwWindowHeight;
		cb.vUVOffset.x = 0;
		cb.vUVOffset.y = 0;
		cb.vColor = VECTOR4(1, 1, 1, 1);                    // -- 2020.1.24
		cb.vColor.w = m_TextData[m_Idx].m_fAlpha;
		cb.vMatInfo    = VECTOR4(1, 0, 0, 0);  // �e�N�X�`���L��
		memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(cb));
		m_pD3D->m_pDeviceContext->Unmap(m_pShader->m_pConstantBufferSprite2D, 0);
	}

	//�e�N�X�`���[���V�F�[�_�[�ɓn��
	m_pD3D->m_pDeviceContext->PSSetShaderResources(0, 1, &m_TextData[m_Idx].m_pResourceView);

	//�v���~�e�B�u�������_�����O
	m_pD3D->m_pDeviceContext->Draw(4, 0);


	// �ۑ�����TextData�z��̓Y�����P���₷�B
	m_Idx++;
	if (m_Idx >= TEXT_DATA_MAX)
	{
		MessageBox(0, _T("Sprite.cpp �쐬����t�H���g�e�N�X�`���̍ő吔�𒴂��܂����B\nReflesh()�������Ă��܂����B\n�܂���TEXT_DATA_MAX�𑝂₵�Ă��������B"), _T(""), MB_OK);
		m_Idx--;
	}
}

//------------------------------------------------------------------------
//
//	�`��O�ɃV�F�[�_�[�����Z�b�g
//
//  �����@�@�Ȃ�
//
//	�߂�l  �Ȃ�
//
//------------------------------------------------------------------------
void CFontTexture::SetShader()
{

	//�g�p����V�F�[�_�[�̃Z�b�g
	m_pD3D->m_pDeviceContext->VSSetShader(m_pShader->m_pSprite2D_VS, NULL, 0);
	m_pD3D->m_pDeviceContext->PSSetShader(m_pShader->m_pSprite2D_PS, NULL, 0);


	//���̃R���X�^���g�o�b�t�@�[���ǂ̃V�F�[�_�[�Ŏg����
	m_pD3D->m_pDeviceContext->VSSetConstantBuffers(0, 1, &m_pShader->m_pConstantBufferSprite2D);
	m_pD3D->m_pDeviceContext->PSSetConstantBuffers(0, 1, &m_pShader->m_pConstantBufferSprite2D);
	//���_�C���v�b�g���C�A�E�g���Z�b�g
	m_pD3D->m_pDeviceContext->IASetInputLayout(m_pShader->m_pSprite2D_VertexLayout);

	//�v���~�e�B�u�E�g�|���W�[���Z�b�g
	m_pD3D->m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �T���v���[���Z�b�g
	m_pD3D->m_pDeviceContext->PSSetSamplers(0, 1, &m_pD3D->m_pSampleLinear);

	// ���ߐF�̃u�����f�B���O��ݒ�
	UINT mask = 0xffffffff;
	m_pD3D->m_pDeviceContext->OMSetBlendState(m_pD3D->m_pBlendStateTrapen, NULL, mask);

	// Z�o�b�t�@�𖳌���
	m_pD3D->SetZBuffer(FALSE);              // -- 2019.4.19

}
//------------------------------------------------------------------------
//
//	�`���ɃV�F�[�_�[�������Z�b�g
//
//  �����@�@�Ȃ�
//
//	�߂�l  �Ȃ�
//
//------------------------------------------------------------------------
void CFontTexture::ResetShader()
{

	// Z�o�b�t�@��L����
	m_pD3D->SetZBuffer(TRUE);              // -- 2019.4.19


	// ���ߐF�̃u�����f�B���O�ɖ߂�
	UINT mask = 0xffffffff;
	m_pD3D->m_pDeviceContext->OMSetBlendState(m_pD3D->m_pBlendStateTrapen, NULL, mask);


}


//------------------------------------------------------------------------
//
//	�t�H���g�e�N�X�`���[�̍쐬
//
//	�EGDI����t�H���g�̃O���t�B�b�N�X�𓾂āA�e�N�X�`���[���쐬����
//	�@�쐬�����e�N�X�`���[�́Am_TextData[m_Idx]�z��Ɋi�[����
//
//  TCHAR* text        �\������e�L�X�g
//  int fontsize       �t�H���g�T�C�Y
//  DWORD colorABGR    �����F�@colorABGR�́AABGR�̎w��B��F���F��(0x00ffffff)
//  TCHAR* fontname    �t�H���g���iNULL�ł��j
//
//	�߂�l  �Ȃ�
//
//------------------------------------------------------------------------ 
void CFontTexture::CreateTex(TCHAR* text, int fontsize, DWORD colorABGR, TCHAR* fontname)
{

	// �t�H���g�̐���
	LOGFONT lf = {
		fontsize,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		SHIFTJIS_CHARSET,
		OUT_TT_ONLY_PRECIS,
		CLIP_DEFAULT_PRECIS,
		PROOF_QUALITY,
		FIXED_PITCH | FF_MODERN,
		//TEXT("�c�e������")
		TEXT("�l�r �o�S�V�b�N")
		//TEXT("�l�r �S�V�b�N")
		//TEXT("HGP�n�p�p�߯�ߑ�")
		//TEXT("HGP�n�p�p�޼��UB")
	};
	if(fontname != NULL) _tcscpy_s(lf.lfFaceName, sizeof(lf.lfFaceName) / sizeof(TCHAR), fontname); // �t�H���g����ݒ�

	HFONT hFont = CreateFontIndirect(&lf);
	if (!(hFont))
	{
		MessageBox(0, _T("Sprite.cpp �e�N�X�`���p�̃t�H���g���쐬�ł��܂���"), _T(""), MB_OK);
	}

	// ������O���t�B�b�N�̐���

	DWORD     dwTextlen    = _tcslen(text);    // �������i�o�C�g���ł͂Ȃ��j  // -- 2018.12.28
	DWORD     dwTextHeight = 0;
	DWORD     dwTextWidth  = 0;
	DWORD     dwAllWidth   = 0;
	FontData* pFontData    = new FontData[dwTextlen];

	// �f�o�C�X�R���e�L�X�g�擾
	// �f�o�C�X�Ƀt�H���g���������Ȃ���GetGlyphOutline�֐��̓G���[�ƂȂ�
	HDC   hdc     = GetDC(NULL);
	HFONT oldFont = (HFONT)SelectObject(hdc, hFont);


	for (DWORD i = 0; i < dwTextlen; i++)
	{
		// �����R�[�h�擾
		UINT code = 0;

#if _UNICODE
		// unicode�̏ꍇ�A�����R�[�h�͒P���Ƀ��C�h������UINT�ϊ�
		code = (UINT)*(text + i);
#else
		// �}���`�o�C�g�����̏ꍇ�A
		// 1�o�C�g�����̃R�[�h�̏ꍇ��1�o�C�g�ڂ�UINT�ϊ��A
		// 2�o�C�g�����̃R�[�h�̏ꍇ��[�擱�R�[�h]*256 + [�����R�[�h]
		BYTE *c = (BYTE*)(text + i);
		if (IsDBCSLeadByte(*c))    // 2�o�C�g�����̐擱�R�[�h���ǂ���
		{
			code = (BYTE)c[0] << 8 | (BYTE)c[1];
			i++;
		}
		else {
			code = c[0];
		}
#endif

		// �t�H���g�r�b�g�}�b�v�擾
		GetTextMetrics(hdc, &(pFontData + i)->TM);
		CONST MAT2 Mat = { { 0,1 },{ 0,0 },{ 0,0 },{ 0,1 } };
		DWORD size = GetGlyphOutline(hdc, code, GGO_GRAY4_BITMAP, &(pFontData + i)->GM, 0, NULL, &Mat);  // �o�b�t�@�T�C�Y�����Ԃ��Ă��炤
		if (size == 0) // �t�H���g�f�[�^���邩  2017.4.15
		{
			(pFontData + i)->ptr = NULL; // �t�H���g�f�[�^�������Ƃ�  2017.4.15
		}
		else {
			(pFontData + i)->ptr = new BYTE[size];
			GetGlyphOutline(hdc, code, GGO_GRAY4_BITMAP, &(pFontData + i)->GM, size, (pFontData + i)->ptr, &Mat);
		}
		if (dwTextWidth < (pFontData + i)->GM.gmCellIncX) dwTextWidth = (pFontData + i)->GM.gmCellIncX;  // �P�����̕�
		if (dwTextHeight < (pFontData + i)->TM.tmHeight) dwTextHeight = (pFontData + i)->TM.tmHeight;    // �P�����̍���
		dwAllWidth += (pFontData + i)->GM.gmCellIncX;				// ������S�̂̒����i�h�b�g���j
	}

	// �f�o�C�X�R���e�L�X�g�ƃt�H���g�n���h���̊J��
	SelectObject(hdc, oldFont);
	DeleteObject(hFont);
	ReleaseDC(NULL, hdc);

	// ----------------------------------------------------
    // ������t�H���g�r�b�g�}�b�v�̑傫���Ńo�[�e�b�N�X�o�b�t�@�[�쐬
	CreateVB(dwAllWidth, dwTextHeight);

	// ----------------------------------------------------
	// �������݉\�e�N�X�`���쐬
	// CPU�ŏ������݂��ł���e�N�X�`�����쐬

	ID3D11Texture2D* pTexture2D;    // 2�c�e�N�X�`��

	D3D11_TEXTURE2D_DESC desc;
	memset(&desc, 0, sizeof(desc));
	desc.Width = dwAllWidth;		// ������P�s���̑傫��
	desc.Height = dwTextHeight;		// �����̍����ő�l
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;   // RGBA(255,255,255,255)�^�C�v
	desc.SampleDesc.Count = 1;
	desc.Usage = D3D11_USAGE_DYNAMIC;          // ���I�i�������݂��邽�߂̕K�{�����j
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;   // �V�F�[�_���\�[�X�Ƃ��Ďg��
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;   // CPU����A�N�Z�X���ď�������OK

	if (FAILED(m_pD3D->m_pDevice->CreateTexture2D(&desc, 0, &pTexture2D)))
	{
		MessageBox(0, _T("Sprite.cpp �e�N�X�`���p�̃t�H���g���쐬�ł��܂���"), _T(""), MB_OK);
	}


	D3D11_MAPPED_SUBRESOURCE hMappedResource = { 0 };

	if (FAILED(m_pD3D->m_pDeviceContext->Map(
		pTexture2D,
		0,
		D3D11_MAP_WRITE_DISCARD,
		0,
		&hMappedResource)))
	{
		MessageBox(0, _T("Sprite.cpp �e�N�X�`���}�b�v  �t�H���g  ���s"), _T(""), MB_OK);
	}


	// �쐬�����e�N�X�`���i�r���[�j�Ƀt�H���g������������
	BYTE* pBits = (BYTE*)hMappedResource.pData;
	ZeroMemory(pBits, hMappedResource.RowPitch * dwTextHeight);

	DWORD dwAllWidthWk = 0;
	for (DWORD i = 0; i < dwTextlen; i++)
	{

		// �t�H���g���̏�������
		// iOfs_x, iOfs_y : �����o���ʒu(����)
		// iBmp_w, iBmp_h : �t�H���g�r�b�g�}�b�v�̕���
		// Level : ���l�̒i�K (GGO_GRAY4_BITMAP�Ȃ̂�17�i�K)
		int iOfs_x = (pFontData + i)->GM.gmptGlyphOrigin.x;
		int iOfs_y = (pFontData + i)->TM.tmAscent - (pFontData + i)->GM.gmptGlyphOrigin.y;
		int iBmp_w = (pFontData + i)->GM.gmBlackBoxX + (4 - ((pFontData + i)->GM.gmBlackBoxX % 4)) % 4;
		int iBmp_h = (pFontData + i)->GM.gmBlackBoxY;
		int Level = 17;
		int x, y;
		DWORD Alpha, Color;

		for (y = iOfs_y; y < iOfs_y + iBmp_h; y++)
		{
			for (x = iOfs_x; x < iOfs_x + iBmp_w; x++)
			{
				if ((pFontData + i)->ptr == NULL) // �t�H���g�f�[�^�������Ƃ�  2017.4.15
				{
					Alpha = 0; // �����F�Ƃ���
				}
				else {
					Alpha = (255 * (pFontData + i)->ptr[x - iOfs_x + iBmp_w * (y - iOfs_y)]) / (Level - 1);
				}
				Color = colorABGR | (Alpha << 24);

				memcpy((BYTE*)pBits + hMappedResource.RowPitch * y + 4 * (x + dwAllWidthWk), &Color, sizeof(DWORD));
			}
		}
		dwAllWidthWk += (pFontData + i)->GM.gmCellIncX;	// �P�������i�߂�
	}

	m_pD3D->m_pDeviceContext->Unmap(pTexture2D, 0);


	// �e�N�X�`�������擾����
	D3D11_TEXTURE2D_DESC texDesc;
	pTexture2D->GetDesc(&texDesc);

	// ShaderResourceView�̏����쐬����
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(srvDesc));
	srvDesc.Format = texDesc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = texDesc.MipLevels;

	SAFE_RELEASE(m_TextData[m_Idx].m_pResourceView);	// �Q��ڈȍ~�̍쐬�ɑΉ�

	// �V�F�[�_�[���\�[�X�r���[�̍쐬
	if (FAILED(m_pD3D->m_pDevice->CreateShaderResourceView(pTexture2D, &srvDesc, &m_TextData[m_Idx].m_pResourceView)))
	{
		MessageBox(0, _T("Sprite.cpp �t�H���g�p�@ShaderResourceView�쐬�Ɏ��s���܂���"), NULL, MB_OK);
	}

	// �쐬�����ꎞ���\�[�X�̉��
	SAFE_RELEASE(pTexture2D);

	for (DWORD i = 0; i < dwTextlen; i++)
	{
		SAFE_DELETE_ARRAY((pFontData + i)->ptr);
	}
	SAFE_DELETE_ARRAY(pFontData);

}