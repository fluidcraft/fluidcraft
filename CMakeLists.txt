cmake_minimum_required(VERSION 3.21)
project(mcpp LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SOURCES ./mcpp/*.cpp)

link_directories(/usr/local/lib64)

add_executable(${PROJECT_NAME} ${SOURCES})
target_compile_options(
	${PROJECT_NAME}
	PRIVATE
	-std=c++2b
	-Wall
	-Wextra
	-Werror
	-Wno-unused-parameter
	-Wno-unused-result
)
target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}")
target_link_libraries(
	${PROJECT_NAME} 
	spdlog fmt
)
install(TARGETS ${PROJECT_NAME})

