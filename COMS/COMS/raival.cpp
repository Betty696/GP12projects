//=============================================================================
//
// ライヴァルの処理 [raival.cpp]
// Author : 藤田高輔
//=============================================================================
#include "main.h"
#include "raival.h"

//=============================================================================
// マクロ定義

//=============================================================================
// プロトタイプ宣言

//=============================================================================
// グローバル変数
RAIVAL *g_raival[RAIVAL_MAX];
LPDIRECT3DTEXTURE9		g_pD3DTextureRaival[RAIVAL_MAX];		// テクスチャへのポインタ

//=============================================================================
// ライヴァルモードの初期化処理
void InitRaival(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//raivalの先頭アドレス取得
	RAIVAL *raival = GetRaival();

	/*現在の仕様上、遷移別に初期化をしないため
	スイッチ範囲外で行う*/
	//初期化ループ
	for (int i = 0; i < RAIVAL_MAX; i++)
	{
		//ライヴァル初期位置＆回転初期化
		(raival + i)->charactor.pos = D3DXVECTOR3(RAIVAL00_FIRST_POS_X, RAIVAL00_FIRST_POS_Y, 0.0f);
		//ライヴァルのサイズ格納(1/2)
		(raival + i)->charactor.size = D3DXVECTOR2(RAIVAL00_TEXTURE_SIZE_X, RAIVAL00_TEXTURE_SIZE_Y);
		//回転初期化
		D3DXVECTOR2 temp = D3DXVECTOR2(RAIVAL00_TEXTURE_SIZE_X, RAIVAL00_TEXTURE_SIZE_Y);
		(raival + i)->charactor.radius = D3DXVec2Length(&temp);											// ライヴァルの半径を初期化
		(raival + i)->charactor.baseangle = atan2f(RAIVAL00_TEXTURE_SIZE_Y, RAIVAL00_TEXTURE_SIZE_X);		// ライヴァルの角度を初期化
		(raival + i)->charactor.rot.z = (raival + i)->charactor.baseangle;
		//使用フラグオン
		(raival + i)->charactor.use = true;
		//キャラ感情セット
		for (int j = 0; j < IDX_MAX; j++)
		{
			(raival + i)->chara_mood[j].attraction = 0;	//0とする
		}
	}
	//手動によりキャラ番号とテクスチャ付与
	//キャラ番号セット
	(raival + 0)->charactor.idx = IDX_RAIVAL00;
	(raival + 1)->charactor.idx = IDX_RAIVAL01;
	(raival + 2)->charactor.idx = IDX_RAIVAL02;
	// テクスチャの読み込み 
	D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
		RAIVAL00_TEXTURE,					// ファイルの名前
		&g_pD3DTextureRaival[0]);				// 読み込むメモリのポインタ
	D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
		RAIVAL01_TEXTURE,					// ファイルの名前
		&g_pD3DTextureRaival[1]);				// 読み込むメモリのポインタ
	D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
		RAIVAL02_TEXTURE,					// ファイルの名前
		&g_pD3DTextureRaival[2]);				// 読み込むメモリのポインタ
	return;
}

//=============================================================================
// ライヴァルモードの初期化処理
void UninitRaival(void)
{
	//各解放
	for (int i = 0; i < RAIVAL_MAX; i++)
	{
		if (g_pD3DTextureRaival != NULL)
		{	// テクスチャの開放
			g_pD3DTextureRaival[i]->Release();
			g_pD3DTextureRaival[i] = NULL;
		}
	}
}

//=============================================================================
// ライヴァルモードの最新処理
void UpdateRaival(void)
{



}

//=============================================================================
// ライヴァルモードの描画処理
void DrawRaival(void)
{

}

//=============================================================================
// ライヴァル取得関数
RAIVAL* GetRaival(void)
{
	return g_raival[0];
}