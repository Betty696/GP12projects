//=============================================================================
//
// リザルト画面処理 [result.cpp]
// Author : 川井一生
//
//=============================================================================
#include "main.h"
#include "result.h"
#include "weekloop.h"
#include "input.h"
#include "fade.h"
#include "player.h"

#include "result BG.h"
//=============================================================================
// マクロ定義

//=============================================================================
// プロトタイプ宣言
void ChangeBG(void);

//=============================================================================
// グローバル変数
int ChangeResultBG;
//=============================================================================
// 初期化処理
void InitResult(void)
{
	ChangeResultBG = HAPPYEND;
	InitResultBG();

	return;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitResult(void)
{
	UninitResultBG();

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateResult(void)
{
	PLAYER *player = GetPlayer();
	switch (player->attraction)
	{
	case 0:
	case 1:
		ChangeResultBG = BADEND;
		break;

	case 2:
	case 3:
		ChangeResultBG = NORMALEND;
		break;

	case 4:
		ChangeResultBG = HAPPYEND;
		break;
	}

	//if (GetKeyboardTrigger(DIK_P)|| GetKeyboardPress(DIK_O))
	//{
	//	ChangeBG();
	//}

	//ポインタ取得
	WEEKLOOP* weekloop = GetWeeekloop();

	UpdateResultBG();

	if (GetKeyboardTrigger(DIK_RETURN))
	{
		SetFade(FADE_OUT, MODE_TITLE);
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawResult(void)
{
	/*ここではほかで書いたドローを呼ぶ*/
	/*↓↓↓こんな感じ*/

	DrawResultBG();
}

//=============================================================================
// リザルト画面切り替え処理
//=============================================================================
void ChangeBG(void)
{
	ChangeResultBG = (ChangeResultBG + 1) % END_MAX;
}

//=============================================================================
// リザルト画面切り替え処理
//=============================================================================
int GetChangeResultBG(void)
{
	return(ChangeResultBG);
}