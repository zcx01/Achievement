project (main) 

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

AUX_SOURCE_DIRECTORY(. DIR_SRCS)
AUX_SOURCE_DIRECTORY(./common_codes DIR_SRCS)
AUX_SOURCE_DIRECTORY(./can DIR_SRCS)
AUX_SOURCE_DIRECTORY(./lin DIR_SRCS)
AUX_SOURCE_DIRECTORY(./ic_base/src DIR_SRCS)
AUX_SOURCE_DIRECTORY(./tcp DIR_SRCS)

#---------------include--------------
set(DIR_INCLUDE ./ ./common_codes ./base ./can ./lin ./ic_base/include ./tcp)

set(CMAKE_BUILD_TYPE "Debug")
include_directories(${DIR_INCLUDE})
add_executable(${PROJECT_NAME} ${DIR_SRCS})
# 设置进程名
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "project_Test")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread") 

