#include "src/Mods/ModFactory.h"
#include "src/Mods/ModEffects/ConstantModEffect.h"
#include "src/DatabaseManagement/DatabaseManipulationFunctions.h"
#include "src/DatabaseManagement/DatabaseRetrievalFunctions.h"
#include "src/Mods/ModBaseDrain.h"
#include "src/Mods/ModFusionLimit.h"
#include <fstream>

#include "src/Services/ServiceLocator.h"
#include "src/Services/Logging/ILogService.h"

#include "src/Mods/ModEffects/ConstantModEffect.h"
#include "src/Mods/ModEffects/FactionModEffect.h"
#include "src/Mods/ModEffects/WeaponDamageIfVictimProcActiveModEffect.h"

#define DEBUG_MOD_FACTORY false

std::shared_ptr<Mod> ModFactory::GetNullMod()
{
	auto mod = std::make_shared<Mod>();
	mod->name = "Null Mod";
	mod->itemCompatibility = "";
	mod->polarity = ModPolarity::AP_UNIVERSAL;
	mod->rank = 0;
	mod->maxRank = ModFusionLimit::QA_NONE;
	mod->baseCapacityDrain = ModBaseDrain::QA_NONE;

	return mod;
}

std::shared_ptr<Mod> ModFactory::GetMod(std::string name)
{
#if DEBUG_MOD_FACTORY
	ServiceLocator::GetService<ILogService>()->Log("Initiated GetMod process");
#endif

	std::string databaseData = DatabaseRetrievalFunctions::GetModData(name);

	return CreateMod(databaseData);
}

std::shared_ptr<Mod> ModFactory::CreateMod(std::string databaseData)
{
#if DEBUG_MOD_FACTORY
	ServiceLocator::GetService<ILogService>()->Log("Creating the Mod");
#endif

	// Create an empty mod that we will then populate with data
	std::shared_ptr<Mod> mod = std::make_shared<Mod>();

	ProcessOverallModDataStruct(mod, databaseData);

#if DEBUG_MOD_FACTORY
	ServiceLocator::GetService<ILogService>()->Log("Created the Mod");
	ServiceLocator::GetService<ILogService>()->Log("Mod name = " + mod->name);
	ServiceLocator::GetService<ILogService>()->Log("Mod itemCompatibility = " + mod->itemCompatibility);
	ServiceLocator::GetService<ILogService>()->Log("ModSlotType = " + mod->slotType.ToString());
	ServiceLocator::GetService<ILogService>()->Log("ModPolarity = " + ModPolarity::ToString(mod->polarity));
#endif

	return mod;
}

void ModFactory::ProcessOverallModDataStruct(std::shared_ptr<Mod> mod, std::string databaseData)
{
	// Currently the data should be in the OverallModData form (Look at data/Mods/Mod Data Structure.txt for reference)
	auto categoryDataPairs = DatabaseManipulationFunctions::ExtractCategoryDataPairs(databaseData);
	for (size_t i = 0; i < categoryDataPairs.size(); i++)
	{
		// Parse the data category and then hash it to use switch statement
		std::string category = DatabaseManipulationFunctions::ParseString(categoryDataPairs[i].first);
		switch (HashString(category))
		{
		case DatabaseCategoryCode::data:
			ProcessDataStruct(mod, DatabaseManipulationFunctions::ExtractStructData(categoryDataPairs[i].second));
			break;
		case DatabaseCategoryCode::id:
			mod->id = DatabaseManipulationFunctions::ParseInt(categoryDataPairs[i].second);
			break;
		case DatabaseCategoryCode::name:
			mod->name = DatabaseManipulationFunctions::ParseString(categoryDataPairs[i].second);
			break;
		case DatabaseCategoryCode::parent:
			mod->parent = DatabaseManipulationFunctions::ParseString(categoryDataPairs[i].second);
			break;
		case DatabaseCategoryCode::parents:
			for (std::string &parent : DatabaseManipulationFunctions::ExtractArrayData(categoryDataPairs[i].second))
			{
				mod->parents.push_back(DatabaseManipulationFunctions::ParseString(parent));
			}
			break;
		case DatabaseCategoryCode::path:
			mod->filePath = DatabaseManipulationFunctions::ParseString(categoryDataPairs[i].second);
			break;
		default:
			break;
		}
	}
}

void ModFactory::ProcessDataStruct(std::shared_ptr<Mod> mod, std::vector<std::pair<std::string, std::string>> categoryDataPairs)
{
	for (size_t i = 0; i < categoryDataPairs.size(); i++)
	{
		// Parse the data category and then hash it to use switch statement
		std::string category = DatabaseManipulationFunctions::ParseString(categoryDataPairs[i].first);
		switch (HashString(category))
		{
		case DatabaseCategoryCode::compatabilityTags:
			for (std::string &compatabilityTag : DatabaseManipulationFunctions::ExtractArrayData(categoryDataPairs[i].second))
			{
				mod->compatabilityTags.push_back(DatabaseManipulationFunctions::ParseString(compatabilityTag));
			}
			break;
		case DatabaseCategoryCode::incompatabilityTags:
			for (std::string &incompatabilityTag : DatabaseManipulationFunctions::ExtractArrayData(categoryDataPairs[i].second))
			{
				mod->incompatabilityTags.push_back(DatabaseManipulationFunctions::ParseString(incompatabilityTag));
			}
			break;
		case DatabaseCategoryCode::itemCompatibility:
			mod->itemCompatibility = DatabaseManipulationFunctions::ParseString(categoryDataPairs[i].second);
			break;
		case DatabaseCategoryCode::polarity:
			mod->polarity = ModPolarity::ParseFromString(DatabaseManipulationFunctions::ParseString(categoryDataPairs[i].second));
			break;
		case DatabaseCategoryCode::slotType:
			mod->slotType = ModSlotType::ParseFromString(DatabaseManipulationFunctions::ParseString(categoryDataPairs[i].second));
			break;
		case DatabaseCategoryCode::fusionLimit:
			mod->maxRank = ModFusionLimit::ParseFromString(DatabaseManipulationFunctions::ParseString(categoryDataPairs[i].second));
			mod->rank = ModFusionLimit::GetMaximumModRank(mod->maxRank); // Set the rank to max rank as the majority of users will consult at maximum performance
			break;
		case DatabaseCategoryCode::baseCapacityDrain:
			mod->baseCapacityDrain = ModBaseDrain::ParseFromString(DatabaseManipulationFunctions::ParseString(categoryDataPairs[i].second));
			break;
		case DatabaseCategoryCode::disableCapacityDrain:
			mod->disableCapacityDrain = DatabaseManipulationFunctions::ParseBool(categoryDataPairs[i].second);
			break;
		case DatabaseCategoryCode::modSet:
			mod->modSet = DatabaseManipulationFunctions::ParseString(categoryDataPairs[i].second);
			break;
		case DatabaseCategoryCode::upgrades:
			for (std::string upgrade : DatabaseManipulationFunctions::ExtractArrayData(categoryDataPairs[i].second))
			{
				auto modEffectCategoryDataPairs = DatabaseManipulationFunctions::ExtractStructData(upgrade);
				mod->AddModEffect(ProcessModEffectData(modEffectCategoryDataPairs));
			}
			break;
		default:
			break;
		}
	}
}

std::shared_ptr<IModEffect> ModFactory::ProcessModEffectData(std::vector<std::pair<std::string, std::string>> categoryDataPairs)
{
	// First of all find the key attributes for this mod effect
	ModUpgradeType upgradeType = ModUpgradeType::NO_EFFECT;
	ModOperationType operationType = ModOperationType::NONE;
	DamageType damageType = DamageType::DT_ANY;
	float value = 0;

	for (size_t i = 0; i < categoryDataPairs.size(); i++)
	{
		std::string category = DatabaseManipulationFunctions::ParseString(categoryDataPairs[i].first);
		switch (HashString(category))
		{
		case DatabaseCategoryCode::upgradeType:
			upgradeType = ModUpgradeType::ParseFromString(DatabaseManipulationFunctions::ParseString(categoryDataPairs[i].second));
#if DEBUG_MOD_FACTORY
			ServiceLocator::GetService<ILogService>()->Log("Got upgradeType " + ModUpgradeType::ToString(upgradeType));
#endif
			break;
		case DatabaseCategoryCode::operationType:
			operationType = ModOperationType::ParseFromString(DatabaseManipulationFunctions::ParseString(categoryDataPairs[i].second));
#if DEBUG_MOD_FACTORY
			ServiceLocator::GetService<ILogService>()->Log("Got operationType " + ModOperationType::ToString(operationType));
#endif
			break;
		case DatabaseCategoryCode::damageType:
			damageType = DamageType::ParseDamageTypeName(DatabaseManipulationFunctions::ParseString(categoryDataPairs[i].second));
#if DEBUG_MOD_FACTORY
			ServiceLocator::GetService<ILogService>()->Log("Got damageType " + damageType.ToString());
#endif
			break;
		case DatabaseCategoryCode::value:
			value = DatabaseManipulationFunctions::ParseFloat(categoryDataPairs[i].second);
#if DEBUG_MOD_FACTORY
			ServiceLocator::GetService<ILogService>()->Log("Got value " + std::to_string(value));
#endif
			break;
		default:
			break;
		}
	}
	// Check that the necessary attributes are set off from the default value
	// It is not a problem if damageType == DT_ANY, as any mod with elements has this
	// And value being 0 may be desired somehow
	if (upgradeType == ModUpgradeType::NO_EFFECT)
	{
		ServiceLocator::GetService<ILogService>()->LogError("Failed to find ModUpgradeType");
		std::__throw_invalid_argument("UpgradeType not found within upgrade data");
	}
	if (operationType == ModOperationType::NONE)
	{
		ServiceLocator::GetService<ILogService>()->LogError("Failed to find ModOperationType");
		std::__throw_invalid_argument("ModOperationType not found within upgrade data");
	}

	// Create the base IModEffect that may be wrapped in other conditional wrappers
	std::shared_ptr<IModEffect> modEffect;
	switch (upgradeType)
	{
	case ModUpgradeType::GAMEPLAY_FACTION_DAMAGE:
	{
		// Since it is a faction damage effect, the required faction needs to be found
		Faction requiredFaction = Faction::NONE;
		for (size_t i = 0; i < categoryDataPairs.size(); i++)
		{
			std::string category = DatabaseManipulationFunctions::ParseString(categoryDataPairs[i].first);
			if (HashString(category) == DatabaseCategoryCode::factionType)
			{
				requiredFaction = Faction::ParseFactionName(DatabaseManipulationFunctions::ParseString(categoryDataPairs[i].second));
				break;
			}
		}

		modEffect = std::make_shared<FactionModEffect>(operationType, value, requiredFaction);
		break;
	}
	case ModUpgradeType::WEAPON_DAMAGE_AMOUNT_IF_VICTIM_PROC_ACTIVE:
		modEffect = std::make_shared<WeaponDamageIfVictimProcActiveModEffect>(operationType, value);
		break;
	default:
		modEffect = std::make_shared<ConstantModEffect>(damageType, upgradeType, operationType, value);
		break;
	}

	return modEffect;
}

ModFactory::DatabaseCategoryCode ModFactory::HashString(std::string &category)
{
	if (category == "data")
		return DatabaseCategoryCode::data;
	if (category == "id")
		return DatabaseCategoryCode::id;
	if (category == "name")
		return DatabaseCategoryCode::name;
	if (category == "parent")
		return DatabaseCategoryCode::parent;
	if (category == "parents")
		return DatabaseCategoryCode::parents;
	if (category == "path")
		return DatabaseCategoryCode::path;
	if (category == "CompatabilityTags")
		return DatabaseCategoryCode::compatabilityTags;
	if (category == "IncompatabilityTags")
		return DatabaseCategoryCode::incompatabilityTags;
	if (category == "ItemCompatibility")
		return DatabaseCategoryCode::itemCompatibility;
	if (category == "ArtifactPolarity")
		return DatabaseCategoryCode::polarity;
	if (category == "ModSlotType")
		return DatabaseCategoryCode::slotType;
	if (category == "FusionLimit")
		return DatabaseCategoryCode::fusionLimit;
	if (category == "DisableCapacityDrain")
		return DatabaseCategoryCode::disableCapacityDrain;
	if (category == "BaseDrain")
		return DatabaseCategoryCode::baseCapacityDrain;
	if (category == "ModSet")
		return DatabaseCategoryCode::modSet;
	if (category == "Upgrades")
		return DatabaseCategoryCode::upgrades;
	if (category == "UpgradeType")
		return DatabaseCategoryCode::upgradeType;
	if (category == "DamageType")
		return DatabaseCategoryCode::damageType;
	if (category == "OperationType")
		return DatabaseCategoryCode::operationType;
	if (category == "Value")
		return DatabaseCategoryCode::value;
	if (category == "SymbolFilter")
		return DatabaseCategoryCode::factionType;
		
#if DEBUG_MOD_FACTORY
	ServiceLocator::GetService<ILogService>()->LogError("Failed to parse category " + category);
#endif
	return DatabaseCategoryCode::ignoreEntry;
}