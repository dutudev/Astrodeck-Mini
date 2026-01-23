#include "ui.hpp"
#include "player.hpp"
#include "raylib.h"
#include <string>

namespace UI {
	Player* player = nullptr;
	Font font;

	void Setup() {
		font = LoadFontEx(((std::string)GetWorkingDirectory() + "/assets/font/RobotoMonoBold.ttf").c_str(), 256, 0, 0);
	}

	void Unload() {
		UnloadFont(font);
	}

	void SetPlayer(Player* playerSet) {
		player = playerSet;
	}

	void DrawHeadUI() {
		DrawRectangleRounded({ 300, 550, 200, 250 }, 0.2f, 2, { 150, 150, 150, 25 });
		std::string textToWrite = "h: " + std::to_string(player->GetHealth()) + "  s: " + std::to_string(player->GetSpeed());
		if (player->IsReloading()) {
			DrawRectangleRounded({ 300, 550, 200, 250 }, 0.2f, 2, { 150, 150, 150, (unsigned char)(25 * player->TimeReloading())});
		}
		DrawTextEx(font, textToWrite.c_str(), Vector2{ 400, 560 } - Vector2{ MeasureTextEx(font, textToWrite.c_str(), 25, 0).x, 0 } / 2.0f, 25, 0, { 255, 255, 255, 150 });
	}
}