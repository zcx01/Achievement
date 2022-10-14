project (main) 
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
AUX_SOURCE_DIRECTORY(. DIR_SRCS)
AUX_SOURCE_DIRECTORY(./array DIR_SRCS)
AUX_SOURCE_DIRECTORY(./str DIR_SRCS)

#---------------include--------------
set(DIR_INCLUDE ./ ./include)

set(CMAKE_BUILD_TYPE "Debug")
include_directories(${DIR_INCLUDE})
add_executable(${PROJECT_NAME} ${DIR_SRCS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread") 
