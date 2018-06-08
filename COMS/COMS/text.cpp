//=============================================================================
//
// �e�L�X�g�̏��� [text.cpp]
// Author : ���c����
// ���ώ� : ���ꐶ
//=============================================================================
#include "main.h"
#include "text.h"
#include "event.h"
#include "weekloop.h"

//=============================================================================
// �}�N����`

//=============================================================================
// �v���g�^�C�v�錾

//=============================================================================
// �O���[�o���ϐ�
TEXT g_text[TEXT_MAX];
LPDIRECT3DTEXTURE9		g_pD3DTextureText[TEXT_KIND];		// �e�N�X�`���ւ̃|�C���^

//=============================================================================
// �e�L�X�g���[�h�̏���������
void InitText(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//text�̐擪�A�h���X�擾
	TEXT *text = GetText();

	//���������[�v
	for (int i = 0; i < TEXT_MAX; i++)
	{
		//�e�L�X�g�����ʒu����]������
		(text + i)->pos = D3DXVECTOR3(TEXT00_FIRST_POS_X, TEXT00_FIRST_POS_Y, 0.0f);
		//�e�L�X�g�̃T�C�Y�i�[(1/2)
		(text + i)->size = D3DXVECTOR2(TEXT00_TEXTURE_SIZE_X, TEXT00_TEXTURE_SIZE_Y);
		//�g�p�t���O�I��
		(text + i)->use = false;
		//�ԍ��Z�b�g
		(text + i)->idx = TEXT_IDX_00;
		//���_�쐬
		MakeVertexText(i);
	}
	// �e�N�X�`���̓ǂݍ��� 
	D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
		TEXT00_TEXTURE,					// �t�@�C���̖��O
		&g_pD3DTextureText[0]);				// �ǂݍ��ރ������̃|�C���^
											// �e�N�X�`���̓ǂݍ��� 
	D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
		TEXT01_TEXTURE,					// �t�@�C���̖��O
		&g_pD3DTextureText[1]);				// �ǂݍ��ރ������̃|�C���^
											// �e�N�X�`���̓ǂݍ��� 
	D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
		TEXT02_TEXTURE,					// �t�@�C���̖��O
		&g_pD3DTextureText[2]);				// �ǂݍ��ރ������̃|�C���^
	return;
}

//=============================================================================
// �e�L�X�g���[�h�̏���������
void UninitText(void)
{
	//�e���
	for (int i = 0; i < TEXT_KIND; i++)
	{
		if (g_pD3DTextureText[i] != NULL)
		{	// �e�N�X�`���̊J��
			g_pD3DTextureText[i]->Release();
			g_pD3DTextureText[i] = NULL;
		}
	}
}

//=============================================================================
// �e�L�X�g���[�h�̍ŐV����
void UpdateText(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//�|�C���^�擾
	TEXT* text = GetText();
	WEEKLOOP* weekloop = GetWeeekloop();
	
	//�E�B�[�N���[�v�̃��[�h������use��؂�ւ���
	if (SetWeekloopMode() == WEEKLOOP_EVENT)
	{
		text->use = true;
	}
	else
	{
		text->use = false;
	}
}

//=============================================================================
// �e�L�X�g���[�h�̕`�揈��
void DrawText(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//�|�C���^�擾
	TEXT* text = GetText();

	//�X�V���[�v
	for (int i = 0; i < TEXT_MAX; i++)
	{
		if (((text + i) + i)->use == true)
		{
			//�f�o�C�X�擾
			LPDIRECT3DDEVICE9 pDevice = GetDevice();
			//�y�[�W���ɍ��킹�ăe�L�X�g��ς���
			int page = SetEventPage();
			switch (page)
			{
			case TEXT_IDX_00:
				pDevice->SetTexture(0, g_pD3DTextureText[TEXT_IDX_00]);
				break;
			case TEXT_IDX_01:
				pDevice->SetTexture(0, g_pD3DTextureText[TEXT_IDX_01]);
				break;
			case TEXT_IDX_02:
				pDevice->SetTexture(0, g_pD3DTextureText[TEXT_IDX_02]);
				break;
			}
			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_2D);
			//�`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, (text + i)->vertexWk, sizeof(VERTEX_2D));
		}
	}
}
//=============================================================================
// ���_�쐬�֐�
HRESULT MakeVertexText(int no)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//text�̎擾
	TEXT *text = GetText();

	// ���_���W�̐ݒ�
	SetVertexText(no);

	// rhw�̐ݒ�
	(text + no)->vertexWk[0].rhw =
	(text + no)->vertexWk[1].rhw =
	(text + no)->vertexWk[2].rhw =
	(text + no)->vertexWk[3].rhw = 1.0f;
	// ���ˌ��̐ݒ� 
	(text + no)->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 180);
	(text + no)->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 180);
	(text + no)->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 180);
	(text + no)->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 180);

	// �e�N�X�`�����W�̐ݒ� 
	SetTextureText(no);

	return S_OK;
}

//=============================================================================
// ���_�Z�b�g�֐�
void SetVertexText(int no)
{
	//text�̎擾
	TEXT *text = GetText();

	// ���_���W�̐ݒ�
	(text + no)->vertexWk[0].vtx.x = text->pos.x - (text + no)->size.x;
	(text + no)->vertexWk[0].vtx.y = text->pos.y - (text + no)->size.y;
	(text + no)->vertexWk[0].vtx.z = 0.0f;

	(text + no)->vertexWk[1].vtx.x = text->pos.x + (text + no)->size.x;
	(text + no)->vertexWk[1].vtx.y = text->pos.y - (text + no)->size.y;
	(text + no)->vertexWk[1].vtx.z = 0.0f;

	(text + no)->vertexWk[2].vtx.x = text->pos.x - (text + no)->size.x;
	(text + no)->vertexWk[2].vtx.y = text->pos.y + (text + no)->size.y;
	(text + no)->vertexWk[2].vtx.z = 0.0f;

	(text + no)->vertexWk[3].vtx.x = text->pos.x + (text + no)->size.x;
	(text + no)->vertexWk[3].vtx.y = text->pos.y + (text + no)->size.y;
	(text + no)->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// �e�N�X�`���ݒ�֐�
void SetTextureText(int no)
{
	//text�̎擾
	TEXT *text = GetText();

	(text + no)->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	(text + no)->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	(text + no)->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	(text + no)->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);
}
//=============================================================================
// �e�L�X�g�擾�֐�
TEXT* GetText(void)
{
	return &g_text[0];
}