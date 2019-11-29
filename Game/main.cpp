#include "stdafx.h"
#include "system/system.h"
#include "Player.h"
#include "level/Level.h"
#include "Game.h"

///////////////////////////////////////////////////////////////////
// �E�B���h�E�v���O�����̃��C���֐��B
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//�Q�[���̏������B
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");

	//�J�������������B
	g_camera3D.SetPosition({ 0.0f, 900.0f, -600.0f });
	g_camera3D.SetTarget({ 0.0f, 0.0f, 0.0f });
	g_camera3D.SetFar(10000.0f);
	
	camera2d.SetPosition({0.0f, 0.0f, -100.0f});
	camera2d.SetTarget({ 0.0f, 0.0f, 0.0f });
	//�v���C���[
	/*Player player;*/
	NewGO<Game>(0, "game");

	//�Q�[�����[�v�B
	while (DispatchWindowMessage() == true)
	{
		//�`��J�n�B
		g_graphicsEngine->BegineRender();
		//�Q�[���p�b�h�̍X�V�B	
		for (auto& pad : g_pad) {
			pad.Update();
		}
		//�����G���W���̍X�V�B
		g_physics.Update();
		//	Execute���X�V�B
		IGameObjectManager().Execute();
		//Game�̃A�b�v�f�[�g�B
		//game.Update();
		//�J�����̍X�V�B
		g_camera3D.Update();
		camera2d.Update();
	}
}