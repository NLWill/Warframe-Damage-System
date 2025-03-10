#include "src/Target/Faction.h"

Faction Faction::ParseFactionName(std::string factionName)
{
	if (factionName == "Tenno")
		return TENNO;
	if (factionName == "Grineer")
		return GRINEER;
	if (factionName == "Corpus")
		return CORPUS;
	if (factionName == "Infested")
		return INFESTED;
	if (factionName == "Orikin")
		return OROKIN;
	if (factionName == "Sentient")
		return SENTIENT;
	if (factionName == "Stalker")
		return STALKER;
	if (factionName == "Narmer")
		return NARMER;
	if (factionName == "Murmur")
		return MURMUR;
	if (factionName == "Scaldra")
		return SCALDRA;
	if (factionName == "Techrot")
		return TECHROT;
	if (factionName == "Syndicates")
		return SYNDICATES;
	if (factionName == "Wild")
		return WILD;
		
	return NONE;
}