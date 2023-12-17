#include "shader.h"

#include <fstream>
#include <iostream>

void Shader::init(const char* vertexShaderFilename, const char* fragmentShaderFilename) {
    shaderId = createShader(vertexShaderFilename, fragmentShaderFilename);
}

Shader::~Shader() {
    glDeleteProgram(shaderId);
}

void Shader::bind() {
    GLCALL(glUseProgram(shaderId));
}

void Shader::unbind() {
    GLCALL(glUseProgram(0));
}

GLuint Shader::compile(std::string shaderSource, GLenum type) {
    GLuint id = GLCALL(glCreateShader(type));
    const char* src = shaderSource.c_str();
    GLCALL(glShaderSource(id, 1, &src, 0));
    GLCALL(glCompileShader(id));

    int result;
    GLCALL(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if(result != GL_TRUE) {
        int length = 0;
        GLCALL(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char* message = new char[length];
        GLCALL(glGetShaderInfoLog(id, length, &length, message));
        std::cout << "Shader compilation error: " << message << std::endl;
        delete[] message;
        return 0;
    }
    return id;
}

std::string Shader::parse(const char* filename) {
    FILE* file;

	if (fopen_s(&file, filename, "rb") != 0) {
		std::cout << "File " << filename << " not found" << std::endl;
		return "";
	}

    std::string contents;
    fseek(file, 0, SEEK_END);
    size_t filesize = ftell(file);
    rewind(file);
    contents.resize(filesize);

    fread(&contents[0], 1, filesize, file);
    fclose(file);

    return contents;
}

GLuint Shader::createShader(const char* vertexShaderFilename, const char* fragmentShaderFilename) {
    std::string vertexShaderSource = parse(vertexShaderFilename);
    std::string fragmentShaderSource = parse(fragmentShaderFilename);

    GLuint program = GLCALL(glCreateProgram());
    GLuint vs = compile(vertexShaderSource, GL_VERTEX_SHADER);
    GLuint fs = compile(fragmentShaderSource, GL_FRAGMENT_SHADER);

    GLCALL(glAttachShader(program, vs));
    GLCALL(glAttachShader(program, fs));
    GLCALL(glLinkProgram(program));

    #ifdef _RELEASE
    GLCALL(glDetachShader(program, vs));
    GLCALL(glDetachShader(program, fs));

    GLCALL(glDeleteShader(vs));
    GLCALL(glDeleteShader(fs));
    #endif

    return program;
}