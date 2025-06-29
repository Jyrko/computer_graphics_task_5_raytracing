cmake_minimum_required(VERSION 3.16)
project(RayTracing)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(src)

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

add_executable(raytracing ${SOURCES})

target_link_libraries(raytracing ${SDL2_LIBRARIES})

if(APPLE)
    target_include_directories(raytracing PRIVATE /opt/homebrew/include)
    target_link_directories(raytracing PRIVATE /opt/homebrew/lib)
    target_link_libraries(raytracing SDL2)
endif()

# Clang-format support
find_program(CLANG_FORMAT clang-format)
if(CLANG_FORMAT)
    file(GLOB_RECURSE ALL_CXX_SOURCE_FILES
        ${CMAKE_SOURCE_DIR}/src/*.cpp
        ${CMAKE_SOURCE_DIR}/src/*.hpp
    )
    
    add_custom_target(format
        COMMAND ${CLANG_FORMAT} -i ${ALL_CXX_SOURCE_FILES}
        COMMENT "Running clang-format on all source files"
    )
    
    add_custom_target(format-check
        COMMAND ${CLANG_FORMAT} --dry-run --Werror ${ALL_CXX_SOURCE_FILES}
        COMMENT "Checking if source files are properly formatted"
    )
endif()
