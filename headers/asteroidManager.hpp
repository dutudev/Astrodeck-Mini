#pragma once
#include "raylib.h"
#include "asteroid.hpp"
#include <vector>

class AsteroidManager {
private:
	int maxAsteroids = 10;
	int currentAsteroids = 0;
	std::vector<Asteroid> asteroids;
	static AsteroidManager instance;
	AsteroidManager(){};
public:
	static AsteroidManager GetInstance();
};