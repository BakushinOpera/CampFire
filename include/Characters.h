#pragma once
#include "GamesEngineeringBase.h"
#include "Input.h"
#include "Box.h"
#include "Graphics.h"


class Characters {
public:
	float x = 0, y=0, hp=200;
	Box hurtbox = { 45,45,15,15 };
	GamesEngineeringBase::Image* cImg;


	const Input* input = nullptr;

	Characters();

	void SetImg(GamesEngineeringBase::Image* img) { cImg = img; }
	void SetInput(const Input* in) { input = in; };
	void Update(float dt) {

	}

	void Draw(GamesEngineeringBase::Window& window, int camX, int camY) {
		int IMGwidth = 100;
		int IMGheight = 100;
		Graphics::DrawSubImg(window, *cImg, 0,0, IMGwidth, IMGheight, x - camX, y - camY);

	}
	
	void TakeDmg(float dmg) {
		hp -= dmg;
	}
};