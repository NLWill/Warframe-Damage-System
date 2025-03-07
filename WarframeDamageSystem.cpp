#include <iostream>
#include <string>
#include <memory>
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
	auto logSystem = std::make_shared<LogService>();
	ServiceLocator::RegisterService<ILogService>(logSystem);
	auto rngSystem = std::make_shared<RNGService>();
	ServiceLocator::RegisterService<IRNGService>(rngSystem);

	ConditionalOverrideManager::Instance().OverrideAll(false);
	ConditionalOverrideManager::Instance().SetOverride(Conditional::whileChanneledAbility, false);
	ConditionalOverrideManager::Instance().SetOverride(Conditional::onHeadshot, true);
	ConditionalOverrideManager::Instance().SetOverride(Conditional::onShieldBreak, false);
	ConditionalOverrideManager::Instance().SetOverride(Conditional::onHeadshotKill, true);

	std::map<std::string, std::pair<float, bool>> bodyPartMultipliers = {{"Head", {3, true}}, {"Body", {1, false}}};
	auto target = std::make_shared<Target>(1, 1, 0, Faction::GRINEER, HealthType::GRINEER, bodyPartMultipliers);
	target->afflictedStatusEffects.push_back(ProcType::PT_BLEEDING);
	target->afflictedStatusEffects.push_back(ProcType::PT_POISONED);

	auto weapon = WeaponFactory::GetMK1Braton();

#pragma region ModDefinitions

	std::vector<std::shared_ptr<IModEffect>> baseDamageModEffects = {std::make_shared<ConstantModEffect>(DamageType::DT_ANY, ModUpgradeType::WEAPON_DAMAGE_AMOUNT, ModOperationType::STACKING_MULTIPLY, 1.65)};
	auto baseDamageMod = make_shared<Mod>("Serration", "Primary", ModPolarity::AP_ATTACK, 10, 10, 4, baseDamageModEffects);
	weapon->modManager->AddMod(baseDamageMod);

	std::vector<std::shared_ptr<IModEffect>> multishotModEffects1 = {std::make_shared<ConstantModEffect>(DamageType::DT_ANY, ModUpgradeType::WEAPON_MULTISHOT, ModOperationType::STACKING_MULTIPLY, 0.9)};
	auto multishotMod1 = std::make_shared<Mod>("Split Chamber", "Primary", ModPolarity::AP_ATTACK, 5, 5, 4, multishotModEffects1);
	weapon->modManager->AddMod(multishotMod1);

	std::vector<std::shared_ptr<IModEffect>> multishotModEffects2 = {std::make_shared<ConstantModEffect>(DamageType::DT_ANY, ModUpgradeType::WEAPON_MULTISHOT, ModOperationType::STACKING_MULTIPLY, 0.6)};
	auto multishotMod2 = std::make_shared<Mod>("Vigilante Armaments", "Primary", ModPolarity::AP_TACTIC, 5, 5, 4, multishotModEffects2);
	// weapon->modManager->AddMod(multishotMod2);

	std::vector<std::shared_ptr<IModEffect>> critDamageModEffects = {std::make_shared<ConstantModEffect>(DamageType::DT_ANY, ModUpgradeType::WEAPON_CRIT_DAMAGE, ModOperationType::STACKING_MULTIPLY, 1.2)};
	auto critDamage = std::make_shared<Mod>("Vital Sense", "Primary", ModPolarity::AP_ATTACK, 5, 5, 4, critDamageModEffects);
	weapon->modManager->AddMod(critDamage);

	std::vector<std::shared_ptr<IModEffect>> factionModEffects = {std::make_shared<FactionModEffect>(ModOperationType::STACKING_MULTIPLY, 0.3f, Faction::GRINEER)};
	auto baneOfGrineer = std::make_shared<Mod>("Bane of Grineer", "Primary", ModPolarity::AP_ATTACK, 5, 5, 4, factionModEffects);
	weapon->modManager->AddMod(baneOfGrineer);

	std::vector<std::shared_ptr<IModEffect>> conditionOverloadModEffects = {std::make_shared<WeaponDamageIfVictimProcActiveModEffect>(ModOperationType::STACKING_MULTIPLY, 0.8)};
	auto conditionOverload = std::make_shared<Mod>("Galvanized Aptitude", "Primary", ModPolarity::AP_ATTACK, 10, 10, 2, conditionOverloadModEffects);
	weapon->modManager->AddMod(conditionOverload);

	std::vector<std::shared_ptr<IModEffect>> critChanceModEffects = {
		std::make_shared<ConditionalModEffect>(std::make_shared<ConstantModEffect>(DamageType::DT_ANY, ModUpgradeType::WEAPON_CRIT_CHANCE, ModOperationType::STACKING_MULTIPLY, 1.2), Conditional::onHeadshot),
		std::make_shared<ConditionalModEffect>(std::make_shared<ConstantModEffect>(DamageType::DT_ANY, ModUpgradeType::WEAPON_CRIT_CHANCE, ModOperationType::STACKING_MULTIPLY, 2), Conditional::onHeadshotKill),
		std::make_shared<ConditionalModEffect>(std::make_shared<ConstantModEffect>(DamageType::DT_ANY, ModUpgradeType::WEAPON_CRIT_TIER, ModOperationType::ADD, 1), Conditional::onHeadshotKill)};
	auto critChance = std::make_shared<Mod>("Galvanized Scope", "Primary", ModPolarity::AP_ATTACK, 5, 5, 4, critChanceModEffects);
	weapon->modManager->AddMod(critChance);

	std::vector<std::shared_ptr<IModEffect>> elementalModEffects = {
		std::make_shared<ConstantModEffect>(DamageType::DT_FIRE, ModUpgradeType::WEAPON_PERCENT_BASE_DAMAGE_ADDED, ModOperationType::STACKING_MULTIPLY, 1.5),
		std::make_shared<ConstantModEffect>(DamageType::DT_ANY, ModUpgradeType::WEAPON_STATUS_CHANCE, ModOperationType::STACKING_MULTIPLY, 2.1)};
	auto elementalMod = std::make_shared<Mod>("90\% elemental mod", "Primary", ModPolarity::AP_ATTACK, 5, 5, 4, elementalModEffects);
	//weapon->modManager->AddMod(elementalMod);

	std::vector<std::shared_ptr<IModEffect>> acuityModEffects = {
		std::make_shared<ConstantModEffect>(DamageType::DT_ANY, ModUpgradeType::WEAPON_CRIT_CHANCE, ModOperationType::STACKING_MULTIPLY, 3.5),
		std::make_shared<ConstantModEffect>(DamageType::DT_ANY, ModUpgradeType::WEAPON_WEAK_POINT_MODIFIER, ModOperationType::ADD, 5.25)};
	auto acuityMod = std::make_shared<Mod>("Rifle Acuity", "Primary", ModPolarity::AP_TACTIC, 10, 10, 6, acuityModEffects);
	// weapon->modManager->AddMod(acuityMod);

	std::vector<std::shared_ptr<IModEffect>> targetAcquiredModEffects = {
		std::make_shared<ConstantModEffect>(DamageType::DT_ANY, ModUpgradeType::WEAPON_HEADSHOT_MULTIPLIER, ModOperationType::STACKING_MULTIPLY, 0.75)};
	auto daikyuTargetAcquiredMod = std::make_shared<Mod>("Amalgam Daikyu Target Acquired", "Primary", ModPolarity::AP_ATTACK, 5, 5, 10, targetAcquiredModEffects);
	// weapon->modManager->AddMod(daikyuTargetAcquiredMod);

	std::vector<std::shared_ptr<IModEffect>> arcaneModEffects = {
		std::make_shared<ConditionalModEffect>(std::make_shared<ConstantModEffect>(DamageType::DT_ANY, ModUpgradeType::WEAPON_DAMAGE_AMOUNT, ModOperationType::STACKING_MULTIPLY, 3.6), Conditional::onHeadshotKill),
		std::make_shared<ConstantModEffect>(DamageType::DT_ANY, ModUpgradeType::WEAPON_HEADSHOT_MULTIPLIER, ModOperationType::STACKING_MULTIPLY, 0.3),
		std::make_shared<ConstantModEffect>(DamageType::DT_ANY, ModUpgradeType::WEAPON_RECOIL, ModOperationType::STACKING_MULTIPLY, -0.5)};
	auto arcane = std::make_shared<Mod>("Primary Deadhead", "Primary", ModPolarity::AP_ATTACK, 5, 5, 0, arcaneModEffects);
	arcane->slotType = ModSlotType::MST_ARCANE;
	weapon->modManager->AddMod(arcane);

	// weapon->weaponData.incarnonUpgrades.SetActiveEvolution(0, 0);
	// weapon->weaponData.incarnonUpgrades.SetActiveEvolution(1, 1);
	// weapon->weaponData.incarnonUpgrades.SetActiveEvolution(2, 0);

	// weapon->modManager->PringCurrentModConfig();

#pragma endregion ModDefinitions

	std::string attackName = "Normal Attack";
	std::string targetBodyPart = "Body";
	int desiredProcess = 1;
	switch (desiredProcess)
	{
	case 1:
	{
		auto [directDamage, dotDamage] = weapon->Fire(attackName, target, targetBodyPart);
		ServiceLocator::GetService<ILogService>()->Log("Direct damage = " + std::to_string(directDamage));
		ServiceLocator::GetService<ILogService>()->Log("Damage over time = " + std::to_string(dotDamage));
		break;
	}
	case 2:
	{
		auto [directDamage, dotDamage] = weapon->GetAverageDamagePerShot(attackName, target, targetBodyPart);
		ServiceLocator::GetService<ILogService>()->Log("Average direct damage per shot = " + std::to_string(directDamage));
		ServiceLocator::GetService<ILogService>()->Log("Average DOT per second per shot = " + std::to_string(dotDamage));
		break;
	}
	case 3:
	{
		float avgBurstDPS = weapon->GetAverageBurstDPS(attackName, target, targetBodyPart);
		ServiceLocator::GetService<ILogService>()->Log("Average burst DPS = " + std::to_string(avgBurstDPS));
		break;
	}
	case 4:
	{
		float avgSustainedDPS = weapon->GetAverageSustainedDPS(attackName, target, targetBodyPart);
		ServiceLocator::GetService<ILogService>()->Log("Average sustained DPS = " + std::to_string(avgSustainedDPS));
		break;
	}
	default:
		break;
	}
};