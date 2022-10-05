//=============================================================================
//		�Q�c�A�N�V�����Q�[���v���O����
//		�b�Q�c�`�����P�P�S�@�@�@�@�@�@           ver 2.8        2020.2.15
//
//		��{�v���V�[�W���E��{�I�u�W�F�N�g�N���X����
//																BaseProc.cpp
//=============================================================================
#include  "BaseProc.h"

//------------------------------------------------------------------------
//
//	��{�v���V�[�W���N���X�̃f�X�g���N�^	
//  �i�S�Ẵv���V�[�W����I�u�W�F�N�g��ǂ݉����č폜����j
//
//  �����@�Ȃ�
//
//------------------------------------------------------------------------
CBaseProc::~CBaseProc()
{
	// �v���V�[�W���|�C���^�z��̍폜
	for (DWORD i = 0; i < m_pProcArray.size(); i++)
	{
		SAFE_DELETE(m_pProcArray[i]);
	}
	// �I�u�W�F�N�g�|�C���^�z��̍폜
	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		SAFE_DELETE(m_pObjArray[i]);
	}
}
//------------------------------------------------------------------------
//
//	��{�v���V�[�W���N���X�̑S�̍X�V����	
//  �i�S�Ẵv���V�[�W����I�u�W�F�N�g��ǂ݉����čX�V����������j
//
//  �����@�Ȃ�
//
//------------------------------------------------------------------------
void CBaseProc::UpdateAll()
{

	Update();                              // �v���V�[�W���̍X�V����
	if (m_nWaitTime > 0) m_nWaitTime--;    // �E�F�C�g�^�C�}�[�̃J�E���g�_�E��

										   // �I�u�W�F�N�g�|�C���^�z��̍X�V
	for (DWORD i = 0; i < m_pObjArray.size(); i++)
	{
		m_pObjArray[i]->Update();          // �I�u�W�F�N�g�̍X�V����
	}

	// ���ʂ̃v���V�[�W���|�C���^�z��̍X�V
	for (DWORD i = 0; i < m_pProcArray.size(); i++)
	{
		m_pProcArray[i]->UpdateAll();      // ���ʂ̃v���V�[�W���̑S�̍X�V�����i�ċA�����j
	}

}

//------------------------------------------------------------------------
//
//  ��{�I�u�W�F�N�g
//	�R���X�g���N�^	
//
//  �����@CGameMain* pGMain  // �Q�[�����C���N���X
//
//------------------------------------------------------------------------
CBaseObj::CBaseObj(CGameMain* pGMain)
{
	// �S�̂̃[���N�����[
	// ���ӓ_�F�N���X���ɂr�s�k��錾���Ă���Ƃ��͎g�p���Ă͂Ȃ�Ȃ�
	ZeroMemory(this, sizeof(CBaseObj));

	m_pGMain = pGMain;			// �Q�[�����C���N���X
	m_dwStatus = NORMAL;
	m_dwStatusSub = NONE;
	m_vCenter.x = -1;			// ��]��X���S�́A�X�v���C�g���S
	m_vCenter.y = -1;			// ��]��Y���S�́A�X�v���C�g���S
	m_fScale = 1.0f;			// �g��k��
	m_fAlpha = 1.0f;			// �����x
	m_nAnimNum = 2;				// �A�j���[�V�����v�f��(�����l�͂Q)
}
//------------------------------------------------------------------------
//
//  ��{�I�u�W�F�N�g
//	�f�X�g���N�^	
//
//------------------------------------------------------------------------
CBaseObj::~CBaseObj()
{
	SAFE_DELETE(m_pSprite);		// �p����̃f�X�g���N�^�Ŏ��s�����Ǝv�����A�O�̂���
}
//------------------------------------------------------------------------
//
//  ��{�I�u�W�F�N�g
//	�X�e�[�^�X�̃��Z�b�g����	
//
//  �����@�Ȃ�
//
//	�߂�l �Ȃ�
//------------------------------------------------------------------------
void  CBaseObj::ResetStatus()
{
	m_dwStatus = NORMAL;		// �X�e�[�^�X
	m_dwStatusSub = WALK;		// �X�e�[�^�X�T�u
	m_dwStatusPhase = 0;		// �X�e�[�^�X�t�F�[�Y
}
//------------------------------------------------------------------------
//
//  ��{�I�u�W�F�N�g
//	�A�j���[�V�����̃��Z�b�g����	
//
//  �����@�Ȃ�
//
//	�߂�l �Ȃ�
//------------------------------------------------------------------------
void  CBaseObj::ResetAnim()
{
	m_nAnimIdx = 0;		// �A�j���[�V�����C���f�b�N�X��
	m_nAnimFrm = 0;		// �A�j���[�V�����t���[���J�E���g
	m_nFlashIdx = 0;		// �t���b�V���A�j���[�V�����C���f�b�N�X��
	m_nFlashFrm = 0;		// �t���b�V���A�j���[�V�����t���[���J�E���g
}
//------------------------------------------------------------------------
//
//  ��{�I�u�W�F�N�g
//	�A�j���[�V�����̃J�E���g�A�b�v����	
//
//  �����@�Ȃ�
//
//	�߂�l int6
//         �A�j���[�V�����p����:0�@�@�@�@�A�j���[�V�����I��:1
//------------------------------------------------------------------------
int  CBaseObj::AnimCountup()
{
	int ret = 0;
	int speed = 10;

	if (m_nAnimNum <= 1) return 1;

	m_nAnimFrm++;
	if (m_nAnimFrm >= speed) {
		m_nAnimFrm = 0;
		m_nAnimIdx++;
		if (m_nAnimIdx >= m_nAnimNum) {
			m_nAnimIdx = 0;
			ret = 1;
		}
	}
	return ret;
}
//------------------------------------------------------------------------
//
//  ��{�I�u�W�F�N�g
//	�t���b�V���A�j���[�V�����̃J�E���g�A�b�v����	
//
//  �����@�Ȃ�
//
//	�߂�l int
//         �A�j���[�V�����p����:0�@�@�@�@�A�j���[�V�����I��:1
//------------------------------------------------------------------------
int  CBaseObj::FlashCountup()
{
	int ret = 0;
	int speed = 2;
	int num = 2;

	m_nFlashFrm++;
	if (m_nFlashFrm >= speed) {
		m_nFlashFrm = 0;
		m_nFlashIdx++;
		if (m_nFlashIdx >= num) {
			m_nFlashIdx = 0;
			ret = 1;
		}
	}
	return ret;
}

//------------------------------------------------------------------------
//
//  ��{�I�u�W�F�N�g
//	�`�惁�\�b�h	
// �i �X�P�[���Ɖ�]���l�����ĕ`��@�j
// �i �X�N���[�����l�����ĕ`��@�j
//
//  �����@�Ȃ�
//
//	�߂�l �Ȃ�
//------------------------------------------------------------------------
void  CBaseObj::Draw()
{
	VECTOR2 vScr = m_pGMain->m_vScroll;  // ---------�X�N���[��
	int cx, cy;
	if (m_bActive) {

		// �����x
		if (m_nFlashIdx == 0)
		{
			m_pSprite->m_vDiffuse.w = m_fAlpha;
		}
		else {
			m_pSprite->m_vDiffuse.w = m_fAlpha * 0.2f; // �����ɋ߂�����
		}

		// �A�j���[�V����
		m_pSprite->m_ofX = m_pSprite->GetDestWidth() * m_nAnimIdx;
		m_pSprite->m_ofY = m_pSprite->GetDestHeight() * m_nDirIdx;

		if (m_fRotate == 0) {	// ��]���Ȃ��Ƃ�

			MATRIX4X4 mWorld, mScale;
			mWorld = XMMatrixTranslation((m_vPos.x + m_vOf.x - vScr.x), (m_vPos.y + m_vOf.y - vScr.y), 0);
			mScale = XMMatrixScaling(m_fScale, m_fScale, 1.0f);
			mWorld = mScale * mWorld;

			// ��ʊO�͕`�悵�Ȃ�
			if (mWorld._41 + m_pSprite->GetDestWidth()*m_fScale  < 0 || mWorld._41 > WINDOW_WIDTH ||
				mWorld._42 + m_pSprite->GetDestHeight()*m_fScale < 0 || mWorld._42 > WINDOW_HEIGHT)
			{
				;
			}
			else {
				m_pSprite->Draw(mWorld);
			}
		}
		else {			// ��]����Ƃ�
			if (m_vCenter.x == -1) {// ��]���S�w���W�̐ݒ�i-1�̂Ƃ��̓L�����N�^���S�j
				cx = m_pSprite->GetDestWidth() / 2;
			}
			else {
				cx = (int)m_vCenter.x;
			}
			if (m_vCenter.y == -1) {// ��]���S�x���W�̐ݒ�i-1�̂Ƃ��̓L�����N�^���S�j
				cy = m_pSprite->GetDestHeight() / 2;
			}
			else {
				cy = (int)m_vCenter.y;
			}

			// ��]�}�g���b�N�X�̍쐬
			MATRIX4X4 mWorld, mCenter, mRot, mScale;
			mWorld = XMMatrixTranslation((m_vPos.x + m_vOf.x - vScr.x), (m_vPos.y + m_vOf.y - vScr.y), 0);
			mScale = XMMatrixScaling(m_fScale, m_fScale, 1.0f);
			mCenter = XMMatrixTranslation(cx, cy, 0);
			mRot = XMMatrixRotationZ(XMConvertToRadians(m_fRotate));
			mWorld = mRot * mCenter * mScale * mWorld;
			mCenter = XMMatrixTranslation(-cx, -cy, 0);
			mWorld = mCenter * mWorld;

			// ��ʊO�͕`�悵�Ȃ�
			if (mWorld._41 + m_pSprite->GetDestWidth()*m_fScale  < 0 || mWorld._41 > WINDOW_WIDTH ||
				mWorld._42 + m_pSprite->GetDestHeight()*m_fScale < 0 || mWorld._42 > WINDOW_HEIGHT)
			{
				;
			}
			else {
				m_pSprite->Draw(mWorld);
			}

		}
	}
}

//------------------------------------------------------------------------
//
//  ��{�I�u�W�F�N�g
//  �I�u�W�F�N�g���m�̏Փ˔��胁�\�b�h�i�X�P�[�����l���j
//
//  ����
//    CBaseObj*  pObj :  �Ώۂ̃I�u�W�F�N�g
//
//	�߂�l BOOL
//        �ڐG���Ă���:TRUE�@�@�@�@�ڐG���Ă��Ȃ�:FALSE
//------------------------------------------------------------------------
BOOL  CBaseObj::isCollision(CBaseObj* pObj)
{
	float ratio = 0.8f; // �ڐG����䗦�B�Ⴆ�΁A0.8�ɂ���ƊO����20%�͐ڐG���肩�珜�O�����B

						// �I�u�W�F�N�g���\������Ă��邱��
	if (!m_bActive || !pObj->m_bActive) return FALSE;

	// �Փ˔���
	BOOL bRet = FALSE;
	DWORD  xd, yd, w1, w2, h1, h2;

	w1 = m_pSprite->GetDestWidth() * m_fScale;
	w2 = pObj->m_pSprite->GetDestWidth() * pObj->m_fScale;
	h1 = m_pSprite->GetDestHeight() * m_fScale;
	h2 = pObj->m_pSprite->GetDestHeight() * pObj->m_fScale;
	xd = abs((long)(((m_vPos.x + m_vOf.x) + w1 / 2) - ((pObj->m_vPos.x + pObj->m_vOf.x) + w2 / 2)));     // ���S�_�Ԃ̋����w����
	yd = abs((long)(((m_vPos.y + m_vOf.y) + h1 / 2) - ((pObj->m_vPos.y + pObj->m_vOf.y) + h2 / 2)));     // ���S�_�Ԃ̋����x����

	if ((xd < (w1 / 2 + w2 / 2)*ratio) &&     // ���S�_�Ԃ̋������I�u�W�F�N�g�̑傫����1/2*ratio��菬������ΐڐG���Ă���
		(yd < (h1 / 2 + h2 / 2)*ratio)) bRet = TRUE;

	return bRet;
}

//------------------------------------------------------------------------
//
//  ��{�I�u�W�F�N�g
//  �I�u�W�F�N�g�ƃN���b�N�ʒu�̏Փ˔��胁�\�b�h�i�X�P�[�����l���j
//
//  ����
//    int nMx :  �}�E�X���W�@�w���W
//    int nMy :  �}�E�X���W�@�x���W
//
//	�߂�l BOOL
//        �q�b�g���Ă���:TRUE�@�@�@�@�q�b�g���Ă��Ȃ�:FALSE
//------------------------------------------------------------------------
BOOL  CBaseObj::isCollisionClick(int nMx, int nMy)
{
	BOOL bRet = FALSE;

	// ��`�̔���
	if (m_bActive && (m_vPos.x + m_vOf.x) <= nMx && (m_vPos.x + m_vOf.x) + (m_pSprite->GetDestWidth() * m_fScale) >= nMx &&
		(m_vPos.y + m_vOf.y) <= nMy && (m_vPos.y + m_vOf.y) + (m_pSprite->GetDestHeight() * m_fScale) >= nMy) bRet = TRUE;

	return bRet;

}
//-----------------------------------------------------------------------------
// ��{�v���V�[�W���N���X�̂����蔻��
//
// �E�S�Ă̑���v���V�[�W���Ƒ���I�u�W�F�N�g��ǂ݉��������蔻����s��
//
//   CBaseObj* pOtherObj      ����̃I�u�W�F�N�g
//
//   �߂�l�@BOOL
//           TRUE:�q�b�g�����Ƃ�       FALSE�F�q�b�g���Ă��Ȃ��Ƃ�
//
//   ���茋�ʁ@�@
//           �q�b�g�����Ƃ��́@�@�@�@����Ǝ����̃I�u�W�F�N�g��m_pOtherObj�ɒl���Z�b�g
//                                   ����Ǝ����̃I�u�W�F�N�g��m_dwStatus��DAMAGE��ݒ肷��
//           �q�b�g���Ă��Ȃ��Ƃ��́@����Ǝ����̃I�u�W�F�N�g��m_pOtherObj��NULL���Z�b�g
//
//-----------------------------------------------------------------------------
BOOL   CBaseProc::Hitcheck(CBaseObj* pOtherObj)
{
	BOOL  bRet = FALSE;

	// �S�Ă̑���Ƃ̂����蔻��
	for (DWORD i = 0; i < m_pObjArray.size(); i++)  // �S�Ă̑���I�u�W�F�N�g
	{
		bRet = m_pObjArray[i]->Hitcheck(pOtherObj);  // ����I�u�W�F�N�g�Ƃ̂����蔻��
		if (bRet) return bRet;
	}

	for (DWORD i = 0; i < m_pProcArray.size(); i++)  // ���ʂ̑���v���V�[�W��
	{
		bRet = m_pProcArray[i]->Hitcheck(pOtherObj);  // ����v���V�[�W���Ƃ̂����蔻��
		if (bRet) return bRet;
	}

	return bRet;
}
//------------------------------------------------------------------------
//
//  ��{�I�u�W�F�N�g
//  �I�u�W�F�N�g���m�̂����蔻�胁�\�b�h
//
//  isCollision���\�b�h���g�p���ăI�u�W�F�N�g���m�̂����蔻����s��
//  �ڐG���Ă���΁A�����̃I�u�W�F�N�g��m_dwStatus�� DAMAGE �ɁA
//  m_pOtherObj�ɑ���̃I�u�W�F�N�g��ݒ肷��B
//
//  ����
//    CBaseObj* pObj:  ����̃I�u�W�F�N�g
//
//	�߂�l BOOL
//        �q�b�g���Ă���:TRUE�@�@�@�@�q�b�g���Ă��Ȃ�:FALSE
//------------------------------------------------------------------------
BOOL  CBaseObj::Hitcheck(CBaseObj* pObj)
{
	if (m_dwStatus == NORMAL && pObj->m_dwStatus == NORMAL && isCollision(pObj))
	{
		m_dwStatus = DAMAGE;
		pObj->m_dwStatus = DAMAGE;
		m_pOtherObj = pObj;
		pObj->m_pOtherObj = this;
		return TRUE;
	}
	return FALSE;
}

//------------------------------------------------------------------------
//
//  ��{�I�u�W�F�N�g
//  �X�v���C�g�̒��S�_�̍��W�����߂�
//
//  ����
//    �Ȃ�
//
//	�߂�l VECTOR2
//        �X�v���C�g���S�_�̍��W
//------------------------------------------------------------------------
VECTOR2  CBaseObj::GetCenterPos()
{
	VECTOR2 vPos = m_vPos;
	if (m_pSprite)
	{
		vPos.x += m_pSprite->GetSrcWidth() / 2;
		vPos.y += m_pSprite->GetSrcHeight() / 2;
	}
	return vPos;
}


//======================================================================
// �ړI�n�itargetX,Y�j�ւ̈ړ�����
//   �����@�@�F�@speed:���̈ړ���
//   �߂�l�@�F�@true�F�ړI�n�ɒB�����@�@false:�܂��ړI�n�ɒB���Ă��Ȃ�
//   �I�u�W�F�N�g�ɐݒ肷��l�@�F�@m_vPosUp�Ɉړ��ʂ�ݒ肷��
//======================================================================
BOOL CBaseObj::TargetMove( float speed)
{
	float mvX, mvY, n;
	BOOL ret = FALSE;

	if (m_vPos.x == m_vTarget.x && m_vPos.y == m_vTarget.y) {  // �ړI�n�ɒB�����Ƃ�
		m_vPosUp.x = 0;
		m_vPosUp.y = 0;
		ret = TRUE; // �ړI�n�ɒB����
	}
	else {    // �ړI�n�ւ̈ړ�����

		mvX = m_vTarget.x - m_vPos.x;   // �ړI�n�܂ł̂w�����̕ψ�
		mvY = m_vTarget.y - m_vPos.y;   // �ړI�n�܂ł̂x�����̕ψ�

		if (abs(mvX) >= abs(mvY)) {   // �w�����̋����������Ƃ�
			if (abs(mvX) < speed) {        // �P��̈ړ��ʂ��ߐڂ��Ă���Ƃ�
				m_vPosUp.x = mvX;
				m_vPosUp.y = mvY;
			}
			else {
				if (mvX >= 0) {
					m_vPosUp.x = speed; // �w�����̈ړ��ʂ�speed�ɂ���
				}
				else {
					m_vPosUp.x = -speed; // �w�����̈ړ��ʂ�-speed�ɂ���
				}
				n = abs(mvX / speed);
				m_vPosUp.y = floor(mvY / n); // �w�����̈ړ��ʂɍ��킹�āA�x�����̈ړ��ʂ�ݒ肷��
			}
		}
		else {                                // �x�����̋����������Ƃ�
			if (abs(mvY) < speed) {        // �P��̈ړ��ʂ��ߐڂ��Ă����
				m_vPosUp.x = mvX;
				m_vPosUp.y = mvY;
			}
			else {
				if (mvY >= 0) {
					m_vPosUp.y = speed; // �x�����̈ړ��ʂ�speed�ɂ���
				}
				else {
					m_vPosUp.y = -speed; // �x�����̈ړ��ʂ�-speed�ɂ���
				}
				n = abs(mvY / speed);
				m_vPosUp.x = floor(mvX / n); // �x�����̈ړ��ʂɍ��킹�āA�w�����̈ړ��ʂ�ݒ肷��
			}
		}
		ret = FALSE;    // �܂��ړI�n�ɒB���Ă��Ȃ�
	}

	return ret;
}
