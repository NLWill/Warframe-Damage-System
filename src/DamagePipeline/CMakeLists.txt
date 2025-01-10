add_subdirectory(CriticalHitProcess)
add_subdirectory(NetworkQuantisationProcess)

target_sources(${TARGET_NAME}
PRIVATE
DamageValue.h
DamageValue.cpp
DamageInstance.h
DamageInstance.cpp
FireInstance.h
FireInstance.cpp
)

set(CPP_SOURCES
${CPP_SOURCES}
${CMAKE_CURRENT_LIST_DIR}/DamageValue.cpp
${CMAKE_CURRENT_LIST_DIR}/DamageInstance.cpp
${CMAKE_CURRENT_LIST_DIR}/FireInstance.cpp
PARENT_SCOPE
)