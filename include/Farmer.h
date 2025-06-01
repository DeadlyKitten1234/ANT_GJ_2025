#pragma once

#include "Globals.h"
#include "InputManager.h"
#include "ConfigManager.h"
#include <iostream>

#include <SDL.h>

class Farmer {
public:
	enum class State {
		STATIC = 0,
		HANGING = 1,
		JUMPING = 2,
		FALLING = 3,
	};

	float getX() const {
		return pos.x;
	}
	float getY() const {
		return pos.y;
	}
	float& getXRef() {
		return pos.x;
	}
	float& getYRef() {
		return pos.y;
	}
	bool isHanging() {
		return hanging;
	}

	void init(SDL_Renderer* renderer, int screenW, int screenH) {
		texture = loadTexture("textures\\farmer", renderer);
		size.x = 2;
		size.y = 4;
		//rect.w = 96;
		//rect.h = 144;
		//rect.x = (screenW - rect.w) / 2;
		//rect.y = (screenH - rect.y) / 2;
	}

	void update(const InputManager& input) {
		if (hanging) {
			if (input.space) {
				velocityY = -0.45;
				hanging = false;
			}
		} 
		if (input.rightArrow) {
			pos.x += 0.2;
			right = true;
			hanging = false;
		}
		if (input.leftArrow) {
			pos.x -= 0.2;
			right = false;
			hanging = false;
		}
		if (!hanging) {
			velocityY += 0.02;
			pos.y += velocityY;
		}
	}
	void draw(SDL_Renderer* renderer, int tileSize) {
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
		std::cout << pos.y << '\n';
		SDL_Rect srcRect = getSrcRect(state);
		SDL_Rect rect = {0, 0, 64, 96};
		rect.x = pos.x * tileSize - rect.w / 2;
		rect.y = (Presenter::SCREEN_H - rect.h) / 2 + rect.h / 2;
		SDL_RenderCopyEx(renderer, texture, &srcRect, &rect,
			0, NULL, right ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);
	}

private:
	SDL_Texture* texture;

	float2 pos;
	float2 size;
	float velocityY;
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
