#include "src/Weapons/WeaponFactory.h"
#include "src/Mods/ModEffects/ConstantModEffect.h"
#include "src/Mods/ModEffects/ConditionalModEffectWrapper.h"

#include "src/DatabaseManagement/DatabaseManipulationFunctions.h"
#include "WeaponFactory.h"

#include "src/Services/ServiceLocator.h"

Weapon *WeaponFactory::GetNullWeapon()
{
	std::map<DamageType, float> nullDamageProportionMap = {{DamageType::DT_ANY, 0}};
	DamageData nullDamageData{nullDamageProportionMap, 0, HitType::HITSCAN, 0, 1, 0, 1};
	AttackData nullAttackData{nullDamageData};
	std::string firingModeName = "Normal Attack";
	FiringMode nullFiringMode{firingModeName, nullAttackData};
	nullFiringMode.fireRate = 1;
	nullFiringMode.reloadTime = 1;
	nullFiringMode.ammoShotRequirement = 1;

	WeaponData nullWeaponData{"Null Weapon", {{firingModeName, nullFiringMode}}};
	nullWeaponData.id = 0;
	nullWeaponData.ammoCapacity = 1;
	nullWeaponData.ammoClipSize = 1;
	return new Weapon(nullWeaponData);
}
/*
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
	std::vector<DamageValue> damageValues = {DamageValue(DamageType::DT_IMPACT, 12.25), DamageValue(DamageType::DT_PUNCTURE, 1.75), DamageValue(DamageType::DT_SLASH, 21)};
	auto weaponAttackData = AttackData(damageValues, 0.16, 2, 0.16, 7.5, "Hitscan");
	std::map<std::string, AttackData> weaponAttackDataMap = {};
	weaponAttackDataMap[weaponAttackData.attackName] = weaponAttackData;
	WeaponData weaponData = WeaponData("Braton Vandal", weaponAttackDataMap);

	return new Weapon(weaponData);
}

Weapon *WeaponFactory::GetFulminPrime()
{
	std::vector<DamageValue> damageValues = {DamageValue(DamageType::DT_PUNCTURE, 8), DamageValue(DamageType::DT_ELECTRICITY, 25)};
	auto weaponAttackData = AttackData(damageValues, 0.34, 2.4, 0.10, 9.33, "Hitscan");
	std::map<std::string, AttackData> weaponAttackDataMap = {};
	weaponAttackDataMap[weaponAttackData.attackName] = weaponAttackData;
	WeaponData weaponData = WeaponData("Fulmin Prime", weaponAttackDataMap);

	return new Weapon(weaponData);
}

Weapon *WeaponFactory::GetNagantakaPrime()
{
	std::vector<DamageValue> damageValues = {DamageValue(DamageType::DT_IMPACT, 1.7), DamageValue(DamageType::DT_PUNCTURE, 15.6), DamageValue(DamageType::DT_SLASH, 155.7)};
	auto weaponAttackData = AttackData(damageValues, 0.25, 2.3, 0.39, 2.5, "Projectile");
	std::map<std::string, AttackData> weaponAttackDataMap = {};
	weaponAttackDataMap[weaponAttackData.attackName] = weaponAttackData;
	WeaponData weaponData = WeaponData("Nagantaka Prime", weaponAttackDataMap);

	return new Weapon(weaponData);
}
*/

Weapon *WeaponFactory::GetExergis()
{
	// Configure data for normal attack
	std::map<DamageType, float> normalDamageProportionMap = {{DamageType::DT_IMPACT, 0.037037}, {DamageType::DT_PUNCTURE, 0.2222222}, {DamageType::DT_SLASH, 0.481481}, {DamageType::DT_RADIATION, 0.259259}};
	DamageData normalDamageData{normalDamageProportionMap, 540, HitType::HITSCAN, 0.08, 1.4, 1.08, 3};
	AttackData normalAttackData{normalDamageData};
	std::string normalFiringModeName = "Normal Attack";
	FiringMode normalFiringMode{normalFiringModeName, normalAttackData};
	normalFiringMode.fireRate = 3.33;
	normalFiringMode.reloadTime = 1.6;
	normalFiringMode.ammoShotRequirement = 1;

	WeaponData weaponData{"Exergis", {{normalFiringModeName, normalFiringMode}}};

	weaponData.id = 1211;
	weaponData.inventorySlot = "Primary";
	weaponData.compatabilityTags = {"PROJECTILE","SINGLESHOT","SEMI_AUTO"};
	weaponData.ammoClipSize = 1;
	weaponData.ammoCapacity = 47;
	weaponData.parent = "/Lotus/Weapons/Tenno/Shotgun/LotusStandardShotgun";
	weaponData.parents = {
		"/Lotus/Weapons/Tenno/Shotgun/LotusStandardShotgun",
		"/Lotus/Weapons/Tenno/Shotgun/LotusShotgun",
		"/Lotus/Weapons/Tenno/LotusLongGun",
		"/Lotus/Weapons/Tenno/LotusBulletWeapon"};
	weaponData.path = "/Lotus/Weapons/Corpus/LongGuns/CrpShapeBlast/CrpShapeBlastShotgun";
	weaponData.productCategory = "LongGuns";
	weaponData.isKuva = false;
	weaponData.omegaAttenuation = 1.1;

	weaponData.normalModSlotCount = 8;
	weaponData.auraSlotCount = 0;
	weaponData.exilusSlotCount = 1;
	weaponData.arcaneSlotCount = 1;
	weaponData.modPolarities = {
		ModPolarity::AP_DEFENSE, ModPolarity::AP_UNIVERSAL, ModPolarity::AP_UNIVERSAL, ModPolarity::AP_UNIVERSAL, ModPolarity::AP_UNIVERSAL, ModPolarity::AP_UNIVERSAL, ModPolarity::AP_UNIVERSAL, ModPolarity::AP_UNIVERSAL,
		ModPolarity::AP_ATTACK,
		ModPolarity::AP_UNIVERSAL};

	// Incarnon Evolution Definitions
	weaponData.incarnonUpgrades = Incarnon();

	return new Weapon(weaponData);
}

Weapon *WeaponFactory::GetLexPrime()
{
	// Configure data for normal attack
	std::map<DamageType, float> normalDamageProportionMap = {{DamageType::DT_IMPACT, 0.1}, {DamageType::DT_PUNCTURE, 0.8}, {DamageType::DT_SLASH, 0.1}};
	DamageData normalDamageData{normalDamageProportionMap, 180, HitType::HITSCAN, 0.25, 2, 0.25, 1};
	AttackData normalAttackData{normalDamageData};
	std::string normalFiringModeName = "Normal Attack";
	FiringMode normalFiringMode{normalFiringModeName, normalAttackData};
	normalFiringMode.fireRate = 2.08;
	normalFiringMode.reloadTime = 2.35;
	normalFiringMode.ammoShotRequirement = 1;

	// Configure data for incarnon attack
	// First the direct hit
	std::map<DamageType, float> incarnonDirectHitDamageProportionMap = {{DamageType::DT_IMPACT, 0.33333333}, {DamageType::DT_RADIATION, 0.66666666}};
	DamageData incarnonDirectHitDamageData{incarnonDirectHitDamageProportionMap, 1200, HitType::PROJECTILE, 0.35, 3, 0.44, 1};
	incarnonDirectHitDamageData.forcedProcs.push_back(ProcType::PT_KNOCKBACK);
	AttackData incarnonAttackData{incarnonDirectHitDamageData};
	std::string incarnonFiringModeName = "Incarnon";
	FiringMode incarnonFiringMode{incarnonFiringModeName, incarnonAttackData};
	incarnonFiringMode.fireRate = 0.67;
	incarnonFiringMode.reloadTime = 2.35;
	incarnonFiringMode.ammoShotRequirement = 1;

	WeaponData weaponData{"Lex Prime", {{normalFiringModeName, normalFiringMode}, {incarnonFiringModeName, incarnonFiringMode}}};

	weaponData.id = 1211;
	weaponData.inventorySlot = "Secondary";
	weaponData.compatabilityTags = {"SEMI_AUTO"};
	weaponData.ammoClipSize = 8;
	weaponData.ammoCapacity = 210;
	weaponData.parent = "/Lotus/Weapons/Tenno/Pistol/HeavyPistol";
	weaponData.parents = {
		"/Lotus/Weapons/Tenno/Pistol/HeavyPistol",
		"/Lotus/Weapons/Tenno/Pistol/LotusSinglePistolGun",
		"/Lotus/Weapons/Tenno/Pistol/LotusSinglePistol",
		"/Lotus/Weapons/Tenno/Pistol/LotusPistol"};
	weaponData.path = "/Lotus/Weapons/Tenno/Pistols/PrimeLex/PrimeLex";
	weaponData.productCategory = "Pistols";
	weaponData.isKuva = false;
	weaponData.omegaAttenuation = 1.2;

	weaponData.normalModSlotCount = 8;
	weaponData.auraSlotCount = 0;
	weaponData.exilusSlotCount = 1;
	weaponData.arcaneSlotCount = 1;
	weaponData.modPolarities = {
		ModPolarity::AP_UNIVERSAL, ModPolarity::AP_UNIVERSAL, ModPolarity::AP_UNIVERSAL, ModPolarity::AP_UNIVERSAL, ModPolarity::AP_UNIVERSAL, ModPolarity::AP_UNIVERSAL, ModPolarity::AP_UNIVERSAL, ModPolarity::AP_ATTACK,
		ModPolarity::AP_TACTIC,
		ModPolarity::AP_UNIVERSAL};

	// Incarnon Evolution Definitions
	{
		// Evolution 2 options
		std::vector<ModEffectBase *> incarnonEvo2aModEffects = {
			new ConstantModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_DAMAGE_AMOUNT, ModOperationType::ADD_TO_BASE_VALUE, 20),
			new ConditionalModEffect(*new ConstantModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_DAMAGE_AMOUNT, ModOperationType::ADD_TO_BASE_VALUE, 80), Conditional::onShieldBreak)};
		Mod *incarnonEvo2a = new Mod("Incarnon Evo 2a", "Primary", ModPolarity::AP_UNIVERSAL, 0, 0, 0, incarnonEvo2aModEffects);
		std::vector<ModEffectBase *> incarnonEvo2bModEffects = {
			new ConstantModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_DAMAGE_AMOUNT, ModOperationType::ADD_TO_BASE_VALUE, 20),
			new ConditionalModEffect(*new ConstantModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_AMMO_CONSUME_RATE, ModOperationType::ADD, -0.6), Conditional::whileChanneledAbility)};
		Mod *incarnonEvo2b = new Mod("Incarnon Evo 2b", "Primary", ModPolarity::AP_UNIVERSAL, 0, 0, 0, incarnonEvo2bModEffects);
		std::vector<Mod *> evo2Options{incarnonEvo2a, incarnonEvo2b};

		// Evolution 3 options
		std::vector<ModEffectBase *> incarnonEvo3aModEffects = {
			new ConditionalModEffect(*new ConstantModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_SPREAD, ModOperationType::STACKING_MULTIPLY, -0.8), Conditional::onHeadshot),	// This ignores the fact it is actually -0.2 stacking up to 4 times
			new ConditionalModEffect(*new ConstantModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_RECOIL, ModOperationType::STACKING_MULTIPLY, -0.8), Conditional::onHeadshot)
		};
		Mod *incarnonEvo3a = new Mod("Incarnon Evo 3a", "Primary", ModPolarity::AP_UNIVERSAL, 0, 0, 0, incarnonEvo3aModEffects);
		std::vector<ModEffectBase *> incarnonEvo3bModEffects = {
			new ConstantModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_MAGAZINE_CAPACITY, ModOperationType::ADD_TO_BASE_VALUE, 10)};
		Mod *incarnonEvo3b = new Mod("Incarnon Evo 3b", "Primary", ModPolarity::AP_UNIVERSAL, 0, 0, 0, incarnonEvo3bModEffects);
		std::vector<ModEffectBase *> incarnonEvo3cModEffects = {
			new ConditionalModEffect(*new ConstantModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_RELOAD_SPEED, ModOperationType::STACKING_MULTIPLY, 1), Conditional::onReloadFromEmpty)
		};
		Mod *incarnonEvo3c = new Mod("Incarnon Evo 3c", "Primary", ModPolarity::AP_UNIVERSAL, 0, 0, 0, incarnonEvo3cModEffects);
		std::vector<Mod *> evo3Options{incarnonEvo3a, incarnonEvo3b, incarnonEvo3c};

		// Evolution 4 options
		std::vector<ModEffectBase *> incarnonEvo4aModEffects = {
			new ConditionalModEffect(*new ConstantModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_HEADSHOT_MULTIPLIER, ModOperationType::STACKING_MULTIPLY, 1), Conditional::onEquip)
		};
		Mod *incarnonEvo4a = new Mod("Incarnon Evo 4a", "Primary", ModPolarity::AP_UNIVERSAL, 0, 0, 0, incarnonEvo4aModEffects);
		std::vector<ModEffectBase *> incarnonEvo4bModEffects = {
			new ConstantModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_STATUS_CHANCE, ModOperationType::ADD_TO_BASE_VALUE, 0.3)
		};
		Mod *incarnonEvo4b = new Mod("Incarnon Evo 4b", "Primary", ModPolarity::AP_UNIVERSAL, 0, 0, 0, incarnonEvo4bModEffects);
		std::vector<ModEffectBase *> incarnonEvo4cModEffects = {
			new ConstantModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_CRIT_CHANCE, ModOperationType::ADD_TO_BASE_VALUE, 0.19),
			new ConstantModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_CRIT_DAMAGE, ModOperationType::ADD_TO_BASE_VALUE, 0.4)};
		Mod *incarnonEvo4c = new Mod("Incarnon Evo 4c", "Primary", ModPolarity::AP_UNIVERSAL, 0, 0, 0, incarnonEvo4cModEffects);
		std::vector<Mod *> evo4Options{incarnonEvo4a, incarnonEvo4b, incarnonEvo4c};

		weaponData.incarnonUpgrades = Incarnon({evo2Options, evo3Options, evo4Options});
	}

	return new Weapon(weaponData);
}

Weapon *WeaponFactory::GetMK1Braton()
{
	// Configure data for normal attack
	std::map<DamageType, float> normalDamageProportionMap = {{DamageType::DT_IMPACT, 0.25}, {DamageType::DT_PUNCTURE, 0.25}, {DamageType::DT_SLASH, 0.5}};
	DamageData normalDamageData{normalDamageProportionMap, 18, HitType::HITSCAN, 0.08, 1.5, 0.05, 1};
	AttackData normalAttackData{normalDamageData};
	std::string normalFiringModeName = "Normal Attack";
	FiringMode normalFiringMode{normalFiringModeName, normalAttackData};
	normalFiringMode.fireRate = 7.5;
	normalFiringMode.reloadTime = 2;
	normalFiringMode.ammoShotRequirement = 1;

	// Configure data for incarnon attack
	// First the direct hit
	std::map<DamageType, float> incarnonDirectHitDamageProportionMap = {{DamageType::DT_IMPACT, 0.4}, {DamageType::DT_PUNCTURE, 0.04}, {DamageType::DT_SLASH, 0.56}};
	DamageData incarnonDirectHitDamageData{incarnonDirectHitDamageProportionMap, 50, HitType::HITSCAN, 0.20, 2.4, 0.10, 1};
	// Then the radial sub-attack
	std::map<DamageType, float> incarnonRadialDamageProportionMap = {{DamageType::DT_FIRE, 1}};
	DamageData incarnonRadialDamageData{incarnonRadialDamageProportionMap, 50, HitType::RADIAL, 0.20, 2.4, 0.10, 1};
	AttackData incarnonAttackData{incarnonDirectHitDamageData, {incarnonRadialDamageData}};
	std::string incarnonFiringModeName = "Incarnon";
	FiringMode incarnonFiringMode{incarnonFiringModeName, incarnonAttackData};
	incarnonFiringMode.fireRate = 5;
	incarnonFiringMode.reloadTime = 2;
	incarnonFiringMode.ammoShotRequirement = 1;

	WeaponData weaponData{"MK1-Braton", {{normalFiringModeName, normalFiringMode}, {incarnonFiringModeName, incarnonFiringMode}}};

	weaponData.id = 1232;
	weaponData.inventorySlot = "Primary";
	weaponData.compatabilityTags = {"ASSAULT_AMMO"};
	weaponData.ammoClipSize = 60;
	weaponData.ammoCapacity = 540;
	weaponData.parent = "/Lotus/Weapons/Tenno/Rifle/Rifle";
	weaponData.parents = {
		"/Lotus/Weapons/Tenno/Rifle/Rifle",
		"/Lotus/Weapons/Tenno/Rifle/LotusAssaultStandardRifle",
		"/Lotus/Weapons/Tenno/Rifle/LotusAssaultRifle",
		"/Lotus/Weapons/Tenno/Rifle/LotusRifle",
		"/Lotus/Weapons/Tenno/LotusLongGun",
		"/Lotus/Weapons/Tenno/LotusBulletWeapon"};
	weaponData.path = "/Lotus/Weapons/Tenno/Rifle/StartingRifle";
	weaponData.productCategory = "LongGuns";
	weaponData.isKuva = false;
	weaponData.omegaAttenuation = 1.35;

	weaponData.normalModSlotCount = 8;
	weaponData.auraSlotCount = 0;
	weaponData.exilusSlotCount = 1;
	weaponData.arcaneSlotCount = 1;
	weaponData.modPolarities = {
		ModPolarity::AP_UNIVERSAL, ModPolarity::AP_UNIVERSAL, ModPolarity::AP_UNIVERSAL, ModPolarity::AP_UNIVERSAL, ModPolarity::AP_UNIVERSAL, ModPolarity::AP_UNIVERSAL, ModPolarity::AP_UNIVERSAL, ModPolarity::AP_UNIVERSAL,
		ModPolarity::AP_TACTIC,
		ModPolarity::AP_UNIVERSAL};

	// Incarnon Evolution Definitions
	{
		// Evolution 2 options
		std::vector<ModEffectBase *> incarnonEvo2aModEffects = {
			new ConstantModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_DAMAGE_AMOUNT, ModOperationType::ADD_TO_BASE_VALUE, 28),
			new ConditionalModEffect(*new ConstantModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_DAMAGE_AMOUNT, ModOperationType::ADD_TO_BASE_VALUE, 22), Conditional::whileChanneledAbility), // This one is conditional to channeling
			new ConditionalModEffect(*new ConstantModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_AMMO_CONSUME_RATE, ModOperationType::ADD, -0.5), Conditional::whileChanneledAbility)			 // This one is conditional to channeling
		};
		Mod *incarnonEvo2a = new Mod("Incarnon Evo 2a", "Primary", ModPolarity::AP_UNIVERSAL, 0, 0, 0, incarnonEvo2aModEffects);
		std::vector<ModEffectBase *> incarnonEvo2bModEffects = {
			new ConstantModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_DAMAGE_AMOUNT, ModOperationType::ADD_TO_BASE_VALUE, 20),
			new ConstantModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_MULTISHOT, ModOperationType::STACKING_MULTIPLY, 0.2)};
		Mod *incarnonEvo2b = new Mod("Incarnon Evo 2b", "Primary", ModPolarity::AP_UNIVERSAL, 0, 0, 0, incarnonEvo2bModEffects);
		std::vector<Mod *> evo2Options{incarnonEvo2a, incarnonEvo2b};

		// Evolution 3 options
		std::vector<ModEffectBase *> incarnonEvo3aModEffects = {
			new ConstantModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_AMMO_MAXIMUM, ModOperationType::ADD_TO_BASE_VALUE, 60)};
		Mod *incarnonEvo3a = new Mod("Incarnon Evo 3a", "Primary", ModPolarity::AP_UNIVERSAL, 0, 0, 0, incarnonEvo3aModEffects);
		std::vector<ModEffectBase *> incarnonEvo3bModEffects = {
			new ConstantModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_SPREAD, ModOperationType::STACKING_MULTIPLY, -0.6),
			new ConstantModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_RECOIL, ModOperationType::STACKING_MULTIPLY, -0.6)};
		Mod *incarnonEvo3b = new Mod("Incarnon Evo 3b", "Primary", ModPolarity::AP_UNIVERSAL, 0, 0, 0, incarnonEvo3bModEffects);
		std::vector<ModEffectBase *> incarnonEvo3cModEffects = {
			// Refill ammo on punch through hit
		};
		Mod *incarnonEvo3c = new Mod("Incarnon Evo 3c", "Primary", ModPolarity::AP_UNIVERSAL, 0, 0, 0, incarnonEvo3cModEffects);
		std::vector<Mod *> evo3Options{incarnonEvo3a, incarnonEvo3b, incarnonEvo3c};

		// Evolution 4 options
		std::vector<ModEffectBase *> incarnonEvo4aModEffects = {
			new ConstantModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_CRIT_CHANCE, ModOperationType::ADD_TO_BASE_VALUE, 0.18),
			new ConstantModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_CRIT_DAMAGE, ModOperationType::ADD_TO_BASE_VALUE, 0.5)};
		Mod *incarnonEvo4a = new Mod("Incarnon Evo 4a", "Primary", ModPolarity::AP_UNIVERSAL, 0, 0, 0, incarnonEvo4aModEffects);
		std::vector<ModEffectBase *> incarnonEvo4bModEffects = {
			new ConstantModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_CRIT_DAMAGE, ModOperationType::ADD_TO_BASE_VALUE, 3.3) // I need to still add the conditional requirement to this, but it will at least provide the numbers
		};
		Mod *incarnonEvo4b = new Mod("Incarnon Evo 4b", "Primary", ModPolarity::AP_UNIVERSAL, 0, 0, 0, incarnonEvo4bModEffects);
		std::vector<ModEffectBase *> incarnonEvo4cModEffects = {
			new ConstantModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_CRIT_CHANCE, ModOperationType::ADD_TO_BASE_VALUE, 0.1),
			new ConstantModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_STATUS_CHANCE, ModOperationType::ADD_TO_BASE_VALUE, 0.12)};
		Mod *incarnonEvo4c = new Mod("Incarnon Evo 4c", "Primary", ModPolarity::AP_UNIVERSAL, 0, 0, 0, incarnonEvo4cModEffects);
		std::vector<Mod *> evo4Options{incarnonEvo4a, incarnonEvo4b, incarnonEvo4c};

		weaponData.incarnonUpgrades = Incarnon({evo2Options, evo3Options, evo4Options});
	}

	auto newWeapon = new Weapon(weaponData);

	return newWeapon;
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
