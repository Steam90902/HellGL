cmake_minimum_required(VERSION 4.1)
project(ProjOpenGL)

set(CMAKE_CXX_STANDARD 20)

# ---------------------------
# Add your sources
# ---------------------------
add_executable(ProjOpenGL
        src/main.cpp
        glad/src/glad.c
        "include/shaderClass.h"
        src/shaderClass.cpp
        "include/VBO.h"
        src/VBO.cpp
        include/EBO.h
        src/EBO.cpp
        include/VAO.h
        src/VAO.cpp
)

# ---------------------------
# GLAD include
# ---------------------------
target_include_directories(ProjOpenGL PRIVATE
        ${PROJECT_SOURCE_DIR}/glad/include
        ${PROJECT_SOURCE_DIR}/include
)

# ---------------------------
# Fetch GLFW automatically
# ---------------------------
include(FetchContent)

FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG        3.4   # pick a stable version
)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)


# Download and make available
FetchContent_MakeAvailable(glfw)

# ---------------------------
# Find OpenGL
# ---------------------------
find_package(OpenGL REQUIRED)

# ---------------------------
# Link everything
# ---------------------------
target_link_libraries(ProjOpenGL
        PRIVATE
        glfw
        OpenGL::GL
)
