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

#include "text box.h"

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
	WEEKLOOP* weekloop = GetWeeekloop();

	weekloop->week_cnt = 0;
	weekloop->loopmood = WEEKLOOP_SCHEDULE;
	//�eInit�Ăяo��
	InitBg();
	InitSchedule();
	InitEvent();
	//InitText();
	InitTextBox();

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
	//UninitText();
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
	WEEKLOOP* weekloop = GetWeeekloop();
	//���݂̏T���[�v�𔻕ʂ��`��
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

	//����T�����o�߂��Ă����烊�U���g��
	if (weekloop->week_cnt >= WEEK_NUM_PROTO_MAX)
	{
		SetFade(FADE_OUT, MODE_RESULT);
	}
}

//=============================================================================
// �E�B�[�N���[�v���[�h�̕`�揈��
void DrawWeekloop(void)
{
	//�E�B�[�N���[�v�擾
	WEEKLOOP* weekloop = GetWeeekloop();
	//���݂̏T���[�v�𔻕ʂ��`��
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
// �E�B�[�N���[�v�Q�b�g�֐�
WEEKLOOP* GetWeeekloop(void)
{
	return &g_weekloop;
}

//=============================================================================
// �E�B�[�N���[�v�̃��[�h��Ԃ��֐�
int SetWeekloopMode(void)
{
	//�E�B�[�N���[�v�擾
	WEEKLOOP* weekloop = GetWeeekloop();

	return weekloop->loopmood;
}