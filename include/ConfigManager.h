#pragma once
#include <SDL.h>
#include <vector>
#include <string>
#include <fstream>
#include "Globals.h"

namespace Config {
extern const std::string cinematicBackgroundPath;
extern const std::string cinematicLocationsPath;
extern const std::string cinematicCropPath;

void readCinematicBackground(SDL_Renderer* renderer, SDL_Texture*& out,
                             std::vector<SDL_Rect>& cropRect, int screenW, int screenH);
}; // namespace Config