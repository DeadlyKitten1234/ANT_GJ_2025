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

void Cinematic::draw(SDL_Renderer* renderer) {
	Presenter::drawObject(background);
	for (int i = cropRects.size() - 1; i >= 0; i--) {
		double swayingAngle = 5 * sin(0.07 * ticks + i);
		SDL_Point swayingPoint = { cropRects[i].w * 0.32, cropRects[i].h * 0.97 };
		SDL_RenderCopyEx(renderer, cropTexture, NULL, &cropRects[i], swayingAngle, &swayingPoint, SDL_FLIP_NONE);
	}
	ticks++;
}
