#pragma once

#include <GL/glew.h>

#include "../defines.h"

struct IndexBuffer {
    void init(void* data, uint32 numIndices, uint8 elementSize) {
        GLCALL(glGenBuffers(1, &bufferId));
        GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferId));
        GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * elementSize, data, GL_STATIC_DRAW));
    }

    virtual ~IndexBuffer() {
        glDeleteBuffers(1, &bufferId);
    }

    void bind() {
        GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferId));
    }

    void unbind() {
        GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    }

private:
    GLuint bufferId;
};
