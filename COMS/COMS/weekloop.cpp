//=============================================================================
//
// �E�B�[�N���[�v���[�h�̏��� [weekloop.cpp]
// Author : ���c����
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
// �}�N����`

//=============================================================================
// �v���g�^�C�v�錾

//=============================================================================
// �O���[�o���ϐ�
WEEKLOOP g_weekloop;
//=============================================================================
// �E�B�[�N���[�v���[�h�̏���������
void InitWeekloop(void)
{
	//�E�B�[�N���[�v�擾
	WEEKLOOP *weekloop = &g_weekloop;

	weekloop->week_cnt = 0;
	weekloop->status = WEEKLOOP_DAY_START;

	OpenEventFile(weekloop->week_cnt);
	SetScheduleScene();
	//�eInit�Ăяo��
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
// �E�B�[�N���[�v���[�h�̏���������
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
// �E�B�[�N���[�v���[�h�̍ŐV����
void UpdateWeekloop(void)
{
	//�Q�[���擾
	GAME* game = GetGame();
	//�E�B�[�N���[�v�擾
	WEEKLOOP *weekloop = &g_weekloop;

	switch (weekloop->status)
	{
	case WEEKLOOP_DAY_START:
		UpdateRival();
		UpdateSchedule();
		UpdateText();
		UpdateTextBox();
		break;
	case WEEKLOOP_EVENT:
		UpdateRival();
		UpdateEvent();
		UpdateText();
		UpdateTextBox();
		break;
	case WEEKLOOP_RESULT:
		UpdateWeekresult();
		UpdateText();
		UpdateTextBox();
		break;
	}

}

//=============================================================================
// �E�B�[�N���[�v���[�h�̕`�揈��
void DrawWeekloop(void)
{
	//�E�B�[�N���[�v�擾
	WEEKLOOP *weekloop = &g_weekloop;
	//���݂̏T���[�v�𔻕ʂ��`��
	switch (weekloop->status)
	{
	case WEEKLOOP_DAY_START:
		DrawBg();
		DrawRival();
		DrawTextBox();
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
// �E�B�[�N���[�v�Q�b�g�֐�
WEEKLOOP* GetWeeekloop(void)
{
	return &g_weekloop;
}

//=============================================================================
// �E�B�[�N�̍X�V
void AdvanceWeek(void)
{
	WEEKLOOP *weekloop = &g_weekloop;
	//�����ŏT�̃J�E���g�A�b�v���s��
	weekloop->week_cnt++;
	// ���̏T�̃f�[�^�ǂݍ���
	OpenEventFile(weekloop->week_cnt);
	// ����̎n�܂�ɐݒ�
	SetScheduleScene();

}
