#pragma once
#include "src/Mods/ModOperationType.h"
#include "src/Weapons/DamageType.h"
#include "src/Mods/ModUpgradeType.h"
#include "src/DamagePipeline/IDamageInstance.h"

struct IModEffect{
	public:
	virtual ~IModEffect() {};
	/// @brief Get the damage type associated with the mod effect
	/// @return For elemental mods, returns the relevant damage type, otherwise returns DT_ANY
	virtual DamageType GetDamageType() = 0;
	/// @brief Get the operation type that this mod applies to the associated ModUpgradeType
	/// @return 
	virtual ModOperationType GetModOperationType() = 0;
	/// @brief Get the variable that this mod affects
	/// @return 
	virtual ModUpgradeType GetUpgradeType() = 0;
	/// @brief Get the magnitude to which this mod affects the associated ModUpgradeType
	/// @param damageInstance 
	/// @return 
	virtual float GetModValue(std::shared_ptr<IDamageInstance> damageInstance) = 0;
	/// @brief Get the average magnitude to which this mod affects the associated ModUpgradeType
	/// @param damageInstance 
	/// @return 
	virtual float GetAverageModValue(std::shared_ptr<IDamageInstance> damageInstance) = 0;
};