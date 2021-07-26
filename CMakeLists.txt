cmake_minimum_required(VERSION 3.7...3.20)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(LearnOpenGL VERSION 1.0
        DESCRIPTION "https://learnopengl.com/"
        LANGUAGES CXX C)

find_package(Git QUIET)

if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
# Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" OFF)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

option(LWYU "Link What You Use" OFF)
option(ICWYU "Include What You Use" OFF)
option(CPPCHECK "Use CPPCHECK" OFF)
option(CLANGTIDY "Use Clang-Tidy" ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_BUILD_PARALLEL_LEVEL 4)
set(CMAKE_CXX_STANDARD 17 CACHE STRING "The C++ standard to use")
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_VISIBILITY_PRESET hidden CACHE STRING "Inline Visibility")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
set(ASSIMP_INSTALL OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_NO_EXPORT ON CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_OBJ_IMPORTER ON CACHE BOOL "" FORCE)
set(INJECT_DEBUG_POSTFIX OFF CACHE BOOL "" FORCE)

add_subdirectory(${CMAKE_SOURCE_DIR}/dependencies/glfw EXCLUDE_FROM_ALL)
add_subdirectory(${CMAKE_SOURCE_DIR}/dependencies/assimp EXCLUDE_FROM_ALL)
add_subdirectory(${CMAKE_SOURCE_DIR}/dependencies/imgui EXCLUDE_FROM_ALL)
add_subdirectory(${CMAKE_SOURCE_DIR}/dependencies/glm EXCLUDE_FROM_ALL)
add_subdirectory(${CMAKE_SOURCE_DIR}/dependencies/glad EXCLUDE_FROM_ALL)

if(LWYU)
    set(CMAKE_LINK_WHAT_YOU_USE TRUE)
endif()

if (MSVC)
    add_compile_options(/W4 /EHsc)
else()
    add_compile_options(-Wall -pedantic)
endif()
#set( CMAKE_VERBOSE_MAKEFILE on )

if(ICWYU)
    find_program(iwyu_path REQUIRED NAMES include-what-you-use iwyu)
    set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endif()

if(CPPCHECK)
    set(CMAKE_CXX_CPPCHECK /opt/homebrew/bin/cppcheck;--std=c++11;${CMAKE_SOURCE_DIR}/src)
endif()

if(CLANGTIDY)
    set(CMAKE_CXX_CLANG_TIDY clang-tidy; -header-filter=${CMAKE_SOURCE_DIR}/src/)
endif()

add_subdirectory(${CMAKE_SOURCE_DIR}/src)