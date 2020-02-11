cmake_minimum_required (VERSION 3.0)

# set the project name
project (mesh_gateway)

# Create a variable that holds the path to the lora_gateway/libloragw
set (LGW_PATH ../../lora_gateway/libloragw)

# Add the local ‘include’ directory and the wiringPi directory to grab headers
include_directories (inc ${LGW_PATH}/inc)

# Actually find the libloragw library object
find_library(LGW_LIB libloragw HINTS ${LGW_PATH} NO_CMAKE_FIND_ROOT_PATH)
# Alert the user if we do not find it
#if(NOT LGW_LIB)
#message(FATAL_ERROR “libloragw library not found”)
#endif()

FILE(GLOB SRC_FILES src/*.c src/LoRaMac/*.c src/LoRaMesh/*.c)
add_executable(mesh_gateway ${SRC_FILES})
