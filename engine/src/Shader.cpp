#include "Shader.h"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Core/Logger.h"

namespace Engine {

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
    std::string vCode = loadSource(vertexPath);
    std::string fCode = loadSource(fragmentPath);

    GLuint vShader = compileShader(GL_VERTEX_SHADER, vCode);
    GLuint fShader = compileShader(GL_FRAGMENT_SHADER, fCode);

    ID = glCreateProgram();
    glAttachShader(ID, vShader);
    glAttachShader(ID, fShader);
    glLinkProgram(ID);

    int success;
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(ID, 512, nullptr, infoLog);
#ifdef ENGINE_DEV_MODE
        Logger::log(std::string("Shader link error:\n") + infoLog, LogLevel::Error);
#endif
    }

    glDeleteShader(vShader);
    glDeleteShader(fShader);
}

Shader::~Shader() {
    if (ID != 0) glDeleteProgram(ID);
}

Shader::Shader(Shader&& other) noexcept
    : ID(other.ID)
{
    other.ID = 0;
}

Shader& Shader::operator=(Shader&& other) noexcept {
    if (this != &other) {
        if (ID != 0) glDeleteProgram(ID);
        ID = other.ID;
        other.ID = 0;
    }
    return *this;
}

void Shader::use() const {
    glUseProgram(ID);
}

std::string Shader::loadSource(const std::string& path) {
    std::ifstream file(path);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

GLuint Shader::compileShader(GLenum type, const std::string& source) {
    GLuint shader = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
#ifdef ENGINE_DEV_MODE
        Logger::log(std::string("Shader compile error:\n") + infoLog, LogLevel::Error);
#endif
    }
    return shader;
}

// --- Uniform helpers ---
void Shader::setMat4(const std::string& name, const glm::mat4& mat) const {
    GLint loc = glGetUniformLocation(ID, name.c_str());
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::setVec3(const std::string& name, const glm::vec3& value) const {
    GLint loc = glGetUniformLocation(ID, name.c_str());
    glUniform3fv(loc, 1, glm::value_ptr(value));
}

} // namespace Engine
