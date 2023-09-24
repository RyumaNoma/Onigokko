/*
プロジェクト設定
参考：
[1]https://dxlib.xsrv.jp/use/dxuse_vscom2022.html
[2]https://www.ay3s-room.com/entry/dxlib-lnk2019
*/
#include "DxLib.h"
#include "ModelResource.hpp"
#include "ModelInstance.hpp"
#include "AABB.hpp"
#include "InGameInputPad.hpp"

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

	game::ModelResourcePtr mr(new game::ModelResource("item.txt"));
	std::shared_ptr<game::ModelInstance> mi(new game::ModelInstance(mr));
	mi->setScale(100);
	game::AABB aabb;

	while (CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		SetCameraPositionAndTarget_UpVecY(VGet(400, 400, 0), VGet(100, 0, 1));
		SetCameraNearFar(5, 1050);

		ClearDrawScreen();

		mi->rotate(DX_PI_F / 300);
		aabb.update(mi);
		mi->draw();
		aabb.drawFrame();

		ScreenFlip();
	}

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了
}