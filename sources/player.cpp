#include "raylib.h"
#include "raymath.h"
#include "player.hpp"
#include <string>
#include <iostream>

Player::Player() {
	shipTexture = LoadTexture(((std::string)GetWorkingDirectory() + "/assets/images/ship.png").c_str());
}

Player::~Player() {
	UnloadTexture(shipTexture);
}

void Player::Logic() {
	if (IsKeyDown(KEY_W)) {
		float rotationRad = (rotation - 90) * PI / 180;
		velocity += Vector2{cosf(rotationRad), sinf(rotationRad)} * speed * GetFrameTime();
	}

	if (IsKeyDown(KEY_A)) {
		rotation -= rotationSpeed * GetFrameTime();
	}

	if (IsKeyDown(KEY_D)) {
		rotation += rotationSpeed * GetFrameTime();
	}

	position += velocity * GetFrameTime();
	std::cout << position.y << '\n';
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
}

void Player::Draw() {
	DrawTexturePro(shipTexture, { 0, 0, (float)shipTexture.width, (float)shipTexture.height }, { position.x, position.y, 50.0f, 50.0f }, { 25.0f, 25.0f }, rotation, WHITE);
}