#include "src/Mods/ModBaseDrain.h"

int ModBaseDrain::GetBaseDrainAmount(ModBaseDrain modBaseDrain)
{
	switch (modBaseDrain){
		case QA_NONE:
		return 0;
		case QA_LOW:
		return 2;
		case QA_MEDIUM:
		return 4;
		case QA_HIGH:
		return 6;
		case QA_VERY_HIGH:
		return 10;
		default:
		std::__throw_invalid_argument("Unhandled modBaseDrain enum in GetBaseDrainAmount");
	}
}

ModBaseDrain ModBaseDrain::ParseFromString(std::string name)
{
	if (name == "QA_NONE") return QA_NONE;
	if (name == "QA_LOW") return QA_LOW;
	if (name == "QA_MEDIUM") return QA_MEDIUM;
	if (name == "QA_HIGH") return QA_HIGH;
	if (name == "QA_VERY_HIGH") return QA_VERY_HIGH;

	std::__throw_invalid_argument("Unhandled modBaseDrain enum in ParseFromString");
}
