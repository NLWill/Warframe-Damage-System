target_sources(${TARGET_NAME}
PRIVATE
RNGServiceBase.h
RNGService.h
RNGService.cpp
NullRNGService.h
)

set(CPP_SOURCES
${CPP_SOURCES}
${CMAKE_CURRENT_LIST_DIR}/RNGService.cpp
PARENT_SCOPE)