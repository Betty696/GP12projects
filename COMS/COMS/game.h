//=============================================================================
//
// ゲームモードの処理 [game.h]
// Author : 川井一生
// 改変者 : 藤田高輔
// 改変内容 : ゲーム内環境の追加など
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"


//=============================================================================
// マクロ定義
#define GRAVITY					(0.25)
#define WEEK_NUM_PROTO_MAX		(5)		//プロトタイプ難易度における最大の週数

//=============================================================================
// 構造体宣言
typedef struct //ゲーム本編を制御するもの（経過週数、難易度）
{
	int difficult;	//選択された難易度
}GAME;

//キャラクター構造体(全キャラクターが共有するもの)
typedef struct
{
	VERTEX_2D			vertexWk[NUM_VERTEX];		// 頂点情報格納ワーク
	D3DXVECTOR3			pos;						// ポリゴン表示用pos
	D3DXVECTOR2			size;						// プレイヤーのサイズ
	D3DXVECTOR3			rot;						// プレイヤーの回転量
	float				radius;						// プレイヤーの半径
	float				baseangle;					// プレイヤーの基準角度
	bool				use;						// 使用フラグ
	int					idx;						// キャラ番号
}CHARACTOR;

//その人がある一人に持つ感情構造体
typedef struct
{
	int					attraction;		//好感度
}CHARA_MOOD;

//難易度のタイプ
enum
{
	DIFFICULT_NULL = -1,	//難易度が選択されてない状態
	DIFFICULT_PROTO,		//プロトタイプ
	DIFFICULT_MAX	//難易度最大数
};

//キャラクター番号列挙
enum
{
	IDX_PLAYER = 0,
	IDX_TERGET,
	IDX_RAIVAL00,
	IDX_RAIVAL01,
	IDX_RAIVAL02,
	IDX_MAX
};

//=============================================================================
// プロトタイプ宣言
void InitGame(int oldMode);
void UninitGame(int oldMode);
void UpdateGame(void);
void DrawGame(void);
void SetDifficult(int difficult);
GAME* GetGame(void);
#endif