//=============================================================================
//
// ���C������ [enemy.h]
// Author : Satoru Uchiyama
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

//=====================================
//	�w�b�_�[�ǂݍ���
//=====================================
#include "main.h"


//=====================================
//	Bg(�w�i)�N���X
//=====================================
class CTitle
{
public:
	CTitle();
	~CTitle();

	////Texture�̓ǂݍ���
	//static HRESULT Lood(void);
	////Texture�̔j��
	//static void Unlood(void);

	//�w�i�̃N���G�C�g
	static CTitle*Create(void);

	//	�w�i�̏���������
	HRESULT Init(void);
	//	�w�i�̏I������
	void Uninit(void);
	//	�w�i�̍X�V����
	void Update(void);
	//	�w�i�̕`�揈��
	void Draw(void);
private:
	int m_nTimeTitle;
};
#endif