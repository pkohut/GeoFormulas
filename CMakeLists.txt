cmake_minimum_required(VERSION 2.8)
project(geo_formulas_ng)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.9)
        # gcc < 4.9 does not provide working std::regex
        message(FATAL_ERROR "GCC version must be at least 4.9")
    endif()
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "CLANG")
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 3.3)
        message(FATAL_ERROR "Clang version must be at least 3.3")
    endif()
endif()

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_BINARY_DIR ${CMAKE_BINARY_DIR}/build)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

include_directories("${PROJECT_INCLUDE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}")

add_subdirectory(GeoFormulas)
add_subdirectory(TerpsTest)



# set(SOURCE_FILES main.cpp)
#add_executable(geo_formulas_ng ${SOURCE_FILES})
