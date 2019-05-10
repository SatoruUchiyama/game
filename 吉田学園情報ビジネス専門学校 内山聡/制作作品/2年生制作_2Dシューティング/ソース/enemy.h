//=============================================================================
//
// ���C������ [enemy.h]
// Author : Satoru Uchiyama
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

//=============================================================================
//�w�b�_�[�ǂݍ���
//=============================================================================
#include "main.h"
#include "scene2d.h"

#define END_ENEMY (3)

#define MAX_ENEMY		(5)			//�A�C�e���̎��
//=============================================================================
//	Enemy(�G)�N���X		CScene2d�̔h��
//=============================================================================
class CEnemy : public CScene2d
{
public:
	//�񋓌^
	typedef enum
	{
		ENEMY_TARGET_01,		//�ړ��p�^�[��
		ENEMY_TARGET_02,		//�ړ��p�^�[��
		ENEMY_TARGET_03,		//�A�C�e�����o��G
		ENEMY_TARGET_04,		//�`���[�g���A���p
		ENEMY_TARGET_05,
		ENEMY_MAX
	}ENEMY_TYPE;

	CEnemy();
	~CEnemy();

	//	Texture�̓ǂݍ���
	static HRESULT Lood(void);

	//	Texture�̔j��
	static void Unlood(void);

	//	�w�i�̃N���G�C�g
	static CEnemy*Create(D3DXVECTOR3 posC, ENEMY_TYPE type,int nLife,D3DXVECTOR3 size);

	//	�G�̏���������
	HRESULT Init(D3DXVECTOR3 posPlay,int nLife, D3DXVECTOR3 size);

	//	�G�̏I������
	void Uninit(void);

	//	�G�̍X�V����
	void Update(void);

	//	�G�̕`�揈��
	void Draw(void);

	//	�_���[�W����
	void HitEnemy(int nDamage);

private:
	//	Texture�̃|�C���^
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_ENEMY];
	//	�ړ���
	D3DXVECTOR3 m_move[MAX_ENEMY];
	//	���W
	D3DXVECTOR3 m_posEnemy[MAX_ENEMY];

	//	�J�E���^�[
	int m_nCountEnemy;

	//	�G�̗̑�
	int m_nLife;

	//�G�̃^�C�v
	ENEMY_TYPE m_EnemyType;

	static int nCountEnemyEnd;
	//	�G�̒e
	int m_nCountBullet_Enemy;
};


#endif

