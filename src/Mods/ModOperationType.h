#pragma once
#include <string>
#include <vector>

class ModOperationType
{
public:
	enum ModOperationTypeEnum
	{
		NONE,
		ADD_TO_BASE_VALUE,
		STACKING_MULTIPLY,
		MULTIPLY,
		ADD,
		SET
	};

	ModOperationType() = default;
	constexpr ModOperationType(ModOperationTypeEnum aModOperationType) : _modOperationType(aModOperationType) {}

	// Allow switch and comparisons.
	constexpr operator ModOperationTypeEnum() const { return _modOperationType; }

	// Prevent usage: if(modoperationtype)
	explicit operator bool() const = delete;

	// Convert Enum into string form for output in the console
	static std::string ToString(ModOperationType modUpgradeType);
	// Convert string representation to Enum form
	static ModOperationType ParseFromString(std::string name);

private:
	ModOperationTypeEnum _modOperationType;

	/// @brief A pairing of enum values and strings for quick parsing and string conversion
	static std::vector<std::pair<ModOperationType, std::string>> modOperationTypeStringNames;
};