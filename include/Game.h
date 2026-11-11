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


enum class Screen { Menu, Playing, GameOver, Win };

class Game {
private:
	Screen screen = Screen::Menu;
	Camera cam;
	GamesEngineeringBase::Window& canvas;

	GamesEngineeringBase::Image umbrellaImg, itemImg, backgroundImg, fireImg, fontImg;
	bool backgroundLoaded = false;

	bool fireLoaded = false;
	FireSeedManager fireSeeds;

	ProjectilePool projPool;
	float spawnTimer = 0.f;
	float spawnInterval = 0.4f;
	float runTime = 0.f;

	int menuIdx = 0;
	Input input;

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
	void DrawTXT(std::string s, int x, int y);
	void Draw();
	int MenuNav(int idx, int count, const InputState& in);
	void Restart();
};