#include "Presenter.h"

//#include "World.h"
//extern World world;

SDL_Texture* Presenter::BACKGROUND_TEXTURE = nullptr;
SDL_Window* Presenter::mainWindow = nullptr;
SDL_Renderer* Presenter::mainRenderer = nullptr;
unsigned int Presenter::SCREEN_W = 0;
unsigned int Presenter::SCREEN_H = 0;

void Presenter::init() {
    SCREEN_W = 1536;
    SCREEN_H = 864;

    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    mainWindow = SDL_CreateWindow("TEMPLATE", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_W, SCREEN_H, 0);
    mainRenderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);
}

void Presenter::draw() {
    SDL_RenderPresent(mainRenderer);
    SDL_RenderClear(mainRenderer);
}

void Presenter::drawObject(SDL_Texture* texture, SDL_Rect* rect, double angle) {
	SDL_RenderCopyEx(mainRenderer, texture, NULL, (rect == nullptr ? NULL : rect), angle, NULL, SDL_FLIP_NONE);
}

void Presenter::drawObject(const Drawable& drawable) {
    SDL_RenderCopy(mainRenderer, drawable.texture, NULL, &drawable.rect);
}