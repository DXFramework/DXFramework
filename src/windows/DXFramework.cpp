#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <iostream>

int main() {
    if(SDL_Init(SDL_INIT_VIDEO) != 0) {
        return -1;
    }
    
    SDL_Window* window = SDL_CreateWindow("DXFramework", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1240, 720, SDL_WINDOW_OPENGL);
    SDL_GLContext glContext = SDL_GL_CreateContext(window);

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
    }

    SDL_Quit();

    return 0;
}