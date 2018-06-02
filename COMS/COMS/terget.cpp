//=============================================================================
//
// ターゲットの処理 [terget.cpp]
// Author : 藤田高輔
//=============================================================================
#include "main.h"
#include "terget.h"

//=============================================================================
// マクロ定義

//=============================================================================
// プロトタイプ宣言

//=============================================================================
// グローバル変数
TERGET *g_terget[TERGET_MAX];
LPDIRECT3DTEXTURE9		g_pD3DTextureTerget[TERGET_MAX];		// テクスチャへのポインタ

//=============================================================================
// ターゲットモードの初期化処理
void InitTerget(int oldMode)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//tergetの先頭アドレス取得
	TERGET *terget = GetTerget();

	switch (oldMode)
	{
	case MODE_NULL:
		// 初めての初期化
		/*何も初期化されていあないと想定して、ターゲット画面内で使うものを全部初期化*/
		break;

	case MODE_TITLE:
		// タイトルになかった物だけ初期化
		/*タイトル画面からターゲット画面へ切り替わった時に、タイトルで初期化されなかったものを初期化*/
		/*注意*/
		/*タイトル画面で初期化されたものはリセット処理が必要な時がある*/

		//=========================
		// 初期化

		//=========================
		// リセット

		break;
	case MODE_RESULT:
		// リザルトになかった物だけ初期化
		/*リザルト画面からターゲット画面へ切り替わった時に、リザルトで初期化されなかったものを初期化*/
		/*注意*/
		/*リザルト画面で初期化されたものはリセット処理が必要な時がある*/

		//=========================
		// 初期化

		//=========================
		// リセット

		break;

	}

	/*現在の仕様上、遷移別に初期化をしないため
	スイッチ範囲外で行う*/
	//初期化ループ
	for (int i = 0; i < TERGET_MAX; i++)
	{
		//ターゲット初期位置＆回転初期化
		(terget + i)->charactor.pos = D3DXVECTOR3(TERGET00_FIRST_POS_X, TERGET00_FIRST_POS_Y, 0.0f);
		//ターゲットのサイズ格納(1/2)
		(terget + i)->charactor.size = D3DXVECTOR2(TERGET00_TEXTURE_SIZE_X, TERGET00_TEXTURE_SIZE_Y);
		//回転初期化
		D3DXVECTOR2 temp = D3DXVECTOR2(TERGET00_TEXTURE_SIZE_X, TERGET00_TEXTURE_SIZE_Y);
		(terget + i)->charactor.radius = D3DXVec2Length(&temp);											// ターゲットの半径を初期化
		(terget + i)->charactor.baseangle = atan2f(TERGET00_TEXTURE_SIZE_Y, TERGET00_TEXTURE_SIZE_X);		// ターゲットの角度を初期化
		(terget + i)->charactor.rot.z = (terget + i)->charactor.baseangle;
		//使用フラグオン
		(terget + i)->charactor.use = true;
		//キャラ番号セット
		(terget + i)->charactor.idx = IDX_TERGET;
		// テクスチャの読み込み 
		D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			TERGET00_TEXTURE,					// ファイルの名前
			&g_pD3DTextureTerget[i]);				// 読み込むメモリのポインタ
		//キャラ感情セット
		for (int j = 0; j < IDX_MAX; j++)
		{
			(terget + i)->chara_mood[j].attraction = 0;	//0とする
		}
	}
	return;
}

//=============================================================================
// ターゲットモードの初期化処理
void UninitTerget(int mode)
{
	switch (mode)
	{
	case MODE_TITLE:
		// タイトルに使わないものをリリース
		/*ターゲット画面からタイトル画面へ切り替えるときに、タイトル画面で使わないものをリリース処理をする*/

		break;

	case MODE_RESULT:
		// リザルトに使わないものをリリース
		/*ターゲット画面からリザルト画面へ切り替えるときに、リザルト画面で使わないものをリリース処理をする*/

		break;
	}

	//各解放
	for (int i = 0; i < TERGET_MAX; i++)
	{
		if (g_pD3DTextureTerget != NULL)
		{	// テクスチャの開放
			g_pD3DTextureTerget[i]->Release();
			g_pD3DTextureTerget[i] = NULL;
		}
	}
}

//=============================================================================
// ターゲットモードの最新処理
void UpdateTerget(void)
{



}

//=============================================================================
// ターゲットモードの描画処理
void DrawTerget(void)
{

}

//=============================================================================
// ターゲット取得関数
TERGET* GetTerget(void)
{
	return g_terget[0];
}