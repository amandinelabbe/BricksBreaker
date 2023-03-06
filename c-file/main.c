#include <stdio.h>
#include <SDL.h>
#include <stdlib.h>
#include <time.h>
#include <SDL_mixer.h>
#include <SDL_audio.h>
#include <SDL_events.h>
#include "Briques.h"
#include "Menu.h"
#include "UserInput.h"

struct keyPressed{
    bool up;
    bool down;
    bool enter;
};

int WinMain(int argc, char *args[]) {
    srand(time(NULL));
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_bool quit = false;
    SDL_Event event;
    struct keyPressed myKeyPressed = {false, false, false, false};

    if(0 != SDL_Init(SDL_INIT_VIDEO))
    {
        fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
        return EXIT_FAILURE;
    }
    window = SDL_CreateWindow("SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              1200, 800, SDL_WINDOW_SHOWN );
    if(NULL == window)
    {
        fprintf(stderr, "Erreur SDL_CreateWindow : %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(NULL == renderer)
    {
        fprintf(stderr, "Erreur SDL_CreateRenderer : %s", SDL_GetError());
        return EXIT_FAILURE;
    }
    while(SDL_PollEvent(&event)){
        if(event.type == SDL_QUIT){
            quit = true;
            break;
        }
        else {

        }
    }

    windowMenu(renderer);
    //gameloop(renderer, 1, 6, 6, 60, 110, 25, 25);


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}
