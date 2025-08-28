#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include "Window.h"
#include "Shader.h"
#include "Texture.h"
#include "Sprite.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int main() {
    Window window("Engine - Sprite", 800, 600);
    if (!window.isRunning()) return -1;

    Shader shader("assets/shaders/sprite.vert", "assets/shaders/sprite.frag");
    Texture texture("assets/textures/player.png");
    Sprite sprite(&texture, {0.0f, 0.0f}, {100.0f, 100.0f});

    // Ortho projection (0,0 sol üst - 800x600 ekran boyutları)
    glm::mat4 projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);

    // Model matrix (sprite’in pozisyon ve boyutu)
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(200.0f, 200.0f, 0.0f)); // 200x200’e taşı
    model = glm::scale(model, glm::vec3(100.0f, 100.0f, 1.0f));     // 100x100 boyut

    shader.use();
    glUniformMatrix4fv(glGetUniformLocation(shader.getID(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(glGetUniformLocation(shader.getID(), "model"), 1, GL_FALSE, glm::value_ptr(model));

    while (window.isRunning()) {
        window.pollEvents();

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        sprite.draw(shader);

        window.swapBuffers();
    }

    return 0;
}
