
cmake_minimum_required(VERSION 3.21)
project(PlayerProfilePlus VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "GEODE_SDK is not set")
endif()

add_subdirectory($ENV{GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode)

file(GLOB_RECURSE SOURCES src/*.cpp)
add_library(${PROJECT_NAME} SHARED ${SOURCES})

set(GEODE_DISABLE_FMT_CONSTEVAL ON CACHE BOOL "" FORCE)

setup_geode_mod(${PROJECT_NAME})
