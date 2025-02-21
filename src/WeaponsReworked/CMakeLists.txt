add_subdirectory(FiringModeImpl)

target_sources(${TARGET_NAME}
PRIVATE
FiringMode.cpp
Weapon.cpp
)

set(CPP_SOURCES
${CPP_SOURCES}
${CMAKE_CURRENT_LIST_DIR}/FiringMode.cpp
${CMAKE_CURRENT_LIST_DIR}/Weapon.cpp
PARENT_SCOPE)