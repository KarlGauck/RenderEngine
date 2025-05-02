cmake_minimum_required(VERSION 3.30)
project(RenderEngine)

set(CMAKE_CXX_STANDARD 20)

# === Find external cmake-projects ===
find_package(glfw3 REQUIRED)

# === Include library directories ===
include_directories(lib/glad/include)
include_directories(lib/linmath)
include_directories(lib/stb)
include_directories(include)
include_directories(src/rendering)
# Executables
add_executable(RenderEngine src/main.cpp lib/glad/src/glad.c
        src/fileutils/FileInput.cpp
        include/rendering/MeshObject.h
        include/rendering/ShaderProgram.h
        src/rendering/MeshObject.inc
        src/rendering/ShaderProgram.cpp
        src/rendering/ShaderProgram.cpp
        include/rendering/TextureBehaviour.h
        include/rendering/Texture.h
        src/rendering/Texture.cpp
)


target_link_libraries(RenderEngine glfw)
