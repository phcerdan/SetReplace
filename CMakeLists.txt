cmake_minimum_required(VERSION 3.13)
project(wolfram_model
    VERSION 0.3.0
    LANGUAGES CXX)
message(STATUS "wolfram_model version: ${wolfram_model_VERSION}")

option(WOLFRAM_MODEL_BUILD_TESTING "Enable cpp testing." OFF)
option(WOLFRAM_MODEL_WRAP_PYTHON "Wrap python using pybind11" OFF)
include(GNUInstallDirs) # Define CMAKE_INSTALL_xxx: LIBDIR, INCLUDEDIR
set(CMAKE_INSTALL_PYTHONLIBDIR wolfram_model) # Install folder for python libs
set(CMAKE_BUILD_PYTHONLIBDIR ${PROJECT_BINARY_DIR}/wolfram_model) # copy python libs at build time
set(wolfram_model_export_file "${PROJECT_BINARY_DIR}/SGEXTTargets.cmake")

if(WOLFRAM_MODEL_WRAP_PYTHON)
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif()

set(libSetReplace_headers
    Rule.hpp
    IDTypes.hpp
    Expression.hpp
    Match.hpp
    Set.hpp
    )
list(TRANSFORM libSetReplace_headers PREPEND "libSetReplace/")
set(libSetReplace_sources
    Expression.cpp
    Match.cpp
    Set.cpp
    )
list(TRANSFORM libSetReplace_sources PREPEND "libSetReplace/")
add_library(SetReplace ${libSetReplace_sources})
target_include_directories(SetReplace PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/libSetReplace>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  )
set(WOLFRAM_MODEL_LIBRARIES ${WOLFRAM_MODEL_LIBRARIES} SetReplace)

install(TARGETS SetReplace
        EXPORT wolfram_modelTargets
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        COMPONENT runtime
        )

install(FILES ${libSetReplace_headers}
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/wolfram_model)

# export to the build tree
export( TARGETS SetReplace
  NAMESPACE wolfram_model::
  APPEND FILE ${wolfram_model_export_file})


if(WOLFRAM_MODEL_BUILD_TESTING)
    enable_testing()
    add_subdirectory(libSetReplace/test)
endif()

if(WOLFRAM_MODEL_WRAP_PYTHON)
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

# INSTALL
set(install_cmake_dir "${CMAKE_INSTALL_LIBDIR}/cmake/wolfram_model")

install (EXPORT wolfram_modelTargets
  NAMESPACE wolfram_model::
  DESTINATION ${install_cmake_dir} )

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/cmake/wolfram_modelConfig.cmake
              ${CMAKE_CURRENT_BINARY_DIR}/wolfram_modelConfigVersion.cmake
              DESTINATION ${install_cmake_dir} )

include(CMakePackageConfigHelpers)

write_basic_package_version_file(wolfram_modelConfigVersion.cmake
  VERSION ${wolfram_model_VERSION}
  COMPATIBILITY SameMajorVersion)

# Build tree
set(wolfram_model_TARGETS_FILE ${wolfram_model_export_file})
configure_package_config_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake/wolfram_modelConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/wolfram_modelConfig.cmake
  INSTALL_DESTINATION ${install_cmake_dir}
  PATH_VARS wolfram_model_TARGETS_FILE
  NO_CHECK_REQUIRED_COMPONENTS_MACRO # wolfram_model does not provide components
  INSTALL_PREFIX ${CMAKE_CURRENT_BINARY_DIR}
  )

# Install tree
set(wolfram_model_TARGETS_FILE ${CMAKE_INSTALL_PREFIX}/${install_cmake_dir}/wolfram_modelTargets.cmake)
configure_package_config_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake/wolfram_modelConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/cmake/wolfram_modelConfig.cmake
  INSTALL_DESTINATION ${install_cmake_dir}
  PATH_VARS wolfram_model_TARGETS_FILE
  NO_CHECK_REQUIRED_COMPONENTS_MACRO # wolfram_model does not provide components
  )

# Add custom target to only install component: runtime (libraries)
add_custom_target(install-runtime
  ${CMAKE_COMMAND}
  -DCMAKE_INSTALL_COMPONENT=runtime
  -P "${PROJECT_BINARY_DIR}/cmake_install.cmake"
  DEPENDS ${WOLFRAM_MODEL_LIBRARIES}
  )
message(STATUS "WOLFRAM_MODEL_LIBRARIES: ${WOLFRAM_MODEL_LIBRARIES}")
add_dependencies(install-runtime ${WOLFRAM_MODEL_LIBRARIES})
if(WOLFRAM_MODEL_WRAP_PYTHON)
  add_dependencies(install-runtime _wolfram_model)
endif()
