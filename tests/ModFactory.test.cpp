#include "../src/Services/ServiceLocator.h"
#include "../src/Mods/ModFactory.h"
#include <string>

void assert(bool condition)
{
	if (!condition)
	{
		throw 1;
	}
}

int main()
{
	ServiceLocator::Initialise();

	try
	{
		Mod *modElec = ModFactory::GetMod("Electricity");
		Mod *modToxin = ModFactory::GetMod("Toxin");
		Mod *modTau = ModFactory::GetMod("Tau");

		assert(modElec->GetModEffects()[0]->GetDamageType() == DamageType::DT_ELECTRICITY);
		assert(modElec->name == "Electricity");
		assert(modElec->GetModEffects().size() == 1);
		assert(modElec->polarity == ModPolarity::AP_NONE);

		assert(modToxin->GetModEffects()[0]->GetDamageType() == DamageType::DT_POISON);
		assert(modTau->GetModEffects()[0]->GetDamageType() == DamageType::DT_TAU);

		/*
		std::string modName = "Serration";
		Mod* serration = ModFactory::GetMod(modName);
		assert(serration->name == modName);
		assert(serration->baseCapacityDrain == 4);
		assert(serration->GetCurrentCapacityDrain() == serration->rank + serration->baseCapacityDrain);
		assert(serration->maxRank == 10);
		assert(serration->polarity == ModPolarity::AP_ATTACK);
		assert(serration->modSet == "");

		bool correctCompatabilityTags = false;
		for (string tag : serration->compatabilityTags){
			if (tag == "Rifle"){
				correctCompatabilityTags = true;
			}
		}
		assert(correctCompatabilityTags);
		assert(serration->modFamily == "WeaponBaseDamageAmount");

		assert(serration->GetModEffects().size() == 1);
		assert(serration->GetModEffects()[0]->GetDamageType() == DamageType::DT_ANY);
		assert(serration->GetModEffects()[0]->GetModOperationType() == ModOperationType::STACKING_MULTIPLY);
		assert(serration->GetModEffects()[0]->GetUpgradeType() == ModUpgradeType::WEAPON_DAMAGE_AMOUNT);
		assert(serration->GetModEffects()[0]->GetModValue() == 0.15f + serration->rank * 0.15f);
		*/

		// Test a mod with two mod effects
		/*
		std::string modName = "Critical Deceleration";
		Mod *criticalDeceleration = ModFactory::GetMod(modName);
		assert(criticalDeceleration->name == modName);
		assert(criticalDeceleration->baseCapacityDrain == 4);
		assert(criticalDeceleration->rank == 5);
		assert(criticalDeceleration->GetCurrentCapacityDrain() == criticalDeceleration->rank + criticalDeceleration->baseCapacityDrain);
		assert(criticalDeceleration->maxRank == 5);
		assert(criticalDeceleration->polarity == ModPolarity::AP_ATTACK);
		assert(criticalDeceleration->modSet == "");

		bool correctCompatabilityTags = false;
		for (string tag : criticalDeceleration->compatabilityTags)
		{
			if (tag == "Shotgun")
			{
				correctCompatabilityTags = true;
			}
		}
		assert(correctCompatabilityTags);
		assert(criticalDeceleration->modFamily == "WeaponCritChanceMod");

		assert(criticalDeceleration->GetModEffects().size() == 2);
		for (int i = 0; i < 2; i++)
		{
			if (criticalDeceleration->GetModEffects()[i]->GetUpgradeType() == ModUpgradeType::WEAPON_CRIT_CHANCE)
			{
				assert(criticalDeceleration->GetModEffects()[i]->GetDamageType() == DamageType::DT_ANY);
				assert(criticalDeceleration->GetModEffects()[i]->GetModOperationType() == ModOperationType::STACKING_MULTIPLY);
				assert(criticalDeceleration->GetModEffects()[i]->GetUpgradeType() == ModUpgradeType::WEAPON_CRIT_CHANCE);
				assert(criticalDeceleration->GetModEffects()[i]->GetModValue() == 2.00f);
			}
			else
			{
				assert(criticalDeceleration->GetModEffects()[i]->GetDamageType() == DamageType::DT_ANY);
				assert(criticalDeceleration->GetModEffects()[i]->GetModOperationType() == ModOperationType::STACKING_MULTIPLY);
				assert(criticalDeceleration->GetModEffects()[i]->GetUpgradeType() == ModUpgradeType::WEAPON_FIRE_RATE);
				assert(criticalDeceleration->GetModEffects()[i]->GetModValue() == -0.2f);
			}
		}
		*/
	}
	catch (int errNum)
	{
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}