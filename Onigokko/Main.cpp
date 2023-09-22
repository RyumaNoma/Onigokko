/*
プロジェクト設定
参考：
[1]https://dxlib.xsrv.jp/use/dxuse_vscom2022.html
[2]https://www.ay3s-room.com/entry/dxlib-lnk2019
*/
#include "DxLib.h"
#include "ModelResource.hpp"
#include "ModelInstance.hpp"
#include "ModelDatabase.hpp"
#include "Stage.hpp"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	SetBackgroundColor(128, 128, 128);
	SetUseLighting(true);
	SetUseZBuffer3D(true);
	SetWriteZBuffer3D(true);
	SetDrawScreen(DX_SCREEN_BACK);


	game::ModelDatabasePtr mdb(new game::ModelDatabase());
	mdb->load("floor", "ground.txt");
	mdb->load("wall", "wall.txt");
	game::Stage stage(VGet(100, 100, 100),
			"ground.txt",
			"wall.txt");

	while (CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		SetCameraPositionAndTarget_UpVecY(VGet(0, 200, 200), VGet(50, 0, 50));
		SetCameraNearFar(5, 1050);

		ClearDrawScreen();

		stage.draw();

		ScreenFlip();
	}

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}