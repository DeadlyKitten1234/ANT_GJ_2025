#pragma once 

#include <SDL_TTF.h>
#include "Drawable.h"

class Presenter {
public:
    static SDL_Window* mainWindow;
    static SDL_Renderer* mainRenderer;

    static unsigned int SCREEN_W;
    static unsigned int SCREEN_H;
    static SDL_Texture* BACKGROUND_TEXTURE;

    void init();
    void draw();

    SDL_Renderer* getRenderer() const { return mainRenderer; }

    static void drawObject(SDL_Texture* texture, SDL_Rect* rect = nullptr, double angle = 0);
    static void drawObject(const Drawable& drawable);
};
