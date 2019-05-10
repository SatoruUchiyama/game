//=============================================================================
//
// �t�F�[�h���� [fade.h]
// Author : 
//
//=============================================================================
#ifndef _FADE_H_
#define _FADE_H_

#include "main.h"
#include "manager.h"
class CManager;
class CFade
{
public:
	CFade();
	~CFade();
	//*************************************
	// �t�F�[�h�̏��
	//*************************************
	typedef enum
	{
		FADE_NONE = 0,		// �������Ă��Ȃ����
		FADE_IN,			// �t�F�[�h�C�����
		FADE_OUT,			// �t�F�[�h�A�E�g���
		FADE_MAX
	} FADE;

	//����L�����̃N���G�C�g
	static CFade*Create(void);
	//*****************************************************************************
	// �v���g�^�C�v�錾
	//*****************************************************************************
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Set(CManager::MODE ModeNext);

	FADE Get(void);
	
	void MakeVertexFade(LPDIRECT3DDEVICE9 pDevice);
private:
	LPDIRECT3DTEXTURE9		m_pTextureFade = NULL;	// �e�N�X�`���ւ̃|�C���^
		LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffFade = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
	static FADE					m_fade;					// �t�F�[�h���
	static CManager::MODE					m_modeNext;				// ���̃��[�h
	static D3DXCOLOR				m_colorFade;			// �t�F�[�h�F

};

#endif