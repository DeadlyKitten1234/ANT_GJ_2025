#pragma once
#include "Cinematic.h"
#include "InputManager.h"
#include "Presenter.h"
#include "Hole.h"
#include "GameState.h"

class World {
public:
	World();
	~World();

	void init();
	void draw();
	void update();

private:
	SDL_Texture* winScreen;
	SDL_Texture* loseScreen;
	InputManager inputManager;
	Presenter presenter;
	Cinematic cinematic;
	GameState state;
	Hole hole;
	int curEndTicks;
	int endTicks = 200;
};
