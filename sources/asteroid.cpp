#include "raylib.h"
#include "raymath.h"
#include "asteroid.hpp"
#include "asteroidManager.hpp"
#include <iostream>

Asteroid::Asteroid(Texture2D tex) {
	texture = tex;
	ResetPos();
	

}

void Asteroid::ResetPos() {
	switch (GetRandomValue(0, 3)) {
	case 0:
		position.x = GetRandomValue(0, 800 - size.x);
		position.y = -size.y / 2.0f;
		break;
	case 1:
		position.x = -size.x /2.0f;
		position.y = GetRandomValue(0, 600 - size.y);
		break;
	case 2:
		position.x = GetRandomValue(0, 800 - size.x);
		position.y = 600 + size.y / 2.0;
		break;
	case 3:
		position.x = 800 + size.x / 2.0f;
		position.y = GetRandomValue(0, 600 - size.y);
		break;
	}

	velocity = Vector2Normalize(Vector2{ 400, 300 } - position);

	float rotation = atan2f(velocity.y, velocity.x) / PI * 180;
	rotation += (float)GetRandomValue(-600, 600) / 24.0f;
	rotation = rotation * PI / 180;
	velocity = Vector2{ cosf(rotation), sinf(rotation) } * GetRandomValue(10, 25);
}

Vector2 Asteroid::GetPosition() {
	return position;
}
Vector2 Asteroid::GetVelocity() {
	return velocity;
}
void Asteroid::SetVelocity(Vector2 set) {
	velocity = set;
}

void Asteroid::Logic() {
	Vector2 tempPos = position + velocity * GetFrameTime();
	for (Asteroid* as : AsteroidManager::GetInstance().GetAsteroids()) {
		if (CheckCollisionCircles(tempPos, 24, as->GetPosition(), 30) && as == this) {
			Vector2 normalVec = Vector2Normalize(position - as->GetPosition());
			velocity = normalVec * Vector2DotProduct(normalVec, velocity) + velocity * Vector2DotProduct(normalVec, velocity);
			as->SetVelocity(normalVec * Vector2DotProduct(normalVec, as->GetVelocity()) + as->GetVelocity() * Vector2DotProduct(normalVec, as->GetVelocity()));
		}
	}
	position += velocity * GetFrameTime();
	if (!CheckCollisionCircleRec(position, 24, {-40.0f, -40.0f, 880, 680})) {
		ResetPos();
	}
	
}

void Asteroid::Draw() {
	DrawTexturePro(texture, { 0, 0, (float)texture.width, (float)texture.height }, { position.x, position.y, size.x, size.y }, size / 2.0f, 0, WHITE);
}