//=============================================================================
//
// ���C������ [manager.h]
// Author : Satoru Uchiyama
//
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

//=====================================
//�w�b�_�[�ǂݍ���
//=====================================
#include "main.h"

//=====================================
//	�O���錾
//=====================================
class CInputKeyboard;
class CInputJoystick;
class CSound;
class CGame;
class CTitle;
class CResult;
class CRanking;
class CTutorial;
class CFade;
//=====================================
//	Manager�N���X
//=====================================
class CManager
{
public:
	//�\����
	typedef enum
	{
		MODE_TITLE = 0,
		MODE_GAME,
		MODE_RESULT,
		MODE_RANKING,
		MODE_TUTORIAL,
		MODE_MAX
	}MODE;

	CManager();
	~CManager();

	//����������
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);
	//�I������
	void Uninit(void);
	//�X�V����
	void Update(void);
	//�`�揈��
	void Draw(void);

	//�����_���[�̎擾
	static CRenderer *GetRenderer(void);
	//�C���v�b�g�̎擾
	static CInputKeyboard *GetInput(void) { return m_pInputKeyboard; };
	//
	static CInputJoystick *GetInputJoystick(void) { return m_pInputJoystick; };
	//�T�E���h�̎擾
	static CSound *GetCSound(void) { return m_psound; };
	static CFade *GetFade(void){ return m_pFade; };
	static MODE GetMode(void) { return m_mode; };
	//
	static void SetMode(MODE mode);
	static CRanking *GetRaning(void) { return m_pRanking; };
private:
	//
	static MODE m_mode;
	//Scene2d�̃|�C���^
	CScene2d  *m_pScene2d;
	//�����_���[�̃|�C���^
	static CRenderer *m_pRenderer;
	//�L�[�{�[�h�̃|�C���^
	static CInputKeyboard *m_pInputKeyboard;
	//
	static CInputJoystick *m_pInputJoystick;
	//�T�E���h�̃|�C���^
	static CSound *m_psound;

	static CGame *m_pGame;

	static CTitle *m_pTitle;

	static CFade *m_pFade;

	static CResult *m_pResult;

	static CRanking *m_pRanking;

	static CTutorial *m_pTutorial;
	//
};
#endif