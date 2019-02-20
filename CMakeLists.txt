# ------------------------------------------------------------------------------
# CMakeLists.txt for aggresss/deps
# ------------------------------------------------------------------------------

cmake_minimum_required(VERSION 2.8)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/CMake" ${CMAKE_MODULE_PATH})
include(Utilities)
include(GNUInstallDirs)

project("deps")

# ------------------------------------------------------------------------------
# Get and Display infomation
# ------------------------------------------------------------------------------

message(STATUS "CMake version: " ${CMAKE_VERSION})
message(STATUS "CMake system name: " ${CMAKE_SYSTEM_NAME})

c_compiler_prefix(C_COMPILER_PREFIX)
if(C_COMPILER_PREFIX)
  message(STATUS "C compiler prefix: " ${C_COMPILER_PREFIX})
endif()

c_compiler_machine(C_COMPILER_MACHINE)
if(C_COMPILER_MACHINE)
  message(STATUS "C compiler machine infomation: " ${C_COMPILER_MACHINE})
endif()

# ------------------------------------------------------------------------------
# Build type
# ------------------------------------------------------------------------------

set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE}
  CACHE STRING "Choose the type of build: None Debug Release Coverage" FORCE)

if(CMAKE_BUILD_TYPE)
  message(STATUS "CMake build type: " ${CMAKE_BUILD_TYPE})
endif()

# Default C / CXX flags
if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall ")
  set(CMAKE_CXX_FLAGS ${CMAKE_C_FLAGS})
endif()

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -ggdb -O0 -Wall")
set(CMAKE_CXX_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG})

set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3 -Wall -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE})

set(CMAKE_C_FLAGS_COVERAGE "${CMAKE_C_FLAGS_DEBUG} -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_FLAGS_COVERAGE ${CMAKE_C_FLAGS_COVERAGE})

# ------------------------------------------------------------------------------
# Test
# ------------------------------------------------------------------------------

find_program(VALGRIND valgrind)
if(VALGRIND)
  # Ctest configuration variables must be set BEFORE include(Ctest)
  set(MEMORYCHECK_COMMAND ${VALGRIND})
  # Check process children and give detail for each leak
  set(MEMORYCHECK_COMMAND_OPTIONS
    "${MEMORYCHECK_COMMAND_OPTIONS} --leak-check=yes --show-reachable=yes")
  set(MEMORYCHECK_COMMAND_OPTIONS
    "${MEMORYCHECK_COMMAND_OPTIONS} --trace-children=yes --track-fds=yes")
  # Set error code.
  set(MEMORYCHECK_COMMAND_OPTIONS
    "${MEMORYCHECK_COMMAND_OPTIONS} --error-exitcode=255")
  # Generate suppression hint.
  set(MEMORYCHECK_COMMAND_OPTIONS
    "${MEMORYCHECK_COMMAND_OPTIONS} --gen-suppressions=all")
  # Set suppression file
  set(MEMORYCHECK_COMMAND_OPTIONS
    "${MEMORYCHECK_COMMAND_OPTIONS} --suppressions=${CMAKE_CURRENT_LIST_DIR}/valgrind.supp")
endif()
include (CTest)
enable_testing()

# ------------------------------------------------------------------------------
# Project options
# ------------------------------------------------------------------------------

option(BUILD_ALL "Build all submodule" OFF)

# ------------------------------------------------------------------------------
# Subdirectory
# ------------------------------------------------------------------------------

SUBDIRLIST(SUB_DIRS ${PROJECT_SOURCE_DIR})
list(REMOVE_ITEM SUB_DIRS ".git")
list(REMOVE_ITEM SUB_DIRS "CMake")
list(REMOVE_ITEM SUB_DIRS "build")
list(REMOVE_ITEM SUB_DIRS "include")

foreach(subdir ${SUB_DIRS})
  add_subdirectory(${subdir})
endforeach()
