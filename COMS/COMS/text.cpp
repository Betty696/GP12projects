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

#include "text box.h"
//=============================================================================
// マクロ定義

//=============================================================================
// プロトタイプ宣言

//=============================================================================
// グローバル変数
TEXT		g_text;
LPD3DXFONT	TextFont = NULL;		// テキスト用のフォント

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
	text->currbufrow = 0;

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
				if (text->drawcnt[i] > text->drawcntmax[i])
				{
					text->drawcnt[i] = TEXT_COLUMN_MAX;
					if (i == TEXT_ROW_MAX -1 && text->currbufrow == text->rowmax)
					{
						switch (weekloop->status)
						{
						case WEEKLOOP_DAY_START:
							SetTextBoxPress(Idx_PRESS_ENTER);
							break;
						case WEEKLOOP_EVENT:
							SetTextBoxPress(Idx_PRESS_123);
							break;
						case WEEKLOOP_RESULT:
							SetTextBoxPress(Idx_PRESS_ENTER);
							break;
						}
					}
				}
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

	int j = 0;
	for (int i = 0; i < TEXT_ROW_MAX; i++)
	{
		if (text->drawcnt[i] != TEXT_COLUMN_MAX)
		{
			text->drawcnt[i] = TEXT_COLUMN_MAX;
			break;
		}
		else
			j++;
	}

	if (j == TEXT_ROW_MAX)
	{
		if (text->currbufrow < text->rowmax)
		{
			for (int i = 0; i < TEXT_ROW_MAX; i++)
			{
				memset(&text->textdis[i][0], 0, strlen(&text->textdis[i][0]));
				text->drawcnt[i] = 0;
			}
			for (int i = 0; i < TEXT_ROW_MAX; i++, text->currbufrow++)
			{
				if (text->currbufrow >= text->rowmax)
					break;
				strcpy(&text->textdis[i][0], &text->textbuf[text->currbufrow][0]);
				text->drawcntmax[i] = strlen(text->textdis[i]);
				text->drawcnt[i] = 0;
			}

		}
	}
}
//=============================================================================
// テキスト取得関数
TEXT *GetText(void)
{
	return &g_text;
}