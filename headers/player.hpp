#pragma once
#include "raylib.h"
#include "bullet.hpp"
#include <vector>
class Player {
private:
	const float MaxSpeed = 150;

	float speed = 100;
	float rotationSpeed = 80;
	float rotation = 0;
	Vector2 position = { 400.0f - 25.0f / 2.0f, 300.0f - 25.0f / 2.0f };
	Vector2 velocity = { 0, 0 };
	Texture shipTexture;

	std::vector<Bullet*> activeBullets;

	void SpawnBullet(Vector2 plrPos, Vector2 plrDir);
public:
	Player();
	~Player();
	void ClearBullets();
	void BulletsLogic();
	void Logic();
	void BulletsDraw();
	void Draw();
};