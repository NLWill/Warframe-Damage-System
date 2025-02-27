#pragma once
#include "src/Weapons/Weapon.h"

class WeaponFactory
{
public:
	static Weapon *GetNullWeapon();
	//static Weapon *GetAX52();
	//static Weapon *GetBratonVandal();
	//static Weapon *GetFulminPrime();
	//static Weapon *GetNagantakaPrime();
	static Weapon *GetExergis();
	static Weapon *GetLexPrime();
	static Weapon *GetMK1Braton();

	static Weapon *GetWeapon(std::string name);

private:
	static Weapon *CreateWeapon(std::string databaseData);
};