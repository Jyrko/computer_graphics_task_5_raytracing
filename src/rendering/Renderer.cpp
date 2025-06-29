#include "Renderer.hpp"

#include <iostream>

#include "Phong.hpp"

Renderer::Renderer(int width, int height)
    : window(nullptr),
      sdlRenderer(nullptr),
      frameBuffer(nullptr),
      pixels(nullptr),
      width(width),
      height(height) {}

Renderer::~Renderer() {
    cleanup();
}

bool Renderer::initialize() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow("Ray Tracing - Spheres", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    sdlRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!sdlRenderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    frameBuffer = SDL_CreateTexture(sdlRenderer, SDL_PIXELFORMAT_RGB888,
                                    SDL_TEXTUREACCESS_STREAMING, width, height);

    if (!frameBuffer) {
        std::cerr << "Texture could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    pixels = new uint32_t[width * height];

    return true;
}

void Renderer::cleanup() {
    delete[] pixels;
    pixels = nullptr;

    if (frameBuffer) {
        SDL_DestroyTexture(frameBuffer);
        frameBuffer = nullptr;
    }

    if (sdlRenderer) {
        SDL_DestroyRenderer(sdlRenderer);
        sdlRenderer = nullptr;
    }

    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }

    SDL_Quit();
}

void Renderer::render(const Scene& scene, const Camera& camera) {
    clear(scene.backgroundColor);

    // Ray tracing for each pixel
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Ray ray = camera.getRay(x, y, width, height);
            Scene::HitInfo hit = scene.raycast(ray);

            Color pixelColor = scene.backgroundColor;

            if (hit.hit) {
                Vector3 viewDirection = (camera.position - hit.point).normalized();
                pixelColor =
                    PhongShader::calculateColor(hit.point, hit.normal, viewDirection, hit.material,
                                                scene.lights, scene.ambientLight);
            }

            setPixel(x, y, pixelColor);
        }
    }
}

void Renderer::present() {
    SDL_UpdateTexture(frameBuffer, nullptr, pixels, width * sizeof(uint32_t));
    SDL_RenderClear(sdlRenderer);
    SDL_RenderCopy(sdlRenderer, frameBuffer, nullptr, nullptr);
    SDL_RenderPresent(sdlRenderer);
}

void Renderer::clear(const Color& color) {
    uint32_t clearColor = color.toRGB();
    for (int i = 0; i < width * height; i++) {
        pixels[i] = clearColor;
    }
}

void Renderer::setPixel(int x, int y, const Color& color) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        pixels[y * width + x] = color.toRGB();
    }
}

bool Renderer::shouldClose() const {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            return true;
        }
    }
    return false;
}

void Renderer::handleEvents(Camera& camera) {
    SDL_Event e;
    static bool mousePressed = false;
    static int lastMouseX = 0, lastMouseY = 0;

    while (SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_MOUSEBUTTONDOWN:
                if (e.button.button == SDL_BUTTON_LEFT) {
                    mousePressed = true;
                    lastMouseX = e.button.x;
                    lastMouseY = e.button.y;
                }
                break;

            case SDL_MOUSEBUTTONUP:
                if (e.button.button == SDL_BUTTON_LEFT) {
                    mousePressed = false;
                }
                break;

            case SDL_MOUSEMOTION:
                if (mousePressed) {
                    int deltaX = e.motion.x - lastMouseX;
                    int deltaY = e.motion.y - lastMouseY;

                    camera.rotate(deltaY * 0.01f, deltaX * 0.01f);

                    lastMouseX = e.motion.x;
                    lastMouseY = e.motion.y;
                }
                break;

            case SDL_MOUSEWHEEL: {
                float currentDistance = camera.distance;
                currentDistance += e.wheel.y * -0.5f;
                currentDistance = std::max(1.0f, std::min(20.0f, currentDistance));
                camera.setDistance(currentDistance);
            } break;
        }
    }
}
