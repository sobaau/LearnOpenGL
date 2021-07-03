cmake_minimum_required(VERSION 3.7...3.20)
#set( CMAKE_VERBOSE_MAKEFILE on )
if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()
project(LearnOpenGL VERSION 1.0
        DESCRIPTION "https://learnopengl.com/"
        LANGUAGES CXX C)

#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
#set(INJECT_DEBUG_POSTFIX OFF CACHE BOOL "" FORCE)
add_subdirectory(${CMAKE_SOURCE_DIR}/dependencies/glfw)
add_subdirectory(${CMAKE_SOURCE_DIR}/dependencies/assimp)

include_directories("${CMAKE_SOURCE_DIR}/src/include")
find_library(COCOA_LIBRARY Cocoa REQUIRED CMAKE_FIND_FRAMEWORK)
find_library(IOKIT_LIBRARY IOKit REQUIRED CMAKE_FIND_FRAMEWORK)
find_library(OPENGL_LIBRARY OpenGL REQUIRED)
#find_library(ASSIMP assimp "${CMAKE_SOURCE_DIR}/src/lib/" REQUIRED STATIC)


# add_library(assimp STATIC IMPORTED)
# add_library(glfw STATIC IMPORTED)
# set_target_properties(assimp PROPERTIES
#   IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/src/lib/libassimp.a"
#   INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/src/include/assimp"
# )
# set_target_properties(glfw PROPERTIES
#   IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/src/lib/libglfw3.a"
#   INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/src/include/GLFW"
# )
set(sources src/main.cpp src/glad.c src/mesh.cpp src/model.cpp src/shader.cpp)
set(headers src/mesh.h src/model.h src/shader.h)
add_executable(opengl ${sources} ${headers})
target_link_libraries(opengl PUBLIC "${OPENGL_LIBRARY}" "${IOKIT_LIBRARY}" "${COCOA_LIBRARY}")
target_link_libraries(opengl PUBLIC glfw assimp)
target_compile_features(opengl PUBLIC cxx_std_17)
set(CMAKE_CXX_FLAGS "-fvisibility=hidden")

#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework Cocoa
#-framework OpenGL -framework IOKit")