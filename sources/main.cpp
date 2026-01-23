#include "raylib.h"
#include "player.hpp"
#include "asteroidManager.hpp"
#include "ui.hpp"
int main() {

	InitWindow(800, 600, "MiniAstrodeck");

	Player player;
	AsteroidManager::GetInstance().LoadTextures();
	UI::Setup();
	while (!WindowShouldClose()) {
		
		player.Logic();
		player.BulletsLogic();
		AsteroidManager::GetInstance().Logic();

		BeginDrawing();
		ClearBackground(BLACK);


		AsteroidManager::GetInstance().Draw();
		player.BulletsDraw();
		player.Draw();

		player.DrawDebug();

		player.ClearBullets();
		AsteroidManager::GetInstance().DrawDebug();

		UI::DrawHeadUI();
		EndDrawing();

	}
	AsteroidManager::GetInstance().UnloadTextures();
	UI::Unload();
	return 0;
}