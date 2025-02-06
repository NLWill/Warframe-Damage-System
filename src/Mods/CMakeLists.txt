add_subdirectory(ModEffects)

target_sources(${TARGET_NAME}
PRIVATE
ModBase.cpp
ModEffectBase.cpp
ModFactory.cpp
ModManager.cpp
)

set(CPP_SOURCES
${CPP_SOURCES}
${CMAKE_CURRENT_LIST_DIR}/ModBase.cpp
${CMAKE_CURRENT_LIST_DIR}/ModEffectBase.cpp
${CMAKE_CURRENT_LIST_DIR}/ModFactory.cpp
${CMAKE_CURRENT_LIST_DIR}/ModManager.cpp
PARENT_SCOPE)