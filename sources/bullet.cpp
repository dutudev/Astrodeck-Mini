#include "raylib.h"
#include "raymath.h"
#include "bullet.hpp"
#include "asteroidManager.hpp"
#include "asteroid.hpp"

Bullet::Bullet(Vector2 startPos, Vector2 startDir) {
	position = startPos;
	direction = startDir;
	startTime = GetTime();
	asteroids = &AsteroidManager::GetInstance().GetAsteroids();
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
			asteroid->SetActive(false);
			active = false;
		}
	}
}

void Bullet::Draw() {
	DrawCircleV(position, size, WHITE);
}