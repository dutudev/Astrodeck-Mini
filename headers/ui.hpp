#pragma once
#include "player.hpp"
#include <string>
#include <vector>

namespace UI {
	class Button;
	extern Player* player;
	extern Font font;
	extern Texture2D logoTex;
	extern Texture2D starsTex;
	extern Shader starsShader;
	extern int timeLocation;
	extern int currentUI;
	extern bool shouldExit;
	extern std::vector<Button*> buttonsActive;

	void Setup();
	void Unload();
	void SetPlayer(Player* playerSet);
	void SetCurrentUI(int set);
	void LogicButtons();
	void Select1();
	void Select2();
	void UpgradePlayer(int n);
	void DrawSelectMenu();
	void DrawEndMenu();
	void DrawWinMenu();
	void DrawHeadUI();
	void DrawMenu();
	void GetTitleDesc(std::string& title, std::string& desc, int n);
	class Button {
	private:
		Vector2 position = {0, 0};
		Vector2 size = {0 ,0};
		std::string text = "";
		float color = 0.0f;
		void(*Function)() = nullptr;
	public:
		Button(Vector2 positionSet, Vector2 sizeSet, std::string textSet, void (*function)());
		void Logic();
		void Draw();
		void DrawNoRound();
	};
}