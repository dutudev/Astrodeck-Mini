#include "raylib.h"
#include "raymath.h"
#include "bullet.hpp"
#include "asteroidManager.hpp"
#include "asteroid.hpp"
#include "player.hpp"

Bullet::Bullet(Vector2 startPos, Vector2 startDir, Player* player) {
	position = startPos;
	direction = startDir;
	startTime = GetTime();
	asteroids = &AsteroidManager::GetInstance().GetAsteroids();
	Bullet::player = player;
}

bool Bullet::isActive() {
	return active;
}

void Bullet::Logic() {
	position += direction * speed * GetFrameTime();

	if (GetTime() >= startTime + timeToLive) {
		active = false;
	}

	for (Asteroid* asteroid : *asteroids) {
		if (CheckCollisionCircles(position, size, asteroid->GetPosition(), 24)) {
			player->AddHealth(1);
			asteroid->SetActive(false);
			active = false;
		}
	}
}

void Bullet::Draw() {
	DrawCircleV(position, size, WHITE);
}