#pragma once

#include "FireSeed.h"
#include "GamesEngineeringBase.h"

class FireSeedManager
{
public:
	static constexpr int SEED_COUNT = 5;

private:
	// Starting arrangement in world coordinates
	static constexpr float START_X = 320.0f;
	static constexpr float SEED_Y = 670.0f;
	static constexpr float SPACING = 80.0f;

	// Heat changes per second
	static constexpr float UNLIT_COOL = 1.0f;
	static constexpr float BURNING_COOL = 2.0f;
	static constexpr float BLAZE_DECAY = 10.0f;

	static constexpr float SPREAD_BURNING = 3.0f;
	static constexpr float SPREAD_BLAZE = 8.0f;

	// Fixed-size array: exactly five seeds
	FireSeed seeds[SEED_COUNT];

public:
	FireSeedManager();

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
};
