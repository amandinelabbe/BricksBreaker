//
// Created by amand on 14/12/2022.
//

#include "Menu.h"
#include "Briques.h"
#include <stdio.h>
#include <SDL.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>
#include <stdbool.h>
#include <SDL_ttf.h>
#include <SDL_image.h>


struct keyPressed{
    bool up;
    bool down;
    bool enter;
};

int nr_min = 1;
int nr_max = 2000;

void windowMenu(SDL_Renderer *renderer) {
    SDL_bool quit = false;
    SDL_Event event;
    int lastTimer = SDL_GetTicks();
    int intervalle = 15;
    struct keyPressed myKeyPressed = {false, false, false};

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
                break;
            }

            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_UP) {
                    myKeyPressed.up = true;
                }
                if (event.key.keysym.sym == SDLK_DOWN) {
                    myKeyPressed.down = true;
                }
                if (event.key.keysym.sym == SDLK_SPACE) {
                    myKeyPressed.enter = true;
                }
            }

            if (event.type == SDL_KEYUP) {
                if (event.key.keysym.sym == SDLK_UP) {
                    myKeyPressed.up = false;
                }
                if (event.key.keysym.sym == SDLK_DOWN) {
                    myKeyPressed.down = false;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        draw_random_points(2000, randomNumber(nr_min, nr_max), renderer);

        SDL_Surface *tmp = NULL;
        SDL_Texture *texture = NULL;

        tmp = IMG_Load("C:\\Users\\amand\\CLionProjects\\CasseBriques\\logoProjet.png");
        if(NULL == tmp){
            fprintf(stderr, "Erreur SDL_LoadBMP : %s", SDL_GetError());
        }

        texture = SDL_CreateTextureFromSurface(renderer, tmp);
        SDL_FreeSurface(tmp);

        SDL_Rect Image_rect;
        Image_rect.x = 500;
        Image_rect.y = 60;
        Image_rect.w = 200;
        Image_rect.h = 200;
        SDL_RenderCopy(renderer, texture, NULL, &Image_rect);

        if(NULL == texture){
            fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());

        }

        if(TTF_Init() == -1){
            fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
            exit(EXIT_FAILURE);
        }


        TTF_Font* Arial = TTF_OpenFont("arial.ttf", 24);
        TTF_Font* Fast = TTF_OpenFont("fast99.ttf", 50);

        SDL_Color White = {255, 255, 255};
        SDL_Color Yellow = {255, 255, 0};
        SDL_Color Blue = {55, 0, 200};

        SDL_Surface* title = TTF_RenderText_Solid(Fast, "Brick Breakers", White);
        SDL_Texture* TitleMessage = SDL_CreateTextureFromSurface(renderer, title);
        SDL_Rect Title_rect;
        Title_rect.x = 340;
        Title_rect.y = 280;
        Title_rect.w = 500;
        Title_rect.h = 100;
        SDL_RenderCopy(renderer, TitleMessage, NULL, &Title_rect);

        SDL_Surface* startMessage = TTF_RenderText_Solid(Arial, "Start", White);
        SDL_Texture* StartMessage = SDL_CreateTextureFromSurface(renderer, startMessage);
        SDL_Rect Start_rect;
        Start_rect.x = 500;
        Start_rect.y = 480;
        Start_rect.w = 175;
        Start_rect.h = 70;
        SDL_RenderCopy(renderer, StartMessage, NULL, &Start_rect);


        SDL_Surface* quitMessage = TTF_RenderText_Solid(Arial, "Quit", White);
        SDL_Texture* QuitMessage = SDL_CreateTextureFromSurface(renderer, quitMessage);
        SDL_Rect Quit_rect;
        Quit_rect.x = 510;
        Quit_rect.y = 550;
        Quit_rect.w = 150;
        Quit_rect.h = 70;
        SDL_RenderCopy(renderer, QuitMessage, NULL, &Quit_rect);

        SDL_FreeSurface(title);
        SDL_FreeSurface(startMessage);
        SDL_FreeSurface(quitMessage);

        //SDL_DestroyTexture(Message);


        if (myKeyPressed.down) {
            SDL_Surface* quitMessage = TTF_RenderText_Solid(Arial, "Quit", Blue);
            SDL_Texture* QuitMessage = SDL_CreateTextureFromSurface(renderer, quitMessage);
            SDL_RenderCopy(renderer, QuitMessage, NULL, &Quit_rect);
        }
        if (myKeyPressed.up) {
            SDL_Surface* startMessage = TTF_RenderText_Solid(Arial, "Start", Blue);
            SDL_Texture* StartMessage = SDL_CreateTextureFromSurface(renderer, startMessage);
            SDL_RenderCopy(renderer, StartMessage, NULL, &Start_rect);
        }

        if (SDL_GetTicks() - lastTimer > intervalle) {
            if (myKeyPressed.up && myKeyPressed.enter) {
                rulesMenu(renderer);
            } else if (myKeyPressed.down && myKeyPressed.enter) {
                quit = true;
            }
        }
        SDL_RenderPresent(renderer);
    }
}

void rulesMenu(SDL_Renderer *renderer) {
    SDL_bool quit = false;
    SDL_Event event;
    int lastTimer = SDL_GetTicks();
    int intervalle = 15;
    struct keyPressed myKeyPressed = {false, false, false, false};

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
                break;
            }
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_SPACE) {
                    myKeyPressed.enter = true;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        draw_random_points(2000, randomNumber(nr_min, nr_max), renderer);

        if(TTF_Init() == -1){
            fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
            exit(EXIT_FAILURE);
        }

        TTF_Font* Arial = TTF_OpenFont("arial.ttf", 18);
        TTF_Font* Fast = TTF_OpenFont("fast99.ttf", 50);
        SDL_Color White = {255, 255, 255};
        SDL_Color Multi = {rand()%255, rand()%255, rand()%255};

        char str[5];
        char *desc = "Description : casse briques avec des niveaux infinis";
        sprintf(str, "%c",*desc);
        SDL_Surface* descMessage = TTF_RenderText_Solid(Arial, desc, White);
        SDL_Texture* DescMessage = SDL_CreateTextureFromSurface(renderer, descMessage);
        SDL_Rect desc_rect;
        desc_rect.x = 30;
        desc_rect.y = 180;
        desc_rect.w = 700;
        desc_rect.h = 50;
        SDL_RenderCopy(renderer, DescMessage, NULL, &desc_rect);

        char *obj = "Objectif : atteindre le plus haut niveau";
        sprintf(str, "%c",*obj);
        SDL_Surface* objMessage = TTF_RenderText_Solid(Arial, obj, White);
        SDL_Texture* ObjMessage = SDL_CreateTextureFromSurface(renderer, objMessage);
        SDL_Rect obj_rect;
        obj_rect.x = 30;
        obj_rect.y = 270;
        obj_rect.w = 500;
        obj_rect.h = 45;
        SDL_RenderCopy(renderer, ObjMessage, NULL, &obj_rect);

        char *vie = "Vies : vous avez 5 vies par niveau, si vous les perdez vous redemarrez au premier niveau";
        sprintf(str, "%c",*vie);
        SDL_Surface* vieMessage = TTF_RenderText_Solid(Arial, vie, White);
        SDL_Texture* VieMessage = SDL_CreateTextureFromSurface(renderer, vieMessage);
        SDL_Rect vie_rect;
        vie_rect.x = 30;
        vie_rect.y = 355;
        vie_rect.w = 1100;
        vie_rect.h = 50;
        SDL_RenderCopy(renderer, VieMessage, NULL, &vie_rect);

        char *diff = "Difficulte : a chaque niveau passe, la vitesse de la balle s'accelere "
                     "et la taille des briques";
        sprintf(str, "%c",*diff);
        SDL_Surface* diffMessage = TTF_RenderText_Solid(Arial, diff, White);
        SDL_Texture* DiffMessage = SDL_CreateTextureFromSurface(renderer, diffMessage);
        SDL_Rect diff_rect;
        diff_rect.x = 30;
        diff_rect.y = 450;
        diff_rect.w = 1100;
        diff_rect.h = 50;
        SDL_RenderCopy(renderer, DiffMessage, NULL, &diff_rect);

        char *diff2 = "retrecies, la vitesse et la taille de la plateforme ne change pas";
        sprintf(str, "%c",*diff);
        SDL_Surface* diff2Message = TTF_RenderText_Solid(Arial, diff2, White);
        SDL_Texture* Diff2Message = SDL_CreateTextureFromSurface(renderer, diff2Message);
        SDL_Rect diff2_rect;
        diff2_rect.x = 160;
        diff2_rect.y = 500;
        diff2_rect.w = 900;
        diff2_rect.h = 50;
        SDL_RenderCopy(renderer, Diff2Message, NULL, &diff2_rect);

        SDL_Surface* rules = TTF_RenderText_Solid(Fast, "REGLE DU JEU", White);
        SDL_Texture* Rules= SDL_CreateTextureFromSurface(renderer, rules);
        SDL_Rect rules_rect;
        rules_rect.x = 460;
        rules_rect.y = 30;
        rules_rect.w = 250;
        rules_rect.h = 70;
        SDL_RenderCopy(renderer, Rules, NULL, &rules_rect);

        SDL_Surface* press = TTF_RenderText_Solid(Arial, "Appuyez sur la touche 'espace' pour jouer", Multi);
        SDL_Texture* Press = SDL_CreateTextureFromSurface(renderer, press);
        SDL_Rect press_rect;
        press_rect.x = 250;
        press_rect.y = 680;
        press_rect.w = 700;
        press_rect.h = 80;
        SDL_RenderCopy(renderer, Press, NULL, &press_rect);

        SDL_FreeSurface(descMessage);
        SDL_FreeSurface(objMessage);
        SDL_FreeSurface(vieMessage);
        SDL_FreeSurface(diffMessage);
        SDL_FreeSurface(rules);
        SDL_FreeSurface(press);

        if (SDL_GetTicks() - lastTimer > intervalle) {
            if (myKeyPressed.enter) {
                gameloop(renderer, 1, 6, 6, 60, 110, 25, 25);
            }
        }
        SDL_RenderPresent(renderer);
    }
}

void restartMenu(SDL_Renderer *renderer) {
    SDL_bool quit = false;
    SDL_Event event;
    int lastTimer = SDL_GetTicks();
    int intervalle = 15;
    struct keyPressed myKeyPressed = {false, false, false, false};

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
                break;
            }

            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_UP) {
                    myKeyPressed.up = true;
                }
                if (event.key.keysym.sym == SDLK_DOWN) {
                    myKeyPressed.down = true;
                }
                if (event.key.keysym.sym == SDLK_SPACE) {
                    myKeyPressed.enter = true;
                }
            }

            if (event.type == SDL_KEYUP) {
                if (event.key.keysym.sym == SDLK_UP) {
                    myKeyPressed.up = false;
                }
                if (event.key.keysym.sym == SDLK_DOWN) {
                    myKeyPressed.down = false;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        draw_random_points(2000, randomNumber(nr_min, nr_max), renderer);

        if(TTF_Init() == -1){
            fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
            exit(EXIT_FAILURE);
        }

        TTF_Font* Arial = TTF_OpenFont("arial.ttf", 24);
        TTF_Font* Fast = TTF_OpenFont("fast99.ttf", 50);

        SDL_Color White = {255, 255, 255};
        SDL_Color Blue = {55, 0, 200};

        SDL_Surface* restartMessage = TTF_RenderText_Solid(Fast, "Dommage vous avez perdu ! Souhaitez vous recommencer ?", White);
        SDL_Texture* RestartMessage = SDL_CreateTextureFromSurface(renderer, restartMessage);
        SDL_Rect restart_rect;
        restart_rect.x = 120;
        restart_rect.y = 100;
        restart_rect.w = 1000;
        restart_rect.h = 50;
        SDL_RenderCopy(renderer, RestartMessage, NULL, &restart_rect);


        SDL_Surface* restart = TTF_RenderText_Solid(Arial, "Restart", White);
        SDL_Texture* Restart= SDL_CreateTextureFromSurface(renderer, restart);
        SDL_Rect Start_rect;
        Start_rect.x = 460;
        Start_rect.y = 390;
        Start_rect.w = 250;
        Start_rect.h = 70;
        SDL_RenderCopy(renderer, Restart, NULL, &Start_rect);


        SDL_Surface* quitMessage = TTF_RenderText_Solid(Arial, "Quit", White);
        SDL_Texture* QuitMessage = SDL_CreateTextureFromSurface(renderer, quitMessage);
        SDL_Rect Quit_rect;
        Quit_rect.x = 500;
        Quit_rect.y = 490;
        Quit_rect.w = 150;
        Quit_rect.h = 70;
        SDL_RenderCopy(renderer, QuitMessage, NULL, &Quit_rect);

        SDL_FreeSurface(restartMessage);
        SDL_FreeSurface(restart);
        SDL_FreeSurface(quitMessage);


        if (myKeyPressed.down) {
            SDL_Surface* quitMessage = TTF_RenderText_Solid(Arial, "Quit", Blue);
            SDL_Texture* QuitMessage = SDL_CreateTextureFromSurface(renderer, quitMessage);
            SDL_RenderCopy(renderer, QuitMessage, NULL, &Quit_rect);
        }
        if (myKeyPressed.up) {
            SDL_Surface* restart = TTF_RenderText_Solid(Arial, "Restart", Blue);
            SDL_Texture* Restart = SDL_CreateTextureFromSurface(renderer, restart);
            SDL_RenderCopy(renderer, Restart, NULL, &Start_rect);
        }

        if (SDL_GetTicks() - lastTimer > intervalle) {
            if (myKeyPressed.up && myKeyPressed.enter) {
                gameloop(renderer, 1, 6, 6, 60, 110, 25, 25);
            } else if (myKeyPressed.down && myKeyPressed.enter) {
                quit = true;
            }
        }
        SDL_RenderPresent(renderer);
    }
}


