#pragma once
#include <SDL.h>
#include <string>
using std::string;

SDL_Texture* loadTexture(string in, SDL_Renderer* renderer);
SDL_Texture* loadText(SDL_Renderer* renderer, const string& text);

struct float2 {
	float2() { x = y = 0; }
	float2(float x_, float y_) { x = x_; y = y_; };
	float x;
	float y;
};

struct int2 {
	int2() { x = y = 0; }
	int2(int x_, int y_) { x = x_; y = y_; };
	int x;
	int y;
};

bool coordsInRect(int x, int y, SDL_Rect rect);