#pragma once
#include <vector>
#include "src/Mods/ModBase.h"

class Incarnon
{
public:
	Incarnon() = default;
	Incarnon(std::vector<std::vector<std::shared_ptr<Mod>>> evolutions);
	~Incarnon() = default;

	/// @brief Set the selected incarnon evolution active
	/// @param evoTier Incarnon tier of desired evolution
	/// @param evoOption Incarnon option of desired evolution
	void SetActiveEvolution(unsigned int evoTier, unsigned int evoOption);
	/// @brief Get the active mod effect for a given evolution tier
	/// @param evoTier The desired evolution tier
	/// @return The mod struct of the active evolution
	std::shared_ptr<Mod> GetEvolutionEffect(unsigned int evoTier);
	/// @brief Get the total number of evolution tiers available on the weapon
	/// @return
	unsigned int GetNumberOfEvolutionTiers();

	/// @brief Get all mod effects of active evolutions pertaining to the provided ModUpgradeType
	/// @param upgradeType
	/// @return
	std::vector<std::shared_ptr<IModEffect>> GetAllModEffects(ModUpgradeType upgradeType);

	/// @brief Iterate over each incarnon evolution tier and apply all mod effects of the active tier related to the provided ModUpgradeType
	/// @param damageInstance The damage instance that is currently being processed
	/// @param upgradeType The variable within the Damage Pipeline that is being evaluated
	/// @param modEffectValues The map of floats that stores the quantities of each ModOperationType over all mods
	void EvaluateModEffects(std::shared_ptr<IDamageInstance> damageInstance, ModUpgradeType upgradeType, std::map<ModOperationType, float> &modEffectValues);

private:
	/// @brief Check whether the provided value is a valid evolution tier
	/// @param evoTier The desired evolution tier
	/// @return Returns true if it is a valid incarnon evolution tier
	bool IsValidEvolutionTier(unsigned int evoTier);
	/// @brief Check that the desired evolution option is a valid option
	/// @param evoTier The desired evolution tier
	/// @param evoOption The desired evolution option
	/// @return Returns true if it is a valid incarnon evolution option
	bool IsValidEvolutionOption(unsigned int evoTier, unsigned int evoOption);

	/// @brief A vector of vectors containing all the evolution options available at each evolution tier
	std::vector<std::vector<std::shared_ptr<Mod>>> _evolutions;
	/// @brief A vector of the currently active evolution option at each tier
	std::vector<unsigned int> activeEvolutions;
};