cmake_minimum_required(VERSION 3.13)
project(SetReplace)
option(SetReplace_BUILD_TESTING "Enable cpp testing." OFF)
set(libSetReplace_headers
    Rule.hpp
    IDTypes.hpp
    Expression.hpp
    Match.hpp
    Set.hpp
    # SetReplace.hpp
    )
set(libSetReplace_sources
    Expression.cpp
    Match.cpp
    Set.cpp
    # SetReplace.cpp
    )
list(TRANSFORM libSetReplace_sources PREPEND "libSetReplace/")
add_library(SetReplace ${libSetReplace_sources})
target_include_directories(SetReplace PUBLIC ./libSetReplace)

if(SetReplace_BUILD_TESTING)
    enable_testing()
    add_subdirectory(libSetReplace/test)
endif()
