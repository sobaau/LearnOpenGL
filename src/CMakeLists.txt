cmake_minimum_required(VERSION 3.7...3.20)
if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()
IF(APPLE)
    find_library(COCOA_LIBRARY Cocoa REQUIRED CMAKE_FIND_FRAMEWORK)
    find_library(IOKIT_LIBRARY IOKit REQUIRED CMAKE_FIND_FRAMEWORK)
    find_library(OPENGL_LIBRARY OpenGL REQUIRED)
ENDIF()
IF(WIN32)
    find_package(OpenGL REQUIRED)
ENDIF()

# Add source files
file(GLOB_RECURSE SOURCE_FILES 
	${CMAKE_SOURCE_DIR}/src/*.c
	${CMAKE_SOURCE_DIR}/src/*.cpp)	
# Add header files
file(GLOB_RECURSE HEADER_FILES 
	${CMAKE_SOURCE_DIR}/src/*.h
	${CMAKE_SOURCE_DIR}/src/*.hpp)

# set(CMAKE_CXX_CLANG_TIDY
#     clang-tidy;
#     -checks=*;)


add_executable(LearnOpenGL ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(LearnOpenGL PUBLIC 
${CMAKE_CURRENT_SOURCE_DIR}/include
${CMAKE_SOURCE_DIR}/dependencies/glfw/include
${CMAKE_SOURCE_DIR}/dependencies/assimp/include
${CMAKE_SOURCE_DIR}/dependencies/imgui
${CMAKE_SOURCE_DIR}/dependencies/imgui/backends
${CMAKE_SOURCE_DIR}/dependencies/stb_image
${CMAKE_SOURCE_DIR}/dependencies/glm
${CMAKE_SOURCE_DIR}/dependencies/glad/include
)
IF(APPLE)
    target_link_libraries(LearnOpenGL PUBLIC "${OPENGL_LIBRARY}" "${IOKIT_LIBRARY}" "${COCOA_LIBRARY}")
ENDIF()
IF(WIN32)
    target_link_libraries(LearnOpenGL PUBLIC OpenGL::GL User32.lib Gdi32.lib Shell32.lib kernel32.lib)
ENDIF()
target_link_libraries(LearnOpenGL PUBLIC glfw assimp imgui glm glad)
target_compile_features(LearnOpenGL PUBLIC cxx_std_17)
add_custom_command(TARGET LearnOpenGL POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/src/shaders/ $<TARGET_FILE_DIR:LearnOpenGL>/shaders/)
add_custom_command(TARGET LearnOpenGL POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/src/textures/ $<TARGET_FILE_DIR:LearnOpenGL>/textures/)
add_custom_command(TARGET LearnOpenGL POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/src/sponza/ $<TARGET_FILE_DIR:LearnOpenGL>/sponza/)
set(CMAKE_CXX_FLAGS "-fvisibility=hidden")
#target_precompile_headers(LearnOpenGL PUBLIC ${HEADER_FILES})
if (CMAKE_BUILD_TYPE EQUAL "Debug")
    message("debug mode")
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shaders DESTINATION ${CMAKE_BINARY_DIR}/bin/Debug/shaders)
ENDIF()
