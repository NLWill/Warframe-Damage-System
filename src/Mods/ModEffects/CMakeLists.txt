target_sources(${TARGET_NAME}
PRIVATE
ConditionalModEffectWrapper.cpp
EventListenerModEffectWrapper.cpp
FactionModEffect.cpp
ModEffect.cpp
ProbabilityModEffectWrapper.cpp
)

set(CPP_SOURCES
${CPP_SOURCES}
${CMAKE_CURRENT_LIST_DIR}/ConditionalModEffectWrapper.cpp
${CMAKE_CURRENT_LIST_DIR}/EventListenerModEffectWrapper.cpp
${CMAKE_CURRENT_LIST_DIR}/FactionModEffect.cpp
${CMAKE_CURRENT_LIST_DIR}/ModEffect.cpp
${CMAKE_CURRENT_LIST_DIR}/ProbabilityModEffectWrapper.cpp
PARENT_SCOPE)