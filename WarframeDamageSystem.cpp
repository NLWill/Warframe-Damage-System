#include <iostream>
#include <string>
#include "src/Services/Logging/LogService.h"
#include "src/Services/RNG/RNGService.h"
#include "src/Services/ServiceLocator.h"

#include "src/Mods/ModEffects/ConstantModEffect.h"
#include "src/Mods/ModEffects/FactionModEffect.h"
#include "src/Mods/ModEffects/WeaponDamageIfVictimProcActiveModEffect.h"
#include <cmath>

#include "src/Weapons/WeaponFactory.h"
#include "src/DamagePipeline/DamagePipeline.h"
#include "src/Target/Target.h"

#include <fstream>
#include "src/DatabaseManagement/DatabaseManipulationFunctions.h"

#include "src/WeaponsReworked/Weapon.h"

int main()
{
	ServiceLocator::Initialise();
	auto logSystem = new LogService();
	ServiceLocator::Provide(logSystem);
	auto rngSystem = new RNGService();
	ServiceLocator::Provide(rngSystem);

	/*
	std::cout << "Hello, World!" << std::endl;
	std::string inp;

	int sum = 0;
	for (int i = 0; i < 100000; i++)
	{
		int gen = ServiceLocator::GetRNG().RandomInt(10);
		sum += gen;
	}
	ServiceLocator::GetLogger().LogWarning(std::to_string(sum));
	std::string average = "Average was " + std::to_string((float)sum / 100000);
	ServiceLocator::GetLogger().LogError(average);
	*/

	std::map<std::string, std::pair<float, bool>> bodyPartMultipliers = {{"Head", {3, true}}, {"Body", {1, false}}};
	Target *target = new Target(1, 1, 0, Faction::GRINEER, HealthType::GRINEER, bodyPartMultipliers, {});

	Weapon *weapon = WeaponFactory::GetMK1Braton();

	std::vector<ModEffectBase *> baseDamageModEffects = {new ConstantModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_DAMAGE_AMOUNT, ModOperationType::STACKING_MULTIPLY, 1.65)};
	Mod *baseDamageMod = new Mod("Serration", "Primary", ModPolarity::AP_ATTACK, 10, 10, 4, baseDamageModEffects);
	baseDamageMod->slotType = ModSlotType::MST_NORMAL;
	// weapon->modManager->AddMod(baseDamageMod, 0);

	std::vector<ModEffectBase *> multishotModEffects1 = {new ConstantModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_MULTISHOT, ModOperationType::STACKING_MULTIPLY, 0.9)};
	Mod *multishotMod1 = new Mod("Split Chamber", "Primary", ModPolarity::AP_ATTACK, 5, 5, 4, multishotModEffects1);
	weapon->modManager->AddMod(multishotMod1, 1);

	std::vector<ModEffectBase *> multishotModEffects2 = {new ConstantModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_MULTISHOT, ModOperationType::STACKING_MULTIPLY, 0.6)};
	Mod *multishotMod2 = new Mod("Vigilante Armaments", "Primary", ModPolarity::AP_TACTIC, 5, 5, 4, multishotModEffects2);
	weapon->modManager->AddMod(multishotMod2, 2);

	std::vector<ModEffectBase *> critDamageModEffects = {new ConstantModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_CRIT_DAMAGE, ModOperationType::STACKING_MULTIPLY, 1.2)};
	Mod *critDamage = new Mod("Vital Sense", "Primary", ModPolarity::AP_ATTACK, 5, 5, 4, critDamageModEffects);
	critDamage->slotType = ModSlotType::MST_NORMAL;
	weapon->modManager->AddMod(critDamage, 3);

	std::vector<ModEffectBase *> factionModEffects = {new FactionModEffect(ModOperationType::STACKING_MULTIPLY, 0.3f, Faction::GRINEER)};
	Mod *baneOfGrineer = new Mod("Bane of Grineer", "Primary", ModPolarity::AP_ATTACK, 5, 5, 4, factionModEffects);
	// weapon->modManager->AddMod(baneOfGrineer, 4);

	std::vector<ModEffectBase *> conditionOverloadModEffects = {new WeaponDamageIfVictimProcActiveModEffect(ModOperationType::STACKING_MULTIPLY, 0.8)};
	Mod *conditionOverload = new Mod("Condition Overload", "Melee", ModPolarity::AP_ATTACK, 5, 5, 10, conditionOverloadModEffects);
	// weapon->modManager->AddMod(conditionOverload, 5);

	std::vector<ModEffectBase *> critChanceModEffects = {new ConstantModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_CRIT_CHANCE, ModOperationType::STACKING_MULTIPLY, 3.2)};
	Mod *critChance = new Mod("Galvanized Scope", "Primary", ModPolarity::AP_ATTACK, 5, 5, 4, critChanceModEffects);
	critChance->slotType = ModSlotType::MST_NORMAL;
	weapon->modManager->AddMod(critChance, 6);

	weapon->weaponData.incarnonUpgrades.SetActiveEvolution(0, 0);
	weapon->weaponData.incarnonUpgrades.SetActiveEvolution(1, 1);
	weapon->weaponData.incarnonUpgrades.SetActiveEvolution(2, 0);

	float totalDamageDealt = 0;
	int iterations = 10000;
	for (int i = 0; i < iterations; i++)
	{
		totalDamageDealt += DamagePipeline::RunDamagePipeline(*weapon, "Normal Attack", *target, "Head");
	}
	std::cout<< "Average dmg = " << totalDamageDealt / iterations;
	
	/*
	std::string input;
	do
	{
		std::cout << "Testing the damage pipeline" << std::endl;
		std::cout << DamagePipeline::RunDamagePipeline(*weapon, "Normal Attack", *target, "Body") << std::endl;
		std::cin >> input;
	} while (input == "y" || input == "Y");
	*/
	delete weapon;
	delete target;
	delete baseDamageMod;
	delete multishotMod1;
	delete multishotMod2;
	delete critDamage;
	delete baneOfGrineer;
	delete conditionOverload;

	/*
	std::string test1 = "this[ is (a ,test, i)t, sho]uld have, sp[lit, o]n multiple, lines";
	std::string test2 = "{{{([])()[{}]}[({})]{}()}}[]";
	std::string properTest = "\"ArtifactPolarity\":[\"AP_ATTACK\",\"AP_ATTACK\",\"AP_ATTACK\",\"AP_ATTACK\",\"AP_ATTACK\"],\"BaseDrain\":\"QA_MEDIUM\",\"ItemCompatibility\":\"/Lotus/Weapons/Tenno/Rifle/LotusRifle\",\"ProductCategory\":\"Upgrades\",\"Slotted\":0,\"Upgrades\":[{\"AutoType\":1,\"DamageType\":\"DT_ANY\",\"DisplayAsMultiplier\":0,\"DisplayAsPercent\":1,\"InvalidModifiers\":[],\"OperationType\":\"STACKING_MULTIPLY\",\"OverrideLocalization\":1,\"ReverseValueSymbol\":0,\"RoundTo\":0.1,\"RoundingMode\":\"RM_ROUND\",\"SmallerIsBetter\":0,\"SymbolFilter\":\"\",\"UpgradeObject\":\"\",\"UpgradeType\":\"WEAPON_CRIT_CHANCE\",\"ValidModifiers\":[],\"ValidPostures\":[],\"ValidProcTypes\":[],\"ValidType\":\"\",\"Value\":0.25}],\"id\":624,\"name\":\"Point Strike\",\"parent\":\"/Lotus/Types/Game/LotusArtifactUpgrades/BaseArtifactUpgrade\",\"parents\":[\"/Lotus/Types/Game/LotusArtifactUpgrades/BaseArtifactUpgrade\",\"/Lotus/Types/Game/LotusArtifactUpgrade\"],\"path\":\"/Lotus/Upgrades/Mods/Rifle/WeaponCritChanceMod\",\"TypeName\":\"/Lotus/Upgrades/Mods/Rifle/WeaponCritChanceMod\"";
	std::string properTest2 = "\"ArtifactPolarity\":\"AP_TACTIC\",\"BaseDrain\":\"QA_MEDIUM\",\"ExcludeFromCodex\":0,\"Icon\":\"/Lotus/Interface/Cards/Images/Rifle/CorruptedCriticalRateForFireRateMod.png\",\"IncludeInBoosterPack\":0,\"ItemCompatibility\":\"/Lotus/Weapons/Tenno/Rifle/LotusRifle\",\"ItemCompatibilityLocTag\":\"/Lotus/Language/Items/RifleCategoryName\",\"LocalizeDescTag\":\"\",\"LocalizeTag\":\"/Lotus/Language/Items/RifleModCorruptedCritRateFireRate\",\"MarketMode\":\"MM_HIDDEN\",\"ProductCategory\":\"Upgrades\",\"Rarity\":\"RARE\",\"RectangleIcon\":1,\"Slotted\":0,\"Upgrades\":[{\"AutoType\":1,\"DamageType\":\"DT_ANY\",\"DisplayAsMultiplier\":0,\"DisplayAsPercent\":1,\"OperationType\":\"STACKING_MULTIPLY\",\"ReverseValueSymbol\":0,\"RoundTo\":0.1,\"RoundingMode\":\"RM_ROUND\",\"SmallerIsBetter\":0,\"UpgradeType\":\"WEAPON_CRIT_CHANCE\",\"ValidModifiers\":[],\"ValidPostures\":[],\"ValidProcTypes\":[],\"ValidType\":\"\",\"Value\":0.33333001},{\"AutoType\":1,\"DamageType\":\"DT_ANY\",\"DisplayAsMultiplier\":0,\"DisplayAsPercent\":1,\"OperationType\":\"STACKING_MULTIPLY\",\"ReverseValueSymbol\":0,\"RoundTo\":0.1,\"RoundingMode\":\"RM_ROUND\",\"SmallerIsBetter\":0,\"UpgradeType\":\"WEAPON_FIRE_RATE\",\"ValidModifiers\":[],\"ValidPostures\":[],\"ValidProcTypes\":[],\"ValidType\":\"\",\"Value\":-0.033300001},{\"AutoType\":0,\"DamageType\":\"DT_ANY\",\"DisplayAsMultiplier\":0,\"DisplayAsPercent\":0,\"OperationType\":\"STACKING_MULTIPLY\",\"ReverseValueSymbol\":0,\"RoundTo\":0.1,\"RoundingMode\":\"RM_ROUND\",\"SmallerIsBetter\":0,\"UpgradeType\":\"WEAPON_FIRE_RATE\",\"ValidModifiers\":[],\"ValidPostures\":[],\"ValidProcTypes\":[],\"ValidType\":\"/Lotus/Weapons/Tenno/Bows/LotusBow\",\"Value\":-0.033300001}],\"id\":582,\"name\":\"Critical Delay\",\"parent\":\"/Lotus/Upgrades/Mods/Rifle/WeaponCritChanceMod\",\"parents\":[\"/Lotus/Upgrades/Mods/Rifle/WeaponCritChanceMod\",\"/Lotus/Types/Game/LotusArtifactUpgrades/BaseArtifactUpgrade\",\"/Lotus/Types/Game/LotusArtifactUpgrade\"],\"path\":\"/Lotus/Upgrades/Mods/Rifle/DualStat/CorruptedCritRateFireRateRifle\",\"TypeName\":\"/Lotus/Upgrades/Mods/Rifle/DualStat/CorruptedCritRateFireRateRifle\"";

	std::string data;
	ifstream file("data/Weapons/Tigris Prime.txt");
	while (file){
		std::string nextLine;
		getline(file, nextLine);
		data+=nextLine;
	}

	auto categoryDataPairs = DatabaseManipulationFunctions::ExtractCategoryDataPairs(data);
	for (auto categoryDataPair : categoryDataPairs){
		ServiceLocator::GetLogger().Log(categoryDataPair.first);
		ServiceLocator::GetLogger().Log(categoryDataPair.second);
		ServiceLocator::GetLogger().Log("----------------");
	}
	*/
};