#ifndef SNAKE
#define SNAKE

#include <stdint.h>
#include "controls.h"

#define MAX_BODY_PARTS_SIZE 100
#define SNAKE_BODY 'X'
#define SNAKE_HEAD '#'

struct body
{
    int32_t x;
    int32_t y;
};


struct snake
{
    struct body head;
    struct body** body_parts;
    int32_t body_parts_count;
};


int8_t snake_init(struct snake* snk);
int8_t snake_step(struct snake* snk, struct motion_coeff* mc);
void snake_add_body(struct snake* snk);
void snake_destroy(struct snake* snk);
#endif