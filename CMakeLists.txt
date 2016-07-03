cmake_minimum_required(VERSION 3.3)
project(geo_formulas_ng)

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
