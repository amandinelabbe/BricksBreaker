//
// Created by amand on 12/12/2022.
//

#ifndef HELLOSDL_BRIQUES_H
#define HELLOSDL_BRIQUES_H

#include <SDL.h>
#include <stdbool.h>

struct color{
    int r;
    int g;
    int b;
};

struct bricks{
    int life;
    int x;
    int y;
    int w;
    int h;
    bool destroyed;
};

void gameloop(SDL_Renderer *renderer, int level, int speedX, int speedY, int bricksH, int bricksW, int spaceI, int spaceJ);
void render(SDL_Renderer *renderer, int life, int level, int score, struct bricks *Bricks, int col, int lin);
bool collisionPlateform(SDL_Rect ball, SDL_Rect plateform);
bool collisionBricks(SDL_Rect ball, struct bricks bricks);
void displayBricks(SDL_Renderer *renderer, int level, struct bricks *Bricks, int col, int lin);
void renderLifeBar(SDL_Renderer *renderer, int life);
void displayText (SDL_Renderer *renderer, int level, int score);
void draw_random_points(int nr_points, bool randomizeColor, SDL_Renderer *renderer);
int randomNumber(int nr_min, int nr_max);
int randomColor();


#endif //HELLOSDL_BRIQUES_H

