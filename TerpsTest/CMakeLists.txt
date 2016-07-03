cmake_minimum_required(VERSION 3.3)

project(geo_formulas_ng)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11")

set (PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set (PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(TERPS_TESTS_SRCS
        ${PROJECT_SOURCE_DIR}/LatLongConversions.cpp
        ${PROJECT_SOURCE_DIR}/TerpsTest.cpp
        ${PROJECT_SOURCE_DIR}/TestArcIntersect.cpp
        ${PROJECT_SOURCE_DIR}/TestCrsIntersect.cpp
        ${PROJECT_SOURCE_DIR}/TestDirect.cpp
        ${PROJECT_SOURCE_DIR}/TestDiscretizedArcLength.cpp
        ${PROJECT_SOURCE_DIR}/TestGeoLocusIntersect.cpp
        ${PROJECT_SOURCE_DIR}/TestGeodesicArcIntersect.cpp
        ${PROJECT_SOURCE_DIR}/TestInverse.cpp
        ${PROJECT_SOURCE_DIR}/TestLocusArcIntersect.cpp
        ${PROJECT_SOURCE_DIR}/TestLocusCrsAtPoint.cpp
        ${PROJECT_SOURCE_DIR}/TestLocusIntersect.cpp
        ${PROJECT_SOURCE_DIR}/TestLocusPerpIntersect.cpp
        ${PROJECT_SOURCE_DIR}/TestLocusTanFixedRadiusArc.cpp
        ${PROJECT_SOURCE_DIR}/TestPerpIntercept.cpp
        ${PROJECT_SOURCE_DIR}/TestPerpTangentPoints.cpp
        ${PROJECT_SOURCE_DIR}/TestPointToArcTangents.cpp
        ${PROJECT_SOURCE_DIR}/TestPtIsOnArc.cpp
        ${PROJECT_SOURCE_DIR}/TestPtIsOnGeodesic.cpp
        ${PROJECT_SOURCE_DIR}/TestPtIsOnLocus.cpp
        ${PROJECT_SOURCE_DIR}/TestTangentFixedRadiusArc.cpp
)

include_directories("${PROJECT_BINARY_DIR}")
add_executable(terps_tests ${TERPS_TESTS_SRCS})
include_directories("${PROJECT_INCLUDE_DIR}")

target_link_libraries(terps_tests geo_formulas)

