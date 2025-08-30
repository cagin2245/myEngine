#pragma once
#include <glad/glad.h>
#include "Shader.h"

class Renderer {
public:
    Renderer();
    ~Renderer();

    void draw(const Shader& shader);

private:
    GLuint VAO, VBO;
};
