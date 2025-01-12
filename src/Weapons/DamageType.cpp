#include "src/Weapons/DamageType.h"
#include "src/Services/ServiceLocator.h"

DamageType DamageType::ParseDamageTypeName(const std::string &name)
{
	if (name == "Impact")
		return DT_IMPACT;
	if (name == "Puncture")
		return DT_PUNCTURE;
	if (name == "Slash")
		return DT_SLASH;
	if (name == "Heat")
		return DT_HEAT;
	if (name == "Cold")
		return DT_COLD;
	if (name == "Electricity")
		return DT_ELECTRICITY;
	if (name == "Toxin")
		return DT_TOXIN;
	if (name == "HeatNC")
		return DT_HEAT_NON_COMBINING;
	if (name == "ColdNC")
		return DT_COLD_NON_COMBINING;
	if (name == "ElectricityNC")
		return DT_ELECTRICITY_NON_COMBINING;
	if (name == "ToxinNC")
		return DT_TOXIN_NON_COMBINING;
	if (name == "Blast")
		return DT_BLAST;
	if (name == "Radiation")
		return DT_RADIATION;
	if (name == "Gas")
		return DT_GAS;
	if (name == "Magnetic")
		return DT_MAGNETIC;
	if (name == "Viral")
		return DT_VIRAL;
	if (name == "Corrosive")
		return DT_CORROSIVE;
	if (name == "Void")
		return DT_VOID;
	if (name == "Tau")
		return DT_TAU;
	if (name == "True")
		return DT_TRUE;

	return DT_ANY;
}

DamageType DamageType::CombineDamageTypes(const DamageType &dt1, const DamageType &dt2)
{
	switch (dt1)
	{
	case DT_HEAT:
		switch (dt2)
		{
		case DT_COLD:
			return DT_BLAST;
			break;
		case DT_ELECTRICITY:
			return DT_RADIATION;
			break;
		case DT_TOXIN:
			return DT_GAS;
			break;
		default:
			break;
		}
		break;
	case DT_COLD:
		switch (dt2)
		{
		case DT_HEAT:
			return DT_BLAST;
			break;
		case DT_ELECTRICITY:
			return DT_MAGNETIC;
			break;
		case DT_TOXIN:
			return DT_VIRAL;
			break;
		default:
			break;
		}
		break;
	case DT_ELECTRICITY:
		switch (dt2)
		{
		case DT_HEAT:
			return DT_RADIATION;
			break;
		case DT_COLD:
			return DT_MAGNETIC;
			break;
		case DT_TOXIN:
			return DT_CORROSIVE;
			break;
		default:
			break;
		}
		break;
	case DT_TOXIN:
		switch (dt2)
		{
		case DT_HEAT:
			return DT_GAS;
			break;
		case DT_COLD:
			return DT_VIRAL;
			break;
		case DT_ELECTRICITY:
			return DT_CORROSIVE;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}

	ServiceLocator::GetLogger().LogError("Unable to combine elements: " + std::to_string(dt1) + " and " + std::to_string(dt2));
	throw 1;
}

std::vector<DamageType> DamageType::DecomposeCombinedElement(DamageType dt)
{
	std::vector<DamageType> result = {};
	switch (dt)
	{
	case DT_BLAST:
		result.push_back(DT_HEAT);
		result.push_back(DT_COLD);
		break;
	case DT_RADIATION:
		result.push_back(DT_HEAT);
		result.push_back(DT_ELECTRICITY);
		break;
	case DT_GAS:
		result.push_back(DT_HEAT);
		result.push_back(DT_TOXIN);
		break;
	case DT_MAGNETIC:
		result.push_back(DT_COLD);
		result.push_back(DT_ELECTRICITY);
		break;
	case DT_VIRAL:
		result.push_back(DT_COLD);
		result.push_back(DT_TOXIN);
		break;
	case DT_CORROSIVE:
		result.push_back(DT_ELECTRICITY);
		result.push_back(DT_TOXIN);
		break;
	default:
		ServiceLocator::GetLogger().LogError("Unable to decompose element: " + std::to_string(dt));
		result.push_back(dt);
		break;
	}

	return result;
}