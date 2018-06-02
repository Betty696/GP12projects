//=============================================================================
//
// イベントヘッダー [event.h]
// Author : 藤田高輔
//
//=============================================================================

/*******************************************************************************
* 多重インクルードの防止
*******************************************************************************/
#ifndef _EVENT_H_
#define _EVENT_H_

/*******************************************************************************
* マクロ定義
*******************************************************************************/
#define EVENT00_MAX	(3)

/*******************************************************************************
* 構造体定義
*******************************************************************************/
typedef struct
{
	int page;		//現在のページ数格納
	int com;		//行動格納変数
	int com_timing;	//行動タイミング格納変数
}EVENT;

enum
{
	CHOICES_NULL = -1,
	CHOICES_01,
	CHOICES_02,
	CHOICES_03,
	CHOICES_MAX
};

enum
{
	TIMING_NULL = -1,
	TIMING_01,
	TIMING_02,
	TIMING_03,
	TIMING_MAX
};
/******************************************************************************
* プロトタイプ宣言
//****************************************************************************/
void InitEvent(void);
void UninitEvent(void);
void UpdateEvent(void);
void DrawEvent(void);
EVENT* GetEvent(void);
int SetEventPage(void);
/*******************************************************************************
* 多重インクルード防止終了
*******************************************************************************/
#endif
