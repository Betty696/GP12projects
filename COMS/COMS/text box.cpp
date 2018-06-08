//=============================================================================
//
// テキストボックスの処理 [text box.cpp]
// Author : 川井一生
//=============================================================================
#include "main.h"
#include "text box.h"

#include "input.h"

//=============================================================================
// マクロ定義
#define TEXT_BOX_TEXTURE	("data/texture/ui/speach bubble.png")	// テキストボックスのテクスチャーパス
#define TEXT_BOX_POS_X		(SCREEN_WIDTH/2)	// テキストボックスの位置
#define TEXT_BOX_POS_Y		((SCREEN_HEIGHT/2) + (SCREEN_HEIGHT/4))
#define TEXT_BOX_SIZE_X		(1205)				// テキストボックスの大きさ(ピクセル数の大きさ)
#define TEXT_BOX_SIZE_Y		(300)

#define TEXT_BOX_ALPHA_RATE	(0.02)				// アルファの変換量・変換速度

#define TEX_BOX_MAX			(1)					// マックス値	(いらないと思うけど)

//=============================================================================
// プロトタイプ宣言

//=============================================================================
// グローバル変数
TEXTBOX					gTextBoxWk;
LPDIRECT3DTEXTURE9		gTextBoxTexture;		// テクスチャへのポインタ

//=============================================================================
// テキストモードの初期化処理
void InitTextBox(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	TEXTBOX *texbox = &gTextBoxWk;

	// テクスチャの読み込み 
	D3DXCreateTextureFromFile(pDevice, TEXT_BOX_TEXTURE, &gTextBoxTexture);

	texbox->use = true;

	texbox->display = true;

	texbox->poly.Pos = D3DXVECTOR2(TEXT_BOX_POS_X, TEXT_BOX_POS_Y);
	texbox->poly.Rot = 0.0f;
	texbox->poly.Size = D3DXVECTOR2(TEXT_BOX_SIZE_X, TEXT_BOX_SIZE_Y);

	texbox->alpha = 0.0f;

	texbox->poly.TexId = 0;

	SetBasic2DVtxdata(pDevice, &texbox->poly);

	SetBasic2DPos(&texbox->poly);
}

//=============================================================================
// 終了処理
void UninitTextBox(void)
{
	TEXTBOX *texbox = &gTextBoxWk;

	// 座標データの解放
	SAFE_RELEASE(texbox->poly.VtxBuff);

	// テクスチャの解放
	SAFE_RELEASE(gTextBoxTexture);
}

//=============================================================================
// 最新処理
void UpdateTextBox(void)
{
	TEXTBOX *texbox = &gTextBoxWk;

	if (!texbox->use)	// 処理を飛ばすか
		return;

	// キー入力で表示するか
	if (GetKeyboardTrigger(DIK_0))
	{
		if (texbox->display)
			texbox->display = false;
		else
			texbox->display = true;
	}

	float alphacheck = texbox->alpha;

	// 透明度を下げる処理
	if (texbox->display)
		if (texbox->alpha < 1.0f)
			texbox->alpha += TEXT_BOX_ALPHA_RATE;

	// 透明度を下げる処理
	if (!texbox->display)
		if (texbox->alpha > 0.0f)
			texbox->alpha -= TEXT_BOX_ALPHA_RATE;

	// 色の変換
	if (alphacheck != texbox->alpha)	// データが一緒なら処理しない
		SetBasic2DCol(&texbox->poly, 1.0f, 1.0f, 1.0f, texbox->alpha);

}

//=============================================================================
// 描画処理
void DrawTextBox(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	TEXTBOX *texbox = &gTextBoxWk;
	if (texbox->alpha > 0.0f)
		DrawBasic2DObject(pDevice,&texbox->poly.VtxBuff,&gTextBoxTexture);
}
