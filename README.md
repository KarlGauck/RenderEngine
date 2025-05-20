# RenderEngine
This is a basic render engine with 3d capabilities which will serve as a basis for any graphical coding-experiment, I will attempt.

## Features
- [x] Perspective Projection
- [ ] Orthographic Projection
- [x] Camera object to control view
- [x] Instances
- [x] SSBOS for custom shader data
- [x] Basic Wavefront Meshloader
- [ ] Material Support for Wavefront Meshloader
- [ ] Support for arbitrary meshes (using Assimp)
- [x] Default Shaders

## How to use
Currently, there is no way to create the window, since all of this functionality is hardcoded into main.

The steps to get a functional image are the following
#### The first triangle (and fully lighted and textured mesh :))
1) Create a shaderprogram with the respective fragment and vertexshaders.
```c
ShaderProgram program {"vertex_path/vertex.glsl", "fragment_path/fragment.glsl"};
program.create_gl_program();
```
2) Create or load a mesh and store it inside a meshobject
```c
// you can also specify the vertices and indices manually
MeshObject mesh = MeshParser::parse_wavefront_obj(FileInput::read_file("mesh_path/mesh.obj"));
mesh.create_buffers();
```

3) Create texturedata and behaviour (optional)
```c
TextureBehaviour texture_behaviour {
    REPEAT,
    REPEAT,
    REPEAT,
    LINEAR,
    LINEAR,
    LINEAR,
    {1.f, 1.f, 1.f, 1.f}
};

Texture texture{};
texture.load_texture(FileInput::read_texture("texture_path/texture.png"));
texture.set_texture_behaviour(texture_behaviour);

// 
mesh.set_texture(0, "texture", texture);
```
4) Create a camera
```c
camera = {
    glm::vec3(0, 0, 0),   // position
    glm::radians(45.f),   // pitch
    glm::radians(-225.f), // yaw
    glm::radians(45.f),   // fov
    0.1f,                 // near plane
    1000.f,               // far plane
    1                     // aspect ratio
};
```

5) Render the mesh
```c
glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
program.render(mesh, camera);
glfwSwapBuffers(window);
```

#### Instanced Rendering
1) Create an instancemanager
```c
InstanceManager instancer(mesh);
instancer.create_buffer();
```

2) Create an instance vector of model matrices
```c
std::vector instances = {
    Instance {
        glm::translate(glm::scale(glm::mat4(1.f), glm::vec3(1.f)), glm::vec3(0.f))
    },
    Instance {
        glm::translate(glm::scale(glm::mat4(1.f), glm::vec3(1.f)), glm::vec3(1.f))
    }
};

instancer.set_instances(instances);
```

3) Render all of the instances
```c
glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
program.render_instanced(instances, camera);
glfwSwapBuffers(window);
```

#### Using SSBOs
Create some struct to upload or upload any inplace data structure such
as numbers, arrays etc. Just make sure, it works with the memory-structure you specify in your shader (such as std430).
```c
struct Data {
    float value1;
    float value2;
};

std::vector<Data> data {
    {
        0.4f,
        2.5f
    },
    {
        10.f
        0.f
    }
};

ShaderStorageBuffer buffer;
buffer.create_buffer();
buffer.set_data(data);
```

Before rendering, bind the buffer to the correct location.
```c
buffer.bind(1);
program.render...;
```

Make sure to include the same structures inside the respective shader.
```glsl
struct Data {
    float value1;
    float value2;
};

// make sure, the binding index matches the index in your c++ code.
layout(binding = 1, std430) readonly buffer ssbo1 {
    Data data[];
};

// inside shader.glsl
```
