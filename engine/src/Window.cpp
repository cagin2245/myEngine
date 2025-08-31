#include <SDL2/SDL.h>
#include <glad/glad.h>
#include "Window.h"
#include "Core/Logger.h"
#include <iostream>

Window::Window(const char* title, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    Engine::Logger::log(std::string("SDL init failed: ") + SDL_GetError(), Engine::LogLevel::Error);
        running = false;
        return;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    window = SDL_CreateWindow(title,
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              width, height,
                              SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (!window) {
    Engine::Logger::log(std::string("Window creation failed: ") + SDL_GetError(), Engine::LogLevel::Error);
        running = false;
        return;
    }

    context = SDL_GL_CreateContext(window);
    if (!context) {
    Engine::Logger::log(std::string("OpenGL context failed: ") + SDL_GetError(), Engine::LogLevel::Error);
        running = false;
        return;
    }

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
    Engine::Logger::log("Failed to initialize GLAD", Engine::LogLevel::Error);
        running = false;
        return;
    }

    
    #ifdef ENGINE_DEV_MODE
    Engine::Logger::log(std::string("OpenGL Version: ") + reinterpret_cast<const char*>(glGetString(GL_VERSION)), Engine::LogLevel::Info);
    #endif
}

Window::~Window() {
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Window::swapBuffers() {
    SDL_GL_SwapWindow(window);
}

void Window::pollEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        }
    }
}
int Window::getWidth() const {
    int w;
    SDL_GetWindowSize(window, &w, nullptr);
    return w;
}
int Window::getHeight() const {
    int h;
    SDL_GetWindowSize(window, nullptr, &h);
    return h;
}
