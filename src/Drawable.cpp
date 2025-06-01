#include "Drawable.h"

Drawable::Drawable() {
	texture = nullptr;
	rect = { -1, -1, 0, 0 };
	alpha = 255;
}

Drawable::~Drawable() {}