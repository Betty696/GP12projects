//=============================================================================
//
// ライヴァルの処理 [raival.h]
// Author : 藤田高輔
//
//=============================================================================
#ifndef _RAIVAL_H_
#define _RAIVAL_H_

#include "main.h"
#include "game.h"


//=============================================================================
// マクロ定義
#define RAIVAL_MAX	(3)											//ライヴァル最大数
#define RAIVAL00_TEXTURE	("COMS/data/texture/chara/的場梨沙.png")	//テクスチャ名
#define RAIVAL01_TEXTURE	("COMS/data/texture/chara/二宮飛鳥.png")	//テクスチャ名
#define RAIVAL02_TEXTURE	("COMS/data/texture/chara/白菊ほたる.png")	//テクスチャ名
#define RAIVAL00_TEXTURE_SIZE_X		(242.0f)	//テクスチャサイズX
#define RAIVAL00_TEXTURE_SIZE_Y		(426.0f)	//テクスチャサイズY
#define RAIVAL00_FIRST_POS_X		(0.0f)		//ライヴァル初期位置
#define RAIVAL00_FIRST_POS_Y		(0.0f)		//ライヴァル初期位置

#define RAIVAL00_TEXTURE_PATTERN_DIVIDE_X	(1)					// アニメパターンのテクスチャ内分割数（X) 
#define RAIVAL00_TEXTURE_PATTERN_DIVIDE_Y	(1)					// アニメパターンのテクスチャ内分割数（Y) 
#define RAIVAL00_ANIM_PATTERN_NUM			(TEXTURE_RAIVAL_PATTERN_DIVIDE_X*TEXTURE_RAIVAL_PATTERN_DIVIDE_Y)	// アニメーションパターン数 
//=============================================================================
// 構造体宣言
//ライヴァル構造体
typedef struct
{
	CHARACTOR		charactor;					//キャラ基本情報
	CHARA_MOOD		chara_mood[IDX_MAX];		//キャラ感情構造体(自分を含め全員分)
}RAIVAL;

//=============================================================================
// プロトタイプ宣言
void InitRaival(void);
void UninitRaival(void);
void UpdateRaival(void);
void DrawRaival(void);
RAIVAL* GetRaival(void);
#endif