//=============================================================================
//
// ���C������ [enemy.h]
// Author : Satoru Uchiyama
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

//=====================================
//	�w�b�_�[�ǂݍ���
//=====================================
#include "main.h"


//=====================================
//	Bg(�w�i)�N���X
//=====================================
class CResult
{
public:
	CResult();
	~CResult();

	////Texture�̓ǂݍ���
	//static HRESULT Lood(void);
	////Texture�̔j��
	//static void Unlood(void);

	//�w�i�̃N���G�C�g
	static CResult*Create(void);

	//	�w�i�̏���������
	HRESULT Init(void);
	//	�w�i�̏I������
	void Uninit(void);
	//	�w�i�̍X�V����
	void Update(void);
	//	�w�i�̕`�揈��
	void Draw(void);
private:
};
#endif