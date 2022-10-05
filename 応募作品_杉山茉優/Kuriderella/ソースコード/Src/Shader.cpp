// ========================================================================================
//
// �V�F�[�_�[�̏���                                                ver 2.8        2020.1.24
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
//
//                                                                              Shader.cpp
// ========================================================================================

#include "Shader.h"

//------------------------------------------------------------------------
//
//	�V�F�[�_�[�̃R���X�g���N�^	
//
//  �����@CDirect3D* pD3D
//
//------------------------------------------------------------------------
CShader::CShader(CDirect3D* pD3D)
{
	ZeroMemory(this, sizeof(CShader));
	m_pD3D = pD3D;
}
//------------------------------------------------------------------------
//
//	�V�F�[�_�[�̃f�X�g���N�^	
//
//------------------------------------------------------------------------
CShader::~CShader()
{

	SAFE_RELEASE(m_pSprite2D_VertexLayout);
	SAFE_RELEASE(m_pSprite2D_VS);
	SAFE_RELEASE(m_pSprite2D_PS);

	SAFE_RELEASE(m_pConstantBufferSprite2D);

}

//------------------------------------------------------------------------
//
//	�e��V�F�[�_�[�̍쐬	
//
//  �E�V�F�[�_�[�ƃR���X�^���g�o�b�t�@���쐬����
//  �E�e�N�X�`���[�T���v���[�ƃu�����h�X�e�[�g���쐬����
//
//  �����@�Ȃ�
//
//	�߂�l HRESULT
//		S_OK	= ����
//		E_FAIL	= �ُ�
//
//------------------------------------------------------------------------
HRESULT CShader::InitShader()
{
	//  �X�v���C�g�p�̃V�F�[�_�[�쐬
	InitShaderSprite();

	//  �R���X�^���g�o�b�t�@�쐬
	InitShaderConstant();

	return S_OK;
}

//------------------------------------------------------------------------
//
//  �X�v���C�g�p�̃V�F�[�_�[�쐬
//
//  �����@�Ȃ�
//
//	�߂�l HRESULT
//		S_OK	= ����
//		E_FAIL	= �ُ�
//
//------------------------------------------------------------------------
HRESULT CShader::InitShaderSprite()
{

	// ���_�C���v�b�g���C�A�E�g���`	
	D3D11_INPUT_ELEMENT_DESC layout_sprite[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = sizeof(layout_sprite) / sizeof(layout_sprite[0]);

	// �o�[�e�b�N�X�V�F�[�_�E�s�N�Z���V�F�[�_�E���_�C���v�b�g���C�A�E�g�̍쐬
	MakeShader(_T("VS"), _T("Sprite2D_VS.cso"), (void**)&m_pSprite2D_VS, layout_sprite, numElements, &m_pSprite2D_VertexLayout);
	MakeShader(_T("PS"), _T("Sprite2D_PS.cso"), (void**)&m_pSprite2D_PS);

	return S_OK;
}

//------------------------------------------------------------------------
//
//  �V�F�[�_�[�̍쐬�֐�
//
//  ����	TCHAR ProfileName[]	�쐬����V�F�[�_�[���
//								(VS,PS,GS,HS,DS,CS)
//			TCHAR FileName[]	�g�k�r�k�t�@�C����
//			void** ppShader		�쐬����V�F�[�_�[(OUT)
//			D3D11_INPUT_ELEMENT_DESC Fluid_layout[]	���_���C�A�E�g��`(�ȗ���)
//			UINT numElements						���_���C�A�E�g�G�������g��(�ȗ���)
//			ID3D11InputLayout** ppInputLayout		�쐬���钸�_���C�A�E�g(OUT)(�ȗ���)
//
//	�߂�l HRESULT
//		S_OK	= ����
//		E_FAIL	= �ُ�
//
//------------------------------------------------------------------------
HRESULT CShader::MakeShader(TCHAR ProfileName[], TCHAR FileName[], void** ppShader, D3D11_INPUT_ELEMENT_DESC Fluid_layout[], UINT numElements, ID3D11InputLayout** ppInputLayout)
{
	// �R���p�C���ς݃V�F�[�_�̓ǂݍ��ݔz��
	BYTE* pCso = NULL;
	DWORD dwCsoSize = 0;

	// �R���p�C���ς݃V�F�[�_�̓ǂݍ��݂�����
	m_pD3D->ReadCso(FileName, &pCso, &dwCsoSize);

	// �V�F�[�_�[��ނ��Ƃ̍쐬����
	if (_tcscmp(ProfileName, _T("VS")) == 0)	// �o�[�e�b�N�X�V�F�[�_�[
	{
		if (FAILED(m_pD3D->m_pDevice->CreateVertexShader(pCso, dwCsoSize, NULL, (ID3D11VertexShader**)ppShader)))
		{
			SAFE_DELETE_ARRAY(pCso);
			MessageBox(0, _T("�o�[�e�b�N�X�V�F�[�_�[�쐬���s"), FileName, MB_OK);
			return E_FAIL;
		}
		if (ppInputLayout)	// ���_�C���v�b�g���C�A�E�g���쐬����Ƃ�
		{
			// ���_�C���v�b�g���C�A�E�g���쐬
			if (FAILED(m_pD3D->m_pDevice->CreateInputLayout(Fluid_layout, numElements, pCso, dwCsoSize, ppInputLayout)))
			{
				MessageBox(0, _T("�C���v�b�g ���C�A�E�g�쐬���s"), FileName, MB_OK);
				return FALSE;
			}
		}
	}
	else if (_tcscmp(ProfileName, _T("PS")) == 0)	// �s�N�Z���V�F�[�_�[
	{
		if (FAILED(m_pD3D->m_pDevice->CreatePixelShader(pCso, dwCsoSize, NULL, (ID3D11PixelShader**)ppShader)))
		{
			SAFE_DELETE_ARRAY(pCso);
			MessageBox(0, _T("�s�N�Z���V�F�[�_�[�쐬���s"), FileName, MB_OK);
			return E_FAIL;
		}
	}
	else if (_tcscmp(ProfileName, _T("GS")) == 0)	// �W�I���g���V�F�[�_�[
	{
		if (FAILED(m_pD3D->m_pDevice->CreateGeometryShader(pCso, dwCsoSize, NULL, (ID3D11GeometryShader**)ppShader)))
		{
			SAFE_DELETE_ARRAY(pCso);
			MessageBox(0, _T("�W�I���g���V�F�[�_�[�쐬���s"), FileName, MB_OK);
			return E_FAIL;
		}
	}
	else if (_tcscmp(ProfileName, _T("HS")) == 0)	// �n���V�F�[�_�[
	{
		if (FAILED(m_pD3D->m_pDevice->CreateHullShader(pCso, dwCsoSize, NULL, (ID3D11HullShader**)ppShader)))
		{
			SAFE_DELETE_ARRAY(pCso);
			MessageBox(0, _T("�n���V�F�[�_�[�쐬���s"), FileName, MB_OK);
			return E_FAIL;
		}
	}
	else if (_tcscmp(ProfileName, _T("DS")) == 0)	// �h���C���V�F�[�_�[
	{
		if (FAILED(m_pD3D->m_pDevice->CreateDomainShader(pCso, dwCsoSize, NULL, (ID3D11DomainShader**)ppShader)))
		{
			SAFE_DELETE_ARRAY(pCso);
			MessageBox(0, _T("�h���C���V�F�[�_�[�쐬���s"), FileName, MB_OK);
			return E_FAIL;
		}
	}
	else if (_tcscmp(ProfileName, _T("CS")) == 0)	// �R���s���[�g�V�F�[�_
	{
		if (FAILED(m_pD3D->m_pDevice->CreateComputeShader(pCso, dwCsoSize, NULL, (ID3D11ComputeShader**)ppShader)))
		{
			SAFE_DELETE_ARRAY(pCso);
			MessageBox(0, _T("�R���s���[�g�V�F�[�_�쐬���s"), FileName, MB_OK);
			return E_FAIL;
		}
	}
	else {
		SAFE_DELETE_ARRAY(pCso);
		MessageBox(0, _T("�V�F�[�_��ގw��G���["), ProfileName, MB_OK);
		return E_FAIL;
	}

	SAFE_DELETE_ARRAY(pCso);
	return S_OK;

}

//------------------------------------------------------------------------
//
//  �e��R���X�^���g�o�b�t�@�[�쐬
//
//  �����@�Ȃ�
//
//	�߂�l HRESULT
//		S_OK	= ����
//		E_FAIL	= �ُ�
//
//------------------------------------------------------------------------
HRESULT CShader::InitShaderConstant()
{
	// �X�v���C�g�p �R���X�^���g�o�b�t�@�[�쐬�@�����ł͕ϊ��s��n���p
	MakeConstantBuffer(sizeof(CONSTANT_BUFFER_SPRITE), &m_pConstantBufferSprite2D);

	return S_OK;
}

//------------------------------------------------------------------------
//
//  �R���X�^���g�o�b�t�@�[�̍쐬�֐�
//
//  ����	UINT	size						�쐬����R���X�^���g�o�b�t�@�[�̃T�C�Y
//			ID3D11Buffer**  pppConstantBuffer	�쐬����R���X�^���g�o�b�t�@�[(OUT)
//
//	�߂�l HRESULT
//		S_OK	= ����
//		E_FAIL	= �ُ�
//
//------------------------------------------------------------------------
HRESULT CShader::MakeConstantBuffer(UINT size, ID3D11Buffer**  ppConstantBuffer)
{
	D3D11_BUFFER_DESC cb = { NULL };

	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.ByteWidth = size;
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;
	cb.Usage = D3D11_USAGE_DYNAMIC;

	if (FAILED(m_pD3D->m_pDevice->CreateBuffer(&cb, NULL, ppConstantBuffer)))
	{
		MessageBox(0, _T("�R���X�^���g�o�b�t�@�[ �쐬���s"), NULL, MB_OK);
		return E_FAIL;
	}
	return S_OK;
}

