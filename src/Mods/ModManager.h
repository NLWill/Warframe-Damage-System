#pragma once
#include <memory>
#include "src/Mods/IModManager.h"
#include "src/Mods/ModSlotType.h"

class ModManager : public IModManager
{
public:
	ModManager(const std::vector<std::pair<ModSlotType, ModPolarity>> modSlotDetails, const std::vector<std::string> compatabilityTags);

	/// @brief Attempt to equip the provided mod into the provided slot index
	/// @param mod A shared pointer to the Mod struct
	/// @param modSlotIndex The index of the desired mod slot
	virtual void AddMod(std::shared_ptr<Mod> mod, unsigned int modSlotIndex);
	/// @brief Attempt to equip the provided mod into the first available mod slot
	/// @param mod A shared pointer to the Mod struct
	virtual void AddMod(std::shared_ptr<Mod> mod);
	/// @brief Remove any mod equipped at the provided slot index
	/// @param modSlotIndex The mod slot index to be emptied
	virtual void RemoveMod(unsigned int modSlotIndex);
	/// @brief Attempt to remove a mod with the given name
	/// @param name The name of the mod to be removed
	virtual void RemoveMod(std::string name);
	/// @brief Get the Mod struct at the given slot index
	/// @param modSlotIndex The desired slot index
	/// @return Returns a shared pointer to the Mod struct, or nullptr if no Mod is equipped in this slot
	virtual std::shared_ptr<Mod> GetMod(unsigned int modSlotIndex);
	/// @brief Get the number of mod slots on the weapon
	/// @return The total number of slots that can equip mods
	virtual int GetModSlotCount();
	/// @brief Print the current list of equipped mods to the terminal
	virtual void PringCurrentModConfig();

	/// @brief Get a vector of ModEffects which affect the provided ModUpgradeType
	/// @param upgradeType The variable within the Damage Pipeline that is being evaluated
	/// @return A vector of shared pointers to all mod effects which affect the associated ModUpgradeType
	virtual std::vector<std::shared_ptr<IModEffect>> GetAllModEffects(ModUpgradeType upgradeType);

private:
	/// @brief List of the mod slots, nullptr for an absent mod
	std::vector<std::shared_ptr<Mod>> equippedMods;
	/// @brief Restrictions placed on each mod slot. Mods must have matching ModSlotType to be equipped in a slot
	std::vector<std::pair<ModSlotType, ModPolarity>> modSlotDetails;
	/// @brief List of compatability tags that prevent the Mod being equipped on certain weapons
	std::vector<std::string> weaponCompatabilityTags;

	/// @brief Check whether the provided Mod is allowed to be equipped at the desired slot index
	/// @param mod Shared pointer to the Mod wanting to be equipped
	/// @param modSlotIndex Slot index for where the Mod is to be equipped
	/// @param outputWarnings Boolean for whether warnings should be output to console if failing to equip the Mod
	/// @return Returns true if the Mod may be equipped in this slot
	bool CanEquipMod(std::shared_ptr<Mod> mod, unsigned int modSlotIndex, bool outputWarnings = false);
	/// @brief Check that the provided slot index is within the range of mod slot size
	/// @param modSlotIndex
	/// @return
	bool CheckValidModSlotIndex(unsigned int modSlotIndex);
	/// @brief Check that the provided Mod may be equipped due to restrictions from ModSlotType
	/// @param mod Shared pointer to the Mod wanting to be equipped
	/// @param modSlotIndex Index of the mod slot where the Mod is being equipped
	/// @return Returns true if the Mod does not clash with slot type restrictions in this mod slot
	bool CheckModSlotRestrictions(std::shared_ptr<Mod> mod, unsigned int modSlotIndex);
};