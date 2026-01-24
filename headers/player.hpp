#pragma once
#include "raylib.h"
#include "bullet.hpp"
#include "asteroid.hpp"
#include "asteroidManager.hpp"
#include "particleEmitter.hpp"
#include "particle.hpp"
#include <vector>
class Player {
private:

	int health = 20;
	float speed = 80;
	float maxSpeed = 80;
	float rotationSpeed = 80;
	float shootCooldown = 2.0f;
	float rotation = 0;
	float lastCooldown = 0;
	Vector2 position = { 400.0f - 25.0f / 2.0f, 300.0f - 25.0f / 2.0f };
	Vector2 velocity = { 0, 0 };
	Vector2 posParticle1 = { -7 , 10 };
	Vector2 posParticle2 = { 7, 10 };
	Vector2 posParticleLine1, posParticleLine2;
	Texture shipTexture;
	ParticleEmitter particleEmitter;

	std::vector<Bullet*> activeBullets;
	std::vector<Asteroid*>* asteroids = nullptr;

	void SpawnBullet(Vector2 plrPos, Vector2 plrDir);
public:
	Player();
	~Player();
	bool IsReloading();
	float TimeReloading();
	int GetHealth();
	int GetSpeed();
	void ClearBullets();
	void BulletsLogic();
	void Logic();
	void BulletsDraw();
	void DrawParticles();
	void Draw();
	void DrawDebug() {
		float rotationRad1 = atan2f(posParticle1.y, posParticle1.x) - rotation * PI / 180.0f;
		float rotationRad2 = atan2f(posParticle2.y, posParticle2.x) - rotation * PI / 180.0f;
		DrawCircleLinesV(position, 10, ORANGE);
		
		DrawLineV(position +  Vector2{ -cosf(rotationRad1), sinf(rotationRad1) } * Vector2Length(posParticle1), position + Vector2{ -cosf(rotationRad2), sinf(rotationRad2) } * Vector2Length(posParticle2), BLUE);
	}
};