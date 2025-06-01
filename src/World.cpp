#include "World.h"

World::World() { }

World::~World() { }

void World::init() {
	presenter.init();
	cinematic.init(presenter.getRenderer(), Presenter::SCREEN_W, Presenter::SCREEN_H);
}

void World::draw() { }

void World::update() { }
