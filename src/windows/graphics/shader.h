#pragma once

#include <gl/glew.h>
#include <string>

#include "../defines.h"

struct Shader {
    void init(const char* vertexShaderFilename, const char* fragmentShaderFilename);
    virtual ~Shader();

    void bind();
    void unbind();

private:
    GLuint compile(std::string shaderSource, GLenum type);
    std::string parse(const char* filename);
    GLuint createShader(const char* vertexShaderFilename, const char* fragmentShaderFilename);

    GLuint shaderId;
};