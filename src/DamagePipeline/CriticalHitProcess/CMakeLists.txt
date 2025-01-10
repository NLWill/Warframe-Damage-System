target_sources(${TARGET_NAME}
PRIVATE
CriticalHitProcess.h
CriticalHitProcess.cpp
)

set(CPP_SOURCES
${CPP_SOURCES}
${CMAKE_CURRENT_LIST_DIR}/CriticalHitProcess.cpp
PARENT_SCOPE
)