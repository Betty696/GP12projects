//=============================================================================
//
// タイトル画面処理 [title.cpp]
// Author : 川井一生
// 改変者 : 塩沼恵
//
//=============================================================================
#include "main.h"
#include "title.h"

#include "title BG.h"

#include "input.h"
#include "fade.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define	TEXTURE_TITLE_LOGO		"data/texture/title/TitleLogo.png"		// ゲームタイトルテクスチャファイル名
#define	TEXTURE_TITLE_ALFA		"data/texture/title/Alfa.png"			// アルファ用テクスチャファイル名
#define	TEXTURE_TITLE_START		"data/texture/title/Start.png"			// スタートテクスチャファイル名
#define	TEXTURE_TITLE_EXIT		"data/texture/title/Exit.png"			// 終了テクスチャファイル名
#define	TEXTURE_TITLE_SHORT		"data/texture/title/Short.png"			// 終了テクスチャファイル名
#define	TEXTURE_TITLE_MIDDLE	"data/texture/title/Middle.png"			// 終了テクスチャファイル名
#define	TEXTURE_TITLE_LONG		"data/texture/title/Long.png"			// 終了テクスチャファイル名
#define	TEXTURE_TITLE_BACK		"data/texture/title/Back.png"			// 終了テクスチャファイル名

#define	TITLE_LOGO_SIZE_X		(SCREEN_WIDTH*2/3)		// ロゴの幅
#define	TITLE_LOGO_SIZE_Y		(SCREEN_HEIGHT)			// ロゴの高さ

#define	TITLE_ALFA_SIZE_X		(SCREEN_WIDTH/2)		// アルファ用画像の幅
#define	TITLE_ALFA_SIZE_Y		(SCREEN_HEIGHT)			// アルファ用画像の高さ

#define	TITLE_START_SIZE_X		(SCREEN_WIDTH / 2)		// スタートテキストの幅
#define	TITLE_START_SIZE_Y		(SCREEN_HEIGHT / 8)		// スタートテキストの高さ

#define	TITLE_EXIT_SIZE_X		(SCREEN_WIDTH / 2)		// 終了テキストの幅
#define	TITLE_EXIT_SIZE_Y		(SCREEN_HEIGHT /8)		// 終了テキストの高さ

#define	TITLE_SHORT_SIZE_X		(SCREEN_WIDTH/2)		// ショートテキストの幅
#define	TITLE_SHORT_SIZE_Y		(SCREEN_HEIGHT /5)		// ショートテキストの高さ

#define	TITLE_MIDDLE_SIZE_X		(SCREEN_WIDTH/2)		// ミドルテキストの幅
#define	TITLE_MIDDLE_SIZE_Y		(SCREEN_HEIGHT /5)		// ミドルテキストの高さ

#define	TITLE_LONG_SIZE_X		(SCREEN_WIDTH/2)		// ロングテキストの幅
#define	TITLE_LONG_SIZE_Y		(SCREEN_HEIGHT /5)		// ロングテキストの高さ

#define	TITLE_BACK_SIZE_X		(SCREEN_WIDTH/2)		// 戻るテキストの幅
#define	TITLE_BACK_SIZE_Y		(SCREEN_HEIGHT /5)		// 戻るテキストの高さ

#define	COMMAND_CHANGE_MAX		(10)					// コマンドテキスト変更上限値
#define	COMMAND_SPEED			(5)						// コマンドテキスト変更スピード
//=============================================================================
// 構造体宣言
//=============================================================================
typedef enum
{
	TITLE_START,
	TITLE_SELECT,
	//	TTITLE_END,
	TITLE_MODE_MAX
}TITLEMODE;

enum
{

	COMMAND_START = 0,
	COMMAND_EXIT,
	COMMAND_MAX,

	COMMAND_SHORT = 0,
	COMMAND_MIDDLE,
	COMMAND_LONG,
	COMMAND_BACK,
	COMMANDMAX

};

//=============================================================================
// プロトタイプ宣言
//=============================================================================
HRESULT MakeVertexTitle(void);
void TitleOperation(void);
void CommandMove(void);
void SetVertexTitle(void);
void TitlePosReset(void);

//=============================================================================
// グローバル変数
//=============================================================================
LPDIRECT3DTEXTURE9		g_pD3DTextureTitleLogo = NULL;		// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTextureAlfa = NULL;			// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTextureStart = NULL;			// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTextureExit = NULL;			// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTextureShort = NULL;			// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTextureMiddle = NULL;			// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTextureLong = NULL;			// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTextureBack = NULL;			// テクスチャへのポインタ

VERTEX_2D				g_vertexWkTitleLogo[NUM_VERTEX];	// 頂点情報格納ワーク
VERTEX_2D				g_vertexWkAlfa[NUM_VERTEX];			// 頂点情報格納ワーク
VERTEX_2D				g_vertexWkStart[NUM_VERTEX];		// 頂点情報格納ワーク
VERTEX_2D				g_vertexWkExit[NUM_VERTEX];			// 頂点情報格納ワーク
VERTEX_2D				g_vertexWkShort[NUM_VERTEX];		// 頂点情報格納ワーク
VERTEX_2D				g_vertexWkMiddle[NUM_VERTEX];		// 頂点情報格納ワーク
VERTEX_2D				g_vertexWkLong[NUM_VERTEX];			// 頂点情報格納ワーク
VERTEX_2D				g_vertexWkBack[NUM_VERTEX];			// 頂点情報格納ワーク

int CommandFlag;		//コマンド選択時のフラグ管理
int MoveCount;			//ムーブ値カウンタ
bool MoveFlag;			//ムーブフラグ
TITLEMODE TitleMode;	//タイトルモード管理

D3DXVECTOR3 pos_Logo;
D3DXVECTOR3 pos_Alfa;
D3DXVECTOR3 pos_Start;
D3DXVECTOR3 pos_Exit;
D3DXVECTOR3 pos_Short;
D3DXVECTOR3 pos_Middle;
D3DXVECTOR3 pos_Long;
D3DXVECTOR3 pos_Back;
//=============================================================================
// 初期化処理
//=============================================================================
void InitTitle(int oldMode)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pos_Logo = D3DXVECTOR3(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2, 0.0f);
	pos_Alfa = D3DXVECTOR3(SCREEN_WIDTH * 3 / 4, SCREEN_HEIGHT / 2, 0.0f);
	pos_Start = D3DXVECTOR3(SCREEN_WIDTH * 3 / 4, SCREEN_HEIGHT * 3 / 10, 0.0f);
	pos_Exit = D3DXVECTOR3(SCREEN_WIDTH * 3 / 4, SCREEN_HEIGHT * 7 / 10, 0.0f);
	pos_Short = D3DXVECTOR3(SCREEN_WIDTH * 3 / 4, SCREEN_HEIGHT / 5, 0.0f);
	pos_Middle = D3DXVECTOR3(SCREEN_WIDTH * 3 / 4, SCREEN_HEIGHT * 2 / 5, 0.0f);
	pos_Long = D3DXVECTOR3(SCREEN_WIDTH * 3 / 4, SCREEN_HEIGHT * 3 / 5, 0.0f);
	pos_Back = D3DXVECTOR3(SCREEN_WIDTH * 3 / 4, SCREEN_HEIGHT * 4 / 5, 0.0f);
	switch (oldMode)
	{
	case MODE_NULL:
		// 初めての初期化
		/*何も初期化されていあないと想定して、タイトル画面内で使うものを全部初期化*/
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
			TEXTURE_TITLE_LOGO,					// ファイルの名前
			&g_pD3DTextureTitleLogo);			// 読み込むメモリー

		D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
			TEXTURE_TITLE_ALFA,					// ファイルの名前
			&g_pD3DTextureAlfa);			// 読み込むメモリー

		D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
			TEXTURE_TITLE_START,				// ファイルの名前
			&g_pD3DTextureStart);				// 読み込むメモリー

		D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
			TEXTURE_TITLE_EXIT,					// ファイルの名前
			&g_pD3DTextureExit);				// 読み込むメモリー

		D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
			TEXTURE_TITLE_SHORT,					// ファイルの名前
			&g_pD3DTextureShort);				// 読み込むメモリー

		D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
			TEXTURE_TITLE_MIDDLE,					// ファイルの名前
			&g_pD3DTextureMiddle);				// 読み込むメモリー

		D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
			TEXTURE_TITLE_LONG,					// ファイルの名前
			&g_pD3DTextureLong);				// 読み込むメモリー

		D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
			TEXTURE_TITLE_BACK,					// ファイルの名前
			&g_pD3DTextureBack);				// 読み込むメモリー

		TitleMode = TITLE_START;		//モードの初期化
		CommandFlag = COMMAND_START;	//コマンドフラグ初期化
		MoveCount = 0;					//移動カウント初期化
		MoveFlag = false;				//移動フラグ初期化
		InitTitleBG();					//背景初期化
		MakeVertexTitle();

		break;
	case MODE_GAME:
		// ゲームになかった物だけ初期化
		/*ゲーム画面からタイトル画面へ切り替わった時に、ゲームで初期化されなかったものを初期化*/
		/*注意*/
		/*ゲーム画面で初期化されたものはリセット処理が必要な時がある*/

		//=========================
		// 初期化
		InitTitleBG();

		//=========================
		// リセット

		break;
	case MODE_RESULT:
		// リザルトになかった物だけ初期化
		/*リザルト画面からタイトル画面へ切り替わった時に、リザルトで初期化されなかったものを初期化*/
		/*注意*/
		/*リザルト画面で初期化されたものはリセット処理が必要な時がある*/

		//=========================
		// 初期化
		InitTitleBG();

		//=========================
		// リセット

		break;
	}

}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTitle(int mode)
{
	switch (mode)
	{
	case MODE_GAME:
		// ゲームに使わないものをリリース
		/*タイトル画面からゲーム画面へ切り替えるときに、ゲーム画面で使わないものをリリース処理をする*/
		if (g_pD3DTextureTitleLogo != NULL)
		{// テクスチャの開放
			g_pD3DTextureTitleLogo->Release();
			g_pD3DTextureTitleLogo = NULL;
		}

		if (g_pD3DTextureAlfa != NULL)
		{// テクスチャの開放
			g_pD3DTextureAlfa->Release();
			g_pD3DTextureAlfa = NULL;
		}

		if (g_pD3DTextureStart != NULL)
		{// テクスチャの開放
			g_pD3DTextureStart->Release();
			g_pD3DTextureStart = NULL;
		}

		if (g_pD3DTextureExit != NULL)
		{// テクスチャの開放
			g_pD3DTextureExit->Release();
			g_pD3DTextureExit = NULL;
		}

		if (g_pD3DTextureShort != NULL)
		{// テクスチャの開放
			g_pD3DTextureShort->Release();
			g_pD3DTextureShort = NULL;
		}

		if (g_pD3DTextureMiddle != NULL)
		{// テクスチャの開放
			g_pD3DTextureMiddle->Release();
			g_pD3DTextureMiddle = NULL;
		}

		if (g_pD3DTextureLong != NULL)
		{// テクスチャの開放
			g_pD3DTextureLong->Release();
			g_pD3DTextureLong = NULL;
		}

		if (g_pD3DTextureBack != NULL)
		{// テクスチャの開放
			g_pD3DTextureBack->Release();
			g_pD3DTextureBack = NULL;
		}

		UninitTitleBG();

		break;
	case MODE_RESULT:
		// リザルトに使わないものをリリース
		/*タイトル画面からリザルト画面へ切り替えるときに、リザルト画面で使わないものをリリース処理をする*/

		UninitTitleBG();

		break;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTitle(void)
{
	/*ここではほかで書いたアップデートを呼ぶ*/
	/*↓↓↓こんな感じ*/
	TitleOperation();
	CommandMove();
	UpdateTitleBG();

	//if (GetKeyboardTrigger(DIK_NUMPAD0))
	//{
	//	SetFade(FADE_OUT, MODE_GAME);
	//}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTitle(void)
{
	/*ここではほかで書いたドローを呼ぶ*/
	/*↓↓↓こんな感じ*/

	DrawTitleBG();
	/*================ タイトルロゴ描画 ================*/
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureTitleLogo);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkTitleLogo, sizeof(VERTEX_2D));

	/*================ アルファ用描画 ================*/
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureAlfa);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkAlfa, sizeof(VERTEX_2D));

	switch (TitleMode)
	{
	case TITLE_START:


		/*================ Start描画 ================*/
		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureStart);

		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkStart, sizeof(VERTEX_2D));

		/*================ EXIT描画 ================*/
		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureExit);

		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkExit, sizeof(VERTEX_2D));

		break;

	case TITLE_SELECT:

		/*================ Short描画 ================*/
		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureShort);

		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkShort, sizeof(VERTEX_2D));

		/*================ Middle描画 ================*/
		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureMiddle);

		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkMiddle, sizeof(VERTEX_2D));

		/*================ Long描画 ================*/
		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureLong);

		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkLong, sizeof(VERTEX_2D));

		/*================ Back描画 ================*/
		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureBack);

		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkBack, sizeof(VERTEX_2D));

		break;

	}
}

//=============================================================================
// タイトル制御関数
//=============================================================================
void TitleOperation(void)
{//各モード時に決定ボタン押下時の処理を決定
	switch (TitleMode)
	{
	case TITLE_START:	//タイトルモードがスタート状態
		if (GetKeyboardTrigger(DIK_RETURN))
		{//決定ボタン押下時
			if (CommandFlag == COMMAND_START)
			{//コマンドフラグがスタートの時
			 //タイトルのモードを1つ進める
				TitleMode = (TITLEMODE)((TitleMode + 1) % TITLE_MODE_MAX);
				//コマンドフラグをコマンドショートに移行させる
				CommandFlag = COMMAND_SHORT;
				//移動フラグをfalseに戻す
				MoveFlag = false;
				//移動カウントをリセットする
				MoveCount = 0;
				//pos値をリセットする
				TitlePosReset();

			}
			else if (CommandFlag == COMMAND_EXIT)
			{//コマンドフラグが終了の時
			 //ゲームの終了処理を行う
				exit(0);
			}
		}
		break;

	case TITLE_SELECT:	//タイトルモードがモード選択状態
		switch (CommandFlag)
		{//各コマンドフラグによって制御を変更する
		case COMMAND_SHORT:		//ショートモード選択中
			if (GetKeyboardTrigger(DIK_RETURN))
			{//決定ボタン押下時
			 //ゲームへ移行。シナリオはショートモード

			 //ゲーム内モードをタイトルからゲームへ移行
			 //SetMode(MODE_GAME, 0);

			 //テスト用
				TitleMode = (TITLEMODE)((TitleMode + 1) % TITLE_MODE_MAX);

			}
			break;

		case COMMAND_MIDDLE:	//ミドルモード選択中
			if (GetKeyboardTrigger(DIK_RETURN))
			{//決定ボタン押下時
			 //ゲームへ移行。シナリオはミドルモード

			 //ゲーム内モードをタイトルからゲームへ移行
			 //SetMode(MODE_GAME, 0);

			 //テスト用
				TitleMode = (TITLEMODE)((TitleMode + 1) % TITLE_MODE_MAX);

			}
			break;

		case COMMAND_LONG:		//ロングモード選択中
			if (GetKeyboardTrigger(DIK_RETURN))
			{//決定ボタン押下時
			 //ゲームへ移行。シナリオはロングモード

			 //ゲーム内モードをタイトルからゲームへ移行
			 //SetMode(MODE_GAME, 0);

			 //テスト用
				TitleMode = (TITLEMODE)((TitleMode + 1) % TITLE_MODE_MAX);
			}
			break;

		case COMMAND_BACK:		//戻るモード選択中
			if (GetKeyboardTrigger(DIK_RETURN))
			{//決定ボタン押下時
			 //タイトルモードを１つ前に戻す
				TitleMode = (TITLEMODE)((TitleMode - 1) % TITLE_MODE_MAX);
				//コマンドフラグをコマンドスタートに移行させる
				CommandFlag = COMMAND_START;
				//移動フラグをfalseに戻す
				MoveFlag = false;
				//移動カウントをリセットする
				MoveCount = 0;
				//pos値をリセットする
				TitlePosReset();

			}
			break;
		}
		break;
	}
}

//=============================================================================
// コマンド移動関数
//=============================================================================
void CommandMove(void)
{
	switch (TitleMode)
	{
	case TITLE_START:	//タイトルモードがスタート状態
						//カウントが溜まるまでの間でテクスチャを動かす
		if (CommandFlag == COMMAND_START)
		{//コマンドフラグ別に処理を行う
			if (MoveCount != COMMAND_CHANGE_MAX)
			{//ムーブカウントが規定時間未到達時
				if (MoveFlag == false)
				{//移動フラグが立ってないとき
				 //元の位置に全てを戻す
				 pos_Exit.x = pos_Start.x;
				 //移動フラグを立てる
					MoveFlag = true;
				}
				//スタートテキストを動かす
				pos_Start.x -= COMMAND_SPEED;
				//移動カウントを加算する
				MoveCount++;
			}
			if (GetKeyboardTrigger(DIK_UP))
			{//上ボタン押下時
			 //コマンドフラグを終了コマンドに移行させる
				CommandFlag = COMMAND_EXIT;
				//移動フラグをfalseに戻す
				MoveFlag = false;
				//移動カウントをリセットする
				MoveCount = 0;
			}
			else if (GetKeyboardTrigger(DIK_DOWN))
			{//下ボタン押下時
			 //コマンドフラグを終了コマンドに移行させる
				CommandFlag = COMMAND_EXIT;
				//移動フラグをfalseに戻す
				MoveFlag = false;
				//移動カウントをリセットする
				MoveCount = 0;
			}
		}
		else if (CommandFlag == COMMAND_EXIT)
		{
			if (MoveCount != COMMAND_CHANGE_MAX)
			{//ムーブカウントが規定時間未到達時
				if (MoveFlag == false)
				{//移動フラグが立ってないとき
				 //元の位置に全てを戻す
				 pos_Start.x = pos_Exit.x;
				 //移動フラグを立てる
					MoveFlag = true;
				}
				//終了テキストを動かす
				pos_Exit.x -= COMMAND_SPEED;
				//移動カウントを加算する
				MoveCount++;
			}
			if (GetKeyboardTrigger(DIK_UP))
			{//上ボタン押下時
			 //コマンドフラグをスタートコマンドに移行させる
				CommandFlag = COMMAND_START;
				//移動フラグをfalseに戻す
				MoveFlag = false;
				//移動カウントをリセットする
				MoveCount = 0;
			}
			else if (GetKeyboardTrigger(DIK_DOWN))
			{//下ボタン押下時
			 //コマンドフラグをスタートコマンドに移行させる
				CommandFlag = COMMAND_START;
				//移動フラグをfalseに戻す
				MoveFlag = false;
				//移動カウントをリセットする
				MoveCount = 0;
			}
		}

		break;

	case TITLE_SELECT:	//タイトルモードがモード選択状態
		switch (CommandFlag)
		{//各コマンドフラグによって制御を変更する
		case COMMAND_SHORT:		//ショートモード選択中
			if (MoveCount != COMMAND_CHANGE_MAX)
			{//ムーブカウントが規定時間未到達時
				if (MoveFlag == false)
				{//移動フラグが立ってないとき
				 //元の位置に全てを戻す
				 pos_Middle.x = pos_Short.x;
				 pos_Back.x = pos_Short.x;
				 //移動フラグを立てる
					MoveFlag = true;
				}
				//スタートテキストを動かす
				pos_Short.x -= COMMAND_SPEED;
				//移動カウントを加算する
				MoveCount++;
			}
			if (GetKeyboardTrigger(DIK_UP))
			{//上ボタン押下時
			 //コマンドフラグを終了コマンドに移行させる
				CommandFlag = COMMAND_BACK;
				//移動フラグをfalseに戻す
				MoveFlag = false;
				//移動カウントをリセットする
				MoveCount = 0;
			}
			else if (GetKeyboardTrigger(DIK_DOWN))
			{//下ボタン押下時
			 //コマンドフラグを終了コマンドに移行させる
				CommandFlag = COMMAND_MIDDLE;
				//移動フラグをfalseに戻す
				MoveFlag = false;
				//移動カウントをリセットする
				MoveCount = 0;
			}

			break;

		case COMMAND_MIDDLE:	//ミドルモード選択中
			if (MoveCount != COMMAND_CHANGE_MAX)
			{//ムーブカウントが規定時間未到達時
				if (MoveFlag == false)
				{//移動フラグが立ってないとき
				 //元の位置に全てを戻す
				 pos_Short.x = pos_Middle.x;
				 pos_Long.x = pos_Middle.x;
				 //移動フラグを立てる
					MoveFlag = true;
				}
				//スタートテキストを動かす
				pos_Middle.x -= COMMAND_SPEED;
				//移動カウントを加算する
				MoveCount++;
			}
			if (GetKeyboardTrigger(DIK_UP))
			{//上ボタン押下時
			 //コマンドフラグを終了コマンドに移行させる
				CommandFlag = COMMAND_SHORT;
				//移動フラグをfalseに戻す
				MoveFlag = false;
				//移動カウントをリセットする
				MoveCount = 0;
			}
			else if (GetKeyboardTrigger(DIK_DOWN))
			{//下ボタン押下時
			 //コマンドフラグを終了コマンドに移行させる
				CommandFlag = COMMAND_LONG;
				//移動フラグをfalseに戻す
				MoveFlag = false;
				//移動カウントをリセットする
				MoveCount = 0;
			}
			break;

		case COMMAND_LONG:		//ロングモード選択中
			if (MoveCount != COMMAND_CHANGE_MAX)
			{//ムーブカウントが規定時間未到達時
				if (MoveFlag == false)
				{//移動フラグが立ってないとき
				 //元の位置に全てを戻す
				 pos_Middle.x = pos_Long.x;
				 pos_Back.x = pos_Long.x;
				 //移動フラグを立てる
					MoveFlag = true;
				}
				//スタートテキストを動かす
				pos_Long.x -= COMMAND_SPEED;
				//移動カウントを加算する
				MoveCount++;
			}
			if (GetKeyboardTrigger(DIK_UP))
			{//上ボタン押下時
			 //コマンドフラグを終了コマンドに移行させる
				CommandFlag = COMMAND_MIDDLE;
				//移動フラグをfalseに戻す
				MoveFlag = false;
				//移動カウントをリセットする
				MoveCount = 0;
			}
			else if (GetKeyboardTrigger(DIK_DOWN))
			{//下ボタン押下時
			 //コマンドフラグを終了コマンドに移行させる
				CommandFlag = COMMAND_BACK;
				//移動フラグをfalseに戻す
				MoveFlag = false;
				//移動カウントをリセットする
				MoveCount = 0;
			}
			break;

		case COMMAND_BACK:		//戻るモード選択中
			if (MoveCount != COMMAND_CHANGE_MAX)
			{//ムーブカウントが規定時間未到達時
				if (MoveFlag == false)
				{//移動フラグが立ってないとき
				 //元の位置に全てを戻す
				 pos_Long.x = pos_Back.x;
				 pos_Short.x = pos_Back.x;
				 //移動フラグを立てる
					MoveFlag = true;
				}
				//スタートテキストを動かす
				pos_Back.x -= COMMAND_SPEED;
				//移動カウントを加算する
				MoveCount++;
			}
			if (GetKeyboardTrigger(DIK_UP))
			{//上ボタン押下時
			 //コマンドフラグを終了コマンドに移行させる
				CommandFlag = COMMAND_LONG;
				//移動フラグをfalseに戻す
				MoveFlag = false;
				//移動カウントをリセットする
				MoveCount = 0;
			}
			else if (GetKeyboardTrigger(DIK_DOWN))
			{//下ボタン押下時
			 //コマンドフラグを終了コマンドに移行させる
				CommandFlag = COMMAND_SHORT;
				//移動フラグをfalseに戻す
				MoveFlag = false;
				//移動カウントをリセットする
				MoveCount = 0;
			}

			break;
		}
	}
}

//=============================================================================
// コマンド取得関数
//=============================================================================
void GetCommandFlag(void)
{
	return (CommandFlag);
}

//=============================================================================
// コマンド移動関数
//=============================================================================
void TitlePosReset(void)
{
	pos_Logo = D3DXVECTOR3(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2, 0.0f);
	pos_Alfa = D3DXVECTOR3(SCREEN_WIDTH * 3 / 4, SCREEN_HEIGHT / 2, 0.0f);
	pos_Start = D3DXVECTOR3(SCREEN_WIDTH * 3 / 4, SCREEN_HEIGHT * 3 / 10, 0.0f);
	pos_Exit = D3DXVECTOR3(SCREEN_WIDTH * 3 / 4, SCREEN_HEIGHT * 7 / 10, 0.0f);
	pos_Short = D3DXVECTOR3(SCREEN_WIDTH * 3 / 4, SCREEN_HEIGHT / 5, 0.0f);
	pos_Middle = D3DXVECTOR3(SCREEN_WIDTH * 3 / 4, SCREEN_HEIGHT * 2 / 5, 0.0f);
	pos_Long = D3DXVECTOR3(SCREEN_WIDTH * 3 / 4, SCREEN_HEIGHT * 3 / 5, 0.0f);
	pos_Back = D3DXVECTOR3(SCREEN_WIDTH * 3 / 4, SCREEN_HEIGHT * 4 / 5, 0.0f);

}