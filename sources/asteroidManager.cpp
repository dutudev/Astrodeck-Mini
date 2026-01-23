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
	/*
	Asteroid* as = new Asteroid(LoadTexture(((std::string)GetWorkingDirectory() + "/assets/images/asteroids/rock1.png").c_str()));
	as->SetPosition({ 100, 300 });
	as->SetVelocity({ 150, 0 });
	asteroids.push_back(as);
	Asteroid* as1 = new Asteroid(LoadTexture(((std::string)GetWorkingDirectory() + "/assets/images/asteroids/rock1.png").c_str()));
	as1->SetPosition({ 450, 340 });
	as1->SetVelocity({ 15, 0 });
	asteroids.push_back(as1);*/
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

void AsteroidManager::AddRemoveAsteroid(Asteroid* toRemove) {
	toRemove->SetActive(false);
}

void AsteroidManager::SetSpawn(bool set) {
	asteroidSpawn = set;
}

void AsteroidManager::Logic() {
	
	if (lastSpawn + spawnCooldown <= GetTime() && asteroids.size() < maxAsteroids) {
		lastSpawn = GetTime();
		Asteroid* asteroid = new Asteroid(asteroidTextures[GetRandomValue(0, 3)]);
		asteroids.push_back(asteroid);
	}
	std::vector<Asteroid*>::iterator iter = asteroids.begin();
	while (iter != asteroids.end()) {
		(*iter)->Logic();
		if (!(*iter)->IsActive()) {
			iter = asteroids.erase(iter);
		}
		else {
			iter++;
		}
	}
	//std::cout << asteroids.size() << '\n';
	
}

void AsteroidManager::Draw() {
	for (Asteroid* asteroid : asteroids) {
		asteroid->Draw();
	}
}

void AsteroidManager::DrawDebug() {
	for (Asteroid* asteroid : asteroids) {
		asteroid->DrawDebug();
	}
}