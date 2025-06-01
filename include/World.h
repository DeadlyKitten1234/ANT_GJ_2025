#pragma once
#include "Cinematic.h"
#include "InputManager.h"
#include "Presenter.h"
#include "Farmer.h"

enum class GameState {
	Cinematic, Gameplay
};

class World {
public:
	World();
	~World();

	void init();
	void draw();
	void update();

private:
	InputManager inputManager;
	Presenter presenter;
	Cinematic cinematic;
	GameState state;
	Farmer farmer;
};
