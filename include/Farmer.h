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
		texture = loadTexture("textures\\farmer", renderer);
		rect.w = 96;
		rect.h = 144;
		rect.x = (screenW - rect.w) / 2;
		rect.y = (screenH - rect.y) / 2;
	}

	void update(const InputManager& input) {
		if (input.rightArrow) {
			rect.x += 10;
			right = true;
		}
		if (input.leftArrow) {
			rect.x -= 10;
			right = false;
		}
		if (hanging) {
			if (input.space) {
				velocityY = -15;
			}
		} else {
			velocityY += 0.5;
			y += velocityY;
		}
	}
	void draw(SDL_Renderer* renderer) {
		State state;
		if (hanging) {
			state = State::HANGING;
		} else {
			if (velocityY > 0) {
				state = State::FALLING;
			} else {
				state = State::JUMPING;
			}
		}
		SDL_Rect srcRect = getSrcRect(state);
		SDL_RenderCopyEx(renderer, texture, &srcRect, &rect,
			0, NULL, right ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);
	}

private:
	SDL_Texture* texture;

	double velocityY;
	double y = 0;
	SDL_Rect rect;
	bool hanging = true;
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
		return {-1, -1, 1, 1};
	}
};
