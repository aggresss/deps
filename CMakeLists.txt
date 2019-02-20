# ------------------------------------------------------------------------------
# CMakeLists.txt for aggresss/deps
# ------------------------------------------------------------------------------

cmake_minimum_required(VERSION 2.8)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/CMake" ${CMAKE_MODULE_PATH})
include(Utilities)

include(GNUInstallDirs)

project("deps")

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
# Subdirectory
# ------------------------------------------------------------------------------
add_subdirectory(b64)
add_subdirectory(cJSON)
add_subdirectory(flag)
add_subdirectory(hmac_sha1)
add_subdirectory(log)
add_subdirectory(md5)
