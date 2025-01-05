#pragma once
#include<random>
#include "src/Services/RNG/RNGServiceBase.h"

class RNGService : public RNG {
public:
	RNGService(int seed = 0);
	virtual ~RNGService();
	virtual int RandomInt();
	virtual int RandomInt(int max);
	virtual int RandomInt(int min, int max);
	virtual float RandomFloat(float min, float max);
	virtual bool RandomBool();
	virtual bool WeightedRandomBool(float weight);
	virtual int WeightedFloorCeiling(float weight);
};