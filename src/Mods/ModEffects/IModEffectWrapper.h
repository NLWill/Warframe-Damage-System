#pragma once
#include "src/Mods/IModEffect.h"

struct IModEffectWrapper : public IModEffect{
	public:
	virtual ~IModEffectWrapper() = default;
	
	/// @brief Evaluate whether this mod effect affects the provided ModUpgradeType and modify the modEffectValues entry appropriately
	/// @param damageInstance The damage instance that is currently being processed
	/// @param upgradeType The variable within the damage pipeline that is being processed
	/// @param modEffectValues The map of floats that stores the quantities of each ModOperationType over all mods
	virtual void EvaluateModEffect(std::shared_ptr<IDamageInstance> damageInstance, ModUpgradeType upgradeType, std::map<ModOperationType, float> &modEffectValues) = 0;
	/// @brief Get the magnitude to which this mod affects the associated ModUpgradeType
	/// @param damageInstance
	/// @return
	virtual float GetModValue(std::shared_ptr<IDamageInstance> damageInstance) = 0;
	/// @brief Get the average magnitude to which this mod affects the associated ModUpgradeType
	/// @param damageInstance
	/// @return
	virtual float GetAverageModValue(std::shared_ptr<IDamageInstance> damageInstance) = 0;

protected:
	/// @brief Get the damage type associated with the mod effect
	/// @return For elemental mods, returns the relevant damage type, otherwise returns DT_ANY
	DamageType GetDamageType();
	/// @brief Get the operation type that this mod applies to the associated ModUpgradeType
	/// @return
	ModOperationType GetModOperationType();
	/// @brief Get the variable within the damage pipeline that this mod affects
	/// @return
	ModUpgradeType GetUpgradeType();

	std::shared_ptr<IModEffect> _wrappedModEffect;
};