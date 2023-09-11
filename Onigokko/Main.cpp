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

	SetCameraPositionAndTarget_UpVecY(VGet(0, 0, 1000), VGet(0, 0, 0));
	SetCameraNearFar(5, 1050);
	SetBackgroundColor(128, 128, 128);

	game::ModelResourcePtr mr(new game::ModelResource("square.txt"));
	game::ModelInstance mi(mr);
	while (WaitKey() != KEY_INPUT_ESCAPE) {
		ClearDrawScreen();
		mi.draw();
		mi.rotate(DX_PI_F / 8.0f);
	}

	WaitKey();				// キー入力待ち

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}