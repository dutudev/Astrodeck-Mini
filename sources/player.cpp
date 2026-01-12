#include "raylib.h"
#include "raymath.h"
#include "player.hpp"
#include <string>
#include <iostream>
#include <vector>

Player::Player() {
	shipTexture = LoadTexture(((std::string)GetWorkingDirectory() + "/assets/images/ship.png").c_str());
}

Player::~Player() {
	UnloadTexture(shipTexture);
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

void Player::Logic() {

	//controls
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

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		float rotationRad = (rotation - 90) * PI / 180;
		SpawnBullet(position, Vector2{ cosf(rotationRad), sinf(rotationRad) });
	}

	//velocity
	if (Vector2Length(velocity) >= MaxSpeed) {
		velocity = Vector2Normalize(velocity) * MaxSpeed;
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

void Player::Draw() {

	DrawTexturePro(shipTexture, { 0, 0, (float)shipTexture.width, (float)shipTexture.height }, { position.x, position.y, 50.0f, 50.0f }, { 25.0f, 25.0f }, rotation, WHITE);

}