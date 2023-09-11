/*
�v���W�F�N�g�ݒ�
�Q�l�F
[1]https://dxlib.xsrv.jp/use/dxuse_vscom2022.html
[2]https://www.ay3s-room.com/entry/dxlib-lnk2019
*/
#include "DxLib.h"
#include "ModelResource.hpp"
#include "ModelInstance.hpp"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
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

	WaitKey();				// �L�[���͑҂�

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}