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
	ConditionalOverrideManager::Instance().SetOverride(Conditional::onHeadshot, true);
	ConditionalOverrideManager::Instance().SetOverride(Conditional::onShieldBreak, false);
	ConditionalOverrideManager::Instance().SetOverride(Conditional::onHeadshotKill, true);



	std::map<std::string, std::pair<float, bool>> bodyPartMultipliers = {{"Head", {3, true}}, {"Body", {1, false}}};
	Target *target = new Target(1, 1, 0, Faction::GRINEER, HealthType::TENNO, bodyPartMultipliers, {});
	target->afflictedStatusEffects.push_back(ProcType::PT_BLEEDING);
	// target->afflictedStatusEffects.push_back(ProcType::PT_POISONED);

	Weapon *weapon = WeaponFactory::GetDaikyu();

	std::vector<ModEffectBase *> baseDamageModEffects = {new ConstantModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_DAMAGE_AMOUNT, ModOperationType::STACKING_MULTIPLY, 1.65)};
	Mod *baseDamageMod = new Mod("Serration", "Primary", ModPolarity::AP_ATTACK, 10, 10, 4, baseDamageModEffects);
	baseDamageMod->slotType = ModSlotType::MST_NORMAL;
	// weapon->modManager->AddMod(baseDamageMod);

	std::vector<ModEffectBase *> multishotModEffects1 = {new ConstantModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_MULTISHOT, ModOperationType::STACKING_MULTIPLY, 0.9)};
	Mod *multishotMod1 = new Mod("Split Chamber", "Primary", ModPolarity::AP_ATTACK, 5, 5, 4, multishotModEffects1);
	multishotMod1->slotType = ModSlotType::MST_NORMAL;
	weapon->modManager->AddMod(multishotMod1);

	std::vector<ModEffectBase *> multishotModEffects2 = {new ConstantModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_MULTISHOT, ModOperationType::STACKING_MULTIPLY, 0.6)};
	Mod *multishotMod2 = new Mod("Vigilante Armaments", "Primary", ModPolarity::AP_TACTIC, 5, 5, 4, multishotModEffects2);
	multishotMod2->slotType = ModSlotType::MST_NORMAL;
	// weapon->modManager->AddMod(multishotMod2);

	std::vector<ModEffectBase *> critDamageModEffects = {new ConstantModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_CRIT_DAMAGE, ModOperationType::STACKING_MULTIPLY, 1.2)};
	Mod *critDamage = new Mod("Vital Sense", "Primary", ModPolarity::AP_ATTACK, 5, 5, 4, critDamageModEffects);
	critDamage->slotType = ModSlotType::MST_NORMAL;
	weapon->modManager->AddMod(critDamage);

	std::vector<ModEffectBase *> factionModEffects = {new FactionModEffect(ModOperationType::STACKING_MULTIPLY, 0.3f, Faction::GRINEER)};
	Mod *baneOfGrineer = new Mod("Bane of Grineer", "Primary", ModPolarity::AP_ATTACK, 5, 5, 4, factionModEffects);
	baneOfGrineer->slotType = ModSlotType::MST_NORMAL;
	//weapon->modManager->AddMod(baneOfGrineer);

	std::vector<ModEffectBase *> conditionOverloadModEffects = {new WeaponDamageIfVictimProcActiveModEffect(ModOperationType::STACKING_MULTIPLY, 0.8)};
	Mod *conditionOverload = new Mod("Galvanized Aptitude", "Primary", ModPolarity::AP_ATTACK, 10, 10, 2, conditionOverloadModEffects);
	conditionOverload->slotType = ModSlotType::MST_NORMAL;
	// weapon->modManager->AddMod(conditionOverload);

	std::vector<ModEffectBase *> critChanceModEffects = {
		new ConditionalModEffect(*new ConstantModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_CRIT_CHANCE, ModOperationType::STACKING_MULTIPLY, 1.2), Conditional::onHeadshot),
		new ConditionalModEffect(*new ConstantModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_CRIT_CHANCE, ModOperationType::STACKING_MULTIPLY, 2), Conditional::onHeadshotKill)};
	Mod *critChance = new Mod("Galvanized Scope", "Primary", ModPolarity::AP_ATTACK, 5, 5, 4, critChanceModEffects);
	critChance->slotType = ModSlotType::MST_NORMAL;
	weapon->modManager->AddMod(critChance);

	std::vector<ModEffectBase *> elementalModEffects = {
		new ConstantModEffect(DamageType::DT_ELECTRICITY, ModUpgradeType::WEAPON_PERCENT_BASE_DAMAGE_ADDED, ModOperationType::STACKING_MULTIPLY, 1.5),
		new ConstantModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_STATUS_CHANCE, ModOperationType::STACKING_MULTIPLY, 2.1)};
	Mod *elementalMod = new Mod("90\% elemental mod", "Primary", ModPolarity::AP_ATTACK, 5, 5, 4, elementalModEffects);
	elementalMod->slotType = ModSlotType::MST_NORMAL;
	weapon->modManager->AddMod(elementalMod);

	std::vector<ModEffectBase *> acuityModEffects = {
		new ConstantModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_CRIT_CHANCE, ModOperationType::STACKING_MULTIPLY, 3.5),
		new ConstantModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_WEAK_POINT_MODIFIER, ModOperationType::ADD, 5.25)};
	Mod *acuityMod = new Mod("Rifle Acuity", "Primary", ModPolarity::AP_TACTIC, 10, 10, 6, acuityModEffects);
	acuityMod->slotType = ModSlotType::MST_NORMAL;
	// weapon->modManager->AddMod(acuityMod);

	std::vector<ModEffectBase *> targetAcquiredModEffects = {
		new ConstantModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_HEADSHOT_MULTIPLIER, ModOperationType::STACKING_MULTIPLY, 0.75)};
	Mod *daikyuTargetAcquiredMod = new Mod("Amalgam Daikyu Target Acquired", "Primary", ModPolarity::AP_ATTACK, 5, 5, 10, targetAcquiredModEffects);
	daikyuTargetAcquiredMod->slotType = ModSlotType::MST_NORMAL;
	//weapon->modManager->AddMod(daikyuTargetAcquiredMod);

	std::vector<ModEffectBase *> arcaneModEffects = {
		new ConditionalModEffect(*new ConstantModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_DAMAGE_AMOUNT, ModOperationType::STACKING_MULTIPLY, 3.6), Conditional::onHeadshotKill),
		new ConstantModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_HEADSHOT_MULTIPLIER, ModOperationType::STACKING_MULTIPLY, 0.3),
		new ConstantModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_RECOIL, ModOperationType::STACKING_MULTIPLY, -0.5)};
	Mod *arcane = new Mod("Primary Deadhead", "Primary", ModPolarity::AP_ATTACK, 5, 5, 0, arcaneModEffects);
	arcane->slotType = ModSlotType::MST_ARCANE;
	// weapon->modManager->AddMod(arcane);

	// weapon->weaponData.incarnonUpgrades.SetActiveEvolution(0, 0);
	// weapon->weaponData.incarnonUpgrades.SetActiveEvolution(1, 1);
	// weapon->weaponData.incarnonUpgrades.SetActiveEvolution(2, 0);

	//weapon->modManager->PringCurrentModConfig();

	std::string attackName = "Normal Attack";
	std::string targetBodyPart = "Body";
	int desiredProcess = 2;
	switch (desiredProcess)
	{
	case 1:
	{
		auto [directDamage, dotDamage] = weapon->Fire(attackName, *target, targetBodyPart);
		ServiceLocator::GetLogger().Log("Direct damage = " + std::to_string(directDamage));
		ServiceLocator::GetLogger().Log("Damage over time = " + std::to_string(dotDamage));
		break;
	}
	case 2:
	{
		auto [directDamage, dotDamage] = weapon->GetAverageDamagePerShot(attackName, *target, targetBodyPart);
		ServiceLocator::GetLogger().Log("Average direct damage per shot = " + std::to_string(directDamage));
		ServiceLocator::GetLogger().Log("Average DOT per second per shot = " + std::to_string(dotDamage));
		break;
	}
	case 3:
	{
		float avgBurstDPS = weapon->GetAverageBurstDPS(attackName, *target, targetBodyPart);
		ServiceLocator::GetLogger().Log("Average burst DPS = " + std::to_string(avgBurstDPS));
		break;
	}
	case 4:
	{
		float avgSustainedDPS = weapon->GetAverageSustainedDPS(attackName, *target, targetBodyPart);
		ServiceLocator::GetLogger().Log("Average sustained DPS = " + std::to_string(avgSustainedDPS));
		break;
	}
	default:
		break;
	}

	delete weapon;
	delete target;
	delete baseDamageMod;
	delete multishotMod1;
	delete multishotMod2;
	delete critDamage;
	delete baneOfGrineer;
	delete conditionOverload;
	delete critChance;
	delete daikyuTargetAcquiredMod;
	delete acuityMod;
	delete elementalMod;
	delete arcane;
};