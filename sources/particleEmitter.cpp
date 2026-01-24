#include "particleEmitter.hpp"

ParticleEmitter::ParticleEmitter(){
	emitting = false;
}

void ParticleEmitter::SetEmitter(bool set) {
	emitting = set;
}

void ParticleEmitter::Reset() {
	std::vector<Particle*>::iterator iter = particles.begin();

	while (iter != particles.end()) {
		delete* iter;
		iter = particles.erase(iter);
	}
}

void ParticleEmitter::Logic(Vector2 linePos1, Vector2 linePos2, Vector2 playerVelocity) {
	if (emitting && lastSpawn + 0.01f <= GetTime()) {
		lastSpawn = GetTime();
		playerVelocity *= -1;
		float rotation = atan2f(playerVelocity.y, playerVelocity.x) / PI * 180;
		rotation += (float)GetRandomValue(-600, 600) / 10.0f; //10
		rotation = rotation * PI / 180;
		particles.push_back(new Particle(Vector2Lerp(linePos1, linePos2, (float)GetRandomValue(0, 1000) / 1000.0f), Vector2{ cosf(rotation), sinf(rotation) } *10));
	}

	std::vector<Particle*>::iterator iter = particles.begin();

	while (iter != particles.end()) {
		if ((*iter)->GetLifetime() <= 0) {
			delete* iter;
			iter = particles.erase(iter);
		}
		else {
			(*iter)->Logic();
			iter++;
		}
	}
}

void ParticleEmitter::Draw() {
	
	for (Particle* particle : particles) {
		particle->Draw();
	}

}