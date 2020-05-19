set(enabled_libs_ SetReplace)

add_subdirectory(set_replace)

# Add the pybind module
pybind11_add_module(_wolfram_model
  wolfram_model_init_py.cpp # Where module is added
  ${all_modules_python_sources} # all the collected sources in submodules
  )
target_link_libraries(_wolfram_model PRIVATE ${enabled_libs_})

install(TARGETS _wolfram_model
  DESTINATION ${CMAKE_INSTALL_PYTHONLIBDIR}
  COMPONENT runtime
  )
install(FILES __init__.py
  DESTINATION ${CMAKE_INSTALL_PYTHONLIBDIR}
  COMPONENT runtime
  )
# Copy __init__ at configure time
file(COPY __init__.py DESTINATION ${CMAKE_BUILD_PYTHONLIBDIR})
# Copy at build time
add_custom_command(
  TARGET _wolfram_model
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
  $<TARGET_FILE:_wolfram_model>
  ${CMAKE_BUILD_PYTHONLIBDIR}/$<TARGET_FILE_NAME:_wolfram_model>
  )

### vis package (python-only) ###
set(_package_name "vis")
set(_package_python_files
  __init__.py
  vis.py
  fixture.py
  )
list(TRANSFORM _package_python_files PREPEND "${_package_name}/")
# Copy at build time
file(COPY ${_package_python_files} DESTINATION ${CMAKE_BUILD_PYTHONLIBDIR}/${_package_name})
install(FILES ${_package_python_files}
  DESTINATION ${CMAKE_INSTALL_PYTHONLIBDIR}/${_package_name}
  COMPONENT runtime
  )

### vis/networkx package (python-only) ###
set(_package_name "vis/networkx")
set(_package_python_files
  __init__.py
  vis.py
  )
list(TRANSFORM _package_python_files PREPEND "${_package_name}/")
# Copy at build time
file(COPY ${_package_python_files} DESTINATION ${CMAKE_BUILD_PYTHONLIBDIR}/${_package_name})
install(FILES ${_package_python_files}
  DESTINATION ${CMAKE_INSTALL_PYTHONLIBDIR}/${_package_name}
  COMPONENT runtime
  )

if(SET_REPLACE_BUILD_TESTING)
  add_subdirectory(tests)
endif()
