#include "Game.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <algorithm>

namespace Engine
{

    Game::Game(int width, int height)
        : width(width), height(height),
          window("Engine - Clean Collision", width, height)
    {
        shader = std::make_shared<Shader>("assets/shaders/sprite.vert", "assets/shaders/sprite.frag");
        playerTexture = std::make_shared<Texture>("assets/textures/player.png");
        enemyTexture = std::make_shared<Texture>("assets/textures/enemy.png");
        player = std::make_shared<Sprite>(playerTexture, glm::vec2{200.0f, 200.0f}, glm::vec2{64.0f, 64.0f});
        enemy = std::make_shared<Sprite>(enemyTexture, glm::vec2{400.0f, 300.0f}, glm::vec2{64.0f, 64.0f});
        projection = glm::ortho(0.0f, (float)width, (float)height, 0.0f, -1.0f, 1.0f);
    }

    void Game::processInput(double dt)
    {
        input.update();
    lastPlayerPos = player->getPosition(); // önceki frame kaydet
    glm::vec2 pos = lastPlayerPos;

        // WASD hareketi uygula
        if (input.isKeyDown(SDL_SCANCODE_W))
            pos.y -= speed * dt;
        if (input.isKeyDown(SDL_SCANCODE_S))
            pos.y += speed * dt;
        if (input.isKeyDown(SDL_SCANCODE_A))
            pos.x -= speed * dt;
        if (input.isKeyDown(SDL_SCANCODE_D))
            pos.x += speed * dt;

    pos.x = std::clamp(pos.x, 0.0f, (float)width - player->getSize().x);
    pos.y = std::clamp(pos.y, 0.0f, (float)height - player->getSize().y);

    player->setPosition(pos);
    }

    void Game::update(double dt)
    {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

    glm::vec2 playerCenter = player->getPosition() + player->getSize() * 0.5f;
    glm::vec2 direction = glm::vec2(mouseX, mouseY) - playerCenter;

        float angle = atan2(direction.y, direction.x); // radyan
        float angleDeg = glm::degrees(angle);

        std::cout << "Mouse: (" << mouseX << "," << mouseY
                  << ") | Angle rad: " << angle
                  << " | deg: " << angleDeg << std::endl;

    player->setRotation(angle); // şimdilik +90 ekleme

        // Çarpışma kontrolü
        if (Collision::AABB(*player, *enemy))
        {
            std::cout << "Collision detected!" << std::endl;
            player->setPosition(lastPlayerPos); // direkt eski pozisyona al
        }
    }

    void Game::render()
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        player->draw(*shader, projection);
        if (Collision::AABB(*player, *enemy))
        {
            glUniform4f(glGetUniformLocation(shader->getID(), "overrideColor"), 1.0f, 0.0f, 0.0f, 1.0f);
        }
        else
        {
            glUniform4f(glGetUniformLocation(shader->getID(), "overrideColor"), 1.0f, 1.0f, 1.0f, 1.0f);
        }
        enemy->draw(*shader, projection);

        window.swapBuffers();
    }

    void Game::run()
    {
        while (window.isRunning())
        {
            window.pollEvents();
            double dt = timer.getDeltaTime();
            processInput(dt);
            update(dt);
            render();
        }
    }

}
