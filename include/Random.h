#pragma once
#include <cinttypes>

class RandNumGen {
public:
	RandNumGen() { seed = 16184 * 31415; };
	RandNumGen(uint32_t seed_) { seed = seed_; };
	~RandNumGen() {};

	//Xor shift algorithm
	inline float rand() {
		seed ^= seed << 13;
		seed ^= seed >> 17;
		seed ^= seed << 5;
		return seed * 0xDEAF / 4294967296.0f;
	}

private:
	uint32_t seed;
};

extern RandNumGen rng;