cmake_minimum_required(VERSION 2.6)
project(Test)
set (CMAKE_MODULE_PATH "/usr/lib/")
set(VTK_DIR "/home/david/Documents/VTKSource/VTK_build")
#set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-std=c++11)
find_package(VTK REQUIRED)

if ( VTK_FOUND )
  message( STATUS "Found VTK-version: " ${VTK_VERSION} " at path: " ${VTK_DIR} )
endif()

include(${VTK_USE_FILE})
include_directories( ../inc /home/david/VTKSource/install/include )

find_library(MECAPPLIB NAMES mecapp libmecapp PATHS ../)
if ( NOT MECAPPLIB )
  message( FATAL_ERROR "libmecapp.so was not found!" )
endif()

add_executable(illumination.out src/illumination.cpp)
target_link_libraries(illumination.out ${VTK_LIBRARIES} ${MECAPPLIB})

add_executable(scatPow.out src/scatteredPower.cpp)
target_link_libraries(scatPow.out ${VTK_LIBRARIES} ${MECAPPLIB})
