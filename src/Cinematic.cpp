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
	double swayingAngle = 0;
	//5 * sin(0.1 * ticks);
	Presenter::drawObject(background);
	for (int i = cropRects.size() - 1; i >= 0; i--) {
		Presenter::drawObject(cropTexture, &cropRects[i], swayingAngle);
	}
	ticks++;
}
