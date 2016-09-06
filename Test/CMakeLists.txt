cmake_minimum_required(VERSION 2.6)
project(Test)
set (CMAKE_MODULE_PATH "/usr/lib/")
set(VTK_DIR "/home/david/Documents/VTKSource/install")
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

find_library(MECAPPLIB NAMES mecapp libmecapp PATHS ../)
if ( NOT MECAPPLIB )
  message( FATAL_ERROR "libmecapp.so was not found!" )
endif()

add_executable(illumination.out src/illumination.cpp)
target_link_libraries(illumination.out ${VTK_LIBRARIES} ${MECAPPLIB})
