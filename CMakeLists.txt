cmake_minimum_required ( VERSION 3.9 )
set ( CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake" )
include ( helpers )
start_hunter ()
option ( TYPIST_WITH_TESTS "Get test dependencies" ON )

project ( typist )
set ( CMAKE_CXX_STANDARD 17 )

if ( ${TYPIST_WITH_TESTS} )
    set ( BOOST_COMPONENTS unit_test_framework )
endif ()

hunter_add_package ( Boost )
find_package ( Boost CONFIG REQUIRED COMPONENTS ${BOOST_COMPONENTS} )

add_library ( typist INTERFACE )
target_include_directories ( typist INTERFACE
                             $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                             $<INSTALL_INTERFACE:$<INSTALL_PREFIX>/include/typist>
                             )

target_link_libraries ( typist INTERFACE Boost::boost )

if ( ${TYPIST_WITH_TESTS} )
    find_package ( Boost CONFIG REQUIRED COMPONENTS unit_test_framework )
    add_executable ( tests tests/tests.cpp )
    target_link_libraries ( tests PRIVATE typist Boost::unit_test_framework )
endif ()