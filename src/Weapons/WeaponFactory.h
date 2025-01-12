#pragma once
#include "src/Weapons/Weapon.h"

class WeaponFactory{
	public:
	static Weapon* GetNullWeapon();
	static Weapon* GetAX52();
	static Weapon* GetBratonVandal();

};