//=============================================================================
//
// サウンド処理 [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

//=====================================
//ヘッダー読み込み
//=====================================
#include "main.h"


//=====================================
//	Sound(音)クラス
//=====================================
class CSound
{
public:
	//*************************************
	// サウンドファイル
	//*************************************
	typedef enum
	{
		SOUND_LABEL_BGM000 = 0,		// BGM0
		SOUND_LABEL_BGM001,			// BGM1
		SOUND_LABEL_BGM002,			// BGM2
		SOUND_LABEL_SE_SHOT,		// 弾発射音
		SOUND_LABEL_SE_HIT000,		// ヒット音0
		SOUND_LABEL_SE_HIT001,		// ヒット音1
		SOUND_LABEL_SE_EXPLOSION,	// 爆発音
		SOUND_LABEL_SE_DECIDE,		// 決定音
		SOUND_LABEL_SE_POTATO1,		// リザルトSE
		SOUND_LABEL_SE_POTATO2,		// 爆発　敵
		SOUND_LABEL_SE_POTATO3,		//　和風SE
		SOUND_LABEL_SE_POTATO4,		// 決定音.wav
		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	typedef struct
	{
		// ファイル名
		char *pFilename;
		// ループカウント(-1でループ再生)
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
	IXAudio2 *m_pXAudio2 = NULL;								// XAudio2オブジェクトへのポインタ
	IXAudio2MasteringVoice *m_pMasteringVoice = NULL;			// マスターボイスへのポインタ
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX] = {};	// ソースボイスへのポインタ
	BYTE *m_apDataAudio[SOUND_LABEL_MAX] = {};					// オーディオデータへのポインタ
	DWORD m_aSizeAudio[SOUND_LABEL_MAX] = {};					// オーディオデータサイズ

	CSound::SOUNDPARAM m_aSoundParam[SOUND_LABEL_MAX] =
	{
		{ "deta/BGM/曲.wav", -1 },		// BGM0
		{ "deta/BGM/bgm001.wav", -1 },		// BGM1
		{ "deta/BGM/arbia.wav", -1 },		// BGM2
		{ "deta/SE/shot000.wav", 0 },			// 弾発射音
		{ "deta/SE/nanndeyznenn.wav", 0 },			// ヒット音0
		{ "deta/SE/hit001.wav", 0 },			// ヒット音1
		{ "deta/SE/explosion000.wav", 0 },	// 爆発音
		{ "deta/SE/decide000.wav", 0 },		// 選択音
		{ "deta/SE/ドカーン1.wav",0 },		// リザルトSE
		{ "deta/SE/ピュン1.wav",0 },		// 爆発　敵	
		{ "deta/SE/ボカッ1.wav",0 },			//和風SE
		{ "deta/SE/始まるよ1.wav",0 }			//決定音
	};

};

#endif
