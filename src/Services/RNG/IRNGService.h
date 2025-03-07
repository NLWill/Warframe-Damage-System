#pragma once
#include <random>
#include "src/Services/IService.h"

class IRNGService : public IService{
public:
	virtual ~IRNGService() = default;

	/// @brief Generate a random int from 0 to INT32_MAX
	/// @return 
	virtual int RandomInt() = 0;

	/// @brief Generate a random int from 0 to max (inclusive). [0, max]
	/// @param max The maximum value possible to be generated
	/// @return 
	virtual int RandomInt(int max) = 0;

	/// @brief Generate a random int within a specified range, [min, max]
	/// @param min The minimum value possible to be generated
	/// @param max The maximum value possible to be generated
	/// @return 
	virtual int RandomInt(int min, int max) = 0;

	/// @brief Generate a random float within a specified range, [min, max)
	/// @param min The minimum value of the range
	/// @param max The maximum value of the range
	/// @return 
	virtual float RandomFloat(float min, float max) = 0;

	/// @brief Generate a random bool with 50/50 probability
	/// @return 
	virtual bool RandomBool() = 0;

	/// @brief Generate a random bool with weighted probability of success
	/// @param weight Probability that the bool returns true
	/// @return 
	virtual bool WeightedRandomBool(float weight) = 0;

	/// @brief Generate a random int with with weighted probability of taking the floor or ceiling of the value
	/// @param weight Initial value to be rounded, with probability based upon the value after the decimal point
	/// @return 
	virtual int WeightedFloorCeiling(float weight) = 0;

	/// Returns the type index of the base interface.
	std::type_index getTypeIndex() const override
	{
		return std::type_index(typeid(IRNGService));
	}

protected:
	int _seed;
	std::default_random_engine _randomEngine;
};