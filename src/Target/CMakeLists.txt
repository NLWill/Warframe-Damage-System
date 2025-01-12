target_sources(${TARGET_NAME}
PRIVATE
Target.cpp
Faction.cpp
HealthType.cpp
)

set(CPP_SOURCES
${CPP_SOURCES}
${CMAKE_CURRENT_LIST_DIR}/Target.cpp
${CMAKE_CURRENT_LIST_DIR}/Faction.cpp
${CMAKE_CURRENT_LIST_DIR}/HealthType.cpp
PARENT_SCOPE
)