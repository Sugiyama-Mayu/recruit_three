//=============================================================================
//		�R�c�Q�[���v���O����
//		�b�R�c�`�����P�P�Q�@�@�@�@�@�@                 ver 3.0        2021.1.11
//
//		�G�t�F�N�g�̏���
//										2021.1.11					Effect.cpp
//=============================================================================

#include "Effect.h"


// ========================================================================================
//
//	�G�t�F�N�g�@���C���v���V�[�W���N���X
//
// ========================================================================================
//------------------------------------------------------------------------
//
//	�G�t�F�N�g�@���C���v���V�[�W���N���X�̃R���X�g���N�^	
//
//------------------------------------------------------------------------
CEffectProc::CEffectProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	m_pParticleProc = new CParticleProc(pGMain);     // �p�[�e�B�N���v���V�[�W���̐���
	m_pProcArray.push_back(m_pParticleProc);   // �v���V�[�W�����v���V�[�W���z��ɓo�^����
	
	m_pBillProc     = new CBillboardProc(pGMain);     // �r���{�[�h�v���V�[�W���̐���(���H�̃L���L��)
	m_pProcArray.push_back(m_pBillProc);        // �v���V�[�W�����v���V�[�W���z��ɓo�^����

	m_pBillFireProc     = new CBillFireProc(pGMain);     // �r���{�[�h�����₫�v���V�[�W���̐���
	m_pProcArray.push_back(m_pBillFireProc);        // �v���V�[�W�����v���V�[�W���z��ɓo�^����
	
	m_pBillStarProc = new CBillboardBornStarProc(pGMain);     // �r���{�[�h�v���V�[�W���̐���(�������G�t�F�N�g)
	m_pProcArray.push_back(m_pBillStarProc);        // �v���V�[�W�����v���V�[�W���z��ɓo�^����
};


// =====================================================================================================
// 
// �e�v���V�[�W�����̏���
// 
// =====================================================================================================
//------------------------------------------------------------------------
//
//	�p�[�e�B�N���v���V�[�W���N���X�̃R���X�g���N�^	
//
//   �Ȃ��A�v���V�[�W����delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
//------------------------------------------------------------------------
CParticleProc::CParticleProc(CGameMain* pGMain) : CBaseProc( pGMain)
{
	const int ParticleNumMax = 100; // ��̃p�[�e�B�N���I�u�W�F�N�g���̃p�[�e�B�N���̐�

	// �p�[�e�B�N���e�N�X�`��
	TCHAR szFName[] = _T("Data/Image/particle3.png");

	//�e�N�X�`���[�ǂݍ���
	m_pTexture = NULL;
	if (FAILED(m_pGMain->m_pD3D->CreateShaderResourceViewFromFile(szFName, &m_pTexture, 3)))
	{
		MessageBox(0, _T("�p�[�e�B�N���@�e�N�X�`���[��ǂݍ��߂܂���"),_T(""), MB_OK);
		return;
	}
	for (int i = 0; i < PARTICLE_MAX; i++)
	{
		// ��̃p�[�e�B�N���I�u�W�F�N�g���̃p�[�e�B�N���̐���ݒ肷��
		m_pObjArray.push_back(new CParticleObj( m_pGMain, ParticleNumMax));  // m_pObjArray�ɃI�u�W�F�N�g�𐶐�����
		((CParticleObj*)(m_pObjArray[i]))->SetTexture( m_pTexture ); // �p�[�e�B�N���e�N�X�`���̃Z�b�g
	}

};
//------------------------------------------------------------------------
//
//	�p�[�e�B�N���v���V�[�W���N���X�̃f�X�g���N�^	
//
//------------------------------------------------------------------------
CParticleProc::~CParticleProc()
{
	SAFE_RELEASE(m_pTexture);
};

//------------------------------------------------------------------------
//
//	�p�[�e�B�N���v���V�[�W���N���X�̊J�n	
//
//	�E�p�[�e�B�N���I�u�W�F�N�g�z��̒�����A�󂢂Ă���p�[�e�B�N����T���ĊJ�n����
//
//  VECTOR3 vEmitPos          �p�[�e�B�N���̔����ʒu
//  VECTOR3 vNormal           �p�[�e�B�N���̔����ʂ̖@���i�ȗ��j
//
//	�߂�l BOOL
//		TRUE	= ����
//		FALSE	= �ُ�
//
//------------------------------------------------------------------------
BOOL CParticleProc::Start(VECTOR3 vEmitPos, VECTOR3 vNormal)
{
	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			m_pObjArray[i]->Start(vEmitPos, vNormal);
			return TRUE;
		}
	}
	return FALSE;
};

// ========================================================================================
//
//	�p�[�e�B�N���I�u�W�F�N�g�N���X
//�i�|�C���g�X�v���C�g�Ńp�[�e�B�N���������j
//
// ========================================================================================
//------------------------------------------------------------------------
//
//	�p�[�e�B�N���I�u�W�F�N�g�̃R���X�g���N�^	
//
//  int MaxParticle          �p�[�e�B�N���̐�
//
//------------------------------------------------------------------------
CParticleObj::CParticleObj(CGameMain* pGMain, int MaxParticle) : CBaseObj( pGMain)
{
	m_pD3D = m_pGMain->m_pD3D;
	m_pShader = m_pGMain->m_pShader;
	m_fAlpha = 0.0f;
	m_fSize = 0.0f;
	m_MaxParticle = 0;
	m_vEmitPos = VECTOR3(0,0,0);
	m_pPartArray = NULL;
	m_Frame = 0;
	m_FrameEnd = 0;
	m_fSpeed = 0.0f;  // �p�[�e�B�N���̈ړ��X�s�[�h
	m_iBarthFrame = 0;     // �p�[�e�B�N���̈ړ��J�n�܂ł̍ő�҂����ԁi�����_���j
	m_pVertexBuffer = NULL;
	m_pTexture = NULL; //�e�N�X�`���[
	//	������
	Init(MaxParticle);
	// �o�[�e�b�N�X�o�b�t�@���쐬
	SetSrc();
}
//------------------------------------------------------------------------
//
//	�p�[�e�B�N���I�u�W�F�N�g�̃f�X�g���N�^	
//
//------------------------------------------------------------------------
CParticleObj::~CParticleObj()
{
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_DELETE_ARRAY(m_pPartArray);
}

//------------------------------------------------------------------------
//	�p�[�e�B�N���I�u�W�F�N�g�̏������֐�
//
//  �e��ݒ�l�̏�����
//
//  int MaxParticle        �p�[�e�B�N���̐�
//
//  �߂�l�@�@�@�Ȃ�
//------------------------------------------------------------------------
void CParticleObj::Init( int MaxParticle )
{
	m_bActive = FALSE;
	m_fAlpha = 1.0f;
	m_fSize = 0.1f;    // �p�[�e�B�N���̃T�C�Y // -- 2018.8.23 
	m_MaxParticle = MaxParticle;   // ��L�p�[�e�B�N���v���V�[�W���Ŏw�肵���p�[�e�B�N����
	m_pPartArray = new PART[m_MaxParticle];    // �p�[�e�B�N���z��̐���
	m_FrameEnd = 60;	// �p�[�e�B�N����\�����Ă��鎞��
	m_fSpeed = 0.015f;  // �p�[�e�B�N���̈ړ��X�s�[�h
	m_iBarthFrame = 20;     // �p�[�e�B�N���̈ړ��J�n�܂ł̍ő�҂����ԁi�����_���j
}

//------------------------------------------------------------------------
//
//	�p�[�e�B�N���I�u�W�F�N�g�̃o�[�e�B�N�X�o�b�t�@�쐬�ƃe�N�X�`���̓ǂݍ���	
//	�i�W�I���g���֘A���������D�����ł́h�_�h�p�j	
//
//	�߂�l HRESULT
//		S_OK	= ����
//		E_FAIL	= �ُ�
//
//------------------------------------------------------------------------
HRESULT CParticleObj::SetSrc()
{
	//�o�[�e�b�N�X
	PARTICLE_VERTEX vertices[] =
	{
		VECTOR3(0.0f, 0.0f, 0.0f)
	};

	// �Q�x�ڈȍ~�ɏ���������邱�Ƃ̑΍�
	SAFE_RELEASE(m_pVertexBuffer);

	// �o�[�e�b�N�X�o�b�t�@�[�쐬
	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(PARTICLE_VERTEX) * 1;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = vertices;
	if (FAILED(m_pD3D->m_pDevice->CreateBuffer(&bd, &InitData, &m_pVertexBuffer)))
	{
		return E_FAIL;
	}

	return S_OK;
}
//------------------------------------------------------------------------
//
//	�p�[�e�B�N���I�u�W�F�N�g�̊J�n	
//  �E�p�[�e�B�N�����w��ʒu���甭��������B
//  �E����������@�����W�Ŏw��ł���B�ȗ�����ƑS�����֔�������B
//
//  VECTOR3 vEmitPos          �p�[�e�B�N���̔����ʒu
//  VECTOR3 vNormal           �p�[�e�B�N���̔����ʂ̖@���i�ȗ��j
//
//	�߂�l BOOL
//		TRUE	= ����
//		FALSE	= �ُ�
//
//------------------------------------------------------------------------
BOOL CParticleObj::Start(VECTOR3 vEmitPos, VECTOR3 vNormal)
{
	if (m_bActive)
	{
		// ���łɕ\�����̂Ƃ�
		return FALSE;

	}else {
		// �J�n����
		m_bActive = TRUE;
		m_fAlpha  = 0.9f;
		m_vEmitPos = vEmitPos;
		m_Frame = 0;

		// �@�������𒆐S�Ƃ��ă����_�������ɔ���������
		VECTOR3 vDist, vMin, vMax;
		vDist.x = (1.0f - fabsf(vNormal.x))/2;
		vDist.y = (1.0f - fabsf(vNormal.y))/2;
		vDist.z = (1.0f - fabsf(vNormal.z))/2;

		if (vNormal.x < 0)
		{
			vMin.x = vNormal.x - vDist.x;
			vMax.x = 0.0f + vDist.x;
		}else {
			vMin.x = 0.0f - vDist.x;
			vMax.x = vNormal.x + vDist.x;
		}
		if (vNormal.y < 0)
		{
			vMin.y = vNormal.y - vDist.y;
			vMax.y = 0.0f + vDist.y;
		}else {
			vMin.y = 0.0f - vDist.y;
			vMax.y = vNormal.y + vDist.y;
		}
		if (vNormal.z < 0)
		{
			vMin.z = vNormal.z - vDist.z;
			vMax.z = 0.0f + vDist.z;
		}else {
			vMin.z = 0.0f - vDist.z;
			vMax.z = vNormal.z + vDist.z;
		}

		// �p�[�e�B�N���̊J�n
		for (int i = 0; i<m_MaxParticle; i++)
		{
			m_pPartArray[i].Pos = m_vEmitPos;
			m_pPartArray[i].Dir.x = ((float)rand() / (float)RAND_MAX) * (vMax.x - vMin.x) + vMin.x;
			m_pPartArray[i].Dir.y = ((float)rand() / (float)RAND_MAX) * (vMax.y - vMin.y) + vMin.y;
			m_pPartArray[i].Dir.z = ((float)rand() / (float)RAND_MAX) * (vMax.z - vMin.z) + vMin.z;
			m_pPartArray[i].Dir = normalize(m_pPartArray[i].Dir);
			m_pPartArray[i].Speed = (5 + ((float)rand() / (float)RAND_MAX)) * m_fSpeed;
			m_pPartArray[i].BirthFrame = (int)(((float)rand() / RAND_MAX) * m_iBarthFrame);
		}
		return TRUE;
	}
}

//------------------------------------------------------------------------
//
//	�p�[�e�B�N���I�u�W�F�N�g�̈ړ��E�X�V����	
//  �E�p�[�e�B�N�����X�V����
//
//	�߂�l �Ȃ�
//
//------------------------------------------------------------------------
void CParticleObj::Update()
{
	if (m_bActive)
	{
		m_Frame++;	// �t���[����i�߂�
		for (int i = 0; i < m_MaxParticle; i++)
		{
			if (m_Frame > m_pPartArray[i].BirthFrame) // ��̃p�[�e�B�N�����\���J�n���ԂɂȂ����Ƃ�
			{
				// �ړ�
				m_pPartArray[i].Pos = m_pPartArray[i].Pos + m_pPartArray[i].Dir * m_pPartArray[i].Speed;

				//m_pPartArray[i].Pos;

				// �d��
				m_pPartArray[i].Dir = m_pPartArray[i].Dir + VECTOR3(0, -0.049f, 0);
				// �n�ʂł̃o�E���h
				//if (m_pPartArray[i].Pos.y < 0)
				//{
				//	m_pPartArray[i].Dir.y = -m_pPartArray[i].Dir.y;
				//	m_pPartArray[i].Speed /= 1.8f;
				//}
			}
		}

		// �����_�����O
		Render();

		if (m_Frame >= m_FrameEnd) // �\�����ԏI����
		{
			m_bActive = FALSE;
		}

	}
}

//------------------------------------------------------------------------
//
//	�p�[�e�B�N���I�u�W�F�N�g����ʂɃ����_�����O	
//  �E�p�[�e�B�N����\������
//
//	�߂�l �Ȃ�
//
//------------------------------------------------------------------------
void CParticleObj::Render()
{
	// �\����ԂłȂ��Ƃ�
	if (!m_bActive)  return;

	//�g�p����V�F�[�_�[�̃Z�b�g
	m_pD3D->m_pDeviceContext->VSSetShader(m_pShader->m_pEffect3D_VS_POINT, NULL, 0);
	m_pD3D->m_pDeviceContext->GSSetShader(m_pShader->m_pEffect3D_GS_POINT, NULL, 0);
	m_pD3D->m_pDeviceContext->PSSetShader(m_pShader->m_pEffect3D_PS, NULL, 0);

	//�o�[�e�b�N�X�o�b�t�@�[���Z�b�g
	UINT stride = sizeof(PARTICLE_VERTEX);
	UINT offset = 0;
	m_pD3D->m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);

	// ���Z�����F�̃u�����f�B���O��ݒ�
	UINT mask = 0xffffffff;
	m_pD3D->m_pDeviceContext->OMSetBlendState(m_pD3D->m_pBlendStateAdd, NULL, mask);

	//�p�[�e�B�N���P�����P���|�C���g�X�v���C�g�Ƃ���m_MaxParticle���`��
	for (int i = 0; i<m_MaxParticle; i++)
	{
		if (m_FrameEnd < m_Frame + (m_iBarthFrame - m_pPartArray[i].BirthFrame)) continue;

		//�X�̃p�[�e�B�N���́A���_���������[���h�g�����X�t�H�[�������߂�
		MATRIX4X4 mWorld = GetLookatMatrix( m_pPartArray[i].Pos, m_pGMain->m_vEyePt);

		RenderParticle(mWorld, m_pGMain->m_mView, m_pGMain->m_mProj);
	}

	// �ʏ�̃u�����f�B���O�ɖ߂�
	m_pD3D->m_pDeviceContext->OMSetBlendState(m_pD3D->m_pBlendStateTrapen, NULL, mask);

	//�W�I���g���V�F�[�_�[�̃��Z�b�g
	m_pD3D->m_pDeviceContext->GSSetShader(NULL, NULL, 0);

	return;
}
//------------------------------------------------------------------------
//
//	�p�[�e�B�N���������_�����O����	
//
//  MATRIX4X4    W    ���[���h�}�g���b�N�X
//  MATRIX4X4    V    �r���[�}�g���b�N�X
//  MATRIX4X4    P    �v���W�F�N�V�����}�g���b�N�X
//
//	�߂�l �Ȃ�
//
//------------------------------------------------------------------------
void CParticleObj::RenderParticle(MATRIX4X4 W, MATRIX4X4 V, MATRIX4X4 P)
{
	//�V�F�[�_�[�̃R���X�^���g�o�b�t�@�[�Ɋe��f�[�^��n��
	D3D11_MAPPED_SUBRESOURCE pData;
	CONSTANT_BUFFER_EFFECT cb;
	ZeroMemory(&cb, sizeof(cb));
	if (SUCCEEDED(m_pD3D->m_pDeviceContext->Map(m_pShader->m_pConstantBufferEffect, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{
		//���[���h�A�J�����A�ˉe�s���n�� // -- 2017.8.25
		cb.mW = XMMatrixTranspose(W);
		cb.mV = XMMatrixTranspose(V);
		cb.mP = XMMatrixTranspose(P);

		cb.fAlpha    = m_fAlpha;
		cb.fSize     = m_fSize;          // �p�[�e�B�N���̃T�C�Y  // -- 2018.8.23
		memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(cb));
		m_pD3D->m_pDeviceContext->Unmap(m_pShader->m_pConstantBufferEffect, 0);
	}
	//���̃R���X�^���g�o�b�t�@�[���ǂ̃V�F�[�_�[�Ŏg����
	m_pD3D->m_pDeviceContext->VSSetConstantBuffers(0, 1, &m_pShader->m_pConstantBufferEffect);
	m_pD3D->m_pDeviceContext->GSSetConstantBuffers(0, 1, &m_pShader->m_pConstantBufferEffect);
	m_pD3D->m_pDeviceContext->PSSetConstantBuffers(0, 1, &m_pShader->m_pConstantBufferEffect);
	//���_�C���v�b�g���C�A�E�g���Z�b�g
	m_pD3D->m_pDeviceContext->IASetInputLayout(m_pShader->m_pEffect3D_VertexLayout);
	//�v���~�e�B�u�E�g�|���W�[���Z�b�g
	m_pD3D->m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
	//�e�N�X�`���[���V�F�[�_�[�ɓn��
	m_pD3D->m_pDeviceContext->PSSetSamplers(0, 1, &m_pD3D->m_pSampleLinear);
	m_pD3D->m_pDeviceContext->PSSetShaderResources(0, 1, &m_pTexture);
	//�v���~�e�B�u�������_�����O
	m_pD3D->m_pDeviceContext->Draw(1, 0);

}

// ========================================================================================
//
//	�r���{�[�h�̃N���X(���H�̃L���L��)
//
// ========================================================================================

//------------------------------------------------------------------------
//
//	�r���{�[�h�v���V�[�W���N���X�̃R���X�g���N�^(���H�̃L���L��)	
//
//   �Ȃ��A�v���V�[�W����delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
//------------------------------------------------------------------------
CBillboardProc::CBillboardProc(CGameMain* pGMain) : CBaseProc( pGMain)
{
	// �r���{�[�h�e�N�X�`��
	TCHAR szFName[] = _T("Data/Image/pipo-btleffect010.png");

	// �����r���{�[�h�X�^�e�B�b�N���b�V���̓ǂݍ���  // -- 2019.7.17
	m_pMesh = new CFbxMesh(pGMain->m_pFbxMeshCtrl, _T("Data/Item/BillSphere.mesh"));
	onlyRenderFlag = false; // M.S �`��݂̂���t���O
	// �e�N�X�`���̓ǂݍ���
	m_pTexture = NULL;
	if (FAILED(Load(szFName)))
	{
		return;
	}
	float fDestWidth = 2;         // M.S �\����
	float fDestHeight = 2;        // M.S �\������
	DWORD dwSrcX = 0;             // M.S �X�v���C�g�̈ʒu�@�w���W
	DWORD dwSrcY = 0;             // M.S �X�v���C�g�̈ʒu�@�x���W
	DWORD dwSrcWidth = 120;       // M.S �X�v���C�g�̕�
	DWORD dwSrcHeight = 120;  // M.S �X�v���C�g�̍���
	DWORD dwNumX = 8;         // M.S �A�j���[�V����������X�v���C�g�̐��@�w����
	DWORD dwNumY = 1;         // M.S �A�j���[�V����������X�v���C�g�̐��@�x����	 
	for (DWORD i = 0; i < BILLBOARD_MAX; i++)
	{
		m_pObjArray.push_back(new CBillboardObj(m_pGMain));  // m_pObjArray�ɃI�u�W�F�N�g�𐶐�����
		((CBillboardObj*)m_pObjArray[i])->m_pTexture = m_pTexture;            // �v���V�[�W���̃e�N�X�`���A�h���X���Z�b�g����
		((CBillboardObj*)m_pObjArray[i])->m_pMesh = m_pMesh;                  // �v���V�[�W���̃��b�V���A�h���X���Z�b�g����
		((CBillboardObj*)m_pObjArray[i])->m_dwImageHeight = m_dwImageHeight;
		((CBillboardObj*)m_pObjArray[i])->m_dwImageWidth  = m_dwImageWidth;
		//  �r���{�[�h�p�̃o�[�e�b�N�X�o�b�t�@�쐬
		((CBillboardObj*)m_pObjArray[i])->
		SetSrc(fDestWidth, fDestHeight, dwSrcX, dwSrcY, dwSrcWidth, dwSrcHeight, dwNumX, dwNumY);
	}
};
//------------------------------------------------------------------------
//
//	�r���{�[�h�v���V�[�W���N���X�̃f�X�g���N�^(���H�̃L���L��)
//
//------------------------------------------------------------------------
CBillboardProc::~CBillboardProc()
{
	SAFE_RELEASE(m_pTexture);
	SAFE_DELETE(m_pMesh);
};

//------------------------------------------------------------------------
//
//	�X�v���C�g�C���[�W�̓ǂݍ���(���H�̃L���L��)	
//
//  TCHAR* szFName            �r���{�[�h�̃e�N�X�`���t�@�C����
//
//	�߂�l HRESULT
//		S_OK	= ����
//		E_FAIL	= �ُ�
//
//------------------------------------------------------------------------
HRESULT CBillboardProc::Load(TCHAR* szFName)
{
	//�e�N�X�`���[�ǂݍ���	�i�p�ӂ���̂̓��\�[�X�r���[�����ł����j
	if (FAILED(m_pGMain->m_pD3D->CreateShaderResourceViewFromFile(szFName, &m_pTexture, m_dwImageWidth, m_dwImageHeight, 3)))
	{
		MessageBox(0, _T("�r���{�[�h�@�e�N�X�`���[��ǂݍ��߂܂���"), szFName, MB_OK);
		return E_FAIL;
	}
	return S_OK;
}

//------------------------------------------------------------------------
//
//	�r���{�[�h�v���V�[�W���̊J�n(���H�̃L���L��)	
//
//	�E�r���{�[�h�I�u�W�F�N�g�z��̒�����A�󂢂Ă���r���{�[�h��T���ĊJ�n����
//
//  VECTOR3 vPos          �r���{�[�h�̔����ʒu
//
//	�߂�l BOOL
//		TRUE	= ����
//		FALSE	= �ُ�
//
//------------------------------------------------------------------------
BOOL CBillboardProc::Start(VECTOR3 vPos)
{
	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			m_pObjArray[i]->Start(vPos);
			return TRUE;
		}
	}
	return FALSE;
};
//M.S ���ʂ̕��̃G�t�F�N�g�̕`��
//�G�t�F�N�g�̃I�u�W�F�N�g�z������ăA�N�e�B�u�ɂȂ��Ă���
//�G�t�F�N�g��Update���Ă�(�A�j���[�V�������~�߂ĕ`��)
//��  ���F�Ȃ�
//�߂�l�F�Ȃ�
void CBillboardProc::Render()    
{
	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		if (m_pObjArray[i]->GetActive() == TRUE)
		{
			onlyRenderFlag = true;          // M.S �`��̂݃t���O��true
			// M.S �`��Ώ�(�������Ă���L���L���G�t�F�N�g)�̃|�C���^��update���Ă�
			GetBillboardLineGlitterObjPtr(i)->Update(); 
			onlyRenderFlag = false;         // M.S �`��̂݃t���O��false
		}
	}
};
//------------------------------------------------------------------------
//
//	�r���{�[�h�I�u�W�F�N�g�̃R���X�g���N�^(���H�̃L���L��)	
//
//  �����@�Ȃ�
//
//------------------------------------------------------------------------
CBillboardObj::CBillboardObj(CGameMain* pGMain) : CBaseObj( pGMain)
{
	m_pD3D = m_pGMain->m_pD3D;
	m_pShader = m_pGMain->m_pShader;

	m_fDestWidth  = 0.0f;
	m_fDestHeight = 0.0f;
	m_dwSrcX = 0;
	m_dwSrcY = 0;
	m_dwSrcWidth = 0;
	m_dwSrcHeight = 0;
	m_vPos = VECTOR3(0,0,0);
	m_vUVOffset = VECTOR2(0,0);
	m_vUVScale = VECTOR2(1,1);              // -- 2019.7.17
	m_dwNumX = 0;
	m_dwNumY = 0;
	m_dwFrame = 0;
	m_fAlpha = 0.0f;
	m_dwImageWidth = 0;
	m_dwImageHeight = 0;
	m_pVertexBuffer = NULL;
	m_pTexture = NULL;  //�e�N�X�`���[�i�p�ӂ���̂̓��\�[�X�r���[�����ł����j
	drawFlag = true;
	//	������
	Init();
}

//------------------------------------------------------------------------
//
//	�r���{�[�h�I�u�W�F�N�g�̃f�X�g���N�^(���H�̃L���L��)	
//
//------------------------------------------------------------------------
CBillboardObj::~CBillboardObj()
{
	SAFE_RELEASE(m_pVertexBuffer);
}
//------------------------------------------------------------------------
//	�r���{�[�h�I�u�W�F�N�g�̏������֐�(���H�̃L���L��)
//
//  �e��ݒ�l�̏�����
//
//  �����@�@�Ȃ�
//
//  �߂�l�@�@�@�Ȃ�
//------------------------------------------------------------------------
void CBillboardObj::Init()
{
	m_bActive = FALSE;
	m_fAlpha = 0.9f;
}
//------------------------------------------------------------------------
//
//	�r���{�[�h�I�u�W�F�N�g�̃o�[�e�B�N�X�o�b�t�@�쐬(���H�̃L���L��)	
//	�i�W�I���g���֘A���������j	
//
//  float fDestWidth         �\����
//  float fDestHeight        �\������
//  DWORD dwSrcX             �X�v���C�g�̈ʒu�@�w���W
//  DWORD dwSrcY             �X�v���C�g�̈ʒu�@�x���W
//  DWORD dwSrcWidth         �X�v���C�g�̕�
//  DWORD dwSrcHeight        �X�v���C�g�̍���
//  DWORD dwNumX             �A�j���[�V����������X�v���C�g�̐��@�w����
//  DWORD dwNumY             �A�j���[�V����������X�v���C�g�̐��@�x����
//
//	�߂�l HRESULT
//		S_OK	= ����
//		E_FAIL	= �ُ�
//
//------------------------------------------------------------------------
HRESULT CBillboardObj::SetSrc(float fDestWidth, float fDestHeight, DWORD dwSrcX, DWORD dwSrcY, DWORD dwSrcWidth, DWORD dwSrcHeight, DWORD dwNumX, DWORD dwNumY)
{
	// �r���{�[�h�p�̔|���S�����쐬���A�o�[�e�b�N�X�o�b�t�@���쐬����
	m_fDestWidth   = fDestWidth;
	m_fDestHeight  = fDestHeight;
	m_dwSrcX       = dwSrcX;
	m_dwSrcY       = dwSrcY;
	m_dwSrcWidth   = dwSrcWidth;
	m_dwSrcHeight  = dwSrcHeight;
	m_dwNumX       = dwNumX;
	m_dwNumY       = dwNumY;

	//�o�[�e�b�N�X�o�b�t�@�[�쐬(�������̍��W�ō쐬)
	BILLBOARD_VERTEX vertices[] =
	{
		VECTOR3(-m_fDestWidth / 2,  m_fDestHeight / 2, 0), VECTOR2((float)(m_dwSrcX + m_dwSrcWidth) / m_dwImageWidth, (float)m_dwSrcY / m_dwImageHeight),                     //���_1  ����
		VECTOR3(m_fDestWidth / 2,  m_fDestHeight / 2, 0), VECTOR2((float)m_dwSrcX / m_dwImageWidth,                (float)m_dwSrcY / m_dwImageHeight),                        //���_2�@�E��    // -- 2021.1.11
		VECTOR3(-m_fDestWidth / 2, -m_fDestHeight / 2, 0), VECTOR2((float)(m_dwSrcX + m_dwSrcWidth) / m_dwImageWidth, (float)(m_dwSrcY + m_dwSrcHeight) / m_dwImageHeight),   //���_3�@����    // -- 2021.1.11
		VECTOR3(m_fDestWidth / 2, -m_fDestHeight / 2, 0), VECTOR2((float)m_dwSrcX / m_dwImageWidth,                (float)(m_dwSrcY + m_dwSrcHeight) / m_dwImageHeight),      //���_4�@�E��
	};

	// �Q�x�ڈȍ~�ɏ���������邱�Ƃ̑΍�
	SAFE_RELEASE(m_pVertexBuffer);

	// �o�[�e�b�N�X�o�b�t�@�[�쐬
	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(BILLBOARD_VERTEX) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = vertices;
	if (FAILED(m_pD3D->m_pDevice->CreateBuffer(&bd, &InitData, &m_pVertexBuffer)))
	{
		return E_FAIL;
	}

	return S_OK;
}
//------------------------------------------------------------------------
//
//	�r���{�[�h�I�u�W�F�N�g�̊J�n(���H�̃L���L��)	
//
//  VECTOR3   vPos     �\���ʒu�i�r���{�[�h�̒��S�_�ʒu���w��j
//
//	�߂�l BOOL
//		TRUE      �\���p��
//		FALSE     �\���I��
//
//------------------------------------------------------------------------
BOOL CBillboardObj::Start(VECTOR3 vPos)
{
	if (m_bActive) return FALSE;  // ���łɊJ�n��

	m_bActive = TRUE;
	m_dwFrame = 0;
	m_vPos = vPos;
	drawFlag = true;
	return TRUE;
}

//------------------------------------------------------------------------
//
//	�r���{�[�h�I�u�W�F�N�g�̍X�V(���H�̃L���L��)	
//
//	�߂�l �Ȃ�
//
//------------------------------------------------------------------------
void CBillboardObj::Update()
{
	const DWORD dwSpeed = 5;   // �r���{�[�h�̃A�j���[�V�����X�s�[�h
	if (!m_bActive) return;
	// M.S �`��̂݃t���O��true���ǂ���
	if (m_pGMain->m_pEffectProc->m_pBillProc->onlyRenderFlag == true) {
		// �A�j���[�V�����𓮂������`�悷��
		DWORD dwIdx;
		dwIdx =  m_dwFrame / dwSpeed;

		// �A�j���[�V�����̂��߂̃e�N�X�`���I�t�Z�b�g��ݒ肷��
		m_vUVOffset.x = (float)(dwIdx % m_dwNumX * GetSrcWidth());   // �w�����̕ψ�
		m_vUVOffset.y = (float)(dwIdx / m_dwNumX * GetSrcHeight());  // �x�����̕ψ�

		//Render();// �����_�����O
		RenderMesh();// �����_�����O(�����r���{�[�h���b�V��)
	}
	else {
		// M.S �`��̂݃t���O��false�̏ꍇ
		// M.S �A�j���[�V�����𓮂����ĕ`�悷��
		DWORD dwIdx;
		m_dwFrame++;
		dwIdx = m_dwFrame / dwSpeed;
		if (dwIdx >= m_dwNumX * m_dwNumY || drawFlag == false)	// �p�^�[���̍Ō�ɒB�����Ƃ�
		{
			m_bActive = FALSE;
			return;
		}
		// �A�j���[�V�����̂��߂̃e�N�X�`���I�t�Z�b�g��ݒ肷��
		m_vUVOffset.x = (float)(dwIdx % m_dwNumX * GetSrcWidth());   // �w�����̕ψ�
		m_vUVOffset.y = (float)(dwIdx / m_dwNumX * GetSrcHeight());  // �x�����̕ψ�
		//Render();// �����_�����O
		RenderMesh();// �����_�����O(�����r���{�[�h���b�V��)
	}
}
//------------------------------------------------------------------------
//
//	�r���{�[�h�I�u�W�F�N�g����ʂɃ����_�����O(���H�̃L���L��)	
//
//	�߂�l BOOL
//		TRUE      �\���p��
//		FALSE     �\���I��
//
//------------------------------------------------------------------------
BOOL CBillboardObj::Render()
{
	if (!m_bActive) return FALSE;

	//�r���{�[�h�́A���_���������[���h�g�����X�t�H�[�������߂�
	MATRIX4X4 mWorld =	GetLookatMatrix( m_vPos, m_pGMain->m_vEyePt);

	//�g�p����V�F�[�_�[�̃Z�b�g
	m_pD3D->m_pDeviceContext->VSSetShader(m_pShader->m_pEffect3D_VS_BILL, NULL, 0);
	m_pD3D->m_pDeviceContext->PSSetShader(m_pShader->m_pEffect3D_PS, NULL, 0);

	//�o�[�e�b�N�X�o�b�t�@�[���Z�b�g
	UINT stride = sizeof(BILLBOARD_VERTEX);
	UINT offset = 0;
	m_pD3D->m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);

	// ���Z�����F�̃u�����f�B���O��ݒ�
	UINT mask = 0xffffffff;
	m_pD3D->m_pDeviceContext->OMSetBlendState(m_pD3D->m_pBlendStateAdd, NULL, mask);

	//�V�F�[�_�[�̃R���X�^���g�o�b�t�@�[�Ɋe��f�[�^��n��
	D3D11_MAPPED_SUBRESOURCE pData;
	CONSTANT_BUFFER_EFFECT cb;
	ZeroMemory(&cb, sizeof(cb));

	if (SUCCEEDED(m_pD3D->m_pDeviceContext->Map(m_pShader->m_pConstantBufferEffect, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{
		//���[���h�A�J�����A�ˉe�s��A�e�N�X�`���[�I�t�Z�b�g��n��
		cb.mWVP = XMMatrixTranspose(mWorld * m_pGMain->m_mView * m_pGMain->m_mProj);

		cb.vUVOffset.x = m_vUVOffset.x / m_dwImageWidth;		// �e�N�X�`���A�j���[�V�����̃I�t�Z�b�g
		cb.vUVOffset.y = m_vUVOffset.y / m_dwImageHeight;		// �e�N�X�`���A�j���[�V�����̃I�t�Z�b�g
		cb.vUVScale.x = 1;
		cb.vUVScale.y = 1;
		cb.fAlpha      = m_fAlpha;

		memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(cb));
		m_pD3D->m_pDeviceContext->Unmap(m_pShader->m_pConstantBufferEffect, 0);
	}
	//���̃R���X�^���g�o�b�t�@�[���ǂ̃V�F�[�_�[�Ŏg����
	m_pD3D->m_pDeviceContext->VSSetConstantBuffers(0, 1, &m_pShader->m_pConstantBufferEffect);
	m_pD3D->m_pDeviceContext->PSSetConstantBuffers(0, 1, &m_pShader->m_pConstantBufferEffect);
	//���_�C���v�b�g���C�A�E�g���Z�b�g
	m_pD3D->m_pDeviceContext->IASetInputLayout(m_pShader->m_pEffect3D_VertexLayout_BILL);
	//�v���~�e�B�u�E�g�|���W�[���Z�b�g
	m_pD3D->m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	//�e�N�X�`���[���V�F�[�_�[�ɓn��
	m_pD3D->m_pDeviceContext->PSSetSamplers(0, 1, &m_pD3D->m_pSampleLinear);
	m_pD3D->m_pDeviceContext->PSSetShaderResources(0, 1, &m_pTexture);
	//�v���~�e�B�u�������_�����O
	m_pD3D->m_pDeviceContext->Draw(4, 0);

	// �ʏ�̃u�����f�B���O�ɖ߂�
	m_pD3D->m_pDeviceContext->OMSetBlendState(m_pD3D->m_pBlendStateTrapen, NULL, mask);

	return TRUE;
}

//------------------------------------------------------------------------  // -- 2019.7.17
//
//	�r���{�[�h���b�V������ʂɃ����_�����O���鏈��(���H�̃L���L��)	
//
// ����
//
//	�߂�l HRESULT
//		S_OK	= ����
//		E_FAIL	= �ُ�
//
//------------------------------------------------------------------------
void CBillboardObj::RenderMesh()
{
	//�g�p����V�F�[�_�[�̓o�^	
	m_pD3D->m_pDeviceContext->VSSetShader(m_pShader->m_pEffect3D_VS_BILLMESH, NULL, 0);
	m_pD3D->m_pDeviceContext->PSSetShader(m_pShader->m_pEffect3D_PS, NULL, 0);

	//�r���{�[�h�́A���_���������[���h�g�����X�t�H�[�������߂�
	MATRIX4X4 mWorld = GetLookatMatrix(m_vPos, m_pGMain->m_vEyePt);
	// ���b�V���̑傫���Ɋg�傷��ݒ肷��i���X�̃��b�V���͂P���l���̔����j
	MATRIX4X4 mScale = XMMatrixScaling(GetDestWidth(), GetDestHeight(), (GetDestWidth() + GetDestHeight()) / 2);
	mWorld = mScale * mWorld;

	// ���Z�����F�̃u�����f�B���O��ݒ�
	UINT mask = 0xffffffff;
	m_pD3D->m_pDeviceContext->OMSetBlendState(m_pD3D->m_pBlendStateAdd, NULL, mask);

	//�V�F�[�_�[�̃R���X�^���g�o�b�t�@�[�Ɋe��f�[�^��n��	
	D3D11_MAPPED_SUBRESOURCE pData;
	CONSTANT_BUFFER_EFFECT cb;
	if (SUCCEEDED(m_pD3D->m_pDeviceContext->Map(m_pShader->m_pConstantBufferEffect, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{
		//���[���h�A�J�����A�ˉe�s��A�e�N�X�`���[�I�t�Z�b�g��n��
		cb.mWVP = XMMatrixTranspose(mWorld * m_pGMain->m_mView * m_pGMain->m_mProj);

		cb.vUVOffset.x = m_vUVOffset.x / m_dwImageWidth;			// �e�N�X�`���A�j���[�V�����̃I�t�Z�b�g
		cb.vUVOffset.y = m_vUVOffset.y / m_dwImageHeight;			// �e�N�X�`���A�j���[�V�����̃I�t�Z�b�g
		cb.vUVScale.x = (float)GetSrcWidth() / m_dwImageWidth;		// �e�N�X�`���A�j���[�V������1/����
		cb.vUVScale.y = (float)GetSrcHeight() / m_dwImageHeight;	// �e�N�X�`���A�j���[�V������1/�c��

		cb.fAlpha = m_fAlpha;

		memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(cb));
		m_pD3D->m_pDeviceContext->Unmap(m_pShader->m_pConstantBufferEffect, 0);
	}

	//���̃R���X�^���g�o�b�t�@�[���ǂ̃V�F�[�_�[�Ŏg����
	m_pD3D->m_pDeviceContext->VSSetConstantBuffers(0, 1, &m_pShader->m_pConstantBufferEffect);
	m_pD3D->m_pDeviceContext->PSSetConstantBuffers(0, 1, &m_pShader->m_pConstantBufferEffect);

	//���_�C���v�b�g���C�A�E�g���Z�b�g
	m_pD3D->m_pDeviceContext->IASetInputLayout(m_pShader->m_pFbxStaticMesh_VertexLayout);

	//�v���~�e�B�u�E�g�|���W�[���Z�b�g
	m_pD3D->m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//�e�N�X�`���[�T���v���[���V�F�[�_�[�ɓn��
	m_pD3D->m_pDeviceContext->PSSetSamplers(0, 1, &m_pD3D->m_pSampleLinear);

	// ���b�V���̕`�揇�����肷��m_dwRenderIdxArray�̐ݒ�
	m_pMesh->SetRenderIdxArray(mWorld, m_pGMain->m_vEyePt);

	// ���b�V���̐������e�N�X�`���[�A�o�[�e�b�N�X�o�b�t�@�A�C���f�b�N�X�o�b�t�@���Z�b�g���āA�����_�����O����
	for (DWORD mi = 0; mi < m_pMesh->m_dwMeshNum; mi++)
	{
		DWORD i = m_pMesh->m_dwRenderIdxArray[mi];

		//�e�N�X�`���[���V�F�[�_�[�ɓn��
		//m_pD3D->m_pDeviceContext->PSSetShaderResources(0, 1, &m_pMesh->m_pMeshArray[i].m_pTexture);
		m_pD3D->m_pDeviceContext->PSSetShaderResources(0, 1, &m_pTexture);

		// �o�[�e�b�N�X�o�b�t�@�[���Z�b�g
		UINT stride = sizeof(StaticVertexNormal);
		UINT offset = 0;
		m_pD3D->m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pMesh->m_pMeshArray[i].m_pVertexBuffer, &stride, &offset);

		//�C���f�b�N�X�o�b�t�@�[���Z�b�g
		m_pD3D->m_pDeviceContext->IASetIndexBuffer(m_pMesh->m_pMeshArray[i].m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

		//�v���~�e�B�u�������_�����O
		// �i�C���f�b�N�X�̐����w�肵�ă����_�����O�j
		m_pD3D->m_pDeviceContext->DrawIndexed(m_pMesh->m_pMeshArray[i].m_dwIndicesNum, 0, 0);
	}

	// �ʏ�̃u�����f�B���O�ɖ߂�
	m_pD3D->m_pDeviceContext->OMSetBlendState(m_pD3D->m_pBlendStateTrapen, NULL, mask);
}
// ========================================================================================
//
//	�r���{�[�h�@�����₫�̃N���X
//
// ========================================================================================
//------------------------------------------------------------------------
//
//	�r���{�[�h�@�����₫�v���V�[�W���N���X�̃R���X�g���N�^	
//
//   �Ȃ��A�v���V�[�W����delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
//------------------------------------------------------------------------
CBillFireProc::CBillFireProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	// �r���{�[�h�@�����₫�e�N�X�`��
	TCHAR szFName[] = _T("Data/Image/pipofm-topen03_192.png");

	// �e�N�X�`���̓ǂݍ���
	m_pTexture = NULL;
	if (FAILED(Load(szFName)))
	{
		return;
	}
	float fDestWidth = 0;         // M.S �\����
	float fDestHeight = 0;        // M.S �\������
	DWORD dwSrcX = 0;             // M.S �X�v���C�g�̈ʒu�@�w���W
	DWORD dwSrcY = 0;             // M.S �X�v���C�g�̈ʒu�@�x���W
	DWORD dwSrcWidth = 192;       // M.S �X�v���C�g�̕�
	DWORD dwSrcHeight = 192;  // M.S �X�v���C�g�̍���
	DWORD dwNumX = 5;         // M.S �A�j���[�V����������X�v���C�g�̐��@�w����
	DWORD dwNumY = 4;         // M.S �A�j���[�V����������X�v���C�g�̐��@�x����	 
	for (DWORD i = 0; i < BILLFIRE_MAX; i++)
	{
		m_pObjArray.push_back(new CBillFireObj(m_pGMain));  // m_pObjArray�ɃI�u�W�F�N�g�𐶐�����
		((CBillFireObj*)m_pObjArray[i])->m_pTexture = m_pTexture;            // �v���V�[�W���̃e�N�X�`���A�h���X���Z�b�g����
		((CBillFireObj*)m_pObjArray[i])->m_dwImageHeight = m_dwImageHeight;
		((CBillFireObj*)m_pObjArray[i])->m_dwImageWidth = m_dwImageWidth;
		// �r���{�[�h�@�����₫�p�̃o�[�e�B�N�X�o�b�t�@�쐬																			
		((CBillFireObj*)m_pObjArray[i])->
		SetSrc(fDestWidth, fDestHeight, dwSrcX, dwSrcY, dwSrcWidth, dwSrcHeight, dwNumX, dwNumY);
	}
};

//------------------------------------------------------------------------
//
//	�r���{�[�h�@�����₫�v���V�[�W���N���X�̃f�X�g���N�^	
//
//------------------------------------------------------------------------
CBillFireProc::~CBillFireProc()
{
	SAFE_RELEASE(m_pTexture);
};

//------------------------------------------------------------------------
//
//	�X�v���C�g�C���[�W�̓ǂݍ���	
//
//  TCHAR* szFName            �r���{�[�h�@�����₫�̃e�N�X�`���t�@�C����
//
//	�߂�l HRESULT
//		S_OK	= ����
//		E_FAIL	= �ُ�
//
//------------------------------------------------------------------------
HRESULT CBillFireProc::Load(TCHAR* szFName)
{
	//�e�N�X�`���[�ǂݍ���	�i�p�ӂ���̂̓��\�[�X�r���[�����ł����j
	if (FAILED(m_pGMain->m_pD3D->CreateShaderResourceViewFromFile(szFName, &m_pTexture, m_dwImageWidth, m_dwImageHeight, 3)))
	{
		MessageBox(0, _T("�r���{�[�h�@�����₫�@�e�N�X�`���[��ǂݍ��߂܂���"), szFName, MB_OK);
		return E_FAIL;
	}
	return S_OK;
}

//------------------------------------------------------------------------
//
//	�r���{�[�h�@�����₫�v���V�[�W���̊J�n	
//  (�����₫�̐�����������g�ōs���Ƃ�)
//
//	�E�r���{�[�h�@�����₫�I�u�W�F�N�g�z��̒�����A�󂢂Ă���r���{�[�h�@�����₫��T���ĊJ�n����
//
//  VECTOR3 vPos          �r���{�[�h�@�����₫�̔����ʒu
//
//	�߂�l BOOL
//		TRUE	= ����
//		FALSE	= �ُ�
//
//------------------------------------------------------------------------
BOOL CBillFireProc::Start(VECTOR3 vPos)
{
	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			m_pObjArray[i]->Start(vPos);
			return TRUE;
		}
	}
	return FALSE;
};

//------------------------------------------------------------------------
//
//	�r���{�[�h�@�����₫�v���V�[�W���̊J�n	
//  (�����₫�̐�����v�������������̐e���s���Ƃ�)
//
//
//	�E�r���{�[�h�@�����₫�I�u�W�F�N�g�z��̒�����A�󂢂Ă���r���{�[�h�@�����₫��T���ĊJ�n����
//
//	�߂�l CBillFireObj*
//		�����ł����Ƃ��@�@�r���{�[�h�@�����₫�I�u�W�F�N�g�A�h���X
//		�����ł��Ȃ��Ƃ��@NULL
//
//------------------------------------------------------------------------
CBillFireObj*  CBillFireProc::Start()
{
	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			m_pObjArray[i]->SetActive(TRUE);
			((CBillFireObj*)(m_pObjArray[i]))->m_bAuto = FALSE;  // �����₫�̐�����v�������������̐e���s��
			((CBillFireObj*)(m_pObjArray[i]))->m_dwFrame = 0;
			return ((CBillFireObj*)(m_pObjArray[i]));
		}
	}
	return NULL;
};

//------------------------------------------------------------------------
//
//	�r���{�[�h�@�����₫�I�u�W�F�N�g�̃R���X�g���N�^	
//
//  �����@�Ȃ�
//
//------------------------------------------------------------------------
CBillFireObj::CBillFireObj(CGameMain* pGMain) : CBaseObj( pGMain)
{
	m_pD3D = m_pGMain->m_pD3D;
	m_pShader = m_pGMain->m_pShader;
	m_fDestWidth  = 0.0f;
	m_fDestHeight = 0.0f;
	m_dwSrcX = 0;
	m_dwSrcY = 0;
	m_dwSrcWidth = 0;
	m_dwSrcHeight = 0;
	m_vPos = VECTOR3(0, 0, 0);
	m_vUVOffset = VECTOR2(0, 0);
	m_dwNumX = 0;
	m_dwNumY = 0;
	m_dwFrame = 0;
	m_fAlpha = 0.0f;
	m_dwImageWidth = 0;
	m_dwImageHeight = 0;
	m_pVertexBuffer = NULL;
	m_pTexture = NULL;  //�e�N�X�`���[�i�p�ӂ���̂̓��\�[�X�r���[�����ł����j
	//	������
	Init();
}

//------------------------------------------------------------------------
//
//	�r���{�[�h�@�����₫�I�u�W�F�N�g�̃f�X�g���N�^	
//
//------------------------------------------------------------------------
CBillFireObj::~CBillFireObj()
{
	SAFE_RELEASE(m_pVertexBuffer);
}
//------------------------------------------------------------------------
//	�r���{�[�h�@�����₫�I�u�W�F�N�g�̏������֐�
//
//  �e��ݒ�l�̏�����
//
//  �����@�@�Ȃ�
//
//  �߂�l�@�@�@�Ȃ�
//------------------------------------------------------------------------
void CBillFireObj::Init()
{
	m_bActive = FALSE;
	m_bAuto  = FALSE;
	m_fAlpha = 0.9f;
}
//------------------------------------------------------------------------
//
//	�r���{�[�h�@�����₫�I�u�W�F�N�g�̃o�[�e�B�N�X�o�b�t�@�쐬	
//	�i�W�I���g���֘A���������j	
//
//  float fDestWidth         �\����
//  float fDestHeight        �\������
//  DWORD dwSrcX             �X�v���C�g�̈ʒu�@�w���W
//  DWORD dwSrcY             �X�v���C�g�̈ʒu�@�x���W
//  DWORD dwSrcWidth         �X�v���C�g�̕�
//  DWORD dwSrcHeight        �X�v���C�g�̍���
//  DWORD dwNumX             �A�j���[�V����������X�v���C�g�̐��@�w����
//  DWORD dwNumY             �A�j���[�V����������X�v���C�g�̐��@�x����
//
//	�߂�l HRESULT
//		S_OK	= ����
//		E_FAIL	= �ُ�
//
//------------------------------------------------------------------------
HRESULT CBillFireObj::SetSrc(float fDestWidth, float fDestHeight, DWORD dwSrcX, DWORD dwSrcY, DWORD dwSrcWidth, DWORD dwSrcHeight, DWORD dwNumX, DWORD dwNumY)
{
	// �r���{�[�h�@�����₫�p�̔|���S�����쐬���A�o�[�e�b�N�X�o�b�t�@���쐬����
	m_fDestWidth = fDestWidth;
	m_fDestHeight = fDestHeight;
	m_dwSrcX = dwSrcX;
	m_dwSrcY = dwSrcY;
	m_dwSrcWidth = dwSrcWidth;
	m_dwSrcHeight = dwSrcHeight;
	m_dwNumX = dwNumX;
	m_dwNumY = dwNumY;
	//�o�[�e�b�N�X�o�b�t�@�[�쐬(�������̍��W�ō쐬)
	BILLBOARD_VERTEX vertices[] =
	{
		VECTOR3(-m_fDestWidth / 2,  m_fDestHeight / 2, 0), VECTOR2((float)(m_dwSrcX + m_dwSrcWidth) / m_dwImageWidth, (float)m_dwSrcY / m_dwImageHeight),                     //���_1  ����
		VECTOR3(m_fDestWidth / 2,  m_fDestHeight / 2, 0), VECTOR2((float)m_dwSrcX / m_dwImageWidth,                (float)m_dwSrcY / m_dwImageHeight),                        //���_2�@�E��    // -- 2021.1.11
		VECTOR3(-m_fDestWidth / 2, -m_fDestHeight / 2, 0), VECTOR2((float)(m_dwSrcX + m_dwSrcWidth) / m_dwImageWidth, (float)(m_dwSrcY + m_dwSrcHeight) / m_dwImageHeight),   //���_3�@����    // -- 2021.1.11
		VECTOR3(m_fDestWidth / 2, -m_fDestHeight / 2, 0), VECTOR2((float)m_dwSrcX / m_dwImageWidth,                (float)(m_dwSrcY + m_dwSrcHeight) / m_dwImageHeight),      //���_4�@�E��
	};
	// �Q�x�ڈȍ~�ɏ���������邱�Ƃ̑΍�
	SAFE_RELEASE(m_pVertexBuffer);
	// �o�[�e�b�N�X�o�b�t�@�[�쐬
	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(BILLBOARD_VERTEX) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = vertices;
	if (FAILED(m_pD3D->m_pDevice->CreateBuffer(&bd, &InitData, &m_pVertexBuffer)))
	{
		return E_FAIL;
	}
	return S_OK;
}
//------------------------------------------------------------------------
//
//	�r���{�[�h�@�����₫�I�u�W�F�N�g�̊J�n	
//
//  VECTOR3   vPos     �\���ʒu�i�r���{�[�h�@�����₫�̒��S�_�ʒu���w��j
//
//	�߂�l BOOL
//		TRUE      �\���p��
//		FALSE     �\���I��
//
//------------------------------------------------------------------------
BOOL CBillFireObj::Start(VECTOR3 vPos)
{
	if (m_bActive) return FALSE;  // ���łɊJ�n��
	m_bActive = TRUE;
	m_bAuto   = TRUE;  // �������[�h
	m_dwFrame = 0;
	m_vPos    = vPos;
	return TRUE;
}

//------------------------------------------------------------------------
//
//	�r���{�[�h�@�����₫�I�u�W�F�N�g�̍X�V	
//
//	�߂�l �Ȃ�
//
//------------------------------------------------------------------------
void CBillFireObj::Update()
{
	const DWORD dwSpeed = 5;   // �A�j���[�V�����X�s�[�h
	DWORD dwIdx;
	if (!m_bActive) return;
	m_dwFrame++;
	dwIdx = m_dwFrame / dwSpeed;
	if (dwIdx >= m_dwNumX * m_dwNumY)	// �p�^�[���̍Ō�ɒB�����Ƃ�
	{
		if (m_bAuto){  // �������[�h�̂Ƃ��͏I��
			m_bActive = FALSE;
			return;
		}
		else {
			dwIdx = 0; // �A�j���[�V�������J��Ԃ�
		}
	}
	// �A�j���[�V�����̂��߂̃e�N�X�`���I�t�Z�b�g��ݒ肷��
	m_vUVOffset.x = (float)(dwIdx % m_dwNumX * GetSrcWidth());   // �w�����̕ψ�
	m_vUVOffset.y = (float)(dwIdx / m_dwNumX * GetSrcHeight());  // �x�����̕ψ�
	Render();// �����_�����O
}
//------------------------------------------------------------------------
//
//	�r���{�[�h�@�����₫�I�u�W�F�N�g����ʂɃ����_�����O	
//
//	�߂�l BOOL
//		TRUE      �\���p��
//		FALSE     �\���I��
//
//------------------------------------------------------------------------
BOOL CBillFireObj::Render()
{
	if (!m_bActive) return FALSE;
	//�r���{�[�h�@�����₫�́A���_���������[���h�g�����X�t�H�[�������߂�
	MATRIX4X4 mWorld = GetLookatMatrix(m_vPos, m_pGMain->m_vEyePt);
	//�g�p����V�F�[�_�[�̃Z�b�g
	m_pD3D->m_pDeviceContext->VSSetShader(m_pShader->m_pEffect3D_VS_BILL, NULL, 0);
	m_pD3D->m_pDeviceContext->PSSetShader(m_pShader->m_pEffect3D_PS, NULL, 0);
	//�o�[�e�b�N�X�o�b�t�@�[���Z�b�g
	UINT stride = sizeof(BILLBOARD_VERTEX);
	UINT offset = 0;
	m_pD3D->m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
	// ���Z�����F�̃u�����f�B���O��ݒ�
	UINT mask = 0xffffffff;
	m_pD3D->m_pDeviceContext->OMSetBlendState(m_pD3D->m_pBlendStateAdd, NULL, mask);
	//�V�F�[�_�[�̃R���X�^���g�o�b�t�@�[�Ɋe��f�[�^��n��
	D3D11_MAPPED_SUBRESOURCE pData;
	CONSTANT_BUFFER_EFFECT cb;
	ZeroMemory(&cb, sizeof(cb));
	if (SUCCEEDED(m_pD3D->m_pDeviceContext->Map(m_pShader->m_pConstantBufferEffect, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{
		//���[���h�A�J�����A�ˉe�s��A�e�N�X�`���[�I�t�Z�b�g��n��
		cb.mWVP = XMMatrixTranspose(mWorld * m_pGMain->m_mView * m_pGMain->m_mProj);
		cb.vUVOffset.x = m_vUVOffset.x / m_dwImageWidth;		// �e�N�X�`���A�j���[�V�����̃I�t�Z�b�g
		cb.vUVOffset.y = m_vUVOffset.y / m_dwImageHeight;		// �e�N�X�`���A�j���[�V�����̃I�t�Z�b�g
		cb.vUVScale.x = 1;
		cb.vUVScale.y = 1;
		cb.fAlpha = m_fAlpha;
		memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(cb));
		m_pD3D->m_pDeviceContext->Unmap(m_pShader->m_pConstantBufferEffect, 0);
	}
	//���̃R���X�^���g�o�b�t�@�[���ǂ̃V�F�[�_�[�Ŏg����
	m_pD3D->m_pDeviceContext->VSSetConstantBuffers(0, 1, &m_pShader->m_pConstantBufferEffect);
	m_pD3D->m_pDeviceContext->PSSetConstantBuffers(0, 1, &m_pShader->m_pConstantBufferEffect);
	//���_�C���v�b�g���C�A�E�g���Z�b�g
	m_pD3D->m_pDeviceContext->IASetInputLayout(m_pShader->m_pEffect3D_VertexLayout_BILL);
	//�v���~�e�B�u�E�g�|���W�[���Z�b�g
	m_pD3D->m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	//�e�N�X�`���[���V�F�[�_�[�ɓn��
	m_pD3D->m_pDeviceContext->PSSetSamplers(0, 1, &m_pD3D->m_pSampleLinear);
	m_pD3D->m_pDeviceContext->PSSetShaderResources(0, 1, &m_pTexture);
	//�v���~�e�B�u�������_�����O
	m_pD3D->m_pDeviceContext->Draw(4, 0);
	// �ʏ�̃u�����f�B���O�ɖ߂�
	m_pD3D->m_pDeviceContext->OMSetBlendState(m_pD3D->m_pBlendStateTrapen, NULL, mask);
	return TRUE;
}


// ========================================================================================
//
//	�r���{�[�h(���̐����G�t�F�N�g)�̃N���X
//
// ========================================================================================

//------------------------------------------------------------------------
//
//	�r���{�[�h�v���V�[�W���N���X�̃R���X�g���N�^(���̐����G�t�F�N�g)	
//
//   �Ȃ��A�v���V�[�W����delete��CBaseProc�̃f�X�g���N�^�ōs�����ߕs�v
//
//------------------------------------------------------------------------
CBillboardBornStarProc::CBillboardBornStarProc(CGameMain* pGMain) : CBaseProc(pGMain)
{
	// �r���{�[�h�e�N�X�`��
	TCHAR szFName[] = _T("Data/Image/pipo-btleffect084.png");	
	// �e�N�X�`���̓ǂݍ���
	m_pTexture = NULL;
	if (FAILED(Load(szFName)))
	{
		return;
	}
	float fDestWidth = 15;         // M.S �\����
	float fDestHeight = 15;        // M.S �\������
	DWORD dwSrcX = 0;             // M.S �X�v���C�g�̈ʒu�@�w���W
	DWORD dwSrcY = 0;             // M.S �X�v���C�g�̈ʒu�@�x���W
	DWORD dwSrcWidth = 120;       // M.S �X�v���C�g�̕�
	DWORD dwSrcHeight = 120;  // M.S �X�v���C�g�̍���
	DWORD dwNumX = 9;         // M.S �A�j���[�V����������X�v���C�g�̐��@�w����
	DWORD dwNumY = 1;         // M.S �A�j���[�V����������X�v���C�g�̐��@�x����	 
	for (DWORD i = 0; i < BILLSTART_MAX; i++)
	{
		m_pObjArray.push_back(new CBillboardBornStarObj(m_pGMain));  // m_pObjArray�ɃI�u�W�F�N�g�𐶐�����
		((CBillboardBornStarObj*)m_pObjArray[i])->m_pTexture = m_pTexture;            // �v���V�[�W���̃e�N�X�`���A�h���X���Z�b�g����
		((CBillboardBornStarObj*)m_pObjArray[i])->m_dwImageHeight = m_dwImageHeight;
		((CBillboardBornStarObj*)m_pObjArray[i])->m_dwImageWidth = m_dwImageWidth;
		//  �r���{�[�h�p�̃o�[�e�b�N�X�o�b�t�@�쐬	
		((CBillboardBornStarObj*)m_pObjArray[i])->
		SetSrc(fDestWidth, fDestHeight, dwSrcX, dwSrcY, dwSrcWidth, dwSrcHeight, dwNumX, dwNumY);  																		
	}
};

//------------------------------------------------------------------------
//
//	�r���{�[�h�v���V�[�W���N���X�̃f�X�g���N�^(���̐����G�t�F�N�g)	
//
//------------------------------------------------------------------------
CBillboardBornStarProc::~CBillboardBornStarProc()
{
	SAFE_RELEASE(m_pTexture);
	SAFE_DELETE(m_pMesh);
};

//------------------------------------------------------------------------
//
//	�X�v���C�g�C���[�W�̓ǂݍ���(���̐����G�t�F�N�g)	
//
//  TCHAR* szFName            �r���{�[�h�̃e�N�X�`���t�@�C����
//
//	�߂�l HRESULT
//		S_OK	= ����
//		E_FAIL	= �ُ�
//
//------------------------------------------------------------------------
HRESULT CBillboardBornStarProc::Load(TCHAR* szFName)
{
	//�e�N�X�`���[�ǂݍ���	�i�p�ӂ���̂̓��\�[�X�r���[�����ł����j
	if (FAILED(m_pGMain->m_pD3D->CreateShaderResourceViewFromFile(szFName, &m_pTexture, m_dwImageWidth, m_dwImageHeight, 3)))
	{
		MessageBox(0, _T("�r���{�[�h�@�e�N�X�`���[��ǂݍ��߂܂���"), szFName, MB_OK);
		return E_FAIL;
	}

	return S_OK;
}

//------------------------------------------------------------------------
//
//	�r���{�[�h�v���V�[�W���̊J�n(���̐����G�t�F�N�g)	
//
//	�E�r���{�[�h�I�u�W�F�N�g�z��̒�����A�󂢂Ă���r���{�[�h��T���ĊJ�n����
//
//  VECTOR3 vPos          �r���{�[�h�̔����ʒu
//
//	�߂�l BOOL
//		TRUE	= ����
//		FALSE	= �ُ�
//
//------------------------------------------------------------------------
BOOL CBillboardBornStarProc::Start(VECTOR3 vPos)
{
	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		if (!m_pObjArray[i]->GetActive())
		{
			m_pObjArray[i]->Start(vPos);
			return TRUE;
		}
	}
	return FALSE;
};


//------------------------------------------------------------------------
//
//	�r���{�[�h�I�u�W�F�N�g�̃R���X�g���N�^(���̐����G�t�F�N�g)	
//
//  �����@�Ȃ�
//
//------------------------------------------------------------------------
CBillboardBornStarObj::CBillboardBornStarObj(CGameMain* pGMain) : CBaseObj(pGMain)
{
	m_pD3D = m_pGMain->m_pD3D;
	m_pShader = m_pGMain->m_pShader;
	m_fDestWidth = 0.0f;
	m_fDestHeight = 0.0f;
	m_dwSrcX = 0;
	m_dwSrcY = 0;
	m_dwSrcWidth = 0;
	m_dwSrcHeight = 0;
	m_vPos = VECTOR3(0, 0, 0);
	m_vUVOffset = VECTOR2(0, 0);
	m_vUVScale = VECTOR2(1, 1);              // -- 2019.7.17
	m_dwNumX = 0;
	m_dwNumY = 0;
	m_dwFrame = 0;
	m_fAlpha = 0.0f;
	m_dwImageWidth = 0;
	m_dwImageHeight = 0;
	m_pVertexBuffer = NULL;
	m_pTexture = NULL;  //�e�N�X�`���[�i�p�ӂ���̂̓��\�[�X�r���[�����ł����j
	//	������
	Init();
}

//------------------------------------------------------------------------
//
//	�r���{�[�h�I�u�W�F�N�g�̃f�X�g���N�^(���̐����G�t�F�N�g)	
//
//------------------------------------------------------------------------
CBillboardBornStarObj::~CBillboardBornStarObj()
{
	SAFE_RELEASE(m_pVertexBuffer);
}
//------------------------------------------------------------------------
//	�r���{�[�h�I�u�W�F�N�g�̏������֐�(���̐����G�t�F�N�g)
//
//  �e��ݒ�l�̏�����
//
//  �����@�@�Ȃ�
//
//  �߂�l�@�@�@�Ȃ�
//------------------------------------------------------------------------
void CBillboardBornStarObj::Init()
{
	m_bActive = FALSE;
	m_fAlpha = 0.9f;
}
//------------------------------------------------------------------------
//
//	�r���{�[�h�I�u�W�F�N�g�̃o�[�e�B�N�X�o�b�t�@�쐬(���̐����G�t�F�N�g)	
//	�i�W�I���g���֘A���������j	
//
//  float fDestWidth         �\����
//  float fDestHeight        �\������
//  DWORD dwSrcX             �X�v���C�g�̈ʒu�@�w���W
//  DWORD dwSrcY             �X�v���C�g�̈ʒu�@�x���W
//  DWORD dwSrcWidth         �X�v���C�g�̕�
//  DWORD dwSrcHeight        �X�v���C�g�̍���
//  DWORD dwNumX             �A�j���[�V����������X�v���C�g�̐��@�w����
//  DWORD dwNumY             �A�j���[�V����������X�v���C�g�̐��@�x����
//
//	�߂�l HRESULT
//		S_OK	= ����
//		E_FAIL	= �ُ�
//
//------------------------------------------------------------------------
HRESULT CBillboardBornStarObj::SetSrc(float fDestWidth, float fDestHeight, DWORD dwSrcX, DWORD dwSrcY, DWORD dwSrcWidth, DWORD dwSrcHeight, DWORD dwNumX, DWORD dwNumY)
{
	// �r���{�[�h�p�̔|���S�����쐬���A�o�[�e�b�N�X�o�b�t�@���쐬����
	m_fDestWidth = fDestWidth;
	m_fDestHeight = fDestHeight;
	m_dwSrcX = dwSrcX;
	m_dwSrcY = dwSrcY;
	m_dwSrcWidth = dwSrcWidth;
	m_dwSrcHeight = dwSrcHeight;
	m_dwNumX = dwNumX;
	m_dwNumY = dwNumY;
	//�o�[�e�b�N�X�o�b�t�@�[�쐬(�������̍��W�ō쐬)
	BILLBOARD_VERTEX vertices[] =
	{
		VECTOR3(-m_fDestWidth / 2,  m_fDestHeight / 2, 0), VECTOR2((float)(m_dwSrcX + m_dwSrcWidth) / m_dwImageWidth, (float)m_dwSrcY / m_dwImageHeight),                     //���_1  ����
		VECTOR3(m_fDestWidth / 2,  m_fDestHeight / 2, 0), VECTOR2((float)m_dwSrcX / m_dwImageWidth,                (float)m_dwSrcY / m_dwImageHeight),                        //���_2�@�E��    // -- 2021.1.11
		VECTOR3(-m_fDestWidth / 2, -m_fDestHeight / 2, 0), VECTOR2((float)(m_dwSrcX + m_dwSrcWidth) / m_dwImageWidth, (float)(m_dwSrcY + m_dwSrcHeight) / m_dwImageHeight),   //���_3�@����    // -- 2021.1.11
		VECTOR3(m_fDestWidth / 2, -m_fDestHeight / 2, 0), VECTOR2((float)m_dwSrcX / m_dwImageWidth,                (float)(m_dwSrcY + m_dwSrcHeight) / m_dwImageHeight),      //���_4�@�E��
	};
	// �Q�x�ڈȍ~�ɏ���������邱�Ƃ̑΍�
	SAFE_RELEASE(m_pVertexBuffer);
	// �o�[�e�b�N�X�o�b�t�@�[�쐬
	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(BILLBOARD_VERTEX) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = vertices;
	if (FAILED(m_pD3D->m_pDevice->CreateBuffer(&bd, &InitData, &m_pVertexBuffer)))
	{
		return E_FAIL;
	}
	return S_OK;
}
//------------------------------------------------------------------------
//
//	�r���{�[�h�I�u�W�F�N�g�̊J�n(���̐����G�t�F�N�g)	
//
//  VECTOR3   vPos     �\���ʒu�i�r���{�[�h�̒��S�_�ʒu���w��j
//
//	�߂�l BOOL
//		TRUE      �\���p��
//		FALSE     �\���I��
//
//------------------------------------------------------------------------
BOOL CBillboardBornStarObj::Start(VECTOR3 vPos)
{
	if (m_bActive) return FALSE;  // ���łɊJ�n��

	m_bActive = TRUE;
	m_dwFrame = 0;
	m_vPos = vPos;

	return TRUE;
}

//------------------------------------------------------------------------
//
//	�r���{�[�h�I�u�W�F�N�g�̍X�V(���̐����G�t�F�N�g)	
//
//	�߂�l �Ȃ�
//
//------------------------------------------------------------------------
void CBillboardBornStarObj::Update()
{
	const DWORD dwSpeed = 5;   // �r���{�[�h�̃A�j���[�V�����X�s�[�h
	DWORD dwIdx;

	if (!m_bActive) return;

	m_dwFrame++;
	dwIdx = m_dwFrame / dwSpeed;

	if (dwIdx >= m_dwNumX * m_dwNumY)	// �p�^�[���̍Ō�ɒB�����Ƃ�
	{
		m_bActive = FALSE;
		return;
	}

	// �A�j���[�V�����̂��߂̃e�N�X�`���I�t�Z�b�g��ݒ肷��
	m_vUVOffset.x = (float)(dwIdx % m_dwNumX * GetSrcWidth());   // �w�����̕ψ�
	m_vUVOffset.y = (float)(dwIdx / m_dwNumX * GetSrcHeight());  // �x�����̕ψ�

	Render();// �����_�����O
	//RenderMesh();// �����_�����O(�����r���{�[�h���b�V��)

}
//------------------------------------------------------------------------
//
//	�r���{�[�h�I�u�W�F�N�g����ʂɃ����_�����O(���̐����G�t�F�N�g)	
//
//	�߂�l BOOL
//		TRUE      �\���p��
//		FALSE     �\���I��
//
//------------------------------------------------------------------------
BOOL CBillboardBornStarObj::Render()
{

	if (!m_bActive) return FALSE;

	//�r���{�[�h�̎��_���������[���h�g�����X�t�H�[�������߂�
	MATRIX4X4 mWorld = GetLookatMatrix(m_vPos, m_pGMain->m_vEyePt);

	//�g�p����V�F�[�_�[�̃Z�b�g
	m_pD3D->m_pDeviceContext->VSSetShader(m_pShader->m_pEffect3D_VS_BILL, NULL, 0);
	m_pD3D->m_pDeviceContext->PSSetShader(m_pShader->m_pEffect3D_PS, NULL, 0);

	//�o�[�e�b�N�X�o�b�t�@�[���Z�b�g
	UINT stride = sizeof(BILLBOARD_VERTEX);
	UINT offset = 0;
	m_pD3D->m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);

	// ���Z�����F�̃u�����f�B���O��ݒ�
	UINT mask = 0xffffffff;
	m_pD3D->m_pDeviceContext->OMSetBlendState(m_pD3D->m_pBlendStateAdd, NULL, mask);

	//�V�F�[�_�[�̃R���X�^���g�o�b�t�@�[�Ɋe��f�[�^��n��
	D3D11_MAPPED_SUBRESOURCE pData;
	CONSTANT_BUFFER_EFFECT cb;
	ZeroMemory(&cb, sizeof(cb));

	if (SUCCEEDED(m_pD3D->m_pDeviceContext->Map(m_pShader->m_pConstantBufferEffect, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{
		//���[���h�A�J�����A�ˉe�s��A�e�N�X�`���[�I�t�Z�b�g��n��
		cb.mWVP = XMMatrixTranspose(mWorld * m_pGMain->m_mView * m_pGMain->m_mProj);

		cb.vUVOffset.x = m_vUVOffset.x / m_dwImageWidth;		// �e�N�X�`���A�j���[�V�����̃I�t�Z�b�g
		cb.vUVOffset.y = m_vUVOffset.y / m_dwImageHeight;		// �e�N�X�`���A�j���[�V�����̃I�t�Z�b�g
		cb.vUVScale.x = 1;
		cb.vUVScale.y = 1;
		cb.fAlpha = m_fAlpha;

		memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(cb));
		m_pD3D->m_pDeviceContext->Unmap(m_pShader->m_pConstantBufferEffect, 0);
	}
	//���̃R���X�^���g�o�b�t�@�[���ǂ̃V�F�[�_�[�Ŏg����
	m_pD3D->m_pDeviceContext->VSSetConstantBuffers(0, 1, &m_pShader->m_pConstantBufferEffect);
	m_pD3D->m_pDeviceContext->PSSetConstantBuffers(0, 1, &m_pShader->m_pConstantBufferEffect);
	//���_�C���v�b�g���C�A�E�g���Z�b�g
	m_pD3D->m_pDeviceContext->IASetInputLayout(m_pShader->m_pEffect3D_VertexLayout_BILL);
	//�v���~�e�B�u�E�g�|���W�[���Z�b�g
	m_pD3D->m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	//�e�N�X�`���[���V�F�[�_�[�ɓn��
	m_pD3D->m_pDeviceContext->PSSetSamplers(0, 1, &m_pD3D->m_pSampleLinear);
	m_pD3D->m_pDeviceContext->PSSetShaderResources(0, 1, &m_pTexture);

	//�v���~�e�B�u�������_�����O
	m_pD3D->m_pDeviceContext->Draw(4, 0);

	// �ʏ�̃u�����f�B���O�ɖ߂�
	m_pD3D->m_pDeviceContext->OMSetBlendState(m_pD3D->m_pBlendStateTrapen, NULL, mask);

	return TRUE;
}

//------------------------------------------------------------------------  // -- 2019.7.17
//
//	�r���{�[�h���b�V������ʂɃ����_�����O���鏈��(���̐����G�t�F�N�g)
//
// ����
//
//	�߂�l HRESULT
//		S_OK	= ����
//		E_FAIL	= �ُ�
//
//------------------------------------------------------------------------
void CBillboardBornStarObj::RenderMesh()
{
	// ���̃Q�[���ɂ͂���Ȃ�
	//�g�p����V�F�[�_�[�̓o�^	
	m_pD3D->m_pDeviceContext->VSSetShader(m_pShader->m_pEffect3D_VS_BILLMESH, NULL, 0);
	m_pD3D->m_pDeviceContext->PSSetShader(m_pShader->m_pEffect3D_PS, NULL, 0);

	//�r���{�[�h�̎��_���������[���h�g�����X�t�H�[�������߂�
	MATRIX4X4 mWorld = GetLookatMatrix(m_vPos, m_pGMain->m_vEyePt);
	// ���b�V���̑傫���Ɋg�傷��ݒ肷��i���X�̃��b�V���͂P���l���̔����j
	MATRIX4X4 mScale = XMMatrixScaling(GetDestWidth(), GetDestHeight(), (GetDestWidth() + GetDestHeight()) / 2);
	mWorld = mScale * mWorld;

	// ���Z�����F�̃u�����f�B���O��ݒ�
	UINT mask = 0xffffffff;
	m_pD3D->m_pDeviceContext->OMSetBlendState(m_pD3D->m_pBlendStateAdd, NULL, mask);

	//�V�F�[�_�[�̃R���X�^���g�o�b�t�@�[�Ɋe��f�[�^��n��	
	D3D11_MAPPED_SUBRESOURCE pData;
	CONSTANT_BUFFER_EFFECT cb;
	if (SUCCEEDED(m_pD3D->m_pDeviceContext->Map(m_pShader->m_pConstantBufferEffect, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{
		//���[���h�A�J�����A�ˉe�s��A�e�N�X�`���[�I�t�Z�b�g��n��
		cb.mWVP = XMMatrixTranspose(mWorld * m_pGMain->m_mView * m_pGMain->m_mProj);

		cb.vUVOffset.x = m_vUVOffset.x / m_dwImageWidth;			// �e�N�X�`���A�j���[�V�����̃I�t�Z�b�g
		cb.vUVOffset.y = m_vUVOffset.y / m_dwImageHeight;			// �e�N�X�`���A�j���[�V�����̃I�t�Z�b�g
		cb.vUVScale.x = (float)GetSrcWidth() / m_dwImageWidth;		// �e�N�X�`���A�j���[�V������1/����
		cb.vUVScale.y = (float)GetSrcHeight() / m_dwImageHeight;	// �e�N�X�`���A�j���[�V������1/�c��

		cb.fAlpha = m_fAlpha;

		memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(cb));
		m_pD3D->m_pDeviceContext->Unmap(m_pShader->m_pConstantBufferEffect, 0);
	}

	//���̃R���X�^���g�o�b�t�@�[���ǂ̃V�F�[�_�[�Ŏg����
	m_pD3D->m_pDeviceContext->VSSetConstantBuffers(0, 1, &m_pShader->m_pConstantBufferEffect);
	m_pD3D->m_pDeviceContext->PSSetConstantBuffers(0, 1, &m_pShader->m_pConstantBufferEffect);

	//���_�C���v�b�g���C�A�E�g���Z�b�g
	m_pD3D->m_pDeviceContext->IASetInputLayout(m_pShader->m_pFbxStaticMesh_VertexLayout);

	//�v���~�e�B�u�E�g�|���W�[���Z�b�g
	m_pD3D->m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//�e�N�X�`���[�T���v���[���V�F�[�_�[�ɓn��
	m_pD3D->m_pDeviceContext->PSSetSamplers(0, 1, &m_pD3D->m_pSampleLinear);

	// ���b�V���̕`�揇�����肷��m_dwRenderIdxArray�̐ݒ�
	m_pMesh->SetRenderIdxArray(mWorld, m_pGMain->m_vEyePt);

	// ���b�V���̐������e�N�X�`���[�A�o�[�e�b�N�X�o�b�t�@�A�C���f�b�N�X�o�b�t�@���Z�b�g���āA�����_�����O����
	for (DWORD mi = 0; mi < m_pMesh->m_dwMeshNum; mi++)
	{
		DWORD i = m_pMesh->m_dwRenderIdxArray[mi];

		//�e�N�X�`���[���V�F�[�_�[�ɓn��
		//m_pD3D->m_pDeviceContext->PSSetShaderResources(0, 1, &m_pMesh->m_pMeshArray[i].m_pTexture);
		m_pD3D->m_pDeviceContext->PSSetShaderResources(0, 1, &m_pTexture);

		// �o�[�e�b�N�X�o�b�t�@�[���Z�b�g
		UINT stride = sizeof(StaticVertexNormal);
		UINT offset = 0;
		m_pD3D->m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pMesh->m_pMeshArray[i].m_pVertexBuffer, &stride, &offset);

		//�C���f�b�N�X�o�b�t�@�[���Z�b�g
		m_pD3D->m_pDeviceContext->IASetIndexBuffer(m_pMesh->m_pMeshArray[i].m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

		//�v���~�e�B�u�������_�����O
		// �i�C���f�b�N�X�̐����w�肵�ă����_�����O�j
		m_pD3D->m_pDeviceContext->DrawIndexed(m_pMesh->m_pMeshArray[i].m_dwIndicesNum, 0, 0);
	}
	// �ʏ�̃u�����f�B���O�ɖ߂�
	m_pD3D->m_pDeviceContext->OMSetBlendState(m_pD3D->m_pBlendStateTrapen, NULL, mask);
}