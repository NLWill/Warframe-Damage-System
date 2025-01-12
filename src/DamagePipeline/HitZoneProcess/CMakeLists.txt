target_sources(${TARGET_NAME}
PRIVATE
HitZoneProcess.cpp
)

set(CPP_SOURCES
${CPP_SOURCES}
${CMAKE_CURRENT_LIST_DIR}/HitZoneProcess.cpp
PARENT_SCOPE
)