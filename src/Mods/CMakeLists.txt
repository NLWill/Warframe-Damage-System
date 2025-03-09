add_subdirectory(ModEffects)

target_sources(${TARGET_NAME}
PRIVATE
ModBase.cpp
ModFactory.cpp
ModManager.cpp
ModUpgradeType.cpp
ModPolarity.cpp
ModOperationType.cpp
ModBaseDrain.cpp
ModFusionLimit.cpp
)

set(CPP_SOURCES
${CPP_SOURCES}
${CMAKE_CURRENT_LIST_DIR}/ModBase.cpp
${CMAKE_CURRENT_LIST_DIR}/ModFactory.cpp
${CMAKE_CURRENT_LIST_DIR}/ModManager.cpp
${CMAKE_CURRENT_LIST_DIR}/ModUpgradeType.cpp
${CMAKE_CURRENT_LIST_DIR}/ModPolarity.cpp
${CMAKE_CURRENT_LIST_DIR}/ModOperationType.cpp
${CMAKE_CURRENT_LIST_DIR}/ModBaseDrain.cpp
${CMAKE_CURRENT_LIST_DIR}/ModFusionLimit.cpp
PARENT_SCOPE)