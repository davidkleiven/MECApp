cmake_minimum_required(VERSION 2.6)
project(MECAPPLib)
set (CMAKE_MODULE_PATH "/usr/lib/")
set(VTK_DIR "/home/david/Documents/VTKSource/VTK_build")
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ../)
add_compile_options(-std=c++11)
find_package(VTK REQUIRED)
include_directories( inc )
if ( VTK_FOUND )
  message( STATUS "Found VTK-version: " ${VTK_VERSION} " at path: " ${VTK_DIR} )
endif()
set (LIB ${VTK_LIBRARIES} )
include_directories( ${VTK_INCLUDE_DIRS} )

# TODO: Seem to be something wrong witht the package detection
find_library( JSONCPP_LIB jsoncpp )
set( LIB ${LIB} jsoncpp.so)
if ( NOT JSONCPP_LIB )
  MESSAGE( FATAL_ERROR "Did not find the jsoncpp library!")
endif( NOT JSONCPP_LIB)
find_path( JSON_HEADER json)
if ( NOT JSON_HEADER )
  MESSAGE( FATAL_ERROR "Did not find the json headers!")
endif( NOT JSON_HEADER )
set( LIB ${LIB} ${JSONCPP_LIB} )

#include(${VTK_USE_FILE})
#include_directories( ../inc /home/david/VTKSource/install/include )
add_subdirectory(src/)
add_subdirectory(unittest/)
add_subdirectory(Test/)

# Unittesting
