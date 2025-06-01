#include "ConfigManager.h"
#include <iostream>
#include <Presenter.h>

namespace Config {
const std::string cinematicBackgroundPath = "textures\\CinematicBackground";
const std::string cinematicBackgroundHolePath = "textures\\CinematicBackgroundHole";
const std::string cinematicLocationsPath = "assets\\textures\\CinematicBackground-Locations.bmp";
const std::string cinematicCropPath = "textures\\plant";
const std::string farmerTexturePath = "textures\\farmer";
const std::string farmerLayerPath = "textures\\FarmerLayer";
const std::string farmerLayerPathHole = "textures\\FarmerLayerHole";
const std::string holeBackgroundPath = "textures\\HoleBackground";
const std::string holeFloorPath = "textures\\HoleFloor";
const std::string gripPath = "textures\\Grip";
const std::string levelPath = "assets\\level.txt";
const std::string winScreen = "textures\\win";
const std::string loseScreen = "textures\\lose";
const std::string holeTop = "textures\\HoleTop";
const std::string catPath = "textures\\cat";

void readCinematicBackground(SDL_Renderer* renderer, SDL_Texture*& out,
                             std::vector<SDL_Rect>& cropRect, int screenW, int screenH) {
	
	out = loadTexture(Config::cinematicBackgroundPath, renderer);
	std::ifstream in(cinematicLocationsPath, std::ios::binary);

	int imgW, imgH;
	in.seekg(std::ios::beg + 18);
	in.read((char*)&imgW, 4);
	in.read((char*)&imgH, 4);
	in.seekg(std::ios::beg + 54);
	int cropsCnt = 0;
	const int horizonH = 241;
	const int biggestCropSz = 60;
	const double cropAspectRatio = double(147) / 179;
	double screenMultW = double(screenW) / imgW;
	double screenMultH = double(screenH) / imgH;

	for (int i = 0; i < imgH; i++) {
		for (int j = 0; j < imgW; j++) {
			unsigned char pxl[3];
			in.read((char*)&pxl, 3);
			if (pxl[0] == 0 && pxl[1] == 0 && pxl[2] == 255) {
				// Crop
				double cropH = lerp(1 - double(i) / horizonH, biggestCropSz, 10);
				double cropW = cropH * cropAspectRatio;
				cropsCnt++;
				cropRect.push_back({int((j - cropW * 0.32) * screenMultW),
				                    int((imgH - i - cropH * 0.97) * screenMultH),
				                    int(cropW * screenMultW),
				                    int(cropH * screenMultH)});
			}
		}
		for (int j = 3 * imgW; j % 4 != 0; j++) {
			char padding;
			in.read(&padding, 1);
		}
	}
	in.close();
}

void readLevel(std::vector<Grip>& grips, float& stPosX, float& stPosY, int& fieldW, int& fieldH, int& tileSzOut) {
	std::ifstream in(levelPath);
	int screenInTiles, levelW, levelH;
	in >> screenInTiles >> levelW >> levelH;
	double tileSz = Presenter::SCREEN_W / screenInTiles;
	tileSzOut = tileSz;
	fieldW = levelW;
	fieldH = levelH;
	for (int i = 0; i < levelH; i++) {
		for (int j = 0; j < levelW; j++) {
			char cur;
			in >> cur;
			if (cur == 'O' || cur == '#' || cur == '*') {
				grips.push_back(Grip(int2(j, i), cur == '*'));
			}
			if (cur == 'O') {
				stPosX = j + 0.5;
				stPosY = i + 0.5;
			}
		}
	}
}

} // namespace Config