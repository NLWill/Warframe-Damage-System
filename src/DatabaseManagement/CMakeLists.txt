target_sources(${TARGET_NAME}
PRIVATE
DatabaseManipulationFunctions.cpp
)

set(CPP_SOURCES
${CPP_SOURCES}
${CMAKE_CURRENT_LIST_DIR}/DatabaseManipulationFunctions.cpp
PARENT_SCOPE)