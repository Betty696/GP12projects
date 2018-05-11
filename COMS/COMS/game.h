//=============================================================================
//
// �Q�[�����[�h�̏��� [game.h]
// Author : ���ꐶ
// ���ώ� : ���c����
// ���ϓ��e : �Q�[�������̒ǉ��Ȃ�
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"


//=============================================================================
// �}�N����`
#define GRAVITY					(0.25)
#define WEEK_NUM_PROTO_MAX		(5)		//�v���g�^�C�v��Փx�ɂ�����ő�̏T��

//=============================================================================
// �\���̐錾
typedef struct //�Q�[���{�҂𐧌䂷����́i�o�ߏT���A��Փx�j
{
	int difficult;	//�I�����ꂽ��Փx
}GAME;

//�L�����N�^�[�\����(�S�L�����N�^�[�����L�������)
typedef struct
{
	VERTEX_2D			vertexWk[NUM_VERTEX];		// ���_���i�[���[�N
	D3DXVECTOR3			pos;						// �|���S���\���ppos
	D3DXVECTOR2			size;						// �v���C���[�̃T�C�Y
	D3DXVECTOR3			rot;						// �v���C���[�̉�]��
	float				radius;						// �v���C���[�̔��a
	float				baseangle;					// �v���C���[�̊�p�x
	bool				use;						// �g�p�t���O
	int					idx;						// �L�����ԍ�
}CHARACTOR;

//���̐l�������l�Ɏ�����\����
typedef struct
{
	int					attraction;		//�D���x
}CHARA_MOOD;

//��Փx�̃^�C�v
enum
{
	DIFFICULT_NULL = -1,	//��Փx���I������ĂȂ����
	DIFFICULT_PROTO,		//�v���g�^�C�v
	DIFFICULT_MAX	//��Փx�ő吔
};

//�L�����N�^�[�ԍ���
enum
{
	IDX_PLAYER = 0,
	IDX_TERGET,
	IDX_RAIVAL00,
	IDX_RAIVAL01,
	IDX_RAIVAL02,
	IDX_MAX
};

//=============================================================================
// �v���g�^�C�v�錾
void InitGame(int oldMode);
void UninitGame(int oldMode);
void UpdateGame(void);
void DrawGame(void);
void SetDifficult(int difficult);
GAME* GetGame(void);
#endif