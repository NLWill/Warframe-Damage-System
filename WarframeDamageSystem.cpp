#include <iostream>
#include <string>
#include "src/Services/Logging/LogService.h"
#include "src/Services/RNG/RNGService.h"
#include "src/Services/ServiceLocator.h"

#include "src/Mods/ModEffects/ProbabilityModEffectWrapper.h"
#include "src/Mods/ModEffects/ModEffect.h"
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

	std::map<std::string, std::pair<float, bool>> bodyPartMultipliers = {{"Head", {3, true}}, {"Body", {1, false}}};
	Target *target = new Target(1, 1, 0, Faction::NONE, HealthType::GRINEER, bodyPartMultipliers);

	Weapon *weapon = WeaponFactory::GetLexPrime();

	std::vector<ModEffectBase *> baseDamageModEffects = {new ModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_DAMAGE_AMOUNT, ModOperationType::STACKING_MULTIPLY, 2.2)};
	Mod *baseDamageMod = new Mod("Serration", "Primary", ModPolarity::MADURAI, 10, 10, 4, baseDamageModEffects);
	//weapon->AddMod(baseDamageMod, 0);

	std::vector<ModEffectBase *> multishotModEffects1 = {new ModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_MULTISHOT, ModOperationType::STACKING_MULTIPLY, 0.9)};
	Mod *multishotMod1 = new Mod("Split Chamber", "Primary", ModPolarity::MADURAI, 5, 5, 4, multishotModEffects1);
	//weapon->AddMod(multishotMod1, 1);

	std::vector<ModEffectBase *> multishotModEffects2 = {new ModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_MULTISHOT, ModOperationType::STACKING_MULTIPLY, 0.6)};
	Mod *multishotMod2 = new Mod("Vigilante Armaments", "Primary", ModPolarity::NARAMON, 5, 5, 4, multishotModEffects2);
	//weapon->AddMod(multishotMod2, 2);

	std::vector<ModEffectBase *> critDamageModEffects = {new ModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_CRIT_DAMAGE, ModOperationType::STACKING_MULTIPLY, 0.9)};
	Mod *critDamage = new Mod("Vital Sense", "Primary", ModPolarity::MADURAI, 5, 5, 4, critDamageModEffects);
	//weapon->AddMod(critDamage, 3);

	do
	{
		std::cout << "Testing the damage pipeline" << std::endl;
		std::cout << DamagePipeline::RunDamagePipeline(*weapon, "Incarnon", *target, "Body") << std::endl;
		std::cin >> inp;
	} while (inp == "y" || inp == "Y");

	// std::cin >> inp;
	delete weapon;
	delete target;
};