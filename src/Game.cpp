#include "Game.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime> 

Game::Game(GamesEngineeringBase::Window& window) :
    canvas(window),
    cam(0, 0, window.getWidth(), window.getHeight())
{ 
    if (!umbrellaImg.load("assets/umbrella.png"))
        std::cout << "Failed to load player asset." << std::endl;
    else
        std::cout << "Loaded." << std::endl;
      
    backgroundLoaded = backgroundImg.load("assets/background/ForestCampsite.png");
    if (!backgroundLoaded)
		std::cout << "Failed to load background asset." << std::endl;
	else
		std::cout << "Background loaded successfully." << std::endl;
      
    // Load the fire seed sprite sheet
	fireLoaded = fireImg.load("assets/fire/fire_seed_sheet_64.png");

	if (!fireLoaded)
	{
		std::cout << "Failed to load fire seed sprite sheet." << std::endl;
	}
	else
	{
		std::cout << "Fire seed sprite sheet loaded successfully." << std::endl;
	}

    player.SetImg(&umbrellaImg);

    float umbrellaWidth = 120.0f;
    player.x = (canvas.getWidth() - umbrellaWidth) / 2.0f;
    player.y = canvas.getHeight() - 220.0f; // <--- Sits right above fire zone

	// Falling objects
	Projectile::LoadAssets();
	Projectile::killY = canvas.getHeight();
	std::srand((unsigned)std::time(nullptr));
}

void Game::Update(float dt) {

    switch (screen)
    {
    case Screen::Playing:
    {
		// Falling objects
		runTime += dt;
		spawnInterval = std::max(0.1f, 0.4f - runTime * 0.004f); // Decrease spawn interval over time
		Projectile::speedScale = std::min(2.0f, 1.0f + runTime * 0.01f); // Increase falling speed over time
		spawnTimer += dt;
		if (spawnTimer >= spawnInterval) {
			spawnTimer -= spawnInterval;
			SpawnDrop();
		}
		projPool.UpdateAll(dt);
		projPool.CheckCollide(player);

        //Umbrella movement speed and controls
        float moveSpeed = 600.0f;
        float umbrellaWidth = 120.0f;

        if (canvas.keyPressed('A') || canvas.keyPressed(VK_LEFT)) {
            player.x -= moveSpeed * dt;
        }
        if (canvas.keyPressed('D') || canvas.keyPressed(VK_RIGHT)) {
            player.x += moveSpeed * dt;
        }

        if (player.x < 0.0f) {
            player.x = 0.0f;
        }
        if (player.x > canvas.getWidth() - umbrellaWidth) {
            player.x = canvas.getWidth() - umbrellaWidth;
        }

        break;
    }
    case Screen::GameOver:
        break;
    default:
        break;
    }      
}

void Game::Draw() {
	canvas.clear();

	switch (screen)
	{
	case Screen::Playing:
		DrawWorld();
		break;
	case Screen::GameOver: {
		DrawBack();
		break;
	}
	default:
		break;
	}
	canvas.present();
}

void Game::DrawWorld() {
	DrawBack();
	if (fireLoaded)
	{
		fireSeeds.Draw(canvas, fireImg, cam.getX(), cam.getY());
	}
	player.Draw(canvas, cam.getX(), cam.getY());
	projPool.DrawAll(canvas, cam.getX(), cam.getY());
}

void Game::DrawBack() {
    if (backgroundLoaded) {
        Graphics::DrawSubImg(
            canvas,
            backgroundImg,
            0, 0,
            1024, 768,
            0, 0
        );
    }

}

void Game::SpawnDrop() {
	// Select the type based on probability: Rain 75%, Hail 10%, Branch 15%
	int r = rand() % 100;
	DropType t = (r < 75) ? Rain : (r < 85) ? Hail : Branch;
	const projectileType* dropType = &Projectile::projTypes[t];

	int w = dropType->img->width;
	int h = dropType->img->height;
	float x = w / 2.0f + rand() % (canvas.getWidth() - w);
	float y = -h / 2.0f; 
	projPool.create(x, y, 0.0f, 1.0f, dropType);
}