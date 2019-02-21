# ------------------------------------------------------------------------------
# CMakeLists.txt for aggresss/deps subdirectory
# ------------------------------------------------------------------------------

string(REGEX MATCH "[^/]+$" SUBMODULE ${CMAKE_CURRENT_LIST_DIR})
option(${SUBMODULE} "Build ${SUBMODULE}" OFF)

if(${SUBMODULE} OR BUILD_ALL)
  # Build
  aux_source_directory(${CMAKE_CURRENT_LIST_DIR} src_${SUBMODULE}_test)

  foreach(f IN LISTS src_${SUBMODULE}_test)
    get_filename_component(b ${f} NAME)
    set_source_files_properties(${f} PROPERTIES
      COMPILE_DEFINITIONS "__FILE_NAME__=\"${b}\"")
  endforeach()

  add_executable(${SUBMODULE}_test ${src_${SUBMODULE}_test})
  target_compile_definitions(${SUBMODULE}_test PRIVATE "-D__PROJECT__=\"[${SUBMODULE}_test]\"")
  target_compile_options(${SUBMODULE}_test PRIVATE -std=c99)

  # Test
  add_test(NAME ${SUBMODULE}_test
    COMMAND ${SUBMODULE}_test)
endif()