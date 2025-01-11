add_subdirectory(MultishotProcess)
add_subdirectory(NetworkQuantisationProcess)
add_subdirectory(StatusChanceProcess)
add_subdirectory(CriticalHitProcess)

target_sources(${TARGET_NAME}
PRIVATE
DamageValue.h
DamageValue.cpp
DamageInstance.h
DamageInstance.cpp
FireInstance.h
FireInstance.cpp
DamagePipeline.cpp
)

set(CPP_SOURCES
${CPP_SOURCES}
${CMAKE_CURRENT_LIST_DIR}/DamageValue.cpp
${CMAKE_CURRENT_LIST_DIR}/DamageInstance.cpp
${CMAKE_CURRENT_LIST_DIR}/FireInstance.cpp
${CMAKE_CURRENT_LIST_DIR}/DamagePipeline.cpp
PARENT_SCOPE
)