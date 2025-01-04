#include<string>
#include<vector>
#include<map>
#include "src/Weapons/AttackData.h"
#include "src/Mods/ModPolarity.h"
#include "src/Mods/ModBase.h"

struct WeaponData{
public:
	std::string name;
	std::string fileName;
	std::map<std::string, AttackData> attacks;
	std::vector<Mod> innateUpgrades;
	
	// Ammo related details
	int ammoCapacity;
	int ammoPickupCount;
	int magazineSize;
	float reloadTime;
	std::string reloadStyle;
	
	// For battery based weapons
	float reloadDelay;
	float reloadDelayEmpty;
	float batteryRegenRate;
	
	// For Spooling Weapons
	int spoolShotRamp;
	
	// Misc
	std::string weaponCategory;
	std::string equipSlot;
	std::vector<std::string> compatabilityTags;
	std::string weaponFamily;
	bool isLichWeapon;
	int levelCap;
	int masteryReq;
	
	// Riven details
	float rivenDisposition;
	
	// Modding Details
	int modSlotCount;
	ModPolarity exilusPolarity;
	std::vector<ModPolarity> modPolarities;

	
	// For snipers
	int hitNextTierOperator;
	float comboResetDelay;
};