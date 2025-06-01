#pragma once
#include <Farmer.h>
#include <SDL.h>
#include <iostream>
#include <vector>
#include <cmath>

class Hole {
public:
	Hole() { }
	~Hole() { }

	void init(SDL_Renderer* renderer, int screenW, int screenH) {
		bgrTexture = loadTexture(Config::holeBackgroundPath, renderer);
		floorTexture = loadTexture(Config::holeFloorPath, renderer);
		gripTexture = loadTexture(Config::gripPath, renderer);
		farmer.init(renderer, screenW, screenH);
		Config::readLevel(grips, farmer.getXRef(),
		                  farmer.getYRef(), fieldW, fieldH, tileSize);
		lastGripY = farmer.getY();
	}
	void draw(SDL_Renderer* renderer) {
		for (int x = 0; x < fieldW; x++) {
			for (int y = -15; y < fieldH; y++) {
				SDL_Rect rect = {
				    x * tileSize,
				    (y - farmer.getY()) * tileSize + Presenter::SCREEN_H / 2,
					tileSize,
					tileSize
				};
				SDL_RenderCopy(renderer, bgrTexture, NULL, &rect);
			}
		}
		for (SDL_Rect gr : grips) {
			SDL_Rect newRect = gr;
			newRect.y += Presenter::SCREEN_H / 2 - farmer.getY() * tileSize;
			Presenter::drawObject(gripTexture, &newRect);
		}
		farmer.draw(renderer, tileSize);
	}
	void update(const InputManager& inputManager) {
		if (farmer.isHanging()) {
			lastGripY = farmer.getY();
		} else {
			if (farmer.getY() - lastGripY >= deathYDif) {
				return;
			}
		}
		farmer.update(inputManager);
	}

private:
	SDL_Texture* bgrTexture;
	SDL_Texture* gripTexture;
	SDL_Texture* floorTexture;
	Farmer farmer;
	int fieldW;
	int fieldH;
	int tileSize;
	float deathYDif = 3.9;
	float lastGripY;

	std::vector<SDL_Rect> grips;
};