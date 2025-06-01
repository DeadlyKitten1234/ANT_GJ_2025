#pragma once
#include "Cinematic.h"
#include "Presenter.h"

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
};