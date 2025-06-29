#include <csignal>
#include <iostream>

#include "rendering/Renderer.hpp"
#include "scene/Camera.hpp"
#include "scene/Scene.hpp"

volatile bool g_running = true;

void signalHandler(int signum) {
    g_running = false;
}

int main() {
    signal(SIGINT, signalHandler);

    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 600;

    Renderer renderer(WINDOW_WIDTH, WINDOW_HEIGHT);
    if (!renderer.initialize()) {
        std::cerr << "Failed to initialize renderer!" << std::endl;
        return -1;
    }

    Scene scene;
    scene.createDefaultScene();

    Camera camera(Vector3(0, 0, -10), Vector3(0, 0, 0), Vector3(0, 1, 0), 60.0f * M_PI / 180.0f);

    std::cout << "Ray Tracing Application Started" << std::endl;
    std::cout << "Controls:" << std::endl;
    std::cout << "- Left mouse drag: Rotate camera" << std::endl;
    std::cout << "- Mouse wheel: Zoom in/out" << std::endl;
    std::cout << "- Close window to exit" << std::endl;

    bool running = true;
    while (running && g_running) {
        renderer.handleEvents(camera);

        if (renderer.shouldClose() || !g_running) {
            running = false;
        }

        renderer.render(scene, camera);

        renderer.present();
    }

    std::cout << "Application closing..." << std::endl;
    return 0;
}
