#include "Game.h"
#include <iostream>
#include <string>


Game::Game(GamesEngineeringBase::Window& window) :
    canvas(window),
    cam(0, 0, window.getWidth(), window.getHeight())
{ 
    //temporary
    if (umbrellaImg.load("assets/Umbrella.png"))
        std::cout << "Failed to load player asset." << std::endl;
    else
        std::cout << "Loaded." << std::endl;
      
    ackgroundLoaded = backgroundImg.load("assets/background/ForestCampsite.png");
    if (!backgroundLoaded)
		  std::cout << "Failed to load background asset." << std::endl;
	  else
		  std::cout << "Background loaded successfully." << std::endl;

      
    //Projectile::LoadAssets();

    player.SetImg(&umbrellaImg);

    float umbrellaWidth = 120.0f;
    player.x = (canvas.getWidth() - umbrellaWidth) / 2.0f;
    player.y = canvas.getHeight() - 220.0f; // <--- Sits right above fire zone
}

void Game::Update(float dt) {

    switch (screen)
    {
    case Screen::Playing:
    {
        // Update World -- Game Runing
        //player.Update(dt);
        //projPool.UpdateAll(dt);
        //projPool.CheckCollide(player);

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
	//temporary
	DrawBack();

	player.Draw(canvas, cam.getX(), cam.getY());
}

void Game::DrawBack() {
//     for (int y = 0;y < canvas.getHeight();y++) {
//         for (int x = 0;x < canvas.getWidth();x++) {
//             canvas.draw(x, y, 45, 55, 75);
//         }
//     }

	if (backgroundLoaded) {
		Graphics::DrawSubImg(
			canvas,
			backgroundImg,
			0, 0,
			1024, 768,
			0, 0
		);

	// Fallback if the background fails to load
	for (int y = 0; y < canvas.getHeight(); y++) {
		for (int x = 0; x < canvas.getWidth(); x++) {
			canvas.draw(x, y, 111, 111, 111);
		}
	}
}
