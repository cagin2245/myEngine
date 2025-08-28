#pragma once
#include <SDL2/SDL.h>

class Window {
public:
    Window(const char* title, int width, int height);
    ~Window();

    void swapBuffers();
    bool shouldClose();
    void pollEvents();

private:
    SDL_Window* window;
    SDL_GLContext context;
    bool running = true;

public:
    inline bool isRunning() const { return running; }
};
