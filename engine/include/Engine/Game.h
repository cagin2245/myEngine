#pragma once
#include "Window.h"
#include "Shader.h"
#include "Texture.h"
#include "Sprite.h"
#include "Collision.h"
#include "Timer.h"
#include "Input.h"
#include <glm/glm.hpp>
#include <memory>

#ifdef ENGINE_DEV_MODE
#include "Core/ProfilerOverlay.h"
#include "Core/TextRenderer.h"
#endif

namespace Engine
{

    class Game
    {
    public:
        Game(int width, int height);
        void run();

    private:
        int width, height;
        Window window;
        std::shared_ptr<Shader> shader;
        std::shared_ptr<Texture> playerTexture;
        std::shared_ptr<Texture> enemyTexture;
        std::unique_ptr<Sprite> player;
    std::unique_ptr<Sprite> enemy;
    glm::mat4 projection;
        Timer timer;
    Input input;

    glm::vec2 lastPlayerPos;
        float speed = 300.0f;

        void processInput(double dt);
        void update(double dt);
        void render();

    #ifdef ENGINE_DEV_MODE
            Profiler profiler;
            std::shared_ptr<TextRenderer> textRenderer;
            std::unique_ptr<ProfilerOverlay> profilerOverlay;
    #endif
    };

}
