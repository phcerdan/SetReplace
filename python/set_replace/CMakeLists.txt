set(current_sources_
  set_replace_init_py.cpp
  expression_py.cpp
  rule_py.cpp
  match_py.cpp
  set_py.cpp
  )
set(module_name_ ${CMAKE_CURRENT_SOURCE_DIR})
list(TRANSFORM current_sources_ PREPEND "${module_name_}/")

set(all_modules_python_sources
  ${all_modules_python_sources}
  ${current_sources_}
  PARENT_SCOPE)
