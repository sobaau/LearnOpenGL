find_library(COCOA_LIBRARY Cocoa REQUIRED CMAKE_FIND_FRAMEWORK)
find_library(IOKIT_LIBRARY IOKit REQUIRED CMAKE_FIND_FRAMEWORK)
find_library(OPENGL_LIBRARY OpenGL REQUIRED)
set(sources main.cpp glad.c mesh.cpp model.cpp shader.cpp)
set(headers mesh.h model.h shader.h)
add_executable(opengl ${sources} ${headers})
target_include_directories(opengl PUBLIC 
${CMAKE_CURRENT_SOURCE_DIR}/include
${CMAKE_SOURCE_DIR}/dependencies/glfw/include
${CMAKE_SOURCE_DIR}/dependencies/assimp/include
${CMAKE_SOURCE_DIR}/dependencies/imgui
${CMAKE_SOURCE_DIR}/dependencies/imgui/backends
${CMAKE_SOURCE_DIR}/dependencies/stb_image
${CMAKE_SOURCE_DIR}/dependencies/glm
)
target_link_libraries(opengl PUBLIC "${OPENGL_LIBRARY}" "${IOKIT_LIBRARY}" "${COCOA_LIBRARY}")
target_link_libraries(opengl PUBLIC glfw assimp imgui glm)
target_compile_features(opengl PUBLIC cxx_std_17)
set(CMAKE_CXX_FLAGS "-fvisibility=hidden")
