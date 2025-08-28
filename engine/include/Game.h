#pragma once
#include "Window.h"
#include "Shader.h"
#include "Texture.h"
#include "Sprite.h"
#include "Timer.h"
#include "Input.h"

class Game {
public:
    Game(int width, int height);
    void run();

private:
    int width, height;
    Window window;
    Shader shader;
    Texture texture;
    Sprite sprite;
    glm::mat4 projection;
    Timer timer;
    Input input;
};
