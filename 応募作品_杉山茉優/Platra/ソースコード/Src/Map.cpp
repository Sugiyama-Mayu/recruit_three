//=============================================================================
//		�R�c�Q�[���v���O���� A
//		�b�R�c�`�����P�P�Q�@�@�@�@�@�@                 ver 3.0        2021.1.11
//		  �}�b�v�̏���
//																	Map.cpp
//=============================================================================
#include  "BaseProc.h"
#include  "Map.h"
#include  "Playchar.h"
#include  "Enemy.h"
#include  "Weapon.h"
#include  "GameMain.h"
#include  "Camera.h"
#include  "BackFore.h"

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

//  ���̓��I�z�u
//M.S �����_�������̔r�o�֐�
// ��  ���F�Ȃ�
// �߂�l�Fint   �r�o���ꂽ1�`4�܂ł̃����_������
int CMapProc::RandomNumMeth() {             
	srand((unsigned int)time(NULL));  // �����_���̏�����
	randomNum = 1 + rand() % 4;       // 1�`4�܂ł̃����_���������擾
	return randomNum;
}
// M.S ���������߁A���̕����ɐi�񂾎��̏c���̈ʒu�r�o
// ��  ���F�Ȃ�
// �߂�l�F�Ȃ�
void CMapProc::DecideDirection() {
	ver = startVertical;              // buf�ɏc�Ɖ�������
	hori = startHorizontal;
	randomNum = RandomNumMeth();      // �����_���������o���A�i�ޕ��������߂�(1������)
	switch (randomNum) {
	case 1:
		up = 1;
		break;
	case 2:
		down = 1;
		break;
	case 3:
		left = 1;
		break;
	case 4:
		right = 1;
	}
	if ((up == 1) || (down == 1)) {      // �c�������Ŋ֐���ʂ�����̖߂�l�̎󂯎���ύX
		hori = outStartNum(up, down, left, right, ver, hori);
	}
	else if ((left == 1) || (right == 1)) {
		ver = outStartNum(up, down, left, right, ver, hori);
	}
}
// M.S �����ɐi�񂾎��̏c���̈ʒu�r�o
// ��  ���Fint up                  1�̏ꍇ�A�r�o��������͏�
//         int down                1�̏ꍇ�A�r�o��������͉�
//         int left                1�̏ꍇ�A�r�o��������͍�
//         int righ                1�̏ꍇ�A�r�o��������͉E
//         int startVertical       �ʒu�����߂�ʒu�̗�
//         int startHorizontal     �ʒu�����߂�ʒu�̍s��
// �߂�l�Fint                     ���߂��ʒu 
//                                 ���߂��Ȃ������ꍇ�A0
int CMapProc::outStartNum(int up, int down, int left, int right, int startVertical, int startHorizontal) {  
	int startVerticalBuf = startVertical;
	int startHorizontalBuf = startHorizontal;
	if (up == 1) {
		startHorizontalBuf -= 2;       // �ʒu�����߂�ꏊ����2�i��
		return startHorizontalBuf;
	}
	else if (down == 1) {
		startHorizontalBuf += 2;
		return startHorizontalBuf;
	}
	else if (left == 1) {
		startVerticalBuf -= 2;
		return startVerticalBuf;
	}
	else if (right == 1) {
		startVerticalBuf += 2;
		return startVerticalBuf;
	}
	return 0;
}
//M.S ���̓��I�����̊֐�
// ��  ���F�Ȃ�
// �߂�l�Fint*          �����������̔z��̃|�C���^
int* CMapProc::MapDynamic()
{
	startVertical = 0;                              // �����l���Z�b�g
	startVertical = 0 + rand() % 5;                 // 0�`4�܂ł̃����_���������擾
	startHorizontal = 0;                            // �����l���Z�b�g   
	startHorizontal = 0 + rand() % 5;               // 0�`4�܂ł̃����_���������擾
	startMap[startHorizontal][startVertical] = 1;   // �������X�^�[�g�Ɍ���(�P������)
	// �������[�v
	while (1) {
		DecideDirection();
		while (1) { // �i�߂�ʒu���m�肷��܂Ŗ������[�v
			// ver��hori��0�`4�ŁA�i�񂾐悪0�������ꍇ�i�z���1������j
			if (ver < 5 && hori < 5 && ver > -1 && hori > -1 && startMap[hori][ver] == 0) {
				// �i�񂾕����ɍ��킹�Ĕz��ɂP������
				if (up == 1) {                 
					if (startMap[hori + 1][ver] != 1) {
						startMap[hori + 1][ver] = 1;
					}
					else {
					}
				}
				else if (down == 1) {
					if (startMap[hori - 1][ver] != 1) {
						startMap[hori - 1][ver] = 1;
					}
					else {
					}
				}
				else if (right == 1) {
					if (startMap[hori][ver - 1] != 1) {
						startMap[hori][ver - 1] = 1;
					}
					else {
					}
				}
				else if (left == 1) {
					if (startMap[hori][ver + 1] != 1) {
						startMap[hori][ver + 1] = 1;
					}
					else {
					}
				}
				arrowSwitch[0] = 0;         // �e��������X�C�b�`�̏�����
				arrowSwitch[1] = 0;
				arrowSwitch[2] = 0;
				arrowSwitch[3] = 0;
				startMap[hori][ver] = 1;       // �i�񂾐�ɂP������
				startHorizontal = hori;        // �ʒu�̍X�V
				startVertical = ver;
				break;
			}
			else { // �i�񂾐悪0�ȊO(�z�u�ς�)�������ꍇ(�z���1�����Ȃ�)
				// ������S�Ď����Ă��i�߂�������Ȃ����ǂ���
				if (arrowSwitch[0] == 1 && arrowSwitch[1] == 1 && arrowSwitch[2] == 1 && arrowSwitch[3] == 1) {
					int* startMapP;
					startMapP = &startMap[0][0];  // startMapP��startMap�z��̃A�h���X������
					return startMapP;
				}
				if (up == 1) {   // �����ϐ��̏�����
					up = 0;
				}
				else if (down == 1) {
					down = 0;
				}
				else if (left == 1) {
					left = 0;
				}
				else if (right == 1) {
					right = 0;
				}
				randomNum = RandomNumMeth(); // �����_�������̔r�o
				switch (randomNum) {
				case 1:
					up = 1;
					arrowSwitch[0] = 1;       // �ς񂾕����Ɋm�F�ς݂�1������
					break;
				case 2:
					down = 1;
					arrowSwitch[1] = 1;
					break;
				case 3:
					left = 1;
					arrowSwitch[2] = 1;
					break;
				case 4:
					right = 1;
					arrowSwitch[3] = 1;
				}
				ver = startVertical;
				hori = startHorizontal;
				if ((up == 1) || (down == 1)) {   // �c�������Ŋ֐���ʂ�����̖߂�l�̎󂯎���ύX
					hori = outStartNum(up, down, left, right, ver, hori);
				}
				else if ((left == 1) || (right == 1)) {
					ver = outStartNum(up, down, left, right, ver, hori);
				}
			}
		}
	}
}
//=============================================================================
//
// �}�b�v�v���V�[�W���̃R���X�g���N�^
//
//-----------------------------------------------------------------------------
CMapProc::CMapProc(CGameMain*	pGMain)
{
	// �N���X�S�̂̃N�����[
	// (vector�N���X�͏������s�v)
	m_pGMain = pGMain;
	m_dwMapNo = 1;
	m_bActive = FALSE;
	m_pColMesh = NULL;					// �R���W�������b�V���ւ̃|�C���^
	m_nEvtIdx = 0;							// -- 2021.2.4
	// M.S �������牺�̃R���X�g���N�^�̓��e�͒ǉ����܂���
	// M.S ��--------------------------------------------------------------------
	mapStarArrayBuf = MapDynamic(); // ���̓��I�����z��̍쐬
	up = 0;                         // ���̓��I�����Ŏg�������ϐ�
	down = 0;
	right = 0;
	left = 0;                 
	startVertical = 0;              // ���̓��I�����Ɏg�p����z��̗�
	startHorizontal = 0;            // ���̓��I�����Ɏg�p����z��̍s
	ver = startVertical;            // ���̓��I�����Ɏg�p����z��̗�buf
	hori = startHorizontal;         // ���̓��I�����Ɏg�p����z��̍sbuf
	randomNum = 0;                  //RandomNumMeth()�Ŏg�p����ϐ�
	// �Q�[�����Ɏg�p����ϐ�
	lineMap1[4][4] = 5;             // �����v���C���[�ʒu
	ChangeButton = 0;               // �z�u���̕ύX����
    trainNumSt = 0;                 // �e���H�̔z�u��
	trainNumSd = 0;
	trainNumCg = 0;
	trainNumSta = 0;
	oldH = m_pGMain->initialH;      // ���̔z�u���̈ʒu�̕ۑ�
	oldV = m_pGMain->initialV;
	LineChangeFlag = 0;             // 0:���� 1:�� 2:�E 3:�� 4:��
	changeNum = 0;					// �����]�����H�̕����ϐ�1
	aboutArrow = 0;                 // �����]�����H�̕����ϐ�2
	typeChangeNum = 1;              // �z�u�\�Ȑ��H�̐���
	starRotateSwitch = 0;           // ���̉�]�����Ԓʂ�ɏ�������ׂ̕ϐ�
	pointArrow1 = 0;                // ���̉�]�p�x�����߂邽�߂̕ϐ�
	pointArrow2 = 0;
	pointArrow3 = 0;
	pointArrow4 = 0;
	sideDegree = 0.0f;              // ���̉�]�p�x�̕ۑ�(����])
	heightDegree = 0.0f;            // ���̉�]�p�x�̕ۑ�(�c��])
	rotateFinish = false;           // ��]�����I���t���O
	surfaceMap = 0;                 // ���ʂɂ���ʂ̐���
	pointArrowNum1 = 0;             // pointArrow�ϐ��̌v�Z���ʂ̕ۑ��ϐ�
	pointArrowNum2 = 0;
	setOk = false;                  // �z��̏������݁A�ǂݍ��݂����Ԓʂ�ɂ���ϐ�
	northNow = 0;                   // ���݂̐��̖ʂ̉�]�i�k�j�̈ʒu�ۑ��ϐ�
    horiRotate = 0;                 // ��]��̃J�[�\���̈ʒu��z��ɍ��킹�����̂ɂ��ĕۑ�����ϐ�(�s)
	verRotate = 0;                  // ��]��̃J�[�\���̈ʒu��z��ɍ��킹�����̂ɂ��ĕۑ�����ϐ�(��)
	oldRotateSurface = 0;           // �ۑ�����ׂ��ʂ������ϐ�
	PlacementSurfaceNum = 0;        // �Ō�ɑ��삵���}�b�v�ʂ̕ۑ��ϐ�
	newSurfacePlacement = false;    // ���̃}�b�v�ʂւ̔z�u����
	permissionH = 0;               // ���̃}�b�v�ʂւ̔z�u���p�̃N���b�N�ʒu�ϐ�
	permissionV = 0;
	doneManPlacement = true;       // �l�̔z�u�������������ǂ����̃t���O
	// �}�b�v�̉�]�ɍ��킹�ăI�u�W�F�N�g�̈ړ����I��������ǂ���
	rotateProcessDoneFlag = true;  // ��]�����̃I�u�W�F�N�g�̉�]�Ȃǂ��I������̂��t���O
	arrayHNum = 0;                 // ��]�p�̊e�l�L�����N�^�[�̐�
	arrayMNum = 0;
	arrayLNum = 0;
	front = VECTOR3(0.0f, 10.0f, 0.0f);   // �ʒu�𒲂ׂ邽�߂̃o�E���f�B���O�{�b�N�X�̈ʒu�ϐ�
	back  = VECTOR3(0.0f, 1.5f, 0.0f);
	starBridgeLitingTime = 0;   // ���̉˂��������点��J�E���g�ϐ�
	starBridgePosNum = 1;       // ���񂾂񋴂����点��ׂ̋��ړ��p�ϐ�
	changeButtonWithinRange = false; // �z�u������H���͈͓����ǂ����̃t���O
	surfaceMapLineJudge = 0;         // ���݂̑���ʃ}�b�v
	linePlacementOkFlag = true;      // �z�u���������t���O
	SaveRotateSurfaceFlag = false;   // �}�b�v�ʂ̕ۑ��A�X�V�����t���O
	waitTime = 0;                    // �������̃G�t�F�N�g�̃^�C���J�E���g
	saveHori = 0;                    // �������̃G�t�F�N�g�Ɏg�p����z��v�f�ԍ�(�s)
	saveVer = 0;                     // �������̃G�t�F�N�g�Ɏg�p����z��v�f�ԍ�(��)
	starEffectOrder = 0;             // �������̃G�t�F�N�g�̃t�F�[�Y
	starObjArrayNum = 0;             // �����������������G�t�F�N�g�̐�	
	// �}�b�v3�̐��̉˂����̔z�u����
	starBridgePermission = false;  // ���̉˂����z�u����
	starBridgeInputFlag = false;   // �N���b�N�������t���O
	NearStarCol = false;           // ��O�̐��ƃ}�E�X�̐ڐG�t���O
	frontStarCol = false;          // ���̐��ƃ}�E�X�̐ڐG�t���O
}
//-----------------------------------------------------------------------------
//
// �}�b�v�v���V�[�W���̃f�X�g���N�^
//
//-----------------------------------------------------------------------------
CMapProc::~CMapProc()
{
	DestroyAll();
}

//-----------------------------------------------------------------------------
//
// �}�b�v�̍폜
//
//-----------------------------------------------------------------------------
void CMapProc::DestroyAll()
{
	m_bActive = FALSE;
	m_nEvtIdx = 0;							// -- 2021.2.4

	// ���b�V���̃f���[�g
	for(DWORD i = 0; i<m_SkyMap.size(); i++)
	{
		SAFE_DELETE(m_SkyMap[i].m_pMesh);
		SAFE_DELETE(m_SkyMap[i].m_pWave);    // �g�p���Ă��Ȃ����O�̂��ߍ폜
	}
	for(DWORD i = 0; i<m_StageMap.size(); i++)
	{
		SAFE_DELETE(m_StageMap[i].m_pMesh);
		SAFE_DELETE(m_StageMap[i].m_pWave);
		SAFE_DELETE(m_StageMap[i].m_pBBox);
	}
	for (DWORD i = 0; i<m_MoveMap.size(); i++)
	{
		SAFE_DELETE(m_MoveMap[i].m_pMesh);
		SAFE_DELETE(m_MoveMap[i].m_pColMesh);
	}
	for (DWORD i = 0; i < m_EventMap.size(); i++)   // -- 2021.2.4
	{
		SAFE_DELETE(m_EventMap[i].m_pBBox);
	}
	SAFE_DELETE(m_pColMesh);

	m_dwMapNo = 0;
	// vector�̍폜
	m_SkyMap.clear();					// ��̃}�b�v  �z��폜
	m_SkyMap.shrink_to_fit();			// ��̃}�b�v  �s�v���������
	m_StageMap.clear();					// �X�e�[�W�̃}�b�v  �z��폜
	m_StageMap.shrink_to_fit();			// �X�e�[�W�̃}�b�v �s�v���������
	m_MoveMap.clear();					// �ړ��}�b�v  �z��폜
	m_MoveMap.shrink_to_fit();			// �ړ��}�b�v �s�v���������
	m_NavMap.clear();					// �i�r�Q�[�V�����}�b�v�z��폜
	m_NavMap.shrink_to_fit();			// �i�r�Q�[�V�����}�b�v�s�v���������
	m_EventMap.clear();					// �C�x���g�}�b�v�z��폜
	m_EventMap.shrink_to_fit();			// �C�x���g�}�b�v�s�v���������
}
// M.S �Q�[���̏�����������֐�
// ��  ���F�Ȃ�
// �߂�l�F�Ȃ�
void CMapProc::ResetNewGameMap() {
	for (int hori = 0; hori < 10; hori++) {
		for (int ver = 0; ver < 10; ver++) {
			lineMap1[hori][ver] = 0 ;      // ����p�̃}�b�v�z��
			lineMapBuf1[hori][ver] = 0;    // ������Ԃł����瑤�̖�
			lineMapBuf2[hori][ver] = 0;    // �����瑤�̂��̉��̖�
			lineMapBuf3[hori][ver] = 0;    // ��ԉ��̖�
			lineMapBuf4[hori][ver] = 0;    // lineMapBuf2�̗���
			lineMapBuf5[hori][ver] = 0;    // �����̖�
			lineMapBuf6[hori][ver] = 0;    // �E���̖�
		}
	}
	for (int hori = 0; hori < 5; hori++) {  // ���̓��I�z��̏�����
		for (int ver = 0; ver < 5; ver++) {
			startMap[hori][ver] = 0;
		}
	}
	lineMap1[4][4] = 5;           // ���C���}�b�v�̃v���C���[�̈ʒu
	up = 0;                       // �����I�����̌����@������p�ϐ�
	down = 0;
	right = 0;
	left = 0;                     // �����ϐ�
	startVertical = 0;            // ���̓��I�����Ɏg�p����z��̗�
	startHorizontal = 0;          // ���̓��I�����Ɏg�p����z��̍s
	ver = startVertical;          // ���̓��I�����Ɏg�p����z��̗�buf
	hori = startHorizontal;       // ���̓��I�����Ɏg�p����z��̍sbuf
	arrowSwitch[4] = { 0 };       // �ǂ̕������I��������̔���p�z��
	ChangeButton = 0;             //�z�u���̕ύX����
	trainNumSt = 0;               // �e���H�̔z�u��
	trainNumSd = 0;
	trainNumCg = 0;
	trainNumSta = 0;
	oldH = m_pGMain->initialH;    // ���̔z�u���̈ʒu�̋L��
	oldV = m_pGMain->initialV;
	LineChangeFlag = 0;           // 0:���� 1:�� 2:�E 3:�� 4:��
	changeNum = 0;                // �����]�����H�̕����ϐ�1
	aboutArrow = 0;               // �����]�����H�̕����ϐ�2
	typeChangeNum = 1;            // �z�u�\�Ȑ��H�̐���
	starRotateSwitch = 0;         // ���̉�]�����Ԓʂ�ɏ�������ׂ̕ϐ�
	pointArrow1 = 0;              // ���̉�]�p�x�����߂邽�߂̕ϐ�
	pointArrow2 = 0; 
	pointArrow3 = 0;
	pointArrow4 = 0;
	sideDegree = 0.0f;            // ���̉�]�p�x�̕ۑ�(����])
	heightDegree = 0.0f;          // ���̉�]�p�x�̕ۑ�(�c��])         
	rotateFinish = false;         // ��]�����I���t���O
	pointArrowNum1 = 0;           // pointArrow�ϐ��̌v�Z���ʂ̕ۑ��ϐ�
	pointArrowNum2 = 0;
	setOk = false;                // �z��̏������݁A�ǂݍ��݂����Ԓʂ�ɂ���ϐ�
	northNow = 0;                 // ���݂̐��̖ʂ̉�]�i�k�j�̈ʒu�ۑ��ϐ�
	horiRotate = 0;               // ��]��̃J�[�\���̈ʒu��z��ɍ��킹�����̂ɂ��ĕۑ�����ϐ�(�s)
	verRotate = 0;                // ��]��̃J�[�\���̈ʒu��z��ɍ��킹�����̂ɂ��ĕۑ�����ϐ�(��)
	oldRotateSurface = 0;         // �ۑ�����ׂ��ʂ������ϐ�
	PlacementSurfaceNum = 0;      // �Ō�ɑ��삵���}�b�v�ʂ̕ۑ��ϐ�
	newSurfacePlacement = false;  // ���̃}�b�v�ʂւ̔z�u����
    saveHori = 0;                 // �����I�������ɃG�t�F�N�g�𔭐����邽�߂Ɋm�F�����ꏊ�̕ۑ�
	saveVer = 0;
	permissionH = 0;               // ���̃}�b�v�ʂւ̔z�u���p�̃N���b�N�ʒu�ϐ�
	permissionV = 0;
	SaveRotateSurfaceFlag = false; // ���̃}�b�v�ʂ̕ۑ��t���O
	doneManPlacement = true;
	// �}�b�v�̉�]�ɍ��킹�ăI�u�W�F�N�g�̈ړ����I��������ǂ���
	rotateProcessDoneFlag = true;
	arrayHNum = 0;                 // ��]�p�̊e�l�L�����N�^�[�̐�
	arrayMNum = 0;
	arrayLNum = 0;
	// PlayChar�̃��Z�b�g
	m_pGMain->m_pPcProc->ResetNewGamePc();
	// Man�̃��Z�b�g
	m_pGMain->m_pEnmProc->ResetNewGameMan();
	// GameMain�̃��Z�b�g
	m_pGMain->rotateFlag = false;
	// ���݂̑���}�b�v�̈ʒu
	surfaceMap = 0;
	// ���̉˂����̃I�u�W�F�N�g�̈ړ��p�ϐ�
	starBridgePosNum = 1;
    // ���̉˂����Q�[�W�̃L���L���̃A�j���[�V�������̏�����
	m_pGMain->m_pBackForeProc->glitterAnimNum = 0;
	// �Z�[�u�������t���O�̏�����
	m_pGMain->m_pBackForeProc->doneBridgeSound = false;
	starBridgeLitingTime = 0;                 // ���̉˂��������点��J�E���g�ϐ�
	changeButtonWithinRange = false;          // �z�u������H���͈͓����ǂ����̃t���O
}
//-----------------------------------------------------------------------------
//
// �}�b�v�P�̉���������
//		m_bActive	0	int
//-----------------------------------------------------------------------------
void CMapProc::LoadMap1()
{
	// vector�������p�̍\����
	const STAGEMAP      sm;
	const MOVEMAP       mm;
	const NAVIGATIONMAP nv;
	//	M.S ���I�����������z��̃|�C���^�����炵���̂�mapStarArray�z��ɓ����
	for (int hori = 0; hori < 5; hori++) {
		for (int ver = 0; ver < 5; ver++) {
			mapStarArray[hori][ver] = *mapStarArrayBuf;
			mapStarArrayBuf++;
		}
	}
	// �S�}�b�v�̍폜 -----------------------------------------------
	DestroyAll();
	// �S�Ă̓G�E����E���ʂ̔�\���� 
	m_pGMain->m_pEnmProc->SetNonActive();
	m_pGMain->m_pWeaponProc->SetNonActive();
	m_pGMain->m_pEffectProc->SetNonActive();
	m_pGMain->m_pEnmProc->ResetEnmNum();      // �G�̔������̃��Z�b�g
	// �o�b��(0,0,-20)�̈ʒu�ɒu�� -------------------------------------
	m_pGMain->m_pPcProc->GetPcObjPtr()->SetWorld(XMMatrixTranslation(-5.0f, 70.0f, -0.0f));   // ���[���h���W�ł��}�b�v�Ɠ������W
	m_pGMain->m_pPcProc->GetPcObjPtr()->SetWorldOld(m_pGMain->m_pPcProc->GetPcObjPtr()->GetWorld());
	m_pGMain->m_pPcProc->GetPcObjPtr()->SetLocalRotY(0.0f);  // ���[�J����(Y��)��0�x�ɂ���
	m_pGMain->transparentSwitch = true;
	// �X�e�[�W�}�b�v�̐ݒ�E�R���W�����}�b�v�̐ݒ� -----------------------------------------
	m_pColMesh = new CCollision(m_pGMain->m_pFbxMeshCtrl);     // �R���W�����}�b�v�̐���	
	int arrayNum = 0;
	// M.S �t�@�C���������ݗp�z��̏�����
	for (int arrayNum = 0; arrayNum < 25; arrayNum++) {
		m_pGMain->starArray[arrayNum] = 0;
	}
	int i = 0;
	// M.S ���I�����������̏���ۑ�
	for (int hori = 0; hori < 5; hori++) {
		for (int ver = 0; ver < 5; ver++) {
			// M.S ���z��1�Ȃ��
			if (mapStarArray[hori][ver] == 1) {
				// M.S 5.0f�̕ς����ŕ����ς�� -�Z�̑����Ń��f�������E�ɓ���
				// M.S -5.0�̕ς����ŕ����ς�� +�Z�𑝂₷�Ə�Ƀ��f��������
				float starSetX = 5.0f*ver + 10.0f*ver;    
				float starSetZ = -5.0f*hori - 10.0f*hori;  
				m_StageMap.push_back(sm);
				// M.S ���̍쐬
				m_StageMap[i].m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Map/EarthStar/earthStar.mesh"));
				m_StageMap[i].m_mWorld = XMMatrixTranslation(0, 0.0f, 100);
				m_StageMap[i].m_pBBox = new CBBox(m_pGMain->m_pShader, m_StageMap[i].m_pMesh->m_vMin/*vmin*/, m_StageMap[i].m_pMesh->m_vMax); // xyz�Pm�̃I�u�W�F�N�g
				m_StageMap[i].m_pBBox->m_mWorld = m_StageMap[i].m_mWorld;
				m_pColMesh->AddFbxLoad(_T("Data/Map/EarthStar/earthStar.mesh"), VECTOR3(0, 0.0f, 100)); // �h�A���b�V���R���W�����̐ݒ�
				m_pGMain->haveToGoStar++;   // M.S �s���Ȃ���΂Ȃ�Ȃ����̐��𑫂�
				m_pGMain->starArray[i] = 1; // M.S �t�@�C���������ݗp�z��ɓ����
				i++;
			}
			else {
			}
		}
	}
	// ��p  -----------------------------------------------------------
	// ��}�b�v�̐ݒ�[0]
	m_SkyMap.push_back(sm);
	m_SkyMap[0].m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Map/GalaxyBack/galaxyBackGround.mesh"));
	m_SkyMap[0].m_mWorld = XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	// �t�@�C���̏�������
	m_pGMain->FileWrite();
	// �}�b�v�m�n�P
	m_dwMapNo = 1;
	m_bActive = TRUE;
}
// M.S �o�^����z�u���̐�
const int MAX_SET = 600;
// M.S �c�̐��H(TrainLineStProc)�̃R���X�g���N�^
// ��  ���FGameMain�̃|�C���^
TrainLineStProc::TrainLineStProc(CGameMain* pGMain)
{
	m_pGMain = pGMain;
	// ���b�V���̐ݒ�
	m_pMesh = new CFbxMesh(pGMain->m_pFbxMeshCtrl, _T("Data/Map/Line/trainLine.mesh"));
	for (int i = 0; i < MAX_SET; i++) {
		m_pTLSObjArray.push_back(new TrainLineStObj(m_pGMain));
		m_pTLSObjArray[i]->SetLineNum(1);            // �z�u���ԍ��̓o�^
		m_pTLSObjArray[i]->SetMesh(this);            // ���b�V���A�h���X�̓o�^
	}
}
// M.S �c�̐��H(TrainLineStProc)�̃f�X�g���N�^
TrainLineStProc::~TrainLineStProc() {

}
// M.S ���̐��H(TrainLineSdProc)�̃R���X�g���N�^
// ��  ���FGameMain�̃|�C���^
TrainLineSdProc::TrainLineSdProc(CGameMain* pGMain)
{
	m_pGMain = pGMain;
	// ���b�V���̐ݒ�
	m_pMesh = new CFbxMesh(pGMain->m_pFbxMeshCtrl, _T("Data/Map/Line/trainLineSide.mesh"));
	for (int i = 0; i < MAX_SET; i++) {
		m_pTLSDObjArray.push_back(new TrainLineSdObj);
		m_pTLSDObjArray[i]->SetLineNum(1);            // �z�u���ԍ��̓o�^
		m_pTLSDObjArray[i]->SetMesh(this);            // ���b�V���A�h���X�̓o�^
	}
}
// M.S ���̐��H(TrainLineSdProc)�̃f�X�g���N�^

TrainLineSdProc::~TrainLineSdProc() {

}
// M.S �����؂�ւ����H(TrainLineCgProc)�̃R���X�g���N�^
// ��  ���FGameMain�̃|�C���^
TrainLineCgProc::TrainLineCgProc(CGameMain* pGMain)
{
	m_pGMain = pGMain;
	// ���b�V���̐ݒ�
	m_pMesh = new CFbxMesh(pGMain->m_pFbxMeshCtrl, _T("Data/Map/Line/trainLine_Big_Center.mesh"));
	for (int i = 0; i < MAX_SET; i++) {
		m_pTCGObjArray.push_back(new TrainLineCgObj);
		m_pTCGObjArray[i]->SetLineNum(2);            // �z�u���ԍ��̓o�^
		m_pTCGObjArray[i]->SetMesh(this);            // ���b�V���A�h���X�̓o�^
	}
}
// M.S �����؂�ւ����H(TrainLineCgProc)�̃f�X�g���N�^
TrainLineCgProc::~TrainLineCgProc() {

}
// M.S �w(TrainLineStationProc)�̃R���X�g���N�^
// ��  ���FGameMain�̃|�C���^
TrainLineStationProc::TrainLineStationProc(CGameMain* pGMain)
{
	m_pGMain = pGMain;
	// ���b�V���̐ݒ�
	m_pMesh = new CFbxMesh(pGMain->m_pFbxMeshCtrl, _T("Data/Map/Line/station.mesh"));
	for (int i = 0; i < MAX_SET; i++) {
		m_pTLSTAObjArray.push_back(new TrainLineStationObj);
		m_pTLSTAObjArray[i]->SetLineNum(3);            // �z�u���ԍ��̓o�^
		m_pTLSTAObjArray[i]->SetMesh(this);            // ���b�V���A�h���X�̓o�^
	}
}
// M.S �w(TrainLineStationProc)�̃f�X�g���N�^
TrainLineStationProc::~TrainLineStationProc() {

}
// M.S �c�̐��H(TrainLineStObj)�̃R���X�g���N�^
// ��  ���FGameMain�̃|�C���^
TrainLineStObj::TrainLineStObj(CGameMain* pGMain) {
}
// M.S �c�̐��H(TrainLineStObj)�̃f�X�g���N�^
TrainLineStObj::~TrainLineStObj() {

}
// M.S ���̐��H(TrainLineSdObj)�̃R���X�g���N�^
// ��  ���F�Ȃ�
TrainLineSdObj::TrainLineSdObj() {

}
// M.S ���̐��H(TrainLineSdObj)�̃f�X�g���N�^
TrainLineSdObj::~TrainLineSdObj() {

}
// M.S �����؂�ւ����H(TrainLineCgObj)�̃R���X�g���N�^
// ��  ���F�Ȃ�
TrainLineCgObj::TrainLineCgObj() {

}
// M.S �����؂�ւ����H(TrainLineCgObj)�̃f�X�g���N�^
TrainLineCgObj::~TrainLineCgObj() {

}
// M.S �w(TrainLineStationObj)�̃R���X�g���N�^
// ��  ���F�Ȃ�
TrainLineStationObj::TrainLineStationObj() {

}
// M.S �w(TrainLineStationObj)�̃f�X�g���N�^
TrainLineStationObj::~TrainLineStationObj() {

}
// M.S �e�ʂ�1�z�u����BBox�̍쐬�A�z�u
// ��  ���F�Ȃ�
// �߂�l�F�Ȃ�
void CMapProc::MakeFrontBBox(){
  //  ���ʂɌ����Ă���ʂ̔���BBox
  // ������Ԃ�y���̃v���X�����̖ʂɔz�u����BBox
  m_pBBoxPosition[0] = 
  new CBBox(m_pGMain->m_pShader, /*Min*/VECTOR3(-0.5, -0.5, -0.5),/*Max*/VECTOR3(0.5, 0.5, 0.5)); 
  // ������Ԃ�z���̃}�C�i�X�����̖ʂɔz�u����BBox
  m_pBBoxPosition[1] = 
  new CBBox(m_pGMain->m_pShader, /*Min*/VECTOR3(-0.5, -0.5, -0.5),/*Max*/VECTOR3(0.5, 0.5, 0.5)); 
  // ������Ԃ�y���̃}�C�i�X�����̖ʂɔz�u����BBox
  m_pBBoxPosition[2] =
  new CBBox(m_pGMain->m_pShader, /*Min*/VECTOR3(-0.5, -0.5, -0.5),/*Max*/VECTOR3(0.5, 0.5, 0.5)); 
  // ������Ԃ�z���̃v���X�����̖ʂɔz�u����BBox
  m_pBBoxPosition[3] = 
  new CBBox(m_pGMain->m_pShader, /*Min*/VECTOR3(-0.5, -0.5, -0.5),/*Max*/VECTOR3(0.5, 0.5, 0.5));
  // ������Ԃ�x���̃v���X�����̖ʂɔz�u����BBox
  m_pBBoxPosition[4] = 
  new CBBox(m_pGMain->m_pShader, /*Min*/VECTOR3(-0.5, -0.5, -0.5),/*Max*/VECTOR3(0.5, 0.5, 0.5));
  // ������Ԃ�x���̃}�C�i�X���̖ʌ��ɔz�u����BBox
  m_pBBoxPosition[5] = 
  new CBBox(m_pGMain->m_pShader, /*Min*/VECTOR3(-0.5, -0.5, -0.5),/*Max*/VECTOR3(0.5, 0.5, 0.5));

  // �����BBox���e�ʂɔz�u����
  m_pBBoxPosition[0]->m_mWorld = XMMatrixTranslation(0.0f, 5.0f, 0.0f);  
  m_pBBoxPosition[1]->m_mWorld = XMMatrixTranslation(0.0f, 0.0f, -5.0f); 
  m_pBBoxPosition[2]->m_mWorld = XMMatrixTranslation(0.0f, -5.0f, 0.0f); 
  m_pBBoxPosition[3]->m_mWorld = XMMatrixTranslation(0.0f, 0.0f, 5.0f);  
  m_pBBoxPosition[4]->m_mWorld = XMMatrixTranslation(5.0f, 0.0f, 0.0f);  
  m_pBBoxPosition[5]->m_mWorld = XMMatrixTranslation(-5.0f, 0.0f, 0.0f); 
}
// M.S �e�ʂ�4�z�u����BBox(�ʂ̉�]�����邽��)�̍쐬
// ��  ���F�Ȃ�
// �߂�l�F�Ȃ�
void CMapProc::MakeSurfaceBBox() {
	for (int ar = 0; ar < 4; ar++) {
		m_pBBoxArrow1[ar] =
			new CBBox(m_pGMain->m_pShader, /*Min*/VECTOR3(-0.5, -0.5, -0.5),/*Max*/VECTOR3(0.5, 0.5, 0.5));
	}
	for (int ar = 0; ar < 4; ar++) {
		m_pBBoxArrow2[ar] =
			new CBBox(m_pGMain->m_pShader, /*Min*/VECTOR3(-0.5, -0.5, -0.5),/*Max*/VECTOR3(0.5, 0.5, 0.5));
	}
	for (int ar = 0; ar < 4; ar++) {
		m_pBBoxArrow3[ar] =
			new CBBox(m_pGMain->m_pShader, /*Min*/VECTOR3(-0.5, -0.5, -0.5),/*Max*/VECTOR3(0.5, 0.5, 0.5));
	}
	for (int ar = 0; ar < 4; ar++) {
		m_pBBoxArrow4[ar] =
			new CBBox(m_pGMain->m_pShader, /*Min*/VECTOR3(-0.5, -0.5, -0.5),/*Max*/VECTOR3(0.5, 0.5, 0.5));
	}
	for (int ar = 0; ar < 4; ar++) {
		m_pBBoxArrow5[ar] =
			new CBBox(m_pGMain->m_pShader, /*Min*/VECTOR3(-0.5, -0.5, -0.5),/*Max*/VECTOR3(0.5, 0.5, 0.5));
	}
	for (int ar = 0; ar < 4; ar++) {
		m_pBBoxArrow6[ar] =
			new CBBox(m_pGMain->m_pShader, /*Min*/VECTOR3(-0.5, -0.5, -0.5),/*Max*/VECTOR3(0.5, 0.5, 0.5));
	}
}
// M.S �e�ʂ�4�z�u����BBox(�ʂ̉�]�����邽��)�̔z�u
// ��  ���F�Ȃ�
// �߂�l�F�Ȃ�
void CMapProc::SetPosSurfaceBBox(){
	// ������Ԃ�y���̃v���X�����̖ʂɔz�u����BBox
	for (int ar = 0; ar < 4; ar++) {
		switch (ar) {
		case 0:
			m_pBBoxArrow1[ar]->m_mWorld = XMMatrixTranslation(0.0f, 6.0f, 4.0f);  // ��
			break;
		case 1:
			m_pBBoxArrow1[ar]->m_mWorld = XMMatrixTranslation(0.0f, 6.0f, -4.0f); // ��
			break;
		case 2:
			m_pBBoxArrow1[ar]->m_mWorld = XMMatrixTranslation(4.0f, 6.0f, 0.0f);  // �E
			break;
		case 3:
			m_pBBoxArrow1[ar]->m_mWorld = XMMatrixTranslation(-4.0f, 6.0f, 0.0f); // ��
			break;
		}
	}
// ������Ԃ�z���̃v���X�����̖ʂɔz�u����BBox
	for (int ar = 0; ar < 4; ar++) {
		switch (ar) {
		case 0:
			m_pBBoxArrow2[ar]->m_mWorld = XMMatrixTranslation(0.0f, -4.0f, 6.0f);  // ��
			break;
		case 1:
			m_pBBoxArrow2[ar]->m_mWorld = XMMatrixTranslation(0.0f, 4.0f, 6.0f); // ��
			break;
		case 2:
			m_pBBoxArrow2[ar]->m_mWorld = XMMatrixTranslation(4.0f, 0.0f, 6.0f);  // �E
			break;
		case 3:
			m_pBBoxArrow2[ar]->m_mWorld = XMMatrixTranslation(-4.0f, 0.0f, 6.0f); // ��
			break;
		}
	}
// ������Ԃ�y���̃}�C�i�X�����̖ʂɔz�u����BBox
	for (int ar = 0; ar < 4; ar++) {
		switch (ar) {
		case 0:
			m_pBBoxArrow3[ar]->m_mWorld = XMMatrixTranslation(0.0f, -6.0f, -4.0f); // ��
			break;
		case 1:
			m_pBBoxArrow3[ar]->m_mWorld = XMMatrixTranslation(0.0f, -6.0f, 4.0f);  // ��
			break;
		case 2:
			m_pBBoxArrow3[ar]->m_mWorld = XMMatrixTranslation(4.0f, -6.0f, 0.0f);  // �E
			break;
		case 3:
			m_pBBoxArrow3[ar]->m_mWorld = XMMatrixTranslation(-4.0f, -6.0f, 0.0f); // ��
			break;
		}
	}
// ������Ԃ�z���̃}�C�i�X�����̖ʂɔz�u����BBox
	for (int ar = 0; ar < 4; ar++) {
		switch (ar) {
		case 0:
			m_pBBoxArrow4[ar]->m_mWorld = XMMatrixTranslation(0.0f, 4.0f, -6.0f);  // ��
			break;
		case 1:
			m_pBBoxArrow4[ar]->m_mWorld = XMMatrixTranslation(0.0f, -4.0f, -6.0f); // ��
			break;
		case 2:
			m_pBBoxArrow4[ar]->m_mWorld = XMMatrixTranslation(4.0f, 0.0f, -6.0f);  // �E
			break;
		case 3:
			m_pBBoxArrow4[ar]->m_mWorld = XMMatrixTranslation(-4.0f, 0.0f, -6.0f); // ��
			break;
		}
	}
// ������Ԃ�x���̃v���X�����̖ʂɔz�u����BBox
	for (int ar = 0; ar < 4; ar++) {
		switch (ar) {
		case 0:
			m_pBBoxArrow5[ar]->m_mWorld = XMMatrixTranslation(6.0f, 0.0f, 4.0f);  // ��
			break;
		case 1:
			m_pBBoxArrow5[ar]->m_mWorld = XMMatrixTranslation(6.0f, 0.0f, -4.0f); // ��
			break;
		case 2:
			m_pBBoxArrow5[ar]->m_mWorld = XMMatrixTranslation(6.0f, -4.0f, 0.0f); // �E
			break;
		case 3:
			m_pBBoxArrow5[ar]->m_mWorld = XMMatrixTranslation(6.0f, 4.0f, 0.0f);  // ��
			break;
		}
	}
// ������Ԃ�x���̃}�C�i�X�����̖ʂɔz�u����BBox
	for (int ar = 0; ar < 4; ar++) {
		switch (ar) {
		case 0:
			m_pBBoxArrow6[ar]->m_mWorld = XMMatrixTranslation(-6.0f, 0.0f, 4.0f);  // ��
			break;
		case 1:
			m_pBBoxArrow6[ar]->m_mWorld = XMMatrixTranslation(-6.0f, 0.0f, -4.0f); // ��
			break;
		case 2:
			m_pBBoxArrow6[ar]->m_mWorld = XMMatrixTranslation(-6.0f, 4.0f, 0.0f);  // �E
			break;
		case 3:
			m_pBBoxArrow6[ar]->m_mWorld = XMMatrixTranslation(-6.0f, -4.0f, 0.0f); // ��
			break;
		}
	}
}
//-----------------------------------------------------------------------------
//
// �}�b�v�Q�̍쐬�ƈړ��̏���
//
//-----------------------------------------------------------------------------
void CMapProc::LoadMap2()
{
	// vector�������p�̍\����
	const STAGEMAP      sm;
	const NAVIGATIONMAP nv;
	// �S�}�b�v�̍폜  -----------------------------------------------
	DestroyAll();
	// �S�Ă̓G�E����E���ʂ̔�\����
	m_pGMain->m_pEnmProc->SetNonActive();
	m_pGMain->m_pWeaponProc->SetNonActive();
	m_pGMain->m_pEffectProc->SetNonActive();
	m_pGMain->m_pEnmProc->ResetEnmNum();      // �G�̔������̃��Z�b�g
	lineMap1[4][4] = 5;       // M.S �v���C���[�̈ʒu��z��}�b�v�ɔ��f
	// M.S ���H��vector�̓Y����
	trainNumSt = 0;
	trainNumSd = 0;
	trainNumCg = 0;
	trainNumSta = 0;
	changeNum = 0;             // M.S �����؂�ւ��u���b�N�̕�������
	aboutArrow = 0;
	typeChangeNum = 1;         // M.S ���H�̒u����ނ̎��ʐ���  1:�������H 2:�����ύX���H
	starRotateSwitch = 0;      // M.S ���̉�]�����̑���ň�x�̂ݍs������
	oldH = m_pGMain->initialH;   // M.S �v���C���[�̏����ʒu4(�s)
	oldV = m_pGMain->initialV;   // M.S �v���C���[�̏����ʒu4(��)
	LineChangeFlag = 0;          // M.S �v���C���[�̐i��ł������
	// �X�e�[�W�}�b�v�̐ݒ� ------------------------------------
	m_pColMesh = new CCollision(m_pGMain->m_pFbxMeshCtrl);     // �R���W�����}�b�v�̐���
	int i = 0;
	m_pGMain->transparentSwitch = false; //�L�����N�^�[�̕\��
	// �}�b�v���b�V���̐ݒ�[0]
	m_StageMap.push_back(sm);
	m_StageMap[i].m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Map/EarthStar/centerEarthStar.mesh"));
	m_StageMap[i].m_mWorld = XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	m_StageMap[i].m_pBBox =
		new CBBox(m_pGMain->m_pShader, m_StageMap[i].m_pMesh->m_vMin/*vmin*/, m_StageMap[i].m_pMesh->m_vMax);
	// M.S 10*10�̃o�E���f�B���O�{�b�N�X�̍쐬
	for (int lineNumHori = 0; lineNumHori < 10; lineNumHori++) {
		for (int lineNumVer = 0; lineNumVer < 10; lineNumVer++) {
			m_pBBoxLine[lineNumHori][lineNumVer] = 
				new CBBox(m_pGMain->m_pShader, /*Min*/VECTOR3(-5.0f + lineNumVer, 0.0f, 4.0f - lineNumHori),
					/*Max*/ VECTOR3(-4.0f + lineNumVer, 0.01f, 5.0f - lineNumHori));
			m_pBBoxLine[lineNumHori][lineNumVer]->m_mWorld = XMMatrixTranslation(0.0f, 5.0f, 0.0f);
		}
	}
	i++;
	// M.S �X�^�[�g�ʒu�̔z�u��
	m_StageMap.push_back(sm);
	m_StageMap[i].m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Map/Line/startPosition.mesh"));
	m_StageMap[i].m_mWorld = XMMatrixTranslation(-0.5f, 5.0f, 0.0f);
	m_StageMap[i].m_pBBox =
		new CBBox(m_pGMain->m_pShader, m_StageMap[i].m_pMesh->m_vMin/*vmin*/, m_StageMap[i].m_pMesh->m_vMax);
	i++;
	MakeFrontBBox();      // M.S �e�ʂ�1�z�u����BBox�̍쐬�A�z�u
	MakeSurfaceBBox();    // M.S �e�ʂ�4�z�u����BBox(�ʂ̉�]�����邽��)�̍쐬
	SetPosSurfaceBBox();  // M.S �e�ʂ�4�z�u����BBox(�ʂ̉�]�����邽��)�̔z�u
	mMapWorldOld = m_StageMap[0].m_mWorld;    // -- 2022.1.18  ��]�O��ۑ�
    // M.S �z�u���������ʒu�ƃ}�b�v�ʒu�������āA�v���C�L�����̈ʒu���o��	
	MATRIX4X4 position = XMMatrixTranslation(-0.45f, 6.0f, 0.5f);  
	position = position * m_StageMap[0].m_mWorld;
	// M.S �L�����N�^�[�̈ʒu���Z�b�g
	m_pGMain->m_pPcProc->GetPcObjPtr()->SetWorld(position);
	// �L�����N�^�[�̈ʒu��ۑ�
	m_pGMain->m_pPcProc->GetPcObjPtr()->SetWorldOld(m_pGMain->m_pPcProc->GetPcObjPtr()->GetWorld());
	m_pGMain->m_pPcProc->GetPcObjPtr()->SetLocalRotY(0.0f);  // ���[�J����(Y��)��0�x�ɂ���
    // M.S ���H�̃I�u�W�F�N�g�����
	TrainLST = new TrainLineStProc(m_pGMain);            // M.S �c���H
	TrainLSD = new TrainLineSdProc(m_pGMain);            // M.S �����H
	TrainLChange = new TrainLineCgProc(m_pGMain);        // M.S �����؂�ւ����H
	TrainLStation = new TrainLineStationProc(m_pGMain);  // M.S �w
	// �h�A���b�V���̐ݒ�[1] 
	m_StageMap.push_back(sm);
	m_StageMap[i].m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Map/MapItem/DOOR1.mesh")); // �}�b�v���b�V���R���W�����̐ݒ�
	m_StageMap[i].m_mWorld = XMMatrixTranslation(220.0f, 0.0f, 240.0f);
	m_pColMesh->AddFbxLoad(_T("Data/Map/MapItem/DOOR1.mesh"), VECTOR3(220.0f, 0.0f, 240.0f));
	SetEvent(VECTOR3(-1.5f, -0.05f, -1.0f), VECTOR3(1.5f, 2.8f, 1.0f), m_StageMap[i].m_mWorld, eEvtChangeMap, 3);  // �C�x���g�̐ݒ�(�}�b�v3�ֈړ�����)
	i++;
	// ��
	m_SkyMap.push_back(sm);
	m_SkyMap[0].m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Map/GalaxyBack/galaxyBack_Circle.mesh"));
	m_SkyMap[0].m_mWorld = XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	// M.S �l�I�u�W�F�N�g�̔z�u�����_���ʒu�̔r�o
	m_pGMain->m_pEnmProc->m_pEnmGolemProc->ResetPlacementMan();
	m_pGMain->m_pEnmProc->m_pEnmRSProc->ResetPlacementMan();
	m_pGMain->m_pEnmProc->m_pEnmBdProc->ResetPlacementMan();
	// �}�b�v�m�n�Q
	m_dwMapNo = 2;
	m_bActive = TRUE;
}
//-----------------------------------------------------------------------------
//
// �}�b�v�R�̍쐬�ƈړ��̏���
//
//-----------------------------------------------------------------------------
void CMapProc::LoadMap3()
{
	// vector�������p�̍\����
	const STAGEMAP      sm;
	const MOVEMAP       mm;
	const NAVIGATIONMAP nv;

	// �S�}�b�v�̍폜 -----------------------------------------------
	DestroyAll();
	// M.S �s�������̐��̍X�V
	// M.S �����L���O���[�h���ǂ���
	if (m_pGMain->m_dwGameMode == 3) {
		// M.S �l�I�u�W�F�N�g�̍��v���o��
		m_pGMain->rankRedMan += m_pGMain->m_pEnmProc->getHighStageMan;
		m_pGMain->rankYellowMan += m_pGMain->m_pEnmProc->getMiddleStageMan;
		m_pGMain->rankBlueMan += m_pGMain->m_pEnmProc->getLowStageMan;
		// M.S �s�������̐��̍X�V
		m_pGMain->rankTraveledStar++;
	}
	else if(m_pGMain->m_dwGameMode != 3){
		// M.S �l�I�u�W�F�N�g�̍��v�̕ۑ�
		m_pGMain->m_pEnmProc->getHighMan += m_pGMain->m_pEnmProc->getHighStageMan;
		m_pGMain->m_pEnmProc->getMiddleMan += m_pGMain->m_pEnmProc->getMiddleStageMan;
		m_pGMain->m_pEnmProc->getLowMan += m_pGMain->m_pEnmProc->getLowStageMan;
		// M.S �s�������̐��̍X�V
		m_pGMain->traveledStar++;
	}	
	// M.S �Ō�̐���������S�[��(�����L���O���[�h�̏ꍇ)
	if (m_pGMain->m_dwGameMode == 3 && m_pGMain->rankHaveToGoStar - m_pGMain->rankTraveledStar <= 0) {
		m_pGMain->m_dwGameStatus = GAMECLEAR;
	}
	// M.S �Ō�̐���������S�[��(�ʏ탂�[�h�̏ꍇ)
	else if (m_pGMain->m_dwGameMode != 3 && m_pGMain->haveToGoStar - m_pGMain->traveledStar <= 0) {
		m_pGMain->m_dwGameStatus = GAMECLEAR;
	}
	// �S�Ă̓G�E����E���ʂ̔�\����
	m_pGMain->m_pEnmProc->SetNonActive();
	m_pGMain->m_pWeaponProc->SetNonActive();
	m_pGMain->m_pEffectProc->SetNonActive();
	m_pGMain->m_pEnmProc->ResetEnmNum();      // �G�̔������̃��Z�b�g	
	ResetNewGameMap();                        // M.S �ϐ��̃��Z�b�g
	m_pGMain->transparentSwitch = true;       // M.S �L�����̔�\��
	// �X�e�[�W�}�b�v�̐ݒ� ------------------------------------
	m_pColMesh = new CCollision(m_pGMain->m_pFbxMeshCtrl);     // �R���W�����}�b�v�̐���
	int i = 0;
	m_StageMap.push_back(sm);     // ��O�̐�
	m_StageMap[i].m_pMesh =
		new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Map/EarthStar/centerEarthStar.mesh"));
	m_StageMap[i].m_mWorld = XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	m_StageMap[i].m_pBBox =
		new CBBox(m_pGMain->m_pShader, m_StageMap[i].m_pMesh->m_vMin/*vmin*/, m_StageMap[i].m_pMesh->m_vMax);
	m_StageMap[i].m_pBBox->m_mWorld = m_StageMap[i].m_mWorld;
	m_pColMesh->AddFbxLoad(_T("Data/Map/EarthStar/centerEarthStar.mesh"), VECTOR3(0.0f, 0.0f, 0.0f)); 
	i++;
	m_StageMap.push_back(sm);     // ���̐�
	m_StageMap[i].m_pMesh = 
		new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Map/EarthStar/centerEarthStar.mesh"));
	m_StageMap[i].m_mWorld = XMMatrixTranslation(0.0f, 0.0f, 20.0f);
	m_StageMap[i].m_pBBox = 
		new CBBox(m_pGMain->m_pShader, m_StageMap[i].m_pMesh->m_vMin/*vmin*/, m_StageMap[i].m_pMesh->m_vMax); 
	m_StageMap[i].m_pBBox->m_mWorld = m_StageMap[i].m_mWorld;
	m_pColMesh->AddFbxLoad(_T("Data/Map/EarthStar/centerEarthStar.mesh"), VECTOR3(0.0f, 0.0f, 20.0f)); 
	i++;
	// M.S ���̓����x��\�����߁A�����ƊO���̉˂����ɕ����Ă���
	// M.S ���񂾂񖾂邭����\�����邽�߃I�u�W�F�N�g��2�g�p��
	m_StageMap.push_back(sm);          // M.S ����
	m_StageMap[i].m_nMaterialFlag = 1;
	m_StageMap[i].m_pMesh =
		new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Map/StarBridge/starBridge_Inside.mesh"));
	m_StageMap[i].m_mWorld = XMMatrixTranslation(0.0f, 0.0f, 100.0f);
	i++;
	m_StageMap.push_back(sm);          // M.S �O��
	m_StageMap[i].m_nMaterialFlag = 1;
	m_StageMap[i].m_pMesh = 
		new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Map/StarBridge/starBridge_Outside.mesh"));
	m_StageMap[i].m_mWorld = XMMatrixTranslation(0.0f, 0.0f, 100.0f);
	i++;
	m_StageMap.push_back(sm);          // M.S ����
	m_StageMap[i].m_nMaterialFlag = 1;  
	m_StageMap[i].m_pMesh = 
		new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Map/StarBridge/starBridge_Inside.mesh"));
	m_StageMap[i].m_mWorld = XMMatrixTranslation(0.0f, 0.0f, 10.0f);
	i++;
	m_StageMap.push_back(sm);          // M.S �O��
	m_StageMap[i].m_nMaterialFlag = 1;
	m_StageMap[i].m_pMesh =
		new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Map/StarBridge/starBridge_Outside.mesh"));
	m_StageMap[i].m_mWorld = XMMatrixTranslation(0.0f, 0.0f, 10.0f);
	i++;
	// ��p  ----------------------------------------------------------
	// ��}�b�v�̐ݒ�[0]
	m_SkyMap.push_back(sm);
	m_SkyMap[0].m_pMesh = new CFbxMesh(m_pGMain->m_pFbxMeshCtrl, _T("Data/Map/GalaxyBack/galaxyBackGround100.mesh"));
	m_SkyMap[0].m_mWorld = XMMatrixTranslation(0.0f, -5.0f, 0.0f);
	// �}�b�v�m�n�R
	m_dwMapNo = 3;
	m_bActive = TRUE;
}
//-----------------------------------------------------------------------------
// �}�b�v�v���V�[�W���̂����蔻��
//
// �E����i��ɂo�b�̕���j�ƃR���W�����}�b�v�Ƃ̂����蔻��
//
//   CBaseObj*    pObj      ����̃I�u�W�F�N�g
//   VECTOR3* pHit		�ڐG�_�̍��W�i�o�́j
//   VECTOR3* pNormal	�ڐG�_�̖@���x�N�g���i�o�́jwwwwwwwwwwwwwwwwwwwww

//
//   �߂�l�@BOOL
//           TRUE:�q�b�g�����Ƃ�       FALSE�F�q�b�g���Ă��Ȃ��Ƃ�
//
//-----------------------------------------------------------------------------
BOOL   CMapProc::Hitcheck(CBaseObj* pObj, VECTOR3* pHit, VECTOR3* pNormal)
{
	return  Hitcheck(GetPositionVector(pObj->GetWorld()), GetPositionVector(pObj->GetWorldOld()), pHit, pNormal);
}
//-----------------------------------------------------------------------------
// �}�b�v�v���V�[�W���̂����蔻��
//
// �E����i��ɂo�b�̕���j�ƃR���W�����}�b�v�Ƃ̂����蔻��
//
//   VECTOR3 vNow       ����̌��݈ʒu
//   VECTOR3 vOld       ����̈�O�̈ʒu
//   VECTOR3* vHit		�ڐG�_�̍��W�i�o�́j
//   VECTOR3* vNormal	�ڐG�_�̖@���x�N�g���i�o�́j
//
//   �߂�l�@BOOL
//           TRUE:�q�b�g�����Ƃ�       FALSE�F�q�b�g���Ă��Ȃ��Ƃ�
//
//-----------------------------------------------------------------------------
BOOL   CMapProc::Hitcheck(VECTOR3 vNow, VECTOR3 vOld, VECTOR3* pHit, VECTOR3* pNormal)
{
	BOOL  bRet;
	for (int i = 0; i < m_MoveMap.size(); i++)
	{
		if (m_MoveMap[i].m_pColMesh && m_MoveMap[i].m_bActive)
		{
			bRet = m_MoveMap[i].m_pColMesh->isCollisionLay(vNow, vOld, *pHit, *pNormal);
			if (bRet) return bRet;
		}
	}

	if (m_pColMesh && m_pColMesh->isCollisionLay(vNow, vOld, *pHit, *pNormal))
	{
		return TRUE;
	}
	else {
		return FALSE;
	}

}
//-----------------------------------------------------------------------------  // -- 2020.12.11
// �}�b�v�v���V�[�W���̂����蔻��
//
// �E����i��ɂo�b�̕���j�̋��ƃR���W�����}�b�v�Ƃ̂����蔻��
//
//   VECTOR3 vNow       ����̌��݂̃I�u�W�F�N�g���S�ʒu
//   VECTOR3 vOld       ����̈�O�̃I�u�W�F�N�g���S�ʒu
//   float& fRadius     ���̔��a
//   VECTOR3 &vHit      �ڐG���̃I�u�W�F�N�g���S�ʒu�̍��W�i�o�́j
//   VECTOR3 &vNormal   �ڐG�_�̖@���x�N�g���i�o�́j
//
//   �߂�l�@BOOL
//           TRUE:�q�b�g�����Ƃ�       FALSE�F�q�b�g���Ă��Ȃ��Ƃ�
//
//-----------------------------------------------------------------------------
BOOL   CMapProc::Hitcheck(VECTOR3 vNow, VECTOR3 vOld, float fRadius, VECTOR3* pHit, VECTOR3* pNormal)
{
	BOOL  bRet;
	for (int i = 0; i < m_MoveMap.size(); i++)
	{
		if (m_MoveMap[i].m_pColMesh && m_MoveMap[i].m_bActive)
		{
			bRet = m_MoveMap[i].m_pColMesh->isCollisionSphere(vNow, vOld, fRadius, *pHit, *pNormal);
			if (bRet) return bRet;
		}
	}

	if (m_pColMesh && m_pColMesh->isCollisionSphere(vNow, vOld, fRadius, *pHit, *pNormal))
	{
		return TRUE;
	}
	else {
		return FALSE;
	}
}
//-----------------------------------------------------------------------------
// �I�u�W�F�N�g�̃��C�ƃ��b�V���ڐG����p�z��Ƃ̐ڐG����ƃX���X������������
//	���፷�Əd�͂��l�������A�ڐG������s��									2019.9.3
//  
//  MATRIX4X4* pWorld     �I�u�W�F�N�g�̌��݂̃}�g���b�N�X(in,out)
//  MATRIX4X4  mWorldOld  �I�u�W�F�N�g�̈�O�̃}�g���b�N�X		
//  float fRadius          �I�u�W�F�N�g�̔��a�i�ȗ��l��0.2�j
//  
//  �߂�l�@int
//		�G���[		= -1
//		�ʏ���ړ�	= 1
//		���n		= 2
//		������		= 3
//-----------------------------------------------------------------------------
int  CMapProc::isCollisionMoveGravity(MATRIX4X4* pWorld, MATRIX4X4 mWorldOld, float fRadius)
{
	int  nRet = 0, nRetMove = 0;  // -- 2019.9.3

	// �ړ��}�b�v�Ƃ̐ڐG����ƈړ�
	for (int i = 0; i < m_MoveMap.size(); i++)
	{
		if (m_MoveMap[i].m_pColMesh && m_MoveMap[i].m_bActive)
		{
			nRetMove = m_MoveMap[i].m_pColMesh->isCollisionMoveGravity(*pWorld, mWorldOld, fRadius);  // -- 2019.9.3
			if (nRetMove == 1 || nRetMove == 2) break;   // �ړ��}�b�v�ƐڐG�����Ƃ�
		}
	}

	// �ʏ�̃}�b�v�Ƃ̐ڐG����ƈړ�
	if (m_pColMesh)
	{
		nRet = m_pColMesh->isCollisionMoveGravity(*pWorld, mWorldOld, fRadius);  // -- 2019.9.3
	}

	if (nRetMove == 1 || nRetMove == 2)  // �ړ��}�b�v�ƐڐG���Ă����Ƃ�   // -- 2019.9.3
	{
		return nRetMove;
	}
	else {
		return nRet;
	}
}
//-----------------------------------------------------------------------------
// �I�u�W�F�N�g�̃��C�ƃ��b�V���ڐG����p�z��Ƃ̐ڐG����ƃX���X������������
//	�d�͂��l�����A�ڐG������s��											2019.9.3
//  
//  MATRIX4X4* pWorld     �I�u�W�F�N�g�̌��݂̃}�g���b�N�X(in,out)
//  MATRIX4X4  mWorldOld  �I�u�W�F�N�g�̈�O�̃}�g���b�N�X		
//  float fRadius          �I�u�W�F�N�g�̔��a�i�ȗ��l��0.2�j
//  
//  �߂�l�@int
//		�ڐG�����Ƃ��@		�P
//		�ڐG���Ă��Ȃ��Ƃ�	�O
//-----------------------------------------------------------------------------
int CMapProc::isCollisionMove(MATRIX4X4* pWorld, MATRIX4X4 mWorldOld, float fRadius)
{
	int  nRet = 0, nRetMove = 0;  // -- 2019.9.3

	// �ړ��}�b�v�Ƃ̐ڐG����ƈړ�
	for (int i = 0; i < m_MoveMap.size(); i++)
	{
		if (m_MoveMap[i].m_pColMesh && m_MoveMap[i].m_bActive)
		{
			nRetMove = m_MoveMap[i].m_pColMesh->isCollisionMove(*pWorld, mWorldOld, fRadius);  // -- 2019.9.3
			if (nRetMove == 1) break;
		}
	}

	// �ʏ�̃}�b�v�Ƃ̐ڐG����ƈړ�
	if (m_pColMesh)
	{
		nRet = m_pColMesh->isCollisionMove(*pWorld, mWorldOld, fRadius);  // -- 2019.9.3
	}

	if (nRetMove == 1)  // �ړ��}�b�v�ƐڐG���Ă����Ƃ�     // -- 2019.9.3
	{
		return nRetMove;
	}
	else {
		return nRet;
	}
}

//M.S �����]�����H���}�b�v�z��ɓ��邩�A�܂��������ꍇ���̔z��̍X�V
//��  ���Fint   h     �����}�b�v�z��̍s
//        int   v     �����}�b�v�z��̗�
//�߂�l�Fbool  true  �}�b�v�z��ɓ��� 
//              false �}�b�v�z��ɓ���Ȃ�
bool CMapProc::SetChangeBoxJudge(int h, int v) {
	// �l�̃}�X�̍�����[h][v]�Ƃ���     �񎟌��z��͉��ɍs���قǁA�E�ɍs���قǗv�f���̒l���傫���Ȃ�
		if (lineMap1[h][v] == 0 && lineMap1[h - 1][v] == 0 && lineMap1[h][v + 1] == 0 && lineMap1[h - 1][v + 1] == 0) {
			lineMap1[h][v] = 2;
			lineMap1[h - 1][v] = 2;
			lineMap1[h][v + 1] = 2;
			lineMap1[h - 1][v + 1] = 2;

			return true;
		}
		return false;
}
//M.S �z�u�����������ϊ��̐i�ޕ����Ɣz�u�\���ǂ�������
//��  ���Fint   h     �����}�b�v�z��̍s
//        int   v     �����}�b�v�z��̗�
//        int   oldH  ��ԐV�����z�u�������H�̌��ݒn(�s)
//        int   oldV  ��ԐV�����z�u�������H�̌��ݒn(��)
//�߂�l�Fint         ���H�z�u��Ɍ���������
int CMapProc::GetChangeNum(int h,int v,int oldH,int oldV) {
	// aboutArrow 1:�� 2:�E 3:�� 4:��
	// changeNum  1:�� 2:�E 3:�� 4:��
	if (h == oldH - 1 && v == oldV) {           // �J�[�\���ƑO�̈ʒu�̊֌W
		aboutArrow = 1;               // ��ړ���E�֕����]��
	   return 2;
	}
	else if (h == oldH - 1 && v == oldV - 1) {
		aboutArrow = 1;                // ��ړ��㍶�֕����]��
		return 4;
	}
	else if (h == oldH + 2 && v == oldV) {
		aboutArrow = 3;                // ���ړ���E�֕����]��
		return 2;
	}
	else if (h == oldH + 2 && v == oldV - 1) {
		aboutArrow = 3;                // ���ړ��㍶�֕����]��
		return 4;
	}
	else if (h == oldH && v == oldV + 1) {
		aboutArrow = 2;                // �E�ړ����֕����]��
		return 1;
	}
	else if (h == oldH + 1 && v == oldV + 1) {
		aboutArrow = 2;                // �E�ړ��㉺�֕����]��
		return 3;
	}
	else if (h == oldH && v == oldV - 2) {
		aboutArrow = 4;                // ���ړ����֕����]��
		return 1;
	}
	else if (h == oldH + 1 && v == oldV - 2){
		aboutArrow = 4;                // ���ړ��㉺�֕����]��
		return 3;
    }
	return 9;
}
//M.S �����]�����H�z�u���̃v���C���[���ݒn�̍X�V
//��  ���Fint   h     �����}�b�v�z��̍s
//        int   v     �����}�b�v�z��̗�
//        int   oldH  ��ԐV�����z�u�������H�̌��ݒn(�s)
//        int   oldV  ��ԐV�����z�u�������H�̌��ݒn(��)
//�߂�l�F�Ȃ�
void CMapProc::UpadateOldHV(int oldH, int oldV,int h, int v) {
	// aboutArrou 1:�� 2:�E 3:�� 4:��
	// changeNum  1:�� 2:�E 3:�� 4:��
	switch (aboutArrow) {
	case 1:  // ��
		if (changeNum == 2) {
			this->oldH = h - 1;
			this->oldV = v + 1;
		}
		else if (changeNum == 4) {
			this->oldH = h - 1;
			this->oldV = v;
		}
		break;
	case 3:   // ��
		if (changeNum == 2) {
			this->oldH = h;
			this->oldV = v + 1;
		}
		else if (changeNum == 4) {
			this->oldH = h;
			this->oldV = v;
		}
		break;
	case 2:  //�E
		if (changeNum == 1) {
			this->oldH = h - 1;
			this->oldV = v + 1;
		}
		else if (changeNum == 3) {
			this->oldH = h;
			this->oldV = v + 1;
		}
		break;
	case 4:
		if (changeNum == 1) {
			this->oldH = h - 1;
			this->oldV = v;
		}
		else if (changeNum == 3) {
			this->oldH = h;
			this->oldV = v;
		}
		break;		
	}	
}
//M.S �l�I�u�W�F�N�g�̉�]�֐�
//��  ���FMATRIX4X4 old   �O��̉�]��߂���]�}�g���N�X
//        MATRIX4X4 mYaw  ����̉�]�}�g���N�X
//�߂�l�F�Ȃ�
void CMapProc::MapManRotate(MATRIX4X4 old, MATRIX4X4 mYaw){
	// �e�l�I�u�W�F�N�g�̌��݂̔z�u���̎擾
	// 6���傫�����6�A��������΁AmanNum�̐���������
	if (m_pGMain->m_pEnmProc->m_pEnmGolemProc->manNum > 6) { // higiMan
		arrayHNum = 6;
	}
	else {
		arrayHNum = m_pGMain->m_pEnmProc->m_pEnmGolemProc->manNum;
	}
	if (m_pGMain->m_pEnmProc->m_pEnmRSProc->manNum > 6) {    // middleMan	
		arrayMNum = 6;
	}
	else {
		arrayMNum = m_pGMain->m_pEnmProc->m_pEnmRSProc->manNum;
	}
	if (m_pGMain->m_pEnmProc->m_pEnmBdProc->manNum > 6) {     // lowMan
		arrayLNum = 6;
	}
	else {
		arrayLNum = m_pGMain->m_pEnmProc->m_pEnmBdProc->manNum;
	}
	// �l�I�u�W�F�N�g�̉�]
	for (int i = 0; i < arrayHNum; i++) {  // higiMan	
		MATRIX4X4 manWorld = m_pGMain->m_pEnmProc->m_pEnmGolemProc->GetWorld(i) * old;
		manWorld = manWorld * mYaw;
		m_pGMain->m_pEnmProc->m_pEnmGolemProc->SetWorld(manWorld, i);
	}

	for (int i = 0; i < arrayMNum; i++) {  // middleMan	
		MATRIX4X4 manWorld = m_pGMain->m_pEnmProc->m_pEnmRSProc->GetWorld(i) * old;
		manWorld = manWorld * mYaw;
		m_pGMain->m_pEnmProc->m_pEnmRSProc->SetWorld(manWorld, i);
	}

	for (int i = 0; i < arrayLNum; i++) {  // lowMan
		MATRIX4X4 manWorld = m_pGMain->m_pEnmProc->m_pEnmBdProc->GetWorld(i) * old;
		manWorld = manWorld * mYaw;
		m_pGMain->m_pEnmProc->m_pEnmBdProc->SetWorld(manWorld, i);
	}

}
//M.S �o�E���f�B���O�{�b�N�X�̉�]�֐�
//��  ���FMATRIX4X4 old   �O��̉�]��߂���]�}�g���N�X
//        MATRIX4X4 mYaw  ����̉�]�}�g���N�X
//�߂�l�F�Ȃ�
void CMapProc::MapBBoxRotate(MATRIX4X4 old, MATRIX4X4 mYaw){
	// �e�ʂ̐��ʔ���BBox�̉�]   
	for (int num = 0; num < 6; num++) {
		// ���[���h�}�g���b�N�X�ɍ��̉�]��������
		m_pBBoxPosition[num]->m_mWorld = m_pBBoxPosition[num]->m_mWorld * old;
		// ���[���h�}�g���b�N�X�ɍ��̉�]��������
		m_pBBoxPosition[num]->m_mWorld = m_pBBoxPosition[num]->m_mWorld * mYaw;
	}
	// �e�ʂ̏㉺���E����BBox�̉�]   �����ʒu:����  
	for (int num = 0; num < 4; num++) {
		// ���[���h�}�g���b�N�X�ɍ��̉�]��������
		m_pBBoxArrow1[num]->m_mWorld = m_pBBoxArrow1[num]->m_mWorld * old;
		// ���[���h�}�g���b�N�X�ɍ��̉�]��������
		m_pBBoxArrow1[num]->m_mWorld = m_pBBoxArrow1[num]->m_mWorld * mYaw;
	}
	// �����ʒu:��
	for (int num = 0; num < 4; num++) {
		// ���[���h�}�g���b�N�X�ɍ��̉�]��������
		m_pBBoxArrow2[num]->m_mWorld = m_pBBoxArrow2[num]->m_mWorld * old;
		// ���[���h�}�g���b�N�X�ɍ��̉�]��������
		m_pBBoxArrow2[num]->m_mWorld = m_pBBoxArrow2[num]->m_mWorld * mYaw;
	}
	// �����ʒu:��
	for (int num = 0; num < 4; num++) {
		// ���[���h�}�g���b�N�X�ɍ��̉�]��������
		m_pBBoxArrow3[num]->m_mWorld = m_pBBoxArrow3[num]->m_mWorld * old;
		// ���[���h�}�g���b�N�X�ɍ��̉�]��������
		m_pBBoxArrow3[num]->m_mWorld = m_pBBoxArrow3[num]->m_mWorld * mYaw;
	}
	// �����ʒu:��
	for (int num = 0; num < 4; num++) {
		// ���[���h�}�g���b�N�X�ɍ��̉�]��������
		m_pBBoxArrow4[num]->m_mWorld = m_pBBoxArrow4[num]->m_mWorld * old;
		// ���[���h�}�g���b�N�X�ɍ��̉�]��������
		m_pBBoxArrow4[num]->m_mWorld = m_pBBoxArrow4[num]->m_mWorld * mYaw;
	}
	// �����ʒu:�E
	for (int num = 0; num < 4; num++) {
		// ���[���h�}�g���b�N�X�ɍ��̉�]��������
		m_pBBoxArrow5[num]->m_mWorld = m_pBBoxArrow5[num]->m_mWorld * old;
		// ���[���h�}�g���b�N�X�ɍ��̉�]��������
		m_pBBoxArrow5[num]->m_mWorld = m_pBBoxArrow5[num]->m_mWorld * mYaw;
	}
	// �����ʒu:��
	for (int num = 0; num < 4; num++) {
		// ���[���h�}�g���b�N�X�ɍ��̉�]��������
		m_pBBoxArrow6[num]->m_mWorld = m_pBBoxArrow6[num]->m_mWorld * old;
		// ���[���h�}�g���b�N�X�ɍ��̉�]��������
		m_pBBoxArrow6[num]->m_mWorld = m_pBBoxArrow6[num]->m_mWorld * mYaw;
	}

	for (int i = 0; i < trainNumSt; i++) {  // �c���H
		TrainLST->m_pTLSObjArray[i]->m_mWorld = TrainLST->m_pTLSObjArray[i]->m_mWorld * old;
		TrainLST->m_pTLSObjArray[i]->m_mWorld = TrainLST->m_pTLSObjArray[i]->m_mWorld * mYaw;
		TrainLST->m_pTLSObjArray[i]->GridWorld = TrainLST->m_pTLSObjArray[i]->GridWorld * old;
		TrainLST->m_pTLSObjArray[i]->GridWorld = TrainLST->m_pTLSObjArray[i]->GridWorld * mYaw;
	}
	for (int i = 0; i < trainNumSd; i++) {  //�����H
		TrainLSD->m_pTLSDObjArray[i]->m_mWorld = TrainLSD->m_pTLSDObjArray[i]->m_mWorld * old;
		TrainLSD->m_pTLSDObjArray[i]->m_mWorld = TrainLSD->m_pTLSDObjArray[i]->m_mWorld * mYaw;
		TrainLSD->m_pTLSDObjArray[i]->GridWorld = TrainLSD->m_pTLSDObjArray[i]->GridWorld * old;
		TrainLSD->m_pTLSDObjArray[i]->GridWorld = TrainLSD->m_pTLSDObjArray[i]->GridWorld * mYaw;
	}
	for (int i = 0; i < trainNumCg; i++) {  // �����ύX�u���b�N
		TrainLChange->m_pTCGObjArray[i]->m_mWorld = TrainLChange->m_pTCGObjArray[i]->m_mWorld * old;
		TrainLChange->m_pTCGObjArray[i]->m_mWorld = TrainLChange->m_pTCGObjArray[i]->m_mWorld * mYaw;
		TrainLChange->m_pTCGObjArray[i]->GridWorld = TrainLChange->m_pTCGObjArray[i]->GridWorld * old;
		TrainLChange->m_pTCGObjArray[i]->GridWorld = TrainLChange->m_pTCGObjArray[i]->GridWorld * mYaw;
	}
	for (int i = 0; i < trainNumSta; i++) {  // �w
		TrainLStation->m_pTLSTAObjArray[i]->m_mWorld = TrainLStation->m_pTLSTAObjArray[i]->m_mWorld * old;
		TrainLStation->m_pTLSTAObjArray[i]->m_mWorld = TrainLStation->m_pTLSTAObjArray[i]->m_mWorld * mYaw;
		TrainLStation->m_pTLSTAObjArray[i]->GridWorld = TrainLStation->m_pTLSTAObjArray[i]->GridWorld * old;
		TrainLStation->m_pTLSTAObjArray[i]->GridWorld = TrainLStation->m_pTLSTAObjArray[i]->GridWorld * mYaw;
	}
}
//M.S ����]���ɐ��ɏ���Ă���I�u�W�F�N�g�̉�]���s��
//    �O�̉�]��-�������Čv�Z��A���̉�]�������čs���Ă���
//��  ���FMATRIX4X4 old   �O��̉�]��߂���]�}�g���N�X
//        MATRIX4X4 mYaw  ����̉�]�}�g���N�X
//�߂�l�F�Ȃ�
void CMapProc::MapPcRotate(MATRIX4X4 old, MATRIX4X4 mYaw) {
	rotateProcessDoneFlag = false;
	// �l�I�u�W�F�N�g�̉�]
	MapManRotate(old, mYaw);
	// �v���C�L�����̉�]
	MATRIX4X4 mPcWorld = m_pGMain->m_pPcProc->GetPcObjPtr()->GetWorld()* old;
	mPcWorld = mPcWorld * mYaw;               // ��]��̍s����|����
	m_pGMain->m_pPcProc->GetPcObjPtr()->SetWorld(mPcWorld);
	m_pGMain->m_pPcProc->GetPcObjPtr()->SetWorldOld(mPcWorld);
	m_pGMain->m_pPcProc->GetPcObjPtr()->SetPosUp(VECTOR3(0, 0, 0));
	// �X�^�[�g�ʒu�̃I�u�W�F�N�g�̉�]
	MATRIX4X4 startWorld = m_StageMap[1].m_mWorld * old;
	m_StageMap[1].m_mWorld = startWorld * mYaw;
	// BBox�̉�]
	MapBBoxRotate(old, mYaw);
	mMapWorldOld = m_StageMap[0].m_mWorld;
	rotateProcessDoneFlag = true;

}
//M.S �}�b�v�z��L�^�p�̊֐�
//��  ���Fint oldRotateSurface   �z����L�^����ʂ̐���
//�߂�l�F�Ȃ�
void CMapProc::lineMapSet(int oldRotateSurface) {
	// ��ɑ���}�b�v�����������Ȃ��悤�ɂ���
	if (setOk == false) {
		int mapBuf[10][10] = { 0 };
		setOk = true;
		//buf�ɍ��̑���ʃ}�b�v�̔z�������
		for (int h = 0; h < 10; h++) {
			for (int v = 0; v < 10; v++) {
				mapBuf[h][v] = lineMap1[h][v];
			}
		}
		// ���̖ʂ̔z����L�^����
		switch (oldRotateSurface) {
		case 0:
			for (int h = 0; h < 10; h++) {
				for (int v = 0; v < 10; v++) {
					lineMapBuf1[h][v] = mapBuf[h][v];
				}
			}
			break;
		case 1:
			for (int h = 0; h < 10; h++) {
				for (int v = 0; v < 10; v++) {
					lineMapBuf2[h][v] = mapBuf[h][v];
				}
			}
			break;
		case 2:
			for (int h = 0; h < 10; h++) {
				for (int v = 0; v < 10; v++) {
					lineMapBuf3[h][v] = mapBuf[h][v];
				}
			}
			break;
		case 3:
			for (int h = 0; h < 10; h++) {
				for (int v = 0; v < 10; v++) {
					lineMapBuf4[h][v] = mapBuf[h][v];
				}
			}
			break;
		case 4:
			for (int h = 0; h < 10; h++) {
				for (int v = 0; v < 10; v++) {
					lineMapBuf5[h][v] = mapBuf[h][v];
  				}
			}
			break;
		case 5:
			for (int h = 0; h < 10; h++) {
				for (int v = 0; v < 10; v++) {
					lineMapBuf6[h][v] = mapBuf[h][v];
				}
			}
			break;
		}
	}
}
//M.S �V�����ʂ̃}�b�v��ǂݍ���
//��  ���Fint rotateSurface   �z���ǂݍ��ޖʂ̐���
//�߂�l�F�Ȃ�
void CMapProc::lineMapNew(int rotateSurface) {
	if (setOk == true) {
		setOk = false;
		int mapBuf[10][10] = { 0 };
		switch (rotateSurface) {
		case 0:
			for (int h = 0; h < 10; h++) {
				for (int v = 0; v < 10; v++) {
					mapBuf[h][v] = lineMapBuf1[h][v];
				}
			}
			break;
		case 1:
			for (int h = 0; h < 10; h++) {
				for (int v = 0; v < 10; v++) {
					mapBuf[h][v] = lineMapBuf2[h][v];
				}
			}
			break;
		case 2:
			for (int h = 0; h < 10; h++) {
				for (int v = 0; v < 10; v++) {
					mapBuf[h][v] = lineMapBuf3[h][v];
				}
			}
			break;
		case 3:
			for (int h = 0; h < 10; h++) {
				for (int v = 0; v < 10; v++) {
					mapBuf[h][v] = lineMapBuf4[h][v];
				}
			}
			break;
		case 4:
			for (int h = 0; h < 10; h++) {
				for (int v = 0; v < 10; v++) {
					mapBuf[h][v] = lineMapBuf5[h][v];
				}
			}
			break;
		case 5:
			for (int h = 0; h < 10; h++) {
				for (int v = 0; v < 10; v++) {
					mapBuf[h][v] = lineMapBuf6[h][v];
				}
			}
			break;
		}
		// ����ʔz���buf������
		for (int h = 0; h < 10; h++) {
			for (int v = 0; v < 10; v++) {
				lineMap1[h][v] = mapBuf[h][v];
			}
		}
	}	
}
//M.S BBox���g�p���Đ��ʂ̖ʂ𒲂ׂ�֐�
//��  ���Fint   bBoxArrayNum   ���ׂ�BBox(��)�̐���
//�߂�l�Fbool  true           ���C��BBox����������
//              false          ���C��BBox���������Ă��Ȃ�
bool CMapProc::SearchFinalPlacementSurface(int bBoxArrayNum) {
	return m_pBBoxPosition[bBoxArrayNum]->OBBCollisionLay(back, front, &mHit, &mNor);
}
//M.S �Ō�ɔz�u���삵���}�b�v�ʂ̕ۑ��p�֐�
//��  ���F�Ȃ�
//�߂�l�Fint   ���ʂɂ���ʂ̐���
//              �ǂ��̖ʂ����ʂɂȂ��ꍇ�A10
int CMapProc::SearchFinalPlacementSurface() {
	for (int nowPlacement = 0;  nowPlacement < 6; nowPlacement++) {
		// ���C���΂��Đ��ʂ̖ʂ𒲂ׂ�
		if (SearchFinalPlacementSurface(nowPlacement) == true) {
			return nowPlacement;
		}
	}
	return 10;
}
//M.S ���̖ʂւ̔z�u�ɂȂ鎞�̔z�u�ʒu�̊Ǘ�
//��  ���Fbool onlyArrowJudgeFlag   true�A�z�u���f�̂� false�A�z�u�������s��
//�߂�l�Fbool                      true�A�z�u�\     false�A�z�u�s��
bool CMapProc::AllowEndPlacement(bool onlyArrowJudgeFlag) {
	// ����}�b�v�̊O������Ȃ����ꍇ
	// permissionH,permissionV�ɔz�u�ł���ʒu�����āA�J�[�\���̈ʒu�Ɣ�ׂ�
	newSurfacePlacement = false;  // �z�u�\����newSurfacePlacement�̏�����
	if (oldH == 0 && LineChangeFlag == 1) {
		switch (surfaceMap) {
		case 0:
			if (PlacementSurfaceNum == 1) {
				permissionH = 9;
				permissionV = oldV;
			}
			break;
		case 1:
			if (PlacementSurfaceNum == 2) {
				permissionH = 9;
				permissionV = oldV;
			}
			break;
		case 2:
			if (PlacementSurfaceNum == 3) {
				permissionH = 9;
				permissionV = oldV;
			}
			break;
		case 3:
			if (PlacementSurfaceNum == 0) {
				permissionH = 9;
				permissionV = oldV;
			}
			else if (PlacementSurfaceNum == 4) {
				permissionH = 9 - oldV;
				permissionV = 9;
				LineChangeFlag = 4;
			}
			else if (PlacementSurfaceNum == 5) {
				permissionH = oldV;
				permissionV = 0;
				LineChangeFlag = 2;
			}
			break;
		}
	}// �v���C�L���������[�ɂ��āA�ړ�����������������
	else if (oldH == 9 && LineChangeFlag == 3) {
		switch (surfaceMap) {
		case 0:
			if (PlacementSurfaceNum == 3) {
				permissionH = 0;
				permissionV = oldV;
			}
			break;
		case 1:
			if (PlacementSurfaceNum == 0) {
				permissionH = 0;
				permissionV = oldV;
			}
			else if (PlacementSurfaceNum == 4) {
				permissionH = oldV;
				permissionV = 9;
				LineChangeFlag = 4;
			}
			else if (PlacementSurfaceNum == 5) {
				permissionH = 9 - oldV;
				permissionV = 0;
				LineChangeFlag = 2;
			}
			break;
		case 2:
			if (PlacementSurfaceNum == 1) {
				permissionH = 0;
				permissionV = oldV;
			}
			break;
		case 3:
			if (PlacementSurfaceNum == 2) {
				permissionH = 0;
				permissionV = oldV;
			}
			break;
		}
	}// �v���C�L���������[�ɂ��āA�ړ�����������������
	else if (oldV == 0 && LineChangeFlag == 4) {
		switch (surfaceMap) {
		case 2:
			if (PlacementSurfaceNum == 5) {
				permissionH = 9 - oldH;
				permissionV = 0;
				LineChangeFlag = 2;
			}
			break;
		case 0:
			if (PlacementSurfaceNum == 4) {
				permissionH = oldH;
				permissionV = 9;
			}
			break;
		case 5:
			if (PlacementSurfaceNum == 0) {
				permissionH = oldH;
				permissionV = 9;
			}
			else if (PlacementSurfaceNum == 1) {
				permissionH = 9;
				permissionV = 9 - oldH;
				LineChangeFlag = 1;
			}
			else if (PlacementSurfaceNum == 2) {
				permissionH = 9 - oldH;
				permissionV = 0;
				LineChangeFlag = 2;
			}
			else if (PlacementSurfaceNum == 3) {
				permissionH = 0;
				permissionV = oldH;
				LineChangeFlag = 3;
			}
		}
	}// �v���C�L�������E�[�ɂ��āA�ړ��������E��������
	else if (oldV == 9 && LineChangeFlag == 2) {
		switch (surfaceMap) {
		case 2:
			if (PlacementSurfaceNum == 4) {
				permissionH = 9 - oldH;
				permissionV = 9;
				LineChangeFlag = 4;
			}
			break;
		case 0:
			if (PlacementSurfaceNum == 5) {
				permissionH = oldH;
				permissionV = 0;
			}
			break;
		case 4:
			if (PlacementSurfaceNum == 0) {
				permissionH = oldH;
				permissionV = 0;
			}
			else if (PlacementSurfaceNum == 1) {
				permissionH = 9;
				permissionV = oldH;
				LineChangeFlag = 1;
			}
			else if (PlacementSurfaceNum == 2) {
				permissionH = 9 - oldH;
				permissionV = 9;
				LineChangeFlag = 4;
			}
			else if (PlacementSurfaceNum == 3) {     
				permissionH = 0;
				permissionV = 9 - oldH;
				LineChangeFlag = 3;
			}
		}
	}
	if (permissionH == horiRotate && permissionV == verRotate) {
		if (onlyArrowJudgeFlag == false) {    // �W���b�W�݂̂��ǂ���
			typeChangeNum = 1;                // �������H�݂̂̔z�u
			newSurfacePlacement = true;       // �V�����ʂɔz�u���u���Ă悢
			return true;
		}
		else {
			return true;
		}
	}
	return false;
}
//M.S (�z�u����Ă��邩�Ȃǂ��l����)�ʒu�I�ɔz�u�ł��邩���f����֐�
//��  ���F�Ȃ�
//�߂�l�Fbool     true�A�z�u�\   false�A�z�u�s��
bool CMapProc::ArrowPlacementPos() {
	bool changeLineArrow = false;
	// �������H���w�̏ꍇ���ǂ���
	if (ChangeButton != 1) {
		// �[�̔��肩�ǂ���
		if (AllowEndPlacement(true) == true) {
			return true;
		}
		// �i��ł�������Ȃǂ���z�u�ł��邩�ǂ������f
		switch (LineChangeFlag) {
		case 0:
		case 1:
			if (horiRotate == oldH - 1 && verRotate == oldV) {
				return true;
			}
			break;
		case 2:
			if (horiRotate == oldH && verRotate == oldV + 1) {
				return true;
			}
			break;
		case 3:
			if (horiRotate == oldH + 1 && verRotate == oldV) {
				return true;
			}
			break;
		case 4:
			if (horiRotate == oldH && verRotate == oldV - 1) {
				return true;
			}
		}
	}
	else {
		switch (LineChangeFlag) {
		case 1:
			if (horiRotate == oldH - 1 && verRotate == oldV) {           // �J�[�\���ƑO�̈ʒu�̊֌W
				changeLineArrow = true;                   // ��ړ���E�֕����]��
			}
			else if (horiRotate == oldH - 1 && verRotate == oldV - 1) {
				changeLineArrow = true;                // ��ړ��㍶�֕����]��
			}
			break;
		case 3:
			if (horiRotate == oldH + 2 && verRotate == oldV) {
				changeLineArrow = true;                // ���ړ���E�֕����]��
			}
			else if (horiRotate == oldH + 2 && verRotate == oldV - 1) {
				changeLineArrow = true;                // ���ړ��㍶�֕����]��
			}
			break;
		case 2:
			if (horiRotate == oldH && verRotate == oldV + 1) {
				changeLineArrow = true;                // �E�ړ����֕����]��
			}
			else if (horiRotate == oldH + 1 && verRotate == oldV + 1) {
				changeLineArrow = true;                // �E�ړ��㉺�֕����]��
			}
			break;
		case 4:
			if (horiRotate == oldH && verRotate == oldV - 2) {
				changeLineArrow = true;                // ���ړ����֕����]��
			}
			else if (horiRotate == oldH + 1 && verRotate == oldV - 2) {
				changeLineArrow = true;               // ���ړ��㉺�֕����]��
			}
		}
	}
	if (changeLineArrow == true) {
		if (lineMap1[horiRotate][verRotate] == 0 
			&& lineMap1[horiRotate - 1][verRotate] == 0 
			&& lineMap1[horiRotate][verRotate + 1] == 0 
			&& lineMap1[horiRotate - 1][verRotate + 1] == 0) {
			return true;
		}
	}
	return false;
}
//M.S ���̓��I�z�u�\���ƃG�t�F�N�g
//��  ���F�Ȃ�
//�߂�l�F�Ȃ�
void CMapProc::BornStarEffect() {
	int finishFlag = 0;
	bool breakFlag = false;
	int effectPlayWaitTime = 30;
	int moveStarTime = 68;
	if (starObjArrayNum < m_StageMap.size()) {  // ���̐��G�t�F�N�g���s��
		if (saveHori < 5) {
			if (saveVer < 5) {
				if (mapStarArray[saveHori][saveVer] == 1) {
					// 5.0f�̕ς����ŕ����ς�� // -�Z�̑����Ń��f�������E�ɓ���
					float starSetX = 5.0f*saveVer + 10.0f*saveVer;        
					// +�Z�𑝂₷�Ə�Ƀ��f��������  // -5.0�̕ς����ŕ����ς��
					float starSetZ = -5.0f*saveHori - 10.0f*saveHori;     
					// waitTime��effectPlayWaitTime�ȏ�ɂȂ�A�ŏ��̏�����������
					if (waitTime >= effectPlayWaitTime && starEffectOrder == 0) {   
						VECTOR3 starEffectPos = VECTOR3(starSetX, 20.0f, starSetZ);
						// �G�t�F�N�g�̕\��
						m_pGMain->m_pEffectProc->m_pBillStarProc->Start(starEffectPos);
						// �ŏ��̏������玟(1)�̏�����
						starEffectOrder = 1;
						// ��������
						m_pGMain->bornStarSound->Play();
					}
					// waitTime��moveStarTime�ȏ�ɂȂ�A��(1)�̏�����������
					else if (waitTime >= moveStarTime && starEffectOrder == 1) {
						// �����ړ�������
						m_StageMap[starObjArrayNum].m_mWorld = XMMatrixTranslation(starSetX, 0.0f, starSetZ);
						m_StageMap[starObjArrayNum].m_pBBox->m_mWorld = m_StageMap[starObjArrayNum].m_mWorld;
						// ����������������������
						starObjArrayNum++;
						// �����̏��ԕϐ���������
						starEffectOrder = 0;
						// waitTime��������
						waitTime = 0;
						//���̔z�������悤��saveVer������
						saveVer++;
						// �c5�A��5�̔z��̂Ȃ̂�saveVer��5�ɂȂ����玟�̍s������悤�ɂ���
						if (saveVer % 5 <= 0) {
							saveHori++;
							saveVer = 0;
						}
					}
					waitTime++;
				}
				else {
					// �����Ȃ������ꍇ�̏��� ���̔z�������悤�ɂ���
					saveVer++;
					if (saveVer % 5 <= 0) {
						saveHori++;
						saveVer = 0;
					}
					waitTime++;
				}
			}
		}
	}
}
//M.S ���̉˂����������āA�����L���O���[�h�ȊO�Ȃ�΃Z�[�u������֐�
//��  ���FVECTOR3 longCursol    �����ړ���̍��W 
//        VECTOR3 shortCursol   �����ړ��O�̍��W
//�߂�l�F�Ȃ�
void CMapProc::BuiltStarBridge(VECTOR3 longCursol, VECTOR3 shortCursol) {
	CDirectInput* pDI = m_pGMain->m_pDI;
	int builtTime = 50;
	// �{�^���𗣂����琯�̉˂����t���O�̏�����
	if (pDI->CheckMouse(KD_UTRG, DIM_LBUTTON)) {
		starBridgeInputFlag = false;
		NearStarCol = false;
		frontStarCol = false;
	}
	// �N���b�N������starBridgeinputFlag��true
	if (pDI->CheckMouse(KD_TRG, DIM_LBUTTON)) {
		starBridgeInputFlag = true;
	}
	// �N���b�N���Ă��đO���ƌ���̐��ƐڐG���Ă�����t���O��true�ɂ���
	if (starBridgeInputFlag == true && NearStarCol == false && frontStarCol == false) {
		if (m_StageMap[0].m_pBBox->OBBCollisionLay(longCursol, shortCursol, &mHit, &mNor) == true) {
			NearStarCol = true;
		}
	}
	if (starBridgeInputFlag == true && NearStarCol == true) {
		if (m_StageMap[1].m_pBBox->OBBCollisionLay(longCursol, shortCursol, &mHit, &mNor)) {
			frontStarCol = true;
		}
	}
	// ��̐��̃t���O��true��������starBridgePermission��true
	if (NearStarCol == true && frontStarCol == true) {
		starBridgePermission = true;
	}
	if (starBridgePermission == true) {
     // starBridgeLitingTime�̑҂����Ԃ��I���A�S�Ẳ˂������������Ă��Ȃ�������
		if (starBridgeLitingTime % builtTime <= 0 && starBridgePosNum <= 4) {
			// starBridgePosNum�����̉˂������ړ�������
			m_StageMap[2].m_mWorld = XMMatrixTranslation(0.0f, 0.0f, starBridgePosNum * 2.5f);
			m_StageMap[3].m_mWorld = XMMatrixTranslation(0.0f, 0.0f, starBridgePosNum * 2.5f);
			m_StageMap[4].m_mWorld = XMMatrixTranslation(0.0f, 0.0f, 10 + starBridgePosNum * 2.5f);
			m_StageMap[5].m_mWorld = XMMatrixTranslation(0.0f, 0.0f, 10 + starBridgePosNum * 2.5f);
			starBridgePosNum++;
			// ���ʉ�
			m_pGMain->bornStarSound->Play();
		}
		// ���̉˂����������I�������
		else if (starBridgePosNum == 5) {
			// ���̉˂����t���O��false
			starBridgeInputFlag = false;
			starBridgePermission = false;
			NearStarCol = false;
			frontStarCol = false;
			starBridgePosNum++;
			// �Z�[�u�t���O��true
			m_pGMain->m_pBackForeProc->builtStarBridge = true;
			// �����N���[�h�ȊO�Ȃ�΃Z�[�u������
			if (m_pGMain->m_dwGameMode != 3) {
				m_pGMain->FileWrite();
			}
		}
		starBridgeLitingTime++;
	}
}
//M.S ���̉�]������֐�
//��  ���F�Ȃ�
//�߂�l�F�Ȃ�
void CMapProc::RotateStar() {
	CDirectInput* pDI = m_pGMain->m_pDI;
	//���̉�]�̃v���C���[����
	if (pDI->CheckMouse(KD_TRG, DIM_RBUTTON) && m_pGMain->m_pPcProc->rotateOkFlag == true
		&& rotateProcessDoneFlag == true && m_pGMain->m_pMapProc->doneManPlacement == true
		&& m_pGMain->m_pEnmProc->rotateOkFlagMan == true && starRotateSwitch == 0) {
		beforePoint = pDI->GetMousePos(); // �h���b�O�i���̉�]�j�����ꂽ��A�J�[�\�����G�ꂽ�ʒu�̎擾
		starRotateSwitch = 1;
	}
	if (pDI->CheckMouse(KD_UTRG, DIM_RBUTTON) && starRotateSwitch == 1) {
		afterPoint = pDI->GetMousePos(); // �h���b�O�i���̉�]�j�����ꂽ��A�J�[�\�������ꂽ�ʒu�̎擾
		starRotateSwitch = 2;
	}
	if (starRotateSwitch == 2) {
		starRotateSwitch = 3;
		resultPoint.x = afterPoint.x - beforePoint.x;    // �O�̍��W���獡�̍��W������
		resultPoint.y = afterPoint.y - beforePoint.y;
		long absoluteX;
		long absoluteY;
		absoluteX = labs(resultPoint.x);                 // ���̌v�Z���ʂ̐�Βl���o��
		absoluteY = labs(resultPoint.y);
		// ��]�����������ɉ�����pointArrow�𑫂�
		if (absoluteX > absoluteY && resultPoint.x > 0) {  // ��   
			pointArrow1 += 1;
			m_pGMain->rotateFlag = true;
		}
		else if (absoluteX > absoluteY && resultPoint.x < 0) {  // ��
			pointArrow2 += 1;
			m_pGMain->rotateFlag = true;
		}
		else if (absoluteX < absoluteY && resultPoint.y < 0) {  // ��
			pointArrow3 += 1;
			m_pGMain->rotateFlag = true;
		}
		else if (absoluteX < absoluteY && resultPoint.y > 0) {   // ��
			pointArrow4 += 1;
			m_pGMain->rotateFlag = true;
		} // �h���b�O�̃J�[�\���������Ă��Ȃ��������]�����Ȃ�
		else if (absoluteX == absoluteY) {
			m_pGMain->rotateFlag = false;
			starRotateSwitch = 0;
		}
	}
	linePlacementOkFlag = true;
	if (m_pGMain->rotateFlag == true) {      // ��]�̑��삪�s��ꂽ��		
		MATRIX4X4 oldZ = XMMatrixRotationZ(XMConvertToRadians(-1 * sideDegree));  // �O�̉�]��-�̃}�g���b�N�X
		// �}�b�v�̈ʒu��oldZ�������ĉ�]��߂�
		m_StageMap[0].m_mWorld = m_StageMap[0].m_mWorld * oldZ;
		sideDegree = 0.0f;                   // ��]�p�x�̏�����
		// ����]���o��  pointArrow2���傫���ꍇ+90�x�ApointArrow1���傫���ꍇ-90�x
		pointArrowNum1 = pointArrow2 - pointArrow1;
		if (pointArrowNum1 > 0) {                           // pointArrow2���傫���ꍇ
			for (int i = 0; pointArrowNum1 % 4 > i; i++) {  // �� 4��(360���̂Ƃ��͉�]���Ȃ�) 
				sideDegree += 90.0f;
			}
		}
		else if (0 > pointArrowNum1) {                       // �� 
			for (int i = 0; pointArrowNum1 % 4 < i; i--) {  // pointArrow1���傫���ꍇ
				sideDegree -= 90.0f;
			}
		}
		mYawZ = XMMatrixRotationZ(XMConvertToRadians(sideDegree));      // Z��]�p�x�̃}�g���b�N�X
		m_StageMap[0].m_mWorld = m_StageMap[0].m_mWorld * mYawZ;        // �}�b�v�̈ʒu�ɉ�]��������
		MapPcRotate(oldZ, mYawZ);          // ���ɔz�u����Ă���I�u�W�F�N�g�̉�]
		// �c��]�̏���
		MATRIX4X4 oldX = XMMatrixRotationX(XMConvertToRadians(-1 * heightDegree)); // �O�̉�]��-��]�̃}�g���b�N�X
		 // �}�b�v�̈ʒu��oldX�������ĉ�]��߂�
		m_StageMap[0].m_mWorld = m_StageMap[0].m_mWorld * oldX;
		heightDegree = 0.0f;              // ��]�p�x�̏�����
		// pointArrow3�̕����傫���ꍇ+90�x�ApointArrow4���傫���ꍇ-90�x
		pointArrowNum2 = pointArrow3 - pointArrow4;
		if (pointArrowNum2 > 0) {
			for (int i = 0; pointArrowNum2 % 4 > i; i++) {   // ��  4��(360���̂Ƃ��͉�]���Ȃ�) 
				heightDegree += 90.0f;
			}
		}
		else if (0 > pointArrowNum2) {                      // ��
			for (int i = 0; pointArrowNum2 % 4 < i; i--) {  // pointArrow4�̕����傫���ꍇ
				heightDegree -= 90.0f;
			}
		}
		mYawX = XMMatrixRotationX(XMConvertToRadians(heightDegree));    // X��]�p�x�̃}�g���b�N�X
		m_StageMap[0].m_mWorld = m_StageMap[0].m_mWorld * mYawX;        // �}�b�v�̈ʒu�ɉ�]��������
		MapPcRotate(oldX, mYawX);       // ���ɔz�u����Ă���I�u�W�F�N�g�̉�]
		rotateFinish = true;            // ��]�t���O�̏�����
		starRotateSwitch = 0;
		SaveRotateSurfaceFlag = true;
		m_pGMain->rotateFlag = false;
	}
}
//M.S ���݂̑���ʃ}�b�v�𒲂ׂ�
//��  ���F�Ȃ�
//�߂�l�F�Ȃ�
void CMapProc::JudgeSurface() {
	for (int surfaceArrayNum = 0; surfaceArrayNum < 6; surfaceArrayNum++) {
		if (SearchFinalPlacementSurface(surfaceArrayNum) == true) {
			// ���C�Ɠ�������BBox������ʂ�ۑ�
			surfaceMapLineJudge = surfaceArrayNum;
			if (rotateFinish == true) {  
				// ��]���Ă�����surfaceMap�ɒ��ׂ��ʂ̐�������A�t���O��false
				surfaceMap = surfaceArrayNum;
				rotateFinish = false;
			}
		}
	}
}
//M.S ���H�̃L���L���G�t�F�N�g�̕\��
//��  ���F�Ȃ�
//�߂�l�F�Ȃ�
void CMapProc::GlitterEffect() {
	// ���H�L���L���G�t�F�N�g�̕\��
	float withinRange = 3.0f;  // �G�t�F�N�g�\���͈�
	// �c���H
	for (int i = 0; i < trainNumSt; i++) {
		// �v���C�L�����Ɛ��H�̈ʒu�̎擾
		VECTOR3 linePos = GetPositionVector(TrainLST->m_pTLSObjArray[i]->GridWorld);
		VECTOR3 pcPos = GetPositionVector(m_pGMain->m_pPcProc->GetPcObjPtr()->GetWorld());
		float distance = magnitude(linePos - pcPos);  // ���H�ƃv���C�L�����̋����v�Z
		// ���H���z�u�ʂɂ���A�܂��̓v���C�L�����Ɠ����ʂ�distance��withinRange�ȓ���������
		// �G�t�F�N�g���o��
		if (TrainLST->m_pTLSObjArray[i]->stLineMap == surfaceMapLineJudge
			|| (TrainLST->m_pTLSObjArray[i]->stLineMap == m_pGMain->m_pPcProc->NewSurfaceNum
				&& distance <= withinRange)) {
			// �G�t�F�N�g�̔���
			m_pGMain->m_pEffectProc->m_pBillProc->Start(linePos);
		}
	}
	// �����H
	for (int i = 0; i < trainNumSd; i++) {
		// �v���C�L�����Ɛ��H�̈ʒu�̎擾
		VECTOR3 linePos = GetPositionVector(TrainLSD->m_pTLSDObjArray[i]->GridWorld);
		VECTOR3 pcPos = GetPositionVector(m_pGMain->m_pPcProc->GetPcObjPtr()->GetWorld());
		float distance = magnitude(linePos - pcPos);  // ���H�ƃv���C�L�����̋����v�Z
		// ���H���z�u�ʂɂ���A�܂���distance��withinRange�ȓ���������G�t�F�N�g���o��
		if (TrainLSD->m_pTLSDObjArray[i]->sdLineMap == surfaceMapLineJudge
			|| (TrainLSD->m_pTLSDObjArray[i]->sdLineMap == m_pGMain->m_pPcProc->NewSurfaceNum
				&& distance <= withinRange)) {
			// �G�t�F�N�g�̔���
			m_pGMain->m_pEffectProc->m_pBillProc->Start(linePos);
		}
	}
	// �����]�����H
	for (int i = 0; i < trainNumCg; i++) {
		// �v���C�L�����Ɛ��H�̈ʒu�̎擾
		VECTOR3 linePos = GetPositionVector(TrainLChange->m_pTCGObjArray[i]->GridWorld);
		VECTOR3 pcPos = GetPositionVector(m_pGMain->m_pPcProc->GetPcObjPtr()->GetWorld());
		float distance = magnitude(linePos - pcPos);  // ���H�ƃv���C�L�����̋����v�Z
		// ���H���z�u�ʂɂ���A�܂���distance��withinRange�ȓ���������G�t�F�N�g���o��
		if (TrainLChange->m_pTCGObjArray[i]->cgLineMap == surfaceMapLineJudge
			|| (TrainLChange->m_pTCGObjArray[i]->cgLineMap == m_pGMain->m_pPcProc->NewSurfaceNum
				&& distance <= withinRange)) {
			// �G�t�F�N�g�̔���
			m_pGMain->m_pEffectProc->m_pBillProc->Start(linePos);
		}
	}
	// �w
	for (int i = 0; i < trainNumSta; i++) {
		// �v���C�L�����Ɛ��H�̈ʒu�̎擾
		VECTOR3 linePos = GetPositionVector(TrainLStation->m_pTLSTAObjArray[i]->GridWorld);
		VECTOR3 pcPos = GetPositionVector(m_pGMain->m_pPcProc->GetPcObjPtr()->GetWorld());
		float distance = magnitude(linePos - pcPos);  // ���H�ƃv���C�L�����̋����v�Z
		// ���H���z�u�ʂɂ���A�܂���distance��withinRange�ȓ���������G�t�F�N�g���o��
		if (TrainLStation->m_pTLSTAObjArray[i]->staLineMap == surfaceMapLineJudge
			|| (TrainLStation->m_pTLSTAObjArray[i]->staLineMap == m_pGMain->m_pPcProc->NewSurfaceNum
				&& distance <= 2.0f)) {
			// �G�t�F�N�g�̔���
			m_pGMain->m_pEffectProc->m_pBillProc->Start(linePos);
		}
	}
}
//M.S �J�[�\���K�C�h�̕\��
//��  ���Fint h   �J�[�\���ɐڐG���Ă���BBox�̍s
//      �Fint v   �J�[�\���ɐڐG���Ă���BBox�̗�
//�߂�l�F�Ȃ�
void CMapProc::DrawCursorGuide(int h, int v) {
	VECTOR3 frontPos = VECTOR3(0.0f, 6.0f, 0.0f);
	// ���̉�]�̎擾�i�k�̌����j
	northNow = m_pGMain->m_pPcProc->judgeDirection(surfaceMap, frontPos, 0);
	changeButtonWithinRange = false;
	if (ChangeButton == 1) {  // �����]�����H���I������Ă����ꍇ
		switch (northNow) {  // ���̉�]�ɍ��킹�ăK�C�h��\��
		case 1:
			if (h - 1 >= 0 && v + 1 <= 9) {  // ����]
				// �J�[�\���Ɠ������Ă���}�X�ڂ̕\��
				m_pBBoxLine[h][v]->
					Render(m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);  
				m_pBBoxLine[h - 1][v]->
					Render(m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);
				m_pBBoxLine[h][v + 1]->
					Render(m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);
				m_pBBoxLine[h - 1][v + 1]->
					Render(m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);
				changeButtonWithinRange = true;
			}break;
		case 2:
			// �J�[�\���Ɠ������Ă���}�X�ڂ̕\��
			if (h + 1 <= 9 && v + 1 <= 9) { //+90�x
				m_pBBoxLine[h][v]->
					Render(m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);  
				m_pBBoxLine[h + 1][v]->
					Render(m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);
				m_pBBoxLine[h][v + 1]->
					Render(m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);
				m_pBBoxLine[h + 1][v + 1]->
					Render(m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);
				changeButtonWithinRange = true;
			}break;
		case 3:
			if (h + 1 <= 9 && v - 1 >= 0) { //+180�x
				 // �J�[�\���Ɠ������Ă���}�X�ڂ̕\��
				m_pBBoxLine[h][v]->
					Render(m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt); 
				m_pBBoxLine[h][v - 1]->
					Render(m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);
				m_pBBoxLine[h + 1][v]->
					Render(m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);
				m_pBBoxLine[h + 1][v - 1]->
					Render(m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);
				changeButtonWithinRange = true;
			}break;
		case 4:
			if (h - 1 >= 0 && v - 1 >= 0) { //+270�x
				// �J�[�\���Ɠ������Ă���}�X�ڂ̕\��
				m_pBBoxLine[h][v]->
					Render(m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);  
				m_pBBoxLine[h][v - 1]->
					Render(m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);
				m_pBBoxLine[h - 1][v]->
					Render(m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);
				m_pBBoxLine[h - 1][v - 1]->
                    Render(m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);
				changeButtonWithinRange = true;
			}
		}

	}
	else { // �����]�����H�ȊO���I������Ă����ꍇ ���̂܂܃J�[�\���̏ꏊ��\��
		m_pBBoxLine[h][v]->Render(m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt); 
	}
	// ���̉�](�ʂ̉�])��z��}�b�v�ɍ��킹�ĕϊ�����
	switch (northNow) {
	case 1: //���̂܂�
		horiRotate = h;
		verRotate = v;
		break;
	case 2: // �E��90�x
		horiRotate = 9 - v;
		verRotate = h;
		break;
	case 3: // �E��180�x
		horiRotate = (h - 9)* -1;
		verRotate = 9 - v;
		break;
	case 4: // �E��270�x
		horiRotate = v;
		verRotate = (h - 9)* -1;
		break;
	}
}
//M.S ���i���H�̔z�u
//��  ���Fint h   �z�u����s
//        int v   �z�u�����
//�߂�l�F�Ȃ�
void CMapProc::PlacementStLine(int h, int v) {
	// ���������ł͂Ȃ��ꍇ�A���̖ʂւ̈ړ��̍ŏ��̏������ǂ�������
	if (LineChangeFlag != 0) {
		AllowEndPlacement(false);
	}// ��������
	if (LineChangeFlag == 0) {
		if (horiRotate == oldH - 1 && verRotate == oldV 
			&& lineMap1[oldH][oldV] != 0) {// ��
			m_pGMain->linePlacementSound->Play();  // �z�u��
			// �}�b�v�z��̍X�V
			lineMap1[horiRotate][verRotate] = 1;
			trainNumSt += 1;  // ���H�̐����v���X����
			// �z�u�������H�̖ʂ̕ۑ�
			TrainLST->m_pTLSObjArray[trainNumSt - 1]->stLineMap = surfaceMap;  
			// �I�u�W�F�N�g�̏����Z�b�g
			TrainLST->Update(trainNumSt, v, h);
			LineChangeFlag = 1;  // �������������ړ�����(1)�ɍX�V
			typeChangeNum = 2;   // �S�Ă̐��H��u����
			// ���ݒn���X�V
			oldH = horiRotate;
			oldV = verRotate;
			linePlacementOkFlag = false;
		}
	}
	//�c���H
	else if (LineChangeFlag == 1) {   //��
		if (horiRotate == oldH - 1 && verRotate == oldV 
			&& lineMap1[oldH][oldV] != 0 || newSurfacePlacement == true) {
			m_pGMain->linePlacementSound->Play();  // �z�u��
			// �}�b�v�z��̍X�V
			lineMap1[horiRotate][verRotate] = 1;
			trainNumSt += 1;  // ���H�̐����v���X����
		    // �z�u�������H�̖ʂ̕ۑ�
			TrainLST->m_pTLSObjArray[trainNumSt - 1]->stLineMap = surfaceMap;
			// �I�u�W�F�N�g�̏����Z�b�g
			TrainLST->Update(trainNumSt, v, h);
			typeChangeNum = 2;  // �S�Ă̐��H��u����
			// ���ݒn���X�V
			oldH = horiRotate;
			oldV = verRotate;
			newSurfacePlacement = false;
			PlacementSurfaceNum = SearchFinalPlacementSurface(); // �Ō�ɑ��삵���ʂ̐��̕ۑ�
			linePlacementOkFlag = false;
		}
	}
	else if (LineChangeFlag == 3) {             // ��
		if (horiRotate == oldH + 1 && verRotate == oldV 
			&& lineMap1[oldH][oldV] != 0 || newSurfacePlacement == true) {
			m_pGMain->linePlacementSound->Play();  // �z�u��
			// �}�b�v�z��̍X�V
			lineMap1[horiRotate][verRotate] = 1;
			trainNumSt += 1; // ���H�̐����v���X����
			// �z�u�������H�̖ʂ̕ۑ�
			TrainLST->m_pTLSObjArray[trainNumSt - 1]->stLineMap = surfaceMap;
			// �I�u�W�F�N�g�̏����Z�b�g
			TrainLST->Update(trainNumSt, v, h);
			typeChangeNum = 2;   // �S�Ă̐��H��u����
			oldH = horiRotate;
			oldV = verRotate;
			newSurfacePlacement = false;
			PlacementSurfaceNum = SearchFinalPlacementSurface(); // �Ō�ɑ��삵���ʂ̐��̕ۑ�
			linePlacementOkFlag = false;
		}
	}// �����H
	else if (LineChangeFlag == 2) {          //�E
		if (verRotate == oldV + 1 && horiRotate == oldH 
			&& lineMap1[oldH][oldV] != 0 || newSurfacePlacement == true) {
			m_pGMain->linePlacementSound->Play(); // �z�u��
			// �}�b�v�z��̍X�V
			lineMap1[horiRotate][verRotate] = 1;
			trainNumSd += 1;  // ���H�̐����v���X����
			// �z�u�������H�̖ʂ̕ۑ�
			TrainLSD->m_pTLSDObjArray[trainNumSd - 1]->sdLineMap = surfaceMap;
			// �I�u�W�F�N�g�̏����Z�b�g
			TrainLSD->Update(trainNumSd, v, h);
			typeChangeNum = 2;  // �S�Ă̐��H��u����
			oldH = horiRotate;
			oldV = verRotate;
			newSurfacePlacement = false;
			PlacementSurfaceNum = SearchFinalPlacementSurface(); // �Ō�ɑ��삵���ʂ̐��̕ۑ�
		}
	}
	else if (LineChangeFlag == 4) {          // ��
		if (verRotate == oldV - 1 && horiRotate == oldH 
			&& lineMap1[oldH][oldV] != 0 || newSurfacePlacement == true) {
			m_pGMain->linePlacementSound->Play();  // �z�u��
			// �}�b�v�z��̍X�V
			lineMap1[horiRotate][verRotate] = 1;
			trainNumSd += 1;  // ���H�̐����v���X����
			// �z�u�������H�̖ʂ̕ۑ�
			TrainLSD->m_pTLSDObjArray[trainNumSd - 1]->sdLineMap = surfaceMap;
			// �I�u�W�F�N�g�̏����Z�b�g
			TrainLSD->Update(trainNumSd, v, h);
			typeChangeNum = 2;  // �S�Ă̐��H��u����
			oldH = horiRotate;
			oldV = verRotate;
			newSurfacePlacement = false;
			PlacementSurfaceNum = SearchFinalPlacementSurface(); // �Ō�ɑ��삵���ʂ̐��̕ۑ�
		}
	}
}
//M.S �����]�����H�̔z�u
//��  ���Fint h   �z�u����s
//        int v   �z�u�����
//�߂�l�F�Ȃ� 
void CMapProc::PlacementCgLine(int h, int v){
// ���������ł͂Ȃ��ꍇ�A���̖ʂւ̈ړ��̍ŏ��̏������ǂ�������{
	if (LineChangeFlag != 0) {
		AllowEndPlacement(false);
	}
	changeNum = GetChangeNum(horiRotate, verRotate, oldH, oldV);  // �I�u�W�F�N�g�̈ʒu������
	// changeNum              1:�� 2:�E 3:�� 4:��
	//  LineChangeFlag        1:�� 2:�E 3:�� 4:�� �����ɐi��ł���  
	// aboutArrou             1:�� 2:�E 3:�� 4:��
	if (typeChangeNum == 2 && changeButtonWithinRange == true 
		&& newSurfacePlacement == false && changeNum != 9) {
		// �����؂�ւ��u���b�N�̔z�u�ʒu�ɒu���邩�ǂ���&�}�b�v�z��̍X�V         
		bool judge = SetChangeBoxJudge(horiRotate, verRotate);     
		if (LineChangeFlag == aboutArrow) {           //�i��ł�������̊m�F(��)
			if (judge == true) {
				//changeNum(�z�u��̉�])�ɍ��킹�ăv���C���[�̕�����؂�ւ���
				m_pGMain->linePlacementSound->Play();
				LineChangeFlag = changeNum;
				trainNumCg += 1;                                  // �z�u���H�̐���+1
				TrainLChange->Update(trainNumCg, v, h);           // �e��������
				UpadateOldHV(oldH, oldV, horiRotate, verRotate);  // �z�u���ݒn�̍X�V
				typeChangeNum = 1;                                // �������H�ȊO�z�u�s��
				TrainLChange->m_pTCGObjArray[trainNumCg - 1]->cgLineMap = surfaceMap;  // �z�u�ʂ̕ۑ�
				PlacementSurfaceNum = SearchFinalPlacementSurface();  // �Ō�ɑ��삵���ʂ̐��̕ۑ�
				newSurfacePlacement = false;
			}
		}
	}
}
//M.S �w�̔z�u
//��  ���Fint h   �z�u����s
//        int v   �z�u�����
//�߂�l�F�Ȃ�
void CMapProc::PlacementStaLine(int h, int v) {
	// ���������ł͂Ȃ��ꍇ�A���̖ʂւ̈ړ��̍ŏ��̏������ǂ�������
	if (LineChangeFlag != 0) {
		AllowEndPlacement(false);
	}
	if (typeChangeNum == 2 && newSurfacePlacement == false) {
		if (LineChangeFlag == 1) {             //��
			if (horiRotate == oldH - 1 && verRotate == oldV && lineMap1[oldH][oldV] != 0) {
				m_pGMain->linePlacementSound->Play(); // ���ʉ�
				trainNumSta += 1; // �z�u���H����+1
				// �z�u�����ʂ̕ۑ�
				TrainLStation->m_pTLSTAObjArray[trainNumSta - 1]->staLineMap = surfaceMap;
				// ���H��������
				TrainLStation->Update(trainNumSta, v, h);
				// �}�b�v�z��ɔz�u���H��������
				lineMap1[horiRotate][verRotate] = 3;
				// �S�Ă̐��H��u����悤�ɂ���
				typeChangeNum = 2;
				// �z�u�ʒu�̍X�V
				oldH = horiRotate;
				oldV = verRotate;
				newSurfacePlacement = false;
				PlacementSurfaceNum = SearchFinalPlacementSurface(); // �Ō�ɑ��삵���ʂ̐��̕ۑ�
			}
		}
		else if (LineChangeFlag == 3) {             // ��
			if (horiRotate == oldH + 1 && verRotate == oldV && lineMap1[oldH][oldV] != 0) {
				m_pGMain->linePlacementSound->Play(); // ���ʉ�
				trainNumSta += 1; // �z�u���H����+1
				// �z�u�����ʂ̕ۑ�
				TrainLStation->m_pTLSTAObjArray[trainNumSta - 1]->staLineMap = surfaceMap;
				// ���H��������
				TrainLStation->Update(trainNumSta, v, h);
				// �}�b�v�z��ɔz�u���H��������
				lineMap1[horiRotate][verRotate] = 3;
				// �S�Ă̐��H��u����悤�ɂ���
				typeChangeNum = 2;
				// �z�u�ʒu�̍X�V
				oldH = horiRotate;
				oldV = verRotate;
				newSurfacePlacement = false;
				PlacementSurfaceNum = SearchFinalPlacementSurface(); // �Ō�ɑ��삵���ʂ̐��̕ۑ�
			}
		}// �����H
		else if (LineChangeFlag == 2) {          //�E
			if (verRotate == oldV + 1 && horiRotate == oldH && lineMap1[oldH][oldV] != 0) {
				m_pGMain->linePlacementSound->Play(); // ���ʉ�
				trainNumSta += 1; // �z�u���H����+1
				// �z�u�����ʂ̕ۑ�
				TrainLStation->m_pTLSTAObjArray[trainNumSta - 1]->staLineMap = surfaceMap;
				// ���H��������
				TrainLStation->Update(trainNumSta, v, h);
				// �}�b�v�z��ɔz�u���H��������
				lineMap1[horiRotate][verRotate] = 3;
				// �S�Ă̐��H��u����悤�ɂ���
				typeChangeNum = 2;
				// �z�u�ʒu�̍X�V
				oldH = horiRotate;
				oldV = verRotate;
				newSurfacePlacement = false;
				PlacementSurfaceNum = SearchFinalPlacementSurface(); // �Ō�ɑ��삵���ʂ̐��̕ۑ�
			}
		}
		else if (LineChangeFlag == 4) {          // ��
			if (verRotate == oldV - 1 && horiRotate == oldH && lineMap1[oldH][oldV] != 0) {
				m_pGMain->linePlacementSound->Play(); // ���ʉ�
				trainNumSta += 1; // �z�u���H����+1
				// �z�u�����ʂ̕ۑ�
				TrainLStation->m_pTLSTAObjArray[trainNumSta - 1]->staLineMap = surfaceMap;
				// ���H��������
				TrainLStation->Update(trainNumSta, v, h);
				// �}�b�v�z��ɔz�u���H��������
				lineMap1[horiRotate][verRotate] = 3;
				// �S�Ă̐��H��u����悤�ɂ���
				typeChangeNum = 2;
				// �z�u�ʒu�̍X�V
				oldH = horiRotate;
				oldV = verRotate;
				newSurfacePlacement = false;
				PlacementSurfaceNum = SearchFinalPlacementSurface(); // �Ō�ɑ��삵���ʂ̐��̕ۑ�
			}
		}
	}
}
//-----------------------------------------------------------------------------
//
// �}�b�v�v���V�[�W���̍X�V
//
//-----------------------------------------------------------------------------
void CMapProc::Update()
{
	CDirectInput* pDI = m_pGMain->m_pDI;
	// �J�[�\���ʒu�̎擾
	POINT point = pDI->GetMousePos();
	m_pGMain->cursolX = point.x;
	m_pGMain->cursolY = point.y;
	// Z���W�̍Ē�`�͂���Ȃ�
	VECTOR3 longCursol = XMVector3Unproject(VECTOR3(m_pGMain->cursolX, m_pGMain->cursolY, 1.0f), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0f, 1.0f,
		m_pGMain->m_mProj, m_pGMain->m_mView, XMMatrixIdentity());  // XMMatrixIdentity�͊�{0��OK�A�΂߂���̔���Ƃ���0�ȊO�̐���������
	VECTOR3 shortCursol = XMVector3Unproject(VECTOR3(m_pGMain->cursolX, m_pGMain->cursolY, 0.0f), 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0f, 1.0f,
		m_pGMain->m_mProj, m_pGMain->m_mView, XMMatrixIdentity());  // XMMatrixIdentity�͊�{0��OK�A�΂߂���̔���Ƃ���0�ȊO�̐���������
	//�}�b�v1�̏���
	if (m_dwMapNo == 1) {
		BornStarEffect();
	}
	if (m_dwMapNo == 3) {
		BuiltStarBridge(longCursol, shortCursol);
	}
	if (pDI->CheckMouse(KD_TRG, DIM_MBUTTON)) {   // �z�u���I��ԍ��̕ύX   0:�������H 1:�����]�����H 2:�w
		m_pGMain->lineChangeSound->Play();
		ChangeButton = (ChangeButton + 1) % 3;
	}
	const float Right_Rotate = 90.0f;
	const float Left_Rotate = -90.0f;	
	if (m_dwMapNo == 2) {
		RotateStar();
		oldRotateSurface = surfaceMap;		
		JudgeSurface();
		// �}�b�v�ʔz��̕ۑ��A�X�V
		if (SaveRotateSurfaceFlag == true) {             // ��]�X�C�b�`��false	
			lineMapSet(oldRotateSurface);
			lineMapNew(surfaceMap);
			SaveRotateSurfaceFlag = false;
		}
        // �z�u���H�̕\��
		TrainLST->RenderLine(trainNumSt, trainNumSd, trainNumCg, trainNumSta, m_pGMain);
		//�J��Ԃ����Ȃǂ��ł�ƕ����͕`�悳��Ȃ��Ȃ�	
		GlitterEffect();
		for (int h = 0; h < 10; h++) {
			for (int v = 0; v < 10; v++) {
				rotateProcessDoneFlag = false;
				// �z�u�J�[�\���K�C�h�Ƃ̓����蔻��
				bool f = m_pBBoxLine[h][v]->OBBCollisionLay(longCursol, shortCursol, &mHit, &mNor);
				if (f == true) {
					DrawCursorGuide(h, v);
					if ((pDI->CheckMouse(KD_TRG, DIM_LBUTTON)) && (lineMap1[horiRotate][verRotate] == 0) 
						&& (m_pGMain->stopOperation == false)) {						
						switch (ChangeButton) {
							//LineChangeFlag          0:��������
							//LineChangeFlag          1:�� 2:�E 3:�� 4:�� �����ɐi��ł���
						case 0:   // �c���H  �����H�̔z�u
							PlacementStLine(h, v);
							break;
						case 1:   // �����]�����H�̔z�u
							PlacementCgLine(h, v);
							break;
						case 2:   // �w�̔z�u			
							PlacementStaLine(h, v);
							break;
						}
					}					
				}
			}
		}
	}
	rotateProcessDoneFlag = true;
	// ��̍X�V�@�@�J�����𒆐S�Ƃ����ʒu�ɒu���A�x����]������
	if (m_SkyMap.size() > 0 )
	{
		MATRIX4X4 mRot;
		mRot = XMMatrixRotationY(XMConvertToRadians(0.01f));//(0.005f));
		m_SkyMap[0].m_mWorld = mRot * m_SkyMap[0].m_mWorld;
	}
	// �ړ��}�b�v�X�V����
	UpdateMoveMap();
	//�����_�����O
	Render();
}
// M.S
// �������H�I�u�W�F(�c)�ɏ����Z�b�g
// ��  ���Fint trainNumSt �z�u���钼�����H(�c)�̍��v�̐�
//         int v          �z�u����}�b�v�z��̗�
//         int h          �z�u����}�b�v�z��̍s��
// �߂�l�F�Ȃ�
void TrainLineStProc::Update(int trainNumSt,int v,int h) {
	// �z�u����ʒu�̕ϐ�
	float verPos  = -4.5f + 1 * v;
	float horiPos = 4.0f - h * 1;
	float yPos    = 5.05f;
	// ���H�̎�ނ̐�����m_pTLSObjArray�̔z�u������H�̗v�f�ɓ����
	m_pTLSObjArray[trainNumSt - 1]->SetLineNum(1);
	// �z�u����ʒu�̃}�g���b�N�X�����
	MATRIX4X4 trans = XMMatrixTranslation(verPos, yPos, horiPos);
	// �z�u������H�̈ʒu���Z�b�g����
	m_pTLSObjArray[trainNumSt - 1]->m_mWorld = trans;
	m_pTLSObjArray[trainNumSt - 1]->m_mWorldOld = trans;
	// �L���L���G�t�F�N�g�̈ʒu�̒����p�ϐ�
	float gridAdjust = 0.5f;
	// �L���L���G�t�F�N�g�̈ʒu�̃Z�b�g
	m_pTLSObjArray[trainNumSt - 1]->GridWorld = XMMatrixTranslation(verPos, yPos, gridAdjust + horiPos);
}
// M.S
// �������H�I�u�W�F(��)�ɏ����Z�b�g
// ��  ���Fint trainNumSt �z�u���钼�����H(��)�̍��v�̐�
//         int v          �z�u����}�b�v�z��̗�
//         int h          �z�u����}�b�v�z��̍s��
// �߂�l�F�Ȃ�
void TrainLineSdProc::Update(int trainNumSd, int v, int h) {
	// �z�u����ʒu�̕ϐ�
	float verPos  = -4.5f + 1 * v;
	float horiPos = 4.0f - h * 1;
	float yPos = 5.05f;
	// ���H�̎�ނ̐�����m_pTLSObjArray�̔z�u������H�̗v�f�ɓ����
	m_pTLSDObjArray[trainNumSd - 1]->SetLineNum(1);
	// �z�u����ʒu�̃}�g���b�N�X�����
	MATRIX4X4 trans = XMMatrixTranslation(verPos, yPos, horiPos);
	// �z�u������H�̈ʒu���Z�b�g����
	m_pTLSDObjArray[trainNumSd - 1]->m_mWorld = trans;
	m_pTLSDObjArray[trainNumSd - 1]->m_mWorldOld = trans;
	// �L���L���G�t�F�N�g�̈ʒu�̒����p�ϐ�
	float gridAdjust = 0.5f;
	// �L���L���G�t�F�N�g�̈ʒu�̃Z�b�g
	m_pTLSDObjArray[trainNumSd - 1]->GridWorld = XMMatrixTranslation(verPos, yPos, gridAdjust + horiPos);
}
// M.S
// �����؂�ւ����H�I�u�W�F�ɏ����Z�b�g
// ��  ���Fint trainNumSt �z�u��������؂�ւ����H�̍��v�̐�
//         int v          �z�u����}�b�v�z��̗�
//         int h          �z�u����}�b�v�z��̍s��
// �߂�l�F����
void TrainLineCgProc::Update(int trainNumCg, int v, int h) {
	// �z�u����ʒu�̃}�g���b�N�X�����
	MATRIX4X4 trans;
	// �}�b�v�ʂ̉�]�ɍ��킹�āA�����z��̈ʒu�ł��z�u����ʒu��ς���
		switch (m_pGMain->m_pMapProc->northNow) {
		case 1: // 0�x��]
			trans = XMMatrixTranslation(-4.0f + 1 * v, 5.05f, 5.0f - h * 1);
			break;
		case 2: // �E��90�x��]
			trans = XMMatrixTranslation(-4.0f + 1 * v, 5.05f, 4.0f - h * 1);
			break;
		case 3: // �E��180�x��]
			trans = XMMatrixTranslation(-5.0f + 1 * v, 5.05f, 4.0f - h * 1);
			break;
		case 4: // �E��270�x��]
			trans = XMMatrixTranslation(-5.0f + 1 * v, 5.05f, 5.0f - h * 1);
			break;
		}
	// ���H�̎�ނ̐�����m_pTCGObjArray�̔z�u������H�̗v�f�ɓ����
	m_pTCGObjArray[trainNumCg - 1]->SetLineNum(2);
	// �z�u������H�̈ʒu���Z�b�g����
	m_pTCGObjArray[trainNumCg - 1]->m_mWorld = trans;
	m_pTCGObjArray[trainNumCg - 1]->m_mWorldOld = trans;
	// �L���L���G�t�F�N�g�̈ʒu�̃Z�b�g
	m_pTCGObjArray[trainNumCg - 1]->GridWorld = trans;
}
// M.S
// �w�I�u�W�F�ɏ����Z�b�g
// ��  ���Fint trainNumSt �z�u����w�̍��v�̐�
//         int v          �z�u����}�b�v�z��̗�
//         int h          �z�u����}�b�v�z��̍s��
// �߂�l�F����
void TrainLineStationProc::Update(int trainNumSta, int v, int h) {
	// �z�u����ʒu�̕ϐ�
	float verPos = -4.5f + 1 * v;
	float horiPos = 4.0f - h * 1;
	float yPos = 5.05f;
	// ���H�̎�ނ̐�����m_pTLSObjArray�̔z�u������H�̗v�f�ɓ����
	m_pTLSTAObjArray[trainNumSta - 1]->SetLineNum(1);
	// �z�u����ʒu�̃}�g���b�N�X�����
	MATRIX4X4 trans = XMMatrixTranslation(verPos, yPos, horiPos);
	// �z�u������H�̈ʒu���Z�b�g����
	m_pTLSTAObjArray[trainNumSta - 1]->m_mWorld = trans;
	m_pTLSTAObjArray[trainNumSta - 1]->m_mWorldOld = trans;
	// �L���L���G�t�F�N�g�̈ʒu�̃Z�b�g
	m_pTLSTAObjArray[trainNumSta - 1]->GridWorld = XMMatrixTranslation(-4.5f + 1 * v, 5.05f, 0.5f + 4.0f - h * 1);
}
//-----------------------------------------------------------------------------   // -- 2021.2.4
//
// �C�x���g�̃Z�b�g
//
// ����
//   VECTOR3 vMin         : �o�E���f�B���O�{�b�N�X�ŏ��l
//   VECTOR3 vMax         : �o�E���f�B���O�{�b�N�X�ő�l
//   MATRIX4X4 mWorld     : �o�E���f�B���O�{�b�N�X�̃��[���h�}�g���b�N�X
//   EVENTKIND nEvtKind   : �C�x���g�̎�� eEvtChangeMap:�}�b�v�ړ�, eEvtMoveMap:�ړ��}�b�v�̐���
//   int nEvtNo           : �C�x���g�ԍ� eEvtChangeMap�̂Ƃ��͈ړ���̃}�b�v�ԍ��AeEvtMoveMap�̂Ƃ��͈ړ��}�b�v�̗v�f�ԍ�
//   int nEvtOpe1         : eEvtMoveMap�̂݁B1:�ړ��}�b�v�̈ړ�Active�̎w��B2:�ړ��}�b�v�̈ړ��t���O�̎w��(�ȗ��l0)
//   int nEvtOpe2         : eEvtMoveMap�̂݁B�ړ�Active�̂Ƃ���0:��\�� 1:�\��  �ړ��t���O�̂Ƃ��́@0:�ړ������@1:���s�ړ��@2:��]�@3:�g��k��(�ȗ��l0)
//   int nEvtKeyPush      : 0:�o�E���f�B���O�{�b�N�X�ɐڐG����ƃC�x���g�����A 1:�o�E���f�B���O�{�b�N�X�ɐڐG���āAENTER�L�[�������ƃC�x���g����(�ȗ��l0)
//
// �߂�l
//   int �Z�b�g�����C�x���g�z��̗v�f�ԍ�
//
//-----------------------------------------------------------------------------
int  CMapProc::SetEvent(VECTOR3 vMin, VECTOR3 vMax, MATRIX4X4 mWorld, EVENTKIND nEvtKind, int nEvtNo, int nEvtOpe1, int nEvtOpe2, int nEvtKeyPush)
{
	const EVENTMAP      em;

	m_EventMap.push_back(em);

	// �o�E���f�B���O�{�b�N�X�̐ݒ�
	m_EventMap[m_nEvtIdx].m_pBBox = new CBBox(m_pGMain->m_pShader, vMin, vMax);
	m_EventMap[m_nEvtIdx].m_pBBox->m_mWorld = mWorld;

	// �e���ڂ̐ݒ�
	m_EventMap[m_nEvtIdx].m_nEvtCycle = 0;
	m_EventMap[m_nEvtIdx].m_nEvtKind = nEvtKind;
	m_EventMap[m_nEvtIdx].m_nEvtNo = nEvtNo;
	m_EventMap[m_nEvtIdx].m_nEvtOpe1 = nEvtOpe1;
	m_EventMap[m_nEvtIdx].m_nEvtOpe2 = nEvtOpe2;
	m_EventMap[m_nEvtIdx].m_nEvtKeyPush = nEvtKeyPush;

	m_nEvtIdx++;
	return  m_nEvtIdx - 1;
}

//-----------------------------------------------------------------------------   // -- 2021.2.4
//
// �C�x���g�̍X�V�E���s
//
//-----------------------------------------------------------------------------
void  CMapProc::UpdateEvent()
{
	VECTOR3 vHit, vNrm;

	for (int i = 0; i < m_EventMap.size(); i++)
	{
		// PC�̃o�E���f�B���O�{�b�N�X�ɐڐG���Ă��邩�̔���
		if (m_EventMap[i].m_pBBox && m_EventMap[i].m_pBBox->OBBCollisionDetection(m_pGMain->m_pPcProc->GetPcObjPtr()->GetBBox(), &vHit, &vNrm))
		{
			// PC�̃o�E���f�B���O�{�b�N�X�ɐڐG���Ă���Ƃ�
			if (m_EventMap[i].m_nEvtCycle == 0)  // �C�x���g�T�C�N�����O�̂Ƃ�(�܂��ڐG���Ă��Ȃ������Ƃ�)
			{
				if (m_EventMap[i].m_nEvtKeyPush == 1 && !(m_pGMain->m_pDI->CheckKey(KD_DAT, DIK_RETURN) || m_pGMain->m_pDI->CheckJoy(KD_DAT, DIJ_A)))  // Enter�L�[�v�b�V�����K�v�ȂƂ�
				{
					VECTOR3 vPc = GetPositionVector(m_pGMain->m_pPcProc->GetPcObjPtr()->GetWorld());
					vPc.y += 2.0f;
					// PC�̓���ɁAEnter�L�[�v�b�V�����s���Ă��Ȃ����̕\��������
					m_pGMain->m_pFont->Draw3D(vPc, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vEyePt, _T("Push Enter Key!"), VECTOR2(0.8f, 0.2f), RGB(255, 0, 0), 1.0f, _T("HGP�n�p�p�޼��UB"));
				}
				else {
					// �C�x���g���s
					RunEvent(m_EventMap[i]);
				}
			}
		}
		else {
			// PC�̃o�E���f�B���O�{�b�N�X�ɐڐG���Ă��Ȃ��Ƃ�
			if (m_EventMap[i].m_nEvtCycle == 2)  // �C�x���g�T�C�N�����Q�̂Ƃ�(���ɐڐG���Ă��ďI���҂��̂Ƃ�)
			{
				m_EventMap[i].m_nEvtCycle = 0;  // �C�x���g�T�C�N�����O�ɖ߂�
			}
		}
	}
}

//-----------------------------------------------------------------------------   // -- 2021.2.4
//
// �C�x���g�̎��s
//
// ����  EVENTMAP& EventMap:�C�x���g�}�b�v
//
//-----------------------------------------------------------------------------
void  CMapProc::RunEvent(EVENTMAP& EventMap)
{
	int i;

	if (EventMap.m_nEvtKind == eEvtChangeMap)   // �}�b�v�ړ��̂Ƃ�
	{
		switch (EventMap.m_nEvtNo)
		{
		case 1:
			LoadMap1();
			break;
		case 2:
			LoadMap2();
			break;
		case 3:
			LoadMap3();
			break;
		}
	}
	else if (EventMap.m_nEvtKind == eEvtMoveMap)  // �ړ��}�b�v�̐���̂Ƃ�
	{
		i = EventMap.m_nEvtNo;
		if (EventMap.m_nEvtOpe1 == 1)   // �\���L���Ɋւ��鏈��
		{
			m_MoveMap[i].m_bActive = EventMap.m_nEvtOpe2;
		}
		else if (EventMap.m_nEvtOpe1 == 2)   // �ړ��Ɋւ��鏈��
		{
			m_MoveMap[i].m_nMoveFlag = EventMap.m_nEvtOpe2;
		}
		EventMap.m_nEvtCycle = 2;  // �C�x���g�T�C�N�����Q�ɂ���   // -- 2021.4.4
	}
}

//-----------------------------------------------------------------------------
//
// �ړ��}�b�v�̍X�V
//
// �ړ��}�b�v�̕��s�ړ����]�̍X�V���s��
// ���E�l�i��[���[���j�ɒB�����Ƃ��́A���]�ichange�j���s��
// ���]�ichange�j�������Ƃ��́Am_nChangeFlag�ɂP���Ԃ�
// ���[�v�����Ȃ��Ƃ��͔��]�̃^�C�~���O�Œ�~����         // -- 2021.2.4
//
//-----------------------------------------------------------------------------
void CMapProc::UpdateMoveMap()
{
	for (DWORD i = 0; i < m_MoveMap.size(); i++)
	{
		if (m_MoveMap[i].m_pColMesh && m_MoveMap[i].m_bActive)   // �ړ��}�b�v�̍X�V����
		{
			m_MoveMap[i].m_pColMesh->m_mWorldOld = m_MoveMap[i].m_pColMesh->m_mWorld;   // ���[���h�}�g���b�N�X��O
			m_MoveMap[i].m_nChangeFlag = 0;      // �`�F���W�t���O�̃��Z�b�g
			if (m_MoveMap[i].m_nMoveFlag == 1)   // ���s�ړ��̏���
			{
				MATRIX4X4 mPosUp;
				mPosUp = XMMatrixTranslation(m_MoveMap[i].m_vUp.x, m_MoveMap[i].m_vUp.y, m_MoveMap[i].m_vUp.z);
				m_MoveMap[i].m_pColMesh->SetWorldMatrix(mPosUp * m_MoveMap[i].m_pColMesh->m_mWorld);  // �ړ������̏���
				if (m_MoveMap[i].m_vUp.x != 0)  // ���E�ɓ�����
				{
					if (GetPositionVector(m_MoveMap[i].m_pColMesh->m_mWorld).x < m_MoveMap[i].m_vMin.x ||  // ���E�ɓ��������߉E�[���[�Ŕ��]
						GetPositionVector(m_MoveMap[i].m_pColMesh->m_mWorld).x > m_MoveMap[i].m_vMax.x )
					{
						m_MoveMap[i].m_vUp.x *= -1;
						m_MoveMap[i].m_nChangeFlag = 1;
					}
				}
				if (m_MoveMap[i].m_vUp.y != 0)  // �㉺�ɓ�����
				{
					if (GetPositionVector(m_MoveMap[i].m_pColMesh->m_mWorld).y < m_MoveMap[i].m_vMin.y ||  // �㉺�ɓ��������ߏ�[���[�Ŕ��]
						GetPositionVector(m_MoveMap[i].m_pColMesh->m_mWorld).y > m_MoveMap[i].m_vMax.y)
					{
						m_MoveMap[i].m_vUp.y *= -1;
						m_MoveMap[i].m_nChangeFlag = 1;
					}
				}
				if (m_MoveMap[i].m_vUp.z != 0)  // �O��ɓ�����
				{
					if (GetPositionVector(m_MoveMap[i].m_pColMesh->m_mWorld).z < m_MoveMap[i].m_vMin.z ||  // �O��ɓ��������ߑO�[��[�Ŕ��]
						GetPositionVector(m_MoveMap[i].m_pColMesh->m_mWorld).z > m_MoveMap[i].m_vMax.z)
					{
						m_MoveMap[i].m_vUp.z *= -1;
						m_MoveMap[i].m_nChangeFlag = 1;
					}
				}
			}
			else if (m_MoveMap[i].m_nMoveFlag == 2){   // ��]�̏���
				MATRIX4X4 mRotUp;
				if (m_MoveMap[i].m_vUp.x != 0)  // �w��]
				{
					mRotUp = XMMatrixRotationX(XMConvertToRadians(m_MoveMap[i].m_vUp.x));
					m_MoveMap[i].m_pColMesh->SetWorldMatrix(mRotUp * m_MoveMap[i].m_pColMesh->m_mWorld);  // �w��]�����̏���
					if (GetRotateVector(m_MoveMap[i].m_pColMesh->m_mWorld).x < m_MoveMap[i].m_vMin.x ||  // �w��]���邽�ߒ[�Ŕ��]
						GetRotateVector(m_MoveMap[i].m_pColMesh->m_mWorld).x > m_MoveMap[i].m_vMax.x)
					{
						m_MoveMap[i].m_vUp.x *= -1;  // �w��]���邽�ߒ[�Ŕ��]
						m_MoveMap[i].m_nChangeFlag = 1;
					}
				}else if (m_MoveMap[i].m_vUp.y != 0)  // �x��]
				{
					mRotUp = XMMatrixRotationY(XMConvertToRadians(m_MoveMap[i].m_vUp.y));
					m_MoveMap[i].m_pColMesh->SetWorldMatrix(mRotUp * m_MoveMap[i].m_pColMesh->m_mWorld);  // �w��]�����̏���
					if (GetRotateVector(m_MoveMap[i].m_pColMesh->m_mWorld).y < m_MoveMap[i].m_vMin.y ||  // �x��]���邽�ߒ[�Ŕ��]
						GetRotateVector(m_MoveMap[i].m_pColMesh->m_mWorld).y > m_MoveMap[i].m_vMax.y)
					{
						m_MoveMap[i].m_vUp.y *= -1;  // �x��]���邽�ߒ[�Ŕ��]
						m_MoveMap[i].m_nChangeFlag = 1;
					}
				}
				else if (m_MoveMap[i].m_vUp.z != 0)  // �y��]
				{
					mRotUp = XMMatrixRotationZ(XMConvertToRadians(m_MoveMap[i].m_vUp.z));
					m_MoveMap[i].m_pColMesh->SetWorldMatrix(mRotUp * m_MoveMap[i].m_pColMesh->m_mWorld);  // �w��]�����̏���
					if (GetRotateVector(m_MoveMap[i].m_pColMesh->m_mWorld).z < m_MoveMap[i].m_vMin.z ||  // �y��]���邽�ߒ[�Ŕ��]
						GetRotateVector(m_MoveMap[i].m_pColMesh->m_mWorld).z > m_MoveMap[i].m_vMax.z)
					{
						m_MoveMap[i].m_vUp.z *= -1;  // �y��]���邽�ߒ[�Ŕ��]
						m_MoveMap[i].m_nChangeFlag = 1;
					}
				}
			}
			else if (m_MoveMap[i].m_nMoveFlag == 3) {   // �g��k���̏���      // -- 2019.12.30
				MATRIX4X4 mScaleUp;
				mScaleUp = XMMatrixScaling(m_MoveMap[i].m_vUp.x, m_MoveMap[i].m_vUp.y, m_MoveMap[i].m_vUp.z);
				m_MoveMap[i].m_pColMesh->SetWorldMatrix(mScaleUp * m_MoveMap[i].m_pColMesh->m_mWorld);  // �g��k�������̏���
				VECTOR3 vScaleNow = GetScaleVector(m_MoveMap[i].m_pColMesh->m_mWorld);     // ���݂̊g�嗦�𓾂�
				if (vScaleNow.x < m_MoveMap[i].m_vMin.x ||      // �K��̊g��k���ɒB������
					vScaleNow.x > m_MoveMap[i].m_vMax.x ||
					vScaleNow.y < m_MoveMap[i].m_vMin.y ||
					vScaleNow.y > m_MoveMap[i].m_vMax.y ||
					vScaleNow.z < m_MoveMap[i].m_vMin.z ||
					vScaleNow.z > m_MoveMap[i].m_vMax.z)
				{
					m_MoveMap[i].m_vUp.x = 1 / avoidZero(m_MoveMap[i].m_vUp.x);  // �g��k���̔��]
					m_MoveMap[i].m_vUp.y = 1 / avoidZero(m_MoveMap[i].m_vUp.y);  // �g��k���̔��]
					m_MoveMap[i].m_vUp.z = 1 / avoidZero(m_MoveMap[i].m_vUp.z);  // �g��k���̔��]
					m_MoveMap[i].m_nChangeFlag = 1;
				}
			}
			// ���[�v�����Ȃ��Ƃ��̒�~���f�B���]�̃^�C�~���O�Œ�~����             // -- 2021.2.4
			if (m_MoveMap[i].m_nLoop == 0 && m_MoveMap[i].m_nChangeFlag == 1)
			{
				m_MoveMap[i].m_nMoveFlag = 0;    // �ړ����Ȃ�
			}
		}
	}
}
//============================================================================
//  �}�b�v�v���V�[�W���̃����_�����O
// 
//    �����@�@�Ȃ�
// 
//    �߂�l�@�Ȃ�
//============================================================================
void  CMapProc::Render(void)
{
	int shineFlag = 0;  // �����_�[�̎w�� M.S
	if (m_bActive) {
		// ��̃����_�����O
		if (m_SkyMap.size() > 0)
		{
			// ��̃����_�����O   �A�e�����Ȃ������_�����O 
			// Z�o�b�t�@�𖳌���
			m_pGMain->m_pD3D->SetZBuffer(TRUE);
			m_SkyMap[0].m_pMesh->Render(m_SkyMap[0].m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, VECTOR3(0, 0, 0), m_pGMain->m_vEyePt, shineFlag);  // �A�e�����Ȃ������_�����O 
		}
		// �}�b�v�����_�����O
		for (DWORD i = 0; i<m_StageMap.size(); i++)
		{
			//     m_dwMapNo(�}�b�v)��2���X�^�[�g�ʒu�̔z�u��  M.S 
			//     m_dwMapNo(�}�b�v)��3����O�̐�  M.S 
			if (MapNumGet() == 2 && i == 1 || MapNumGet() == 3 && i == 0) {
				shineFlag = 3; 	// �����_�[�̎w�� M.S
				m_StageMap[i].m_pMesh->Render(m_StageMap[i].m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt, shineFlag);
				shineFlag = 0;  // �����_�[�̎w���0�ɖ߂� M.S
			}		
		    else if (m_StageMap[i].m_nMaterialFlag == 0)  // �ʏ�̃u�����h�X�e�[�g
			{
				if (m_StageMap[i].m_pMesh) m_StageMap[i].m_pMesh->Render(m_StageMap[i].m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt, shineFlag);
			}			
			else if (m_StageMap[i].m_nMaterialFlag == 2)  // �f�B�X�v���C�X�����g�}�b�s���O
			{
				// �f�B�X�v���C�X�����g�}�b�v�����_�����O
				if (m_StageMap[i].m_pMesh) 	m_StageMap[i].m_pMesh->RenderDisplace(m_StageMap[i].m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);
			}		
		}
		// �ړ��}�b�v�����_�����O     * ���̃v���O�����ł͎g�p���Ă��Ȃ�
		for (DWORD i = 0; i<m_MoveMap.size(); i++)
		{
			if( m_MoveMap[i].m_nMaterialFlag == 0 )  // �ʏ�̃u�����h�X�e�[�g
			{
				if (m_MoveMap[i].m_pMesh && m_MoveMap[i].m_bActive)	m_MoveMap[i].m_pMesh->Render(m_MoveMap[i].m_pColMesh->m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt, shineFlag);
			}
			else if( m_MoveMap[i].m_nMaterialFlag == 2 )  // �f�B�X�v���C�X�����g�}�b�s���O
			{
				if (m_MoveMap[i].m_pMesh && m_MoveMap[i].m_bActive)	m_MoveMap[i].m_pMesh->RenderDisplace(m_MoveMap[i].m_pColMesh->m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);
			}
		}
	}
}
// M.S
// ���H�̃����_�����O
// ��  ���Fint        trainNumSt    �z�u���钼�����H(�c)�̍��v�̐�
//         int        trainNumSd    �z�u���钼�����H(��)�̍��v�̐�
//         int        trainNumCg    �z�u��������؂�ւ����H�̍��v�̐�
//         int        trainNumSta   �z�u����w�̍��v�̐�
//         CGameMain* mproc         CGameMain�̃|�C���^
// �߂�l�F�Ȃ�
void TrainLineStProc::RenderLine(int trainNumSt,int trainNumSd,int trainNumCg,
	                             int trainNumSta, CGameMain* mproc){
	// �}�b�v�����_�����O
	int shineNum = 1;  // �����_�[�̎w�� M.S
	// �������H(�c)���z�u������Ă��邩�ǂ���
	if (trainNumSt > 0) {
		for (DWORD i = 0; i < trainNumSt; i++)
		{
			// �z�u���ꂢ�Ă鐔�����_�����O����
			if (mproc->m_pMapProc->TrainLST->m_pTLSObjArray[i]->m_pMesh) {
				mproc->m_pMapProc->TrainLST->m_pTLSObjArray[i]->m_pMesh->
					Render(mproc->m_pMapProc->TrainLST->m_pTLSObjArray[i]->m_mWorld,
						mproc->m_mView, mproc->m_mProj, mproc->m_vLightDir, mproc->m_vEyePt, shineNum);
			}
		}
	}
	// �������H(��)���z�u������Ă��邩�ǂ���
	if (trainNumSd > 0) {
		for (DWORD i = 0; i < trainNumSd; i++)
		{
			// �z�u���ꂢ�Ă鐔�����_�����O����
			if (mproc->m_pMapProc->TrainLSD->m_pTLSDObjArray[i]->m_pMesh) {
				mproc->m_pMapProc->TrainLSD->m_pTLSDObjArray[i]->m_pMesh->
				Render(mproc->m_pMapProc->TrainLSD->m_pTLSDObjArray[i]->m_mWorld,
				mproc->m_mView, mproc->m_mProj, mproc->m_vLightDir, mproc->m_vEyePt, shineNum);
			}
		}
	}
	// �����؂�ւ����H���z�u������Ă��邩�ǂ���
	if (trainNumCg > 0) {
		for (DWORD i = 0; i < trainNumCg; i++)
		{
			// �z�u���ꂢ�Ă鐔�����_�����O����
			if (mproc->m_pMapProc->TrainLChange->m_pTCGObjArray[i]->m_pMesh) {
				mproc->m_pMapProc->TrainLChange->m_pTCGObjArray[i]->m_pMesh->
				Render(mproc->m_pMapProc->TrainLChange->m_pTCGObjArray[i]->m_mWorld,
				mproc->m_mView, mproc->m_mProj, mproc->m_vLightDir, mproc->m_vEyePt, shineNum);
			}
		}
	}
	// �w���z�u������Ă��邩�ǂ���
	if (trainNumSta > 0) {
		for (DWORD i = 0; i < trainNumSta; i++)
		{
			// �z�u���ꂢ�Ă鐔�����_�����O����
			if (mproc->m_pMapProc->TrainLStation->m_pTLSTAObjArray[i]->m_pMesh) {
				mproc->m_pMapProc->TrainLStation->m_pTLSTAObjArray[i]->m_pMesh->
				Render(mproc->m_pMapProc->TrainLStation->m_pTLSTAObjArray[i]->m_mWorld,
    			mproc->m_mView, mproc->m_mProj, mproc->m_vLightDir, mproc->m_vEyePt, shineNum);
			}
		}
	}
}
//============================================================================
//  �}�b�v�v���V�[�W���̃����_�����O ���̂Q
// 
//  �������̃}�b�v�I�u�W�F�N�g��`�悷�邽�߁A�僋�[�v�̍Ō�Ɏ��s�����
// 
//    �����@�@�Ȃ�
// 
//    �߂�l�@�Ȃ�
//============================================================================
void  CMapProc::Render2(void)
{
	int shineFlag = 0;
	if (m_bActive) {

		// �}�b�v�����_�����O
		for (DWORD i = 0; i<m_StageMap.size(); i++)
		{
			if (MapNumGet() == 3 && (i == 2 || i == 3)) {
				shineFlag = 2;
				m_StageMap[i].m_pMesh->Render(m_StageMap[i].m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, VECTOR3(0, 0, 0), m_pGMain->m_vEyePt, shineFlag);
				shineFlag = 0;
			}
			else if (MapNumGet() == 3 && (i == 4 || i == 5)) {
				shineFlag = 4;
				m_StageMap[i].m_pMesh->Render(m_StageMap[i].m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, VECTOR3(0, 0, 0), m_pGMain->m_vEyePt, shineFlag);
				shineFlag = 0;
			}
			if (m_StageMap[i].m_nMaterialFlag == 1)  // �����F�̃u�����h�X�e�[�g
			{
				// �����F�̃����_�����O
				if (m_StageMap[i].m_pMesh) m_StageMap[i].m_pMesh->Render(m_StageMap[i].m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, VECTOR3(0, 0, 0), m_pGMain->m_vEyePt, shineFlag);
			}
		}

		// �ړ��}�b�v�����_�����O     * ���̃v���O�����ł͎g�p���Ă��Ȃ�
		for (DWORD i = 0; i<m_MoveMap.size(); i++)
		{
			if (m_MoveMap[i].m_nMaterialFlag == 1)  // �����F�̃u�����h�X�e�[�g
			{
				if (m_MoveMap[i].m_pMesh && m_MoveMap[i].m_bActive)	m_MoveMap[i].m_pMesh->Render(m_MoveMap[i].m_pColMesh->m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt, shineFlag);
			}
		}

		// �g�̃����_�����O
		for (DWORD i = 0; i<m_StageMap.size(); i++)
		{
			if (m_StageMap[i].m_nMaterialFlag == 3)  
			{
				// �g�����_�����O
				if (m_StageMap[i].m_pWave)
					m_StageMap[i].m_pWave->Render(m_StageMap[i].m_mWorld, m_pGMain->m_mView, m_pGMain->m_mProj, m_pGMain->m_vLightDir, m_pGMain->m_vEyePt);
			}
		}

	}
}

