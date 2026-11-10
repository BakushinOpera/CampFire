#include "Game.h"
#include <string>
#include <iostream>


Game::Game(GamesEngineeringBase::Window& window) :
    canvas(window),
    cam(0, 0, window.getWidth(), window.getHeight())
{ 
    //temporary
    if (playerImg.load("assets/Soldier.png"))
        std::cout << "Failed to load player asset." << std::endl;
    else
        std::cout << "Loaded." << std::endl;

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
    for (int y = 0;y < canvas.getHeight();y++) {
        for (int x = 0;x < canvas.getWidth();x++) {
            canvas.draw(x, y, 111, 111, 111);
        }
    }
}
