#pragma once
#include "Texture.h"
#include "Shader.h"
#include <glm/glm.hpp>
#include  <memory>
#include "GLUtils.h"

class Sprite
{
public:
    Sprite(std::shared_ptr<Texture> texture, glm::vec2 position, glm::vec2 size);
    void draw(Shader &shader, const glm::mat4 &projection);

    void setPosition(const glm::vec2 &pos) { position = pos; }
    void setSize(const glm::vec2 &s) { size = s; }
    void setRotation(float angle);
    void setTexture(std::shared_ptr<Texture> tex) { texture = tex; }
    void setColor(const glm::vec4 &color) { /* Implement color modulation if needed */ }
    void setTexCoords(const glm::vec4 &coords) { /* Implement texture coordinate adjustment if needed */ }
    void setFlip(bool flipX, bool flipY) { /* Implement flipping if needed */ }
    void setAlpha(float alpha) { /* Implement alpha blending if needed */ }
    void setLayer(int layer) { /* Implement layering if needed */ }
    void setVisible(bool visible) { /* Implement visibility if needed */ }
    void setAnchorPoint(const glm::vec2 &anchor) { /* Implement anchor point if needed */ }
    void setTiling(const glm::vec2 &tiling) { /* Implement texture tiling if needed */ }
    void setOffset(const glm::vec2 &offset) { /* Implement texture offset if needed */ }
    void setWrapMode(int mode) { /* Implement wrap mode if needed */ }
    void setFilterMode(int mode) { /* Implement filter mode if needed */ }
    void setMipmaps(bool mipmaps) { /* Implement mipmap generation if needed */ }

    glm::vec2 getPosition() const { return position; }
    glm::vec2 getSize() const { return size; }
    float getRotation() const { return 0.0f; /* Implement if needed */ }
    std::shared_ptr<Texture> getTexture() const { return texture.lock(); }
    glm::vec4 getColor() const { return glm::vec4(1.0f); /* Implement if needed */ }
    glm::vec4 getTexCoords() const { return glm::vec4(0.0f); /* Implement if needed */ }
    bool isVisible() const { return true; /* Implement if needed */ }
    glm::vec4 getAABB() const
    {
        return glm::vec4(position.x, position.y, size.x, size.y);
        // x, y, w, h
        }
    private:
    std::weak_ptr<Texture> texture;
        glm::vec2 position;
        glm::vec2 size;
        
    GLVertexArray VAO;
    GLBuffer VBO;
        float rotation = 0.0f;
        

        void initRenderData();
    };
