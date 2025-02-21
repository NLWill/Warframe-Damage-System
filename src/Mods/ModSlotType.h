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
	
	std::string ToString(){
		switch (_modSlotType){
			case MST_NORMAL:
			return "Normal Slot Type";
			case MST_AURA:
			return "Aura Slot Type";
			case MST_EXILUS:
			return "Exilus Slot Type";
			case MST_ARCANE:
			return "Arcane Slot Type";
			default:
			return "";
		}
	}

private:
	ModSlotTypeEnum _modSlotType;
};