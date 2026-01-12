#include "raylib.h"
#include "player.hpp"

int main() {

	InitWindow(800, 600, "MiniAstrodeck");

	Player player;

	while (!WindowShouldClose()) {
		
		player.Logic();
		player.BulletsLogic();

		BeginDrawing();
		ClearBackground(BLACK);


		player.BulletsDraw();
		player.Draw();

		player.ClearBullets();

		EndDrawing();

	}


	return 0;
}