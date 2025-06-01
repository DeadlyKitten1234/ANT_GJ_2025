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
		cinematic.draw(presenter.getRenderer());
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
		farmer.update(inputManager);
		return;
	case GameState::Gameplay:
	default:
		return;
	}
}
