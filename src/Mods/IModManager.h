#pragma once
#include "src/Mods/ModBase.h"
#include <vector>

class IModManager
{
public:
	/// @brief Attempt to equip the provided mod into the provided slot index
	/// @param mod A shared pointer to the Mod struct
	/// @param modSlotIndex The index of the desired mod slot
	virtual void AddMod(std::shared_ptr<Mod> mod, unsigned int modSlotIndex) = 0;
	/// @brief Attempt to equip the provided mod into the first available mod slot
	/// @param mod A shared pointer to the Mod struct
	virtual void AddMod(std::shared_ptr<Mod> mod) = 0;
	/// @brief Remove any mod equipped at the provided slot index
	/// @param modSlotIndex The mod slot index to be emptied
	virtual void RemoveMod(unsigned int modSlotIndex) = 0;
	/// @brief Attempt to remove a mod with the given name
	/// @param name The name of the mod to be removed
	virtual void RemoveMod(std::string name) = 0;
	/// @brief Get the Mod struct at the given slot index
	/// @param modSlotIndex The desired slot index
	/// @return Returns a shared pointer to the Mod struct, or nullptr if no Mod is equipped in this slot
	virtual std::shared_ptr<Mod> GetMod(unsigned int modSlotIndex) = 0;
	/// @brief Get the number of mod slots on the weapon
	/// @return The total number of slots that can equip mods
	virtual int GetModSlotCount() = 0;
	/// @brief Print the current list of equipped mods to the terminal
	virtual void PringCurrentModConfig() = 0;

	/// @brief Retrieve a vector of all mod effects from the equipped mods that affect the specified ModUpgradeType
	/// @param upgradeType The variable within the Damage Pipeline that is being evaluated
	/// @return A vector of all relevant mod effects
	virtual std::vector<std::shared_ptr<IModEffect>> GetAllModEffects(ModUpgradeType upgradeType) = 0;

	/// @brief Iterate over all mods equipped and apply all of the mod effects pertaining to the ModUpgradeType
	/// @param damageInstance The damage instance that is currently being processed
	/// @param upgradeType The variable within the Damage Pipeline that is being evaluated
	/// @param modEffectValues The map of floats that stores the quantities of each ModOperationType over all mods
	virtual void EvaluateModEffects(std::shared_ptr<IDamageInstance> damageInstance, ModUpgradeType upgradeType, std::map<ModOperationType, float> &modEffectValues) = 0;

protected:
};