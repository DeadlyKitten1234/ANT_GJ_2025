#include "Globals.h"
#include "SDL_ttf.h"
#include <iostream>

SDL_Texture* loadTexture(string in, SDL_Renderer* renderer) {
	in = "assets\\" + in + ".bmp";
	SDL_Surface* loadingSurface = SDL_LoadBMP(in.c_str());
	SDL_Texture* out = nullptr;
	out = SDL_CreateTextureFromSurface(renderer, loadingSurface);
	SDL_FreeSurface(loadingSurface);
	return out;
}

SDL_Texture* loadText(SDL_Renderer* renderer, const string& text) {
    TTF_Font* font = TTF_OpenFont("assets\\font\\Font - Copy.TTF", 20);
    if (font == NULL) {
        std::cout << "Error " << TTF_GetError() << "\n";
    }
    SDL_Surface* text_srf = nullptr;
    SDL_Texture* text_img = nullptr;
    text_srf = TTF_RenderText_Solid(font, text.c_str(), /*SDL_Color*/{ 255, 255, 255 });
    text_img = SDL_CreateTextureFromSurface(renderer, text_srf);
    SDL_FreeSurface(text_srf);
    return text_img;
}
bool coordsInRect(int x, int y, SDL_Rect rect) {
	return rect.x <= x && x <= rect.x + rect.w && rect.y <= y && y <= rect.y + rect.h;	
}
