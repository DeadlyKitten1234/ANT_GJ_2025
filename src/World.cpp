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
		if (cinematic.draw(presenter.getRenderer())) {
			state = GameState::Gameplay;
		}
		break;
	case GameState::Gameplay:
		farmer.draw(presenter.getRenderer());
	default:
		return;
	}
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
