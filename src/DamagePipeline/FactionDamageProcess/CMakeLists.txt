target_sources(${TARGET_NAME}
PRIVATE
FactionDamageProcess.cpp
)

set(CPP_SOURCES
${CPP_SOURCES}
${CMAKE_CURRENT_LIST_DIR}/FactionDamageProcess.cpp
PARENT_SCOPE
)