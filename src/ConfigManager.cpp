#include "ConfigManager.h"


namespace Config {
const std::string cinematicBackgroundPath = "CinematicBackground";
const std::string cinematicCropPath = "textures\\plant";
void readCinematicBackground(SDL_Renderer* renderer, SDL_Texture* out,
                             std::vector<SDL_Rect>& cropRect, int screenW,
                             int screenH) {
	out = loadTexture(cinematicBackgroundPath, renderer);
	std::ifstream in("assets\\" + cinematicBackgroundPath + ".bmp",
	                 std::ios::binary);

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
			char pxl[3];
			in.read(pxl, 3);
			if (pxl[2] == 0 && pxl[1] == 0 && pxl[0] == 0) {
				// Crop
				double cropH = double((horizonH - i) * biggestCropSz) / horizonH;
				double cropW = cropH * cropAspectRatio;
				cropsCnt++;
				cropRect.push_back({int((j - cropW / 2) * screenMultW),
				                    int((imgH - i - cropH) * screenMultH),
				                    int(cropW * screenMultW),
				                    int(cropW * screenMultH)});
			}
		}
		for (int j = 3 * imgW; j % 4 != 0; j++) {
			char padding;
			in.read(&padding, 1);
		}
	}
}
} // namespace Config