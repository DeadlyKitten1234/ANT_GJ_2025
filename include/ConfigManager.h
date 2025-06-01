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
extern const std::string cinematicBackgroundHolePath;
extern const std::string farmerTexturePath;
extern const std::string farmerLayerPath;
extern const std::string farmerLayerPathHole;
extern const std::string holeBackgroundPath;
extern const std::string levelPath;
extern const std::string holeFloorPath;
extern const std::string gripPath;
extern const std::string winScreen;
extern const std::string loseScreen;

void readCinematicBackground(SDL_Renderer* renderer, SDL_Texture*& out,
                             std::vector<SDL_Rect>& cropRect, int screenW, int screenH);

void readLevel(int screenW, std::vector<SDL_Rect>& rects, float& stPosX, float& stPosY, int& bottomY, int& tileSzOut);
}; // namespace Config