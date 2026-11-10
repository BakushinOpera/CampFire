
#include "FireSeedManager.h"

// Create and position the five seeds
FireSeedManager::FireSeedManager()
{
	for (int i = 0; i < SEED_COUNT; i++)
	{
		float seedX = START_X + i * SPACING;

		seeds[i].SetPosition(seedX, SEED_Y);
	}

	// Start the middle seed with enough heat to burn
	seeds[SEED_COUNT / 2].ChangeHeat(50.0f);
}

// Update all seeds and spread heat between neighbours
void FireSeedManager::Update(float dt)
{
	// Store heat changes before applying them
	float heatChanges[SEED_COUNT] = {};

	// First pass: calculate cooling and heat spreading
	for (int i = 0; i < SEED_COUNT; i++)
	{
		// Natural cooling depends on the current state
		switch (seeds[i].GetState())
		{
		case FireState::Unlit:
			heatChanges[i] -= UNLIT_COOL;
			break;

		case FireState::Burning:
			heatChanges[i] -= BURNING_COOL;
			break;

		case FireState::Blaze:
			heatChanges[i] -= BLAZE_DECAY;
			break;
		}

		// Check the left neighbour
		if (i > 0)
		{
			if (seeds[i - 1].GetState() == FireState::Burning)
			{
				heatChanges[i] += SPREAD_BURNING;
			}
			else if (seeds[i - 1].GetState() == FireState::Blaze)
			{
				heatChanges[i] += SPREAD_BLAZE;
			}
		}

		// Check the right neighbour
		if (i < SEED_COUNT - 1)
		{
			if (seeds[i + 1].GetState() == FireState::Burning)
			{
				heatChanges[i] += SPREAD_BURNING;
			}
			else if (seeds[i + 1].GetState() == FireState::Blaze)
			{
				heatChanges[i] += SPREAD_BLAZE;
			}
		}
	}

	// Second pass: apply the changes and update animation
	for (int i = 0; i < SEED_COUNT; i++)
	{
		seeds[i].ChangeHeat(heatChanges[i] * dt);
		seeds[i].Update(dt);
	}
}

// Draw all five seeds
void FireSeedManager::Draw(
	GamesEngineeringBase::Window& window,
	GamesEngineeringBase::Image& image,
	int camX,
	int camY)
{
	for (int i = 0; i < SEED_COUNT; i++)
	{
		seeds[i].Draw(window, image, camX, camY);
	}
}

// Return the number of seeds
int FireSeedManager::Count() const
{
	return SEED_COUNT;
}

// Return a reference to a particular seed
FireSeed& FireSeedManager::Seed(int index)
{
	return seeds[index];
}

// Check whether every seed is unlit
bool FireSeedManager::AllUnlit() const
{
	for (int i = 0; i < SEED_COUNT; i++)
	{
		if (seeds[i].GetState() != FireState::Unlit)
		{
			return false;
		}
	}

	return true;
}
