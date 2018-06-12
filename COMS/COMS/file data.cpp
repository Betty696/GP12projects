//=============================================================================
//
// �t�@�C���f�[�^�̏��� [file data.cpp]
// Author : ���
//
//=============================================================================
#include "main.h"
#include "file data.h"

#include "text.h"
//=============================================================================
// �}�N����`
#define EVENT_FILE_PATH		"data/text/event"
#define TXT_FILE_EXTENSION	".txt"
#define CSV_FILE_EXTENSION	".csv"

#define DAY_START			"##Daystart"
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
// �O���[�o���ϐ�
char	FileData[MAX_PATH][MAX_PATH];		// �t�@�C���̒��g


//=============================================================================
// �v���g�^�C�v�錾
void ClearTextData(void);

void CopyFromBuf(void);

//=============================================================================
// �t�@�C�����J������
void OpenEventFile(int week)
{
	FILE *fp;
	char filename[MAX_PATH];				// �t�@�C����
	char file_num[4];						// �t�@�C���ԍ�


	file_num[0] = NULL;
	file_num[1] = NULL;
	file_num[2] = NULL;
	file_num[3] = NULL;

	file_num[2] = week % 10 + '0';
	file_num[1] = week / 10 % 10 + '0';
	file_num[0] = week / 100 % 10 + '0';


	strcpy(filename, EVENT_FILE_PATH);		// �p�X

	strcat(filename, &file_num[0]);			// �ԍ�

	strcat(filename, TXT_FILE_EXTENSION);	// �g���q



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
// �^�[�Q�b�g���鏗�̃e�L�X�g�f�[�^���o�b�t�@�[�ɏ������ޏ���
void LoadDayStartText(void)
{
	TEXT *text = GetText();

	char search[20];

	strcpy(search, DAY_START);		// �����Ώۂ�����

	int row = 0;							// �t�@�C���f�[�^�̃f�[�^�̈ʒu�w��
	for (row = 0; row < MAX_PATH; row++)		// �R�s�[����ꏊ������
	{
		if (strcmp(&FileData[row][0], &search[0]) == 0)
		{
			row++;
			break;
		}
	}

	ClearTextData();		// �e�L�X�g�̍\���̂̒��g���N���A

	int j = 0;							// �o�b�t�@�[�̈ʒu�w��

	while (true)						// �I���܂ŃR�s�[
	{
		if (strcmp(&FileData[row][0], END_OF_SECTION) == 0)
			break;

		strcpy(&text->textbuf[j][0], &FileData[row][0]); // �e�L�X�g�o�b�t�@�[�ɃR�s�[

		row++;
		j++;
	}
	text->rowmax = j;					// �ǂݎ��s�̃}�b�N�X�Z�b�g

	CopyFromBuf();
}

//=============================================================================
// �^�[�Q�b�g���鏗�̃e�L�X�g�f�[�^���o�b�t�@�[�ɏ������ޏ���
void LoadTargetSelectText(int Idx)
{
	TEXT *text = GetText();

	char buf[2] = { NULL, NULL };
	char search[10];

	buf[0] = Idx + '0';					// �C���f�b�N�X�̐����𕶎��ɕϊ�
	strcpy(search, SEARCH_RIVAL);		// �����Ώۂ�����
	strcat(search, &buf[0]);

	int row = 0;							// �t�@�C���f�[�^�̃f�[�^�̈ʒu�w��
	for (row = 0; row < MAX_PATH; row++)		// �R�s�[����ꏊ������
	{
		if (strcmp(&FileData[row][0], &search[0]) == 0)
		{
			row++;
			break;
		}
	}

	for (int i = 0; i < BUFF_ROW_MAX; i++)	// �o�b�t�@�[���N���A
		memset(&text->textbuf[i][0], 0, strlen(&text->textbuf[i][0]));

	for (int i = 0; i < TEXT_ROW_MAX; i++)
		memset(&text->textdis[i][0], 0, strlen(&text->textdis[i][0]));

	int j = 0;							// �o�b�t�@�[�̈ʒu�w��
	while (true)						// �I���܂ŃR�s�[
	{
		if (strcmp(&FileData[row][0], END_OF_SECTION) == 0)
			break;

		strcpy(&text->textbuf[j][0], &FileData[row][0]); // �e�L�X�g�o�b�t�@�[�ɃR�s�[

		row++;
		j++;
	}
	text->rowmax = j;					// �ǂݎ��s�̃}�b�N�X�Z�b�g

	for (int i = 0; i < TEXT_ROW_MAX; i++)	// �\���J�E���g���[����
		text->drawcnt[i] = 0;

	CopyFromBuf();
}

//=============================================================================
// �I�v�V�����̃e�L�X�g���o�b�t�@�[�ɏ������ޏ���
void LoadOptionText()
{
	TEXT *text = GetText();

	int row = 0;							// �t�@�C���f�[�^�̃f�[�^�̈ʒu�w��
	for (row = 0; row < MAX_PATH; row++)		// �R�s�[����ꏊ������
	{
		if (strcmp(&FileData[row][0], OPTION) == 0)
		{
			row++;
			break;
		}
	}

	for (int i = 0; i < BUFF_ROW_MAX; i++)	// �o�b�t�@�[���N���A
		memset(&text->textbuf[i][0], 0, strlen(&text->textbuf[i][0]));

	for (int i = 0; i < TEXT_ROW_MAX; i++)
		memset(&text->textdis[i][0], 0, strlen(&text->textdis[i][0]));

	int j = 0;							// �o�b�t�@�[�̈ʒu�w��
	while (true)						// �I���܂ŃR�s�[
	{
		if (strcmp(&FileData[row][0], END_OF_SECTION) == 0)
			break;

		strcpy(&text->textbuf[j][0], &FileData[row][0]);

		row++;
		j++;
	}
	text->rowmax = j;					// �ǂݎ��s�̃}�b�N�X�Z�b�g

	for (int i = 0; i < TEXT_ROW_MAX; i++)	// �\���J�E���g���[����
		text->drawcnt[i] = 0;


	CopyFromBuf();

}

//=============================================================================
// ���U���g�̃e�L�X�g���o�b�t�@�[�ɏ������ޏ���
void LoadResultText(int Idx)
{
	TEXT *text = GetText();

	char buf[2] = { NULL , NULL};
	char search[10];

	buf[0] = Idx + '0';					// �C���f�b�N�X�̐����𕶎��ɕϊ�
	strcpy(search, SEARCH_RESULT);		// �����Ώۂ�����
	strcat(search, buf);

	int row = 0;							// �t�@�C���f�[�^�̃f�[�^�̈ʒu�w��
	for (row = 0; row < MAX_PATH; row++)	// �R�s�[����ꏊ������
	{
		if (strcmp(&FileData[row][0], &search[0]) == 0)
		{
			row++;
			break;
		}
	}

	for (int i = 0; i < BUFF_ROW_MAX; i++)	// �o�b�t�@�[���N���A
		memset(&text->textbuf[i][0], 0, strlen(&text->textbuf[i][0]));

	for (int i = 0; i < TEXT_ROW_MAX;i++)
		memset(&text->textdis[i][0], 0, strlen(&text->textdis[i][0]));


	int j = 0;							// �o�b�t�@�[�̈ʒu�w��
	while (true)						// �I���܂ŃR�s�[
	{
		if (strcmp(&FileData[row][0], END_OF_SECTION) == 0)
			break;

		strcpy(&text->textbuf[j][0], &FileData[row][0]);

		row++;
		j++;
	}
	text->rowmax = j;					// �ǂݎ��s�̃}�b�N�X�Z�b�g
	for (int i = 0; i < TEXT_ROW_MAX; i++)	// �\���J�E���g���[����
		text->drawcnt[i] = 0;


	CopyFromBuf();
}



void ClearTextData(void)
{
	TEXT *text = GetText();

	for (int i = 0; i < BUFF_ROW_MAX; i++)	// �o�b�t�@�[���N���A
		memset(&text->textbuf[i][0], 0, strlen(&text->textbuf[i][0]));

	for (int i = 0; i < TEXT_ROW_MAX; i++)
		memset(&text->textdis[i][0], 0, strlen(&text->textdis[i][0]));

	for (int i = 0; i < TEXT_ROW_MAX; i++)	// �\���J�E���g���[����
		text->drawcnt[i] = 0;
}

void CopyFromBuf(void)
{
	TEXT *text = GetText();

	text->currbufrow = 0;
	for (int i = 0; i < TEXT_ROW_MAX && i < text->rowmax; i++, text->currbufrow++)
	{
		strcpy(&text->textdis[i][0], &text->textbuf[text->currbufrow][0]);
		text->drawcnt[i] = 0;
		text->drawcntmax[i] = strlen(text->textdis[i]);
	}
}