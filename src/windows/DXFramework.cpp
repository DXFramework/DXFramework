#define GLEW_STATIC
#include <GL/glew.h>
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <iostream>

#include "defines.h"
#include "graphics/vertex_buffer.h"
#include "graphics/shader.h"
#include "graphics/index_buffer.h"

void openGLDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
    std::cout << "[OpenGL Error] " << message << std::endl;
}

int main() {
    if(SDL_Init(SDL_INIT_VIDEO) != 0) {
        return -1;
    }

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    #ifdef _DEBUG
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
    #endif
    
    uint32 flags = SDL_WINDOW_OPENGL;

    SDL_Window* window = SDL_CreateWindow("DXFramework", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1240, 720, flags);
    SDL_GLContext glContext = SDL_GL_CreateContext(window);

    GLenum err = glewInit();
    if(err != GLEW_OK) {
        std::cout << "Error: " << glewGetErrorString(err) << std::endl;
        std::cin.get();
        return -1; 
    }
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    #ifdef _DEBUG
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(openGLDebugCallback, 0);
    #endif

    Vertex vertices[] = {
        Vertex{-0.5f, -0.5f, 0.0f,
        1.0f, 0.0f, 0.0f, 1.0f},
        Vertex{-0.5f, 0.5f, 0.0f,
        0.0f, 1.0f, 0.0f, 1.0f},
        Vertex{0.5f, -0.5f, 0.0f,
        0.0f, 0.0f, 1.0f, 1.0f},
        Vertex{0.5f, 0.5f, 0.0f,
        1.0f, 0.0f, 0.0f, 1.0f}
    };
    uint32 numVertices = 4;

    uint32 indices[] = {
        0, 1, 2,
        1, 2, 3
    };
    uint32 numIndices = 6;

    IndexBuffer indexBuffer;
    indexBuffer.init(indices, numIndices, sizeof(indices[0]));

    VertexBuffer vertexBuffer;
    vertexBuffer.init(vertices, numVertices);

    Shader shader;
    shader.init("shaders/basic.vs", "shaders/basic.fs");
    shader.bind();

    uint64 perfCounterFrequency = SDL_GetPerformanceFrequency();
    uint64 lastCounter = SDL_GetPerformanceCounter();
    float32 delta = 0.0f;

    //Wireframe
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    bool close = false;
    while(!close) {
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_QUIT: {
                    close = true;
                    break;
                }
            }
        }

        GLCALL(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
        GLCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

        vertexBuffer.bind();
        indexBuffer.bind();
        GLCALL(glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0));
        indexBuffer.unbind();
        vertexBuffer.unbind();

        SDL_GL_SwapWindow(window);

        uint64 endCounter = SDL_GetPerformanceCounter();
        uint64 counterElapsed = endCounter - lastCounter;
        delta = ((float32)counterElapsed) / (float32)perfCounterFrequency;
        uint32 FPS = (uint32)((float32)perfCounterFrequency / (float32)counterElapsed);
        lastCounter = endCounter;
    }

    SDL_Quit();

    return 0;
}