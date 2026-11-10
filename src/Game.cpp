#include "Game.h"
#include <iostream>
#include <string>


Game::Game(GamesEngineeringBase::Window& window) :
	canvas(window),
	cam(0, 0, window.getWidth(), window.getHeight())
{
	//Added
	backgroundLoaded = backgroundImg.load(
		"assets/background/ForestCampsite.png"
	);

	if (!backgroundLoaded)
		std::cout << "Failed to load background asset." << std::endl;
	else
		std::cout << "Background loaded successfully." << std::endl;


	// Load player image
	if (!playerImg.load("assets/Soldier.png"))
		std::cout << "Failed to load player asset." << std::endl;
	else
		std::cout << "Player loaded successfully." << std::endl;

	Projectile::LoadAssets();
	Projectile::killY = canvas.getHeight();
	std::srand((unsigned)std::time(nullptr));

	//player.SetInput(&input);
	player.SetImg(&playerImg);
}

void Game::Update(float dt) {

	switch (screen)
	{
	case Screen::Playing:
		// Update World -- Game Runing
		spawnTimer += dt;
		if (spawnTimer >= spawnInterval) {
			spawnTimer -= spawnInterval;
			SpawnDrop();
		}
		//player.Update(dt);
		projPool.UpdateAll(dt);
		//projPool.CheckCollide(player);

		break;
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
	//temporary
	DrawBack();

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

		return;
	}

	// Fallback if the background fails to load
	for (int y = 0; y < canvas.getHeight(); y++) {
		for (int x = 0; x < canvas.getWidth(); x++) {
			canvas.draw(x, y, 111, 111, 111);
		}
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