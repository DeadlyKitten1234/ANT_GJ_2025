#include "InputManager.h"
#include "SDL_scancode.h"

InputManager::InputManager() { quit = false; }

InputManager::~InputManager() {}

void InputManager::getInput() {
    mouseIsPressed = false;
    mouseMoved = false;
    mouseReleased = false;
    keyReleased = false;

	rightArrow = false;
	leftArrow = false;
	downArrow = false;
	space = false;

    SDL_Event event;

	key = SDL_GetKeyboardState(NULL);
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            quit = true;
            break;

        case SDL_MOUSEMOTION:
            SDL_GetMouseState(&(mouseCoord.x), &(mouseCoord.y));
            mouseMoved = true;
            break;

        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT) {
                mouseIsPressed = true;
                mouseIsHeld = true;
            }
            break;
            
        case SDL_MOUSEBUTTONUP:
            if (event.button.button == SDL_BUTTON_LEFT) {
                mouseReleased = true;
                mouseIsHeld = false;
            }
            break;
        case SDL_KEYUP:
            keyReleased = true;
            break;
        }
    }

	if (key[SDL_SCANCODE_RIGHT]) {
		rightArrow = true;
	}
	if (key[SDL_SCANCODE_LEFT]) {
		leftArrow = true;
	}
    if (key[SDL_SCANCODE_DOWN]) {
        downArrow = true;
	}
	if (key[SDL_SCANCODE_SPACE]) {
		space = true;
	}
}
