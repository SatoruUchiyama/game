//=============================================================================
//
// メイン処理 [scene.h]
// Author : Satoru Uchiyama
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

//=====================================
//ヘッダー読み込み
//=====================================
#include "main.h"

//=====================================
//	Sceneクラス
//=====================================
class CScene
{
public:
	//列挙型
	typedef enum
	{
		OBJTYPE_NOEN = 0,
		OBJTYPE_BG,
		OBJTYPE_PLAYER,
		OBJTYPE_ENEMY,
		OBJTYPE_BULLET,
		OBJTYPE_ITEM,
		OBJTYPE_EXPLOSION,
		OBJTYPE_MAX
	}OBJTYPE;

	//CScene();
	CScene(int nPriority);
	virtual ~CScene();
	
	//ポリゴンの初期化処理
	virtual HRESULT Init(void) = 0;
	//ポリゴンの終了処理
	virtual void Uninit(void) = 0;
	//ポリゴンの更新処理
	virtual void Update(void) = 0;
	//ポリゴンの描画処理
	virtual void Draw(void) = 0;

	//	全てを開放
	static void ReleaseAll(void);
	//	闇の進化
	static void UpdateAll(void);
	//	光の描画の顕現
	static void DrawAll(void);
	//	オブジェクトの開放
	void Release(void);

	//オブジェクトのタイプの設定
	void SetObjType(OBJTYPE objType);
	//オブジェクトのタイプを取得
	OBJTYPE GetObjType(void);
	//シーンを持ってくる
	static CScene *GetScene(int nIndex, int nPriority);
private:
	//シーンのポインタ
	//static CScene *m_apScene[MAX_MODEL];
	static CScene *m_apScene[MAX_PRIORITY_2][MAX_MODEL];
	int m_nPriority;
	//
	static int m_nNumAll;
	//
	OBJTYPE m_objType;
	//自分のID
	int m_nID;
};
#endif
