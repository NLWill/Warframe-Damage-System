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

	std::string ToString()
	{
		switch (_modSlotType)
		{
		case MST_NORMAL:
			return "MST_NORMAL";
		case MST_AURA:
			return "MST_AURA";
		case MST_EXILUS:
			return "MST_EXILUS";
		case MST_ARCANE:
			return "MST_ARCANE";
		default:
			return "";
		}
	}

	static ModSlotType ParseFromString(std::string name)
	{
		if (name == "MST_NORMAL")
			return MST_NORMAL;
		if (name == "MST_AURA")
			return MST_AURA;
		if (name == "MST_EXILUS")
			return MST_EXILUS;
		if (name == "MST_ARCANE")
			return MST_ARCANE;
	}

private:
	ModSlotTypeEnum _modSlotType;
};