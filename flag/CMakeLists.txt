# ------------------------------------------------------------------------------
# CMakeLists.txt for aggresss/deps subdirectory
# ------------------------------------------------------------------------------

string(REGEX MATCH "[^/]+$" SUBMODULE_NAME ${CMAKE_CURRENT_LIST_DIR})
option(${SUBMODULE_NAME} "Build ${SUBMODULE_NAME}" OFF)

if(${SUBMODULE_NAME})
  # Build
  aux_source_directory(${CMAKE_CURRENT_LIST_DIR} src_${SUBMODULE_NAME}_test)
  add_executable(${SUBMODULE_NAME}_test ${src_${SUBMODULE_NAME}_test})
  target_compile_options(${SUBMODULE_NAME}_test PRIVATE -std=c99)
  # Test
  add_test(NAME ${SUBMODULE_NAME}_test
    COMMAND ${SUBMODULE_NAME}_test --num 505)
  set_tests_properties(${SUBMODULE_NAME}_test PROPERTIES
    PASS_REGULAR_EXPRESSION "505")
endif(${SUBMODULE_NAME})