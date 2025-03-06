#pragma once
#include <random>

class IRNGService {
public:
	virtual ~IRNGService() {};

	/// <summary>
	/// Generate a random int from 0 to INT32_MAX
	/// </summary>
	/// <returns></returns>
	virtual int RandomInt() = 0;

	/// <summary>
	/// Generate a random int from 0 to max (inclusive)
	/// </summary>
	/// <param name="max"></param>
	/// <returns></returns>
	virtual int RandomInt(int max) = 0;

	/// <summary>
	/// Generate a random int from min to max (inclusive)
	/// </summary>
	/// <param name="min"></param>
	/// <param name="max"></param>
	/// <returns></returns>
	virtual int RandomInt(int min, int max) = 0;

	/// <summary>
	/// Generate a random float from min (inclusive) to max (exclusive)
	/// </summary>
	/// <param name="min"></param>
	/// <param name="max"></param>
	/// <returns></returns>
	virtual float RandomFloat(float min, float max) = 0;

	/// <summary>
	/// Generate a random bool with equal probability
	/// </summary>
	/// <returns></returns>
	virtual bool RandomBool() = 0;

	/// <summary>
	/// Generate a random bool with weighted probability of success
	/// </summary>
	/// <param name="weight"></param>
	/// <returns></returns>
	virtual bool WeightedRandomBool(float weight) = 0;

	/// <summary>
	/// Generate a random int with with weighted probability of taking the floor or ceiling of the value
	/// </summary>
	/// <param name="weight"></param>
	/// <returns></returns>
	virtual int WeightedFloorCeiling(float weight) = 0;

protected:
	int _seed;
	std::default_random_engine _randomEngine;
};