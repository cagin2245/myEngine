#include <glad/glad.h>

#include "Core/Profiler.h"
#include "ResourceManager.h"
#include "Game.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <algorithm>

namespace Engine
{
    // ...existing code...
    Game::Game(int width, int height)
        : width(width), height(height),
          window("Engine - Clean Collision", width, height)
#ifdef ENGINE_DEV_MODE
        , profiler()
        , profilerOverlay(profiler)
#endif
    {
#ifdef ENGINE_DEV_MODE
        std::cout << "DEV MODE" << std::endl;
        
#endif
        shader = ResourceManager::LoadShader("assets/shaders/sprite.vert", "assets/shaders/sprite.frag", "sprite");
        playerTexture = ResourceManager::LoadTexture("assets/textures/player.png", "player");
        enemyTexture = ResourceManager::LoadTexture("assets/textures/enemy.png", "enemy");
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

        player->setRotation(angle); // şimdilik +90 ekleme

        // Çarpışma kontrolü
        if (Collision::AABB(*player, *enemy))
        {

            player->setPosition(lastPlayerPos); // direkt eski pozisyona al
        }
    }

    void Game::render()
    {
        PROFILE_FUNCTION();
        glViewport(0, 0, width, height);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glClear(GL_COLOR_BUFFER_BIT);
#ifdef ENGINE_DEV_MODE
        profilerOverlay.render();
#endif

        if (!shader)
        {
            std::cerr << "[render] Shader pointer null!" << std::endl;
        }
        if (!playerTexture)
        {
            std::cerr << "[render] Player texture pointer null!" << std::endl;
        }
        if (!enemyTexture)
        {
            std::cerr << "[render] Enemy texture pointer null!" << std::endl;
        }
        if (!player)
        {
            std::cerr << "[render] Player sprite pointer null!" << std::endl;
        }
        if (!enemy)
        {
            std::cerr << "[render] Enemy sprite pointer null!" << std::endl;
        }

        if (shader && player)
            player->draw(*shader, projection);
        if (shader && player && enemy && Collision::AABB(*player, *enemy))
        {
            glUniform4f(glGetUniformLocation(shader->getID(), "overrideColor"), 1.0f, 0.0f, 0.0f, 1.0f);
        }
        else if (shader)
        {
            glUniform4f(glGetUniformLocation(shader->getID(), "overrideColor"), 1.0f, 1.0f, 1.0f, 1.0f);
        }
        if (shader && enemy)
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
