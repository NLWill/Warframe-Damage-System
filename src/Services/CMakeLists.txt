add_subdirectory(Logging)
add_subdirectory(RNG)

target_sources(${TARGET_NAME}
PRIVATE
ServiceLocator.h
ServiceLocator.cpp
)