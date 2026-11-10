#pragma once

class Box {
public:
	int x, y, w, h;
	static bool Overlap(const Box& a, const Box& b) {
		return a.x < b.x + b.w && a.x + a.w > b.x &&
			a.y < b.y + b.h && a.y + a.h > b.y;
	}
	static Box OffsetBox(const Box& local, float x_, float y_) {
		return { (int)x_ + local.x, (int)y_ + local.y, local.w, local.h };
	}
};