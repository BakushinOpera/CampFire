#pragma once
#include "GamesEngineeringBase.h" 
#include "Graphics.h"
#include "Input.h"
#include "Characters.h"
#include "Projectile.h"
#include "Camera.h"
#include "Box.h"
#include <algorithm>


enum class Screen{Playing, GameOver};
class Game {
private:
	Screen screen = Screen::Playing;
	Camera cam;
    GamesEngineeringBase::Window& canvas;

	GamesEngineeringBase::Image playerImg, itemImg;
	//ProjectilePool projPool;
    //Input input;
	Characters player;

	void DrawWorld();
	void DrawBack();
public:
	bool quit = false;
	explicit Game(GamesEngineeringBase::Window& window);
    Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	void Update(float dt);
	void Draw();
};