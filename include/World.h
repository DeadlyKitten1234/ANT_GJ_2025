#pragma once
#include "Cinematic.h"
#include "Presenter.h"

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
	Presenter presenter;
	Cinematic cinematic;
	GameState state;
};