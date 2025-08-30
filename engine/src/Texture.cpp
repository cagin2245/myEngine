#define STB_IMAGE_IMPLEMENTATION
#include "Texture.h"
#include <stb_image.h>
#include <iostream>

Texture::Texture(const std::string& path) {

    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
    #ifdef ENGINE_DEV_MODE
    std::cout << "Texture load: " << path << " | w: " << width << ", h: " << height << ", ch: " << channels << ", data: " << (void*)data << std::endl;
    #endif
    if (!data) {
        #ifdef ENGINE_DEV_MODE
        std::cerr << "Failed to load texture: " << path << std::endl;
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
    std::cout << "Texture load: " << path << " | w: " << width << ", h: " << height << ", ch: " << channels << ", format: " << (format == GL_RGB ? "GL_RGB" : "GL_RGBA") << std::endl;
    #endif

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0,
                 format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
}

Texture::~Texture() {
    glDeleteTextures(1, &id);
}

void Texture::bind(unsigned int slot) const {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}
