#include "Game.h"
#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>

Game::Game(int width, int height)
    : width(width), height(height),
      window("Engine - Clean Code", width, height),
      shader("assets/shaders/sprite.vert", "assets/shaders/sprite.frag"),
      texture("assets/textures/player.png"),
      sprite(&texture, {400.0f, 300.0f}, {64.0f, 64.0f})
{
    projection = glm::ortho(0.0f, (float)width, (float)height, 0.0f, -1.0f, 1.0f);
}

void Game::run() {
    float speed = 200.0f;

    while (window.isRunning()) {
        window.pollEvents();
        input.update();

        double dt = timer.getDeltaTime();
        glm::vec2 pos = sprite.getPosition();

        if (input.isKeyDown(SDL_SCANCODE_W)) pos.y -= speed * dt;
        if (input.isKeyDown(SDL_SCANCODE_S)) pos.y += speed * dt;
        if (input.isKeyDown(SDL_SCANCODE_A)) pos.x -= speed * dt;
        if (input.isKeyDown(SDL_SCANCODE_D)) pos.x += speed * dt;

        pos.x = std::clamp(pos.x, 0.0f, (float)width - sprite.getSize().x);
        pos.y = std::clamp(pos.y, 0.0f, (float)height - sprite.getSize().y);

        sprite.setPosition(pos);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        sprite.draw(shader, projection);
        window.swapBuffers();
    }
}
