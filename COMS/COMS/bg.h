//=============================================================================
//
// �o�b�N�O���E���h�̏��� [bg.h]
// Author : ���c����
//
//=============================================================================
#ifndef _BG_H_
#define _BG_H_

#include "main.h"
#include "game.h"


//=============================================================================
// �}�N����`
#define BG_MAX	(1)											//�o�b�N�O���E���h�ő吔
#define BG_KIND	(BG_IDX_MAX)								//��ސ�
#define BG00_TEXTURE	("data/texture/BG/�X�P�W���[����ʉ��摜.png")	//�e�N�X�`����
#define BG01_TEXTURE	("data/texture/BG/�C�x���g��ʉ��摜.png")		//�e�N�X�`����
#define BG02_TEXTURE	("data/texture/BG/���U���g���摜.png")			//�e�N�X�`����
#define BG00_TEXTURE_SIZE_X		(SCREEN_WIDTH/2)			//�e�N�X�`���T�C�YX
#define BG00_TEXTURE_SIZE_Y		(SCREEN_HEIGHT/2)			//�e�N�X�`���T�C�YY
#define BG00_FIRST_POS_X		(SCREEN_WIDTH/2)			//�o�b�N�O���E���h�����ʒu
#define BG00_FIRST_POS_Y		(SCREEN_HEIGHT/2)			//�o�b�N�O���E���h�����ʒu

#define BG00_TEXTURE_PATTERN_DIVIDE_X	(1)					// �A�j���p�^�[���̃e�N�X�`�����������iX) 
#define BG00_TEXTURE_PATTERN_DIVIDE_Y	(1)					// �A�j���p�^�[���̃e�N�X�`�����������iY) 
#define BG00_ANIM_PATTERN_NUM			(TEXTURE_BG_PATTERN_DIVIDE_X*TEXTURE_BG_PATTERN_DIVIDE_Y)	// �A�j���[�V�����p�^�[���� 
//=============================================================================
// �\���̐錾
//�o�b�N�O���E���h�\����
typedef struct
{
	VERTEX_2D			vertexWk[NUM_VERTEX];		// ���_���i�[���[�N
	D3DXVECTOR3			pos;						// �|���S���\���ppos
	D3DXVECTOR2			size;						// �T�C�Y
	bool				use;						// �g�p�t���O
	int					idx;						// �ԍ�
}BG;

enum
{
	BG_IDX_NULL = -1,
	BG_IDX_SCHEDULE,
	BG_IDX_EVENT,
	BG_IDX_RESULT,
	BG_IDX_MAX
};
//=============================================================================
// �v���g�^�C�v�錾
void InitBg(void);
void UninitBg(void);
void UpdateBg(void);
void DrawBg(void);
HRESULT MakeVertexBg(int no);
void SetVertexBg(int no);
void SetTextureBg(int no);
BG* GetBg(int no);
#endif