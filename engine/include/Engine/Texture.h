#pragma once
#include <string>
#include <glad/glad.h>

namespace Engine {
class Texture {
public:
    Texture(const std::string& path);
    ~Texture();

    // Non-copyable, moveable
    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;
    Texture(Texture&& other) noexcept;
    Texture& operator=(Texture&& other) noexcept;

    void bind(unsigned int slot = 0) const;
    void unbind() const;

    inline int getWidth() const { return width; }
    inline int getHeight() const { return height; }

private:
    GLuint id;
    int width, height, channels;
};
}