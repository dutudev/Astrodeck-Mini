#include "raylib.h"
#include "player.hpp"
#include "asteroidManager.hpp"
#include "ui.hpp"
int WinMain() {

	InitWindow(800, 600, "MiniAstrodeck");
	SetExitKey(KEY_NULL);

	Player player;
	AsteroidManager::GetInstance().LoadTextures();
	UI::Setup();
	UI::SetCurrentUI(0);
	while (!UI::shouldExit) {

		if (WindowShouldClose()) {
			UI::shouldExit = true;
		}

		switch (UI::currentUI) {
		case 0:
			UI::LogicButtons();
			break;
		case 1:
			player.Logic();
			player.BulletsLogic();
			AsteroidManager::GetInstance().Logic();
			break;
		case 2:
			UI::LogicButtons();
			break;
		case 3:
			UI::LogicButtons();
			break;
		case 4:
			UI::LogicButtons();
		}
		
		BeginDrawing();
		ClearBackground(BLACK);

		switch (UI::currentUI) {
		case 0:
			UI::DrawMenu();
			break;
		case 1:
			player.DrawParticles();
			AsteroidManager::GetInstance().Draw();
			player.BulletsDraw();
			player.Draw();

			//player.DrawDebug();

			player.ClearBullets();
			//AsteroidManager::GetInstance().DrawDebug();
			
			UI::DrawHeadUI();
			break;
		case 2:
			player.DrawParticles();
			AsteroidManager::GetInstance().Draw();
			player.BulletsDraw();
			player.Draw();

			UI::DrawHeadUI();
			UI::DrawSelectMenu();
			break;
		case 3:
			player.DrawParticles();
			AsteroidManager::GetInstance().Draw();
			player.BulletsDraw();
			player.Draw();

			UI::DrawHeadUI();
			UI::DrawEndMenu();
			break;
		case 4:
			player.DrawParticles();
			AsteroidManager::GetInstance().Draw();
			player.BulletsDraw();
			player.Draw();

			UI::DrawHeadUI();
			UI::DrawWinMenu();
		}
		EndDrawing();

	}
	AsteroidManager::GetInstance().UnloadTextures();
	UI::Unload();
	return 0;
}