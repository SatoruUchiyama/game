//=============================================================================
//
// ���C������ [enemy.h]
// Author : Satoru Uchiyama
//
//=============================================================================
#ifndef _LOGO_H_
#define _LOGO_H_

//=====================================
//�w�b�_�[�ǂݍ���
//=====================================
#include "main.h"
#include "scene2d.h"


#define MAX_LOGO (5)
//=====================================
//	Enemy(�G)�N���X		CScene2d�̔h��
//=====================================
class CLogo : public CScene2d
{
public:
	//�񋓌^
	typedef enum
	{
		LOGO_TYPE_00,
		LOGO_TYPE_01,
		LOGO_TYPE_02,
		LOGO_TYPE_03,
		LOGO_TYPE_04,
		LOGO_TYPE_MAX
	}LOGO_TYPE;
	CLogo();
	~CLogo();

	//Texture�̓ǂݍ���
	static HRESULT Lood(void);
	//Texture�̔j��
	static void Unlood(void);

	//�w�i�̃N���G�C�g
	static CLogo*Create(D3DXVECTOR3 posC, LOGO_TYPE type, D3DXVECTOR3 size);

	//�G�̏���������
	HRESULT Init(D3DXVECTOR3 posPlay, D3DXVECTOR3 size);
	//�G�̏I������
	void Uninit(void);
	//�G�̍X�V����
	void Update(void);
	//�G�̕`�揈��
	void Draw(void);

private:
	//Texture�̃|�C���^
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_LOGO];
	//�ړ���
	D3DXVECTOR3 m_move[MAX_LOGO];
	//���W
	D3DXVECTOR3 m_pos;
	//�J�E���^�[
	int m_nCount;
	//�G�̗̑�
	int m_nLife;
	//
	LOGO_TYPE m_type;
	//
	D3DXVECTOR3 m_size;
};


#endif

