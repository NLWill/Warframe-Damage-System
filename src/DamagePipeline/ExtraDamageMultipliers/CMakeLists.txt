target_sources(${TARGET_NAME}
PRIVATE
ExtraDamageMultipliers.cpp
)

set(CPP_SOURCES
${CPP_SOURCES}
${CMAKE_CURRENT_LIST_DIR}/ExtraDamageMultipliers.cpp
PARENT_SCOPE
)