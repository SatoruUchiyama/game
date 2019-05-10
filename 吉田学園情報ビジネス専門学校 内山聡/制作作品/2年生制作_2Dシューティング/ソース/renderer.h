//=============================================================================
//
// ���C������ [renderer.h]
// Author : Satoru Uchiyama
//
//=============================================================================
#ifndef _RENDERER_H_
#define _RENDERER_H_

//=====================================
//�w�b�_�[�ǂݍ���
//=====================================
#include "main.h"

class CPauselogo;
//=====================================
//	Renderer�N���X
//=====================================
class CRenderer
{
public:
	CRenderer();
	~CRenderer();

	//�����_���[�̏���������
	HRESULT Init(HWND hWnd, bool bWindow);
	//�����_���[�̏I������
	void Uninit(void);
	//�����_���[�̍X�V����
	void Update(void);
	//�����_���[�̕`�揈��
	void Draw(void);

	//�f�o�C�X�̎擾
	//LPDIRECT3DDEVICE9 GetDevice(void);
	LPDIRECT3DDEVICE9 GetDevice(void) { return m_pD3DDevice; };
private:
#ifdef _DEBUG
	void DrawFPS(void);
#endif
	bool m_bPause;
	CPauselogo *m_pPauseLogo;
	// Direct3D�I�u�W�F�N�g
	LPDIRECT3D9				m_pD3D = NULL;
	// Device�I�u�W�F�N�g(�`��ɕK�v)
	LPDIRECT3DDEVICE9		m_pD3DDevice = NULL;

	//FPS�̃J�E���g�����炤
	int m_FpsCount;
#ifdef _DEBUG
	// �t�H���g�ւ̃|�C���^
	LPD3DXFONT				m_pFont = NULL;
#endif
};
#endif

