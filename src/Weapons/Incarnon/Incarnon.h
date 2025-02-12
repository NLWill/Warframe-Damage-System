#pragma once
#include <vector>
#include "src/Mods/ModBase.h"

class Incarnon{
public:
Incarnon() = default;
Incarnon(std::vector<std::vector<Mod *>> evolutions);
void SetActiveEvolution(int evoTier, int evoOption);
Mod *GetEvolutionEffect(int evoTier);
int GetNumberOfEvolutionTiers();
std::vector<ModEffectBase *> GetAllModEffects(ModUpgradeType upgradeType);

private:
bool IsValidEvolutionTier(int evoTier);
bool IsValidEvolutionOption(int evoTier, int evoOption);
std::vector<std::vector<Mod *>> _evolutions;
std::vector<int> activeEvolutions;
std::string weaponFamily;
};