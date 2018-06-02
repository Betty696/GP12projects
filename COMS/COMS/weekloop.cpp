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

#include "text box.h"

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
	WEEKLOOP* weekloop = GetWeeekloop();

	weekloop->week_cnt = 0;
	weekloop->loopmood = WEEKLOOP_SCHEDULE;
	//各Init呼び出し
	InitBg();
	InitSchedule();
	InitEvent();
	//InitText();
	InitTextBox();

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
	//UninitText();
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
	WEEKLOOP* weekloop = GetWeeekloop();
	//現在の週ループを判別し描画
	switch (weekloop->loopmood)
	{
	case WEEKLOOP_SCHEDULE:
		UpdateSchedule();
		UpdateBg();
		break;
	case WEEKLOOP_EVENT:
		UpdateBg();
		UpdateEvent();
		//UpdateText();
		UpdateTextBox();
		break;
	case WEEKLOOP_RESULT:
		UpdateBg();
		UpdateWeekresult();
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
	WEEKLOOP* weekloop = GetWeeekloop();
	//現在の週ループを判別し描画
	switch (weekloop->loopmood)
	{
	case WEEKLOOP_SCHEDULE:
		DrawBg();
		break;
	case WEEKLOOP_EVENT:
		DrawBg();
		DrawEvent();
		//DrawText();
		DrawTextBox();
		break;
	case WEEKLOOP_RESULT:
		DrawBg();
		DrawWeekresult();
		break;
	}
}

//=============================================================================
// ウィークループゲット関数
WEEKLOOP* GetWeeekloop(void)
{
	return &g_weekloop;
}

//=============================================================================
// ウィークループのモードを返す関数
int SetWeekloopMode(void)
{
	//ウィークループ取得
	WEEKLOOP* weekloop = GetWeeekloop();

	return weekloop->loopmood;
}