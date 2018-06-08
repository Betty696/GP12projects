//=============================================================================
//
// ファイルデータの処理 [file data.cpp]
// Author : 川井
//
//=============================================================================
#include "main.h"
#include "file data.h"

#include "text.h"
//=============================================================================
// マクロ定義
#define EVENT_FILE_PATH		"data/text/event"
#define TXT_FILE_EXTENSION	".txt"
#define CSV_FILE_EXTENSION	".csv"

#define SEARCH_RIVAL		"##Rival"
#define RIVAL01				"##Rival1"
#define RIVAL02				"##Rival2"
#define RIVAL03				"##Rival3"

#define OPTION				"##option"

#define SEARCH_RESULT		"##op"
#define RESULT01			"##op1"
#define RESULT02			"##op2"
#define RESULT03			"##op3"

#define END_OF_SECTION		"##end"


#define END_OF_FILE			"##FileEnd"

//=============================================================================
// グローバル変数
char	FileData[MAX_PATH][MAX_PATH];		// ファイルの中身

//=============================================================================
// ファイルを開く処理
void OpenEventFile(int week)
{
	FILE *fp;
	char filename[MAX_PATH];				// ファイル名
	char file_num[4];						// ファイル番号


	file_num[0] = NULL;
	file_num[1] = NULL;
	file_num[2] = NULL;
	file_num[3] = NULL;

	file_num[2] = week % 10 + '0';
	file_num[1] = week / 10 % 10 + '0';
	file_num[0] = week / 100 % 10 + '0';


	strcpy(filename, EVENT_FILE_PATH);		// パス

	strcat(filename, &file_num[0]);			// 番号

	strcat(filename, TXT_FILE_EXTENSION);	// 拡張子



	fp = fopen(filename, "r");
	if (fp == NULL)
		perror("Error opening file");
	for (int i = 0; i < MAX_PATH; i++)
	{
		fscanf(fp, "%s", &FileData[i][0]);
		if (strcmp(&FileData[i][0], END_OF_FILE) == 0)
			break;
	}
}

//=============================================================================
// ターゲットする女のテキストデータをバッファーに書き込む処理
void LoadTargetText(int Idx)
{
	TEXT *text = GetText();

	char buf[2] = { NULL, NULL };
	char search[10];

	buf[0] = Idx + '0';					// インデックスの数字を文字に変換
	strcpy(search, SEARCH_RIVAL);		// 検索対象を検索
	strcat(search, &buf[0]);

	int row = 0;							// ファイルデータのデータの位置指定
	for (row = 0; row < MAX_PATH; row++)		// コピーする場所を検索
	{
		if (strcmp(&FileData[row][0], &search[0]) == 0)
			break;
	}

	for (int i = 0; i < BUFF_ROW_MAX; i++)	// バッファーをクリア
		memset(&text->textbuf[i][0], 0, sizeof(text->textbuf[i][0]));

	int j = 0;							// バッファーの位置指定
	while (true)						// 終わりまでコピー
	{
		if (strcmp(&FileData[row][0], END_OF_SECTION) == 0)
			break;

		strcpy(&text->textbuf[j][0], &FileData[row][0]); // テキストバッファーにコピー

		row++;
		j++;
	}
	text->rowmax = j;					// 読み取る行のマックスセット

	for (int i = 0; i < TEXT_ROW_MAX; i++)	// 表示カウントをゼロに
		text->drawcnt[i] = 0;
}

//=============================================================================
// オプションのテキストをバッファーに書き込む処理
void LoadOptionText()
{
	TEXT *text = GetText();

	int row = 0;							// ファイルデータのデータの位置指定
	for (row = 0; row < MAX_PATH; row++)		// コピーする場所を検索
	{
		if (strcmp(&FileData[row][0], OPTION) == 0)
		{
			row++;
			break;
		}
	}

	for (int i = 0; i < BUFF_ROW_MAX; i++)	// バッファーをクリア
		memset(&text->textbuf[i][0], 0, sizeof(text->textbuf[i][0]));

	int j = 0;							// バッファーの位置指定
	while (true)						// 終わりまでコピー
	{
		if (strcmp(&FileData[row][0], END_OF_SECTION) == 0)
			break;

		strcpy(&text->textbuf[j][0], &FileData[row][0]);

		row++;
		j++;
	}
	text->rowmax = j;					// 読み取る行のマックスセット

	for (int i = 0; i < TEXT_ROW_MAX; i++)	// 表示カウントをゼロに
		text->drawcnt[i] = 0;
}

//=============================================================================
// リザルトのテキストをバッファーに書き込む処理
void LoadResultText(int Idx)
{
	TEXT *text = GetText();

	char buf[2] = { NULL , NULL};
	char search[10];

	buf[0] = Idx + '0';					// インデックスの数字を文字に変換
	strcpy(search, SEARCH_RESULT);		// 検索対象を検索
	strcat(search, buf);

	int row = 0;							// ファイルデータのデータの位置指定
	for (row = 0; row < MAX_PATH; row++)		// コピーする場所を検索
	{
		if (strcmp(&FileData[row][0], &search[0]) == 0)
			break;
	}

	for (int i = 0; i < BUFF_ROW_MAX; i++)	// バッファーをクリア
		memset(&text->textbuf[i][0], 0, sizeof(text->textbuf[i][0]));

	int j = 0;							// バッファーの位置指定
	while (true)						// 終わりまでコピー
	{
		if (strcmp(&FileData[row][0], END_OF_SECTION) == 0)
			break;

		strcpy(&text->textbuf[j][0], &FileData[row][0]);

		row++;
		j++;
	}
	text->rowmax = j;					// 読み取る行のマックスセット

	for (int i = 0; i < TEXT_ROW_MAX; i++)	// 表示カウントをゼロに
		text->drawcnt[i] = 0;
}
