#ifndef CONTROLS
#define CONTROLS

#include "stdint.h"
#include <Windows.h>

#define UP_ARROW 72
#define LEFT_ARROW 75
#define RIGHT_ARROW 77
#define DOWN_ARROW 80
#define LISTEN_KEYBOARD_STACK_SIZE 3

struct motion_coeff
{
    int8_t x_coeff;
    int8_t y_coeff;
};

int8_t controls_init(struct motion_coeff* mc);
DWORD WINAPI ListenKeyboard(LPVOID lpParam);

#endif