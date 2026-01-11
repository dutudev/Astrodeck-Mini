#pragma once
#include "raylib.h"

class Player {
private:
	const float MaxSpeed = 150;

	float speed = 100;
	float rotationSpeed = 80;
	float rotation = 0;
	Vector2 position = {50, 50};
	Vector2 velocity = { 0, 0 };
	Texture shipTexture;
public:
	Player();
	~Player();
	void Logic();
	void Draw();
};