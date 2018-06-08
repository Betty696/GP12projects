//=============================================================================
//
// バックグラウンドの処理 [bg.cpp]
// Author : 藤田高輔
//=============================================================================
#include "main.h"
#include "bg.h"
#include "weekloop.h"

//=============================================================================
// マクロ定義

//=============================================================================
// プロトタイプ宣言

//=============================================================================
// グローバル変数
BG g_bg[BG_MAX];
LPDIRECT3DTEXTURE9		g_pD3DTextureBg[BG_KIND];		// テクスチャへのポインタ

//=============================================================================
// バックグラウンドモードの初期化処理
void InitBg(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//bgの先頭アドレス取得
	BG *bg = GetBg(0);

	//初期化ループ
	for (int i = 0; i < BG_MAX; i++)
	{
		//バックグラウンド初期位置＆回転初期化
		(bg + i)->pos = D3DXVECTOR3(BG00_FIRST_POS_X, BG00_FIRST_POS_Y, 0.0f);
		//バックグラウンドのサイズ格納(1/2)
		(bg + i)->size = D3DXVECTOR2(BG00_TEXTURE_SIZE_X, BG00_TEXTURE_SIZE_Y);
		//使用フラグオン
		(bg + i)->use = true;
		//番号セット
		(bg + i)->idx = BG_IDX_SCHEDULE;
		//頂点作成
		MakeVertexBg(i);
	}
	// テクスチャの読み込み 
	D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
		BG00_TEXTURE,					// ファイルの名前
		&g_pD3DTextureBg[0]);				// 読み込むメモリのポインタ
	// テクスチャの読み込み 
	D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
		BG01_TEXTURE,					// ファイルの名前
		&g_pD3DTextureBg[1]);				// 読み込むメモリのポインタ
	// テクスチャの読み込み 
	D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
		BG02_TEXTURE,					// ファイルの名前
		&g_pD3DTextureBg[2]);				// 読み込むメモリのポインタ
	return;
}

//=============================================================================
// バックグラウンドモードの初期化処理
void UninitBg(void)
{
	//各解放
	for (int i = 0; i < BG_KIND; i++)
	{
		if (g_pD3DTextureBg[i] != NULL)
		{	// テクスチャの開放
			g_pD3DTextureBg[i]->Release();
			g_pD3DTextureBg[i] = NULL;
		}
	}
}

//=============================================================================
// バックグラウンドモードの最新処理
void UpdateBg(void)
{
	//ポインタ取得
	BG* bg = GetBg(0);
	WEEKLOOP* weekloop = GetWeeekloop();

	//現在のモードを判別してIDを入れる
	bg->idx = weekloop->status;
}

//=============================================================================
// バックグラウンドモードの描画処理
void DrawBg(void)
{
	//ポインタ取得
	BG* bg = GetBg(0);
	//更新ループ
	for (int i = 0; i < BG_MAX; i++)
	{
		if ((bg + i)->use == true)
		{
			//デバイス取得
			LPDIRECT3DDEVICE9 pDevice = GetDevice();
			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_2D);
			// テクスチャの設定 (スイッチにより切り替える)
			pDevice->SetTexture(0, g_pD3DTextureBg[bg->idx]);
			//描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, (bg + i)->vertexWk, sizeof(VERTEX_2D));
		}
	}
}
//=============================================================================
// 頂点作成関数
HRESULT MakeVertexBg(int no)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//bgの取得
	BG *bg = GetBg(no);

	// 頂点座標の設定
	SetVertexBg(no);

	// rhwの設定
	bg->vertexWk[0].rhw =
	bg->vertexWk[1].rhw =
	bg->vertexWk[2].rhw =
	bg->vertexWk[3].rhw = 1.0f;
	// 反射光の設定 
	bg->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 180);
	bg->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 180);
	bg->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 180);
	bg->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 180);

	// テクスチャ座標の設定 
	SetTextureBg(no);

	return S_OK;
}

//=============================================================================
// 頂点セット関数
void SetVertexBg(int no)
{
	//bgの取得
	BG *bg = GetBg(no);

	// 頂点座標の設定
	bg->vertexWk[0].vtx.x = bg->pos.x - (bg + no)->size.x;
	bg->vertexWk[0].vtx.y = bg->pos.y - (bg + no)->size.y;
	bg->vertexWk[0].vtx.z = 0.0f;

	bg->vertexWk[1].vtx.x = bg->pos.x + (bg + no)->size.x;
	bg->vertexWk[1].vtx.y = bg->pos.y - (bg + no)->size.y;
	bg->vertexWk[1].vtx.z = 0.0f;

	bg->vertexWk[2].vtx.x = bg->pos.x - (bg + no)->size.x;
	bg->vertexWk[2].vtx.y = bg->pos.y + (bg + no)->size.y;
	bg->vertexWk[2].vtx.z = 0.0f;

	bg->vertexWk[3].vtx.x = bg->pos.x + (bg + no)->size.x;
	bg->vertexWk[3].vtx.y = bg->pos.y + (bg + no)->size.y;
	bg->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// テクスチャ設定関数
void SetTextureBg(int no)
{
	//bgの取得
	BG *bg = GetBg(no);

	bg->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	bg->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	bg->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	bg->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);
}
//=============================================================================
// バックグラウンド取得関数
BG* GetBg(int no)
{
	return &g_bg[no];
}