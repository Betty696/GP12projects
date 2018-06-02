//=============================================================================
//
// ���C���@���̏��� [raival.cpp]
// Author : ���c����
//=============================================================================
#include "main.h"
#include "raival.h"

//=============================================================================
// �}�N����`

//=============================================================================
// �v���g�^�C�v�錾

//=============================================================================
// �O���[�o���ϐ�
RAIVAL *g_raival[RAIVAL_MAX];
LPDIRECT3DTEXTURE9		g_pD3DTextureRaival[RAIVAL_MAX];		// �e�N�X�`���ւ̃|�C���^

//=============================================================================
// ���C���@�����[�h�̏���������
void InitRaival(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//raival�̐擪�A�h���X�擾
	RAIVAL *raival = GetRaival();

	/*���݂̎d�l��A�J�ڕʂɏ����������Ȃ�����
	�X�C�b�`�͈͊O�ōs��*/
	//���������[�v
	for (int i = 0; i < RAIVAL_MAX; i++)
	{
		//���C���@�������ʒu����]������
		(raival + i)->charactor.pos = D3DXVECTOR3(RAIVAL00_FIRST_POS_X, RAIVAL00_FIRST_POS_Y, 0.0f);
		//���C���@���̃T�C�Y�i�[(1/2)
		(raival + i)->charactor.size = D3DXVECTOR2(RAIVAL00_TEXTURE_SIZE_X, RAIVAL00_TEXTURE_SIZE_Y);
		//��]������
		D3DXVECTOR2 temp = D3DXVECTOR2(RAIVAL00_TEXTURE_SIZE_X, RAIVAL00_TEXTURE_SIZE_Y);
		(raival + i)->charactor.radius = D3DXVec2Length(&temp);											// ���C���@���̔��a��������
		(raival + i)->charactor.baseangle = atan2f(RAIVAL00_TEXTURE_SIZE_Y, RAIVAL00_TEXTURE_SIZE_X);		// ���C���@���̊p�x��������
		(raival + i)->charactor.rot.z = (raival + i)->charactor.baseangle;
		//�g�p�t���O�I��
		(raival + i)->charactor.use = true;
		//�L��������Z�b�g
		for (int j = 0; j < IDX_MAX; j++)
		{
			(raival + i)->chara_mood[j].attraction = 0;	//0�Ƃ���
		}
	}
	//�蓮�ɂ��L�����ԍ��ƃe�N�X�`���t�^
	//�L�����ԍ��Z�b�g
	(raival + 0)->charactor.idx = IDX_RAIVAL00;
	(raival + 1)->charactor.idx = IDX_RAIVAL01;
	(raival + 2)->charactor.idx = IDX_RAIVAL02;
	// �e�N�X�`���̓ǂݍ��� 
	D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
		RAIVAL00_TEXTURE,					// �t�@�C���̖��O
		&g_pD3DTextureRaival[0]);				// �ǂݍ��ރ������̃|�C���^
	D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
		RAIVAL01_TEXTURE,					// �t�@�C���̖��O
		&g_pD3DTextureRaival[1]);				// �ǂݍ��ރ������̃|�C���^
	D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
		RAIVAL02_TEXTURE,					// �t�@�C���̖��O
		&g_pD3DTextureRaival[2]);				// �ǂݍ��ރ������̃|�C���^
	return;
}

//=============================================================================
// ���C���@�����[�h�̏���������
void UninitRaival(void)
{
	//�e���
	for (int i = 0; i < RAIVAL_MAX; i++)
	{
		if (g_pD3DTextureRaival != NULL)
		{	// �e�N�X�`���̊J��
			g_pD3DTextureRaival[i]->Release();
			g_pD3DTextureRaival[i] = NULL;
		}
	}
}

//=============================================================================
// ���C���@�����[�h�̍ŐV����
void UpdateRaival(void)
{



}

//=============================================================================
// ���C���@�����[�h�̕`�揈��
void DrawRaival(void)
{

}

//=============================================================================
// ���C���@���擾�֐�
RAIVAL* GetRaival(void)
{
	return g_raival[0];
}