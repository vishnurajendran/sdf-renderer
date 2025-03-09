cmake_minimum_required(VERSION 3.0)
project(sdf_renderer)

set(CMAKE_CXX_STANDARD 20)

# Include Directories
set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/src)
set(GLAD_HEADER_DIR ${PROJECT_SOURCE_DIR}/vendor/glad/include)

# Source Files
set(SRC_FILES
        src/main.cpp
        src/shader/Shader.cpp
        src/shader/Shader.h
        src/utils/fileio.cpp
        src/utils/fileio.h
        src/glutils/gl_utils.cpp
        src/glutils/gl_utils.h
        src/renderer/SDFRenderer.cpp
        src/renderer/SDFRenderer.h
        src/shader/data/generic_shader_data.h
        src/shader/data/ray_shader_data.h
        src/shader/data/lighting_shader_data.h
        src/shader/data/ray_shader_data.cpp
        src/shader/data/lighting_shader_data.cpp
        src/shader/data/generic_shader_data.cpp
        src/renderer/scene/scene_element.cpp
        src/renderer/scene/scene_element.h
        src/renderer/scene/Camera.cpp
        src/renderer/scene/Camera.h
)

# Include FetchContent for GLFW
include(FetchContent)
FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.3.8
)
FetchContent_MakeAvailable(glfw)

# Include FetchContent for GLFW
FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG master
)
FetchContent_MakeAvailable(glm)

# Create GLAD Library
add_library(glad ${PROJECT_SOURCE_DIR}/vendor/glad/src/glad.c)
target_include_directories(glad PUBLIC ${GLAD_HEADER_DIR})

# Set binary output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Create the executable
add_executable(sdf_renderer ${SRC_FILES})
target_include_directories(sdf_renderer PRIVATE ${INCLUDE_DIR})

# Link Libraries
target_link_libraries(sdf_renderer PRIVATE glad glfw glm)
