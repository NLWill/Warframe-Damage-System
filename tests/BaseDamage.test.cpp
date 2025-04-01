#include "../src/Services/Logging/LogService.h"
#include "../src/Services/RNG/RNGService.h"

#include "../src/Weapons/WeaponFactory.h"
#include "../src/Services/ServiceLocator.h"
#include "../src/Services/Logging/ILogService.h"
#include "../src/Mods/ModEffects/ConstantModEffect.h"
#include "../src/Mods/ModEffects/ConditionalModEffectWrapper.h"
#include "../src/Mods/ModEffects/FactionModEffect.h"
#include "../src/Mods/ModEffects/WeaponDamageIfVictimProcActiveModEffect.h"
#include "../src/Weapons/WeaponFireFunctions.h"

#include <type_traits>
#include <vector>

void assert(bool condition)
{
	if (!condition)
	{
		throw 1;
	}
}

template <typename T>
void assert(T expected, T actual)
{
	if (expected != actual)
	{
		throw 1;
	}
}

template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
void AssertApproxEqual(T expected, T actual)
{

	T difference = std::abs(actual - expected);

	if (difference > 1e-3)
	{
		ServiceLocator::GetService<ILogService>()->LogError("Test Failed. Expected: " + std::to_string(expected) + " Actual: " + std::to_string(actual));
		throw 1;
	}
}

void TestConfiguration(std::shared_ptr<Weapon> weapon, std::string attackName, std::shared_ptr<Target> target, std::string targetBodyPart, float expectedNonCritValue, float expectedCritValue, int iterationCount)
{
	auto results = std::vector<float>();
	for (int i = 0; i < iterationCount; i++)
	{
		results.push_back(WeaponFireFunctions::Fire(weapon, attackName, target, targetBodyPart).first);
	}
	float minValue = results[0];
	float maxValue = results[0];
	for (auto value : results)
	{
		if (value < minValue)
			minValue = value;
		if (value > maxValue)
			maxValue = value;
	}

	AssertApproxEqual(expectedNonCritValue, minValue);
	AssertApproxEqual(expectedCritValue, maxValue);
}

int main()
{
	auto logSystem = std::make_shared<LogService>();
	ServiceLocator::RegisterService<ILogService>(logSystem);
	auto rngSystem = std::make_shared<RNGService>();
	ServiceLocator::RegisterService<IRNGService>(rngSystem);

	ConditionalOverrideManager::Instance().OverrideAll(true);

	float iterationCount = 100; // This should be high enough to guarantee a critical hit and non-crit under most circumstances (as long as CC is not ~99%)

	try
	{
		std::map<std::string, std::pair<float, bool>> bodyPartMultipliers = {{"Head", {3, true}}, {"Body", {1, false}}};

		auto targetDummy = std::make_shared<Target>(1, 1, 0, Faction::NONE, HealthType::TENNO, bodyPartMultipliers);

		auto targetGrineer = std::make_shared<Target>(1, 1, 0, Faction::GRINEER, HealthType::GRINEER, bodyPartMultipliers);

		auto weapon = WeaponFactory::GetMK1Braton();

		{
			float expectedDamageNonCrit = 18;
			float expectedDamageCrit = 27.0066;

			TestConfiguration(weapon, "Normal Attack", targetDummy, "Body", expectedDamageNonCrit, expectedDamageCrit, iterationCount);
		}

		{
			std::vector<std::shared_ptr<IModEffect>> baseDamageModEffects = {std::make_shared<ConstantModEffect>(DamageType::DT_ANY, ModUpgradeType::WEAPON_DAMAGE_AMOUNT, ModOperationType::STACKING_MULTIPLY, 1.65)};
			auto baseDamageMod = std::make_shared<Mod>("Serration", "/Lotus/Weapons/Tenno/Rifle/LotusRifle", ModPolarity::AP_ATTACK, 10, ModFusionLimit::QA_VERY_HIGH, ModBaseDrain::QA_MEDIUM, baseDamageModEffects);
			weapon->modManager->AddMod(baseDamageMod);

			float expectedDamageNonCrit = 47.7;
			float expectedDamageCrit = 71.5675;

			TestConfiguration(weapon, "Normal Attack", targetDummy, "Body", expectedDamageNonCrit, expectedDamageCrit, iterationCount);
		}

		{
			std::vector<std::shared_ptr<IModEffect>> critChanceModEffects = {
				std::make_shared<ConditionalModEffect>(std::make_shared<ConstantModEffect>(DamageType::DT_ANY, ModUpgradeType::WEAPON_CRIT_CHANCE, ModOperationType::STACKING_MULTIPLY, 1.2), Conditional::onHeadshot),
				std::make_shared<ConditionalModEffect>(std::make_shared<ConstantModEffect>(DamageType::DT_ANY, ModUpgradeType::WEAPON_CRIT_CHANCE, ModOperationType::STACKING_MULTIPLY, 2), Conditional::onHeadshotKill)};
			auto critChance = std::make_shared<Mod>("Galvanized Scope", "/Lotus/Weapons/Tenno/Rifle/LotusRifle", ModPolarity::AP_ATTACK, 5, ModFusionLimit::QA_HIGH, ModBaseDrain::QA_MEDIUM, critChanceModEffects);
			weapon->modManager->AddMod(critChance);

			std::vector<std::shared_ptr<IModEffect>> critDamageModEffects = {std::make_shared<ConstantModEffect>(DamageType::DT_ANY, ModUpgradeType::WEAPON_CRIT_DAMAGE, ModOperationType::STACKING_MULTIPLY, 1.2)};
			auto critDamage = std::make_shared<Mod>("Vital Sense", "/Lotus/Weapons/Tenno/Rifle/LotusRifle", ModPolarity::AP_ATTACK, 5, ModFusionLimit::QA_HIGH, ModBaseDrain::QA_MEDIUM, critDamageModEffects);
			weapon->modManager->AddMod(critDamage);

			std::vector<std::shared_ptr<IModEffect>> flatCritChanceModEffects = {std::make_shared<ConstantModEffect>(DamageType::DT_ANY, ModUpgradeType::WEAPON_CRIT_CHANCE, ModOperationType::ADD, 1)};
			auto flatCritChance = std::make_shared<Mod>("Flat Crit Chance Bonus", "/Lotus/Weapons/Tenno/Rifle/LotusRifle", ModPolarity::AP_ATTACK, 5, ModFusionLimit::QA_HIGH, ModBaseDrain::QA_MEDIUM, flatCritChanceModEffects);
			weapon->modManager->AddMod(flatCritChance);

			float expectedDamageNonCrit = 157.448;
			float expectedDamageCrit = 267.197;

			TestConfiguration(weapon, "Normal Attack", targetDummy, "Body", expectedDamageNonCrit, expectedDamageCrit, iterationCount);
		}

		{
			std::vector<std::shared_ptr<IModEffect>> multishotModEffects1 = {std::make_shared<ConstantModEffect>(DamageType::DT_ANY, ModUpgradeType::WEAPON_FIRE_ITERATIONS, ModOperationType::STACKING_MULTIPLY, 1)};
			auto multishotMod1 = std::make_shared<Mod>("Split Chamber", "/Lotus/Weapons/Tenno/Rifle/LotusRifle", ModPolarity::AP_ATTACK, 5, ModFusionLimit::QA_HIGH, ModBaseDrain::QA_MEDIUM, multishotModEffects1);
			multishotMod1->slotType = ModSlotType::MST_NORMAL;
			weapon->modManager->AddMod(multishotMod1);

			float expectedDamageNoCrits = 314.897;
			float expectedDamageAllCrits = 534.394;

			TestConfiguration(weapon, "Normal Attack", targetDummy, "Body", expectedDamageNoCrits, expectedDamageAllCrits, iterationCount);
		}

		{
			std::vector<std::shared_ptr<IModEffect>> factionModEffects = {std::make_shared<FactionModEffect>(ModOperationType::STACKING_MULTIPLY, 0.3f, Faction::GRINEER)};
			auto baneOfGrineer = std::make_shared<Mod>("Bane of Grineer", "/Lotus/Weapons/Tenno/Rifle/LotusRifle", ModPolarity::AP_ATTACK, 5, ModFusionLimit::QA_HIGH, ModBaseDrain::QA_MEDIUM, factionModEffects);
			weapon->modManager->AddMod(baneOfGrineer);

			float expectedDamageNoCrits = 460.537;
			float expectedDamageAllCrits = 781.551;

			TestConfiguration(weapon, "Normal Attack", targetGrineer, "Body", expectedDamageNoCrits, expectedDamageAllCrits, iterationCount);
		}

		{
			std::vector<std::shared_ptr<IModEffect>> conditionOverloadModEffects = {std::make_shared<WeaponDamageIfVictimProcActiveModEffect>(ModOperationType::STACKING_MULTIPLY, 0.8)};
			auto conditionOverload = std::make_shared<Mod>("Galvanized Aptitude", "/Lotus/Weapons/Tenno/Rifle/LotusRifle", ModPolarity::AP_ATTACK, 10, ModFusionLimit::QA_VERY_HIGH, ModBaseDrain::QA_LOW, conditionOverloadModEffects);
			weapon->modManager->AddMod(conditionOverload);

			targetGrineer->afflictedStatusEffects.push_back(ProcType::PT_BLEEDING);
			targetGrineer->afflictedStatusEffects.push_back(ProcType::PT_POISONED);

			float expectedDamageNoCrits = 738.597;
			float expectedDamageAllCrits = 1253.43;

			TestConfiguration(weapon, "Normal Attack", targetGrineer, "Body", expectedDamageNoCrits, expectedDamageAllCrits, iterationCount);
		}

		{
			std::vector<std::shared_ptr<IModEffect>> arcaneModEffects = {
				std::make_shared<ConditionalModEffect>(std::make_shared<ConstantModEffect>(DamageType::DT_ANY, ModUpgradeType::WEAPON_DAMAGE_AMOUNT, ModOperationType::STACKING_MULTIPLY, 3.6), Conditional::onHeadshotKill),
				std::make_shared<ConstantModEffect>(DamageType::DT_ANY, ModUpgradeType::WEAPON_HEADSHOT_MULTIPLIER, ModOperationType::STACKING_MULTIPLY, 0.3),
				std::make_shared<ConstantModEffect>(DamageType::DT_ANY, ModUpgradeType::WEAPON_RECOIL, ModOperationType::STACKING_MULTIPLY, -0.5)};
			auto arcane = std::make_shared<Mod>("/Lotus/Weapons/Tenno/Rifle/LotusRifle Deadhead", "/Lotus/Weapons/Tenno/Rifle/LotusRifle", ModPolarity::AP_ATTACK, 5, ModFusionLimit::QA_HIGH, ModBaseDrain::QA_NONE, arcaneModEffects);
			arcane->slotType = ModSlotType::MST_ARCANE;
			weapon->modManager->AddMod(arcane);

			float expectedDamageNoCrits = 1364.2314;
			float expectedDamageAllCrits = 2315.1604;

			TestConfiguration(weapon, "Normal Attack", targetGrineer, "Body", expectedDamageNoCrits, expectedDamageAllCrits, iterationCount);
		}
	}
	catch (int errNum)
	{
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}