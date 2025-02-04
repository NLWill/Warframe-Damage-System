#include "src/Weapons/WeaponFactory.h"
#include "src/Mods/ModEffects/ConstantModEffect.h"

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

Weapon *WeaponFactory::GetLexPrime()
{
	std::vector<DamageValue> damageData = {DamageValue(DamageType::DT_IMPACT, 18), DamageValue(DamageType::DT_PUNCTURE, 144), DamageValue(DamageType::DT_SLASH, 18)};
	auto weaponAttackData = AttackData(damageData, 0.25, 2, 0.25, 2.08, "Hitscan");
	weaponAttackData.attackName = "Normal Attack";

	std::vector<DamageValue> incarnonDamageData = {DamageValue(DamageType::DT_IMPACT, 400), DamageValue(DamageType::DT_RADIATION, 800)};
	auto weaponIncarnonAttackData = AttackData(incarnonDamageData, 0.35, 3, 0.44, 0.67, "Projectile");
	weaponIncarnonAttackData.forcedProcs.push_back(StatusEffect::PT_KNOCKBACK);
	weaponIncarnonAttackData.projectileSpeed = 110;
	weaponIncarnonAttackData.damageFallOff = {{"StartRange", 10}, {"EndRange", 15}, {"Reduction", 0.667}};
	weaponIncarnonAttackData.attackName = "Incarnon";

	std::map<std::string, AttackData> weaponAttackDataMap = {};
	weaponAttackDataMap[weaponAttackData.attackName] = weaponAttackData;
	weaponAttackDataMap[weaponIncarnonAttackData.attackName] = weaponIncarnonAttackData;

	WeaponData data = WeaponData("Lex Prime", weaponAttackDataMap);
	data.weaponCategory = "Secondary";
	data.equipSlot = "Secondary";
	data.magazineSize = 8;
	data.reloadTime = 2.35;
	data.weaponFamily = "Lex";

	//std::vector<ModEffectBase *> incarnonEvo2ModEffects = {new ConstantModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_DAMAGE_AMOUNT, ModOperationType::ADD_TO_BASE_VALUE, 20)};
	//Mod *incarnonEvo2 = new Mod("Incarnon Evo 2", "Secondary", ModPolarity::NONE, 0, 0, 0, incarnonEvo2ModEffects);
	std::vector<ModEffectBase *> incarnonEvo4aModEffects = {new ConstantModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_CRIT_CHANCE, ModOperationType::ADD_TO_BASE_VALUE, 0.19)};
	Mod *incarnonEvo4a = new Mod("Incarnon Evo 4a", "Secondary", ModPolarity::AP_NONE, 0, 0, 0, incarnonEvo4aModEffects);
	std::vector<ModEffectBase *> incarnonEvo4bModEffects = {new ConstantModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_CRIT_DAMAGE, ModOperationType::ADD_TO_BASE_VALUE, 0.4)};
	Mod *incarnonEvo4b = new Mod("Incarnon Evo 4b", "Secondary", ModPolarity::AP_NONE, 0, 0, 0, incarnonEvo4bModEffects);

	//data.innateUpgrades.push_back(incarnonEvo2);
	data.innateUpgrades.push_back(incarnonEvo4a);
	data.innateUpgrades.push_back(incarnonEvo4b);

	return new Weapon(data);
}
