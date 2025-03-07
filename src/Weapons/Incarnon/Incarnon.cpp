#include "src/Weapons/Incarnon/Incarnon.h"
#include "src/Services/ServiceLocator.h"
#include "src/Services/Logging/ILogService.h"

Incarnon::Incarnon(std::vector<std::vector<std::shared_ptr<Mod>>> evolutions) : _evolutions{evolutions}
{
	activeEvolutions = {};
	for (size_t i = 0; i < _evolutions.size(); i++)
	{
		activeEvolutions.push_back(100);
	}	
}

Incarnon::~Incarnon()
{
	/* This seems to be causing a crash when returning from the WeaponFactory methods????
	for (int i = 0; i < _evolutions.size(); i++){
		for (auto pointer : _evolutions[i]){
			delete pointer;
		}
		_evolutions[i].clear();
	}
	_evolutions.clear();
	*/
}

void Incarnon::SetActiveEvolution(unsigned int evoTier, unsigned int evoOption)
{
	if (!IsValidEvolutionTier(evoTier)){
		ServiceLocator::GetService<ILogService>()->LogWarning("Invalid incarnon evolution tier provided in SetActiveEvolution");
		return;
	}

	// Check that a valid evolution option is being selected. Special consideration may be given for evoOption == -1, as this shall represent no options selected.
	if (!IsValidEvolutionOption(evoTier, evoOption)){
		ServiceLocator::GetService<ILogService>()->LogWarning("Invalid incarnon evolution option provided in SetActiveEvolution");
		// Continue anyway and set activeEvolutions to this value, as it will disable all upgrades in this evoTier
	}

	activeEvolutions[evoTier] = evoOption;
}

std::shared_ptr<Mod> Incarnon::GetEvolutionEffect(unsigned int evoTier)
{
	if (!IsValidEvolutionOption(evoTier, activeEvolutions[evoTier])){
		return nullptr;
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

	for (unsigned int evoTier = 0; evoTier < GetNumberOfEvolutionTiers(); evoTier++)
	{
		if (!IsValidEvolutionOption(evoTier, activeEvolutions[evoTier])){
			// No option is selected on this tier, continue on next evoTier
			continue;
		}

		auto mod = GetEvolutionEffect(evoTier);

		if (mod == nullptr){
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
	if (evoTier >= _evolutions.size()){
		//ServiceLocator::GetService<ILogService>()->LogWarning("Invalid incarnon evolution tier");
		//ServiceLocator::GetService<ILogService>()->LogWarning("Evolutions size = " + std::to_string(GetNumberOfEvolutionTiers()));
		return false;
	}

	return true;
}

bool Incarnon::IsValidEvolutionOption(unsigned int evoTier, unsigned int evoOption)
{
	if (!IsValidEvolutionTier(evoTier)){
		return false;
	}

	if (evoOption >= _evolutions[evoTier].size()){
		//ServiceLocator::GetService<ILogService>()->LogWarning("Invalid incarnon evolution option");
		//ServiceLocator::GetService<ILogService>()->LogWarning("Evolution option = " + std::to_string(evoOption));
		return false;
	}

	return true;
}
