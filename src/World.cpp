#include "World.h"
#include <iostream>

World::World() { }

World::~World() { }

void World::init() {
	presenter.init();
	cinematic.init(presenter.getRenderer(), Presenter::SCREEN_W, Presenter::SCREEN_H);
	farmer.init(presenter.getRenderer(), Presenter::SCREEN_W, Presenter::SCREEN_H);
	state = GameState::Cinematic;
}

void World::draw() {
	switch (state) { 
	case GameState::Cinematic:
		cinematic.draw();
		break;
	default:
		return;
	}
	farmer.draw(presenter.getRenderer());
	presenter.draw();
}

void World::update() {
	inputManager.getInput();
	switch (state) {
	case GameState::Cinematic:
		return;
	case GameState::Gameplay:
		farmer.update(inputManager);
	default:
		return;
	}
}
