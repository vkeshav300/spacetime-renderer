# Validity checks
if (NOT APPLE)
	message(FATAL_ERROR "This project is only supported on macOS")
endif()

# CMake config
cmake_minimum_required(VERSION 3.31.6)

# Debug config
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
	add_definitions(-DDEBUG)
	message(STATUS "Debug mode enabled")
endif()

# Project config
project(
	spacetime-renderer
	LANGUAGES CXX
)

set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")
set(EXTERNAL_HEADERS_DIR "${CMAKE_SOURCE_DIR}/dependencies")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")

# Language config
set(CMAKE_CXX_STANDARD 23)

# Misc config
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Find packages
find_package(GLFW3 REQUIRED)

# Process source files 
file(GLOB_RECURSE SOURCES
	"${SOURCE_DIR}/*.cpp"
	"${SOURCE_DIR}/*.mm"
)

add_executable(
	${PROJECT_NAME}
	${SOURCES}
)

# Process header files
target_include_directories(
	${PROJECT_NAME} PRIVATE
	${CMAKE_SOURCE_DIR}/include
	${GLFW3_INCLUDE_DIRS}
	${EXTERNAL_HEADERS_DIR}/metal-cpp
	${EXTERNAL_HEADERS_DIR}/metal-cpp-extensions
	${EXTERNAL_HEADERS_DIR}/stb
)

# Link external packages / libraries
target_link_libraries(
	${PROJECT_NAME} PUBLIC
	${GLFW3_LIBRARIES}
	"-framework Metal"
	"-framework Foundation"
	"-framework Quartzcore"
	"-framework IOKit"
	"-framework Cocoa"
	"-framework CoreGraphics"
	"-framework AppKit"
	"-framework MetalKit"
	objc
)


# Process metal shaders 
set(SHADER_SRC_DIR "${CMAKE_SOURCE_DIR}/shaders")
set(SHADER_BIN_DIR "${CMAKE_BINARY_DIR}/shaders")
set(METALLIB_OUTPUT "${CMAKE_BINARY_DIR}/default.metallib")

file(GLOB METAL_SHADERS "${SHADER_SRC_DIR}/*.metal")
file(MAKE_DIRECTORY "${SHADER_BIN_DIR}")

set(COMPILED_SHADERS)
foreach(SHADER ${METAL_SHADERS})
	get_filename_component(SHADER_NAME "${SHADER}" NAME_WE)
	set(COMPILED_SHADER "${SHADER_BIN_DIR}/${SHADER_NAME}.air")
	add_custom_command(
		OUTPUT "${COMPILED_SHADER}"
		COMMAND xcrun -sdk macosx metal -c "${SHADER}" -o "${COMPILED_SHADER}" -I "${CMAKE_SOURCE_DIR}/include"
		DEPENDS "${SHADER}"
		COMMENT "Compiling metal shader ${SHADER_NAME}.metal"
	)

	list(APPEND COMPILED_SHADERS "${COMPILED_SHADER}")
endforeach()

add_custom_command(
	OUTPUT "${METALLIB_OUTPUT}"
	COMMAND xcrun -sdk macosx metallib "${COMPILED_SHADERS}" -o "${METALLIB_OUTPUT}"
	DEPENDS ${COMPILED_SHADERS}
    COMMENT "Linking Metal shaders into default.metallib"
)

add_custom_target(metal_shaders ALL DEPENDS "${METALLIB_OUTPUT}")

