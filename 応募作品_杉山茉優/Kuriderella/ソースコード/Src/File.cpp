//=============================================================================
//		�Q�c�A�N�V�����Q�[���v���O����
//		�b�Q�c�`�����P�P�S�@�@�@�@�@�@           ver 2.8        2020.2.15
//
//		�t�@�C�����͂̏���
//																File.cpp
//=============================================================================

#include "Map.h"

//-----------------------------------------------------------------------------
// �}�b�v�t�@�C���̓ǂݍ���
//
//   �����@�@�@TCHAR* FName
//             CMap* &pMap
//-----------------------------------------------------------------------------
BOOL	CMapProc::MapRead( TCHAR* FileName, CMap* &pMap)
{
	const int BUFSIZE = 2048;                        // -- 2020.2.15
	FILE    *fp;
	TCHAR   szWork[BUFSIZE], ww[BUFSIZE];
	TCHAR   *p, *s;


	//fp = _tfopen(FileName, _T("r, ccs = UNICODE"));	// �X�N���v�g�ǂݍ���(Unicode�œǂݍ���)
	fp = _tfopen(FileName, _T("r"));	// �X�N���v�g�ǂݍ���
	if (fp) {

		SAFE_DELETE(pMap);		// �ȑO�̃}�b�v���폜����
		pMap = new CMap(m_pGMain);		// �}�b�v�̐���

		_tcscpy(pMap->m_MapFileName, FileName);   // �}�b�v����ۑ����Ă���  // -- 2019.3.5

		while (_fgetts(szWork, BUFSIZE, fp) != NULL)  // �t�@�C���̍Ō�ɒB����܂ň�s�Âǂݍ���
		{
			s = _tcsstr(szWork, _T("\n"));      // ������̍Ō��\n���폜����
			if (s != NULL)
			{
				*s = _T('\0');
			}

			if (_tcsncmp(szWork, _T("@MapData"), 8) == 0)  // �}�b�v�S�̂Ɋւ���f�[�^
			{
				_stscanf_s(szWork, _T("%s %d, %d, %d, %d, %s"), ww, sizeof(ww) / sizeof(TCHAR), &pMap->m_nMapX, &pMap->m_nMapY,
					&pMap->m_nMapchipWidth, &pMap->m_nMapchipHeight, pMap->m_ImageName, sizeof(pMap->m_ImageName) / sizeof(TCHAR));
				// �}�b�v�̏�����
				pMap->InitMap();
			}
			else if (_tcsncmp(szWork, _T("@Back"), 5) == 0)  // ��i�}�b�v�f�[�^
			{

				_stscanf_s(szWork, _T("%s"), ww, sizeof(ww) / sizeof(TCHAR));  // �^�C�g���s

				for (int y = 0; y < pMap->m_nMapY; y++)  // �}�b�v�f�[�^
				{
					if (_fgetts(szWork, BUFSIZE, fp) == NULL) break;  // ��s�ǂݍ��ށB�f�[�^���Ȃ��Ȃ�����I��
					s = _tcsstr(szWork, _T("\n"));      // ������̍Ō��\n���폜����
					if (s != NULL)
					{
						*s = _T('\0');
					}
					p = szWork;
					for (int x = 0; x < pMap->m_nMapX; x++)
					{
						_stscanf_s(p, _T("%d,"), &pMap->m_MapBakTbl[y*pMap->m_nMapX + x]);
						p = _tcschr(p, _T(','));
						p++;
					}
				}
			}
			else if (_tcsncmp(szWork, _T("@Fore"), 5) == 0) {  // �O�i�}�b�v�f�[�^

				_stscanf_s(szWork, _T("%s"), ww, sizeof(ww) / sizeof(TCHAR));  // �^�C�g���s

				for (int y = 0; y < pMap->m_nMapY; y++)  // �}�b�v�f�[�^
				{
					if (_fgetts(szWork, BUFSIZE, fp) == NULL) break;  // ��s�ǂݍ��ށB�f�[�^���Ȃ��Ȃ�����I��
					s = _tcsstr(szWork, _T("\n"));      // ������̍Ō��\n���폜����
					if (s != NULL)
					{
						*s = _T('\0');
					}
					p = szWork;
					for (int x = 0; x < pMap->m_nMapX; x++)
					{
						_stscanf_s(p, _T("%d,"), &pMap->m_MapForTbl[y*pMap->m_nMapX + x]);
						p = _tcschr(p, _T(','));
						p++;
					}
				}
			}
			else if (_tcsncmp(szWork, _T("@MapLine"), 8) == 0) {  // �}�b�v���f�[�^

				_stscanf_s(szWork, _T("%s %d"), ww, sizeof(ww) / sizeof(TCHAR), &pMap->m_nMapLnLength);  // �^�C�g���s

				pMap->m_MapLn = new CMapLine[pMap->m_nMapLnLength];

				for (int i = 0; i < pMap->m_nMapLnLength; i++)  // �}�b�v���f�[�^
				{
					if (_fgetts(szWork, BUFSIZE, fp) == NULL) break;  // ��s�ǂݍ��ށB�f�[�^���Ȃ��Ȃ�����I��
					s = _tcsstr(szWork, _T("\n"));      // ������̍Ō��\n���폜����
					if (s != NULL)
					{
						*s = _T('\0');
					}
					p = szWork;
					_stscanf_s(p, _T("%f,"), &pMap->m_MapLn[i].m_vStart.x);
					p = _tcschr(p, _T(','));
					p++;
					_stscanf_s(p, _T("%f,"), &pMap->m_MapLn[i].m_vStart.y);
					p = _tcschr(p, _T(','));
					p++;
					_stscanf_s(p, _T("%f,"), &pMap->m_MapLn[i].m_vEnd.x);
					p = _tcschr(p, _T(','));
					p++;
					_stscanf_s(p, _T("%f,"), &pMap->m_MapLn[i].m_vEnd.y);
					p = _tcschr(p, _T(','));
					p++;
					_stscanf_s(p, _T("%f,"), &pMap->m_MapLn[i].m_vNormal.x);
					p = _tcschr(p, _T(','));
					p++;
					_stscanf_s(p, _T("%f,"), &pMap->m_MapLn[i].m_vNormal.y);
					p = _tcschr(p, _T(','));
					p++;
				}
			}

			else if (_tcsncmp(szWork, _T("@EvtMap"), 7) == 0) {  // �C�x���g�}�b�v�f�[�^

				_stscanf_s(szWork, _T("%s %d"), ww, sizeof(ww)/sizeof(TCHAR), &pMap->m_nEvtMapLength);  // �^�C�g���s
				pMap->m_EvtMap = new CEvtMap[pMap->m_nEvtMapLength];

				for (int i = 0; i < pMap->m_nEvtMapLength; i++)  // �C�x���g�}�b�v�f�[�^
				{
					if (_fgetts(szWork, BUFSIZE, fp) == NULL) break;  // ��s�ǂݍ��ށB�f�[�^���Ȃ��Ȃ�����I��
					s = _tcsstr(szWork, _T("\n"));      // ������̍Ō��\n���폜����
					if (s != NULL)
					{
						*s = _T('\0');
					}
					p = szWork;

					_stscanf_s(p, _T("%f,"), &pMap->m_EvtMap[i].m_vStart.x);
					p = _tcschr(p,_T(','));
					p++;
					_stscanf_s(p, _T("%f,"), &pMap->m_EvtMap[i].m_vStart.y);
					p = _tcschr(p,_T(','));
					p++;

					_stscanf_s(p, _T("%d,"), &pMap->m_EvtMap[i].m_nEvtID);
					p = _tcschr(p,_T(','));
					p++;
					_stscanf_s(p, _T("%x,"), &pMap->m_EvtMap[i].m_dwEvtNo);
					p = _tcschr(p,_T(','));
					p++;
					_stscanf_s(p, _T("%d,"), &pMap->m_EvtMap[i].m_nCnt1);
					p = _tcschr(p,_T(','));
					p++;
				}
			}
			else {
				;  // �^�C�g���̂Ȃ��s�͓ǂݔ�΂�
			}
		}
		fclose(fp);
	}
	return TRUE;
}

