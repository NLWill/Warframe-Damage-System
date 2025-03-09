#pragma once
#include <string>

class ModBaseDrain
{
public:
	enum ModBaseDrainEnum
	{
		QA_NONE,
		QA_LOW,
		QA_MEDIUM,
		QA_HIGH,
		QA_VERY_HIGH
	};

	ModBaseDrain() = default;
	constexpr ModBaseDrain(ModBaseDrainEnum modBaseDrain) : _modBaseDrain(modBaseDrain) {}

	// Allow switch and comparisons.
	constexpr operator ModBaseDrainEnum() const { return _modBaseDrain; }

	// Prevent usage: if(ModBaseDrain)
	explicit operator bool() const = delete;

	// Convert enum into base drain amount for unupgraded mod
	static int GetBaseDrainAmount(ModBaseDrain modBaseDrain); 
	// Convert string representation to Enum form
	static ModBaseDrain ParseFromString(std::string name);

private:
	ModBaseDrainEnum _modBaseDrain;
};