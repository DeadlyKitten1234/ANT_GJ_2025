#pragma once
#include "Globals.h"

class Grip {
public:
	Grip() { }
	Grip(int2 a, bool b) { pos = a; isSlippery = b; }
	~Grip() { }

	int2 pos;
	bool isSlippery;
};