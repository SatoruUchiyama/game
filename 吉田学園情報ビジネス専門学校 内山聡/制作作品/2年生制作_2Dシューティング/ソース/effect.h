//=============================================================================
//
// ���C������ [explosion.h]
// Author : Satoru Uchiyama
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

//=====================================
//�w�b�_�[�ǂݍ���
//=====================================
#include "main.h"
#include "scene2d.h"

//====================================
//	�}�N����`
//====================================

//=====================================
//	Explosion(����)�N���X
//=====================================
class CEffect : public CScene2d
{
public:
	CEffect();
	~CEffect();

	//Texture�̓ǂݍ���
	static HRESULT Lood(void);
	//�e�N�X�`���̔j��
	static void Unlood(void);

	//�����̃N���G�C�g
	static CEffect*Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, float fRadius, int Life, D3DXCOLOR color);

	//�|���S���̏���������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, float fRadius,int Life, D3DXCOLOR color);
	//�|���S���̏I������
	void Uninit(void);
	//�|���S���̍X�V����
	void Update(void);
	//�|���S���̕`�揈��
	void Draw(void);
private:
	// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;
	//�e�N�X�`���̂̃|�C���^
	static LPDIRECT3DTEXTURE9 m_pTexture;

	D3DXVECTOR3 m_Pos;
	int m_Life;
	float m_fRadius;
};
#endif