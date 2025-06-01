#pragma once
#include "Globals.h"

class Grip {
public:
	Grip() { }
	Grip(int2 a, bool b, bool c) { pos = a; isSlippery = b; isCheckpoint = c; }
	~Grip() { }

	int2 pos;
	bool isSlippery;
	bool isCheckpoint;
};