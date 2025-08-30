#include "Sprite.h"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>  // translate, rotate, scale
#include <glm/gtc/type_ptr.hpp>          // value_ptr


Sprite::Sprite(std::shared_ptr<Texture> texture, glm::vec2 position, glm::vec2 size)
    : texture(std::move(texture)), position(position), size(size) 
{
    float vertices[] = {
        // pos      // tex
        0.0f, 1.0f,  0.0f, 1.0f,
        1.0f, 0.0f,  1.0f, 0.0f,
        0.0f, 0.0f,  0.0f, 0.0f,

        0.0f, 1.0f,  0.0f, 1.0f,
        1.0f, 1.0f,  1.0f, 1.0f,
        1.0f, 0.0f,  1.0f, 0.0f
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Sprite::initRenderData() {
    // This function can be used to initialize or reset rendering data if needed
    float vertices[] = {
        // pos   // tex
        0.0f, 1.0f,  0.0f, 0.0f,
        1.0f, 0.0f,  1.0f, 1.0f,
        0.0f, 0.0f,  0.0f, 1.0f,

        0.0f, 1.0f,  0.0f, 0.0f,
        1.0f, 1.0f,  1.0f, 0.0f,
        1.0f, 0.0f,  1.0f, 1.0f
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}




void Sprite::draw(Shader& shader, const glm::mat4& projection) {
   shader.use();

    // Model matrix
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));
    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); // merkezden rotate
    model = glm::rotate(model, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));
    model = glm::scale(model, glm::vec3(size, 1.0f));

    glUniformMatrix4fv(glGetUniformLocation(shader.getID(), "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(glGetUniformLocation(shader.getID(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    if (texture) texture->bind();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void Sprite::setRotation(float angle) {
    rotation = angle;
}