#include "GLUtils.h"
#include <glad/glad.h>

GLVertexArray::GLVertexArray() {
    glGenVertexArrays(1, &id);
}

GLVertexArray::~GLVertexArray() {
    if (id != 0) glDeleteVertexArrays(1, &id);
}

GLVertexArray::GLVertexArray(GLVertexArray&& other) noexcept
    : id(other.id)
{
    other.id = 0;
}

GLVertexArray& GLVertexArray::operator=(GLVertexArray&& other) noexcept {
    if (this != &other) {
        if (id != 0) glDeleteVertexArrays(1, &id);
        id = other.id;
        other.id = 0;
    }
    return *this;
}

void GLVertexArray::bind() const { glBindVertexArray(id); }
void GLVertexArray::unbind() const { glBindVertexArray(0); }

GLBuffer::GLBuffer() {
    glGenBuffers(1, &id);
}

GLBuffer::~GLBuffer() {
    if (id != 0) glDeleteBuffers(1, &id);
}

GLBuffer::GLBuffer(GLBuffer&& other) noexcept
    : id(other.id)
{
    other.id = 0;
}

GLBuffer& GLBuffer::operator=(GLBuffer&& other) noexcept {
    if (this != &other) {
        if (id != 0) glDeleteBuffers(1, &id);
        id = other.id;
        other.id = 0;
    }
    return *this;
}

void GLBuffer::bind(GLenum target) const { glBindBuffer(target, id); }
void GLBuffer::unbind(GLenum target) const { glBindBuffer(target, 0); }
