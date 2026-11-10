#pragma once
#include "GamesEngineeringBase.h"
#include "Graphics.h"
#include "Box.h"

class TileMap {
public:
	
	void Draw(GamesEngineeringBase::Window& window, int camX, int camY, int viewW, int viewH);
};