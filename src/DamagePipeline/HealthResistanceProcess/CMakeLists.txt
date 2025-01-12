target_sources(${TARGET_NAME}
PRIVATE
HealthResistanceProcess.cpp
)

set(CPP_SOURCES
${CPP_SOURCES}
${CMAKE_CURRENT_LIST_DIR}/HealthResistanceProcess.cpp
PARENT_SCOPE
)