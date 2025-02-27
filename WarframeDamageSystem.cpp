#include <iostream>
#include <string>
#include "src/Services/Logging/LogService.h"
#include "src/Services/RNG/RNGService.h"
#include "src/Services/ServiceLocator.h"

#include "src/Mods/ModEffects/ConstantModEffect.h"
#include "src/Mods/ModEffects/FactionModEffect.h"
#include "src/Mods/ModEffects/WeaponDamageIfVictimProcActiveModEffect.h"
#include "src/Mods/ModEffects/ConditionalModEffectWrapper.h"
#include <cmath>

#include "src/Weapons/WeaponFactory.h"
#include "src/DamagePipeline/DamagePipeline.h"
#include "src/Target/Target.h"

#include "src/Mods/ModEffects/ConditionalOverrideManager.h"

int main()
{
	ServiceLocator::Initialise();
	auto logSystem = new LogService();
	ServiceLocator::Provide(logSystem);
	auto rngSystem = new RNGService();
	ServiceLocator::Provide(rngSystem);

	ConditionalOverrideManager::Instance().OverrideAll(false);
	ConditionalOverrideManager::Instance().SetOverride(Conditional::whileChanneledAbility, false);
	ConditionalOverrideManager::Instance().SetOverride(Conditional::onHeadshot, false);
	ConditionalOverrideManager::Instance().SetOverride(Conditional::onShieldBreak, false);
	ConditionalOverrideManager::Instance().SetOverride(Conditional::onHeadshotKill, true);

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
	target->afflictedStatusEffects.push_back(ProcType::PT_BLEEDING);
	target->afflictedStatusEffects.push_back(ProcType::PT_POISONED);

	Weapon *weapon = WeaponFactory::GetMK1Braton();

	std::vector<ModEffectBase *> baseDamageModEffects = {new ConstantModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_DAMAGE_AMOUNT, ModOperationType::STACKING_MULTIPLY, 1.65)};
	Mod *baseDamageMod = new Mod("Serration", "Primary", ModPolarity::AP_ATTACK, 10, 10, 4, baseDamageModEffects);
	baseDamageMod->slotType = ModSlotType::MST_NORMAL;
	weapon->modManager->AddMod(baseDamageMod, 0);

	std::vector<ModEffectBase *> multishotModEffects1 = {new ConstantModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_MULTISHOT, ModOperationType::STACKING_MULTIPLY, 1)};
	Mod *multishotMod1 = new Mod("Split Chamber", "Primary", ModPolarity::AP_ATTACK, 5, 5, 4, multishotModEffects1);
	multishotMod1->slotType = ModSlotType::MST_NORMAL;
	weapon->modManager->AddMod(multishotMod1, 1);

	std::vector<ModEffectBase *> multishotModEffects2 = {new ConstantModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_MULTISHOT, ModOperationType::STACKING_MULTIPLY, 0.6)};
	Mod *multishotMod2 = new Mod("Vigilante Armaments", "Primary", ModPolarity::AP_TACTIC, 5, 5, 4, multishotModEffects2);
	multishotMod2->slotType = ModSlotType::MST_NORMAL;
	// weapon->modManager->AddMod(multishotMod2, 2);

	std::vector<ModEffectBase *> critDamageModEffects = {new ConstantModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_CRIT_DAMAGE, ModOperationType::STACKING_MULTIPLY, 1.2)};
	Mod *critDamage = new Mod("Vital Sense", "Primary", ModPolarity::AP_ATTACK, 5, 5, 4, critDamageModEffects);
	critDamage->slotType = ModSlotType::MST_NORMAL;
	weapon->modManager->AddMod(critDamage, 3);

	std::vector<ModEffectBase *> factionModEffects = {new FactionModEffect(ModOperationType::STACKING_MULTIPLY, 0.3f, Faction::GRINEER)};
	Mod *baneOfGrineer = new Mod("Bane of Grineer", "Primary", ModPolarity::AP_ATTACK, 5, 5, 4, factionModEffects);
	baneOfGrineer->slotType = ModSlotType::MST_NORMAL;
	weapon->modManager->AddMod(baneOfGrineer, 4);

	std::vector<ModEffectBase *> conditionOverloadModEffects = {new WeaponDamageIfVictimProcActiveModEffect(ModOperationType::STACKING_MULTIPLY, 0.8)};
	Mod *conditionOverload = new Mod("Galvanized Aptitude", "Primary", ModPolarity::AP_ATTACK, 10, 10, 2, conditionOverloadModEffects);
	conditionOverload->slotType = ModSlotType::MST_NORMAL;
	weapon->modManager->AddMod(conditionOverload, 5);

	std::vector<ModEffectBase *> critChanceModEffects = {
		new ConstantModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_CRIT_CHANCE, ModOperationType::STACKING_MULTIPLY, 1.2),
		new ConditionalModEffect(*new ConstantModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_CRIT_CHANCE, ModOperationType::STACKING_MULTIPLY, 2), Conditional::onHeadshotKill)};
	Mod *critChance = new Mod("Galvanized Scope", "Primary", ModPolarity::AP_ATTACK, 5, 5, 4, critChanceModEffects);
	critChance->slotType = ModSlotType::MST_NORMAL;
	weapon->modManager->AddMod(critChance, 6);

	std::vector<ModEffectBase *> flatCritChanceModEffects = {
		new ConstantModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_CRIT_CHANCE, ModOperationType::ADD, 1)};	// Add a flat 100% crit chance to increase crit tier by 1
	Mod *flatCritChance = new Mod("Flat CC bonus", "Primary", ModPolarity::AP_ATTACK, 5, 5, 4, flatCritChanceModEffects);
	flatCritChance->slotType = ModSlotType::MST_NORMAL;
	weapon->modManager->AddMod(flatCritChance, 7);

	// weapon->weaponData.incarnonUpgrades.SetActiveEvolution(0, 0);
	// weapon->weaponData.incarnonUpgrades.SetActiveEvolution(1, 1);
	// weapon->weaponData.incarnonUpgrades.SetActiveEvolution(2, 0);

	float totalDamageDealt = 0;
	int iterations = 1;
	for (int i = 0; i < iterations; i++)
	{
		totalDamageDealt += weapon->Fire("Normal Attack", *target, "Body");
	}
	std::cout << "Average dmg = " << totalDamageDealt / iterations << std::endl;

	delete weapon;
	delete target;
	delete baseDamageMod;
	delete multishotMod1;
	delete multishotMod2;
	delete critDamage;
	delete baneOfGrineer;
	delete conditionOverload;
	delete critChance;
};