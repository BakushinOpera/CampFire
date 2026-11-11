#pragma once
#include "GamesEngineeringBase.h" 

struct Button {
	bool now = false, pressed = false, released = false;

	void UpdateButton(bool down) {
		pressed = down && !now;
		released = !down && now;
		now = down;
	}
};
struct InputState {
	int moveX = 0, moveY = 0;
	bool moving = false;

	// UI
	Button esc, enter, uiUp, uiDown, uiLeft, uiRight;
};
class Input {
private:
	InputState iState;
public:
	void Update(GamesEngineeringBase::Window& window) {
		iState.moveX = 0;
		if (window.keyPressed('D')) iState.moveX += 1;
		if (window.keyPressed('A')) iState.moveX -= 1;
		iState.uiUp.UpdateButton(window.keyPressed('W'));
		iState.uiDown.UpdateButton(window.keyPressed('S'));
		iState.enter.UpdateButton(window.keyPressed(VK_RETURN));
		iState.esc.UpdateButton(window.keyPressed(VK_ESCAPE));
	}
	const InputState& GetState() const { return iState; };
};