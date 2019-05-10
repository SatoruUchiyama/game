
//*****************************************************************************
//
//	�w�i�̏����ibg,h�j
//	Author : uchiyama
//
//*****************************************************************************
#ifndef _RANKING_H_
#define _RANKING_H_

#include "scene.h"
#define MAX_RANKING   (6)
#define MAX_NUMBER    (6)
class CNumber;
//�N���X�i�V�[���̔h���N���X�j
class CRanking
{
public:
	CRanking();											//�R���X�g���N�^
	~CRanking();										//�f�X�g���N�^

	HRESULT Init(void);									//����������
	void Uninit(void);									//�I������
	void Update(void);									//�X�V����
	void Draw(void);									//�`�揈��

														//�ÓI�����o�֐�
	static CRanking *Create(void);
	static void SaveRanking(void);
	static void LoadRanking(void);

private:
	static CNumber *m_apNumber[MAX_RANKING][MAX_NUMBER]; //�X�R�A�����\�����邩�F�������ɂ��邩

	D3DXVECTOR3				m_move;						// �|���S���̈ʒu
	D3DXCOLOR				m_col;						// �|���S���̈ʒu
	static int m_RankScore[MAX_RANKING];
	int m_nTimeRanking;
	static int m_nType;
};
#endif