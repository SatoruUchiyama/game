//=============================================================================
//
// ���C������ [number.h]
// Author : Satoru Uchiyama
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

//=====================================
//	�w�b�_�[�ǂݍ���
//=====================================
#include "main.h"
#include "scene.h"

//=====================================
//	�}�N����`
//=====================================
//=====================================
//	�O���錾
//=====================================
class CNumber;

//=====================================
//	Score�N���X
//=====================================
class CScore :public  CScene
{
public:
	CScore();
	~CScore();

	//�X�R�A�̏���������
	HRESULT Init(void);
	//�X�R�A�̏I������
	void Uninit(void);
	//�X�R�A�̍X�V����
	void Update(void);
	//�X�R�A�̕`�揈��
	void Draw(void);
	int GetScore(void);
	//�X�R�A�̃N���G�C�g
	static CScore *Create(D3DXVECTOR3 pos);

	static void AddScore(int nValue);

//	void SetScore(int nScore);
	//int GetScore(void);
private:
	//Number�̃|�C���^
	static CNumber *m_pNumber[8];
	//
	int m_nScore;

	//�ԍ��̋L��
	static int m_nKioku;
};
#endif