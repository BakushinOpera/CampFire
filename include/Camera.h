#pragma once
#include "Graphics.h"

class Camera {
private:
	float x, y;			// world position
	int viewW, viewH;	// screen size
public:
	Camera();
	Camera(float x, float y, int viewW, int viewH):
		x(x),
		y(y),
		viewW(viewW),
		viewH(viewH)
	{};
	void SetX(int x_) { x = x_; }
	int getX() { return x; };
	int getY() { return y; };
	int getW() { return viewW; };
	int getH() { return viewH; };
	void setView(int w, int h) { 
		viewW = w; 
		viewH = h; 
	}

};