//*****************************************************************************
//
//     シーンの処理[scene.h]
//     Auther:Hodaka Niwa
//
//*****************************************************************************
#ifndef _SCENE_H_
#define _SCENE_H_

//*****************************************************************************
//    インクルードファイル
//*****************************************************************************
#include "main.h"

//*****************************************************************************
//     マクロ定義
//*****************************************************************************
#define MAX_PRIORITY_NUM (12)     // 処理の優先順位の最大数
#define MAX_SCENE        (3000)   // シーンを作る数

//*****************************************************************************
//    シーンクラスの定義
//*****************************************************************************
class CScene
{
public:    // 誰でもアクセス可能
	//------------------------
	//  オブジェクトの種類
	//------------------------
	typedef enum
	{
		OBJTYPE_NONE = -1,     // 無し
		OBJTYPE_TITLE,         // タイトル
		OBJTYPE_TUTORIAL,      // チュートリアル
		OBJTYPE_GAME,          // ゲーム
		OBJTYPE_RESULT,        // リザルト
		OBJTYPE_RANKING,       // ランキング
		OBJTYPE_PAUSE,         // ポーズ
		OBJTYPE_2DPOLYGON,     // 2Dポリゴン
		OBJTYPE_3DPOLYGON,     // 3Dポリゴン
		OBJTYPE_BILLBOARD,     // ビルボード
		OBJTYPE_XFILEMODEL,    // Xファイルモデル
		OBJTYPE_MESHFIELD,     // メッシュフィールド(地面)
		OBJTYPE_MESHCYLINDER,  // メッシュシリンダー(円筒)
		OBJTYPE_MESHDOME,      // メッシュドーム(半球)
		OBJTYPE_MESHSPHERE,    // メッシュスフィア(球)
		OBJTYPE_MESHORBIT,     // メッシュオービット(軌跡)
		OBJTYPE_CHARACTER,     // キャラクター
		OBJTYPE_PLAYER,        // プレイヤー
		OBJTYPE_PLAYERMANAGER, // プレイヤー管轄クラス
		OBJTYPE_ENEMY,         // エネミー
		OBJTYPE_ENEMYMANAGER,  // エネミー管轄クラス
		OBJTYPE_EMITTER,       // エミッター
		OBJTYPE_PARTICLE,      // パーティクル
		OBJTYPE_ORBITEFFECT,   // 軌跡エフェクト
		OBJTYPE_EFFECTMANAGER, // エフェクト管轄クラス
		OBJTYPE_SKY,           // 空
		OBJTYPE_MOUNTAIN,      // 山
		OBJTYPE_OBJECT,        // 配置物
		OBJTYPE_OBJECTMOVE,    // 動く配置物
		OBJTYPE_OBJECTGOAL,    // ゴール用配置物
		OBJTYPE_GAUGE,         // ゲージ
		OBJTYPE_LIFEGAUGE,     // 体力ゲージ
		OBJTYPE_TIMER,         // タイマー
		OBJTYPE_SCORE,         // スコア
		OBJTYPE_STOCK,         // 残機
		OBJTYPE_PRESENT,       // プレゼント
		OBJTYPE_UI,			   // UI
		OBJTYPE_BILLPRESENT,   // プレゼント用ビルボード
		OBJTYPE_MAX
	}OBJTYPE;

	CScene(int nPriority = 3, OBJTYPE objType = OBJTYPE_NONE);
	virtual ~CScene();

	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	static int GetNumAll(void);
	static void UpdateAll(void);
	static void DrawAll(void);
	static void ReleaseAll(void);
	static void DeathCheck(void);
	static CScene *GetTop(int nPriority);

	void SetObjType(OBJTYPE ObjType);
	OBJTYPE GetObjType(void);
	CScene *GetNext(void);
	CScene *GetPrev(void);
	int GetPriority(void);

protected: // このクラスと派生クラスだけがアクセス可能
	void Release(void);

private:   // このクラスだけがアクセス可能
	static int    m_nNumAll;                      // シーンの最大数
	static CScene *m_apTop[MAX_PRIORITY_NUM];     // 先頭のシーンクラスへのポインタ(開始位置がわからなくなるので保存する)
	static CScene *m_apCur[MAX_PRIORITY_NUM];     // 現在の最後尾シーンクラスへのポインタ(新しいシーンクラスへのポインタを追加するために保存)
	CScene        *m_pPrev;                       // 自分の前のシーンクラスへのポインタ
	CScene        *m_pNext;                       // 自分の次のシーンクラスへのポインタ
	bool          m_bDeath;                       // 死亡フラグ
	OBJTYPE       m_ObjType;                      // オブジェクトの種類
	int           m_nPriority;                    // 優先順位の番号
};

#endif