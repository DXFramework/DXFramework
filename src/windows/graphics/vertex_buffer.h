#pragma once

#include <GL/glew.h>

#include "../defines.h"
#include <cstddef>

struct VertexBuffer {
    void init(void* data, uint32 numVertices) {
        GLCALL(glGenVertexArrays(1, &vao));
        GLCALL(glBindVertexArray(vao));

        GLCALL(glGenBuffers(1, &bufferId));
        GLCALL(glBindBuffer(GL_ARRAY_BUFFER, bufferId));
        GLCALL(glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(Vertex), data, GL_STATIC_DRAW));

        GLCALL(glEnableVertexAttribArray(0));
        GLCALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(struct Vertex, x)));

        GLCALL(glEnableVertexAttribArray(1));
        GLCALL(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(struct Vertex, r)));

        GLCALL(glBindVertexArray(0));
    }

    virtual ~VertexBuffer() {
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &bufferId);
    }

    void bind() {
        GLCALL(glBindVertexArray(vao));
    }

    void unbind() {
        GLCALL(glBindVertexArray(0));
    }

private:
    GLuint bufferId;
    GLuint vao;
};
