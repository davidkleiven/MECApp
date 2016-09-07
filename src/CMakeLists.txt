cmake_minimum_required(VERSION 2.6)
project(MECAPLib)
set (CMAKE_MODULE_PATH "/usr/lib/")
set(VTK_DIR "/home/david/Documents/VTKSource/VTK_build")
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ../)
add_compile_options(-std=c++11)
find_package(VTK REQUIRED)

if ( VTK_FOUND )
  message( STATUS "Found VTK-version: " ${VTK_VERSION} " at path: " ${VTK_DIR} )
endif()

include(${VTK_USE_FILE})
include_directories( ../inc /home/david/VTKSource/install/include )

add_library(mecapp SHARED facet.cpp facets.cpp point.cpp gmshreader.cpp regionBoundary.cpp fresnel.cpp complexConjVec.cpp)
