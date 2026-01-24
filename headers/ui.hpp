#pragma once
#include "player.hpp"
#include <string>
#include <vector>

namespace UI {
	class Button;
	extern Player* player;
	extern Font font;
	extern Texture2D logoTex;
	extern int currentUI;
	extern bool shouldExit;
	extern std::vector<Button*> buttonsActive;

	void Setup();
	void Unload();
	void SetPlayer(Player* playerSet);
	void SetCurrentUI(int set);
	void LogicButtons();
	void DrawEndMenu();
	void DrawHeadUI();
	void DrawMenu();

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
	};
}