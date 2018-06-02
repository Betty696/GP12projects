//=============================================================================
//
// �E�B�[�N���[�v���[�h�̏��� [weekloop.h]
// Author : ���c����
//
//=============================================================================
#ifndef _WEEKLOOP_H_
#define _WEEKLOOP_H_

#include "main.h"


//=============================================================================
// �}�N����`

//=============================================================================
// �\���̐錾
//�T���[�v�\����
typedef struct
{
	int loopmood;		//���ݏT���[�v�̃��[�h�i�[�ϐ�
	int week_cnt;		//�T�o�ߐ��J�E���g�ϐ�
}WEEKLOOP;
//�T���[�v�����[�h�ԍ�
enum
{
	WEEKLOOP_NULL = -1,
	WEEKLOOP_SCHEDULE,
	WEEKLOOP_EVENT,
	WEEKLOOP_RESULT,
	WEEKLOOP_MAX
};

//=============================================================================
// �v���g�^�C�v�錾
void InitWeekloop(void);
void UninitWeekloop(void);
void UpdateWeekloop(void);
void DrawWeekloop(void);
WEEKLOOP* GetWeeekloop(void);
int SetWeekloopMode(void);
#endif