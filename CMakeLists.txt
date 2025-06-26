cmake_minimum_required(VERSION 3.16)
project(RayTracing)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SDL2
find_package(SDL2 REQUIRED)

# Include directories
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(src)

# Source files
set(SOURCES
    src/main.cpp
    src/math/Vector3.cpp
    src/math/Matrix4.cpp
    src/math/Ray.cpp
    src/scene/Sphere.cpp
    src/scene/Light.cpp
    src/scene/Camera.cpp
    src/scene/Scene.cpp
    src/rendering/Renderer.cpp
    src/rendering/Phong.cpp
    src/utils/Color.cpp
)

# Create executable
add_executable(raytracing ${SOURCES})

# Link libraries
target_link_libraries(raytracing ${SDL2_LIBRARIES})

# For macOS, you might need to add the following if using Homebrew SDL2
if(APPLE)
    target_include_directories(raytracing PRIVATE /opt/homebrew/include)
    target_link_directories(raytracing PRIVATE /opt/homebrew/lib)
    target_link_libraries(raytracing SDL2)
endif()
