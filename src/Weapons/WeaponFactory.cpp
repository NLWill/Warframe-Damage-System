#include "src/Weapons/WeaponFactory.h"

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
	auto ax52AttackData = AttackData({DamageValue(DamageType::DT_PUNCTURE, 40)}, 0.26, 2.4, 0.18, 10, "Hitscan");
	std::map<std::string, AttackData> ax52AttackDataMap = {};
	ax52AttackDataMap[ax52AttackData.attackName] = ax52AttackData;
	WeaponData data = WeaponData("AX-52", ax52AttackDataMap);

	return new Weapon(data);
}

Weapon *WeaponFactory::GetBratonVandal()
{
	std::vector<DamageValue> damageData = {DamageValue(DamageType::DT_IMPACT, 12.25), DamageValue(DamageType::DT_PUNCTURE, 1.75), DamageValue(DamageType::DT_SLASH, 21)};
	auto bratonVandalAttackData = AttackData(damageData, 0.16, 2, 0.16, 7.5, "Hitscan");
	std::map<std::string, AttackData> bratonVandalAttackDataMap = {};
	bratonVandalAttackDataMap[bratonVandalAttackData.attackName] = bratonVandalAttackData;
	WeaponData data = WeaponData("Dex Sybaris", bratonVandalAttackDataMap);

	return new Weapon(data);
}
