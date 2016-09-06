cmake_minimum_required(VERSION 2.6)
set(VTK_DIR "/home/david/Documents/VTKSource/VTK_build")
add_compile_options(-std=c++11)
find_package(VTK REQUIRED)

if ( VTK_FOUND )
  message( STATUS "Found VTK-version: " ${VTK_VERSION} " at path: " ${VTK_DIR} )
endif()

include(${VTK_USE_FILE})
include_directories( ../inc /home/david/VTKSource/install/include )
find_package(Boost REQUIRED)
find_library(MECAPP mecapp PATHS ../)
find_library(BOOST_PROGRAM_OPTIONS boost_program_options)
find_library(BOOST_UNIT_TEST boost_unit_test_framework)

if (NOT MECAPP)
  message( FATAL_ERROR "Did not find libmecapp.so" )
endif()

if (NOT BOOST_PROGRAM_OPTIONS )
  message( FATAL_ERROR "Did not find libboost_program_options.so" )
endif()

if (NOT BOOST_UNIT_TEST )
  message( FATAL_ERROR "Did not find libunittest_framework.so" )
endif()

message( STATUS "Found Boost-version: " ${BOOST_VERSION} )
add_executable( alltest.out alltest.cpp )
target_link_libraries(alltest.out PRIVATE ${BOOST_PROGRAM_OPTIONS} ${BOOST_UNIT_TEST} ${MECAPP} ${VTK_LIBRARIES})
