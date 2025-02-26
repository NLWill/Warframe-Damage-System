target_sources(${TARGET_NAME}
PRIVATE
ConditionOverloadProcess.cpp
)

set(CPP_SOURCES
${CPP_SOURCES}
${CMAKE_CURRENT_LIST_DIR}/ConditionOverloadProcess.cpp
PARENT_SCOPE
)