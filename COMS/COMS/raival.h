//=============================================================================
//
// ���C���@���̏��� [raival.h]
// Author : ���c����
//
//=============================================================================
#ifndef _RAIVAL_H_
#define _RAIVAL_H_

#include "main.h"
#include "game.h"


//=============================================================================
// �}�N����`
#define RAIVAL_MAX	(3)											//���C���@���ő吔
#define RAIVAL00_TEXTURE	("COMS/data/texture/chara/�I�ꗜ��.png")	//�e�N�X�`����
#define RAIVAL01_TEXTURE	("COMS/data/texture/chara/��{��.png")	//�e�N�X�`����
#define RAIVAL02_TEXTURE	("COMS/data/texture/chara/���e�ق���.png")	//�e�N�X�`����
#define RAIVAL00_TEXTURE_SIZE_X		(242.0f)	//�e�N�X�`���T�C�YX
#define RAIVAL00_TEXTURE_SIZE_Y		(426.0f)	//�e�N�X�`���T�C�YY
#define RAIVAL00_FIRST_POS_X		(0.0f)		//���C���@�������ʒu
#define RAIVAL00_FIRST_POS_Y		(0.0f)		//���C���@�������ʒu

#define RAIVAL00_TEXTURE_PATTERN_DIVIDE_X	(1)					// �A�j���p�^�[���̃e�N�X�`�����������iX) 
#define RAIVAL00_TEXTURE_PATTERN_DIVIDE_Y	(1)					// �A�j���p�^�[���̃e�N�X�`�����������iY) 
#define RAIVAL00_ANIM_PATTERN_NUM			(TEXTURE_RAIVAL_PATTERN_DIVIDE_X*TEXTURE_RAIVAL_PATTERN_DIVIDE_Y)	// �A�j���[�V�����p�^�[���� 
//=============================================================================
// �\���̐錾
//���C���@���\����
typedef struct
{
	CHARACTOR		charactor;					//�L������{���
	CHARA_MOOD		chara_mood[IDX_MAX];		//�L��������\����(�������܂ߑS����)
}RAIVAL;

//=============================================================================
// �v���g�^�C�v�錾
void InitRaival(void);
void UninitRaival(void);
void UpdateRaival(void);
void DrawRaival(void);
RAIVAL* GetRaival(void);
#endif