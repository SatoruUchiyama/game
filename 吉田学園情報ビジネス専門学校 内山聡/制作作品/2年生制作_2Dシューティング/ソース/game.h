//=============================================================================
//
// ���C������ [enemy.h]
// Author : Satoru Uchiyama
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

//=====================================
//	�w�b�_�[�ǂݍ���
//=====================================
#include "main.h"

class CScore;
//=====================================
//	GAME(�w�i)�N���X
//=====================================
class CGame
{
public:
	CGame();
	~CGame();

	////Texture�̓ǂݍ���
	//static HRESULT Lood(void);
	////Texture�̔j��
	//static void Unlood(void);

	//�w�i�̃N���G�C�g
	static CGame*Create(void);
	//static CPlayer*GetPlayer(int nIdx);
	//	�w�i�̏���������
	HRESULT Init(void);
	//	�w�i�̏I������
	void Uninit(void);
	//	�w�i�̍X�V����
	void Update(void);
	//	�w�i�̕`�揈��
	void Draw(void);

	static CScore *GetScore(void) { return m_score; };
private:
	//static CPlayer *m_pPlayer[2];
	static CScore *m_score;
};
#endif