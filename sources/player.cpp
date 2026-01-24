#include "raylib.h"
#include "raymath.h"
#include "player.hpp"
#include "ui.hpp"
#include <string>
#include <iostream>
#include <vector>

Player::Player() {
	shipTexture = LoadTexture(((std::string)GetWorkingDirectory() + "/assets/images/ship.png").c_str());
	asteroids = &AsteroidManager::GetInstance().GetAsteroids();
	UI::SetPlayer(this);
}

Player::~Player() {
	UnloadTexture(shipTexture);
	UI::SetPlayer(nullptr);
}

void Player::SpawnBullet(Vector2 plrPos, Vector2 plrDir) {
	
	Bullet* bulletPtr = new Bullet(position, plrDir);
	activeBullets.push_back(bulletPtr);
}

void Player::BulletsLogic() {
	for (Bullet* bullet : activeBullets) {
		(*bullet).Logic();
	}
}

bool Player::IsReloading() {
	return lastCooldown + shootCooldown > GetTime();

}

float Player::TimeReloading() {
	return lastCooldown + shootCooldown - GetTime();
}

int Player::GetHealth() {
	return health;
}

int Player::GetSpeed() {
	return Vector2Length(velocity);
}

void Player::Logic() {
	float rotationRad = (rotation - 90) * PI / 180;
	//controls
	if (IsKeyDown(KEY_W)) {
		velocity += Vector2{ cosf(rotationRad), sinf(rotationRad) } *speed * GetFrameTime();
		particleEmitter.SetEmitter(true);
	}
	else {
		particleEmitter.SetEmitter(false);
	}

	if (IsKeyDown(KEY_A)) {
		rotation -= rotationSpeed * GetFrameTime();
	}

	if (IsKeyDown(KEY_D)) {
		rotation += rotationSpeed * GetFrameTime();
	}

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && lastCooldown + shootCooldown <= GetTime()) {
		SpawnBullet(position, Vector2{ cosf(rotationRad), sinf(rotationRad) });
		lastCooldown = GetTime();
	}

	for (Asteroid* asteroid : *asteroids) {
		if (CheckCollisionCircles(position, 10, asteroid->GetPosition(), 24)) {
			asteroid->SetActive(false);
			velocity = Vector2Normalize(velocity) * Vector2Length(velocity) * 0.35f;
			health -= 6;
		}
	}

	//velocity
	if (Vector2Length(velocity) >= maxSpeed) {
		velocity = Vector2Normalize(velocity) * maxSpeed;
	}
	position += velocity * GetFrameTime();
	
	//wrap-around
	if (position.y <= -30) {
		position.y = 625;
	}
	if (position.y >= 630) {
		position.y = -25;
	}
	if (position.x <= -30) {
		position.x = 825;
	}
	if (position.x >= 830) {
		position.x = -25;
	}
	float rotationRad1 = atan2f(posParticle1.y, posParticle1.x) - rotation * PI / 180.0f;
	float rotationRad2 = atan2f(posParticle2.y, posParticle2.x) - rotation * PI / 180.0f;
	//particles
	posParticleLine1 = position + Vector2{ -cosf(rotationRad1), sinf(rotationRad1) } * Vector2Length(posParticle1);
	posParticleLine2 = position + Vector2{ -cosf(rotationRad2), sinf(rotationRad2) } * Vector2Length(posParticle2);

	particleEmitter.Logic(posParticleLine1, posParticleLine2, Vector2Normalize(Vector2{ cosf(rotationRad), sinf(rotationRad) }) * 55);
}

void Player::ClearBullets() {
	std::vector<Bullet*>::iterator iter = activeBullets.begin();
	while (iter != activeBullets.end()) {
		if (!(*(*iter)).isActive()) {
			Bullet* bulToDel = (*iter);
			iter = activeBullets.erase(iter);
			delete bulToDel;
		}
		else {
			iter++;
		}
	}
	//std::cout << activeBullets.size() << '\n';
}

void Player::BulletsDraw() {
	for (Bullet* bullet : activeBullets) {
		(*bullet).Draw();
	}
}

void Player::DrawParticles() {
	particleEmitter.Draw();
}

void Player::Draw() {
	
	DrawTexturePro(shipTexture, { 0, 0, (float)shipTexture.width, (float)shipTexture.height }, { position.x, position.y, 50.0f, 50.0f }, { 25.0f, 25.0f }, rotation, WHITE);

}