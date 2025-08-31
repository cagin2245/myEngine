#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>

namespace Engine {
class Shader {
public:
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();

    // Non-copyable, moveable
    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;
    Shader(Shader&& other) noexcept;
    Shader& operator=(Shader&& other) noexcept;

    void use() const;
    GLuint getID() const { return ID; }

    // Uniform helpers
    void setMat4(const std::string& name, const glm::mat4& mat) const;
    void setVec3(const std::string& name, const glm::vec3& value) const;

private:
    GLuint ID;
    std::string loadSource(const std::string& path);
    GLuint compileShader(GLenum type, const std::string& source);
};
}