#include "particle.hpp"

Particle::Particle(Vector2 positionSet, Vector2 velocitySet) {
	position = positionSet;
	velocity = velocitySet;
}

float Particle::GetLifetime() {
	return lifetime;
}

void Particle::Logic() {
	position += velocity * GetFrameTime();
	lifetime -= GetFrameTime();
}

void Particle::Draw() {
	DrawCircleV(position, 2 * Clamp(lifetime, 0, 1), WHITE);
}