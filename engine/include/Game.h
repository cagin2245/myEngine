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

namespace Engine {

class Game {
public:
    Game(int width, int height);
    void run();

private:
    int width, height;
    Window window;
    std::shared_ptr<Shader> shader;
    std::shared_ptr<Texture> playerTexture;
    std::shared_ptr<Texture> enemyTexture;
    std::shared_ptr<Sprite> player;
    std::shared_ptr<Sprite> enemy;
    glm::mat4 projection;
    Timer timer;
    Input input;

    glm::vec2 lastPlayerPos; // Önceki pozisyonu sakla
    float speed = 300.0f;    // Hareket hızı (piksel

    void processInput(double dt);
    void update(double dt);
    void render();
};

} // namespace Engine
