cmake_minimum_required(VERSION 3.13)
project(SetReplace)

option(SetReplace_BUILD_TESTING "Enable cpp testing." OFF)
option(SetReplace_WRAP_PYTHON "Wrap python using pybind11" OFF)
include(GNUInstallDirs) # Define CMAKE_INSTALL_xxx: LIBDIR, INCLUDEDIR
set(CMAKE_INSTALL_PYTHONLIBDIR wolfram_model) # Install folder for python libs
set(CMAKE_BUILD_PYTHONLIBDIR ${PROJECT_BINARY_DIR}/wolfram_model) # copy python libs at build time

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

if(SetReplace_WRAP_PYTHON)
    # Fetch pybind11
    include(FetchContent)
    FetchContent_Declare(
        pybind11
        GIT_REPOSITORY https://github.com/pybind/pybind11
        GIT_TAG v2.5
        )
    FetchContent_GetProperties(pybind11)
    if(NOT pybind11_POPULATED)
        FetchContent_Populate(pybind11)
        add_subdirectory(${pybind11_SOURCE_DIR} ${pybind11_BINARY_DIR})
    endif()


    add_subdirectory(python)
endif()
