#pragma once

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

private:
	ModOperationTypeEnum _modOperationType;
};