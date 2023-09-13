/*
プロジェクト設定
参考：
[1]https://dxlib.xsrv.jp/use/dxuse_vscom2022.html
[2]https://www.ay3s-room.com/entry/dxlib-lnk2019
*/
#include "DxLib.h"
#include "ModelResource.hpp"
#include "ModelInstance.hpp"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	SetBackgroundColor(128, 128, 128);
	SetUseLighting(false);
	SetUseZBuffer3D(true);
	SetWriteZBuffer3D(true);
	SetDrawScreen(DX_SCREEN_BACK);

	game::ModelResourcePtr mr(new game::ModelResource("cube.txt"));
	game::ModelInstance mi(mr);
	mi.setScale(100);
	mi.setAnchor(VGet(0.5, 0.5, 0.5));
	mi.move(VGet(-0.5, -0.5, -0.5));
	while (CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		SetCameraPositionAndTarget_UpVecY(VGet(0, 400, 400), VGet(0, 0, 0));
		SetCameraNearFar(5, 1050);

		ClearDrawScreen();

		mi.draw();
		mi.rotate(DX_PI_F / 100.0f);
		ScreenFlip();
	}

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}