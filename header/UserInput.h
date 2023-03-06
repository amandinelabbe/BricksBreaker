//
// Created by amand on 12/12/2022.
//

#include <stdbool.h>
#include <SDL.h>

#ifndef HELLOSDL_USERINPUT_H
#define HELLOSDL_USERINPUT_H

#endif //HELLOSDL_USERINPUT_H

struct keyboardControl{
    bool up;
    bool down;
    bool left;
    bool right;
    bool a;
};

void updateKeyboardControl(SDL_Event* event, struct keyboardControl* keyboardControl);
