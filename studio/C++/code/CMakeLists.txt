project (main) 
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

#---------------src--------------
AUX_SOURCE_DIRECTORY(./ DIR_SRCS)
AUX_SOURCE_DIRECTORY(./src DIR_SRCS)
AUX_SOURCE_DIRECTORY(./storage DIR_SRCS)
AUX_SOURCE_DIRECTORY(./text_tip DIR_SRCS)
AUX_SOURCE_DIRECTORY(./chime DIR_SRCS)
AUX_SOURCE_DIRECTORY(./ic_base/src DIR_SRCS)

#---------------include--------------
set(DIR_INCLUDE ./include ./ ./ic_base/include)

set(CMAKE_BUILD_TYPE "Debug")
include_directories(${DIR_INCLUDE})
add_executable(${PROJECT_NAME} ${DIR_SRCS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a -pthread") 

