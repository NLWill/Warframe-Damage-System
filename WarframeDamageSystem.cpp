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

	Weapon *weapon = WeaponFactory::GetLexPrime();

	std::vector<ModEffectBase *> baseDamageModEffects = {new ConstantModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_DAMAGE_AMOUNT, ModOperationType::STACKING_MULTIPLY, 2.2)};
	Mod *baseDamageMod = new Mod("Serration", "Primary", ModPolarity::AP_ATTACK, 10, 10, 4, baseDamageModEffects);
	// weapon->modManager->AddMod(baseDamageMod, 0);

	std::vector<ModEffectBase *> multishotModEffects1 = {new ConstantModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_MULTISHOT, ModOperationType::STACKING_MULTIPLY, 0.9)};
	Mod *multishotMod1 = new Mod("Split Chamber", "Primary", ModPolarity::AP_ATTACK, 5, 5, 4, multishotModEffects1);
	// weapon->modManager->AddMod(multishotMod1, 1);

	std::vector<ModEffectBase *> multishotModEffects2 = {new ConstantModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_MULTISHOT, ModOperationType::STACKING_MULTIPLY, 0.6)};
	Mod *multishotMod2 = new Mod("Vigilante Armaments", "Primary", ModPolarity::AP_TACTIC, 5, 5, 4, multishotModEffects2);
	// weapon->modManager->AddMod(multishotMod2, 2);

	std::vector<ModEffectBase *> critDamageModEffects = {new ConstantModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_CRIT_DAMAGE, ModOperationType::STACKING_MULTIPLY, 0.9)};
	Mod *critDamage = new Mod("Vital Sense", "Primary", ModPolarity::AP_ATTACK, 5, 5, 4, critDamageModEffects);
	// weapon->modManager->AddMod(critDamage, 3);

	std::vector<ModEffectBase *> factionModEffects = {new FactionModEffect(ModOperationType::STACKING_MULTIPLY, 0.3f, Faction::GRINEER)};
	Mod *baneOfGrineer = new Mod("Bane of Grineer", "Primary", ModPolarity::AP_ATTACK, 5, 5, 4, factionModEffects);
	// weapon->modManager->AddMod(baneOfGrineer, 4);

	std::vector<ModEffectBase *> conditionOverloadModEffects = {new WeaponDamageIfVictimProcActiveModEffect(ModOperationType::STACKING_MULTIPLY, 0.8)};
	Mod *conditionOverload = new Mod("Condition Overload", "Melee", ModPolarity::AP_ATTACK, 5, 5, 10, conditionOverloadModEffects);
	weapon->modManager->AddMod(conditionOverload, 5);
	
	std::string input;
	do
	{
		std::cout << "Testing the damage pipeline" << std::endl;
		std::cout << DamagePipeline::RunDamagePipeline(*weapon, "Normal Attack", *target, "Body") << std::endl;
		target->afflictedStatusEffects.push_back(StatusEffect::PT_IMMOLATION);
		std::cin >> input;
	} while (input == "y" || input == "Y");

	delete weapon;
	delete target;
	delete baseDamageMod;
	delete multishotMod1;
	delete multishotMod2;
	delete critDamage;
	delete baneOfGrineer;
};