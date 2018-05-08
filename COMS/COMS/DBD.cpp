#ifdef _DEBUG
//=============================================================================
//
// デバッグデータ表示処理 [DBD.cpp]
// Author : 川井一生
/*
デバッグのデータを管理
*/
//=============================================================================
#include "main.h"



#include "input.h"
#include "DBD.h"




//=============================================================================
// マクロ定義

//=============================================================================
// プロトタイプ宣言
int Line(int no);

void CheckifGamePadPressed(void);
//=============================================================================
// グローバル変数

LPD3DXFONT		g_pD3DXFont = NULL;		// フォントへのポインタ

/*ゲームパッドのチェック用　　１が押されてる　　０が押されていない*/
int				But_A = 0;
int				But_B = 0;
int				But_X = 0;
int				But_Y = 0;
int				But_L1 = 0;
int				But_R1 = 0;
int				But_L2 = 0;
int				But_R2 = 0;
int				But_LS = 0;
int				But_RS = 0;
int				But_SELECT = 0;
int				But_START = 0;

int				Joy_RV = 0;
int				Joy_RH = 0;
int				Joy_LV = 0;
int				Joy_LH = 0;

//=============================================================================
void InitDBD(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 情報表示用フォントを設定
	D3DXCreateFont(pDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &g_pD3DXFont);

}

void DrawDBD(int no)
{
	RECT	rect	= { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	char	str[256];



	CheckifGamePadPressed();



	// FPS
	sprintf(str, "FPS:%d\n", no);
	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	// カメラの位置　camera Eye	
	//rect = { 0,Line(1),SCREEN_WIDTH,SCREEN_HEIGHT };		// bg x and y
	//sprintf(str, "cam x:%f z:%f y:%f\n", camera->Eye.x, camera->Eye.z, camera->Eye.y);
	//g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

}

int Line(int no)
{
	return (no * 15);
}

/*ゲームパッドのボタンチェック*/
void CheckifGamePadPressed(void)
{
	// reset buttons
	But_A = 0;
	But_B = 0;
	But_X = 0;
	But_Y = 0;
	But_L1 = 0;
	But_R1 = 0;
	But_L2 = 0;
	But_R2 = 0;
	But_LS = 0;
	But_RS = 0;
	But_SELECT = 0;
	But_START = 0;
	Joy_RV = 0;
	Joy_RH = 0;
	Joy_LV = 0;
	Joy_LH = 0;

	if (IsButtonPressed(0, BUTTON_A))
		But_A++;

	if (IsButtonPressed(0, BUTTON_B))
		But_B++;

	if (IsButtonPressed(0, BUTTON_X))
		But_X++;

	if (IsButtonPressed(0, BUTTON_Y))
		But_Y++;

	if (IsButtonPressed(0, BUTTON_L1))
		But_L1++;

	if (IsButtonPressed(0, BUTTON_R1))
		But_R1++;

	if (IsButtonPressed(0, BUTTON_L2))
		But_L2++;

	if (IsButtonPressed(0, BUTTON_R2))
		But_R2++;

	if (IsButtonPressed(0, BUTTON_SELECT))
		But_SELECT++;

	if (IsButtonPressed(0, BUTTON_START))
		But_START++;

	if (IsButtonPressed(0, BUTTON_LS))
		But_LS++;

	if (IsButtonPressed(0, BUTTON_RS))
		But_RS++;

	if (IsButtonPressed(0, BUTTON_R_UP))
		Joy_RV++;

	if (IsButtonPressed(0, BUTTON_R_DOWN))
		Joy_RV--;

	if (IsButtonPressed(0, BUTTON_R_RIGHT))
		Joy_RH++;

	if (IsButtonPressed(0, BUTTON_R_LEFT))
		Joy_RH--;

	if (IsButtonPressed(0, BUTTON_UP))
		Joy_LV++;

	if (IsButtonPressed(0, BUTTON_DOWN))
		Joy_LV--;

	if (IsButtonPressed(0, BUTTON_RIGHT))
		Joy_LH++;

	if (IsButtonPressed(0, BUTTON_LEFT))
		Joy_LH--;
}


void UninitDBD(void)
{
	// 情報表示用フォントの開放
	SAFE_RELEASE(g_pD3DXFont);
}
#endif
