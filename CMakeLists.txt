cmake_minimum_required(VERSION 3.3)
project(Block-Game)

set(CMAKE_EXE_LINKER_FLAGS -static)

find_package(OpenGL REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Including GLFW
add_subdirectory(glfw)
include_directories(glfw/include)

# Including GLAD
include_directories(glad/include)

# Including GLM
include_directories(glm/glm)

set(SOURCE_FILES src/main.cpp glad/src/glad.c src/Shader.cpp src/Shader.h src/Chunk.cpp src/Chunk.h src/stb_image.h src/Texture.cpp src/Texture.h src/Camera.cpp src/Camera.h)

add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_FILES})

# Linking GLFW and OGL
target_link_libraries(${CMAKE_PROJECT_NAME} glfw ${GLFW_LIBRARIES} ${OPENGL_LIBRARY})
