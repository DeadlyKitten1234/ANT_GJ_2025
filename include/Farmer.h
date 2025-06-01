#pragma once

#include "Globals.h"
#include "InputManager.h"
#include "ConfigManager.h"

#include <SDL.h>

class Farmer {
public:
	enum class State {
		STATIC = 0,
		HANGING = 1,
		JUMPING = 2,
		FALLING = 3,
	};

	void init(SDL_Renderer* renderer, int screenW, int screenH) {
		texture = loadTexture(Config::farmerTexturePath, renderer);
		rect.w = 32;
		rect.h = 48;
		rect.x = (screenW - rect.w) / 2;
		rect.y = (screenH - rect.y) / 2;
	}

	void update(const InputManager& input) {
		velocityY += 1;

		if (input.rightArrow) {
			rect.x += 5;
		}
		if (input.leftArrow) {
			rect.x -= 5;
		}
		if (input.space) {
			velocityY = -5;
		}

		y += velocityY;
	}
	void draw(SDL_Renderer* renderer) {
		SDL_Rect srcRect = getSrcRect(state);
		SDL_RenderCopyEx(renderer, texture, &srcRect, &rect,
			0, NULL, right ? SDL_FLIP_NONE : SDL_FLIP_VERTICAL);
	}

private:
	SDL_Texture* texture;

	int velocityY;
	int y = 0;
	SDL_Rect rect;
	State state = State::STATIC;
	bool right = true;

	static SDL_Rect getSrcRect(State state) {
		switch (state) {
		case State::STATIC:
			return {0, 0, 32, 48};
		case State::HANGING:
			return {0, 48, 32, 48};
		case State::JUMPING:
			return {32, 0, 32, 48};
		case State::FALLING:
			return {32, 48, 32, 48};
		}
		return {-1,-1,1,1};
	}
};
