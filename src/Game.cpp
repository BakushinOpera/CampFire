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

	//Projectile::LoadAssets();

	//player.SetInput(&input);
	player.SetImg(&playerImg);
}

void Game::Update(float dt) {

	switch (screen)
	{
	case Screen::Playing:
		// Update World -- Game Runing
		//player.Update(dt);
		//projPool.UpdateAll(dt);
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