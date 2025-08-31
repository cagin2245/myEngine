// Single-file stb_image implementation
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Texture.h"
#include "Core/Logger.h"
#include <iostream>

namespace Engine {

Texture::Texture(const std::string& path) {

    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
#ifdef ENGINE_DEV_MODE
    Logger::log(std::string("Texture load: ") + path + " | w: " + std::to_string(width) + ", h: " + std::to_string(height) + ", ch: " + std::to_string(channels), LogLevel::Debug);
#endif
    if (!data) {
#ifdef ENGINE_DEV_MODE
        Logger::log(std::string("Failed to load texture: ") + path, LogLevel::Error);
#endif
        id = 0;
        return;
    }

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    GLenum format = GL_RGB;
    if (channels == 4) format = GL_RGBA;
#ifdef ENGINE_DEV_MODE
    Logger::log(std::string("Texture load: ") + path + " | w: " + std::to_string(width) + ", h: " + std::to_string(height) + ", ch: " + std::to_string(channels) + ", format: " + (format == GL_RGB ? "GL_RGB" : "GL_RGBA"), LogLevel::Debug);
#endif

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0,
                 format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
}

Texture::~Texture() {
    if (id != 0) glDeleteTextures(1, &id);
}

void Texture::bind(unsigned int slot) const {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::Texture(Texture&& other) noexcept
    : id(other.id), width(other.width), height(other.height), channels(other.channels)
{
    other.id = 0;
    other.width = other.height = other.channels = 0;
}

Texture& Texture::operator=(Texture&& other) noexcept {
    if (this != &other) {
        if (id != 0) glDeleteTextures(1, &id);
        id = other.id;
        width = other.width; height = other.height; channels = other.channels;
        other.id = 0;
        other.width = other.height = other.channels = 0;
    }
    return *this;
}

} // namespace Engine
