//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

//=====================================
//�w�b�_�[�ǂݍ���
//=====================================
#include "main.h"


//=====================================
//	Sound(��)�N���X
//=====================================
class CSound
{
public:
	//*************************************
	// �T�E���h�t�@�C��
	//*************************************
	typedef enum
	{
		SOUND_LABEL_BGM000 = 0,		// BGM0
		SOUND_LABEL_BGM001,			// BGM1
		SOUND_LABEL_BGM002,			// BGM2
		SOUND_LABEL_SE_SHOT,		// �e���ˉ�
		SOUND_LABEL_SE_HIT000,		// �q�b�g��0
		SOUND_LABEL_SE_HIT001,		// �q�b�g��1
		SOUND_LABEL_SE_EXPLOSION,	// ������
		SOUND_LABEL_SE_DECIDE,		// ���艹
		SOUND_LABEL_SE_POTATO1,		// ���U���gSE
		SOUND_LABEL_SE_POTATO2,		// �����@�G
		SOUND_LABEL_SE_POTATO3,		//�@�a��SE
		SOUND_LABEL_SE_POTATO4,		// ���艹.wav
		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	typedef struct
	{
		// �t�@�C����
		char *pFilename;
		// ���[�v�J�E���g(-1�Ń��[�v�Đ�)
		int nCntLoop;
	} SOUNDPARAM;

	CSound();
	~CSound();
	HRESULT InitSound(HWND hWnd);
	void UninitSound(void);
	HRESULT PlaySound(SOUND_LABEL label);
	void StopSound(SOUND_LABEL label);
	void StopSound(void);
private:
	IXAudio2 *m_pXAudio2 = NULL;								// XAudio2�I�u�W�F�N�g�ւ̃|�C���^
	IXAudio2MasteringVoice *m_pMasteringVoice = NULL;			// �}�X�^�[�{�C�X�ւ̃|�C���^
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX] = {};	// �\�[�X�{�C�X�ւ̃|�C���^
	BYTE *m_apDataAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^�ւ̃|�C���^
	DWORD m_aSizeAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^�T�C�Y

	CSound::SOUNDPARAM m_aSoundParam[SOUND_LABEL_MAX] =
	{
		{ "deta/BGM/��.wav", -1 },		// BGM0
		{ "deta/BGM/bgm001.wav", -1 },		// BGM1
		{ "deta/BGM/arbia.wav", -1 },		// BGM2
		{ "deta/SE/shot000.wav", 0 },			// �e���ˉ�
		{ "deta/SE/nanndeyznenn.wav", 0 },			// �q�b�g��0
		{ "deta/SE/hit001.wav", 0 },			// �q�b�g��1
		{ "deta/SE/explosion000.wav", 0 },	// ������
		{ "deta/SE/decide000.wav", 0 },		// �I����
		{ "deta/SE/�h�J�[��1.wav",0 },		// ���U���gSE
		{ "deta/SE/�s����1.wav",0 },		// �����@�G	
		{ "deta/SE/�{�J�b1.wav",0 },			//�a��SE
		{ "deta/SE/�n�܂��1.wav",0 }			//���艹
	};

};

#endif
