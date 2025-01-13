#include "src/Weapons/WeaponFactory.h"
#include "WeaponFactory.h"

Weapon *WeaponFactory::GetNullWeapon()
{
	auto nullAttackData = AttackData({}, 0, 1, 0, 1, "Hitscan");
	std::map<std::string, AttackData> nullAttackDataMap = {};
	nullAttackDataMap[nullAttackData.attackName] = nullAttackData;
	WeaponData data = WeaponData("Null Weapon", nullAttackDataMap);

	return new Weapon(data);
}

Weapon *WeaponFactory::GetAX52()
{
	auto weaponAttackData = AttackData({DamageValue(DamageType::DT_PUNCTURE, 40)}, 0.26, 2.4, 0.18, 10, "Hitscan");
	std::map<std::string, AttackData> weaponAttackDataMap = {};
	weaponAttackDataMap[weaponAttackData.attackName] = weaponAttackData;
	WeaponData data = WeaponData("AX-52", weaponAttackDataMap);

	return new Weapon(data);
}

Weapon *WeaponFactory::GetBratonVandal()
{
	std::vector<DamageValue> damageData = {DamageValue(DamageType::DT_IMPACT, 12.25), DamageValue(DamageType::DT_PUNCTURE, 1.75), DamageValue(DamageType::DT_SLASH, 21)};
	auto weaponAttackData = AttackData(damageData, 0.16, 2, 0.16, 7.5, "Hitscan");
	std::map<std::string, AttackData> weaponAttackDataMap = {};
	weaponAttackDataMap[weaponAttackData.attackName] = weaponAttackData;
	WeaponData data = WeaponData("Braton Vandal", weaponAttackDataMap);

	return new Weapon(data);
}

Weapon *WeaponFactory::GetFulminPrime()
{
	std::vector<DamageValue> damageData = {DamageValue(DamageType::DT_PUNCTURE, 8), DamageValue(DamageType::DT_ELECTRICITY, 25)};
	auto weaponAttackData = AttackData(damageData, 0.34, 2.4, 0.10, 9.33, "Hitscan");
	std::map<std::string, AttackData> weaponAttackDataMap = {};
	weaponAttackDataMap[weaponAttackData.attackName] = weaponAttackData;
	WeaponData data = WeaponData("Fulmin Prime", weaponAttackDataMap);

	return new Weapon(data);
}

Weapon *WeaponFactory::GetNagantakaPrime()
{
	std::vector<DamageValue> damageData = {DamageValue(DamageType::DT_IMPACT, 1.7), DamageValue(DamageType::DT_PUNCTURE, 15.6), DamageValue(DamageType::DT_SLASH, 155.7)};
	auto weaponAttackData = AttackData(damageData, 0.25, 2.3, 0.39, 2.5, "Projectile");
	std::map<std::string, AttackData> weaponAttackDataMap = {};
	weaponAttackDataMap[weaponAttackData.attackName] = weaponAttackData;
	WeaponData data = WeaponData("Nagantaka Prime", weaponAttackDataMap);

	return new Weapon(data);
}
