using <string>;
using "AttackData.h";
using "ModPolarity.h";

struct Weapon{
public:
	std::string name;
	std::string fileName;
	std::map<string, AttackData> attacks;
	std::array<std::string, int> innateUpgrades;
	
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
	std::array<std::string, int> compatabilityTags;
	std::string weaponFamily;
	bool isLichWeapon;
	int levelCap;
	int masteryReq;
	
	// Riven details
	float rivenDisposition;
	
	// Modding Details
	ModPolarity exilusPolarity;
	std::array<ModPolarity, int> modPolarities;
	
	// For snipers
	int hitNextTierOperator;
	float comboResetDelay;
}