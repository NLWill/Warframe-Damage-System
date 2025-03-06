#pragma once
#include "src/Weapons/Weapon.h"
#include <memory>

class WeaponFactory
{
public:
	static std::shared_ptr<Weapon> GetNullWeapon();
	//static std::shared_ptr<Weapon> GetAX52();
	//static std::shared_ptr<Weapon> GetBratonVandal();
	//static std::shared_ptr<Weapon> GetFulminPrime();
	//static std::shared_ptr<Weapon> GetNagantakaPrime();
	static std::shared_ptr<Weapon> GetDaikyu();
	static std::shared_ptr<Weapon> GetExergis();
	static std::shared_ptr<Weapon> GetLexPrime();
	static std::shared_ptr<Weapon> GetMK1Braton();

	static std::shared_ptr<Weapon> GetWeapon(std::string name);

private:
	static std::shared_ptr<Weapon> CreateWeapon(std::string databaseData);
};