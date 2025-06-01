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
		Config::readLevel(Presenter::SCREEN_W, grips, farmer.getXRef(),
		                  farmer.getYRef(), finishY, bgrTileSize);
		farmer.init(renderer, screenW, screenH);
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
		farmer.draw(renderer);
	}
	void update(const InputManager& inputManager) {
		farmer.update(inputManager);
	}

private:
	SDL_Texture* bgrTexture;
	SDL_Texture* floorTexture;
	Farmer farmer;
	int bgrTileSize;
	int finishY;

	std::vector<SDL_Rect> grips;
};