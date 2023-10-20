﻿/*
プロジェクト設定
参考：
[1]https://dxlib.xsrv.jp/use/dxuse_vscom2022.html
[2]https://www.ay3s-room.com/entry/dxlib-lnk2019
*/
#include "DxLib.h"
#include "ModelDatabase.hpp"
#include "PlayerModel.hpp"
#include "MessageServer.hpp"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	const auto White = GetColorF(1.0f, 1.0f, 1.0f, 1.0f);
	const auto Black = GetColorF(0.0f, 0.0f, 0.0f, 1.0f);
	const auto Gray = GetColorF(0.1f, 0.1f, 0.1f, 1.0f);
	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}
	// 背景色
	SetBackgroundColor(128, 128, 128);

	// 標準ライトの設定
	ChangeLightTypeDir(VGet(-1, 0, 0));// ディレクショナルライトにする
	SetLightAmbColor(White);// アンビエントカラー
	SetLightDifColor(White);// ディフューズカラーを設定

	// マテリアルのパラメータをセット
	MATERIALPARAM MatParam;
	MatParam.Diffuse = White;	// ディフューズカラーは白
	MatParam.Ambient = Gray;	// アンビエントカラーは白( ライトのアンビエントカラーを弱くして反映する )
	MatParam.Specular = Black;	// スペキュラカラーは無し
	MatParam.Emissive = Black;	// エミッシブカラー( 自己発光 )もなし
	MatParam.Power = 0.0f;						// スペキュラはないので０
	SetMaterialParam(MatParam);

	// 3D描画機能を有効にする
	SetUseZBuffer3D(true);
	SetWriteZBuffer3D(true);

	// ダブルバッファリング
	SetDrawScreen(DX_SCREEN_BACK);

	game::ModelDatabasePtr mdb(new game::ModelDatabase());
	game::MessageServerPtr server(new game::MessageServer());
	game::PlayerModelPtr playerModel(new game::PlayerModel(server, mdb, 100, "oni.txt"));

	while (CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		SetCameraPositionAndTarget_UpVecY(VGet(200, 200, 200), VGet(50, 0, 50));
		SetCameraNearFar(5, 2000);

		ClearDrawScreen();

		playerModel->draw();

		ScreenFlip();
	}

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了
}