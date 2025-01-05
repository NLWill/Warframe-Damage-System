#pragma once
#include<random>
#include "src/Services\RNG\RNGServiceBase.h"

class NullRNG : public RNG {
public:
	virtual ~NullRNG() {};
	virtual int RandomInt() { return 0; };
	virtual int RandomInt(int max) { return 0; };
	virtual int RandomInt(int min, int max) { return 0; };
	virtual float RandomFloat(float min, float max) { return 0; };
	virtual bool RandomBool() { return false; };
	virtual bool WeightedRandomBool(float weight) { return false; };
	virtual int WeightedFloorCeiling(float weight) { return 0; };
};