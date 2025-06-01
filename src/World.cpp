#include "World.h"
#include <iostream>

World::World() { }

World::~World() { }

void World::init() {
	presenter.init();
	cinematic.init(presenter.getRenderer(), Presenter::SCREEN_W, Presenter::SCREEN_H);
	state = GameState::Cinematic;
}

void World::draw() {
	switch (state) { 
	case GameState::Cinematic:
		cinematic.draw(presenter.getRenderer());
		break;
	default:
		return;
	}
	presenter.draw();
}

void World::update() {
	switch (state) {
	case GameState::Cinematic:
		return;
	default:
		return;
	}
}
