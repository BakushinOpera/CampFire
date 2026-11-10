#pragma once
#include "GamesEngineeringBase.h" 

class Graphics {
public:
	//Debug
	static void DrawBox(GamesEngineeringBase::Window& window, int x, int y, int w, int h);

	static void DrawSubImg(GamesEngineeringBase::Window& window, GamesEngineeringBase::Image& image, int srcX, int srcY, int w, int h, int desX, int desY);

};