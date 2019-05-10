//=============================================================================
//
// ���C������ [bg.h]
// Author : Satoru Uchiyama
//
//=============================================================================
#ifndef _BG_H_
#define _BG_H_

//=====================================
//	�}�N����`
//=====================================
#define MAX_BG_TEXTURE		(4)			//	BG�̃e�N�X�`���̍ő吔
#define SPEED_BG_00			(0.0002f)	//	1���ڂ̃e�N�X�`���X�s�[�h
#define SPEED_BG_01			(0.0005f)	//	2���ڂ̃e�N�X�`���X�s�[�h
#define SPEED_BG_02  		(0.001f)	//	3���ڂ̃e�N�X�`���X�s�[�h
#define SPEED_BG_03			(0.004f)	//	4���ڂ̃e�N�X�`���X�s�[�h
//=====================================
//	�w�b�_�[�ǂݍ���
//=====================================
#include "main.h"
#include "scene.h"

//=====================================
//	�O���錾
//=====================================
class CScene2D;

//=====================================
//	Bg(�w�i)�N���X
//=====================================
class CBg : public CScene
{
public:
	CBg();
	~CBg();

	//Texture�̓ǂݍ���
	static HRESULT Lood(void);
	//Texture�̔j��
	static void Unlood(void);

	//�w�i�̃N���G�C�g
	static CBg*Create(void);

	//	�w�i�̏���������
	HRESULT Init(void);
	//	�w�i�̏I������
	void Uninit(void);
	//	�w�i�̍X�V����
	void Update(void);
	//	�w�i�̕`�揈��
	void Draw(void);
private:
	//Texture�̃|�C���^
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_BG_TEXTURE];
	CScene2d *m_pScene2d[MAX_BG_TEXTURE];
	float m_texBase[MAX_BG_TEXTURE];

	//�ړ���
	D3DXVECTOR3 m_move;
};
#endif