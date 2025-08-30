#pragma once
#include <glad/glad.h>
#include "Shader.h"
#include "GLUtils.h"

class Renderer {
public:
    Renderer();
    ~Renderer();

    void draw(const Shader& shader);

private:
    GLVertexArray VAO;
    GLBuffer VBO;
};
