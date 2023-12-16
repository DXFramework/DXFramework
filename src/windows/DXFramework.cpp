#define GLEW_STATIC
#include <GL/glew.h>
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <iostream>

typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef float float32;
typedef double float64;

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

        glBegin(GL_TRIANGLES);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(0.0f, 0.5f);
        glVertex2f(0.5f, -0.5f);
        glEnd();

        SDL_GL_SwapWindow(window);
    }

    SDL_Quit();

    return 0;
}