#pragma once
#include "raylib.h"
#include "raymath.h"

class Asteroid {
private:
	const Vector2 size = { 72, 72 };

	
	Vector2 position = { 0, 0 };
	Vector2 velocity = { 0, 0 };
	Texture2D texture;
	void ResetPos();
public:
	Asteroid(Texture2D tex);
	Vector2 GetPosition();
	Vector2 GetVelocity();
	void SetVelocity(Vector2 set);
	void Logic();
	void Draw();
	void DrawDebug() {
		DrawCircleLinesV(position, 24, RED);
	};

};