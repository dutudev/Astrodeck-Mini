#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "asteroidManager.hpp"


AsteroidManager AsteroidManager::instance;

void AsteroidManager::LoadTextures() {
	asteroidTextures.push_back(LoadTexture(((std::string)GetWorkingDirectory() + "/assets/images/asteroids/rock1.png").c_str()));
	asteroidTextures.push_back(LoadTexture(((std::string)GetWorkingDirectory() + "/assets/images/asteroids/rock2.png").c_str()));
	asteroidTextures.push_back(LoadTexture(((std::string)GetWorkingDirectory() + "/assets/images/asteroids/rock3.png").c_str()));
	asteroidTextures.push_back(LoadTexture(((std::string)GetWorkingDirectory() + "/assets/images/asteroids/rock4.png").c_str()));
	//Asteroid* as = new Asteroid(LoadTexture(((std::string)GetWorkingDirectory() + "/assets/images/asteroids/rock1.png").c_str()));
	//asteroids.push_back(as);
}

void AsteroidManager::UnloadTextures() {
	for (Texture2D& tex : asteroidTextures) {
		UnloadTexture(tex);
	}
}

AsteroidManager& AsteroidManager::GetInstance() {
	return instance;
}

std::vector<Asteroid*>& AsteroidManager::GetAsteroids() {
	return asteroids;
}

void AsteroidManager::SetSpawn(bool set) {
	asteroidSpawn = set;
}

void AsteroidManager::Logic() {
	if (lastSpawn + spawnCooldown <= GetTime() ) {
		lastSpawn = GetTime();
		Asteroid* asteroid = new Asteroid(asteroidTextures[GetRandomValue(0, 3)]);
		asteroids.push_back(asteroid);
	}
	for (Asteroid* asteroid : asteroids) {
		asteroid->Logic();
	}
	//std::cout << asteroids.size() << '\n';
	
}

void AsteroidManager::Draw() {
	for (Asteroid* asteroid : asteroids) {
		asteroid->Draw();
		asteroid->DrawDebug();
	}
}