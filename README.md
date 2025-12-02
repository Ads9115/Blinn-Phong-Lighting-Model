# Blinn–Phong Lighting in OpenGL (C++)

This project implements a rotating 3D cube lit using the Blinn–Phong lighting model in modern OpenGL. It includes ambient, diffuse, and specular shading, along with a moving point light visualized by a small secondary cube.

The project is written entirely in C++ using GLFW, GLAD, and a custom math library.

<img width="1482" height="708" alt="Image" src="https://github.com/user-attachments/assets/5cfa3c6b-4f81-4377-9a86-cc2d6aeb60e1" />

## Features

- Blinn–Phong lighting model (ambient, diffuse, specular)
- Per-face normals for correct flat shading
- Animated point light moving along a circular path
- Emissive shader for a small “light cube” that displays the light position
- Full model–view–projection (MVP) pipeline
- Custom math library with:
  - vec3 operations
  - mat4 translate, scale, rotate
  - lookAt camera transform
  - perspective projection

## Build Instructions

1. Install dependencies:
   - GLFW
   - GLAD
   - OpenGL 3.3+
2. Include all `.vert`, `.frag`, and source files in your project.
3. Build using CMake or any IDE such as Visual Studio or CLion.
4. Run the executable.

## Future Improvements

- Shadow mapping
- Multiple light sources
- Soft shadows and global illumination experiments
- Integration with a CPU-side ray tracer
