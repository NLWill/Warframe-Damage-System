add_subdirectory(Incarnon)

target_sources(${TARGET_NAME}
PRIVATE
AttackData.cpp
DamageType.cpp
StatusEffect.cpp
ProcType.cpp
Weapon.cpp
WeaponData.cpp
WeaponFactory.cpp
)

set(CPP_SOURCES
${CPP_SOURCES}
${CMAKE_CURRENT_LIST_DIR}/Weapon.cpp
${CMAKE_CURRENT_LIST_DIR}/WeaponData.cpp
${CMAKE_CURRENT_LIST_DIR}/AttackData.cpp
${CMAKE_CURRENT_LIST_DIR}/DamageType.cpp
${CMAKE_CURRENT_LIST_DIR}/StatusEffect.cpp
${CMAKE_CURRENT_LIST_DIR}/ProcType.cpp
${CMAKE_CURRENT_LIST_DIR}/WeaponFactory.cpp
PARENT_SCOPE)