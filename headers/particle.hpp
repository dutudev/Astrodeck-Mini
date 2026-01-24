#pragma once
#include "raylib.h"
#include "raymath.h"

class Particle {
private:
	Vector2 position;
	Vector2 velocity;
	float lifetime = 5.0f;
public:
	Particle(Vector2 positionSet, Vector2 velocitySet);
	float GetLifetime();
	void Logic();
	void Draw();

};