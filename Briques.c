//
// Created by amand on 12/12/2022.
//

#include "Briques.h"
#include "UserInput.h"
#include <stdio.h>
#include <SDL.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>
#include <stdbool.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "Menu.h"


void gameloop(SDL_Renderer *renderer, int level, int speedX, int speedY, int bricksH, int bricksW, int spaceI, int spaceJ) {

    srand(time(NULL));
    bool quit = false;
    bool allBricksDestroyed = true;
    SDL_Event event;
    int life = 5;
    int lastActionTime = SDL_GetTicks();
    int speedPlateform = 10;
    int score = 0;
    int col = 8;
    int lin = 5;
    struct keyboardControl keyboardControl;
    struct bricks Bricks[col][lin];


    SDL_Surface *tmp = NULL;
    SDL_Texture *texture = NULL;
    tmp = IMG_Load("C:\\Users\\amand\\CLionProjects\\CasseBriques\\balle.png");
    if(NULL == tmp){
        fprintf(stderr, "Erreur SDL_LoadBMP : %s", SDL_GetError());
    }

    texture = SDL_CreateTextureFromSurface(renderer, tmp);          /* Déclaration de sa position */
    SDL_FreeSurface(tmp);
    SDL_Rect ball_rect;
    ball_rect.x = 580;
    ball_rect.y = 660;
    ball_rect.w = 40;
    ball_rect.h = 40;

    SDL_Surface *plateform = NULL;
    SDL_Texture *texture1 = NULL;
    plateform = IMG_Load("C:\\Users\\amand\\CLionProjects\\CasseBriques\\plateforme.png" );

    if(NULL == plateform){
        fprintf(stderr, "Erreur SDL_LoadBMP : %s", SDL_GetError());
    }

    texture1 = SDL_CreateTextureFromSurface(renderer, plateform);
    SDL_FreeSurface(plateform);
    SDL_Rect player_rect;
    player_rect.x = 550;
    player_rect.y = 700;
    player_rect.w = 100;
    player_rect.h = 20;

    while(!quit){
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                quit = true;
                break;
            }
            else{
                updateKeyboardControl(&event, &keyboardControl);
            }
        }

        SDL_SetRenderDrawColor(renderer, 0,0,0,255);
        SDL_RenderClear(renderer);

        for(int i=0; i<col; i++){
            for(int j=0; j<lin; j++){
                if (level % 3 == 1) {
                    if (Bricks[i][j].destroyed == false) {
                        Bricks[i][j].x = i * 135 + spaceI * 3;
                        Bricks[i][j].y = j * 75 + spaceJ * 4;
                        Bricks[i][j].w = bricksW;
                        Bricks[i][j].h = bricksH;
                    }
                }
                if (level % 3 == 2) {
                    if (Bricks[i][j].destroyed == false) {
                        Bricks[i][j].x = i * 135 + spaceI * 3;
                        Bricks[i][j].y = j * 75 + spaceJ * 4;
                        Bricks[i][j].w = bricksW;
                        Bricks[i][j].h = bricksH;
                    }
                }
                if (level % 3 == 0) {
                    if (Bricks[i][j].destroyed == false) {
                        Bricks[i][j].x = i * 135 + spaceI * 3;
                        Bricks[i][j].y = j * 85 + spaceJ * 4;
                        Bricks[i][j].w = bricksW;
                        Bricks[i][j].h = bricksH;
                    }
                }
                if (collisionBricks(ball_rect, Bricks[i][j])) {
                    speedY = speedY * -1;
                    Bricks[i][j].x = 0;
                    Bricks[i][j].y = 0;
                    Bricks[i][j].w = 0;
                    Bricks[i][j].h = 0;
                    Bricks[i][j].destroyed = true;
                    score += 100;
                }
            }
        }
        if(collisionPlateform(ball_rect, player_rect)){
            speedY = speedY * -1;
        }
        if(keyboardControl.right){
            player_rect.x += speedPlateform;
        }else if(keyboardControl.left){
            player_rect.x -= speedPlateform;
        }

        if (player_rect.x <= 0 ){
            player_rect.x = 0;
        } else if (player_rect.x + player_rect.w > 1200){
            player_rect.x = 1200 - player_rect.w;
        }

        if(SDL_GetTicks() - lastActionTime > 15) {
            ball_rect.x = ball_rect.x + speedX;
            ball_rect.y = ball_rect.y + speedY;
            if (ball_rect.x + ball_rect.w > 1200 || ball_rect.x < 0) {
                speedX = speedX * -1;
            }
            if (ball_rect.y < 0) {
                speedY = speedY * -1;
            }
            if (ball_rect.y + ball_rect.h > 800) {
                ball_rect.x = 580;
                ball_rect.y = 500;
                life--;
            }
            lastActionTime = SDL_GetTicks();
        }

        if (score == col * lin * 100){
            level++;
            speedX++;
            speedY++;
            bricksH -= 2;
            bricksW -= 4;
            spaceI += 4;
            spaceJ += 4;
            if (bricksH <= 20 && bricksW <= 40){
                bricksH = 20;
                bricksW = 40;
            }
            gameloop(renderer, level, speedX, speedY, bricksH, bricksW, 25, 25);
        }

        if (life <= 0){
            restartMenu(renderer);
        }

        SDL_RenderCopy(renderer, texture, NULL, &ball_rect);
        SDL_RenderCopy(renderer, texture1, NULL, &player_rect);
        render(renderer,  life, level, score, &Bricks, col, lin);
    }
}

void render(SDL_Renderer *renderer,  int life, int level, int score, struct bricks *Bricks, int col, int lin) {        /* fonction qui permet de quasi tout afficher */
    /* elle est appelée à la fin de gameloop */
    randomColor();
    randomNumber(1000, 2000);
    draw_random_points(2000, randomNumber(1000, 2000), renderer);
    renderLifeBar(renderer, life);
    displayText(renderer, level, score);
    displayBricks(renderer, level, Bricks, col, lin);
    SDL_RenderPresent(renderer);
}

bool collisionPlateform(SDL_Rect ball, SDL_Rect plateform) {                          /* Fonction qui permet la collision entre la balle */
    /* et la plateforme */
    bool xCollide = (plateform.x < ball.x && plateform.x + plateform.w > ball.x) ||
            (plateform.x < ball.x + ball.w && plateform.x + plateform.w > ball.x + ball.w);
    bool yCollide = (plateform.y < ball.y && plateform.y + plateform.h > ball.y) ||
            (plateform.y < ball.y + ball.h && plateform.y + plateform.h > ball.y + ball.h);

    return xCollide && yCollide;
}

bool collisionBricks(SDL_Rect ball, struct bricks bricks) {                          /* Fonction qui permet la collision entre la balle */
    /* et les briques */
    bool xCollision = (bricks.x < ball.x && bricks.x + bricks.w > ball.x) ||
            (bricks.x < ball.x + ball.w && bricks.x + bricks.w > ball.x + ball.w);
    bool yCollision = (bricks.y < ball.y && bricks.y + bricks.h > ball.y ) ||
            (bricks.y < ball.y + ball.h && bricks.y + bricks.h > ball.y + ball.h);

    return xCollision && yCollision;
}

void displayBricks(SDL_Renderer *renderer, int level, struct bricks *Bricks, int col, int lin) {         /* Affichage des briques sur l'écran */
    int nbbricks = col * lin;

    if (level % 3 == 1) {
        SDL_Surface *imgBricks = NULL;
        SDL_Texture *textureBricks = NULL;
        imgBricks = IMG_Load("C:\\Users\\amand\\CLionProjects\\CasseBriques\\briquesGalaxy.png");

        if (NULL == imgBricks) {
            fprintf(stderr, "Erreur SDL_LoadBMP : %s", SDL_GetError());
        }

        textureBricks = SDL_CreateTextureFromSurface(renderer, imgBricks);
        SDL_FreeSurface(imgBricks);

        for (int i = 0; i < nbbricks; i++) {
            SDL_Rect brick_rect = {Bricks[i].x, Bricks[i].y, Bricks[i].w, Bricks[i].h};
            SDL_RenderCopy(renderer, textureBricks, NULL, &brick_rect);
        }
    }
    if (level % 3 == 2) {
        SDL_Surface *imgBricksLV2 = NULL;
        SDL_Texture *textureBricksLV2 = NULL;
        imgBricksLV2 = IMG_Load("C:\\Users\\amand\\CLionProjects\\CasseBriques\\briquesGalaxyL2.png");

        if (NULL == imgBricksLV2) {
            fprintf(stderr, "Erreur SDL_LoadBMP : %s", SDL_GetError());
        }

        textureBricksLV2 = SDL_CreateTextureFromSurface(renderer, imgBricksLV2);
        SDL_FreeSurface(imgBricksLV2);

        for (int i = 0; i < nbbricks; i++) {
            SDL_Rect brick_rectLV2 = {Bricks[i].x, Bricks[i].y, Bricks[i].w, Bricks[i].h};
            SDL_RenderCopy(renderer, textureBricksLV2, NULL, &brick_rectLV2);
        }
    }

    if (level % 3 == 0) {
        SDL_Surface *imgBricksLV3 = NULL;
        SDL_Texture *textureBricksLV3 = NULL;
        imgBricksLV3 = IMG_Load("C:\\Users\\amand\\CLionProjects\\CasseBriques\\briquesGalaxyL3.png");

        if (NULL == imgBricksLV3) {
            fprintf(stderr, "Erreur SDL_LoadBMP : %s", SDL_GetError());
        }

        textureBricksLV3 = SDL_CreateTextureFromSurface(renderer, imgBricksLV3);
        SDL_FreeSurface(imgBricksLV3);

        for (int i = 0; i < nbbricks; i++) {
            SDL_Rect brick_rectLV3 = {Bricks[i].x, Bricks[i].y, Bricks[i].w, Bricks[i].h};
            SDL_RenderCopy(renderer, textureBricksLV3, NULL, &brick_rectLV3);
        }
    }
}

void displayText(SDL_Renderer *renderer, int level, int score){
    /* Affichage du numéro du niveau en haut à droite de l'écran et du score qui augmente */
    if(TTF_Init() == -1){
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    char str[5];
    sprintf(str, "%d",level);
    TTF_Font* Fast = TTF_OpenFont("fast99.ttf", 50);
    SDL_Color White = {255, 255, 255};

    SDL_Surface* levelDisplay= TTF_RenderText_Solid(Fast, str, White);
    SDL_Texture* LevelDisplay= SDL_CreateTextureFromSurface(renderer, levelDisplay);
    SDL_Rect Level_rect;
    Level_rect.x = 1150;
    Level_rect.y = 19;
    Level_rect.w = 10;
    Level_rect.h = 25;
    SDL_RenderCopy(renderer, LevelDisplay, NULL, &Level_rect);

    SDL_Surface* levelMessage = TTF_RenderText_Solid(Fast, "level :", White);
    SDL_Texture* LevelMessage = SDL_CreateTextureFromSurface(renderer, levelMessage);
    SDL_Rect LevelM_rect;
    LevelM_rect.x = 1040;
    LevelM_rect.y = 15;
    LevelM_rect.w = 100;
    LevelM_rect.h = 30;
    SDL_RenderCopy(renderer, LevelMessage, NULL, &LevelM_rect);

    char string[5];
    sprintf(string, "%d",score);
    SDL_Surface* scoreDisplay= TTF_RenderText_Solid(Fast, string, White);
    SDL_Texture* ScoreDisplay= SDL_CreateTextureFromSurface(renderer, scoreDisplay);
    SDL_Rect score_rect;
    score_rect.x = 920;
    score_rect.y = 20;
    score_rect.w = 30;
    score_rect.h = 25;
    SDL_RenderCopy(renderer, ScoreDisplay, NULL, &score_rect);

    SDL_Surface* scoreMessage= TTF_RenderText_Solid(Fast, "score :", White);
    SDL_Texture* ScoreMessage= SDL_CreateTextureFromSurface(renderer, scoreMessage);
    SDL_Rect scoreM_rect;
    scoreM_rect.x = 800;
    scoreM_rect.y = 15;
    scoreM_rect.w = 100;
    scoreM_rect.h = 30;
    SDL_RenderCopy(renderer, ScoreMessage, NULL, &scoreM_rect);
}

void renderLifeBar(SDL_Renderer *renderer, int life) {               /* Fonction qui affiche le nombre de vie en haut à
                                                                    * gauche de l'écran en fonction du nombre de vie
                                                                    * qu'on choisit pour le niveau*/
    int heightLife = 10;
    int sideLife = 20;

    SDL_Surface *tmp = NULL;
    SDL_Texture *texture = NULL;

    tmp = IMG_Load("C:\\Users\\amand\\CLionProjects\\CasseBriques\\pv.png");
    if(NULL == tmp){
        fprintf(stderr, "Erreur SDL_LoadBMP : %s", SDL_GetError());
    }

    texture = SDL_CreateTextureFromSurface(renderer, tmp);
    SDL_FreeSurface(tmp);
    SDL_Rect pv_rect;
    pv_rect.x ;
    pv_rect.y = heightLife;
    pv_rect.w = sideLife;
    pv_rect.h = sideLife;

    for(int i = 0; i < life; i++){
        pv_rect.x = (i+1)*heightLife + i * sideLife;
        SDL_RenderCopy(renderer, texture, NULL, &pv_rect);
    }
}

/* Les trois dernières fonctions
* affichent les points aléatoirement en fond d'écran*/

void draw_random_points(int nr_points, bool randomizeColor, SDL_Renderer *renderer){
    int width = 1200;
    int height = 800;
    for(int i = 0; i < nr_points; ++i){
        if(randomizeColor){
            SDL_SetRenderDrawColor(renderer, randomColor(), randomColor(), randomColor(), 255);
        }
        SDL_RenderDrawPoint(renderer, randomNumber(0, width), randomNumber(0, height));
    }
}

int randomNumber(int nr_min, int nr_max){
    static bool initialized = false;

    if(!initialized){
        initialized = true;
        srand(time(NULL));
    }
    return rand() % nr_max + nr_min;
}

int randomColor(){
    return randomNumber(0, 255);
}

