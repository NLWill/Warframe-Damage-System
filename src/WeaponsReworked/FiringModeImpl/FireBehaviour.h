#pragma once
#include <vector>
#include <string>

class FireBehaviour
{
public:
//AIMED_ACCURACY:{Spread:{SHOOTING:{range:[1,4],type:ST_EXPONENTIAL}}},
bool ignoreFireIterations;
bool isMeleeBehavior;
bool isSilenced;
bool roundUpAmmoConsumption;
bool scaleAmmoRequirement;
bool useAmmo;
bool ammoRequirement;
std::string ammoType;
int fireIterations;
float traceDistance;
float tracePunctureDepth;

private:

};