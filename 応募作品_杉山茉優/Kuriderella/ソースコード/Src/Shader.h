// ========================================================================================
//
// �V�F�[�_�[�̏���                                               ver 2.8        2020.1.24
//
//   �V�F�[�_�[�O�����̓ǂݍ��݂ƃV�F�[�_�[�̍쐬
//   �C���v�b�g���C�A�E�g�̍쐬
//   �R���X�^���g�o�b�t�@�̍쐬
//
//
//    �o�^����Ă���V�F�[�_�[
//
//		�E�X�v���C�g�p�̃V�F�[�_�[�@InitShaderSprite()
//
//                                                                              Shader.h
// ========================================================================================
#pragma once

//�w�b�_�[�t�@�C���̃C���N���[�h
#include <stdio.h>
#include <windows.h>

#include "Main.h"
#include "Direct3D.h"

//�V�F�[�_�[�̃o�b�t�@�\���̒�`

//�@�X�v���C�g�V�F�[�_�[�p�̃R���X�^���g�o�b�t�@�[�̃A�v�����\���� 
struct CONSTANT_BUFFER_SPRITE
{
	MATRIX4X4   mW;
	float       ViewPortWidth;
	float       ViewPortHeight;
	VECTOR2     vUVOffset;
	VECTOR4     vColor;      // �J���[���B�������̊������w�肷��
	VECTOR4     vMatInfo;    // �}�e���A���֘A���@x:�e�N�X�`���L�薳���BDrawRect()�ADrawLine()�Ŏg�p�B
	CONSTANT_BUFFER_SPRITE()
	{
		ZeroMemory(this, sizeof(CONSTANT_BUFFER_SPRITE));
	}
};


//
// CShader�N���X
//
class CShader
{
public:
	// Direct3D11
	CDirect3D*              m_pD3D;

	// �V�F�[�_�[
	ID3D11InputLayout*      m_pSprite2D_VertexLayout;
	ID3D11VertexShader*     m_pSprite2D_VS;
	ID3D11PixelShader*      m_pSprite2D_PS;

	// �R���X�^���g�o�b�t�@
	ID3D11Buffer*			m_pConstantBufferSprite2D;


public:
	HRESULT InitShader();
	HRESULT InitShaderSprite();
	HRESULT InitShaderConstant();

	HRESULT MakeShader(TCHAR ProfileName[], TCHAR FileName[], void** ppShader, D3D11_INPUT_ELEMENT_DESC Fluid_layout[] = NULL, UINT numElements = 0, ID3D11InputLayout** ppInputLayout = NULL);
	HRESULT MakeConstantBuffer(UINT size, ID3D11Buffer**  ppConstantBuffer);

	CShader(CDirect3D* pD3D);
	~CShader();

};
