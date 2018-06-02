//=============================================================================
//
// テキストの処理 [text.h]
// Author : 藤田高輔
//
//=============================================================================
#ifndef _TEXT_H_
#define _TEXT_H_

#include "main.h"
#include "game.h"


//=============================================================================
// マクロ定義
#define TEXT_BOX_TEXTURE	("data/texture/ui/speach bubble.png")	// テキストボックスのテクスチャーパス
#define TEXT_BOX_POS_X		(SCREEN_WIDTH/2)	// テキストボックスの位置
#define TEXT_BOX_POS_Y		(SCREEN_HEIGHT/2)
#define TEXT_BOX_SIZE_X		(1205)				// テキストボックスの大きさ(ピクセル数の大きさ)
#define TEXT_BOX_SIZE_Y		(300)

#define TEX_BOX_MAX			(1)					// マックス値	(いらないと思うけど)



#define TEXT_MAX	(1)										//テキスト最大数
#define TEXT_KIND	(TEXT_IDX_MAX)							//種類数
#define TEXT00_TEXTURE	("data/texture/BG/test01.png")		//テクスチャ名
#define TEXT01_TEXTURE	("data/texture/BG/test02.png")		//テクスチャ名
#define TEXT02_TEXTURE	("data/texture/BG/test03.png")		//テクスチャ名
#define TEXT00_TEXTURE_SIZE_X		(SCREEN_WIDTH/2)		//テクスチャサイズX
#define TEXT00_TEXTURE_SIZE_Y		(SCREEN_HEIGHT/2)		//テクスチャサイズY
#define TEXT00_FIRST_POS_X		(SCREEN_WIDTH/2)			//テキスト初期位置
#define TEXT00_FIRST_POS_Y		(SCREEN_HEIGHT/2)			//テキスト初期位置

#define TEXT00_TEXTURE_PATTERN_DIVIDE_X	(1)					// アニメパターンのテクスチャ内分割数（X) 
#define TEXT00_TEXTURE_PATTERN_DIVIDE_Y	(1)					// アニメパターンのテクスチャ内分割数（Y) 
#define TEXT00_ANIM_PATTERN_NUM			(TEXTURE_TEXT_PATTERN_DIVIDE_X*TEXTURE_TEXT_PATTERN_DIVIDE_Y)	// アニメーションパターン数 
//=============================================================================
// 構造体宣言
//テキスト構造体
typedef struct
{
	VERTEX_2D			vertexWk[NUM_VERTEX];		// 頂点情報格納ワーク
	D3DXVECTOR3			pos;						// ポリゴン表示用pos
	D3DXVECTOR2			size;						// サイズ
	bool				use;						// 使用フラグ
	int					idx;						// テキスト番号
}TEXT;

enum
{
	TEXT_IDX_NULL = -1,
	TEXT_IDX_00,
	TEXT_IDX_01,
	TEXT_IDX_02,
	TEXT_IDX_MAX
};
//=============================================================================
// プロトタイプ宣言
void InitText(void);
void UninitText(void);
void UpdateText(void);
void DrawText(void);
HRESULT MakeVertexText(int no);
void SetVertexText(int no);
void SetTextureText(int no);
TEXT* GetText(void);
#endif