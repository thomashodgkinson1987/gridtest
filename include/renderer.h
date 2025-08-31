#ifndef RENDERER_H
#define RENDERER_H

#include <stdbool.h>

#include "colour.h"

typedef struct renderer Renderer;
typedef struct world World;

Renderer *renderer_create(
    int screen_width,
    int screen_height,
    const char *screen_title);
void renderer_free(Renderer *renderer);

void renderer_begin_frame(Renderer *renderer, World *world);
void renderer_end_frame(Renderer *renderer);

void renderer_draw_glyph(
    const Renderer *renderer,
    int grid_x,
    int grid_y,
    char glyph,
    Colour fg_colour,
    Colour bg_colour);

void renderer_draw_text(
    int pixel_x,
    int pixel_y,
    const char *text,
    Colour colour,
    int size);

bool renderer_should_close(void);

void renderer_set_dirty(Renderer *renderer);

#endif // RENDERER_H
