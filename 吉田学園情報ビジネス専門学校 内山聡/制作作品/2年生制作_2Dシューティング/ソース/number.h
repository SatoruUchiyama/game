//=============================================================================
//
// ���C������ [number.h]
// Author : Satoru Uchiyama
//
//=============================================================================
#ifndef _NUMBER_H_
#define _NUMBER_H_

//=====================================
//	�w�b�_�[�ǂݍ���
//=====================================
#include "main.h"

//=====================================
//	�}�N����`
//=====================================
#define MAX_TRUSS		(8)
//=====================================
//	Number(��������)�N���X
//=====================================
class CNumber
{
public:
	CNumber();
	~CNumber();

	//�e�N�X�`���̓ǂݍ���
	static HRESULT Lood(void);
	//�e�N�X�`���̔j��
	static void Unlood(void);

	//�����̏���������
	HRESULT Init(D3DXVECTOR3 pos);
	//�����̏I������
	void Uninit(void);
	//�����̍X�V����
	void Update(void);
	//�����̕`�揈��
	void Draw(void);
	void DrawScore(int nKioku);
	//�����̃Z�b�g
	//void SetNumber(int nNumber);
private:
	// �e�N�X�`���ւ̃|�C���^
	static LPDIRECT3DTEXTURE9	m_pTexture;
	// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
};
#endif