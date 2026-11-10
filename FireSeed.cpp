
#include "FireSeed.h"
#include "Graphics.h"

// Create a fire seed at the supplied world position
FireSeed::FireSeed(float startX, float startY)
	: x(startX),
	y(startY),
	heat(0.0f),
	state(FireState::Unlit),
	hitbox{ 0, 0, CELL_SIZE, CELL_SIZE },
	animTime(0.0f),
	frame(0)
{
}

// Set the seed's position in the game world
void FireSeed::SetPosition(float newX, float newY)
{
	x = newX;
	y = newY;
}

// Update the state using hysteresis
void FireSeed::UpdateState()
{
	switch (state)
	{
	case FireState::Unlit:
		if (heat >= 30.0f)
		{
			state = FireState::Burning;
		}
		break;

	case FireState::Burning:
		if (heat >= 100.0f)
		{
			state = FireState::Blaze;
		}
		else if (heat < 20.0f)
		{
			state = FireState::Unlit;
		}
		break;

	case FireState::Blaze:
		if (heat < 70.0f)
		{
			state = FireState::Burning;
		}
		break;
	}
}

// Advance the animation
void FireSeed::Update(float dt)
{
	animTime += dt;

	// Calculate the current animation frame
	frame = static_cast<int>(animTime * ANIMATION_FPS) % FRAME_COUNT;
}

// Draw the current animation frame
void FireSeed::Draw(
	GamesEngineeringBase::Window& window,
	GamesEngineeringBase::Image& image,
	int camX,
	int camY)
{
	// Convert world coordinates into screen coordinates
	int screenX = static_cast<int>(x) - camX;
	int screenY = static_cast<int>(y) - camY;

	// Select the sprite sheet row from the current state
	int row = static_cast<int>(state);

	// Calculate the source position in the sprite sheet
	int sourceX = frame * CELL_SIZE;
	int sourceY = row * CELL_SIZE;

	Graphics::DrawSubImg(
		window,
		image,
		sourceX,
		sourceY,
		CELL_SIZE,
		CELL_SIZE,
		screenX,
		screenY
	);
}

// Increase or decrease the seed's heat
void FireSeed::ChangeHeat(float amount)
{
	heat += amount;

	// Keep heat within the valid range
	if (heat < 0.0f)
	{
		heat = 0.0f;
	}

	if (heat > 100.0f)
	{
		heat = 100.0f;
	}

	// Recalculate the fire state
	UpdateState();
}

// Return the collision rectangle in world coordinates
Box FireSeed::GetBounds() const
{
	return Box::OffsetBox(hitbox, x, y);
}

// Return the current heat
float FireSeed::GetHeat() const
{
	return heat;
}

// Return the current state
FireState FireSeed::GetState() const
{
	return state;
}
