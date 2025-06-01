#pragma once

#include <SDL.h>
#include "Globals.h"

class InputManager {
public:
	InputManager();
	~InputManager();
	
	bool mouseIsPressed;
	bool mouseReleased;
	bool mouseIsHeld;
	bool mouseMoved;
	bool keyReleased;
	bool quit;
	int2 mouseCoord;

	void getInput();
};