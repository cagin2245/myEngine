#pragma once
#include <glad/glad.h>
#include <string>

class Shader {
public:
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();

    void use() const;
    GLuint getID() const { return ID; }
    

private:
    GLuint ID;
    std::string loadSource(const std::string& path);
    GLuint compileShader(GLenum type, const std::string& source);
};
