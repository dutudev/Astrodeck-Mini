#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "asteroidManager.hpp"
#include "ui.hpp"


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


float AsteroidManager::GetTimeWaveShown() {
	return timeWaveShown;
}

float AsteroidManager::GetTimeWaveLeft() {
	return timeTillEndWave;
}

int AsteroidManager::GetWave() {
	return wave;
}

void AsteroidManager::UnloadTextures() {
	for (Texture2D& tex : asteroidTextures) {
		UnloadTexture(tex);
	}
}

int AsteroidManager::GetSelect1() {
	return select1;
}

int AsteroidManager::GetSelect2() {
	return select2;
}

int AsteroidManager::GetMaxAsteroids() {
	return maxAsteroids;
}

void AsteroidManager::UpdateMaxAsteroids(int n) {
	maxAsteroids = n;
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

void AsteroidManager::Reset() {
	asteroids.clear();
	maxAsteroids = 10;
	asteroidSpawn = false;
	spawnCooldown = 1.0f;
	lastSpawn = 0.0f;
	wave = 0;
	timeTillEndWave = 0;
	timeWaveShown = 0;
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
	timeTillEndWave -= GetFrameTime();
	if (timeTillEndWave <= 0) {
		wave++;
		timeTillEndWave = 30 + 10 * (wave - 1); // 30
		timeWaveShown = 30 + 10 * (wave - 1); // 30
		select1 = GetRandomValue(0, 3);
		select2 = GetRandomValue(0, 3);
		while (select1 == select2) {
			select2 = GetRandomValue(0, 3);
		}
		if (wave != 1) {
			UI::SetCurrentUI(2);
		}
		if (wave == 6) {
			UI::SetCurrentUI(4);
		}
	}
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