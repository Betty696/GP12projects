//=============================================================================
//
// �o�b�N�O���E���h�̏��� [bg.cpp]
// Author : ���c����
//=============================================================================
#include "main.h"
#include "bg.h"
#include "weekloop.h"

//=============================================================================
// �}�N����`

//=============================================================================
// �v���g�^�C�v�錾

//=============================================================================
// �O���[�o���ϐ�
BG g_bg[BG_MAX];
LPDIRECT3DTEXTURE9		g_pD3DTextureBg[BG_KIND];		// �e�N�X�`���ւ̃|�C���^

//=============================================================================
// �o�b�N�O���E���h���[�h�̏���������
void InitBg(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//bg�̐擪�A�h���X�擾
	BG *bg = GetBg(0);

	//���������[�v
	for (int i = 0; i < BG_MAX; i++)
	{
		//�o�b�N�O���E���h�����ʒu����]������
		(bg + i)->pos = D3DXVECTOR3(BG00_FIRST_POS_X, BG00_FIRST_POS_Y, 0.0f);
		//�o�b�N�O���E���h�̃T�C�Y�i�[(1/2)
		(bg + i)->size = D3DXVECTOR2(BG00_TEXTURE_SIZE_X, BG00_TEXTURE_SIZE_Y);
		//�g�p�t���O�I��
		(bg + i)->use = true;
		//�ԍ��Z�b�g
		(bg + i)->idx = BG_IDX_SCHEDULE;
		//���_�쐬
		MakeVertexBg(i);
	}
	// �e�N�X�`���̓ǂݍ��� 
	D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
		BG00_TEXTURE,					// �t�@�C���̖��O
		&g_pD3DTextureBg[0]);				// �ǂݍ��ރ������̃|�C���^
	// �e�N�X�`���̓ǂݍ��� 
	D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
		BG01_TEXTURE,					// �t�@�C���̖��O
		&g_pD3DTextureBg[1]);				// �ǂݍ��ރ������̃|�C���^
	// �e�N�X�`���̓ǂݍ��� 
	D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
		BG02_TEXTURE,					// �t�@�C���̖��O
		&g_pD3DTextureBg[2]);				// �ǂݍ��ރ������̃|�C���^
	return;
}

//=============================================================================
// �o�b�N�O���E���h���[�h�̏���������
void UninitBg(void)
{
	//�e���
	for (int i = 0; i < BG_KIND; i++)
	{
		if (g_pD3DTextureBg[i] != NULL)
		{	// �e�N�X�`���̊J��
			g_pD3DTextureBg[i]->Release();
			g_pD3DTextureBg[i] = NULL;
		}
	}
}

//=============================================================================
// �o�b�N�O���E���h���[�h�̍ŐV����
void UpdateBg(void)
{
	//�|�C���^�擾
	BG* bg = GetBg(0);
	WEEKLOOP* weekloop = GetWeeekloop();

	//���݂̃��[�h�𔻕ʂ���ID������
	bg->idx = weekloop->status;
}

//=============================================================================
// �o�b�N�O���E���h���[�h�̕`�揈��
void DrawBg(void)
{
	//�|�C���^�擾
	BG* bg = GetBg(0);
	//�X�V���[�v
	for (int i = 0; i < BG_MAX; i++)
	{
		if ((bg + i)->use == true)
		{
			//�f�o�C�X�擾
			LPDIRECT3DDEVICE9 pDevice = GetDevice();
			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_2D);
			// �e�N�X�`���̐ݒ� (�X�C�b�`�ɂ��؂�ւ���)
			pDevice->SetTexture(0, g_pD3DTextureBg[bg->idx]);
			//�`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, (bg + i)->vertexWk, sizeof(VERTEX_2D));
		}
	}
}
//=============================================================================
// ���_�쐬�֐�
HRESULT MakeVertexBg(int no)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//bg�̎擾
	BG *bg = GetBg(no);

	// ���_���W�̐ݒ�
	SetVertexBg(no);

	// rhw�̐ݒ�
	bg->vertexWk[0].rhw =
	bg->vertexWk[1].rhw =
	bg->vertexWk[2].rhw =
	bg->vertexWk[3].rhw = 1.0f;
	// ���ˌ��̐ݒ� 
	bg->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 180);
	bg->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 180);
	bg->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 180);
	bg->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 180);

	// �e�N�X�`�����W�̐ݒ� 
	SetTextureBg(no);

	return S_OK;
}

//=============================================================================
// ���_�Z�b�g�֐�
void SetVertexBg(int no)
{
	//bg�̎擾
	BG *bg = GetBg(no);

	// ���_���W�̐ݒ�
	bg->vertexWk[0].vtx.x = bg->pos.x - (bg + no)->size.x;
	bg->vertexWk[0].vtx.y = bg->pos.y - (bg + no)->size.y;
	bg->vertexWk[0].vtx.z = 0.0f;

	bg->vertexWk[1].vtx.x = bg->pos.x + (bg + no)->size.x;
	bg->vertexWk[1].vtx.y = bg->pos.y - (bg + no)->size.y;
	bg->vertexWk[1].vtx.z = 0.0f;

	bg->vertexWk[2].vtx.x = bg->pos.x - (bg + no)->size.x;
	bg->vertexWk[2].vtx.y = bg->pos.y + (bg + no)->size.y;
	bg->vertexWk[2].vtx.z = 0.0f;

	bg->vertexWk[3].vtx.x = bg->pos.x + (bg + no)->size.x;
	bg->vertexWk[3].vtx.y = bg->pos.y + (bg + no)->size.y;
	bg->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// �e�N�X�`���ݒ�֐�
void SetTextureBg(int no)
{
	//bg�̎擾
	BG *bg = GetBg(no);

	bg->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	bg->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	bg->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	bg->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);
}
//=============================================================================
// �o�b�N�O���E���h�擾�֐�
BG* GetBg(int no)
{
	return &g_bg[no];
}