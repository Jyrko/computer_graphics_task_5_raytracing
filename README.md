# Ray Tracing - Spheres

A C++ implementation of ray-casting rendering for spheres using the Phong illumination model.

## Features

- Ray-casting algorithm for sphere intersection
- Phong illumination model (ambient, diffuse, specular lighting)
- Interactive orbital camera controls
- Multiple spheres with different materials
- Real-time rendering using SDL2

## Requirements

- C++17 compiler
- SDL2 library
- CMake 3.16+

## Building on macOS

### Install SDL2 using Homebrew:
```bash
brew install sdl2
```

### Build the project:
```bash
mkdir build
cd build
cmake ..
make
```

### Run the application:
```bash
./raytracing
```

## Code Formatting

This project uses clang-format for consistent code style.

### Format all source files:
```bash
# Using the script
./format.sh

# Or using CMake
make format
```

### Check formatting without modifying files:
```bash
make format-check
```

### Install clang-format (if not already installed):
```bash
brew install clang-format
```

## Controls

- **Left mouse drag**: Rotate camera around the scene
- **Mouse wheel**: Zoom in/out
- **Close window**: Exit application

## Project Structure

```
src/
├── main.cpp                 # Main application entry point
├── math/                    # Mathematical utilities
│   ├── Vector3.hpp/cpp      # 3D vector operations
│   ├── Matrix4.hpp/cpp      # 4x4 matrix transformations
│   └── Ray.hpp/cpp          # Ray representation
├── scene/                   # Scene objects
│   ├── Sphere.hpp/cpp       # Sphere geometry and intersection
│   ├── Light.hpp/cpp        # Point light source
│   ├── Camera.hpp/cpp       # Camera with orbital controls
│   └── Scene.hpp/cpp        # Scene management
├── rendering/               # Rendering pipeline
│   ├── Renderer.hpp/cpp     # SDL2 renderer and event handling
│   └── Phong.hpp/cpp        # Phong illumination model
└── utils/                   # Utility classes
    └── Color.hpp/cpp        # Color representation
```

## Implementation Details

- **Ray-Sphere Intersection**: Solves quadratic equation for ray-sphere intersection
- **Phong Shading**: Implements ambient, diffuse, and specular reflection components
- **Camera System**: Orbital camera with spherical coordinate system
- **Material Properties**: Configurable ambient, diffuse, and specular coefficients

## Scene Configuration

The default scene includes:
- 4 spheres with different colors and materials
- 1 white point light source
- Configurable ambient lighting
- Interactive camera controls

You can modify the scene by editing the `createDefaultScene()` function in `Scene.cpp`.
