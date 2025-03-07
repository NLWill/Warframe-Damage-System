#include "src/Weapons/Incarnon/Incarnon.h"
#include "src/Services/ServiceLocator.h"
#include "src/Services/Logging/ILogService.h"
#include "src/Mods/ModFactory.h"

Incarnon::Incarnon(std::vector<std::vector<std::shared_ptr<Mod>>> evolutions) : _evolutions{evolutions}
{
	activeEvolutions = {};
	for (size_t i = 0; i < _evolutions.size(); i++)
	{
		// Set the active evolutions value to an impossible number to signify that no evolutions are active
		activeEvolutions.push_back(100);
	}
}

void Incarnon::SetActiveEvolution(unsigned int evoTier, unsigned int evoOption)
{
	if (!IsValidEvolutionTier(evoTier))
	{
		ServiceLocator::GetService<ILogService>()->LogWarning("Invalid incarnon evolution tier provided in SetActiveEvolution");
		return;
	}

	// Check that a valid evolution option is being selected. If not, disable all options on the provided evo tier
	if (!IsValidEvolutionOption(evoTier, evoOption))
	{
		ServiceLocator::GetService<ILogService>()->LogWarning("Invalid incarnon evolution option provided in SetActiveEvolution, disabling all options on this evolution tier");
		// Continue anyway and set activeEvolutions to this value, as it will disable all upgrades in this evoTier
	}

	activeEvolutions[evoTier] = evoOption;
}

std::shared_ptr<Mod> Incarnon::GetEvolutionEffect(unsigned int evoTier)
{
	// If the current active option is not a valid value, all are disabled so return an empty mod struct
	if (!IsValidEvolutionOption(evoTier, activeEvolutions[evoTier]))
	{
		return ModFactory::GetNullMod();
	}

	return _evolutions[evoTier][activeEvolutions[evoTier]];
}

unsigned int Incarnon::GetNumberOfEvolutionTiers()
{
	return _evolutions.size();
}

std::vector<std::shared_ptr<IModEffect>> Incarnon::GetAllModEffects(ModUpgradeType upgradeType)
{
	std::vector<std::shared_ptr<IModEffect>> relevantEffects;

	// Iterate over each evolution tier and if it is active add all effects relevant to the provided ModUpgradeType
	for (unsigned int evoTier = 0; evoTier < GetNumberOfEvolutionTiers(); evoTier++)
	{
		if (!IsValidEvolutionOption(evoTier, activeEvolutions[evoTier]))
		{
			// No option is selected on this tier, continue on next evoTier
			continue;
		}

		auto mod = GetEvolutionEffect(evoTier);

		if (mod == nullptr)
		{
			continue;
		}

		for (auto modEffect : mod->GetModEffects())
		{
			if (modEffect->GetUpgradeType() == upgradeType)
			{
				relevantEffects.push_back(modEffect);
			}
		}
	}

	return relevantEffects;
}

bool Incarnon::IsValidEvolutionTier(unsigned int evoTier)
{
	if (evoTier >= _evolutions.size())
	{
		// ServiceLocator::GetService<ILogService>()->LogWarning("Invalid incarnon evolution tier");
		// ServiceLocator::GetService<ILogService>()->LogWarning("Evolutions size = " + std::to_string(GetNumberOfEvolutionTiers()));
		return false;
	}

	return true;
}

bool Incarnon::IsValidEvolutionOption(unsigned int evoTier, unsigned int evoOption)
{
	if (!IsValidEvolutionTier(evoTier))
	{
		return false;
	}

	if (evoOption >= _evolutions[evoTier].size())
	{
		// ServiceLocator::GetService<ILogService>()->LogWarning("Invalid incarnon evolution option");
		// ServiceLocator::GetService<ILogService>()->LogWarning("Evolution option = " + std::to_string(evoOption));
		return false;
	}

	return true;
}
