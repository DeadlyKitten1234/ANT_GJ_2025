#include "World.h"
#include <iostream>

World::World() { }

World::~World() { }

void World::init() {
	presenter.init();
	cinematic.init(presenter.getRenderer(), Presenter::SCREEN_W, Presenter::SCREEN_H);
	hole.init(presenter.getRenderer(), Presenter::SCREEN_W, Presenter::SCREEN_H);
	state = GameState::Gameplay;
}

void World::draw() {
	switch (state) { 
	case GameState::Cinematic:
		if (cinematic.draw(presenter.getRenderer())) {
			state = GameState::Gameplay;
		}
		break;
	case GameState::Gameplay:
		hole.draw(presenter.getRenderer());
		break;
	default:
		return;
	}
	presenter.draw();
}

void World::update() {
	inputManager.getInput();
	switch (state) {
	case GameState::Cinematic:
		break;
	case GameState::Gameplay:
		hole.update(inputManager);
		break;
	default:
		return;
	}
}
