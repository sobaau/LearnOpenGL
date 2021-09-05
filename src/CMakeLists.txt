cmake_minimum_required(VERSION 3.7...3.20)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
  cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

if(APPLE)
  find_library(COCOA_LIBRARY Cocoa REQUIRED CMAKE_FIND_FRAMEWORK)
  find_library(IOKIT_LIBRARY IOKit REQUIRED CMAKE_FIND_FRAMEWORK)
  find_library(OPENGL_LIBRARY OpenGL REQUIRED)
endif()

if(WIN32)
  find_package(OpenGL REQUIRED)
endif()

option(MOVE_ASSETS "Move assets after build" ON)
option(USE_PCH "Use Precombiled Headers" OFF)

# Add source files
file(GLOB_RECURSE SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/*.c
     ${CMAKE_SOURCE_DIR}/src/*.cpp)
# Add header files
file(GLOB_RECURSE HEADER_FILES ${CMAKE_SOURCE_DIR}/src/*.h
     ${CMAKE_SOURCE_DIR}/src/*.hpp)

add_executable(OpenGLDemo ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(
  OpenGLDemo SYSTEM
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
          ${CMAKE_SOURCE_DIR}/dependencies/glfw/include
          ${CMAKE_SOURCE_DIR}/dependencies/assimp/include
          ${CMAKE_SOURCE_DIR}/dependencies/imgui
          ${CMAKE_SOURCE_DIR}/dependencies/imgui/backends
          ${CMAKE_SOURCE_DIR}/dependencies/stb_image
          ${CMAKE_SOURCE_DIR}/dependencies/glm
          ${CMAKE_SOURCE_DIR}/dependencies/glad/include)

if(APPLE)
  target_link_libraries(
    OpenGLDemo PRIVATE "${OPENGL_LIBRARY}" "${IOKIT_LIBRARY}"
                       "${COCOA_LIBRARY}")
endif()

if(WIN32)
  target_link_libraries(OpenGLDemo PRIVATE OpenGL::GL User32.lib Gdi32.lib
                                           Shell32.lib kernel32.lib)
endif()

target_link_libraries(OpenGLDemo PRIVATE glfw assimp imgui glm glad)

# if(MOVE_ASSETS)
#   if(WIN32)
#     add_custom_command(
#       TARGET OpenGLDemo
#       POST_BUILD
#       COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/src/shaders/"
#               "$<TARGET_FILE_DIR:OpenGLDemo>/shaders/")
#     add_custom_command(
#       TARGET OpenGLDemo
#       POST_BUILD
#       COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/src/textures/"
#               "$<TARGET_FILE_DIR:OpenGLDemo>/textures/")
#     add_custom_command(
#       TARGET OpenGLDemo
#       POST_BUILD
#       COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/src/sponza/"
#               "$<TARGET_FILE_DIR:OpenGLDemo>/sponza/")
#     add_custom_command(
#       TARGET OpenGLDemo
#       POST_BUILD
#       COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/src/rock/"
#               "$<TARGET_FILE_DIR:OpenGLDemo>/rock/")
#     add_custom_command(
#       TARGET OpenGLDemo
#       POST_BUILD
#       COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/src/planet/"
#               "$<TARGET_FILE_DIR:OpenGLDemo>/planet/")
#   else()
#     add_custom_command(
#       TARGET OpenGLDemo
#       POST_BUILD
#       COMMAND rsync ARGS -r "${CMAKE_SOURCE_DIR}/src/shaders/"
#               "$<TARGET_FILE_DIR:OpenGLDemo>/shaders/")
#     add_custom_command(
#       TARGET OpenGLDemo
#       POST_BUILD
#       COMMAND rsync ARGS -r "${CMAKE_SOURCE_DIR}/src/textures/"
#               "$<TARGET_FILE_DIR:OpenGLDemo>/textures/")
#     add_custom_command(
#       TARGET OpenGLDemo
#       POST_BUILD
#       COMMAND rsync ARGS -r "${CMAKE_SOURCE_DIR}/src/sponza/"
#               "$<TARGET_FILE_DIR:OpenGLDemo>/sponza/")
#     add_custom_command(
#       TARGET OpenGLDemo
#       POST_BUILD
#       COMMAND rsync ARGS -r "${CMAKE_SOURCE_DIR}/src/rock/"
#               "$<TARGET_FILE_DIR:OpenGLDemo>/rock/")
#     add_custom_command(
#       TARGET OpenGLDemo
#       POST_BUILD
#       COMMAND rsync ARGS -r "${CMAKE_SOURCE_DIR}/src/planet/"
#               "$<TARGET_FILE_DIR:OpenGLDemo>/planet/")
#   endif()
# endif()

if(USE_PCH)
  target_precompile_headers(OpenGLDemo PRIVATE ${HEADER_FILES})
endif()
