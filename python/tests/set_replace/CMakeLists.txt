set(python_tests_
  test_expressions.py
  test_rule.py
  test_match.py
  test_set.py
  )
set(module_name_ "set_replace")
set(test_folder "${CMAKE_CURRENT_SOURCE_DIR}")
# test files should start with "test_"
# test functions (in .py) should start with "test_" for autodiscover to work
foreach(python_test ${python_tests_})
  set(python_test_name_ python||${module_name_}||${python_test})
  add_test(NAME ${python_test_name_}
    COMMAND
    ${PYTHON_EXECUTABLE} -m pytest ${CMAKE_CURRENT_SOURCE_DIR}
    --verbose -r All
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
    )
  # Append the build folder where python lib is to PYTHONPATH
  # Allowing ctest -R "a_python_test_name_" -V to work
  set_tests_properties(${python_test_name_} PROPERTIES
    ENVIRONMENT PYTHONPATH=$ENV{PYTHONPATH}:${CMAKE_BUILD_PYTHONLIBDIR})
endforeach()
