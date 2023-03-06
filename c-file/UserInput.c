//
// Created by amand on 12/12/2022.
//

#include "UserInput.h"
#include "Briques.h"

void updateKeyboardControl(SDL_Event* event, struct keyboardControl* keyboardControl){


    if(event->type == SDL_KEYDOWN){
        if(event->key.keysym.sym == SDLK_UP){
            keyboardControl->up = true;
        }
        if(event->key.keysym.sym == SDLK_DOWN){
            keyboardControl->down = true;
        }
        if(event->key.keysym.sym == SDLK_LEFT){
            keyboardControl->left = true;
        }
        if(event->key.keysym.sym == SDLK_RIGHT) {
            keyboardControl->right = true;
        }
    }
    if(event->type == SDL_KEYUP){
        if(event->key.keysym.sym == SDLK_UP){
            keyboardControl->up = false;
        }
        if(event->key.keysym.sym == SDLK_DOWN){
            keyboardControl->down = false;
        }
        if(event->key.keysym.sym == SDLK_LEFT){
            keyboardControl->left = false;
        }
        if(event->key.keysym.sym == SDLK_RIGHT){
            keyboardControl->right = false;
        }
    }
}