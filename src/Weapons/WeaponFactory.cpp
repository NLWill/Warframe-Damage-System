#include "src/Weapons/WeaponFactory.h"

#include "src/Mods/ModEffects/ConstantModEffect.h"
#include "src/Mods/ModEffects/ConditionalModEffectWrapper.h"

#include "src/Mods/ModManager.h"

#include "src/DatabaseManagement/DatabaseManipulationFunctions.h"

#include "src/Services/ServiceLocator.h"

std::shared_ptr<Weapon> WeaponFactory::GetNullWeapon()
{
	std::map<DamageType, float> nullDamageProportionMap = {{DamageType::DT_ANY, 1}};
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
	nullWeaponData.omegaAttenuation = 1.5;

	std::vector<std::pair<ModSlotType, ModPolarity>> modSlotDetails = {
		{ModSlotType::MST_NORMAL, ModPolarity::AP_UNIVERSAL},
		{ModSlotType::MST_NORMAL, ModPolarity::AP_UNIVERSAL},
		{ModSlotType::MST_NORMAL, ModPolarity::AP_UNIVERSAL},
		{ModSlotType::MST_NORMAL, ModPolarity::AP_UNIVERSAL},
		{ModSlotType::MST_NORMAL, ModPolarity::AP_UNIVERSAL},
		{ModSlotType::MST_NORMAL, ModPolarity::AP_UNIVERSAL},
		{ModSlotType::MST_NORMAL, ModPolarity::AP_UNIVERSAL},
		{ModSlotType::MST_NORMAL, ModPolarity::AP_UNIVERSAL},
		{ModSlotType::MST_EXILUS, ModPolarity::AP_UNIVERSAL},
		{ModSlotType::MST_ARCANE, ModPolarity::AP_UNIVERSAL},
	};

	auto modManager = std::make_shared<ModManager>(modSlotDetails, nullWeaponData.compatabilityTags, nullWeaponData.parents);

	return std::make_shared<Weapon>(nullWeaponData, modManager);
}
/*
std::shared_ptr<Weapon> WeaponFactory::GetAX52()
{
	auto weaponAttackData = AttackData({DamageValue(DamageType::DT_PUNCTURE, 40)}, 0.26, 2.4, 0.18, 10, "Hitscan");
	std::map<std::string, AttackData> weaponAttackDataMap = {};
	weaponAttackDataMap[weaponAttackData.attackName] = weaponAttackData;
	WeaponData weaponData = WeaponData("AX-52", weaponAttackDataMap);

	return std::make_shared<Weapon>(weaponData);
}

std::shared_ptr<Weapon> WeaponFactory::GetBratonVandal()
{
	std::vector<DamageValue> damageValues = {DamageValue(DamageType::DT_IMPACT, 12.25), DamageValue(DamageType::DT_PUNCTURE, 1.75), DamageValue(DamageType::DT_SLASH, 21)};
	auto weaponAttackData = AttackData(damageValues, 0.16, 2, 0.16, 7.5, "Hitscan");
	std::map<std::string, AttackData> weaponAttackDataMap = {};
	weaponAttackDataMap[weaponAttackData.attackName] = weaponAttackData;
	WeaponData weaponData = WeaponData("Braton Vandal", weaponAttackDataMap);

	return std::make_shared<Weapon>(weaponData);
}

std::shared_ptr<Weapon> WeaponFactory::GetFulminPrime()
{
	std::vector<DamageValue> damageValues = {DamageValue(DamageType::DT_PUNCTURE, 8), DamageValue(DamageType::DT_ELECTRICITY, 25)};
	auto weaponAttackData = AttackData(damageValues, 0.34, 2.4, 0.10, 9.33, "Hitscan");
	std::map<std::string, AttackData> weaponAttackDataMap = {};
	weaponAttackDataMap[weaponAttackData.attackName] = weaponAttackData;
	WeaponData weaponData = WeaponData("Fulmin Prime", weaponAttackDataMap);

	return std::make_shared<Weapon>(weaponData);
}

std::shared_ptr<Weapon> WeaponFactory::GetNagantakaPrime()
{
	std::vector<DamageValue> damageValues = {DamageValue(DamageType::DT_IMPACT, 1.7), DamageValue(DamageType::DT_PUNCTURE, 15.6), DamageValue(DamageType::DT_SLASH, 155.7)};
	auto weaponAttackData = AttackData(damageValues, 0.25, 2.3, 0.39, 2.5, "Projectile");
	std::map<std::string, AttackData> weaponAttackDataMap = {};
	weaponAttackDataMap[weaponAttackData.attackName] = weaponAttackData;
	WeaponData weaponData = WeaponData("Nagantaka Prime", weaponAttackDataMap);

	return std::make_shared<Weapon>(weaponData);
}
*/

std::shared_ptr<Weapon> WeaponFactory::GetDaikyu()
{
	// Configure data for normal attack
	std::map<DamageType, float> normalDamageProportionMap = {{DamageType::DT_IMPACT, 0.3}, {DamageType::DT_PUNCTURE, 0.4}, {DamageType::DT_SLASH, 0.3}};
	DamageData normalDamageData{normalDamageProportionMap, 700, HitType::HITSCAN, 0.34, 2, 0.46, 1};
	AttackData normalAttackData{normalDamageData};
	std::string normalFiringModeName = "Normal Attack";
	FiringMode normalFiringMode{normalFiringModeName, normalAttackData};
	normalFiringMode.fireRate = 1;
	normalFiringMode.reloadTime = 0.6;
	normalFiringMode.ammoShotRequirement = 1;

	WeaponData weaponData{"Daikyu", {{normalFiringModeName, normalFiringMode}}};

	weaponData.id = 1072;
	weaponData.inventorySlot = "Primary";
	weaponData.compatabilityTags = {"PROJECTILE", "DAIKYU"};
	weaponData.ammoClipSize = 1;
	weaponData.ammoCapacity = 47;
	weaponData.parent = "/Lotus/Weapons/Tenno/Bows/LotusLongBow";
	weaponData.parents = {
		"/Lotus/Weapons/Tenno/Bows/LotusLongBow",
		"/Lotus/Weapons/Tenno/Bows/LotusBow",
		"/Lotus/Weapons/Tenno/Rifle/LotusRifle",
		"/Lotus/Weapons/Tenno/LotusLongGun",
		"/Lotus/Weapons/Tenno/LotusBulletWeapon"};
	weaponData.path = "/Lotus/Weapons/Tenno/Bows/AsymetricalBow/AsymetricalBow";
	weaponData.productCategory = "LongGuns";
	weaponData.isKuva = false;
	weaponData.omegaAttenuation = 1.25;

	std::vector<std::pair<ModSlotType, ModPolarity>> modSlotDetails = {
		{ModSlotType::MST_NORMAL, ModPolarity::AP_UNIVERSAL},
		{ModSlotType::MST_NORMAL, ModPolarity::AP_UNIVERSAL},
		{ModSlotType::MST_NORMAL, ModPolarity::AP_UNIVERSAL},
		{ModSlotType::MST_NORMAL, ModPolarity::AP_UNIVERSAL},
		{ModSlotType::MST_NORMAL, ModPolarity::AP_UNIVERSAL},
		{ModSlotType::MST_NORMAL, ModPolarity::AP_UNIVERSAL},
		{ModSlotType::MST_NORMAL, ModPolarity::AP_UNIVERSAL},
		{ModSlotType::MST_NORMAL, ModPolarity::AP_ATTACK},
		{ModSlotType::MST_EXILUS, ModPolarity::AP_TACTIC},
		{ModSlotType::MST_ARCANE, ModPolarity::AP_UNIVERSAL},
	};

	auto modManager = std::make_shared<ModManager>(modSlotDetails, weaponData.compatabilityTags, weaponData.parents);

	// Incarnon Evolution Definitions
	weaponData.incarnonUpgrades = Incarnon();

	return std::make_shared<Weapon>(weaponData, modManager);
}

std::shared_ptr<Weapon> WeaponFactory::GetExergis()
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
	weaponData.compatabilityTags = {"PROJECTILE", "SINGLESHOT", "SEMI_AUTO"};
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

	std::vector<std::pair<ModSlotType, ModPolarity>> modSlotDetails = {
		{ModSlotType::MST_NORMAL, ModPolarity::AP_DEFENSE},
		{ModSlotType::MST_NORMAL, ModPolarity::AP_UNIVERSAL},
		{ModSlotType::MST_NORMAL, ModPolarity::AP_UNIVERSAL},
		{ModSlotType::MST_NORMAL, ModPolarity::AP_UNIVERSAL},
		{ModSlotType::MST_NORMAL, ModPolarity::AP_UNIVERSAL},
		{ModSlotType::MST_NORMAL, ModPolarity::AP_UNIVERSAL},
		{ModSlotType::MST_NORMAL, ModPolarity::AP_UNIVERSAL},
		{ModSlotType::MST_NORMAL, ModPolarity::AP_UNIVERSAL},
		{ModSlotType::MST_EXILUS, ModPolarity::AP_ATTACK},
		{ModSlotType::MST_ARCANE, ModPolarity::AP_UNIVERSAL},
	};

	auto modManager = std::make_shared<ModManager>(modSlotDetails, weaponData.compatabilityTags, weaponData.parents);

	// Incarnon Evolution Definitions
	weaponData.incarnonUpgrades = Incarnon();

	return std::make_shared<Weapon>(weaponData, modManager);
}

std::shared_ptr<Weapon> WeaponFactory::GetLexPrime()
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

	std::vector<std::pair<ModSlotType, ModPolarity>> modSlotDetails = {
		{ModSlotType::MST_NORMAL, ModPolarity::AP_UNIVERSAL},
		{ModSlotType::MST_NORMAL, ModPolarity::AP_UNIVERSAL},
		{ModSlotType::MST_NORMAL, ModPolarity::AP_UNIVERSAL},
		{ModSlotType::MST_NORMAL, ModPolarity::AP_UNIVERSAL},
		{ModSlotType::MST_NORMAL, ModPolarity::AP_UNIVERSAL},
		{ModSlotType::MST_NORMAL, ModPolarity::AP_UNIVERSAL},
		{ModSlotType::MST_NORMAL, ModPolarity::AP_UNIVERSAL},
		{ModSlotType::MST_NORMAL, ModPolarity::AP_ATTACK},
		{ModSlotType::MST_EXILUS, ModPolarity::AP_TACTIC},
		{ModSlotType::MST_ARCANE, ModPolarity::AP_UNIVERSAL},
	};

	auto modManager = std::make_shared<ModManager>(modSlotDetails, weaponData.compatabilityTags, weaponData.parents);

	// Incarnon Evolution Definitions
	{
		// Evolution 2 options
		std::vector<std::shared_ptr<IModEffect>> incarnonEvo2aModEffects = {
			std::make_shared<ConstantModEffect>(DamageType::DT_ANY, ModUpgradeType::WEAPON_DAMAGE_AMOUNT, ModOperationType::ADD_TO_BASE_VALUE, 20),
			std::make_shared<ConditionalModEffect>(std::make_shared<ConstantModEffect>(DamageType::DT_ANY, ModUpgradeType::WEAPON_DAMAGE_AMOUNT, ModOperationType::ADD_TO_BASE_VALUE, 80), Conditional::onShieldBreak)};
		auto incarnonEvo2a = std::make_shared<Mod>("Incarnon Evo 2a", "Primary", ModPolarity::AP_UNIVERSAL, 0, ModFusionLimit::QA_NONE, ModBaseDrain::QA_NONE, incarnonEvo2aModEffects);
		std::vector<std::shared_ptr<IModEffect>> incarnonEvo2bModEffects = {
			std::make_shared<ConstantModEffect>(DamageType::DT_ANY, ModUpgradeType::WEAPON_DAMAGE_AMOUNT, ModOperationType::ADD_TO_BASE_VALUE, 20),
			std::make_shared<ConditionalModEffect>(std::make_shared<ConstantModEffect>(DamageType::DT_ANY, ModUpgradeType::WEAPON_AMMO_CONSUME_RATE, ModOperationType::ADD, -0.6), Conditional::whileChanneledAbility)};
		auto incarnonEvo2b = std::make_shared<Mod>("Incarnon Evo 2b", "Primary", ModPolarity::AP_UNIVERSAL, 0, ModFusionLimit::QA_NONE, ModBaseDrain::QA_NONE, incarnonEvo2bModEffects);
		std::vector<std::shared_ptr<Mod>> evo2Options{incarnonEvo2a, incarnonEvo2b};

		// Evolution 3 options
		std::vector<std::shared_ptr<IModEffect>> incarnonEvo3aModEffects = {
			std::make_shared<ConditionalModEffect>(std::make_shared<ConstantModEffect>(DamageType::DT_ANY, ModUpgradeType::WEAPON_SPREAD, ModOperationType::STACKING_MULTIPLY, -0.8), Conditional::onHeadshot), // This ignores the fact it is actually -0.2 stacking up to 4 times
			std::make_shared<ConditionalModEffect>(std::make_shared<ConstantModEffect>(DamageType::DT_ANY, ModUpgradeType::WEAPON_RECOIL, ModOperationType::STACKING_MULTIPLY, -0.8), Conditional::onHeadshot)};
		auto incarnonEvo3a = std::make_shared<Mod>("Incarnon Evo 3a", "Primary", ModPolarity::AP_UNIVERSAL, 0, ModFusionLimit::QA_NONE, ModBaseDrain::QA_NONE, incarnonEvo3aModEffects);
		std::vector<std::shared_ptr<IModEffect>> incarnonEvo3bModEffects = {
			std::make_shared<ConstantModEffect>(DamageType::DT_ANY, ModUpgradeType::WEAPON_CLIP_MAX, ModOperationType::ADD_TO_BASE_VALUE, 10)};
		auto incarnonEvo3b = std::make_shared<Mod>("Incarnon Evo 3b", "Primary", ModPolarity::AP_UNIVERSAL, 0, ModFusionLimit::QA_NONE, ModBaseDrain::QA_NONE, incarnonEvo3bModEffects);
		std::vector<std::shared_ptr<IModEffect>> incarnonEvo3cModEffects = {
			std::make_shared<ConditionalModEffect>(std::make_shared<ConstantModEffect>(DamageType::DT_ANY, ModUpgradeType::WEAPON_RELOAD_SPEED, ModOperationType::STACKING_MULTIPLY, 1), Conditional::onReloadFromEmpty)};
		auto incarnonEvo3c = std::make_shared<Mod>("Incarnon Evo 3c", "Primary", ModPolarity::AP_UNIVERSAL, 0, ModFusionLimit::QA_NONE, ModBaseDrain::QA_NONE, incarnonEvo3cModEffects);
		std::vector<std::shared_ptr<Mod>> evo3Options{incarnonEvo3a, incarnonEvo3b, incarnonEvo3c};

		// Evolution 4 options
		std::vector<std::shared_ptr<IModEffect>> incarnonEvo4aModEffects = {
			std::make_shared<ConditionalModEffect>(std::make_shared<ConstantModEffect>(DamageType::DT_ANY, ModUpgradeType::WEAPON_HEADSHOT_MULTIPLIER, ModOperationType::STACKING_MULTIPLY, 1), Conditional::onEquip)};
		auto incarnonEvo4a = std::make_shared<Mod>("Incarnon Evo 4a", "Primary", ModPolarity::AP_UNIVERSAL, 0, ModFusionLimit::QA_NONE, ModBaseDrain::QA_NONE, incarnonEvo4aModEffects);
		std::vector<std::shared_ptr<IModEffect>> incarnonEvo4bModEffects = {
			std::make_shared<ConstantModEffect>(DamageType::DT_ANY, ModUpgradeType::WEAPON_PROC_CHANCE, ModOperationType::ADD_TO_BASE_VALUE, 0.3)};
		auto incarnonEvo4b = std::make_shared<Mod>("Incarnon Evo 4b", "Primary", ModPolarity::AP_UNIVERSAL, 0, ModFusionLimit::QA_NONE, ModBaseDrain::QA_NONE, incarnonEvo4bModEffects);
		std::vector<std::shared_ptr<IModEffect>> incarnonEvo4cModEffects = {
			std::make_shared<ConstantModEffect>(DamageType::DT_ANY, ModUpgradeType::WEAPON_CRIT_CHANCE, ModOperationType::ADD_TO_BASE_VALUE, 0.19),
			std::make_shared<ConstantModEffect>(DamageType::DT_ANY, ModUpgradeType::WEAPON_CRIT_DAMAGE, ModOperationType::ADD_TO_BASE_VALUE, 0.4)};
		auto incarnonEvo4c = std::make_shared<Mod>("Incarnon Evo 4c", "Primary", ModPolarity::AP_UNIVERSAL, 0, ModFusionLimit::QA_NONE, ModBaseDrain::QA_NONE, incarnonEvo4cModEffects);
		std::vector<std::shared_ptr<Mod>> evo4Options{incarnonEvo4a, incarnonEvo4b, incarnonEvo4c};

		weaponData.incarnonUpgrades = Incarnon({evo2Options, evo3Options, evo4Options});
	}

	return std::make_shared<Weapon>(weaponData, modManager);
}

std::shared_ptr<Weapon> WeaponFactory::GetMK1Braton()
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

	std::vector<std::pair<ModSlotType, ModPolarity>> modSlotDetails = {
		{ModSlotType::MST_NORMAL, ModPolarity::AP_UNIVERSAL},
		{ModSlotType::MST_NORMAL, ModPolarity::AP_UNIVERSAL},
		{ModSlotType::MST_NORMAL, ModPolarity::AP_UNIVERSAL},
		{ModSlotType::MST_NORMAL, ModPolarity::AP_UNIVERSAL},
		{ModSlotType::MST_NORMAL, ModPolarity::AP_UNIVERSAL},
		{ModSlotType::MST_NORMAL, ModPolarity::AP_UNIVERSAL},
		{ModSlotType::MST_NORMAL, ModPolarity::AP_UNIVERSAL},
		{ModSlotType::MST_NORMAL, ModPolarity::AP_UNIVERSAL},
		{ModSlotType::MST_EXILUS, ModPolarity::AP_TACTIC},
		{ModSlotType::MST_ARCANE, ModPolarity::AP_UNIVERSAL},
	};

	auto modManager = std::make_shared<ModManager>(modSlotDetails, weaponData.compatabilityTags, weaponData.parents);

	// Incarnon Evolution Definitions
	{
		// Evolution 2 options
		std::vector<std::shared_ptr<IModEffect>> incarnonEvo2aModEffects = {
			std::make_shared<ConstantModEffect>(DamageType::DT_ANY, ModUpgradeType::WEAPON_DAMAGE_AMOUNT, ModOperationType::ADD_TO_BASE_VALUE, 28),
			std::make_shared<ConditionalModEffect>(std::make_shared<ConstantModEffect>(DamageType::DT_ANY, ModUpgradeType::WEAPON_DAMAGE_AMOUNT, ModOperationType::ADD_TO_BASE_VALUE, 22), Conditional::whileChanneledAbility), // This one is conditional to channeling
			std::make_shared<ConditionalModEffect>(std::make_shared<ConstantModEffect>(DamageType::DT_ANY, ModUpgradeType::WEAPON_AMMO_CONSUME_RATE, ModOperationType::ADD, -0.5), Conditional::whileChanneledAbility)		  // This one is conditional to channeling
		};
		auto incarnonEvo2a = std::make_shared<Mod>("Incarnon Evo 2a", "Primary", ModPolarity::AP_UNIVERSAL, 0, ModFusionLimit::QA_NONE, ModBaseDrain::QA_NONE, incarnonEvo2aModEffects);
		std::vector<std::shared_ptr<IModEffect>> incarnonEvo2bModEffects = {
			std::make_shared<ConstantModEffect>(DamageType::DT_ANY, ModUpgradeType::WEAPON_DAMAGE_AMOUNT, ModOperationType::ADD_TO_BASE_VALUE, 20),
			std::make_shared<ConstantModEffect>(DamageType::DT_ANY, ModUpgradeType::WEAPON_FIRE_ITERATIONS, ModOperationType::STACKING_MULTIPLY, 0.2)};
		auto incarnonEvo2b = std::make_shared<Mod>("Incarnon Evo 2b", "Primary", ModPolarity::AP_UNIVERSAL, 0, ModFusionLimit::QA_NONE, ModBaseDrain::QA_NONE, incarnonEvo2bModEffects);
		std::vector<std::shared_ptr<Mod>> evo2Options{incarnonEvo2a, incarnonEvo2b};

		// Evolution 3 options
		std::vector<std::shared_ptr<IModEffect>> incarnonEvo3aModEffects = {
			std::make_shared<ConstantModEffect>(DamageType::DT_ANY, ModUpgradeType::WEAPON_AMMO_MAX, ModOperationType::ADD_TO_BASE_VALUE, 60)};
		auto incarnonEvo3a = std::make_shared<Mod>("Incarnon Evo 3a", "Primary", ModPolarity::AP_UNIVERSAL, 0, ModFusionLimit::QA_NONE, ModBaseDrain::QA_NONE, incarnonEvo3aModEffects);
		std::vector<std::shared_ptr<IModEffect>> incarnonEvo3bModEffects = {
			std::make_shared<ConstantModEffect>(DamageType::DT_ANY, ModUpgradeType::WEAPON_SPREAD, ModOperationType::STACKING_MULTIPLY, -0.6),
			std::make_shared<ConstantModEffect>(DamageType::DT_ANY, ModUpgradeType::WEAPON_RECOIL, ModOperationType::STACKING_MULTIPLY, -0.6)};
		auto incarnonEvo3b = std::make_shared<Mod>("Incarnon Evo 3b", "Primary", ModPolarity::AP_UNIVERSAL, 0, ModFusionLimit::QA_NONE, ModBaseDrain::QA_NONE, incarnonEvo3bModEffects);
		std::vector<std::shared_ptr<IModEffect>> incarnonEvo3cModEffects = {
			// Refill ammo on punch through hit
		};
		auto incarnonEvo3c = std::make_shared<Mod>("Incarnon Evo 3c", "Primary", ModPolarity::AP_UNIVERSAL, 0, ModFusionLimit::QA_NONE, ModBaseDrain::QA_NONE, incarnonEvo3cModEffects);
		std::vector<std::shared_ptr<Mod>> evo3Options{incarnonEvo3a, incarnonEvo3b, incarnonEvo3c};

		// Evolution 4 options
		std::vector<std::shared_ptr<IModEffect>> incarnonEvo4aModEffects = {
			std::make_shared<ConstantModEffect>(DamageType::DT_ANY, ModUpgradeType::WEAPON_CRIT_CHANCE, ModOperationType::ADD_TO_BASE_VALUE, 0.18),
			std::make_shared<ConstantModEffect>(DamageType::DT_ANY, ModUpgradeType::WEAPON_CRIT_DAMAGE, ModOperationType::ADD_TO_BASE_VALUE, 0.5)};
		auto incarnonEvo4a = std::make_shared<Mod>("Incarnon Evo 4a", "Primary", ModPolarity::AP_UNIVERSAL, 0, ModFusionLimit::QA_NONE, ModBaseDrain::QA_NONE, incarnonEvo4aModEffects);
		std::vector<std::shared_ptr<IModEffect>> incarnonEvo4bModEffects = {
			std::make_shared<ConstantModEffect>(DamageType::DT_ANY, ModUpgradeType::WEAPON_CRIT_DAMAGE, ModOperationType::ADD_TO_BASE_VALUE, 3.3) // I need to still add the conditional requirement to this, but it will at least provide the numbers
		};
		auto incarnonEvo4b = std::make_shared<Mod>("Incarnon Evo 4b", "Primary", ModPolarity::AP_UNIVERSAL, 0, ModFusionLimit::QA_NONE, ModBaseDrain::QA_NONE, incarnonEvo4bModEffects);
		std::vector<std::shared_ptr<IModEffect>> incarnonEvo4cModEffects = {
			std::make_shared<ConstantModEffect>(DamageType::DT_ANY, ModUpgradeType::WEAPON_CRIT_CHANCE, ModOperationType::ADD_TO_BASE_VALUE, 0.1),
			std::make_shared<ConstantModEffect>(DamageType::DT_ANY, ModUpgradeType::WEAPON_PROC_CHANCE, ModOperationType::ADD_TO_BASE_VALUE, 0.12)};
		auto incarnonEvo4c = std::make_shared<Mod>("Incarnon Evo 4c", "Primary", ModPolarity::AP_UNIVERSAL, 0, ModFusionLimit::QA_NONE, ModBaseDrain::QA_NONE, incarnonEvo4cModEffects);
		std::vector<std::shared_ptr<Mod>> evo4Options{incarnonEvo4a, incarnonEvo4b, incarnonEvo4c};

		weaponData.incarnonUpgrades = Incarnon({evo2Options, evo3Options, evo4Options});
	}

	return std::make_shared<Weapon>(weaponData, modManager);
}

std::shared_ptr<Weapon> WeaponFactory::GetWeapon(std::string name)
{
	(void)name;
	std::string databaseData;
	return CreateWeapon(databaseData);
}

std::shared_ptr<Weapon> WeaponFactory::CreateWeapon(std::string databaseData)
{
	// Currently the weaponData should be in the BaseWeaponData form
	auto categoryDataPairs = DatabaseManipulationFunctions::ExtractCategoryDataPairs(databaseData);
	(void)categoryDataPairs;
	return GetNullWeapon();
}
