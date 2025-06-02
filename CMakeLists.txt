cmake_minimum_required(VERSION 3.30)
project(RenderEngine)

set(CMAKE_CXX_STANDARD 20)

# === Find external cmake-projects ===
find_package(glfw3 REQUIRED)
find_package(glm CONFIG REQUIRED)

# === Include library directories ===
include_directories(lib/glad/include)
include_directories(lib/linmath)
include_directories(lib/stb)
include_directories(include)
# Executables
add_executable(RenderEngine src/main.cpp lib/glad/src/glad.c
        src/fileutils/FileInput.cpp
        include/rendering/MeshObject.h
        include/rendering/ShaderProgram.h
        src/rendering/MeshObject.cpp
        src/rendering/ShaderProgram.cpp
        src/rendering/ShaderProgram.cpp
        include/rendering/TextureBehaviour.h
        include/rendering/Texture.h
        src/rendering/Texture.cpp
        include/rendering/InstanceManager.h
        src/rendering/InstanceManager.cpp
        include/rendering/Camera.h
        src/rendering/Camera.cpp
        include/fileutils/MeshParser.h
        src/fileutils/MeshParser.cpp
        include/stdextentions/StringUtils.h
        src/stdextentions/StringUtils.cpp
        include/rendering/ShaderStorageBuffer.h
        src/rendering/ShaderStorageBuffer.cpp
        include/rendering/Window.h
)


target_link_libraries(RenderEngine PRIVATE glfw glm::glm)
