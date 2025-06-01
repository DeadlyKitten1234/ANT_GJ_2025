#pragma once

#include "Globals.h"
#include "ConfigManager.h"

#include <iostream>
#include <SDL.h>

class HealthBar {
public:
	static constexpr int HEARTS_COUNT = 5;

	int getLives() {
		return lives;
	}
	void decreaseLives() {
		lives--;
	}
	void setLives(int x) {
		lives = x;
	}

	void init(SDL_Renderer* renderer) {
		heartTexture = loadTexture(Config::heart, renderer);
		brokenHeartTexture = loadTexture(Config::heartBroken, renderer);
	}
	void render(SDL_Renderer* renderer) {
		for (int i = 0; i < lives; i++) {
			SDL_RenderCopy(renderer, heartTexture, NULL, &rect);
			rect.x += rect.w;
		}
		for (int i = lives; i < HEARTS_COUNT; i++) {
			SDL_RenderCopy(renderer, brokenHeartTexture, NULL, &rect);
			rect.x += rect.w;
		}
		rect.x = 0;
	}

private:
	SDL_Texture* heartTexture;
	SDL_Texture* brokenHeartTexture;

	SDL_Rect rect = {0, 0, 50, 50};

	int lives = HEARTS_COUNT;
};