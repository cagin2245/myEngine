#pragma once
#include <map>
#include <string>
#include <glm/glm.hpp>
#include "Shader.h"
#include <ft2build.h>
#include FT_FREETYPE_H

struct Character {
    unsigned int TextureID; // glyph texture
    glm::ivec2 Size;        // glyph size
    glm::ivec2 Bearing;     // offset from baseline
    unsigned int Advance;   // next glyph offset
};

namespace Engine {

class TextRenderer {
public:
    TextRenderer(unsigned int width, unsigned int height);
    void load(const std::string& fontPath, unsigned int fontSize);
    void renderText(const std::string& text, float x, float y, float scale, glm::vec3 color);

private:
    std::map<char, Character> Characters;
    unsigned int VAO, VBO;
    Shader shader;
};

} // namespace Engine
