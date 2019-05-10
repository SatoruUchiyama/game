//=============================================================================
//
// �|�[�Y���j���[���� [pauseselect.h]
// Author : 
//
//=============================================================================
#ifndef _PAUSESELECT_H_
#define _PAUSESELECT_H_

#include "main.h"
#include "scene.h"

class CScene2d;

//*****************************************************************************
// �}�N����`
//****************************************************************************
#define PAUSESELECT_POS_X			(200)						//���_���WX�̈ړ���
#define PAUSESELECT_POS_Y			(50)						//���_���WY�̈ړ���
#define TEX_LEFT				(0.0f)						//�e�N�X�`�����WU��
#define TEX_RIGHT				(1.0f)						//�e�N�X�`�����WU�E
#define TEX_TOP					(0.0f)						//�e�N�X�`�����WV��
#define TEX_BOT					(1.0f)						//�e�N�X�`�����WV��
#define MAX_PAUSEMENU			(3)							//�����L���O�̐�

class CPauselogo : public CScene
{
public:
	typedef enum
	{
		SELECTMODE_CONTINUE = 0,		//���s���
		SELECTMODE_RETRY,			//���g���C���
		SELECTMODE_QUIT,			//�I��
		SELECTMODE_MAX				//��Ԃ̑���
	}SELECTMODE;						//�񋓌^

	CPauselogo(int nPriority = 7);
	~CPauselogo();

	//Texture�̓ǂݍ�
	static HRESULT Lood(void);
	//Texture�̔j��
	static void Unlood(void);
	//����L�����̃N���G�C�g
	static CPauselogo*Create(D3DXVECTOR3 pos,float fwidth, float fheight);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static SELECTMODE GetMode(void);
	int GetSelect(void);
private:
	D3DXVECTOR3 m_pos;
	float m_fwidth;
	float m_fheight;
	int	m_nSelect;
	static SELECTMODE m_Mode;
	D3DXCOLOR m_color[MAX_PAUSEMENU];
	CScene2d *m_apScene2D[MAX_PAUSEMENU];
	//�e�N�X�`���̃|�C���^
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_PAUSEMENU];

	float m_fMenuPosY;
	// ���_�o�b�t�@�ւ̃|�C���^
};
#endif