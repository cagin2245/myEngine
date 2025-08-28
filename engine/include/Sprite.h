#pragma once
#include "Texture.h"
#include "Shader.h"
#include <glm/glm.hpp>

class Sprite {
public:
    Sprite(Texture* texture, glm::vec2 position, glm::vec2 size);
    void draw(const Shader& shader);

private:
    Texture* texture;
    glm::vec2 position;
    glm::vec2 size;
    GLuint VAO, VBO;
};
