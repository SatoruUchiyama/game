//=============================================================================
//
// ���C������ [player.h]
// Author : Satoru Uchiyama
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//=====================================
//�w�b�_�[�ǂݍ���
//=====================================
#include "main.h"
#include "scene2d.h"

#define MAX_PLAYER		(2)
//=====================================
//	Player(����L����)�N���X
//=====================================
class CPlayer : public CScene2d
{
public:
	//�񋓌^
	typedef enum
	{
		OBJTYPE_PLAYER_01 = 0,
		OBJTYPE_PLAYER_02,
		OBJTYPE_MAX
	}PLAYER_TYPE;
	//�񋓌^
	typedef enum
	{
		OBJTYPE_PLAYER_NORMAL = 0,
		OBJTYPE_PLAYER_PARTY,
		OBJTYPE_MAX2
	}PLAYER_PARTY_TYPE;

	CPlayer();
	~CPlayer();

	//Texture�̓ǂݍ���
	static HRESULT Lood(void);
	//Texture�̔j��
	static void Unlood(void);

	//����L�����̃N���G�C�g
	static CPlayer*Create(D3DXVECTOR3 posC , D3DXVECTOR3 size, PLAYER_TYPE type);

	//�v���C���[�̏���������
	HRESULT Init(D3DXVECTOR3 posPlay);
	//�v���C���[�̏I������
	void Uninit(void);
	//�v���C���[�̍X�V����
	void Update(void);
	//�v���C���[�̕`�揈��
	void Draw(void);
	//�_���[�W����
	void HitPlayer(int nDamage);

	D3DXVECTOR3 GetSize(void) { return m_size; }
private:
	//�e�N�X�`���̃|�C���^
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_PLAYER];
	D3DXVECTOR3 m_move;					//�ړ���
	D3DXVECTOR3 m_posPlayer;			//���W
	int m_nCountBullet;					//�e�̌��X�s�[�h���R���g���[��
	int m_nLife;
	PLAYER_TYPE m_type;
	PLAYER_PARTY_TYPE m_typeParty;
	D3DXVECTOR3 m_size;
	static int m_nCount;
};
#endif

