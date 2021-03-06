cmake_minimum_required(VERSION 3.7...3.20)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
  cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(
  LearnOpenGL
  VERSION 1.0
  DESCRIPTION "https://learnopengl.com/"
  LANGUAGES CXX C)

find_package(Git QUIET)

if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
  # Update submodules as needed
  option(GIT_SUBMODULE "Check submodules during build" OFF)
  if(GIT_SUBMODULE)
    message(STATUS "Submodule update")
    execute_process(
      COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
      RESULT_VARIABLE GIT_SUBMOD_RESULT)
    if(NOT GIT_SUBMOD_RESULT EQUAL "0")
      message(
        FATAL_ERROR
          "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodules"
      )
    endif()
  endif()
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY $<1:${CMAKE_SOURCE_DIR}/bin>)

include(cmake/Doxygen.cmake)
enable_doxygen()

option(LINK_WHAT_YOU_USE "Link What You Use")
option(INCLUDE_WHAT_YOU_USE "Include What You Use")
option(CPPCHECK "Use CPPCHECK")
option(CLANGTIDY "Use Clang-Tidy" ON)
include(cmake/CmakeProjectSettings.cmake)

add_subdirectory(${CMAKE_SOURCE_DIR}/dependencies/glfw EXCLUDE_FROM_ALL)
add_subdirectory(${CMAKE_SOURCE_DIR}/dependencies/assimp EXCLUDE_FROM_ALL)
add_subdirectory(${CMAKE_SOURCE_DIR}/dependencies/imgui EXCLUDE_FROM_ALL)
add_subdirectory(${CMAKE_SOURCE_DIR}/dependencies/glm EXCLUDE_FROM_ALL)
add_subdirectory(${CMAKE_SOURCE_DIR}/dependencies/glad EXCLUDE_FROM_ALL)
if(LWYU)
  set(CMAKE_LINK_WHAT_YOU_USE TRUE)
endif()

if(ICWYU)
  find_program(iwyu_path REQUIRED NAMES include-what-you-use iwyu)
  set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endif()

if(CPPCHECK)
  set(CMAKE_CXX_CPPCHECK
      /opt/homebrew/bin/cppcheck;--std=c++17 --suppress=missingInclude
      --enable=all --inline-suppr -i dependencies --report-progress --output-file=cppcheck.txt; ${CMAKE_SOURCE_DIR}/src/)
endif()

if(CLANGTIDY)
  set(CMAKE_CXX_CLANG_TIDY clang-tidy; -header-filter=${CMAKE_SOURCE_DIR}/src/)
endif()
add_library(project_warnings INTERFACE)
include(cmake/CompilerWarnings.cmake)
set_project_warnings(project_warnings)
add_subdirectory(${CMAKE_SOURCE_DIR}/src)
