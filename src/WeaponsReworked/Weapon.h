#pragma once
#include "src/WeaponsReworked/WeaponData.h"
#include <string>
#include <vector>

class Weapon
{
public:
	WeaponData data;
	int id;
	std::string name;
	std::string parent;
	std::vector<std::string> parents;
	std::string path;
};