set(TEST_NAME RNGServiceLocatorTest)
add_executable(${TEST_NAME} RNGServiceLocator.test.cpp)
target_include_directories(${TEST_NAME} PRIVATE ${CMAKE_SOURCE_DIR})
target_sources(${TEST_NAME} PRIVATE ${CPP_SOURCES})
add_test(${TEST_NAME} ${TEST_NAME})

set(TEST_NAME ProbabilityModEffectWrapperTest)
add_executable(${TEST_NAME} ProbabilityModEffectWrapper.test.cpp)
target_include_directories(${TEST_NAME} PRIVATE ${CMAKE_SOURCE_DIR})
target_sources(${TEST_NAME} PRIVATE ${CPP_SOURCES})
add_test(${TEST_NAME} ${TEST_NAME})

add_executable(GuaranteedPass GuaranteedPass.Test.cpp)
add_test(GuaranteedPass GuaranteedPass)