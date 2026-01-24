#include "ui.hpp"
#include "player.hpp"
#include "raylib.h"
#include <string>
#include <vector>
#include <iostream>

namespace UI {
	Player* player = nullptr;
	Font font;
	Texture2D logoTex;
	int currentUI = 0;
	bool shouldExit = false;
	std::vector<Button*> buttonsActive;

	void Setup() {
		font = LoadFontEx(((std::string)GetWorkingDirectory() + "/assets/font/RobotoMonoBold.ttf").c_str(), 256, 0, 0);
		logoTex = LoadTexture(((std::string)GetWorkingDirectory() + "/assets/images/astrodeckLogo.png").c_str());
	}

	void Unload() {
		UnloadFont(font);
		UnloadTexture(logoTex);
	}

	void SetPlayer(Player* playerSet) {
		player = playerSet;
	}

	void GoToGame() {
		SetCurrentUI(1);
	}

	void ExitGame() {
		shouldExit = true;
	}

	void SetCurrentUI(int set) {
		currentUI = set;
		std::vector<Button*>::iterator iter = buttonsActive.begin();
		while(iter != buttonsActive.end()) {
			delete *iter;
			iter = buttonsActive.erase(iter);
		}
		switch (set) {
		case 0:
			buttonsActive.push_back(new Button({ 400, 300 }, { 200, 50 }, "Play", GoToGame));
			buttonsActive.push_back(new Button({ 400, 400 }, { 200, 50 }, "Exit", ExitGame));
			break;

		}
	}

	void LogicButtons() {
		for (Button* button : buttonsActive) {
			button->Logic();
		}
	}

	void DrawHeadUI() {
		DrawRectangleRounded({ 300, 550, 200, 250 }, 0.2f, 2, { 150, 150, 150, 25 });
		std::string textToWrite = "h: " + std::to_string(player->GetHealth()) + "  s: " + std::to_string(player->GetSpeed());
		if (player->IsReloading()) {
			DrawRectangleRounded({ 300, 550, 200, 250 }, 0.2f, 2, { 150, 150, 150, (unsigned char)(25 * player->TimeReloading())});
		}
		DrawTextEx(font, textToWrite.c_str(), Vector2{ 400, 560 } - Vector2{ MeasureTextEx(font, textToWrite.c_str(), 25, 0).x, 0 } / 2.0f, 25, 0, { 255, 255, 255, 150 });
	}

	void DrawMenu() {
		DrawTexturePro(logoTex, { 0, 0, (float)logoTex.width, (float)logoTex.height }, { 400, 150, 350, 350 }, {175, 175}, 0, WHITE);
		for (Button* button : buttonsActive) {
			button->Draw();
		}
		DrawTextPro(font, "Game made by dutudev", Vector2{ 400, 580} - MeasureTextEx(font, "Game made by dutudev", 24, 0) /2.0f, {0, 0}, 0, 24, 0, WHITE);
	}

	Button::Button(Vector2 positionSet, Vector2 sizeSet, std::string textSet, void (*function)()) {
		position = positionSet;
		size = sizeSet;
		text = textSet;
		Function = function;
	}

	void Button::Logic() {
		if (CheckCollisionPointRec(GetMousePosition(), { position.x - size.x / 2.0f, position.y - size.y / 2.0f, size.x , size.y })) {
			color = 1.0f;
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				Function();
			}
		}
		else {
			color = 0.0f;
		}
		
	}

	void Button::Draw() {
		DrawRectangleRounded({ position.x - size.x / 2.0f, position.y - size.y / 2.0f, size.x , size.y }, 0.2, 2, { 255, 255, 255, (unsigned char)(20 + 30 * color) });
		DrawTextPro(font, text.c_str(), position, MeasureTextEx(font, text.c_str(), 40, 5) / 2.0f, 0, 40, 5, WHITE);
	}
}