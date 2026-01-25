#pragma once
#include "raylib.h"
#include "asteroidManager.hpp"
#include "asteroid.hpp"
#include <vector>

class Player;

class Bullet {
private:
	const float speed = 650.0f;
	const int size = 2;
	const float timeToLive = 3.0f;

	bool active = true;
	float startTime = 0.0f;
	Vector2 position = { 0, 0 };
	Vector2 direction = { 0, 0 };
	Player* player = nullptr;
	std::vector<Asteroid*>* asteroids = nullptr;
public:
	Bullet( Vector2 startPos, Vector2 startDirection, Player* player);
	bool isActive();
	void Logic();
	void Draw();
};