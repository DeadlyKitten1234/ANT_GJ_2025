#pragma once
#include <Farmer.h>
#include <SDL.h>
#include <iostream>
#include <vector>

class Hole {
public:
	Hole() { }
	~Hole() { }

	void init(SDL_Renderer* renderer, int screenW, int screenH) {
		bgrTexture = loadTexture(Config::holeBackgroundPath, renderer);
		floorTexture = loadTexture(Config::holeFloorPath, renderer);
		gripTexture = loadTexture(Config::gripPath, renderer);
		Config::readLevel(Presenter::SCREEN_W, grips, farmer.getXRef(),
		                  farmer.getYRef(), finishY, bgrTileSize);
		farmer.init(renderer, screenW, screenH);
		lastGripY = farmer.getY();
	}
	void draw(SDL_Renderer* renderer) {
		int yOffset = -farmer.getY() % bgrTileSize;
		if (yOffset > 0) {
			yOffset -= bgrTileSize;
		}
		SDL_Rect bgrTileRect = {0, yOffset, bgrTileSize, bgrTileSize};
		for (; bgrTileRect.y < (int)Presenter::SCREEN_H;
		     bgrTileRect.y += bgrTileSize) {
			for (bgrTileRect.x = 0; bgrTileRect.x < (int)Presenter::SCREEN_W;
			     bgrTileRect.x += bgrTileSize) {
				SDL_RenderCopy(renderer,
				               farmer.getY() + bgrTileRect.y >= finishY ? floorTexture : bgrTexture,
				               NULL, &bgrTileRect);
			}
		}
		for (SDL_Rect gr : grips) {
			if (!(gr.y + gr.h - farmer.getY() < 0 || gr.y - farmer.getY() > Presenter::SCREEN_H)) {
				SDL_Rect newRect = gr;
				newRect.y -= farmer.getY();
				Presenter::drawObject(gripTexture, &newRect);
			}
		}
		farmer.draw(renderer);
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
	int bgrTileSize;
	int finishY;
	int lastGripY;
	int deathYDif = 300;

	std::vector<SDL_Rect> grips;
};