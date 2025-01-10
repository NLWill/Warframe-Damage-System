target_sources(${TARGET_NAME}
PRIVATE
StatusChanceProcess.cpp
)

set(CPP_SOURCES
${CPP_SOURCES}
${CMAKE_CURRENT_LIST_DIR}/StatusChanceProcess.cpp
PARENT_SCOPE
)