#pragma once

class ModSlotType
{
public:
	enum ModSlotTypeEnum
	{
		MST_NORMAL,
		MST_AURA,
		MST_EXILUS,
		MST_ARCANE
	};

	ModSlotType() = default;
	constexpr ModSlotType(ModSlotTypeEnum aModSlotType) : _modSlotType(aModSlotType) {}

	// Allow switch and comparisons.
	constexpr operator ModSlotTypeEnum() const { return _modSlotType; }

	// Prevent usage: if(modslottype)
	explicit operator bool() const = delete;
	
	

private:
	ModSlotTypeEnum _modSlotType;
};