#pragma once
#include "raylib.h"
#include "raymath.h"
#include <vector>

class Asteroid {
private:
	const Vector2 size = { 72, 72 };

	bool active = true;
	Vector2 position = { 0, 0 };
	Vector2 velocity = { 0, 0 };
	Texture2D texture;
	std::vector<Asteroid*> asteroidsCollided;
	void ResetPos();
public:
	Asteroid(Texture2D tex);
	Vector2 GetPosition();
	Vector2 GetVelocity();
	void AddAsteroidCollided(Asteroid* asteroid);
	void SetVelocity(Vector2 set);
	void SetPosition(Vector2 set);
	void SetActive(bool set);
	bool IsActive();
	void Logic();
	void Draw();
	void DrawDebug() {
		DrawCircleLinesV(position, 24, RED);
		DrawLineV(position, position + velocity, YELLOW);
	};

};