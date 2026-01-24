#pragma once
#include "particle.hpp"
#include <vector>

class ParticleEmitter {
private:
	bool emitting = false;
	float lastSpawn = 0;
	std::vector<Particle*> particles;
public:
	ParticleEmitter();
	void SetEmitter(bool set);
	void Logic(Vector2 linePos1, Vector2 linePos2, Vector2 playerVelocity);
	void Draw();
};