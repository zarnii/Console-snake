#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include "game_field.h"
#include "snake.h"

int main(void)
{
    struct game_field* gf = malloc(sizeof(struct game_field));
    int8_t gf_init_result = game_field_init(gf, 10, 10);

    if (gf_init_result != 0)
    {
        printf("Game field init error");

        return 0;
    }

    struct snake* snk = malloc(sizeof(struct snake));
    int8_t snk_init_result = snake_init(snk);

    struct motion_coeff mc;
    int8_t mc_init_result = controls_init(&mc);

    if (snk_init_result != 0)
    {
        printf("Snake init error");

        return 0;
    }

    HANDLE handleThread = CreateThread(NULL, LISTEN_KEYBOARD_STACK_SIZE, ListenKeyboard, &mc, 0, NULL);

    while (1)
    {
        if (game_field_render(gf, snk))
        {
            break;
        }

        game_field_print(gf);

        if(snake_step(snk, &mc))
        {
            break;
        }

        Sleep(500);
    }

    game_field_destroy(gf);
    snake_destroy(snk);

    CloseHandle(handleThread);
    printf("GAME OVER");
    getch();
    
    return 0;
}