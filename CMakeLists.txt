cmake_minimum_required(VERSION 3.7...3.20)
#set( CMAKE_VERBOSE_MAKEFILE on )
if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()
project(LearnOpenGL VERSION 1.0
        DESCRIPTION "https://learnopengl.com/"
        LANGUAGES CXX C)


set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(INJECT_DEBUG_POSTFIX OFF CACHE BOOL "" FORCE)
add_subdirectory(${CMAKE_SOURCE_DIR}/dependencies/glfw)
add_subdirectory(${CMAKE_SOURCE_DIR}/dependencies/assimp)
add_subdirectory(${CMAKE_SOURCE_DIR}/dependencies/imgui)
add_subdirectory(${CMAKE_SOURCE_DIR}/dependencies/glm)
add_subdirectory(${CMAKE_SOURCE_DIR}/dependencies/glad)
if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /EHsc)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall)
endif()
add_subdirectory(${CMAKE_SOURCE_DIR}/src)

#set(CMAKE_CXX_FLAGS "-fvisibility=hidden")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework Cocoa
#-framework OpenGL -framework IOKit")