//=============================================================================
//
// ウィークループモードの処理 [weekloop.cpp]
// Author : 藤田高輔
//=============================================================================
#include "main.h"
#include "fade.h"
#include "weekloop.h"
#include "schedule.h"
#include "weekloop.h"
#include "event.h"
#include "text.h"
#include "weekresult.h"
#include "bg.h"
#include "game.h"

#include "rival.h"
#include "text box.h"

#include "file data.h"

//=============================================================================
// マクロ定義

//=============================================================================
// プロトタイプ宣言

//=============================================================================
// グローバル変数
WEEKLOOP g_weekloop;
//=============================================================================
// ウィークループモードの初期化処理
void InitWeekloop(void)
{
	//ウィークループ取得
	WEEKLOOP *weekloop = &g_weekloop;

	weekloop->week_cnt = 0;
	weekloop->status = WEEKLOOP_TARGET;

	OpenEventFile(weekloop->week_cnt);
	//各Init呼び出し
	InitSchedule();
	InitBg();
	InitEvent();
	InitText();
	InitTextBox();


	InitRival();
	InitWeekresult();

	return;
}

//=============================================================================
// ウィークループモードの初期化処理
void UninitWeekloop(void)
{
	UninitBg();
	UninitSchedule();
	UninitEvent();
	UninitRival();
	UninitTextBox();
	UninitWeekresult();
}

//=============================================================================
// ウィークループモードの最新処理
void UpdateWeekloop(void)
{
	//ゲーム取得
	GAME* game = GetGame();
	//ウィークループ取得
	WEEKLOOP *weekloop = &g_weekloop;

	switch (weekloop->status)
	{
	case WEEKLOOP_TARGET:
		UpdateRival();
		UpdateSchedule();
		UpdateBg();
		UpdateText();
		UpdateTextBox();
		break;
	case WEEKLOOP_EVENT:
		UpdateRival();
		UpdateBg();
		UpdateEvent();
		UpdateText();
		UpdateTextBox();
		break;
	case WEEKLOOP_RESULT:
		UpdateBg();
		UpdateWeekresult();
		UpdateText();
		UpdateTextBox();
		break;
	}

	//既定週数が経過していたらリザルトへ
	if (weekloop->week_cnt >= WEEK_NUM_PROTO_MAX)
	{
		SetFade(FADE_OUT, MODE_RESULT);
	}
}

//=============================================================================
// ウィークループモードの描画処理
void DrawWeekloop(void)
{
	//ウィークループ取得
	WEEKLOOP *weekloop = &g_weekloop;
	//現在の週ループを判別し描画
	switch (weekloop->status)
	{
	case WEEKLOOP_TARGET:
		DrawBg();
		DrawRival();
		DrawTextData();
		break;
	case WEEKLOOP_EVENT:
		DrawBg();
		DrawEvent();
		DrawRival();
		DrawTextBox();
		DrawTextData();
		break;
	case WEEKLOOP_RESULT:
		DrawBg();
		DrawWeekresult();
		DrawTextBox();
		DrawTextData();
		break;
	}
}

//=============================================================================
// ウィークループゲット関数
WEEKLOOP* GetWeeekloop(void)
{
	return &g_weekloop;
}
