#ifndef RENDERER_H
#define RENDERER_H

#include "colour.h"
#include <stdbool.h>

// --- Initialization and Shutdown ---

// Initializes the window and loads all rendering assets (like the font).
void renderer_init(int screen_width, int screen_height, const char *title);
void renderer_shutdown(void);

// --- Frame Management ---

// Should be called at the beginning of the main game loop's drawing phase.
void renderer_begin_frame(void);

// Should be called at the end of the main game loop's drawing phase.
void renderer_end_frame(void);

// --- Drawing Functions ---

// The core function for our grid-based rendering.
// Draws a single character glyph from our bitmap font to a specific grid cell.
void renderer_draw_glyph(
    int grid_x,
    int grid_y,
    char glyph,
    Colour fg_colour,
    Colour bg_colour);

// A helper function for drawing simple text (like UI elements) that doesn't
// need to be aligned to the main grid.
void renderer_draw_text(
    int pixel_x,
    int pixel_y,
    const char *text,
    Colour colour);

// --- Window Management ---

// A function to check if the user has requested to close the window.
bool renderer_should_close(void);

#endif // RENDERER_H
