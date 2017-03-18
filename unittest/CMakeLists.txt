find_package(Boost REQUIRED)
find_library(MECAPP mecapp PATHS ../)
find_library(BOOST_PROGRAM_OPTIONS boost_program_options)
find_library(BOOST_UNIT_TEST boost_unit_test_framework)

if (NOT BOOST_PROGRAM_OPTIONS )
  message( FATAL_ERROR "Did not find libboost_program_options.so" )
endif()

if (NOT BOOST_UNIT_TEST )
  message( FATAL_ERROR "Did not find libunittest_framework.so" )
endif()

message( STATUS "Found Boost-version: " ${BOOST_VERSION} )

if ( MECAPP )
  add_executable( alltest.out alltest.cpp )
  target_link_libraries(alltest.out PRIVATE ${LIB} ${BOOST_PROGRAM_OPTIONS} ${BOOST_UNIT_TEST} ${MECAPP})
endif()
