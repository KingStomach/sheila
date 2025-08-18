function(sheila_unit_test FILE_NAME)
  get_filename_component(TEST_NAME ${FILE_NAME} NAME_WE)
  set(TEST_PROJECT_NAME test_${TEST_NAME})

  set(multiValueArgs MACRO PROPERTIES)
  cmake_parse_arguments(TEST "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

  add_executable(${TEST_PROJECT_NAME} EXCLUDE_FROM_ALL ${FILE_NAME})
  target_compile_features(${TEST_PROJECT_NAME} PUBLIC cxx_std_23)
  target_link_libraries(${TEST_PROJECT_NAME} PRIVATE sheila)
  target_compile_definitions(${TEST_PROJECT_NAME} PRIVATE SHEILA_TEST_BUILD ${TEST_MACRO})
  set_target_properties(${TEST_PROJECT_NAME} PROPERTIES FOLDER "test")

  add_test(NAME ${TEST_NAME} COMMAND ${TEST_PROJECT_NAME})
  if(TEST_PROPERTIES)
    list(PREPEND TEST_PROPERTIES PROPERTIES)
    set_tests_properties(${TEST_NAME} ${TEST_PROPERTIES})
  endif()
endfunction()
