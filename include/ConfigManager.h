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
extern const std::string catPath;
extern const std::string winScreen;
extern const std::string loseScreen;
extern const std::string holeTop;

void readCinematicBackground(SDL_Renderer* renderer, SDL_Texture*& out,
                             std::vector<SDL_Rect>& cropRect, int screenW,
                             int screenH);

void readLevel(std::vector<int2>& rects, float& stPosX, float& stPosY,
               int& fieldW, int& fieldH, int& tileSzOut);
} // namespace Config