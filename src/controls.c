#include "controls.h"
#include <conio.h>

int8_t controls_init(struct motion_coeff* mc)
{
    mc->x_coeff = 0;
    mc->y_coeff = 1;

    return 0;
}

DWORD WINAPI ListenKeyboard(LPVOID lpParam)
{
    while (1)
    {
        uint8_t key = getch();

        if (key == UP_ARROW)
        {
            ((struct motion_coeff*)lpParam)->x_coeff = 0;
            ((struct motion_coeff*)lpParam)->y_coeff = -1;
        }
        else if (key == LEFT_ARROW)
        {
            ((struct motion_coeff*)lpParam)->x_coeff = -1;
            ((struct motion_coeff*)lpParam)->y_coeff = 0;
        }
        else if (key == RIGHT_ARROW)
        {
            ((struct motion_coeff*)lpParam)->x_coeff = 1;
            ((struct motion_coeff*)lpParam)->y_coeff = 0;
        }
        else if (key == DOWN_ARROW)
        {
            ((struct motion_coeff*)lpParam)->x_coeff = 0;
            ((struct motion_coeff*)lpParam)->y_coeff = 1;
        }
    }

    return 0;
}