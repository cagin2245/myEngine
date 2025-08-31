#include "Renderer.h"

namespace Engine {

Renderer::Renderer() {
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    VAO.bind();

    VBO.bind(GL_ARRAY_BUFFER);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(0);

    VBO.unbind(GL_ARRAY_BUFFER);
    VAO.unbind();
}

Renderer::~Renderer() {
    // RAII will clean up
}

void Renderer::draw(const Shader& shader) {
    shader.use();
    VAO.bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

} // namespace Engine
