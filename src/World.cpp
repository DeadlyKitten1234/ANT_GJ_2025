#include "World.h"
#include <iostream>

World::World() { }

World::~World() { }

void World::init() {
	presenter.init();
	winScreen = loadTexture(Config::winScreen, presenter.getRenderer());
	loseScreen = loadTexture(Config::loseScreen, presenter.getRenderer());
	cinematic.init(presenter.getRenderer(), Presenter::SCREEN_W, Presenter::SCREEN_H);
	hole.init(presenter.getRenderer(), Presenter::SCREEN_W, Presenter::SCREEN_H);
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
		hole.draw(presenter.getRenderer());
		break;
	case GameState::Win:
		SDL_RenderCopy(presenter.getRenderer(), winScreen, NULL, NULL);
		break;
	case GameState::Lose:
		SDL_RenderCopy(presenter.getRenderer(), loseScreen, NULL, NULL);
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
		hole.update(inputManager, state);
		break;
	case GameState::Win:
		break;
	case GameState::Lose:
		break;
	default:
		return;
	}
}
