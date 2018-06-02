//=============================================================================
//
// �^�[�Q�b�g�̏��� [terget.cpp]
// Author : ���c����
//=============================================================================
#include "main.h"
#include "terget.h"

//=============================================================================
// �}�N����`

//=============================================================================
// �v���g�^�C�v�錾

//=============================================================================
// �O���[�o���ϐ�
TERGET *g_terget[TERGET_MAX];
LPDIRECT3DTEXTURE9		g_pD3DTextureTerget[TERGET_MAX];		// �e�N�X�`���ւ̃|�C���^

//=============================================================================
// �^�[�Q�b�g���[�h�̏���������
void InitTerget(int oldMode)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//terget�̐擪�A�h���X�擾
	TERGET *terget = GetTerget();

	switch (oldMode)
	{
	case MODE_NULL:
		// ���߂Ă̏�����
		/*��������������Ă����Ȃ��Ƒz�肵�āA�^�[�Q�b�g��ʓ��Ŏg�����̂�S��������*/
		break;

	case MODE_TITLE:
		// �^�C�g���ɂȂ�����������������
		/*�^�C�g����ʂ���^�[�Q�b�g��ʂ֐؂�ւ�������ɁA�^�C�g���ŏ���������Ȃ��������̂�������*/
		/*����*/
		/*�^�C�g����ʂŏ��������ꂽ���̂̓��Z�b�g�������K�v�Ȏ�������*/

		//=========================
		// ������

		//=========================
		// ���Z�b�g

		break;
	case MODE_RESULT:
		// ���U���g�ɂȂ�����������������
		/*���U���g��ʂ���^�[�Q�b�g��ʂ֐؂�ւ�������ɁA���U���g�ŏ���������Ȃ��������̂�������*/
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
	for (int i = 0; i < TERGET_MAX; i++)
	{
		//�^�[�Q�b�g�����ʒu����]������
		(terget + i)->charactor.pos = D3DXVECTOR3(TERGET00_FIRST_POS_X, TERGET00_FIRST_POS_Y, 0.0f);
		//�^�[�Q�b�g�̃T�C�Y�i�[(1/2)
		(terget + i)->charactor.size = D3DXVECTOR2(TERGET00_TEXTURE_SIZE_X, TERGET00_TEXTURE_SIZE_Y);
		//��]������
		D3DXVECTOR2 temp = D3DXVECTOR2(TERGET00_TEXTURE_SIZE_X, TERGET00_TEXTURE_SIZE_Y);
		(terget + i)->charactor.radius = D3DXVec2Length(&temp);											// �^�[�Q�b�g�̔��a��������
		(terget + i)->charactor.baseangle = atan2f(TERGET00_TEXTURE_SIZE_Y, TERGET00_TEXTURE_SIZE_X);		// �^�[�Q�b�g�̊p�x��������
		(terget + i)->charactor.rot.z = (terget + i)->charactor.baseangle;
		//�g�p�t���O�I��
		(terget + i)->charactor.use = true;
		//�L�����ԍ��Z�b�g
		(terget + i)->charactor.idx = IDX_TERGET;
		// �e�N�X�`���̓ǂݍ��� 
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TERGET00_TEXTURE,					// �t�@�C���̖��O
			&g_pD3DTextureTerget[i]);				// �ǂݍ��ރ������̃|�C���^
		//�L��������Z�b�g
		for (int j = 0; j < IDX_MAX; j++)
		{
			(terget + i)->chara_mood[j].attraction = 0;	//0�Ƃ���
		}
	}
	return;
}

//=============================================================================
// �^�[�Q�b�g���[�h�̏���������
void UninitTerget(int mode)
{
	switch (mode)
	{
	case MODE_TITLE:
		// �^�C�g���Ɏg��Ȃ����̂������[�X
		/*�^�[�Q�b�g��ʂ���^�C�g����ʂ֐؂�ւ���Ƃ��ɁA�^�C�g����ʂŎg��Ȃ����̂������[�X����������*/

		break;

	case MODE_RESULT:
		// ���U���g�Ɏg��Ȃ����̂������[�X
		/*�^�[�Q�b�g��ʂ��烊�U���g��ʂ֐؂�ւ���Ƃ��ɁA���U���g��ʂŎg��Ȃ����̂������[�X����������*/

		break;
	}

	//�e���
	for (int i = 0; i < TERGET_MAX; i++)
	{
		if (g_pD3DTextureTerget != NULL)
		{	// �e�N�X�`���̊J��
			g_pD3DTextureTerget[i]->Release();
			g_pD3DTextureTerget[i] = NULL;
		}
	}
}

//=============================================================================
// �^�[�Q�b�g���[�h�̍ŐV����
void UpdateTerget(void)
{



}

//=============================================================================
// �^�[�Q�b�g���[�h�̕`�揈��
void DrawTerget(void)
{

}

//=============================================================================
// �^�[�Q�b�g�擾�֐�
TERGET* GetTerget(void)
{
	return g_terget[0];
}