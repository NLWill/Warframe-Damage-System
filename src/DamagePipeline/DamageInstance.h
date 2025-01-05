#include<map>
#include<vector>
#include "src/Weapons/DamageType.h"
#include "src/Weapons/StatusEffect.h"

class DamageInstance{
public:
std::map<DamageType, float> attackData;
std::vector<StatusEffect> statusEffects; 


private:


}