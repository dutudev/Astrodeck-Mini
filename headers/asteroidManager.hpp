#pragma once
#include "raylib.h"
#include "asteroid.hpp"
#include <vector>

class AsteroidManager {
private:
	int maxAsteroids = 10;
	int currentAsteroids = 0;
	bool asteroidSpawn = false;
	float spawnCooldown = 1.0f;
	float lastSpawn = 0.0f;
	std::vector<Asteroid*> asteroids;
	std::vector<Texture2D> asteroidTextures;
	static AsteroidManager instance;
	AsteroidManager() {};
public:
	static AsteroidManager& GetInstance();
	std::vector<Asteroid*>& GetAsteroids();
	void AddRemoveAsteroid(Asteroid* toRemove);
	void LoadTextures();
	void UnloadTextures();
	void SetSpawn(bool set);
	void Logic();
	void Draw();
	void DrawDebug();
};