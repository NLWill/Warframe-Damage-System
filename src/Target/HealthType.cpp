#include "src/Target/HealthType.h"
#include <map>
#include <unordered_map>

float HealthType::GetDamageTypeModifier(const DamageType &dt)
{
	float mult = 1; // Default value
	
	switch (_healthType)
	{
	case TENNO:
		switch (dt)
		{
		default:
			break;
		}
		break;
	case GRINEER:
		switch (dt)
		{
		case DamageType::DT_IMPACT:
		case DamageType::DT_CORROSIVE:
			mult = 1.5;
			break;
		default:
			break;
		}
		break;
	case KUVA_GRINEER:
		switch (dt)
		{
		case DamageType::DT_IMPACT:
		case DamageType::DT_CORROSIVE:
			mult = 1.5;
			break;
		case DamageType::DT_HEAT:
			mult = 0.5;
			break;
		default:
			break;
		}
		break;
	case CORPUS:
		switch (dt)
		{
		case DamageType::DT_PUNCTURE:
		case DamageType::DT_MAGNETIC:
			mult = 1.5;
			break;
		default:
			break;
		}
		break;
	case CORPUS_AMALGAM:
		switch (dt)
		{
		case DamageType::DT_ELECTRICITY:
		case DamageType::DT_MAGNETIC:
			mult = 1.5;
			break;
		case DamageType::DT_BLAST:
			mult = 0.5;
			break;
		default:
			break;
		}
		break;
	case INFESTED:
		switch (dt)
		{
		case DamageType::DT_HEAT:
		case DamageType::DT_SLASH:
			mult = 1.5;
			break;
		default:
			break;
		}
		break;
	case INFESTED_DEIMOS:
		switch (dt)
		{
		case DamageType::DT_BLAST:
		case DamageType::DT_GAS:
			mult = 1.5;
			break;
		case DamageType::DT_VIRAL:
			mult = 0.5;
			break;
		default:
			break;
		}
		break;
	case OROKIN:
		switch (dt)
		{
		case DamageType::DT_PUNCTURE:
		case DamageType::DT_VIRAL:
			mult = 1.5;
			break;
		case DamageType::DT_RADIATION:
			mult = 0.5;
			break;
		default:
			break;
		}
		break;
	case SENTIENT:
		switch (dt)
		{
		case DamageType::DT_RADIATION:
		case DamageType::DT_COLD:
			mult = 1.5;
			break;
		case DamageType::DT_CORROSIVE:
			mult = 0.5;
			break;
		default:
			break;
		}
		break;
	case NARMER:
		switch (dt)
		{
		case DamageType::DT_SLASH:
		case DamageType::DT_TOXIN:
			mult = 1.5;
			break;
		case DamageType::DT_MAGNETIC:
			mult = 0.5;
			break;
		default:
			break;
		}
		break;
	case MURMUR:
		switch (dt)
		{
		case DamageType::DT_RADIATION:
		case DamageType::DT_ELECTRICITY:
			mult = 1.5;
			break;
		case DamageType::DT_VIRAL:
			mult = 0.5;
			break;
		default:
			break;
		}
		break;
	case ZARIMAN:
		switch (dt)
		{
		case DamageType::DT_VOID:
			mult = 1.5;
			break;
		default:
			break;
		}
		break;
	case SCALDRA:
		switch (dt)
		{
		case DamageType::DT_IMPACT:
		case DamageType::DT_CORROSIVE:
			mult = 1.5;
			break;
		case DamageType::DT_GAS:
			mult = 0.5;
			break;
		default:
			break;
		}
		break;
	case TECHROT:
		switch (dt)
		{
		case DamageType::DT_MAGNETIC:
		case DamageType::DT_GAS:
			mult = 1.5;
			break;
		case DamageType::DT_COLD:
			mult = 0.5;
			break;
		default:
			break;
		}
		break;

	default:
		break;
	}

	return mult;
}