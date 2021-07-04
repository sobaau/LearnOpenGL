#set(HEADERS include/glad.h)
add_library(glad glad.c)
target_include_directories(glad PUBLIC 
${CMAKE_CURRENT_SOURCE_DIR}/include
${CMAKE_SOURCE_DIR}/dependencies/glfw/include
)
target_compile_features(imgui PUBLIC cxx_std_11)