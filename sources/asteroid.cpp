#include "raylib.h"
#include "raymath.h"
#include "asteroid.hpp"
#include "asteroidManager.hpp"
#include <iostream>
#include <algorithm>

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
	velocity = Vector2{ cosf(rotation), sinf(rotation) } * GetRandomValue(18, 45);
	for (Asteroid* as : AsteroidManager::GetInstance().GetAsteroids()) {
		if (CheckCollisionCircles(position, 24, as->GetPosition(), 24) && as != this) {
			ResetPos();
		}
	}
}

Vector2 Asteroid::GetPosition() {
	return position;
}
Vector2 Asteroid::GetVelocity() {
	return velocity;
}

void Asteroid::AddAsteroidCollided(Asteroid* asteroid) {
	asteroidsCollided.push_back(asteroid);
}

void Asteroid::SetVelocity(Vector2 set) {
	velocity = set;
}

void Asteroid::SetPosition(Vector2 set) {
	position = set;
}

void Asteroid::SetActive(bool set) {
	active = set;
}

bool Asteroid::IsActive() {
	return active;
}

void Asteroid::Logic() {
	Vector2 tempPos = position + velocity * GetFrameTime();
	for (Asteroid* as : AsteroidManager::GetInstance().GetAsteroids()) {
		if (CheckCollisionCircles(tempPos, 24, as->GetPosition(), 24) && as != this && std::find(asteroidsCollided.begin(), asteroidsCollided.end(), as) == asteroidsCollided.end()) {

			//calculate velocity direction of the first asteroid
			Vector2 normalVec1 = Vector2Normalize(position - as->GetPosition());
			Vector2 velocity1Normal = Vector2Scale(normalVec1, -1 * Vector2DotProduct(velocity, normalVec1));
			Vector2 velocity1Tangential = velocity1Normal + velocity;

			//calculate velocity direction of the second asteroid
			Vector2 normalVec2 = Vector2Scale(normalVec1, -1);
			Vector2 velocity2Normal = Vector2Scale(normalVec2, -1 * Vector2DotProduct(as->GetVelocity(), normalVec2));
			Vector2 velocity2Tangential = velocity2Normal + as->GetVelocity();

			Vector2 auxVelocity1Normal = velocity1Normal;
			velocity1Normal = Vector2Scale(velocity2Normal, -1);
			velocity2Normal = Vector2Scale(auxVelocity1Normal, -1);

			velocity = velocity1Normal + velocity1Tangential;
			as->SetVelocity(velocity2Normal + velocity2Tangential);

			asteroidsCollided.clear();
			as->AddAsteroidCollided(this);
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