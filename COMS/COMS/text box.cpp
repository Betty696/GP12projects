//=============================================================================
//
// �e�L�X�g�{�b�N�X�̏��� [text box.cpp]
// Author : ���ꐶ
//=============================================================================
#include "main.h"
#include "text box.h"

#include "input.h"

//=============================================================================
// �}�N����`
#define TEXT_BOX_TEXTURE	("data/texture/ui/speach bubble.png")	// �e�L�X�g�{�b�N�X�̃e�N�X�`���[�p�X
#define TEXT_BOX_POS_X		(SCREEN_WIDTH/2)	// �e�L�X�g�{�b�N�X�̈ʒu
#define TEXT_BOX_POS_Y		((SCREEN_HEIGHT/2) + (SCREEN_HEIGHT/4))
#define TEXT_BOX_SIZE_X		(1205)				// �e�L�X�g�{�b�N�X�̑傫��(�s�N�Z�����̑傫��)
#define TEXT_BOX_SIZE_Y		(300)

#define TEXT_BOX_ALPHA_RATE	(0.02)				// �A���t�@�̕ϊ��ʁE�ϊ����x

#define TEX_BOX_MAX			(1)					// �}�b�N�X�l	(����Ȃ��Ǝv������)

//=============================================================================
// �v���g�^�C�v�錾

//=============================================================================
// �O���[�o���ϐ�
TEXTBOX					gTextBoxWk;
LPDIRECT3DTEXTURE9		gTextBoxTexture;		// �e�N�X�`���ւ̃|�C���^

//=============================================================================
// �e�L�X�g���[�h�̏���������
void InitTextBox(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	TEXTBOX *texbox = &gTextBoxWk;

	// �e�N�X�`���̓ǂݍ��� 
	D3DXCreateTextureFromFile(pDevice, TEXT_BOX_TEXTURE, &gTextBoxTexture);

	texbox->use = true;

	texbox->display = true;

	texbox->poly.Pos = D3DXVECTOR2(TEXT_BOX_POS_X, TEXT_BOX_POS_Y);
	texbox->poly.Rot = 0.0f;
	texbox->poly.Size = D3DXVECTOR2(TEXT_BOX_SIZE_X, TEXT_BOX_SIZE_Y);

	texbox->alpha = 0.0f;

	texbox->poly.TexId = 0;

	SetBasic2DVtxdata(pDevice, &texbox->poly);

	SetBasic2DPos(&texbox->poly);
}

//=============================================================================
// �I������
void UninitTextBox(void)
{
	TEXTBOX *texbox = &gTextBoxWk;

	// ���W�f�[�^�̉��
	SAFE_RELEASE(texbox->poly.VtxBuff);

	// �e�N�X�`���̉��
	SAFE_RELEASE(gTextBoxTexture);
}

//=============================================================================
// �ŐV����
void UpdateTextBox(void)
{
	TEXTBOX *texbox = &gTextBoxWk;

	if (!texbox->use)	// �������΂���
		return;

	// �L�[���͂ŕ\�����邩
	if (GetKeyboardTrigger(DIK_0))
	{
		if (texbox->display)
			texbox->display = false;
		else
			texbox->display = true;
	}

	float alphacheck = texbox->alpha;

	// �����x�������鏈��
	if (texbox->display)
		if (texbox->alpha < 1.0f)
			texbox->alpha += TEXT_BOX_ALPHA_RATE;

	// �����x�������鏈��
	if (!texbox->display)
		if (texbox->alpha > 0.0f)
			texbox->alpha -= TEXT_BOX_ALPHA_RATE;

	// �F�̕ϊ�
	if (alphacheck != texbox->alpha)	// �f�[�^���ꏏ�Ȃ珈�����Ȃ�
		SetBasic2DCol(&texbox->poly, 1.0f, 1.0f, 1.0f, texbox->alpha);

}

//=============================================================================
// �`�揈��
void DrawTextBox(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	TEXTBOX *texbox = &gTextBoxWk;
	if (texbox->alpha > 0.0f)
		DrawBasic2DObject(pDevice,&texbox->poly.VtxBuff,&gTextBoxTexture);
}
