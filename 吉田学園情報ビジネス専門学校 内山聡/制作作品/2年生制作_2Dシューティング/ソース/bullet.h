//=============================================================================
//
// ���C������ [bullet.h]
// Author : Satoru Uchiyama
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

//=====================================
//�w�b�_�[�ǂݍ���
//=====================================
#include "main.h"
#include "scene2d.h"

//=====================================
//	Bullet(�e)�N���X
//=====================================
class CBullet : public CScene2d
{
public:

	//�񋓌^
	typedef enum
	{
		BULLET_TYPE_NONE = 0,
		BULLET_TYPE_ENEMY,
		BULLET_TYPE_PLAYER,
		BULLET_TYPE_MAX
	}TYPE_BULLET;

	CBullet();
	~CBullet();
	//Texture�̓ǂݍ���
	static HRESULT Lood(void);
	//Texture�̔j��
	static void Unlood(void);

	//�e�̃N���G�C�g
	static CBullet*Create(D3DXVECTOR3 moveC, TYPE_BULLET type);

	//	�e�̏���������
	HRESULT Init(D3DXVECTOR3 moveBullet, TYPE_BULLET type);
	//	�e�̏I������
	void Uninit(void);			
	//	�e�̍X�V����
	void Update(void);
	//	�e�̕`�揈��
	void Draw(void);

private:
	//Texture�̃|�C���^
	static LPDIRECT3DTEXTURE9 m_pTexture;
	//�ړ���
	D3DXVECTOR3 m_move;
	//�e�̗̑�
	int m_nLife;
	//�e�̋��(�N�̒e��)
	TYPE_BULLET m_BulletType;
};
#endif