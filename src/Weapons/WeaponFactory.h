#pragma once
#include "src/Weapons/Weapon.h"
#include <memory>

class WeaponFactory
{
public:
	static shared_ptr<Weapon> GetNullWeapon();
	//static shared_ptr<Weapon> GetAX52();
	//static shared_ptr<Weapon> GetBratonVandal();
	//static shared_ptr<Weapon> GetFulminPrime();
	//static shared_ptr<Weapon> GetNagantakaPrime();
	static shared_ptr<Weapon> GetDaikyu();
	static shared_ptr<Weapon> GetExergis();
	static shared_ptr<Weapon> GetLexPrime();
	static shared_ptr<Weapon> GetMK1Braton();

	static shared_ptr<Weapon> GetWeapon(std::string name);

private:
	static shared_ptr<Weapon> CreateWeapon(std::string databaseData);
};