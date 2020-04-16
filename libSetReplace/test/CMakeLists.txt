
# TODO: Handle with FetchPackage or ExternalProject_Add
find_package(GTest REQUIRED)
set(GTEST_LIBRARIES gtest gtest_main)

set(_link_libraries SetReplace ${GTEST_LIBRARIES})

add_executable(test_SetReplace test_SetReplace.cpp)
target_link_libraries(test_SetReplace ${_link_libraries})

gtest_discover_tests(test_SetReplace)
