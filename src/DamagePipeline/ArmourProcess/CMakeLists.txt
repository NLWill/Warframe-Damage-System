target_sources(${TARGET_NAME}
PRIVATE
ArmourProcess.cpp
)

set(CPP_SOURCES
${CPP_SOURCES}
${CMAKE_CURRENT_LIST_DIR}/ArmourProcess.cpp
PARENT_SCOPE
)