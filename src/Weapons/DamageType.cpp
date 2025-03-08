#include "src/Weapons/DamageType.h"
#include "src/Services/ServiceLocator.h"
#include "src/Services/Logging/ILogService.h"

std::string DamageType::ToString()
{
	switch (_damageType)
	{
	case DT_IMPACT:
		return "DT_IMPACT";
	case DT_PUNCTURE:
		return "DT_PUNCTURE";
	case DT_SLASH:
		return "DT_SLASH";
	case DT_FIRE:
		return "DT_FIRE";
	case DT_FREEZE:
		return "DT_FREEZE";
	case DT_ELECTRICITY:
		return "DT_ELECTRICITY";
	case DT_POISON:
		return "DT_POISON";
	case DT_FIRE_NON_COMBINING:
		return "DT_FIRE_NON_COMBINING";
	case DT_FREEZE_NON_COMBINING:
		return "DT_FREEZE_NON_COMBINING";
	case DT_ELECTRICITY_NON_COMBINING:
		return "DT_ELECTRICITY_NON_COMBINING";
	case DT_POISON_NON_COMBINING:
		return "DT_POISON_NON_COMBINING";
	case DT_EXPLOSION:
		return "DT_EXPLOSION";
	case DT_RADIATION:
		return "DT_RADIATION";
	case DT_GAS:
		return "DT_GAS";
	case DT_MAGNETIC:
		return "DT_MAGNETIC";
	case DT_VIRAL:
		return "DT_VIRAL";
	case DT_CORROSIVE:
		return "DT_CORROSIVE";
	case DT_VOID:
		return "DT_VOID";
	case DT_TAU:
		return "DT_TAU";
	case DT_ANY:
		return "DT_ANY";
	default:
		return "DT_" + std::to_string(_damageType);
	}
}

DamageType DamageType::ParseDamageTypeName(const std::string &name)
{
	if (name == "DT_IMPACT")
		return DT_IMPACT;
	if (name == "DT_PUNCTURE")
		return DT_PUNCTURE;
	if (name == "DT_SLASH")
		return DT_SLASH;
	if (name == "DT_FIRE")
		return DT_FIRE;
	if (name == "DT_FREEZE")
		return DT_FREEZE;
	if (name == "DT_ELECTRICITY")
		return DT_ELECTRICITY;
	if (name == "DT_POISON")
		return DT_POISON;
	if (name == "DT_FIRE_NON_COMBINING")
		return DT_FIRE_NON_COMBINING;
	if (name == "DT_FREEZE_NON_COMBINING")
		return DT_FREEZE_NON_COMBINING;
	if (name == "DT_ELECTRICITY_NON_COMBINING")
		return DT_ELECTRICITY_NON_COMBINING;
	if (name == "DT_POISON_NON_COMBINING")
		return DT_POISON_NON_COMBINING;
	if (name == "DT_EXPLOSION")
		return DT_EXPLOSION;
	if (name == "DT_RADIATION")
		return DT_RADIATION;
	if (name == "DT_GAS")
		return DT_GAS;
	if (name == "DT_MAGNETIC")
		return DT_MAGNETIC;
	if (name == "DT_VIRAL")
		return DT_VIRAL;
	if (name == "DT_CORROSIVE")
		return DT_CORROSIVE;
	if (name == "DT_VOID")
		return DT_VOID;
	if (name == "DT_TAU")
		return DT_TAU;
	if (name == "DT_TRUE")
		return DT_TRUE;

	return DT_ANY;
}

bool DamageType::CanCombineDamageTypes(const DamageType &dt1, const DamageType &dt2)
{
	bool dt1IsBaseElement = dt1 == DT_FIRE || dt1 == DT_FREEZE || dt1 == DT_ELECTRICITY || dt1 == DT_POISON;
	bool dt2IsBaseElement = dt2 == DT_FIRE || dt2 == DT_FREEZE || dt2 == DT_ELECTRICITY || dt2 == DT_POISON;

	return dt1IsBaseElement && dt2IsBaseElement;
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