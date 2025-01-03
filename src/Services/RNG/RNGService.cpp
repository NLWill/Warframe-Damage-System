#pragma once
#include<random>
#include "src/Services/RNG/RNGService.h"

class RNGService : public RNG {
public:
	RNGService(int seed = 0) {
		if (seed == 0) {
			std::random_device rd;
			_seed = rd();
		}
		else {
			_seed = seed;
		}
		_randomEngine = std::default_random_engine(_seed);
	}

	virtual ~RNGService() {

	}

	virtual int RandomInt() {
		std::uniform_int_distribution<int> uint_dist(0, INT32_MAX);
		int result = uint_dist(_randomEngine);
	}

	virtual int RandomInt(int max) {
		std::uniform_int_distribution<int> uint_dist(0, max);
		int result = uint_dist(_randomEngine);
	}

	virtual int RandomInt(int min, int max) {
		std::uniform_int_distribution<int> uint_dist(min, max);
		int result = uint_dist(_randomEngine);
	}

	virtual float RandomFloat(float min, float max) {
		std::uniform_real_distribution<float> ufloat_dist(min, max);
		float result = ufloat_dist(_randomEngine);
	}

	virtual bool RandomBool() {
		return RandomInt() < INT32_MAX / 2;
	}

	virtual bool WeightedRandomBool(float weight) {
		if (weight >= 1) return true;
		else if (weight <= 0) return false;

		return (float)RandomInt() < weight * INT32_MAX;
	}

	virtual int WeightedFloorCeiling(float weight) {
		return WeightedRandomBool(std::fmod(weight, 1)) ? (int)std::ceil(weight) : (int)std::floor(weight);
	}
};