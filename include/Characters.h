#pragma once
#include "GamesEngineeringBase.h"
#include "Input.h"
#include "Box.h"
#include "Graphics.h"


class Characters {
public:
	float x = 0, y=0, hp=200;
	Box hurtbox = { 0,10,120,50 };
	GamesEngineeringBase::Image* cImg;


	const Input* input = nullptr;

	Characters();

	void SetImg(GamesEngineeringBase::Image* img) { cImg = img; }
	void SetInput(const Input* in) { input = in; };
	void Update(float dt) {

	}

	void Draw(GamesEngineeringBase::Window& window, int camX, int camY) {
		int srcWidth = cImg->width;
		int srcHeight = cImg->height;

		int drawWidth = srcWidth;
		int drawHeight = srcHeight;

		Graphics::DrawSubImg(window, *cImg, 0,0, srcWidth, srcHeight, (int)x - camX, (int)y - camY);

	}

	//gives the exact world space bounding box of the umbrella to help whoever is adding the droplets
	Box GetWorldBox() const {
		return Box::OffsetBox(hurtbox, x, y);
	}
	
	void TakeDmg(float dmg) {
		hp -= dmg;
	}
};