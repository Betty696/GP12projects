//=============================================================================
//
// �e�L�X�g�̏��� [text.h]
// Author : ���c����
//
//=============================================================================
#ifndef _TEXT_H_
#define _TEXT_H_

#include "main.h"
#include "game.h"


//=============================================================================
// �}�N����`
#define TEXT_BOX_TEXTURE	("data/texture/ui/speach bubble.png")	// �e�L�X�g�{�b�N�X�̃e�N�X�`���[�p�X
#define TEXT_BOX_POS_X		(SCREEN_WIDTH/2)	// �e�L�X�g�{�b�N�X�̈ʒu
#define TEXT_BOX_POS_Y		(SCREEN_HEIGHT/2)
#define TEXT_BOX_SIZE_X		(1205)				// �e�L�X�g�{�b�N�X�̑傫��(�s�N�Z�����̑傫��)
#define TEXT_BOX_SIZE_Y		(300)

#define TEX_BOX_MAX			(1)					// �}�b�N�X�l	(����Ȃ��Ǝv������)



#define TEXT_MAX	(1)										//�e�L�X�g�ő吔
#define TEXT_KIND	(TEXT_IDX_MAX)							//��ސ�
#define TEXT00_TEXTURE	("data/texture/BG/test01.png")		//�e�N�X�`����
#define TEXT01_TEXTURE	("data/texture/BG/test02.png")		//�e�N�X�`����
#define TEXT02_TEXTURE	("data/texture/BG/test03.png")		//�e�N�X�`����
#define TEXT00_TEXTURE_SIZE_X		(SCREEN_WIDTH/2)		//�e�N�X�`���T�C�YX
#define TEXT00_TEXTURE_SIZE_Y		(SCREEN_HEIGHT/2)		//�e�N�X�`���T�C�YY
#define TEXT00_FIRST_POS_X		(SCREEN_WIDTH/2)			//�e�L�X�g�����ʒu
#define TEXT00_FIRST_POS_Y		(SCREEN_HEIGHT/2)			//�e�L�X�g�����ʒu

#define TEXT00_TEXTURE_PATTERN_DIVIDE_X	(1)					// �A�j���p�^�[���̃e�N�X�`�����������iX) 
#define TEXT00_TEXTURE_PATTERN_DIVIDE_Y	(1)					// �A�j���p�^�[���̃e�N�X�`�����������iY) 
#define TEXT00_ANIM_PATTERN_NUM			(TEXTURE_TEXT_PATTERN_DIVIDE_X*TEXTURE_TEXT_PATTERN_DIVIDE_Y)	// �A�j���[�V�����p�^�[���� 
//=============================================================================
// �\���̐錾
//�e�L�X�g�\����
typedef struct
{
	VERTEX_2D			vertexWk[NUM_VERTEX];		// ���_���i�[���[�N
	D3DXVECTOR3			pos;						// �|���S���\���ppos
	D3DXVECTOR2			size;						// �T�C�Y
	bool				use;						// �g�p�t���O
	int					idx;						// �e�L�X�g�ԍ�
}TEXT;

enum
{
	TEXT_IDX_NULL = -1,
	TEXT_IDX_00,
	TEXT_IDX_01,
	TEXT_IDX_02,
	TEXT_IDX_MAX
};
//=============================================================================
// �v���g�^�C�v�錾
void InitText(void);
void UninitText(void);
void UpdateText(void);
void DrawText(void);
HRESULT MakeVertexText(int no);
void SetVertexText(int no);
void SetTextureText(int no);
TEXT* GetText(void);
#endif