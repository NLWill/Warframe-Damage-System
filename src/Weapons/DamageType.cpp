#include "src/Weapons/DamageType.h"
#include "src/Services/ServiceLocator.h"
#include "src/Services/Logging/ILogService.h"

std::string DamageType::ToString()
{
	switch (_damageType)
	{
	case DT_IMPACT:
		return "Impact";
	case DT_PUNCTURE:
		return "Puncture";
	case DT_SLASH:
		return "Slash";
	case DT_FIRE:
		return "Heat";
	case DT_FREEZE:
		return "Cold";
	case DT_ELECTRICITY:
		return "Electricity";
	case DT_POISON:
		return "Toxin";
	case DT_FIRE_NON_COMBINING:
		return "HeatNC";
	case DT_FREEZE_NON_COMBINING:
		return "ColdNC";
	case DT_ELECTRICITY_NON_COMBINING:
		return "ElectricityNC";
	case DT_POISON_NON_COMBINING:
		return "ToxinNC";
	case DT_EXPLOSION:
		return "Blast";
	case DT_RADIATION:
		return "Radiation";
	case DT_GAS:
		return "Gas";
	case DT_MAGNETIC:
		return "Magnetic";
	case DT_VIRAL:
		return "Viral";
	case DT_CORROSIVE:
		return "Corrosive";
	case DT_VOID:
		return "Void";
	case DT_TAU:
		return "Tau";
	case DT_ANY:
		return "DT_ANY";
	default:
		return "DT_" + std::to_string(_damageType);
	}
}

DamageType DamageType::ParseDamageTypeName(const std::string &name)
{
	if (name == "Impact")
		return DT_IMPACT;
	if (name == "Puncture")
		return DT_PUNCTURE;
	if (name == "Slash")
		return DT_SLASH;
	if (name == "Heat")
		return DT_FIRE;
	if (name == "Cold")
		return DT_FREEZE;
	if (name == "Electricity")
		return DT_ELECTRICITY;
	if (name == "Toxin")
		return DT_POISON;
	if (name == "HeatNC")
		return DT_FIRE_NON_COMBINING;
	if (name == "ColdNC")
		return DT_FREEZE_NON_COMBINING;
	if (name == "ElectricityNC")
		return DT_ELECTRICITY_NON_COMBINING;
	if (name == "ToxinNC")
		return DT_POISON_NON_COMBINING;
	if (name == "Blast")
		return DT_EXPLOSION;
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
	case DT_FIRE:
		switch (dt2)
		{
		case DT_FREEZE:
			return DT_EXPLOSION;
			break;
		case DT_ELECTRICITY:
			return DT_RADIATION;
			break;
		case DT_POISON:
			return DT_GAS;
			break;
		default:
			break;
		}
		break;
	case DT_FREEZE:
		switch (dt2)
		{
		case DT_FIRE:
			return DT_EXPLOSION;
			break;
		case DT_ELECTRICITY:
			return DT_MAGNETIC;
			break;
		case DT_POISON:
			return DT_VIRAL;
			break;
		default:
			break;
		}
		break;
	case DT_ELECTRICITY:
		switch (dt2)
		{
		case DT_FIRE:
			return DT_RADIATION;
			break;
		case DT_FREEZE:
			return DT_MAGNETIC;
			break;
		case DT_POISON:
			return DT_CORROSIVE;
			break;
		default:
			break;
		}
		break;
	case DT_POISON:
		switch (dt2)
		{
		case DT_FIRE:
			return DT_GAS;
			break;
		case DT_FREEZE:
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

	ServiceLocator::GetService<ILogService>()->LogError("Unable to combine elements: " + std::to_string(dt1) + " and " + std::to_string(dt2));
	throw 1;
}

std::vector<DamageType> DamageType::DecomposeCombinedElement(DamageType dt)
{
	std::vector<DamageType> result = {};
	switch (dt)
	{
	case DT_EXPLOSION:
		result.push_back(DT_FIRE);
		result.push_back(DT_FREEZE);
		break;
	case DT_RADIATION:
		result.push_back(DT_FIRE);
		result.push_back(DT_ELECTRICITY);
		break;
	case DT_GAS:
		result.push_back(DT_FIRE);
		result.push_back(DT_POISON);
		break;
	case DT_MAGNETIC:
		result.push_back(DT_FREEZE);
		result.push_back(DT_ELECTRICITY);
		break;
	case DT_VIRAL:
		result.push_back(DT_FREEZE);
		result.push_back(DT_POISON);
		break;
	case DT_CORROSIVE:
		result.push_back(DT_ELECTRICITY);
		result.push_back(DT_POISON);
		break;
	default:
		ServiceLocator::GetService<ILogService>()->LogError("Unable to decompose element: " + std::to_string(dt));
		result.push_back(dt);
		break;
	}

	return result;
}