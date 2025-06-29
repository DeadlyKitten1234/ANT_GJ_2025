#pragma once
#include <SDL.h>
#include <vector>


class Cinematic {
public:
	Cinematic();
	~Cinematic();

	void init(SDL_Renderer* renderer, int screenW, int screenH);
	bool draw(SDL_Renderer* renderer);

private:
	std::vector<SDL_Rect> cropRects;
	SDL_Texture* background;
	SDL_Texture* cropTexture;
	SDL_Texture* farmerLayer;
	int ticks;
};
