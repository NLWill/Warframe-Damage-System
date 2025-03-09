#include "src/Mods/ModFusionLimit.h"

int ModFusionLimit::GetMaximumModRank(ModFusionLimit modFusionLimit)
{
	switch (modFusionLimit){
		case QA_NONE:
		return 0;
		case QA_MEDIUM:
		return 3;
		case QA_HIGH:
		return 5;
		case QA_VERY_HIGH:
		return 10;
		default:
		std::__throw_invalid_argument("Unhandled modFusionLimit enum in GetMaximumModRank");
	}
}

ModFusionLimit ModFusionLimit::ParseFromString(std::string name)
{
	if (name == "QA_NONE") return QA_NONE;
	if (name == "QA_MEDIUM") return QA_MEDIUM;
	if (name == "QA_HIGH") return QA_HIGH;
	if (name == "QA_VERY_HIGH") return QA_VERY_HIGH;

	std::__throw_invalid_argument("Unhandled ModFusionLimit enum in ParseFromString");
}
