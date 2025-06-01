#include "Cinematic.h"
#include "ConfigManager.h"
#include "Presenter.h"
#include <iostream>

Cinematic::Cinematic() { }

Cinematic::~Cinematic() { }

void Cinematic::init(SDL_Renderer* renderer, int screenW, int screenH) {
	Config::readCinematicBackground(renderer, background, cropRects, screenW, screenH);
	cropTexture = loadTexture(Config::cinematicCropPath, renderer);
	farmerLayer = loadTexture(Config::farmerLayerPath, renderer);
}

bool Cinematic::draw(SDL_Renderer* renderer) {
	double offsetX = 0, offsetY = 0;
	if (200 <= ticks && ticks <= 300) {
		offsetX += 15 * sin(ticks * 10 + 0.12334);
		offsetY += 15 * sin(ticks * 10);
	}
	if (ticks == 280) {
		//Hole appears
		background = loadTexture(Config::cinematicBackgroundHolePath, renderer);
		farmerLayer = loadTexture(Config::farmerLayerPathHole, renderer);
		double multX = (double)Presenter::SCREEN_W / 738, multY = (double)Presenter::SCREEN_H / 414;
		int holeCenterX = 634 * multX;
		int holeCenterY = 356 * multY;
		for (int i = 0; i < cropRects.size(); i++) {
			int dx = (cropRects[i].x - holeCenterX) / multX;
			int dy = (cropRects[i].y - holeCenterY) * 1.7 / multY;
			if (dx * dx + dy * dy < 240 * 240) {
				cropRects.erase(cropRects.begin() + i);
				i--;
			}
		}
	}
	if (ticks > 300) {
		return true;
	}

	SDL_Rect backgroundRect = { offsetX, offsetY, Presenter::SCREEN_W, Presenter::SCREEN_H };
	Presenter::drawObject(background, &backgroundRect);
	for (int i = cropRects.size() - 1; i >= 0; i--) {
		double swayingAngle = 5 * sin(0.07 * ticks + i);
		SDL_Point swayingPoint = { cropRects[i].w * 0.32, cropRects[i].h * 0.97 };
		SDL_Rect newRect = { cropRects[i].x + offsetX, cropRects[i].y + offsetY, cropRects[i].w, cropRects[i].h };
		SDL_RenderCopyEx(renderer, cropTexture, NULL, &newRect, swayingAngle, &swayingPoint, SDL_FLIP_NONE);
	}
	Presenter::drawObject(farmerLayer, &backgroundRect);
	ticks++;
}
