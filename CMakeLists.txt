cmake_minimum_required(VERSION 3.0)
project(sdf_renderer)

set(CMAKE_CXX_STANDARD 20)
set (GLAD_HEADER_DIR ${PROJECT_SOURCE_DIR}/vendor/glad/include)

set(GLAD_HEADER_FILE ${PROJECT_SOURCE_DIR}/vendor/glad/include/glad/glad.h)
set(GLAD_SRC_FILE ${PROJECT_SOURCE_DIR}/vendor/glad/src/glad.c)

include(FetchContent)
# Fetch GLFW
FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG        3.3.8 # Change this to the latest stable version if needed
)

FetchContent_MakeAvailable(glfw)

message(${GLAD_HEADER_FILE} ${GLAD_SRC_FILE})
add_library(glad ${GLAD_HEADER_FILE} ${GLAD_SRC_FILE})
target_include_directories(glad PUBLIC ${GLAD_HEADER_DIR})

# Set binary output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Create the executable
add_executable(sdf_renderer main.cpp)

# Link necessary libraries
target_link_libraries(sdf_renderer PRIVATE
        glad
        glfw
)
