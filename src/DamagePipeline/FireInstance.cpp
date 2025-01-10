#include "src/DamagePipeline/FireInstance.h"

std::vector<ModEffectBase *> FireInstance::GetAllModEffects(ModUpgradeType upgradeType)
{
	std::vector<ModEffectBase*> relevantEffects = {};

	for (auto mod : weapon->equippedMods){
		for (auto modEffect : mod->GetModEffects()){
			if (modEffect->GetUpgradeType() == upgradeType){
				relevantEffects.push_back(modEffect);
			}
		}
	}

	for (auto mod : weapon->data.innateUpgrades){
		for (auto modEffect : mod->GetModEffects()){
			if (modEffect->GetUpgradeType() == upgradeType){
				relevantEffects.push_back(modEffect);
			}
		}
	}

	/*
	for (auto mod : target->innateUpgrades){
		for (auto modEffect : mod->GetModEffects()){
			if (modEffect->GetUpgradeType() == upgradeType){
				relevantEffects.push_back(modEffect);
			}
		}
	}
	*/
	
	return std::vector<ModEffectBase *>();
}