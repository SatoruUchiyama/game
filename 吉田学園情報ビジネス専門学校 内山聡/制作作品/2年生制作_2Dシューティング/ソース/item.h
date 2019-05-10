//=============================================================================
//
// ���C������ [enemy.h]
// Author : Satoru Uchiyama
//
//=============================================================================
#ifndef _ITEM_H_
#define _ITEM_H_

//=====================================
//�w�b�_�[�ǂݍ���
//=====================================
#include "main.h"
#include "scene2d.h"


#define MAX_X	(-15.0f)			//�ړ���
#define MAX_Y	(-30.0f)			//�ړ���
#define MAX_ITEM		(3)			//�A�C�e���̎��
//=====================================
//	Enemy(�G)�N���X		CScene2d�̔h��
//=====================================
class CItem : public CScene2d
{
public:
	//�񋓌^
	typedef enum
	{
		ITEM_RECOVERY_01,		//	����
		ITEM_RECOVERY_02,		//	����
		ITEM_RECOVERY_03,		//	���
		ITEM_MAX
	}ITEM_TYPE;
	CItem();
	~CItem();

	//Texture�̓ǂݍ���
	static HRESULT Lood(void);

	//Texture�̔j��
	static void Unlood(void);

	//�w�i�̃N���G�C�g
	static CItem*Create(D3DXVECTOR3 posC, ITEM_TYPE type);

	//�G�̏���������
	HRESULT Init(D3DXVECTOR3 posPlay);

	//�G�̏I������
	void Uninit(void);

	//�G�̍X�V����
	void Update(void);

	//�G�̕`�揈��
	void Draw(void);

	//�_���[�W����
	void HitItem(int nDamage,D3DXVECTOR3 pos);

private:
	//Texture�̃|�C���^
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_ITEM];
	//�ړ���
	D3DXVECTOR3 m_move;
	//���W
	D3DXVECTOR3 m_posItem;
	//�J�E���^�[
	int m_nCountEnemy;
	//�^�C�v�̃����o
	ITEM_TYPE m_type;
	//�G�̗̑�
	int m_nLife;
};


#endif

