#include <glad/glad.h>

#include "Core/Profiler.h"
#include "Core/MemoryTracker.h"
#include "Core/TextRenderer.h"
#include "ResourceManager.h"
#include "Game.h"
#include "Core/Logger.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <algorithm>

namespace Engine
{
#// ...existing code...
    Game::Game(int width, int height)
        : width(width), height(height),
          window("Engine - Clean Collision", width, height)
#ifdef ENGINE_DEV_MODE
          ,
          profiler()
#endif
    {
#ifdef ENGINE_DEV_MODE
        // textRenderer is a shared_ptr in the header; create it here and then
        // construct the profiler overlay which expects a reference + shared_ptr
        textRenderer = std::make_shared<TextRenderer>(width, height);
        textRenderer->load("assets/fonts/arial.ttf", 24);
        profilerOverlay = std::make_unique<ProfilerOverlay>(profiler, textRenderer);
#endif
#ifdef ENGINE_DEV_MODE
    Engine::Logger::log("DEV MODE", Engine::LogLevel::Debug);

#endif
        shader = ResourceManager::LoadShader("assets/shaders/sprite.vert", "assets/shaders/sprite.frag", "sprite");
        playerTexture = ResourceManager::LoadTexture("assets/textures/player.png", "player");
        enemyTexture = ResourceManager::LoadTexture("assets/textures/enemy.png", "enemy");
    player = std::make_unique<Sprite>(playerTexture, glm::vec2{200.0f, 200.0f}, glm::vec2{64.0f, 64.0f});
    enemy = std::make_unique<Sprite>(enemyTexture, glm::vec2{400.0f, 300.0f}, glm::vec2{64.0f, 64.0f});
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
        glEnable(GL_BLEND);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glViewport(0, 0, width, height);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glClear(GL_COLOR_BUFFER_BIT);
        // NOTE: profiler overlay will be rendered after scene objects so it appears on top

        if (!shader)
        {
            Engine::Logger::log("[render] Shader pointer null!", Engine::LogLevel::Error);
        }
        if (!playerTexture)
        {
            Engine::Logger::log("[render] Player texture pointer null!", Engine::LogLevel::Error);
        }
        if (!enemyTexture)
        {
            Engine::Logger::log("[render] Enemy texture pointer null!", Engine::LogLevel::Error);
        }
        if (!player)
        {
            Engine::Logger::log("[render] Player sprite pointer null!", Engine::LogLevel::Error);
        }
        if (!enemy)
        {
            Engine::Logger::log("[render] Enemy sprite pointer null!", Engine::LogLevel::Error);
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

#ifdef ENGINE_DEV_MODE
        // Draw profiler overlay after scene so it appears on top
        if (profilerOverlay)
        {
            // Ensure overlay draws above everything
            glDisable(GL_DEPTH_TEST);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            profilerOverlay->render(10,30);
        }
#endif

        window.swapBuffers();
    }

    void Game::run()
    {
        while (window.isRunning())
        {
            profiler.beginFrame();
            window.pollEvents();

            double dt = timer.getDeltaTime();
            processInput(dt);
            update(dt);
            render();

            profiler.endFrame();
        }
    }

}
