#pragma once
#include "Box.h"
#include "Camera.h"
#include "Characters.h"
#include "FireSeedManager.h"
#include "GamesEngineeringBase.h" 
#include "Graphics.h"
#include "Input.h"
#include "Projectile.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>


enum class Screen { Playing, GameOver };

class Game {
private:
	Screen screen = Screen::Playing;
	Camera cam;
	GamesEngineeringBase::Window& canvas;

	//GamesEngineeringBase::Image playerImg, itemImg;
	GamesEngineeringBase::Image playerImg, itemImg, backgroundImg, fireImg;
	bool backgroundLoaded = false;

	bool fireLoaded = false;
	FireSeedManager fireSeeds;

	//ProjectilePool projPool;
	ProjectilePool projPool;
	float spawnTimer = 0.f;
	float spawnInterval = 0.4f;
	float runTime = 0.f;
	//Input input;
	Characters player;

	void DrawWorld();
	void DrawBack();
	void SpawnDrop();

public:
	bool quit = false;
	explicit Game(GamesEngineeringBase::Window& window);
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	void Update(float dt);
	void Draw();
};