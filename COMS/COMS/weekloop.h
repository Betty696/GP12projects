//=============================================================================
//
// ウィークループモードの処理 [weekloop.h]
// Author : 藤田高輔
//
//=============================================================================
#ifndef _WEEKLOOP_H_
#define _WEEKLOOP_H_

#include "main.h"


//=============================================================================
// マクロ定義
#define DAYS_TILL_WEEK_LOOP	(5)
//=============================================================================
// 構造体宣言
//週ループ構造体
typedef struct
{
	int status;			//現在週ループのモード格納変数
	int week_cnt;		//週経過数カウント変数
}WEEKLOOP;
//週ループ内モード番号
enum
{
	WEEKLOOP_NULL = -1,
	WEEKLOOP_DAY_START,
	WEEKLOOP_EVENT,
	WEEKLOOP_RESULT,
	WEEKLOOP_MAX
};

//=============================================================================
// プロトタイプ宣言
void InitWeekloop(void);
void UninitWeekloop(void);
void UpdateWeekloop(void);
void DrawWeekloop(void);
WEEKLOOP* GetWeeekloop(void);
void AdvanceWeek(void);
#endif