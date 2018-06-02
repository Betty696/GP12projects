//=============================================================================
//
// �e�L�X�g�{�b�N�X�̏��� [text box.h]
// Author : ���ꐶ
//
//=============================================================================
#ifndef _TEXT_BOX_H_
#define _TEXT_BOX_H_

#include "main.h"
#include "basic.h"

//=============================================================================
// �}�N����`

//=============================================================================
// �\���̐錾
//�e�L�X�g�\����
typedef struct
{
	bool	use;
	POLY	poly;
	float	alpha;
	bool	display;
}TEXTBOX;

//=============================================================================
// �v���g�^�C�v�錾
void InitTextBox(void);
void UninitTextBox(void);
void UpdateTextBox(void);
void DrawTextBox(void);
#endif