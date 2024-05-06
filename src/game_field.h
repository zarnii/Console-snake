#ifndef GAME_WORLD
#define GAME_FIELD

#include <stdint.h>
#include <Windows.h>
#include "snake.h"

#define APPLE 'o'

struct game_field
{
    char** field;
    int32_t height;
    int32_t width;
    int32_t apple_x;
    int32_t apple_y;
};

int8_t game_field_init(struct game_field* gf, int32_t weight, int32_t height);
int8_t game_field_render(struct game_field* gf, struct snake* snk);
void game_field_print(struct game_field* gf);
void game_field_destroy(struct game_field* gf);
#endif