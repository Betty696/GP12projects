//=============================================================================
//
// �v���C���[�̏��� [player.cpp]
// Author : ���c����
//=============================================================================
#include "main.h"
#include "player.h"

//=============================================================================
// �}�N����`

//=============================================================================
// �v���g�^�C�v�錾

//=============================================================================
// �O���[�o���ϐ�
PLAYER g_player[PLAYER_MAX];
LPDIRECT3DTEXTURE9		g_pD3DTexturePlayer[PLAYER_MAX];		// �e�N�X�`���ւ̃|�C���^

//=============================================================================
// �v���C���[���[�h�̏���������
void InitPlayer(int oldMode)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//player�̐擪�A�h���X�擾
	PLAYER *player = GetPlayer();

	switch (oldMode)
	{
	case MODE_NULL:
		// ���߂Ă̏�����
		/*��������������Ă����Ȃ��Ƒz�肵�āA�v���C���[��ʓ��Ŏg�����̂�S��������*/
		break;

	case MODE_TITLE:
		// �^�C�g���ɂȂ�����������������
		/*�^�C�g����ʂ���v���C���[��ʂ֐؂�ւ�������ɁA�^�C�g���ŏ���������Ȃ��������̂�������*/
		/*����*/
		/*�^�C�g����ʂŏ��������ꂽ���̂̓��Z�b�g�������K�v�Ȏ�������*/

		//=========================
		// ������

		//=========================
		// ���Z�b�g

		break;
	case MODE_RESULT:
		// ���U���g�ɂȂ�����������������
		/*���U���g��ʂ���v���C���[��ʂ֐؂�ւ�������ɁA���U���g�ŏ���������Ȃ��������̂�������*/
		/*����*/
		/*���U���g��ʂŏ��������ꂽ���̂̓��Z�b�g�������K�v�Ȏ�������*/

		//=========================
		// ������

		//=========================
		// ���Z�b�g

		break;

	}

	/*���݂̎d�l��A�J�ڕʂɏ����������Ȃ�����
	�X�C�b�`�͈͊O�ōs��*/
	//���������[�v
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		//�v���C���[�����ʒu����]������
		(player + i)->charactor.pos = D3DXVECTOR3(PLAYER00_FIRST_POS_X, PLAYER00_FIRST_POS_Y, 0.0f);
		//�v���C���[�̃T�C�Y�i�[(1/2)
		(player + i)->charactor.size = D3DXVECTOR2(PLAYER00_TEXTURE_SIZE_X, PLAYER00_TEXTURE_SIZE_Y);
		//��]������
		D3DXVECTOR2 temp = D3DXVECTOR2(PLAYER00_TEXTURE_SIZE_X, PLAYER00_TEXTURE_SIZE_Y);
		(player + i)->charactor.radius = D3DXVec2Length(&temp);											// �v���C���[�̔��a��������
		(player + i)->charactor.baseangle = atan2f(PLAYER00_TEXTURE_SIZE_Y, PLAYER00_TEXTURE_SIZE_X);		// �v���C���[�̊p�x��������
		(player + i)->charactor.rot.z = (player + i)->charactor.baseangle;
		//�g�p�t���O�I��
		(player + i)->charactor.use = true;
		//�L�����ԍ��Z�b�g
		(player + i)->charactor.idx = IDX_PLAYER;
		// �e�N�X�`���̓ǂݍ��� 
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			PLAYER00_TEXTURE,					// �t�@�C���̖��O
			&g_pD3DTexturePlayer[i]);				// �ǂݍ��ރ������̃|�C���^
	}
	return;
}

//=============================================================================
// �v���C���[���[�h�̏���������
void UninitPlayer(int mode)
{
	switch (mode)
	{
	case MODE_TITLE:
		// �^�C�g���Ɏg��Ȃ����̂������[�X
		/*�v���C���[��ʂ���^�C�g����ʂ֐؂�ւ���Ƃ��ɁA�^�C�g����ʂŎg��Ȃ����̂������[�X����������*/

		break;

	case MODE_RESULT:
		// ���U���g�Ɏg��Ȃ����̂������[�X
		/*�v���C���[��ʂ��烊�U���g��ʂ֐؂�ւ���Ƃ��ɁA���U���g��ʂŎg��Ȃ����̂������[�X����������*/

		break;
	}
	//�e���
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		if (g_pD3DTexturePlayer != NULL)
		{	// �e�N�X�`���̊J��
			g_pD3DTexturePlayer[i]->Release();
			g_pD3DTexturePlayer[i] = NULL;
		}
	}
}

//=============================================================================
// �v���C���[���[�h�̍ŐV����
void UpdatePlayer(void)
{



}

//=============================================================================
// �v���C���[���[�h�̕`�揈��
void DrawPlayer(void)
{

}

//=============================================================================
// �v���C���[�擾�֐�
PLAYER* GetPlayer(void)
{
	return &g_player[0];
}