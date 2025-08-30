#pragma once
#include <glad/glad.h>

class GLVertexArray {
public:
    GLVertexArray();
    ~GLVertexArray();

    // non-copyable
    GLVertexArray(const GLVertexArray&) = delete;
    GLVertexArray& operator=(const GLVertexArray&) = delete;

    // movable
    GLVertexArray(GLVertexArray&& other) noexcept;
    GLVertexArray& operator=(GLVertexArray&& other) noexcept;

    void bind() const;
    void unbind() const;
    GLuint get() const { return id; }
private:
    GLuint id = 0;
};

class GLBuffer {
public:
    GLBuffer();
    ~GLBuffer();

    GLBuffer(const GLBuffer&) = delete;
    GLBuffer& operator=(const GLBuffer&) = delete;

    GLBuffer(GLBuffer&& other) noexcept;
    GLBuffer& operator=(GLBuffer&& other) noexcept;

    void bind(GLenum target = GL_ARRAY_BUFFER) const;
    void unbind(GLenum target = GL_ARRAY_BUFFER) const;
    GLuint get() const { return id; }
private:
    GLuint id = 0;
};
