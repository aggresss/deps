# ------------------------------------------------------------------------------
# CMakeLists.txt for aggresss/deps subdirectory
# ------------------------------------------------------------------------------

string(REGEX MATCH "[^/]+$" SUBMODULE ${CMAKE_CURRENT_LIST_DIR})
option(${SUBMODULE} "Build ${SUBMODULE}" OFF)

if(${SUBMODULE} OR BUILD_ALL)
  # Build
  aux_source_directory(${CMAKE_CURRENT_LIST_DIR} src_${SUBMODULE}_test)
  add_executable(${SUBMODULE}_test ${src_${SUBMODULE}_test})
  target_compile_options(${SUBMODULE}_test PRIVATE -std=c99)
  # Test
  add_test(NAME ${SUBMODULE}_test
    COMMAND ${SUBMODULE}_test --num 505)
  set_tests_properties(${SUBMODULE}_test PROPERTIES
    PASS_REGULAR_EXPRESSION "505")
endif()