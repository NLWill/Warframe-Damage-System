target_sources(${TARGET_NAME}
PRIVATE
LogService.cpp
LoggerServiceBase.h
LogService.h
NullLogService.h
)

set(CPP_SOURCES
${CPP_SOURCES}
${CMAKE_CURRENT_LIST_DIR}/LogService.cpp
PARENT_SCOPE)