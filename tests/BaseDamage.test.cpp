#include "../src/Services/Logging/LogService.h"
#include "../src/Services/RNG/RNGService.h"

#include "../src/Weapons/WeaponFactory.h"
#include "../src/Services/ServiceLocator.h"
#include "../src/Mods/ModEffects/ConstantModEffect.h"
#include "../src/Mods/ModEffects/ConditionalModEffectWrapper.h"
#include "../src/Mods/ModEffects/FactionModEffect.h"
#include "../src/Mods/ModEffects/WeaponDamageIfVictimProcActiveModEffect.h"

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
		ServiceLocator::GetLogger().LogError("Test Failed. Expected: " + std::to_string(expected) + " Actual: " + std::to_string(actual));
		throw 1;
	}
}

void TestConfiguration(Weapon *weapon, std::string attackName, Target *target, std::string targetBodyPart, float expectedNonCritValue, float expectedCritValue, int iterationCount)
{
	auto results = std::vector<float>();
	for (int i = 0; i < iterationCount; i++)
	{
		results.push_back(weapon->Fire("Normal Attack", *target, "Body").first);
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
	ServiceLocator::Initialise();
	auto logSystem = new LogService();
	ServiceLocator::Provide(logSystem);
	auto rngSystem = new RNGService();
	ServiceLocator::Provide(rngSystem);

	float iterationCount = 100; // This should be high enough to guarantee a critical hit and non-crit under most circumstances (as long as CC is not ~99%)

	try
	{
		std::map<std::string, std::pair<float, bool>> bodyPartMultipliers = {{"Head", {3, true}}, {"Body", {1, false}}};

		Target *targetDummy = new Target(1, 1, 0, Faction::NONE, HealthType::TENNO, bodyPartMultipliers, {});

		Target *targetGrineer = new Target(1, 1, 0, Faction::GRINEER, HealthType::GRINEER, bodyPartMultipliers, {});

		Weapon *weapon = WeaponFactory::GetMK1Braton();

		{
			float expectedDamageNonCrit = 18;
			float expectedDamageCrit = 27.0066;

			TestConfiguration(weapon, "Normal Attack", targetDummy, "Body", expectedDamageNonCrit, expectedDamageCrit, iterationCount);
		}

		{
			std::vector<ModEffectBase *> baseDamageModEffects = {new ConstantModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_DAMAGE_AMOUNT, ModOperationType::STACKING_MULTIPLY, 1.65)};
			Mod *baseDamageMod = new Mod("Serration", "Primary", ModPolarity::AP_ATTACK, 10, 10, 4, baseDamageModEffects);
			baseDamageMod->slotType = ModSlotType::MST_NORMAL;
			weapon->modManager->AddMod(baseDamageMod, 0);

			float expectedDamageNonCrit = 47.7;
			float expectedDamageCrit = 71.5675;

			TestConfiguration(weapon, "Normal Attack", targetDummy, "Body", expectedDamageNonCrit, expectedDamageCrit, iterationCount);
		}

		{
			std::vector<ModEffectBase *> critChanceModEffects = {
				new ConstantModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_CRIT_CHANCE, ModOperationType::STACKING_MULTIPLY, 3.2)};
			Mod *critChance = new Mod("Galvanized Scope", "Primary", ModPolarity::AP_ATTACK, 5, 5, 4, critChanceModEffects);
			critChance->slotType = ModSlotType::MST_NORMAL;
			weapon->modManager->AddMod(critChance, 1);

			std::vector<ModEffectBase *> critDamageModEffects = {new ConstantModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_CRIT_DAMAGE, ModOperationType::STACKING_MULTIPLY, 1.2)};
			Mod *critDamage = new Mod("Vital Sense", "Primary", ModPolarity::AP_ATTACK, 5, 5, 4, critDamageModEffects);
			critDamage->slotType = ModSlotType::MST_NORMAL;
			weapon->modManager->AddMod(critDamage, 2);

			std::vector<ModEffectBase *> flatCritChanceModEffects = {
				new ConstantModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_CRIT_CHANCE, ModOperationType::ADD, 1)};	// Add a flat 100% crit chance to increase crit tier by 1
			Mod *flatCritChance = new Mod("Flat CC bonus", "Primary", ModPolarity::AP_ATTACK, 5, 5, 4, flatCritChanceModEffects);
			flatCritChance->slotType = ModSlotType::MST_NORMAL;
			weapon->modManager->AddMod(flatCritChance, 3);

			float expectedDamageNonCrit = 157.448;
			float expectedDamageCrit = 267.197;
		}

		{
			std::vector<ModEffectBase *> multishotModEffects1 = {new ConstantModEffect(DamageType::DT_ANY, ModUpgradeType::WEAPON_MULTISHOT, ModOperationType::STACKING_MULTIPLY, 1)};
			Mod *multishotMod1 = new Mod("Split Chamber", "Primary", ModPolarity::AP_ATTACK, 5, 5, 4, multishotModEffects1);
			multishotMod1->slotType = ModSlotType::MST_NORMAL;
			weapon->modManager->AddMod(multishotMod1, 4);

			float expectedDamageNoCrits = 314.897;
			float expectedDamageAllCrits = 534.394;

			TestConfiguration(weapon, "Normal Attack", targetDummy, "Body", expectedDamageNoCrits, expectedDamageAllCrits, iterationCount);
		}

		{
			std::vector<ModEffectBase *> factionModEffects = {new FactionModEffect(ModOperationType::STACKING_MULTIPLY, 0.3f, Faction::GRINEER)};
			Mod *baneOfGrineer = new Mod("Bane of Grineer", "Primary", ModPolarity::AP_ATTACK, 5, 5, 4, factionModEffects);
			baneOfGrineer->slotType = ModSlotType::MST_NORMAL;
			weapon->modManager->AddMod(baneOfGrineer, 5);

			float expectedDamageNoCrits = 460.537;
			float expectedDamageAllCrits = 781.551;

			TestConfiguration(weapon, "Normal Attack", targetGrineer, "Body", expectedDamageNoCrits, expectedDamageAllCrits, iterationCount);
		}

		{
			std::vector<ModEffectBase *> conditionOverloadModEffects = {new WeaponDamageIfVictimProcActiveModEffect(ModOperationType::STACKING_MULTIPLY, 0.8)};
			Mod *conditionOverload = new Mod("Galvanized Aptitude", "Primary", ModPolarity::AP_ATTACK, 10, 10, 2, conditionOverloadModEffects);
			conditionOverload->slotType = ModSlotType::MST_NORMAL;
			weapon->modManager->AddMod(conditionOverload, 6);
	
			targetGrineer->afflictedStatusEffects.push_back(ProcType::PT_BLEEDING);
			targetGrineer->afflictedStatusEffects.push_back(ProcType::PT_POISONED);

			float expectedDamageNoCrits = 738.597;
			float expectedDamageAllCrits = 1253.43;

			TestConfiguration(weapon, "Normal Attack", targetGrineer, "Body", expectedDamageNoCrits, expectedDamageAllCrits, iterationCount);
		}
	}
	catch (int errNum)
	{
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}