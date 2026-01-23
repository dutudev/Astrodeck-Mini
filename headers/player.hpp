#pragma once
#include "raylib.h"
#include "bullet.hpp"
#include "asteroid.hpp"
#include "asteroidManager.hpp"
#include <vector>
class Player {
private:

	int health = 20;
	float speed = 80;
	float maxSpeed = 80;
	float rotationSpeed = 80;
	float shootCooldown = 2.0f;
	float rotation = 0;
	float lastCooldown = 0;
	Vector2 position = { 400.0f - 25.0f / 2.0f, 300.0f - 25.0f / 2.0f };
	Vector2 velocity = { 0, 0 };
	Texture shipTexture;

	std::vector<Bullet*> activeBullets;
	std::vector<Asteroid*>* asteroids = nullptr;

	void SpawnBullet(Vector2 plrPos, Vector2 plrDir);
public:
	Player();
	~Player();
	bool IsReloading();
	float TimeReloading();
	int GetHealth();
	int GetSpeed();
	void ClearBullets();
	void BulletsLogic();
	void Logic();
	void BulletsDraw();
	void Draw();
	void DrawDebug() {
		DrawCircleLinesV(position, 10, ORANGE);
	}
};