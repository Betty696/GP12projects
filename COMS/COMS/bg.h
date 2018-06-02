//=============================================================================
//
// バックグラウンドの処理 [bg.h]
// Author : 藤田高輔
//
//=============================================================================
#ifndef _BG_H_
#define _BG_H_

#include "main.h"
#include "game.h"


//=============================================================================
// マクロ定義
#define BG_MAX	(1)											//バックグラウンド最大数
#define BG_KIND	(BG_IDX_MAX)								//種類数
#define BG00_TEXTURE	("data/texture/BG/スケジュール画面仮画像.png")	//テクスチャ名
#define BG01_TEXTURE	("data/texture/BG/イベント画面仮画像.png")		//テクスチャ名
#define BG02_TEXTURE	("data/texture/BG/リザルト仮画像.png")			//テクスチャ名
#define BG00_TEXTURE_SIZE_X		(SCREEN_WIDTH/2)			//テクスチャサイズX
#define BG00_TEXTURE_SIZE_Y		(SCREEN_HEIGHT/2)			//テクスチャサイズY
#define BG00_FIRST_POS_X		(SCREEN_WIDTH/2)			//バックグラウンド初期位置
#define BG00_FIRST_POS_Y		(SCREEN_HEIGHT/2)			//バックグラウンド初期位置

#define BG00_TEXTURE_PATTERN_DIVIDE_X	(1)					// アニメパターンのテクスチャ内分割数（X) 
#define BG00_TEXTURE_PATTERN_DIVIDE_Y	(1)					// アニメパターンのテクスチャ内分割数（Y) 
#define BG00_ANIM_PATTERN_NUM			(TEXTURE_BG_PATTERN_DIVIDE_X*TEXTURE_BG_PATTERN_DIVIDE_Y)	// アニメーションパターン数 
//=============================================================================
// 構造体宣言
//バックグラウンド構造体
typedef struct
{
	VERTEX_2D			vertexWk[NUM_VERTEX];		// 頂点情報格納ワーク
	D3DXVECTOR3			pos;						// ポリゴン表示用pos
	D3DXVECTOR2			size;						// サイズ
	bool				use;						// 使用フラグ
	int					idx;						// 番号
}BG;

enum
{
	BG_IDX_NULL = -1,
	BG_IDX_SCHEDULE,
	BG_IDX_EVENT,
	BG_IDX_RESULT,
	BG_IDX_MAX
};
//=============================================================================
// プロトタイプ宣言
void InitBg(void);
void UninitBg(void);
void UpdateBg(void);
void DrawBg(void);
HRESULT MakeVertexBg(int no);
void SetVertexBg(int no);
void SetTextureBg(int no);
BG* GetBg(int no);
#endif