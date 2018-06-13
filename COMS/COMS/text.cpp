//=============================================================================
//
// �e�L�X�g�̏��� [text.cpp]
// Author : ���c����
// ���ώ� : ���
//
//=============================================================================
#include "main.h"
#include "text.h"
#include "event.h"
#include "weekloop.h"
#include "input.h"

#include "text box.h"
//=============================================================================
// �}�N����`

//=============================================================================
// �v���g�^�C�v�錾

//=============================================================================
// �O���[�o���ϐ�
TEXT		g_text;
LPD3DXFONT	TextFont = NULL;		// �e�L�X�g�p�̃t�H���g

//=============================================================================
// �e�L�X�g�̏���������
void InitText(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	TEXT *text = &g_text;

	D3DXCreateFont(pDevice, FONT_SIZE, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "�l�r ����", &TextFont);

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
// �e�L�X�g�̃[���N���A����
void ClearText(char *text)
{
	memset(text, 0, sizeof(text));
}

//=============================================================================
// �`��e�L�X�g���[���N���A����
void ClearDrawText(void)
{
	TEXT* text = GetText();
	for (int i = 0; i < TEXT_ROW_MAX; i++)
	{
		text->drawcnt[i] = 0;
	}
}

//=============================================================================
// �e�L�X�g�̍ŐV����
void UpdateText(void)
{
	TEXT* text = GetText();
	WEEKLOOP* weekloop = GetWeeekloop();
	//===========================================
	// �`�悷�镶�����̍ŐV����
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
// �e�L�X�g�`��֐�
void DrawTextData(void) // DrawText�̓��C�u�����[�̃f�t�@�C���ł��邩��DrawTextData
{
	TEXT *text = &g_text;

	for (int i = 0; i < TEXT_ROW_MAX; i++)
	{
		TextFont->DrawText(NULL, &text->textdis[i][0], text->drawcnt[i], &text->rectPos[i], DT_LEFT, D3DCOLOR_ARGB(0xff, 0x00, 0x00, 0x00));
	}
}

//=============================================================================
// �e�L�X�g�X�V����
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
// �e�L�X�g�擾�֐�
TEXT *GetText(void)
{
	return &g_text;
}