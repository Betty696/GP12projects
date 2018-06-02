//=============================================================================
//
// プレイヤーの処理 [player.cpp]
// Author : 藤田高輔
//=============================================================================
#include "main.h"
#include "player.h"

//=============================================================================
// マクロ定義

//=============================================================================
// プロトタイプ宣言

//=============================================================================
// グローバル変数
PLAYER g_player[PLAYER_MAX];
LPDIRECT3DTEXTURE9		g_pD3DTexturePlayer[PLAYER_MAX];		// テクスチャへのポインタ

//=============================================================================
// プレイヤーモードの初期化処理
void InitPlayer(int oldMode)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//playerの先頭アドレス取得
	PLAYER *player = GetPlayer();

	switch (oldMode)
	{
	case MODE_NULL:
		// 初めての初期化
		/*何も初期化されていあないと想定して、プレイヤー画面内で使うものを全部初期化*/
		break;

	case MODE_TITLE:
		// タイトルになかった物だけ初期化
		/*タイトル画面からプレイヤー画面へ切り替わった時に、タイトルで初期化されなかったものを初期化*/
		/*注意*/
		/*タイトル画面で初期化されたものはリセット処理が必要な時がある*/

		//=========================
		// 初期化

		//=========================
		// リセット

		break;
	case MODE_RESULT:
		// リザルトになかった物だけ初期化
		/*リザルト画面からプレイヤー画面へ切り替わった時に、リザルトで初期化されなかったものを初期化*/
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
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		//プレイヤー初期位置＆回転初期化
		(player + i)->charactor.pos = D3DXVECTOR3(PLAYER00_FIRST_POS_X, PLAYER00_FIRST_POS_Y, 0.0f);
		//プレイヤーのサイズ格納(1/2)
		(player + i)->charactor.size = D3DXVECTOR2(PLAYER00_TEXTURE_SIZE_X, PLAYER00_TEXTURE_SIZE_Y);
		//回転初期化
		D3DXVECTOR2 temp = D3DXVECTOR2(PLAYER00_TEXTURE_SIZE_X, PLAYER00_TEXTURE_SIZE_Y);
		(player + i)->charactor.radius = D3DXVec2Length(&temp);											// プレイヤーの半径を初期化
		(player + i)->charactor.baseangle = atan2f(PLAYER00_TEXTURE_SIZE_Y, PLAYER00_TEXTURE_SIZE_X);		// プレイヤーの角度を初期化
		(player + i)->charactor.rot.z = (player + i)->charactor.baseangle;
		//使用フラグオン
		(player + i)->charactor.use = true;
		//キャラ番号セット
		(player + i)->charactor.idx = IDX_PLAYER;
		// テクスチャの読み込み 
		D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			PLAYER00_TEXTURE,					// ファイルの名前
			&g_pD3DTexturePlayer[i]);				// 読み込むメモリのポインタ
	}
	return;
}

//=============================================================================
// プレイヤーモードの初期化処理
void UninitPlayer(int mode)
{
	switch (mode)
	{
	case MODE_TITLE:
		// タイトルに使わないものをリリース
		/*プレイヤー画面からタイトル画面へ切り替えるときに、タイトル画面で使わないものをリリース処理をする*/

		break;

	case MODE_RESULT:
		// リザルトに使わないものをリリース
		/*プレイヤー画面からリザルト画面へ切り替えるときに、リザルト画面で使わないものをリリース処理をする*/

		break;
	}
	//各解放
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		if (g_pD3DTexturePlayer != NULL)
		{	// テクスチャの開放
			g_pD3DTexturePlayer[i]->Release();
			g_pD3DTexturePlayer[i] = NULL;
		}
	}
}

//=============================================================================
// プレイヤーモードの最新処理
void UpdatePlayer(void)
{



}

//=============================================================================
// プレイヤーモードの描画処理
void DrawPlayer(void)
{

}

//=============================================================================
// プレイヤー取得関数
PLAYER* GetPlayer(void)
{
	return &g_player[0];
}