#include "src/Weapons/WeaponFactory.h"
#include "src/Mods/ModEffects/ConstantModEffect.h"

#include "src/DatabaseManagement/DatabaseManipulationFunctions.h"
#include "WeaponFactory.h"

#include "src/Services/ServiceLocator.h"

Weapon *WeaponFactory::GetNullWeapon()
{
	auto nullAttackData = AttackData({}, 0, 1, 0, 1, "Hitscan");
	std::map<std::string, AttackData> nullAttackDataMap = {};
	nullAttackDataMap[nullAttackData.attackName] = nullAttackData;
	WeaponData weaponData = WeaponData("Null Weapon", nullAttackDataMap);

	return new Weapon(weaponData);
}

Weapon *WeaponFactory::GetAX52()
{
	auto weaponAttackData = AttackData({DamageValue(DamageType::DT_PUNCTURE, 40)}, 0.26, 2.4, 0.18, 10, "Hitscan");
	std::map<std::string, AttackData> weaponAttackDataMap = {};
	weaponAttackDataMap[weaponAttackData.attackName] = weaponAttackData;
	WeaponData weaponData = WeaponData("AX-52", weaponAttackDataMap);

	return new Weapon(weaponData);
}

Weapon *WeaponFactory::GetBratonVandal()
{
	std::vector<DamageValue> damageData = {DamageValue(DamageType::DT_IMPACT, 12.25), DamageValue(DamageType::DT_PUNCTURE, 1.75), DamageValue(DamageType::DT_SLASH, 21)};
	auto weaponAttackData = AttackData(damageData, 0.16, 2, 0.16, 7.5, "Hitscan");
	std::map<std::string, AttackData> weaponAttackDataMap = {};
	weaponAttackDataMap[weaponAttackData.attackName] = weaponAttackData;
	WeaponData weaponData = WeaponData("Braton Vandal", weaponAttackDataMap);

	return new Weapon(weaponData);
}

Weapon *WeaponFactory::GetFulminPrime()
{
	std::vector<DamageValue> damageData = {DamageValue(DamageType::DT_PUNCTURE, 8), DamageValue(DamageType::DT_ELECTRICITY, 25)};
	auto weaponAttackData = AttackData(damageData, 0.34, 2.4, 0.10, 9.33, "Hitscan");
	std::map<std::string, AttackData> weaponAttackDataMap = {};
	weaponAttackDataMap[weaponAttackData.attackName] = weaponAttackData;
	WeaponData weaponData = WeaponData("Fulmin Prime", weaponAttackDataMap);

	return new Weapon(weaponData);
}

Weapon *WeaponFactory::GetNagantakaPrime()
{
	std::vector<DamageValue> damageData = {DamageValue(DamageType::DT_IMPACT, 1.7), DamageValue(DamageType::DT_PUNCTURE, 15.6), DamageValue(DamageType::DT_SLASH, 155.7)};
	auto weaponAttackData = AttackData(damageData, 0.25, 2.3, 0.39, 2.5, "Projectile");
	std::map<std::string, AttackData> weaponAttackDataMap = {};
	weaponAttackDataMap[weaponAttackData.attackName] = weaponAttackData;
	WeaponData weaponData = WeaponData("Nagantaka Prime", weaponAttackDataMap);

	return new Weapon(weaponData);
}

Weapon *WeaponFactory::GetLexPrime()
{
	std::vector<DamageValue> damageData = {DamageValue(DamageType::DT_IMPACT, 18), DamageValue(DamageType::DT_PUNCTURE, 144), DamageValue(DamageType::DT_SLASH, 18)};
	auto weaponAttackData = AttackData(damageData, 0.25, 2, 0.25, 2.08, "Hitscan");
	weaponAttackData.attackName = "Normal Attack";

	std::vector<DamageValue> incarnonDamageData = {DamageValue(DamageType::DT_IMPACT, 400), DamageValue(DamageType::DT_RADIATION, 800)};
	auto weaponIncarnonAttackData = AttackData(incarnonDamageData, 0.35, 3, 0.44, 0.67, "Projectile");
	weaponIncarnonAttackData.forcedProcs.push_back(ProcType::PT_KNOCKBACK);
	weaponIncarnonAttackData.projectileSpeed = 110;
	weaponIncarnonAttackData.damageFallOff = {{"StartRange", 10}, {"EndRange", 15}, {"Reduction", 0.667}};
	weaponIncarnonAttackData.attackName = "Incarnon";

	std::map<std::string, AttackData> weaponAttackDataMap = {};
	weaponAttackDataMap[weaponAttackData.attackName] = weaponAttackData;
	weaponAttackDataMap[weaponIncarnonAttackData.attackName] = weaponIncarnonAttackData;

	WeaponData weaponData = WeaponData("Lex Prime", weaponAttackDataMap);
	weaponData.weaponCategory = "Secondary";
	weaponData.equipSlot = "Secondary";
	weaponData.magazineSize = 8;
	weaponData.reloadTime = 2.35;
	weaponData.weaponFamily = "Lex";

	//std::vector<ModEffectBase *> incarnonEvo2ModEffects = {new ConstantModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_DAMAGE_AMOUNT, ModOperationType::ADD_TO_BASE_VALUE, 80)};
	//Mod *incarnonEvo2 = new Mod("Incarnon Evo 2", "Secondary", ModPolarity::AP_UNIVERSAL, 0, 0, 0, incarnonEvo2ModEffects);
	std::vector<ModEffectBase *> incarnonEvo4aModEffects = {new ConstantModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_CRIT_CHANCE, ModOperationType::ADD_TO_BASE_VALUE, 0.19)};
	Mod *incarnonEvo4a = new Mod("Incarnon Evo 4a", "Secondary", ModPolarity::AP_UNIVERSAL, 0, 0, 0, incarnonEvo4aModEffects);
	std::vector<ModEffectBase *> incarnonEvo4bModEffects = {new ConstantModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_CRIT_DAMAGE, ModOperationType::ADD_TO_BASE_VALUE, 0.4)};
	Mod *incarnonEvo4b = new Mod("Incarnon Evo 4b", "Secondary", ModPolarity::AP_UNIVERSAL, 0, 0, 0, incarnonEvo4bModEffects);

	//weaponData.innateUpgrades.push_back(incarnonEvo2);
	weaponData.innateUpgrades.push_back(incarnonEvo4a);
	weaponData.innateUpgrades.push_back(incarnonEvo4b);

	return new Weapon(weaponData);
}

Weapon *WeaponFactory::GetMK1Braton()
{
	std::vector<DamageValue> damageData = {DamageValue(DamageType::DT_IMPACT, 4.5), DamageValue(DamageType::DT_PUNCTURE, 4.5), DamageValue(DamageType::DT_SLASH, 9)};
	auto weaponAttackData = AttackData(damageData, 0.08, 1.5, 0.05, 7.5, "Hitscan");
	weaponAttackData.attackName = "Normal Attack";

	/*
	std::vector<DamageValue> incarnonDamageData = {DamageValue(DamageType::DT_IMPACT, 400), DamageValue(DamageType::DT_RADIATION, 800)};
	auto weaponIncarnonAttackData = AttackData(incarnonDamageData, 0.35, 3, 0.44, 0.67, "Projectile");
	weaponIncarnonAttackData.forcedProcs.push_back(ProcType::PT_KNOCKBACK);
	weaponIncarnonAttackData.projectileSpeed = 110;
	weaponIncarnonAttackData.damageFallOff = {{"StartRange", 10}, {"EndRange", 15}, {"Reduction", 0.667}};
	weaponIncarnonAttackData.attackName = "Incarnon";
	*/

	std::map<std::string, AttackData> weaponAttackDataMap = {};
	weaponAttackDataMap[weaponAttackData.attackName] = weaponAttackData;
	//weaponAttackDataMap[weaponIncarnonAttackData.attackName] = weaponIncarnonAttackData;

	WeaponData weaponData = WeaponData("MK1-Braton", weaponAttackDataMap);
	weaponData.id = 1232;
	weaponData.weaponCategory = "Primary";
	weaponData.equipSlot = "Primary";
	weaponData.compatabilityTags = {"ASSAULT_AMMO"};
	weaponData.magazineSize = 60;
	weaponData.ammoCapacity = 540;
	weaponData.reloadTime = 2;
	weaponData.weaponFamily = "Braton";
	weaponData.isLichWeapon = false;
	weaponData.rivenDisposition = 1.35;

	weaponData.normalModSlotCount = 8;
	weaponData.auraSlotCount = 0;
	weaponData.exilusSlotCount = 1;
	weaponData.arcaneSlotCount = 1;
	weaponData.modPolarities = {
		ModPolarity::AP_UNIVERSAL,ModPolarity::AP_UNIVERSAL,ModPolarity::AP_UNIVERSAL,ModPolarity::AP_UNIVERSAL,ModPolarity::AP_UNIVERSAL,ModPolarity::AP_UNIVERSAL,ModPolarity::AP_UNIVERSAL,ModPolarity::AP_UNIVERSAL,
		ModPolarity::AP_TACTIC,
		ModPolarity::AP_UNIVERSAL
	};

	// Evolution 2 options
	std::vector<ModEffectBase *> incarnonEvo2aModEffects = {
		new ConstantModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_DAMAGE_AMOUNT, ModOperationType::ADD_TO_BASE_VALUE, 28)
	};
	Mod *incarnonEvo2a = new Mod("Incarnon Evo 2a", "Primary", ModPolarity::AP_UNIVERSAL, 0, 0, 0, incarnonEvo2aModEffects);
	std::vector<ModEffectBase *> incarnonEvo2bModEffects = {
		new ConstantModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_DAMAGE_AMOUNT, ModOperationType::ADD_TO_BASE_VALUE, 20),
		new ConstantModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_MULTISHOT, ModOperationType::STACKING_MULTIPLY, 0.2)
	};
	Mod *incarnonEvo2b = new Mod("Incarnon Evo 2b", "Primary", ModPolarity::AP_UNIVERSAL, 0, 0, 0, incarnonEvo2bModEffects);
	std::vector<Mod *> evo2Options{incarnonEvo2a, incarnonEvo2b};

	// Evolution 3 options
	std::vector<ModEffectBase *> incarnonEvo3aModEffects = {
		new ConstantModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_AMMO_MAXIMUM, ModOperationType::ADD_TO_BASE_VALUE, 60)
	};
	Mod *incarnonEvo3a = new Mod("Incarnon Evo 2a", "Primary", ModPolarity::AP_UNIVERSAL, 0, 0, 0, incarnonEvo3aModEffects);
	std::vector<ModEffectBase *> incarnonEvo3bModEffects = {
		new ConstantModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_SPREAD, ModOperationType::STACKING_MULTIPLY, -0.6),
		new ConstantModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_RECOIL, ModOperationType::STACKING_MULTIPLY, -0.6)
	};
	Mod *incarnonEvo3b = new Mod("Incarnon Evo 2b", "Primary", ModPolarity::AP_UNIVERSAL, 0, 0, 0, incarnonEvo3bModEffects);
	std::vector<ModEffectBase *> incarnonEvo3cModEffects = {
		
	};
	Mod *incarnonEvo3c = new Mod("Incarnon Evo 2c", "Primary", ModPolarity::AP_UNIVERSAL, 0, 0, 0, incarnonEvo3cModEffects);
	std::vector<Mod *> evo3Options{incarnonEvo3a, incarnonEvo3b, incarnonEvo3c};

	// Evolution 4 options
	std::vector<ModEffectBase *> incarnonEvo4aModEffects = {
		new ConstantModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_CRIT_CHANCE, ModOperationType::ADD_TO_BASE_VALUE, 0.18),
		new ConstantModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_CRIT_DAMAGE, ModOperationType::ADD_TO_BASE_VALUE, 0.5)
	};
	Mod *incarnonEvo4a = new Mod("Incarnon Evo 4a", "Primary", ModPolarity::AP_UNIVERSAL, 0, 0, 0, incarnonEvo4aModEffects);
	std::vector<ModEffectBase *> incarnonEvo4bModEffects = {
		new ConstantModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_CRIT_DAMAGE, ModOperationType::ADD_TO_BASE_VALUE, 3.3)	// I need to still add the conditional requirement to this, but it will at least provide the numbers
	};
	Mod *incarnonEvo4b = new Mod("Incarnon Evo 4b", "Primary", ModPolarity::AP_UNIVERSAL, 0, 0, 0, incarnonEvo4bModEffects);
	std::vector<ModEffectBase *> incarnonEvo4cModEffects = {
		new ConstantModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_CRIT_CHANCE, ModOperationType::ADD_TO_BASE_VALUE, 0.1),
		new ConstantModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_STATUS_CHANCE, ModOperationType::ADD_TO_BASE_VALUE, 0.12)
	};
	Mod *incarnonEvo4c = new Mod("Incarnon Evo 4c", "Primary", ModPolarity::AP_UNIVERSAL, 0, 0, 0, incarnonEvo4cModEffects);
	std::vector<Mod *> evo4Options{incarnonEvo4a, incarnonEvo4b, incarnonEvo4c};

	weaponData.incarnonUpgrades = Incarnon({evo2Options, evo3Options, evo4Options});

	return new Weapon(weaponData);
}

Weapon *WeaponFactory::GetWeapon(std::string name)
{
	std::string databaseData;
	return CreateWeapon(databaseData);
}

Weapon *WeaponFactory::CreateWeapon(std::string databaseData)
{
	// Currently the weaponData should be in the BaseWeaponData form
	auto categoryDataPairs = DatabaseManipulationFunctions::ExtractCategoryDataPairs(databaseData);
	return nullptr;
}
