#pragma once
#include <SDL.h>
#include <string>
using std::string;

SDL_Texture* loadTexture(string in, SDL_Renderer* renderer);
SDL_Texture* loadText(SDL_Renderer* renderer, const string& text);

template<typename T>
T lerp(double t, T a, T b) {
	return t * a + (1 - t) * b;
}

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

inline bool rectCollision(SDL_Rect r1, SDL_Rect r2) {
	return (r1.x + r1.w >= r2.x &&
	        r1.x <= r2.x + r2.w &&
	        r1.y + r1.h >= r2.y &&
	        r1.y <= r2.y + r2.h);
}

bool coordsInRect(int x, int y, SDL_Rect rect);