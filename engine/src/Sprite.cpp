#include "Sprite.h"
#include "Core/Logger.h"
#include <glm/gtc/matrix_transform.hpp>  // translate, rotate, scale
#include <glm/gtc/type_ptr.hpp>          // value_ptr
#include <iostream>


Sprite::Sprite(std::shared_ptr<Texture> texture, glm::vec2 position, glm::vec2 size)
    : texture(texture), position(position), size(size) 
{
    float vertices[] = {
        // pos         // tex
        0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
        0.0f, 0.0f, 0.0f,  0.0f, 1.0f,

        0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
        1.0f, 1.0f, 0.0f,  1.0f, 0.0f,
        1.0f, 0.0f, 0.0f,  1.0f, 1.0f
    };

    VAO.bind();
    VBO.bind(GL_ARRAY_BUFFER);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    VBO.unbind(GL_ARRAY_BUFFER);
    VAO.unbind();
}

void Sprite::initRenderData() {
    // 3D pozisyon + 2D texcoord, 5 float stride
    float vertices[] = {
        // pos         // tex
        0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
        1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
        0.0f, 0.0f, 0.0f,  0.0f, 0.0f,

        0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
        1.0f, 1.0f, 0.0f,  1.0f, 1.0f,
        1.0f, 0.0f, 0.0f,  1.0f, 0.0f
    };

    VAO.bind();
    VBO.bind(GL_ARRAY_BUFFER);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    VBO.unbind(GL_ARRAY_BUFFER);
    VAO.unbind();
}




void Sprite::draw(Shader& shader, const glm::mat4& projection) {
    // Null kontrolü: weak_ptr'i lock et
    auto tex = texture.lock();
    if (!tex) {
        Engine::Logger::log("[Sprite::draw] Texture pointer null!", Engine::LogLevel::Error);
        return;
    }
    shader.use();

    // Model matrix
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));
    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); // merkezden rotate
    model = glm::rotate(model, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));
    model = glm::scale(model, glm::vec3(size, 1.0f));


    glUniformMatrix4fv(glGetUniformLocation(shader.getID(), "model"), 1, GL_FALSE, glm::value_ptr(model));
    // view uniformunu kimlik matrisi olarak ayarla
    glm::mat4 view = glm::mat4(1.0f);
    glUniformMatrix4fv(glGetUniformLocation(shader.getID(), "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shader.getID(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    tex->bind();
    // Texture uniformunu ayarla
    glUniform1i(glGetUniformLocation(shader.getID(), "image"), 0);
    VAO.bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);
    VAO.unbind();
}

void Sprite::setRotation(float angle) {
    rotation = angle;
}