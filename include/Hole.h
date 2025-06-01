#pragma once
#include <SDL.h>
#include <Farmer.h>

class Hole {
public:
	Hole();
	~Hole();

	void init(SDL_Renderer* renderer);
	void draw();
	void update();
private:
	SDL_Texture* background;
	Farmer farmer;
};