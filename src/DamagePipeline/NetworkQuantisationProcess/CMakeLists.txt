target_sources(${TARGET_NAME}
PRIVATE
NetworkQuantisation.h
NetworkQuantisation.cpp
)

set(CPP_SOURCES
${CPP_SOURCES}
${CMAKE_CURRENT_LIST_DIR}/NetworkQuantisation.cpp
PARENT_SCOPE
)