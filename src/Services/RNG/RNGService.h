#pragma once
#include <random>
#include "src/Services/RNG/IRNGService.h"

class RNGService : public IRNGService {
public:
	RNGService(int seed = 0);
	virtual ~RNGService() = default;
	virtual int RandomInt();
	virtual int RandomInt(int max);
	virtual int RandomInt(int min, int max);
	virtual float RandomFloat(float min, float max);
	virtual bool RandomBool();
	virtual bool WeightedRandomBool(float weight);
	virtual int WeightedFloorCeiling(float weight);
};