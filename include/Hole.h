#pragma once
#include <SDL.h>
#include <Farmer.h>
#include <iostream>

class Hole {
public:
	Hole() { }
	~Hole() { }

	void init(SDL_Renderer* renderer, int screenW, int screenH) {
		bgrTexture = loadTexture(Config::holeBackgroundPath, renderer);
		farmer.init(renderer, screenW, screenH);
	}
	void draw(SDL_Renderer* renderer) {
		int yOffset = -farmer.getY() % bgrTileSize;
		if (yOffset > 0) {
			yOffset -= bgrTileSize;
		}
		SDL_Rect bgrTileRect = {0, yOffset, bgrTileSize, bgrTileSize};
		for (; bgrTileRect.y < (int)Presenter::SCREEN_H; bgrTileRect.y += bgrTileSize) {
			for (bgrTileRect.x = 0; bgrTileRect.x < (int)Presenter::SCREEN_W;
			     bgrTileRect.x += bgrTileSize) {
				SDL_RenderCopy(renderer, bgrTexture, NULL, &bgrTileRect);
			}
		}
		farmer.draw(renderer);
	}
	void update(const InputManager& inputManager) {
		farmer.update(inputManager);
	}

private:
	SDL_Texture* bgrTexture;
	Farmer farmer;
	int bgrTileSize = 160;
};