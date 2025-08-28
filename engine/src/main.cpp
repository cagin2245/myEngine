#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include "Window.h"
#include "Renderer.h"
#include "Shader.h"


int main() {
    Window window("Engine - Triangle", 800, 600);
    if (!window.isRunning()) return -1;

    Shader shader("assets/shaders/triangle.vert", "assets/shaders/triangle.frag");
    Renderer renderer;

    while (window.isRunning()) {
        window.pollEvents();

        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        renderer.draw(shader);

        window.swapBuffers();
    }

    return 0;
}
