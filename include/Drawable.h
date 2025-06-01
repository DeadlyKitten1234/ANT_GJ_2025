#pragma once
#include <SDL.h>

class Drawable {
public:
	Drawable();
	~Drawable();

	void setRect(SDL_Rect rect_) { rect = rect_; };
	void setTexture(SDL_Texture* texture_) { texture = texture_; };
	void setAlpha(int alpha_) { alpha = alpha_; }

	SDL_Rect rect;
	SDL_Texture* texture;
	int alpha;
};