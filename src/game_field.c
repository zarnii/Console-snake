#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "game_field.h"

void game_field_generate_apple(struct game_field* gf);
void game_field_clear(struct game_field* gf);

int8_t game_field_init(struct game_field* gf, int32_t width, int32_t height)
{
    gf->field = malloc(sizeof(char*) * height);

    if (gf->field == NULL)
    {
        return 1;
    }
    gf->height = height;
    gf->width = width;

    for (int32_t i = 0; i < height; i++)
    {
        char* row = malloc(sizeof(char) * width);

        for (int32_t j = 0; j < width; j++)
        {
            row[j] = '.';
        }

        gf->field[i] = row;
        row = NULL;
    }

    game_field_generate_apple(gf);

    return 0;
}

void game_field_destroy(struct game_field* gf)
{
    for (size_t i = 0; i < gf->height; i++)
    {
        free(gf->field[i]);
    }

    free(gf->field);
    free(gf);
}

int8_t game_field_render(struct game_field* gf, struct snake* snk)
{
    
    /* clear */
    game_field_clear(gf);
    
    /* snake generate */
    if (snk->head.x < 0 || 
        snk->head.y < 0 ||
        snk->head.x == gf->width ||
        snk->head.y == gf->height)
    {
        return 1;
    }

    gf->field[snk->head.y][snk->head.x] = SNAKE_HEAD;

    if (snk->head.x == gf->apple_x && snk->head.y == gf->apple_y)
    {
        snake_add_body(snk);
        game_field_generate_apple(gf);
    }

    for (size_t i = 0; i < snk->body_parts_count; i++)
    {
        struct body* bd = snk->body_parts[i];
        gf->field[bd->y][bd->x] = SNAKE_BODY;
    }

    /* apple generate */
    gf->field[gf->apple_y][gf->apple_x] = APPLE;

    return 0;
}

void game_field_print(struct game_field* gf)
{
    system("cls");

    size_t field_length = 0;
    char* field = malloc(sizeof(char) * ((gf->height * gf->width) + gf->height));

    for (size_t i = 0; i < gf->height; i++)
    {
        for (size_t j = 0; j < gf->width; j++)
        {
            field[field_length] = gf->field[i][j];
            field_length++;
        }
        field[field_length] = '\n';
        field_length++;
    }

    printf(field);
    free(field);
}

void game_field_clear(struct game_field* gf)
{
    for (size_t i = 0; i < gf->height; i++)
    {
        char* row = gf->field[i];

        for (size_t j = 0; j < gf->width; j++)
        {
            row[j] = '.';
        }

        row = NULL;
    }
}

void game_field_generate_apple(struct game_field* gf)
{
    srand(time(NULL));
    size_t x = 0 + rand() % gf->width;
    size_t y = 0 + rand() % gf->height;
    
    gf->field[y][x] = APPLE;
    gf->apple_x = x;
    gf->apple_y = y;
}