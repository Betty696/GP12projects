//=============================================================================
//
// �^�C�g����ʏ��� [title.cpp]
// Author : ���ꐶ
//
//=============================================================================
#include "main.h"
#include "title.h"

#include "title BG.h"

#include "input.h"
#include "fade.h"

//=============================================================================
// �}�N����`

//=============================================================================
// �v���g�^�C�v�錾

//=============================================================================
// �O���[�o���ϐ�

//=============================================================================
// ����������
void InitTitle(int oldMode)
{
	switch (oldMode)
	{
	case MODE_NULL:
		// ���߂Ă̏�����
		/*��������������Ă����Ȃ��Ƒz�肵�āA�^�C�g����ʓ��Ŏg�����̂�S��������*/

		InitTitleBG();

		break;
	case MODE_GAME:
		// �Q�[���ɂȂ�����������������
		/*�Q�[����ʂ���^�C�g����ʂ֐؂�ւ�������ɁA�Q�[���ŏ���������Ȃ��������̂�������*/
		/*����*/
		/*�Q�[����ʂŏ��������ꂽ���̂̓��Z�b�g�������K�v�Ȏ�������*/

		//=========================
		// ������
		InitTitleBG();

		//=========================
		// ���Z�b�g

		break;
	case MODE_RESULT:
		// ���U���g�ɂȂ�����������������
		/*���U���g��ʂ���^�C�g����ʂ֐؂�ւ�������ɁA���U���g�ŏ���������Ȃ��������̂�������*/
		/*����*/
		/*���U���g��ʂŏ��������ꂽ���̂̓��Z�b�g�������K�v�Ȏ�������*/

		//=========================
		// ������
		InitTitleBG();

		//=========================
		// ���Z�b�g

		break;
	}

}

//=============================================================================
// �I������
//=============================================================================
void UninitTitle(int mode)
{
	switch (mode)
	{
	case MODE_GAME:
		// �Q�[���Ɏg��Ȃ����̂������[�X
		/*�^�C�g����ʂ���Q�[����ʂ֐؂�ւ���Ƃ��ɁA�Q�[����ʂŎg��Ȃ����̂������[�X����������*/

		UninitTitleBG();

		break;
	case MODE_RESULT:
		// ���U���g�Ɏg��Ȃ����̂������[�X
		/*�^�C�g����ʂ��烊�U���g��ʂ֐؂�ւ���Ƃ��ɁA���U���g��ʂŎg��Ȃ����̂������[�X����������*/

		UninitTitleBG();

		break;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTitle(void)
{
	/*�����ł͂ق��ŏ������A�b�v�f�[�g���Ă�*/
	/*����������Ȋ���*/

	UpdateTitleBG();

	if (GetKeyboardTrigger(DIK_NUMPAD0))
	{
		SetFade(FADE_OUT, MODE_GAME);
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTitle(void)
{
	/*�����ł͂ق��ŏ������h���[���Ă�*/
	/*����������Ȋ���*/

	DrawTitleBG();
}
