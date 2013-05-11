PROJECT(bqinv)
cmake_minimum_required(VERSION 2.6)
SET( CMAKE_BUILD_TYPE "Debug")

SET(ROOT_DIR ${CMAKE_SOURCE_DIR})
SET(SRC_DIR ${ROOT_DIR}/src)
INCLUDE_DIRECTORIES(${ROOT_DIR}/include)
INCLUDE_DIRECTORIES(${ROOT_DIR}/include/core)
AUX_SOURCE_DIRECTORY(${SRC_DIR} SRC)
AUX_SOURCE_DIRECTORY(${SRC_DIR}/core SRC_LIB)

add_library(bqinv SHARED ${SRC_LIB})

add_executable(yb ${SRC_DIR}/main.cpp)
target_link_libraries(yb bqinv dl pthread)

