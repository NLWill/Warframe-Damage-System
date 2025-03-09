#pragma once
#include <string>

class ModFusionLimit
{
public:
	enum ModFusionLimitEnum
	{
		QA_NONE,
		QA_MEDIUM,
		QA_HIGH,
		QA_VERY_HIGH
	};

	ModFusionLimit() = default;
	constexpr ModFusionLimit(ModFusionLimitEnum modFusionLimit) : _modFusionLimit(modFusionLimit) {}

	// Allow switch and comparisons.
	constexpr operator ModFusionLimitEnum() const { return _modFusionLimit; }

	// Prevent usage: if(ModFusionLimit)
	explicit operator bool() const = delete;

	// Convert enum into the maximum rank a mod may be upgraded to
	static int GetMaximumModRank(ModFusionLimit modFusionLimit); 
	// Convert string representation to Enum form
	static ModFusionLimit ParseFromString(std::string name);

private:
	ModFusionLimitEnum _modFusionLimit;
};