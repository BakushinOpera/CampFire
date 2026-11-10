#include <iostream>
#include "GamesEngineeringBase.h" // Include the GamesEngineeringBase header
#include "Graphics.h"
#include "Game.h"

int main() {

    // Create a canvas window with dimensions 1024x768 and title “Tiles"
    GamesEngineeringBase::Window canvas;
    canvas.create(720, 1024, "Camp Fire");
    bool running = true; // Variable to control the main loop's running state.

    GamesEngineeringBase::Timer timer;

    // use new 
    Game* game = new Game(canvas);
    while (running)
    {
        canvas.checkInput();
        // Render
        // Clear the window for the next frame rendering
        game->Update(timer.dt());
        game->Draw();
        if (game->quit) break;

    }
    delete game;
    return 0;
}