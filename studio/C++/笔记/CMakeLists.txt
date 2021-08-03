#project name  
PROJECT(test_math)  
  
#
add_definitions("-Wall -lpthread -g")  
  
#head file path  
INCLUDE_DIRECTORIES(  
include  
)  
  
#source directory  
AUX_SOURCE_DIRECTORY(src DIR_SRCS)  
  
#set environment variable  
SET(TEST_MATH  
${DIR_SRCS}  
)  
  
#set extern libraries  
SET(LIBRARIES  
libm.so  
)  
  
# set output binary path  
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)  
  
SET(FS_BUILD_BINARY_PREFIX "Yfs")  
  
#add executable file  
ADD_EXECUTABLE(${FS_BUILD_BINARY_PREFIX}sqrt ${TEST_MATH})  
  
#add link library  
TARGET_LINK_LIBRARIES(${FS_BUILD_BINARY_PREFIX}sqrt ${LIBRARIES}) 