target_sources(${TARGET_NAME}
PRIVATE
DatabaseManipulationFunctions.cpp
DatabaseRetrievalFunctions.cpp
)

set(CPP_SOURCES
${CPP_SOURCES}
${CMAKE_CURRENT_LIST_DIR}/DatabaseManipulationFunctions.cpp
${CMAKE_CURRENT_LIST_DIR}/DatabaseRetrievalFunctions.cpp
PARENT_SCOPE)