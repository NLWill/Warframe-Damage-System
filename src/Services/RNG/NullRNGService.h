#pragma once
#include <random>
#include "src/Services\RNG\IRNGService.h"

class NullRNG : public IRNGService {
public:
	virtual ~NullRNG() = default;
	virtual int RandomInt() { return 0; };
	virtual int RandomInt(int max) { (void)max; return 0; };
	virtual int RandomInt(int min, int max) { (void)min; (void)max; return 0; };
	virtual float RandomFloat(float min, float max) { (void)min; (void)max; return 0; };
	virtual bool RandomBool() { return false; };
	virtual bool WeightedRandomBool(float weight) { (void)weight; return false; };
	virtual int WeightedFloorCeiling(float weight) { (void)weight; return 0; };
};