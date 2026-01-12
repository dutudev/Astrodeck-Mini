#include "raylib.h"
#include "raymath.h"
#include "bullet.hpp"


Bullet::Bullet(Vector2 startPos, Vector2 startDir) {
	position = startPos;
	direction = startDir;
	startTime = GetTime();
}

bool Bullet::isActive() {
	return active;
}

void Bullet::Logic() {
	position += direction * speed * GetFrameTime();
	if (GetTime() >= startTime + timeToLive) {
		active = false;
	}
}

void Bullet::Draw() {
	DrawCircleV(position, size, WHITE);
}