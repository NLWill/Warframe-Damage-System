cmake_minimum_required(VERSION 3.27...3.31)

project("Warframe Damage System" VERSION 0.1
DESCRIPTION "Simulation of the damage mechanics of the MMO Warframe"
LANGUAGES CXX
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra")

set(TARGET_NAME WarframeDamageSystem)

add_executable(${TARGET_NAME} WarframeDamageSystem.cpp)

# Process the sub-folder CMakeLists files
set(CPP_SOURCES "")
set(HEADER_SOURCES "")
add_subdirectory(include)
add_subdirectory(src)

# Add the relevant include directories
target_include_directories(${TARGET_NAME} 
PUBLIC include
)
target_include_directories(${TARGET_NAME} 
PRIVATE ./
PRIVATE ${CMAKE_ROOT_DIR}
)

# Copy all data files into the binary directory. Ensure all files are up to date
file(REMOVE_RECURSE ${CMAKE_CURRENT_BINARY_DIR}/data/)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/data/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/data/)

# Add all the tests that need to be performed
set(ENABLE_TESTING false)
if (ENABLE_TESTING)
	include(CTest)
	enable_testing()
	add_subdirectory(tests)
endif()