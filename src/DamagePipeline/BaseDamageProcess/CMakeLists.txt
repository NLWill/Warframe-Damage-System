target_sources(${TARGET_NAME}
PRIVATE
BaseDamageProcess.cpp
)

set(CPP_SOURCES
${CPP_SOURCES}
${CMAKE_CURRENT_LIST_DIR}/BaseDamageProcess.cpp
PARENT_SCOPE
)