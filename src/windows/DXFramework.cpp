#define GLEW_STATIC
#include <GL/glew.h>
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <iostream>

#include "defines.h"
#include "graphics/vertex_buffer.h"
#include "graphics/shader.h"

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
    
    SDL_Window* window = SDL_CreateWindow("DXFramework", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1240, 720, SDL_WINDOW_OPENGL);
    SDL_GLContext glContext = SDL_GL_CreateContext(window);

    GLenum err = glewInit();
    if(err != GLEW_OK) {
        std::cout << "Error: " << glewGetErrorString(err) << std::endl;
        std::cin.get();
        return -1; 
    }
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    Vertex vertices[] = {
        Vertex{-0.5f, -0.5f, 0.0f},
        Vertex{0.0f, 0.5f, 0.0f},
        Vertex{0.5f, -0.5f, 0.0f},
    };
    uint32 numVertices = 3;

    VertexBuffer vertexBuffer;
    vertexBuffer.init(vertices, numVertices);

    Shader shader;
    shader.init("shaders/basic.vs", "shaders/basic.fs");
    shader.bind();

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

        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        vertexBuffer.bind();
        glDrawArrays(GL_TRIANGLES, 0, numVertices);
        vertexBuffer.unbind();

        SDL_GL_SwapWindow(window);
    }

    SDL_Quit();

    return 0;
}