#include <iostream>
#include "World.h"
#include <SDL.h>

#undef main

World* world;

int main(int argc, char* argv[]) {
	world = new World();
	world->init();
	while (1) {
		world->draw();
		world->update();
		SDL_Delay(20);
	}

	delete world;
	return 0;
}
