target_sources(${TARGET_NAME}
PRIVATE
AttackData.cpp
DamageData.cpp
)

set(CPP_SOURCES
${CPP_SOURCES}
${CMAKE_CURRENT_LIST_DIR}/AttackData.cpp
${CMAKE_CURRENT_LIST_DIR}/DamageData.cpp
PARENT_SCOPE)