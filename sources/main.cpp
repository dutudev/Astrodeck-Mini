#include "raylib.h"
#include "player.hpp"
#include "asteroidManager.hpp"
int main() {

	InitWindow(800, 600, "MiniAstrodeck");

	Player player;
	AsteroidManager::GetInstance().LoadTextures();

	while (!WindowShouldClose()) {
		
		player.Logic();
		player.BulletsLogic();
		AsteroidManager::GetInstance().Logic();

		BeginDrawing();
		ClearBackground(BLACK);


		AsteroidManager::GetInstance().Draw();
		player.BulletsDraw();
		player.Draw();
		player.ClearBullets();

		EndDrawing();

	}
	AsteroidManager::GetInstance().UnloadTextures();

	return 0;
}