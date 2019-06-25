cmake_minimum_required(VERSION 3.11)

project(tl-expected VERSION 1.0.0 LANGUAGES CXX)

option(EXPECTED_ENABLE_TESTS "Enable tests." ON)

include(FetchContent)
FetchContent_Declare(
  tl_cmake
  GIT_REPOSITORY https://github.com/TartanLlama/tl-cmake.git
)
FetchContent_GetProperties(tl_cmake)
if(NOT tl_cmake_POPULATED)
  FetchContent_Populate(tl_cmake)
  set(CMAKE_MODULE_PATH ${tl_cmake_SOURCE_DIR} ${CMAKE_MODULE_PATH})
endif()
include(add-tl)

tl_add_library(expected SOURCES 
               include/tl/expected.hpp)

# Prepare "Catch" library for other executables
set(CATCH_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})

if(EXPECTED_ENABLE_TESTS)
  # Make test executable
  set(TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tests/main.cpp
                   ${CMAKE_CURRENT_SOURCE_DIR}/tests/extensions.cpp
                   ${CMAKE_CURRENT_SOURCE_DIR}/tests/assignment.cpp
                   ${CMAKE_CURRENT_SOURCE_DIR}/tests/emplace.cpp
                   ${CMAKE_CURRENT_SOURCE_DIR}/tests/issues.cpp
                   ${CMAKE_CURRENT_SOURCE_DIR}/tests/bases.cpp
                   ${CMAKE_CURRENT_SOURCE_DIR}/tests/observers.cpp
                   ${CMAKE_CURRENT_SOURCE_DIR}/tests/swap.cpp
                   ${CMAKE_CURRENT_SOURCE_DIR}/tests/constructors.cpp)

  add_executable(tests ${TEST_SOURCES})

  target_link_libraries(tests Catch expected)

  set(CXXSTD 14 CACHE STRING "C++ standard to use, default C++14")
  set_property(TARGET tests PROPERTY CXX_STANDARD ${CXXSTD})
  set_property(TARGET tests PROPERTY CXX_FLAGS "-Wall -Wextra")
endif()
