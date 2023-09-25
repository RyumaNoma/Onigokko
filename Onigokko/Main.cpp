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
#include "CollisionDetection.hpp"

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
	game::ModelResourcePtr mr2(new game::ModelResource("person.txt"));
	std::shared_ptr<game::ModelInstance> mi(new game::ModelInstance(mr));
	std::shared_ptr<game::ModelInstance> mi2(new game::ModelInstance(mr2));
	mi->setScale(100);
	mi->move(VGet(0, 0, -400));
	mi2->setScale(100);
	game::AABB aabb, aabb2;

	while (CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		SetCameraPositionAndTarget_UpVecY(VGet(600, 600, 600), VGet(0, 0, 0));
		SetCameraNearFar(5, 2000);

		ClearDrawScreen();

		if (!game::CollisionDetection::testMove(aabb, VGet(0, 0, 2), aabb2, VGet(0,0,0)).first) {
			mi->draw();
			aabb.drawFrame();
		}
		mi2->draw();
		aabb2.drawFrame();

		mi->move(VGet(0, 0, 2));
		aabb.update(mi);
		aabb2.update(mi2);


		ScreenFlip();
	}

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了
}