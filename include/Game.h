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
	void DrawTXT(const std::string& s, int x, int y, int scale = 1, unsigned char r = 255, unsigned char g = 255, unsigned char b = 255);
	int TextWidth(const std::string& s, int scale = 1);
	void DrawTXTCentered(const std::string& s, int y, int scale = 1, unsigned char r = 255, unsigned char g = 255, unsigned char b = 255);
	void DimScreen(float k);
	void DrawEndScreen(const std::string& title, unsigned char r, unsigned char g, unsigned char b);
	void Draw();
	int MenuNav(int idx, int count, const InputState& in);
	void Restart();
};