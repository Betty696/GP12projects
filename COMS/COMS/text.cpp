//=============================================================================
//
// テキストの処理 [text.cpp]
// Author : 藤田高輔
// 改変者 : 川井一生
//=============================================================================
#include "main.h"
#include "text.h"
#include "event.h"
#include "weekloop.h"

//=============================================================================
// マクロ定義

//=============================================================================
// プロトタイプ宣言

//=============================================================================
// グローバル変数
TEXT g_text[TEXT_MAX];
LPDIRECT3DTEXTURE9		g_pD3DTextureText[TEXT_KIND];		// テクスチャへのポインタ

//=============================================================================
// テキストモードの初期化処理
void InitText(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//textの先頭アドレス取得
	TEXT *text = GetText();

	//初期化ループ
	for (int i = 0; i < TEXT_MAX; i++)
	{
		//テキスト初期位置＆回転初期化
		(text + i)->pos = D3DXVECTOR3(TEXT00_FIRST_POS_X, TEXT00_FIRST_POS_Y, 0.0f);
		//テキストのサイズ格納(1/2)
		(text + i)->size = D3DXVECTOR2(TEXT00_TEXTURE_SIZE_X, TEXT00_TEXTURE_SIZE_Y);
		//使用フラグオン
		(text + i)->use = false;
		//番号セット
		(text + i)->idx = TEXT_IDX_00;
		//頂点作成
		MakeVertexText(i);
	}
	// テクスチャの読み込み 
	D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
		TEXT00_TEXTURE,					// ファイルの名前
		&g_pD3DTextureText[0]);				// 読み込むメモリのポインタ
											// テクスチャの読み込み 
	D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
		TEXT01_TEXTURE,					// ファイルの名前
		&g_pD3DTextureText[1]);				// 読み込むメモリのポインタ
											// テクスチャの読み込み 
	D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
		TEXT02_TEXTURE,					// ファイルの名前
		&g_pD3DTextureText[2]);				// 読み込むメモリのポインタ
	return;
}

//=============================================================================
// テキストモードの初期化処理
void UninitText(void)
{
	//各解放
	for (int i = 0; i < TEXT_KIND; i++)
	{
		if (g_pD3DTextureText[i] != NULL)
		{	// テクスチャの開放
			g_pD3DTextureText[i]->Release();
			g_pD3DTextureText[i] = NULL;
		}
	}
}

//=============================================================================
// テキストモードの最新処理
void UpdateText(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//ポインタ取得
	TEXT* text = GetText();
	WEEKLOOP* weekloop = GetWeeekloop();
	
	//ウィークループのモードを見てuseを切り替える
	if (SetWeekloopMode() == WEEKLOOP_EVENT)
	{
		text->use = true;
	}
	else
	{
		text->use = false;
	}
}

//=============================================================================
// テキストモードの描画処理
void DrawText(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//ポインタ取得
	TEXT* text = GetText();

	//更新ループ
	for (int i = 0; i < TEXT_MAX; i++)
	{
		if (((text + i) + i)->use == true)
		{
			//デバイス取得
			LPDIRECT3DDEVICE9 pDevice = GetDevice();
			//ページ数に合わせてテキストを変える
			int page = SetEventPage();
			switch (page)
			{
			case TEXT_IDX_00:
				pDevice->SetTexture(0, g_pD3DTextureText[TEXT_IDX_00]);
				break;
			case TEXT_IDX_01:
				pDevice->SetTexture(0, g_pD3DTextureText[TEXT_IDX_01]);
				break;
			case TEXT_IDX_02:
				pDevice->SetTexture(0, g_pD3DTextureText[TEXT_IDX_02]);
				break;
			}
			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_2D);
			//描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, (text + i)->vertexWk, sizeof(VERTEX_2D));
		}
	}
}
//=============================================================================
// 頂点作成関数
HRESULT MakeVertexText(int no)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//textの取得
	TEXT *text = GetText();

	// 頂点座標の設定
	SetVertexText(no);

	// rhwの設定
	(text + no)->vertexWk[0].rhw =
	(text + no)->vertexWk[1].rhw =
	(text + no)->vertexWk[2].rhw =
	(text + no)->vertexWk[3].rhw = 1.0f;
	// 反射光の設定 
	(text + no)->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 180);
	(text + no)->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 180);
	(text + no)->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 180);
	(text + no)->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 180);

	// テクスチャ座標の設定 
	SetTextureText(no);

	return S_OK;
}

//=============================================================================
// 頂点セット関数
void SetVertexText(int no)
{
	//textの取得
	TEXT *text = GetText();

	// 頂点座標の設定
	(text + no)->vertexWk[0].vtx.x = text->pos.x - (text + no)->size.x;
	(text + no)->vertexWk[0].vtx.y = text->pos.y - (text + no)->size.y;
	(text + no)->vertexWk[0].vtx.z = 0.0f;

	(text + no)->vertexWk[1].vtx.x = text->pos.x + (text + no)->size.x;
	(text + no)->vertexWk[1].vtx.y = text->pos.y - (text + no)->size.y;
	(text + no)->vertexWk[1].vtx.z = 0.0f;

	(text + no)->vertexWk[2].vtx.x = text->pos.x - (text + no)->size.x;
	(text + no)->vertexWk[2].vtx.y = text->pos.y + (text + no)->size.y;
	(text + no)->vertexWk[2].vtx.z = 0.0f;

	(text + no)->vertexWk[3].vtx.x = text->pos.x + (text + no)->size.x;
	(text + no)->vertexWk[3].vtx.y = text->pos.y + (text + no)->size.y;
	(text + no)->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// テクスチャ設定関数
void SetTextureText(int no)
{
	//textの取得
	TEXT *text = GetText();

	(text + no)->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	(text + no)->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	(text + no)->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	(text + no)->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);
}
//=============================================================================
// テキスト取得関数
TEXT* GetText(void)
{
	return &g_text[0];
}