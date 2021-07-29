cmake_minimum_required(VERSION 3.7...3.20)
#set( CMAKE_VERBOSE_MAKEFILE on )
if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()
project(glad C)

file(GLOB_RECURSE SOURCE_FILES 
	${CMAKE_CURRENT_SOURCE_DIR}/*.c
	${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)	
# Add header files
file(GLOB_RECURSE HEADER_FILES 
	${CMAKE_CURRENT_SOURCE_DIR}/*.h
	${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)


add_library(glad ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(glad PUBLIC 
${CMAKE_CURRENT_SOURCE_DIR}/include
${CMAKE_SOURCE_DIR}/dependencies/glfw/include
)