#pragma once
#include "player.hpp"


namespace UI {
	extern Player* player;
	extern Font font;

	void Setup();
	void Unload();
	void SetPlayer(Player* playerSet);
	void DrawHeadUI();
}