cmake_minimum_required(VERSION 3.13)
project(wolfram-setreplace)
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
add_library(libSetReplace ${libSetReplace_sources})
