#include "src/Target/HealthType.h"
#include <map>
#include <unordered_map>

float HealthType::GetHealthTypeModifier(const HealthType &healthType, const DamageType &dt)
{
	float mult = 1; // Default value
	
	switch (healthType)
	{
	case HEALTH_TYPE_TENNO:
		switch (dt)
		{
		default:
			break;
		}
		break;
	case HEALTH_TYPE_GRINEER:
		switch (dt)
		{
		case DT_IMPACT:
		case DT_CORROSIVE:
			mult = 1.5;
			break;
		default:
			break;
		}
		break;
	case HEALTH_TYPE_KUVA_GRINEER:
		switch (dt)
		{
		case DT_IMPACT:
		case DT_CORROSIVE:
			mult = 1.5;
			break;
		case DT_HEAT:
			mult = 0.5;
			break;
		default:
			break;
		}
		break;
	case HEALTH_TYPE_CORPUS:
		switch (dt)
		{
		case DT_PUNCTURE:
		case DT_MAGNETIC:
			mult = 1.5;
			break;
		default:
			break;
		}
		break;
	case HEALTH_TYPE_CORPUS_AMALGAM:
		switch (dt)
		{
		case DT_ELECTRICITY:
		case DT_MAGNETIC:
			mult = 1.5;
			break;
		case DT_BLAST:
			mult = 0.5;
			break;
		default:
			break;
		}
		break;
	case HEALTH_TYPE_INFESTED:
		switch (dt)
		{
		case DT_HEAT:
		case DT_SLASH:
			mult = 1.5;
			break;
		default:
			break;
		}
		break;
	case HEALTH_TYPE_INFESTED_DEIMOS:
		switch (dt)
		{
		case DT_BLAST:
		case DT_GAS:
			mult = 1.5;
			break;
		case DT_VIRAL:
			mult = 0.5;
			break;
		default:
			break;
		}
		break;
	case HEALTH_TYPE_OROKIN:
		switch (dt)
		{
		case DT_PUNCTURE:
		case DT_VIRAL:
			mult = 1.5;
			break;
		case DT_RADIATION:
			mult = 0.5;
			break;
		default:
			break;
		}
		break;
	case HEALTH_TYPE_SENTIENT:
		switch (dt)
		{
		case DT_RADIATION:
		case DT_COLD:
			mult = 1.5;
			break;
		case DT_CORROSIVE:
			mult = 0.5;
			break;
		default:
			break;
		}
		break;
	case HEALTH_TYPE_NARMER:
		switch (dt)
		{
		case DT_SLASH:
		case DT_TOXIN:
			mult = 1.5;
			break;
		case DT_MAGNETIC:
			mult = 0.5;
			break;
		default:
			break;
		}
		break;
	case HEALTH_TYPE_MURMUR:
		switch (dt)
		{
		case DT_RADIATION:
		case DT_ELECTRICITY:
			mult = 1.5;
			break;
		case DT_VIRAL:
			mult = 0.5;
			break;
		default:
			break;
		}
		break;
	case HEALTH_TYPE_ZARIMAN:
		switch (dt)
		{
		case DT_VOID:
			mult = 1.5;
			break;
		default:
			break;
		}
		break;
	case HEALTH_TYPE_SCALDRA:
		switch (dt)
		{
		case DT_IMPACT:
		case DT_CORROSIVE:
			mult = 1.5;
			break;
		case DT_GAS:
			mult = 0.5;
			break;
		default:
			break;
		}
		break;
	case HEALTH_TYPE_TECHROT:
		switch (dt)
		{
		case DT_MAGNETIC:
		case DT_GAS:
			mult = 1.5;
			break;
		case DT_COLD:
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