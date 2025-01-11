target_sources(${TARGET_NAME}
PRIVATE
AttackData.cpp
DamageType.h
StatusEffect.h
Weapon.cpp
WeaponData.cpp
)

set(CPP_SOURCES
${CPP_SOURCES}
${CMAKE_CURRENT_LIST_DIR}/Weapon.cpp
${CMAKE_CURRENT_LIST_DIR}/WeaponData.cpp
${CMAKE_CURRENT_LIST_DIR}/AttackData.cpp
PARENT_SCOPE)