#include "Cinematic.h"
#include "ConfigManager.h"
#include "Presenter.h"
#include <iostream>

Cinematic::Cinematic() { }

Cinematic::~Cinematic() { }

void Cinematic::init(SDL_Renderer* renderer, int screenW, int screenH) {
	Config::readCinematicBackground(renderer, background, cropRects, screenW, screenH);
	cropTexture = loadTexture(Config::cinematicCropPath, renderer);
}

void Cinematic::draw() {
	double swayingAngle = 5 * sin(ticks);
	Presenter::drawObject(background);
	std::cout << cropRects.size() << '\n';
	for (int i = 0; i < cropRects.size(); i++) {
		Presenter::drawObject(cropTexture, &cropRects[i], swayingAngle);
	}
	ticks++;
}
