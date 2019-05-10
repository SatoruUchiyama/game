//=============================================================================
//
// ���C������ [explosion.h]
// Author : Satoru Uchiyama
//
//=============================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

//=====================================
//�w�b�_�[�ǂݍ���
//=====================================
#include "main.h"
#include "scene2d.h"

//====================================
//	�}�N����`
//====================================
#define MAX_COUNTER		(5)
#define MAX_PATTERN		(8)
#define UV_U			(0.125f)
#define UV_V			(1.0f)

//=====================================
//	Explosion(����)�N���X
//=====================================
class CExplosion : public CScene2d
{
public:
	CExplosion();
	~CExplosion();

	//Texture�̓ǂݍ���
	static HRESULT Lood(void);
	//�e�N�X�`���̔j��
	static void Unlood(void);

	//�����̃N���G�C�g
	static CExplosion*Create(D3DXVECTOR3 posExplosion);

	//�|���S���̏���������
	HRESULT Init(D3DXVECTOR3 posExplosion);
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
	//�A�j���[�V�����̃J�E���g
	int m_nCounterAnimation;
	//�A�j���[�V�����̃p�^�[��
	int m_nPatternAnimation;
};
#endif