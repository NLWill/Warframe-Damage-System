#pragma once
#include <vector>
#include "src/Mods/ModBase.h"

class Incarnon{
public:
Incarnon() = default;
Incarnon(std::vector<std::vector<shared_ptr<Mod>>> evolutions);
~Incarnon();
void SetActiveEvolution(unsigned int evoTier, unsigned int evoOption);
shared_ptr<Mod> GetEvolutionEffect(unsigned int evoTier);
unsigned int GetNumberOfEvolutionTiers();
std::vector<shared_ptr<IModEffect>> GetAllModEffects(ModUpgradeType upgradeType);

private:
bool IsValidEvolutionTier(unsigned int evoTier);
bool IsValidEvolutionOption(unsigned int evoTier, unsigned int evoOption);
std::vector<std::vector<shared_ptr<Mod>>> _evolutions;
std::vector<int> activeEvolutions;
std::string weaponFamily;
};