cmake_minimum_required(VERSION 3.28)

project(omp_lab
        VERSION 1.0
        LANGUAGES CXX
        DESCRIPTION "omp"
)

set(CMAKE_CXX_STANDARD 20)

OPTION (USE_OpenMP "Use OpenMP" ON)
IF(USE_OpenMP)
    FIND_PACKAGE(OpenMP)
    IF(OPENMP_FOUND)
        SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    ENDIF()
ENDIF()

set(CMAKE_OSX_ARCHITECTURES x86_64)

add_executable(omp_lab main.cpp hit.h hit.cpp Parser.hpp Parser.cpp)
