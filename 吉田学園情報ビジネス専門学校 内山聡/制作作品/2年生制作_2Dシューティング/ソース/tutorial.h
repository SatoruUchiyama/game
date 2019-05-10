//=============================================================================
//
// ���C������ [enemy.h]
// Author : Satoru Uchiyama
//
//=============================================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

//=====================================
//	�w�b�_�[�ǂݍ���
//=====================================
#include "main.h"

//=====================================
//	Bg(�w�i)�N���X
//=====================================
class CTutorial
{
public:
	CTutorial();
	~CTutorial();

	//�w�i�̃N���G�C�g
	static CTutorial*Create(void);

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