target_sources(${TARGET_NAME}
PRIVATE
AttackData.h
DamageType.h
StatusEffect.h
Weapon.cpp
WeaponData.h
)

set(CPP_SOURCES
${CPP_SOURCES}
${CMAKE_CURRENT_LIST_DIR}/Weapon.cpp
PARENT_SCOPE)