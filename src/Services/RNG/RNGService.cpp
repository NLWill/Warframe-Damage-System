#include <random>
#include "src/Services/RNG/RNGService.h"

RNGService::RNGService(int seed)
{
	if (seed == 0)
	{
		std::random_device rd;
		_seed = rd();
	}
	else
	{
		_seed = seed;
	}
	_randomEngine = std::default_random_engine(_seed);
}

RNGService::~RNGService()
{
}

int RNGService::RandomInt()
{
	std::uniform_int_distribution<int> uint_dist(0, INT32_MAX);
	int result = uint_dist(_randomEngine);
	return result;
}

int RNGService::RandomInt(int max)
{
	std::uniform_int_distribution<int> uint_dist(0, max);
	int result = uint_dist(_randomEngine);
	return result;
}

int RNGService::RandomInt(int min, int max)
{
	std::uniform_int_distribution<int> uint_dist(min, max);
	int result = uint_dist(_randomEngine);
	return result;
}

float RNGService::RandomFloat(float min, float max)
{
	std::uniform_real_distribution<float> ufloat_dist(min, max);
	float result = ufloat_dist(_randomEngine);
	return result;
}

bool RNGService::RandomBool()
{
	return RandomInt() < INT32_MAX / 2;
}

bool RNGService::WeightedRandomBool(float weight)
{
	if (weight >= 1)
		return true;
	else if (weight <= 0)
		return false;

	return (float)RandomInt() < weight * INT32_MAX;
}

int RNGService::WeightedFloorCeiling(float weight)
{
	return WeightedRandomBool(std::fmod(weight, 1)) ? (int)std::ceil(weight) : (int)std::floor(weight);
}