#include "snake.h"
#include <stdlib.h>

int8_t snake_check_head_collision(struct snake* snk);

int8_t snake_init(struct snake* snk)
{
    snk->body_parts = malloc(sizeof(struct body*) * MAX_BODY_PARTS_SIZE);

    if (snk->body_parts == NULL)
    {
        return 1;
    }

    for (size_t i = 0; i < MAX_BODY_PARTS_SIZE; i++)
    {
        snk->body_parts[i] = NULL;
    }
    
    struct body head = {2, 1};
    struct body* bd = malloc(sizeof(struct body));

    snk->head = head;
    bd->x = head.x - 1;
    bd->y = head.y;
    snk->body_parts_count = 1;
    snk->body_parts[0] = bd;
    bd = NULL;

    return 0;
}

void snake_destroy(struct snake* snk)
{
    for (size_t i = 0; i < snk->body_parts_count; i++)
    {
        free(snk->body_parts[i]);
    }

    free(snk->body_parts);
    free(snk);
}

int8_t snake_step(struct snake* snk, struct motion_coeff* mc)
{
    int32_t head_x = snk->head.x;
    int32_t head_y = snk->head.y;

    snk->head.x += mc->x_coeff;
    snk->head.y += mc->y_coeff;

    if (snake_check_head_collision(snk))
    {
        return 1;
    }

    for (size_t i = 0; i < snk->body_parts_count; i++)
    {
        struct body* bd = snk->body_parts[i];
        int32_t temp_x = bd->x;
        int32_t temp_y = bd->y;

        bd->x = head_x;
        bd->y = head_y;
        bd = NULL;

        head_x = temp_x;
        head_y = temp_y;
    }

    return 0;
}

void snake_add_body(struct snake* snk)
{
    struct body* prev_bd = snk->body_parts[snk->body_parts_count-1];
    struct body* bd = malloc(sizeof(struct body));

    bd->x = prev_bd->x - 1;
    bd->y = prev_bd->y;

    snk->body_parts[snk->body_parts_count] = bd;
    snk->body_parts_count++;

    bd = NULL;
}

int8_t snake_check_head_collision(struct snake* snk)
{
    for (size_t i = 0; i < snk->body_parts_count; i++)
    {
        struct body* bd = snk->body_parts[i];

        if (snk->head.x == bd->x && snk->head.y == bd->y)
        {
            return 1;
        }
    }

    return 0;
}