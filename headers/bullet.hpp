#pragma once
#include "raylib.h"


class Bullet {
private:
	const float speed = 650.0f;
	const int size = 2;
	const float timeToLive = 3.0f;

	bool active = true;
	float startTime = 0.0f;
	Vector2 position = { 0, 0 };
	Vector2 direction = { 0, 0 };
public:
	Bullet( Vector2 startPos, Vector2 startDirection);
	bool isActive();
	void Logic();
	void Draw();
};