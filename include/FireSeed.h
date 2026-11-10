
#pragma once

#include "Box.h"
#include "GamesEngineeringBase.h"

// The three possible states of one fire seed
enum class FireState
{
	Unlit = 0,
	Burning = 1,
	Blaze = 2
};

class FireSeed
{
public:
	// Sprite sheet dimensions
	static constexpr int CELL_SIZE = 64;
	static constexpr int FRAME_COUNT = 6;
	static constexpr int ANIMATION_FPS = 10;

private:
	// Position in the game world
	float x;
	float y;

	// Current heat, limited to 0-100
	float heat;

	// Current visual/gameplay state
	FireState state;

	// Collision rectangle relative to the seed position
	Box hitbox;

	// Animation information
	float animTime;
	int frame;

	// Update the state according to the heat
	void UpdateState();

public:
	// Create a seed at a world position
	FireSeed(float startX = 0.0f, float startY = 0.0f);

	// Set the seed's world position
	void SetPosition(float newX, float newY);

	// Update animation and other per-frame behaviour
	void Update(float dt);

	// Draw the current animation frame
	void Draw(
		GamesEngineeringBase::Window& window,
		GamesEngineeringBase::Image& image,
		int camX,
		int camY
	);

	// Change the seed's heat
	void ChangeHeat(float amount);

	// Return information needed by other systems
	Box GetBounds() const;
	float GetHeat() const;
	FireState GetState() const;
};
