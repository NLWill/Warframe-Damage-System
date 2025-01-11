target_sources(${TARGET_NAME}
PRIVATE
MultishotProcess.cpp
)

set(CPP_SOURCES
${CPP_SOURCES}
${CMAKE_CURRENT_LIST_DIR}/MultishotProcess.cpp
PARENT_SCOPE
)