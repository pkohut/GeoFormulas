cmake_minimum_required(VERSION 3.3)
project(geo_formulas)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(GEO_FORMULAS_SRCS
        ${PROJECT_SOURCE_DIR}/ArcIntercept.cpp
        ${PROJECT_SOURCE_DIR}/CMakeLists.txt
        ${PROJECT_SOURCE_DIR}/CrsIntersect.cpp
        ${PROJECT_SOURCE_DIR}/DirectArcLength.cpp
        ${PROJECT_SOURCE_DIR}/DiscretizedArcLength.cpp
        ${PROJECT_SOURCE_DIR}/DistToLocusD.cpp
        ${PROJECT_SOURCE_DIR}/DistanceIntersection.cpp
        ${PROJECT_SOURCE_DIR}/DistanceToLocusP.cpp
        ${PROJECT_SOURCE_DIR}/ECEF.cpp
        ${PROJECT_SOURCE_DIR}/FindLinearRoot.cpp
        ${PROJECT_SOURCE_DIR}/GeoLocusIntersect.cpp
        ${PROJECT_SOURCE_DIR}/GeodesicArcIntercept.cpp
        ${PROJECT_SOURCE_DIR}/GeometricMeanMeridional.cpp
        ${PROJECT_SOURCE_DIR}/GetArcExtent.cpp
        ${PROJECT_SOURCE_DIR}/LocusArcIntersect.cpp
        ${PROJECT_SOURCE_DIR}/LocusCrsAtPoint.cpp
        ${PROJECT_SOURCE_DIR}/LocusIntersect.cpp
        ${PROJECT_SOURCE_DIR}/LocusPerpIntercept.cpp
        ${PROJECT_SOURCE_DIR}/LocusTanFixedRadiusArc.cpp
        ${PROJECT_SOURCE_DIR}/Mod.cpp
        ${PROJECT_SOURCE_DIR}/PerpIntercept.cpp
        ${PROJECT_SOURCE_DIR}/PerpTangentPoints.cpp
        ${PROJECT_SOURCE_DIR}/PointOnLocusP.cpp
        ${PROJECT_SOURCE_DIR}/PointToArcTangents.cpp
        ${PROJECT_SOURCE_DIR}/PrimeVerticalCurvature.cpp
        ${PROJECT_SOURCE_DIR}/PtIsOnArc.cpp
        ${PROJECT_SOURCE_DIR}/PtIsOnGeodesic.cpp
        ${PROJECT_SOURCE_DIR}/PtIsOnLocus.cpp
        ${PROJECT_SOURCE_DIR}/SignAzimuthDifference.cpp
        ${PROJECT_SOURCE_DIR}/TangentFixedRadiusArc.cpp
        ${PROJECT_SOURCE_DIR}/VincentyDestination.cpp
        ${PROJECT_SOURCE_DIR}/VincentyDistance.cpp

        )

include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_INCLUDE_DIR}")


add_library(${PROJECT_NAME} ${GEO_FORMULAS_SRCS})
