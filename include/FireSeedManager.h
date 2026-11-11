#pragma once

#include "FireSeed.h"
#include "GamesEngineeringBase.h"

class FireSeedManager
{
public:
	static constexpr int SEED_COUNT = 5;

private:
	// Layout (pixels). Everything is worked out from the window size,
	// so changing the window size in main.cpp does not break the layout.
	static constexpr float SPACING = 120.0f;       // distance between seed left edges
	static constexpr float BOTTOM_MARGIN = 72.0f;  // gap between seed bottom and window bottom

	// Heat changes per second
	static constexpr float UNLIT_COOL = 1.0f;
	static constexpr float BURNING_COOL = 2.0f;
	static constexpr float BLAZE_DECAY = 10.0f;

	static constexpr float SPREAD_BURNING = 3.0f;
	static constexpr float SPREAD_BLAZE = 8.0f;

	// Fixed-size array: exactly five seeds
	FireSeed seeds[SEED_COUNT];

	float topY;   // world Y of the top edge of the seeds

public:
	// screenW / screenH = window size. The seeds are centred horizontally
	// and sit near the bottom of the window.
	FireSeedManager(int screenW = 1024, int screenH = 720);

	void Update(float dt);

	void Draw(
		GamesEngineeringBase::Window& window,
		GamesEngineeringBase::Image& image,
		int camX,
		int camY
	);

	int Count() const;

	FireSeed& Seed(int index);

	bool AllUnlit() const;

	// Top edge of the seed sprites, so other objects (the umbrella)
	// can be placed relative to the fire.
	float TopY() const;

	bool AllLit();
};
