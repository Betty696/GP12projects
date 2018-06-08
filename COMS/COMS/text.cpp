//=============================================================================
//
// テキストの処理 [text.cpp]
// Author : 藤田高輔
// 改変者 : 川井
//
//=============================================================================
#include "main.h"
#include "text.h"
#include "event.h"
#include "weekloop.h"
#include "input.h"

//=============================================================================
// マクロ定義

//=============================================================================
// プロトタイプ宣言

//=============================================================================
// グローバル変数
TEXT		g_text;
LPD3DXFONT	TextFont = NULL;		// テキスト用のフォント

bool	LoadNewText = false;		// 新しく分を読み込むか

//=============================================================================
// テキストの初期化処理
void InitText(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	TEXT *text = &g_text;

	D3DXCreateFont(pDevice, FONT_SIZE, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "ＭＳ 明朝", &TextFont);

	ClearText(&text->textdis[0][0]);
	ClearText(&text->textbuf[0][0]);
	text->order = 0;
	text->bufcnt = 0;

	for (int i = 0; i < TEXT_ROW_MAX; i++)
	{
		text->rectPos[i] = { TEXT_POS_X, TEXT_POS_Y + (i * TEXT_ROW_HEIGHT), SCREEN_WIDTH, SCREEN_HEIGHT };
		text->drawcnt[i] = 0;
	}
}

//=============================================================================
// テキストのゼロクリア処理
void ClearText(char *text)
{
	memset(text, 0, sizeof(text));
}

//=============================================================================
// 描画テキストをゼロクリア処理
void ClearDrawText(void)
{
	TEXT* text = GetText();
	for (int i = 0; i < TEXT_ROW_MAX; i++)
	{
		text->drawcnt[i] = 0;
	}
}

//=============================================================================
// テキストの最新処理
void UpdateText(void)
{
	TEXT* text = GetText();
	WEEKLOOP* weekloop = GetWeeekloop();
	//===========================================
	// 描画する文字数の最新処理
	if (text->wait > TEST_SPEED)
		text->wait = 0;

	text->wait++;

	if (text->wait >= TEST_SPEED)
	{
		for (int i = 0; i < TEXT_ROW_MAX; i++)
		{
			if (text->drawcnt[i - 1] == TEXT_COLUMN_MAX && text->drawcnt[i] != TEXT_COLUMN_MAX 
				|| i == 0 && text->drawcnt[i] < TEXT_COLUMN_MAX)
			{
				text->drawcnt[i]++;
			}
			else if (text->drawcnt[(TEXT_ROW_MAX - 1)] == TEXT_COLUMN_MAX && i + 1 == TEXT_ROW_MAX)
			{
				LoadNewText = true;
			}

		}
	}
}

//=============================================================================
// テキスト描画関数
void DrawTextData(void) // DrawTextはライブラリーのデファインであるからDrawTextData
{
	TEXT *text = &g_text;

	for (int i = 0; i < TEXT_ROW_MAX; i++)
	{
		TextFont->DrawText(NULL, &text->textdis[i][0], text->drawcnt[i], &text->rectPos[i], DT_LEFT, D3DCOLOR_ARGB(0xff, 0x00, 0x00, 0x00));
	}
}

//=============================================================================
// テキスト更新処理
void AdvanceText(void)
{
	TEXT *text = &g_text;

	for (int i = 0; i < TEXT_ROW_MAX; i++)
	{
		if (text->drawcnt[i] != TEXT_COLUMN_MAX)
		{
			text->drawcnt[i] = TEXT_COLUMN_MAX;
			break;
		}
	}

	if (LoadNewText)
	{
		for (int i = 0; i < TEXT_ROW_MAX && text->bufcnt < text->rowmax; i++, text->bufcnt++)
		{
			strcpy(&text->textdis[i][0], &text->textbuf[text->bufcnt][0]);
		}

		for (int i = 0; i < TEXT_ROW_MAX; i++)
		{
			text->drawcnt[i] = 0;
		}
		LoadNewText = false;
	}
}
//=============================================================================
// テキスト取得関数
TEXT *GetText(void)
{
	return &g_text;
}