#include "raylib.h"
#include "player.hpp"

int main() {

	InitWindow(800, 600, "e");

	Player player;

	while (!WindowShouldClose()) {
		
		player.Logic();

		BeginDrawing();
		ClearBackground(BLACK);

		player.Draw();

		EndDrawing();

	}


	return 0;
}