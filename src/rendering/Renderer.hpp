#pragma once
#include <SDL.h>

#include "../scene/Camera.hpp"
#include "../scene/Scene.hpp"

class Renderer {
  private:
    SDL_Window* window;
    SDL_Renderer* sdlRenderer;
    SDL_Texture* frameBuffer;
    uint32_t* pixels;
    int width, height;

  public:
    Renderer(int width, int height);
    ~Renderer();

    bool initialize();
    void cleanup();

    // Rendering
    void render(const Scene& scene, const Camera& camera);
    void present();
    void clear(const Color& color);

    // Pixel manipulation
    void setPixel(int x, int y, const Color& color);

    // Event handling
    bool shouldClose() const;
    void handleEvents(Camera& camera);

    // Getters
    int getWidth() const {
        return width;
    }
    int getHeight() const {
        return height;
    }
};
