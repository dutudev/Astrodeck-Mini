#pragma once
#include "raylib.h"
#include "asteroid.hpp"
#include <vector>

class AsteroidManager {
private:
	int maxAsteroids = 10;
	bool asteroidSpawn = false;
	float spawnCooldown = 1.0f;
	float lastSpawn = 0.0f;
	int wave = 0;
	float timeTillEndWave = 0;
	float timeWaveShown = 0;
	int select1 = 0, select2 = 0;
	std::vector<Asteroid*> asteroids;
	std::vector<Texture2D> asteroidTextures;
	static AsteroidManager instance;
	AsteroidManager() {};
public:
	static AsteroidManager& GetInstance();
	std::vector<Asteroid*>& GetAsteroids();
	float GetTimeWaveShown();
	float GetTimeWaveLeft();
	int GetSelect1();
	int GetSelect2();
	int GetWave();
	int GetMaxAsteroids();
	void UpdateMaxAsteroids(int n);
	void AddRemoveAsteroid(Asteroid* toRemove);
	void LoadTextures();
	void UnloadTextures();
	void SetSpawn(bool set);
	void Reset();
	void Logic();
	void Draw();
	void DrawDebug();
};