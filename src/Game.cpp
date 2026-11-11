#include "Game.h"
#include <cstdlib>
#include <ctime> 
#include <iostream>
#include <string>

Game::Game(GamesEngineeringBase::Window& window) :
	canvas(window),
	cam(0, 0, window.getWidth(), window.getHeight()),
	// Fire seeds are laid out from the window size
	fireSeeds((int)window.getWidth(), (int)window.getHeight())
{
	menuIdx = 0;
	if (!umbrellaImg.load("assets/umbrella.png"))
		std::cout << "Failed to load player asset." << std::endl;
	else
		std::cout << "Loaded." << std::endl;

	// New background, drawn at 1024x720 and scaled to the window if the sizes differ
	backgroundLoaded = backgroundImg.load("assets/background/night_forest.png");
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

	if(!fontImg.load("assets/font.png")) std::cout << "Failed to load font sprite sheet." << std::endl;
	else std::cout << "Font image sprite sheet loaded successfully." << std::endl;


	player.SetImg(&umbrellaImg);

	float umbrellaWidth = 120.0f;
	player.x = (canvas.getWidth() - umbrellaWidth) / 2.0f;

	// The umbrella floats above the fire seeds so it can shield them from the rain:
	// seed top edge, minus the umbrella height, minus a 40 px gap.
	player.y = fireSeeds.TopY() - (float)umbrellaImg.height - 40.0f;

	// Falling objects
	Projectile::LoadAssets();
	Projectile::killY = canvas.getHeight();
	std::srand((unsigned)std::time(nullptr));
}

void Game::Update(float dt) {
	input.Update(canvas);
	const InputState& in = input.GetState();
	// ESC closes the game
	if (in.esc.pressed) {
		quit = true;
	}

	switch (screen)
	{
	case Screen::Menu: {
		menuIdx = MenuNav(menuIdx, 2, in);
		if (in.enter.pressed) {
			if (menuIdx == 0) screen = Screen::Playing;
			else quit = true;
		}
		break;
	}
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
		projPool.CheckFireHit(fireSeeds);

		// Fire seeds: heat spreading, cooling and sprite animation
		fireSeeds.Update(dt);

		if (fireSeeds.AllUnlit())
			screen = Screen::GameOver;

		// TEMP test controls until rain/branch hits change the seeds' heat.
		// Hold 1-5 to heat that seed, hold Shift + 1-5 to cool it. Delete this block later.
		{
			float rate = canvas.keyPressed(VK_SHIFT) ? -60.0f : 60.0f;
			for (int i = 0; i < fireSeeds.Count(); i++)
			{
				if (canvas.keyPressed('1' + i))
					fireSeeds.Seed(i).ChangeHeat(rate * dt);
			}
		}

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

		if (fireSeeds.AllLit()) screen = Screen::Win;

		break;
	}
	case Screen::GameOver: {
		menuIdx = MenuNav(menuIdx, 2, in);
		if (in.enter.pressed) {
			if (menuIdx == 0) screen = Screen::Playing;
			else quit = true;
		}
		break;
	}
	case Screen::Win: {
		menuIdx = MenuNav(menuIdx, 2, in);
		if (in.enter.pressed) {
			if (menuIdx == 0) screen = Screen::Playing;
			else quit = true;
		}
		break;
	}
	default:
		break;
	}
}
int  Game::MenuNav(int idx, int count, const InputState& in) {
	if (in.uiDown.pressed) idx = (idx + 1) % count;
	if (in.uiUp.pressed) idx = (idx - 1 + count) % count;
	return idx;
}

void Game::Draw() {
	canvas.clear();

	switch (screen)
	{
	case Screen::Menu: {
		DrawBack();
		const std::string options[] = { "Start", "Exit" };
		for (int i = 0;i < 2;i++) {
			int x = 500;
			int y = 200 + i * 50; // the top position and the distance between
			if (i == menuIdx) DrawTXT(">", x - 32, y);
			DrawTXT(options[i], x, y);
		}
		break;
	}
	case Screen::Playing:
		DrawWorld();
		break;
	case Screen::GameOver: {
		DrawBack();
		DrawTXT("Game Over !", 500, 200);
		const std::string options[] = { "Restart", "Exit" };
		for (int i = 0;i < 2;i++) {
			int x = 500;
			int y = 300 + i * 50; // the top position and the distance between
			if (i == menuIdx) DrawTXT(">", x - 32, y);
			DrawTXT(options[i], x, y);
		}
		break;
	}
	case Screen::Win: {
		DrawBack();
		DrawTXT("You Win !", 500, 200);
		const std::string options[] = { "Restart", "Exit" };
		for (int i = 0;i < 2;i++) {
			int x = 500;
			int y = 300 + i * 50; // the top position and the distance between
			if (i == menuIdx) DrawTXT(">", x - 32, y);
			DrawTXT(options[i], x, y);
		}
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
	const int W = (int)canvas.getWidth();
	const int H = (int)canvas.getHeight();

	if (!backgroundLoaded) {
		// Plain dark fallback so the window is never left black and empty
		for (int y = 0; y < H; y++)
			for (int x = 0; x < W; x++)
				canvas.draw(x, y, 20, 24, 42);
		return;
	}

	const int iw = (int)backgroundImg.width;
	const int ih = (int)backgroundImg.height;

	// Same size as the window: straight copy
	if (iw == W && ih == H) {
		Graphics::DrawSubImg(canvas, backgroundImg, 0, 0, W, H, 0, 0);
		return;
	}

	// Different size: stretch to fill the window (nearest-neighbour keeps the pixels crisp)
	for (int y = 0; y < H; y++) {
		const int sy = y * ih / H;
		for (int x = 0; x < W; x++) {
			const int sx = x * iw / W;
			canvas.draw(x, y, backgroundImg.atUnchecked(sx, sy));
		}
	}
}

void Game::DrawTXT(std::string s, int x, int y) {
	int first = 32, cols = 15, rows = 8;
	int sw = fontImg.width / cols;
	int sh = fontImg.height / rows;

	for (char c : s) {
		int idx = c - first;
		if (idx >= 0 && idx < cols * rows)
			Graphics::DrawSubImg(canvas, fontImg, (idx % cols) * sw, (idx / cols) * sh, sw, sh, x, y);
		x += sw;
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
