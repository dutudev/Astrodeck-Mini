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
	Texture2D starsTex;
	Shader starsShader;
	int currentUI = 0;
	int timeLocation = 0;
	bool shouldExit = false;
	std::vector<Button*> buttonsActive;

	void Setup() {
		font = LoadFontEx(((std::string)GetWorkingDirectory() + "/assets/font/RobotoMonoBold.ttf").c_str(), 256, 0, 0);
		logoTex = LoadTexture(((std::string)GetWorkingDirectory() + "/assets/images/astrodeckLogo.png").c_str());
		starsTex = LoadTexture(((std::string)GetWorkingDirectory() + "/assets/images/starsFrontmanu.png").c_str());
		starsShader = LoadShader(0, ((std::string)GetWorkingDirectory() + "/assets/shaders/starShader.glsl").c_str());
		timeLocation = GetShaderLocation(starsShader, "time");
	}

	void Unload() {
		UnloadFont(font);
		UnloadTexture(logoTex);
		UnloadTexture(starsTex);
		UnloadShader(starsShader);
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

	void GoToMenu() {
		SetCurrentUI(0);
		player->Reset();
		AsteroidManager::GetInstance().Reset();
	}

	void RetryGame() {
		player->Reset();
		AsteroidManager::GetInstance().Reset();
		SetCurrentUI(1);
	}

	void Select1() {
		UpgradePlayer(AsteroidManager::GetInstance().GetSelect1());
	}

	void Select2() {
		UpgradePlayer(AsteroidManager::GetInstance().GetSelect2());
	}

	void UpgradePlayer(int n) {
		player->Upgrade(n);
		SetCurrentUI(1);
		AsteroidManager::GetInstance().UpdateMaxAsteroids(AsteroidManager::GetInstance().GetMaxAsteroids() + 3);
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
		case 2:
			buttonsActive.push_back(new Button({ 200, 300 }, { 400, 600 }, "", Select1));
			buttonsActive.push_back(new Button({ 600, 300 }, { 400, 600 }, "", Select2));
			break;
		case 3:
			buttonsActive.push_back(new Button({ 400, 350 }, { 200, 50 }, "Retry", RetryGame));
			buttonsActive.push_back(new Button({ 400, 450 }, { 200, 50 }, "Exit", GoToMenu));
			break;

		case 4:
			buttonsActive.push_back(new Button({ 400, 350 }, { 200, 50 }, "Replay", RetryGame));
			buttonsActive.push_back(new Button({ 400, 450 }, { 200, 50 }, "Exit", GoToMenu));
			break;
		}
	}

	void DrawEndMenu() {
		DrawRectangle(0, 0, 800, 600, { 0, 0, 0, 100 });
		DrawTextPro(font, "Game Over", Vector2{ 400, 200 } - MeasureTextEx(font, "Game Over", 64, 0) / 2.0f, { 0, 0 }, 0, 64, 0, WHITE);
		for (Button* button : buttonsActive) {
			button->Draw();
		}
	}

	void DrawWinMenu() {
		DrawRectangle(0, 0, 800, 600, { 0, 0, 0, 100 });
		DrawTextPro(font, "You Win", Vector2{ 400, 200 } - MeasureTextEx(font, "You Win", 64, 0) / 2.0f, { 0, 0 }, 0, 64, 0, WHITE);
		for (Button* button : buttonsActive) {
			button->Draw();
		}
	}


	void DrawSelectMenu() {
		for (Button* button : buttonsActive) {
			button->DrawNoRound();
		}
		DrawTextPro(font, "Select Upgrade", Vector2{ 400, 175 } - MeasureTextEx(font, "Select Upgrade", 64, 0) / 2.0f, { 0, 0 }, 0, 64, 0, WHITE);
		std::string title1, desc1, title2, desc2;
		GetTitleDesc(title1, desc1, AsteroidManager::GetInstance().GetSelect1());
		GetTitleDesc(title2, desc2, AsteroidManager::GetInstance().GetSelect2());
		DrawTextEx(font, title1.c_str(), Vector2{ 200, 300 } - MeasureTextEx(font, title1.c_str(), 32, 0) / 2.0f, 32, 0, WHITE);
		DrawTextEx(font, desc1.c_str(), Vector2{ 200, 350 } - MeasureTextEx(font, desc1.c_str(), 24, 0) / 2.0f, 24, 0, WHITE);
		DrawTextEx(font, title2.c_str(), Vector2{ 600, 300 } - MeasureTextEx(font, title2.c_str(), 32, 0) / 2.0f, 32, 0, WHITE);
		DrawTextEx(font, desc2.c_str(), Vector2{ 600, 350 } - MeasureTextEx(font, desc2.c_str(), 24, 0) / 2.0f, 24, 0, WHITE);
	}

	void GetTitleDesc(std::string& title, std::string& desc, int n) {
		switch (n) {
		case 0:
			title = "Speed";
			desc = "Increase speed and acceleration";
			break;
		case 1: 
			title = "Cooldown";
			desc = "Decrease shoot cooldown";
			break;
		case 2:
			title = "Rotation";
			desc = "Increase rotation speed";
			break;
		case 3:
			title = "Health";
			desc = "Increase max health";
			break;
		}
	}

	void LogicButtons() {
		for (Button* button : buttonsActive) {
			button->Logic();
		}
	}

	void DrawHeadUI() {
		DrawRectangleRounded({ 300, 550, 200, 250 }, 0.2f, 2, { (unsigned char)(150 + 65 * player->DamageAnim()), (unsigned char)(150 + 65 * player->HealthAnim()), 150, (unsigned char)(25 + 10 * player->HealthAnim() + 10 * player->DamageAnim()) });
		std::string textToWrite = "h: " + std::to_string(player->GetHealth()) + "  s: " + std::to_string(player->GetSpeed());
		if (player->IsReloading()) {
			DrawRectangleRounded({ 300, 550, 200, 250 }, 0.2f, 2, { 150, 150, 150, (unsigned char)(25 * player->TimeReloading()) });
		}
		DrawTextEx(font, textToWrite.c_str(), Vector2{ 400, 560 } - Vector2{ MeasureTextEx(font, textToWrite.c_str(), 25, 0).x, 0 } / 2.0f, 25, 0, { 255, 255, 255, 150 });

		if (AsteroidManager::GetInstance().GetTimeWaveShown() - 6 <= AsteroidManager::GetInstance().GetTimeWaveLeft()) {
			std::string text = "Wave - " + std::to_string(AsteroidManager::GetInstance().GetWave());
			std::string text2 = std::to_string((int)ceilf(AsteroidManager::GetInstance().GetTimeWaveLeft())) + " secs";
			DrawTextEx(font, text.c_str(), Vector2{ 400, 100 } - MeasureTextEx(font, text.c_str(), 36, 0) / 2.0f, 36, 0, { 255, 255, 255, 125 });
			if (AsteroidManager::GetInstance().GetTimeWaveShown() - 5 <= AsteroidManager::GetInstance().GetTimeWaveLeft()) {
				DrawTextEx(font, text2.c_str(), Vector2{ 400, 120 } - MeasureTextEx(font, text2.c_str(), 30, 0) / 2.0f, 30, 0, { 255, 255, 255, 100 });
			}
		}
	}

	void DrawMenu() {
		float shaderTime = GetTime() * 0.05f;
		SetShaderValue(starsShader, timeLocation, &shaderTime, SHADER_UNIFORM_FLOAT);
		BeginShaderMode(starsShader);
		DrawTexturePro(starsTex, { 0, 0, (float)starsTex.width, (float)starsTex.height }, { 400 - 500, 300 - 500, 1000, 1000 }, {0, 0}, 0, WHITE);//{ 400 - 500, 300 - 500, 1000, 1000 }
		EndShaderMode();
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
		DrawRectangleRounded({ position.x - size.x / 2.0f, position.y - size.y / 2.0f, size.x , size.y }, 0.2, 2, { 200, 200, 200, (unsigned char)(20 + 30 * color) });
		DrawTextPro(font, text.c_str(), position, MeasureTextEx(font, text.c_str(), 40, 5) / 2.0f, 0, 40, 5, WHITE);
	}

	void Button::DrawNoRound() {
		DrawRectangleRounded({ position.x - size.x / 2.0f, position.y - size.y / 2.0f, size.x , size.y }, 0, 2, { 200, 200, 200, (unsigned char)(20 + 30 * color) });
		DrawTextPro(font, text.c_str(), position, MeasureTextEx(font, text.c_str(), 40, 5) / 2.0f, 0, 40, 5, WHITE);
	}
}