#include <iostream>
#include "scene/Scene.hpp"
#include "scene/Camera.hpp"
#include "rendering/Renderer.hpp"

int main() {
    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 600;
    
    // Initialize renderer
    Renderer renderer(WINDOW_WIDTH, WINDOW_HEIGHT);
    if (!renderer.initialize()) {
        std::cerr << "Failed to initialize renderer!" << std::endl;
        return -1;
    }
    
    // Create scene
    Scene scene;
    scene.createDefaultScene();
    
    // Create camera
    Camera camera(Vector3(0, 0, -5), Vector3(0, 0, 0), Vector3(0, 1, 0), 45.0f * M_PI / 180.0f);
    
    std::cout << "Ray Tracing Application Started" << std::endl;
    std::cout << "Controls:" << std::endl;
    std::cout << "- Left mouse drag: Rotate camera" << std::endl;
    std::cout << "- Mouse wheel: Zoom in/out" << std::endl;
    std::cout << "- Close window to exit" << std::endl;
    
    // Main loop
    bool running = true;
    while (running) {
        // Handle events
        renderer.handleEvents(camera);
        
        // Check if should close
        if (renderer.shouldClose()) {
            running = false;
        }
        
        // Render scene
        renderer.render(scene, camera);
        
        // Present frame
        renderer.present();
    }
    
    std::cout << "Application closing..." << std::endl;
    return 0;
}
