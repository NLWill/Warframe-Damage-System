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