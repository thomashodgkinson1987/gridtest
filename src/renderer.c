#include "renderer.h"
#include "raylib.h"

#include <stdio.h>
#include <stdlib.h>

// --- Module-Private State ---

// This static struct holds all the rendering-specific data.
// It is only visible within this .c file.
static struct
{
    int screen_width;
    int screen_height;

    Texture2D font_texture;
    Rectangle glyph_atlas[256]; // Our "dictionary" mapping char -> Rectangle
    int glyph_width;
    int glyph_height;

} renderer_state;

// --- Static Helper Functions ---

// Helper to convert our custom Colour struct to a Raylib Color struct.
static Color to_raylib_colour(Colour colour)
{
    return (Color){
        .r = colour.r,
        .g = colour.g,
        .b = colour.b,
        .a = colour.a};
}

// The core logic for building the glyph atlas lookup table.
static void build_glyph_atlas(void)
{
    // Define the characters in the order they appear in the font texture.
    const char *chars_row0 = "abcdefghijklmnopqrstuvwxyz ";
    const char *chars_row1 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const char *chars_row2 = "1234567890";
    const char *chars_row3 = "()[]{}<>+-?!^:#_@%~$\"'&*=`|/\\.,;";

    renderer_state.glyph_width = 12;
    renderer_state.glyph_height = 12;

    // Process row 0 (lowercase)
    for (int i = 0; chars_row0[i] != '\0'; ++i)
    {
        char c = chars_row0[i];
        renderer_state.glyph_atlas[(unsigned char)c] = (Rectangle){
            .x = i * renderer_state.glyph_width,
            .y = 0 * renderer_state.glyph_height,
            .width = renderer_state.glyph_width,
            .height = renderer_state.glyph_height};
    }

    // Process row 1 (uppercase)
    for (int i = 0; chars_row1[i] != '\0'; ++i)
    {
        char c = chars_row1[i];
        renderer_state.glyph_atlas[(unsigned char)c] = (Rectangle){
            .x = i * renderer_state.glyph_width,
            .y = 1 * renderer_state.glyph_height,
            .width = renderer_state.glyph_width,
            .height = renderer_state.glyph_height};
    }

    // Process row 2 (numbers)
    for (int i = 0; chars_row2[i] != '\0'; ++i)
    {
        char c = chars_row2[i];
        renderer_state.glyph_atlas[(unsigned char)c] = (Rectangle){
            .x = i * renderer_state.glyph_width,
            .y = 2 * renderer_state.glyph_height,
            .width = renderer_state.glyph_width,
            .height = renderer_state.glyph_height};
    }

    // Process row 3 (symbols)
    for (int i = 0; chars_row3[i] != '\0'; ++i)
    {
        char c = chars_row3[i];
        renderer_state.glyph_atlas[(unsigned char)c] = (Rectangle){
            .x = i * renderer_state.glyph_width,
            .y = 3 * renderer_state.glyph_height,
            .width = renderer_state.glyph_width,
            .height = renderer_state.glyph_height};
    }
}

// --- Public API Implementation ---

void renderer_init(int screen_width, int screen_height, const char *title)
{
    renderer_state.screen_width = screen_width;
    renderer_state.screen_height = screen_height;

    InitWindow(screen_width, screen_height, title);
    SetTargetFPS(60);

    // Load the font texture
    renderer_state.font_texture = LoadTexture("res/bitmap_font_0001.png");
    if (renderer_state.font_texture.id == 0)
    {
        // A simple way to handle the error if the texture is not found
        fprintf(
            stderr,
            "ERROR: Failed to load font texture 'res/bitmap_font_0001.png'\n");
        exit(EXIT_FAILURE);
    }

    // Build the lookup table
    build_glyph_atlas();
}

void renderer_shutdown(void)
{
    UnloadTexture(renderer_state.font_texture);
    CloseWindow();
}

void renderer_begin_frame(void)
{
    BeginDrawing();
    ClearBackground(BLACK);
}

void renderer_end_frame(void)
{
    EndDrawing();
}

void renderer_draw_glyph(
    int grid_x,
    int grid_y,
    char glyph,
    Colour fg_colour,
    Colour bg_colour)
{
    // Calculate the destination pixel position on the screen
    const float dest_x = (float)grid_x * renderer_state.glyph_width;
    const float dest_y = (float)grid_y * renderer_state.glyph_height;

    // Convert our custom Colour to Raylib Color
    Color raylib_bg = to_raylib_colour(bg_colour);
    Color raylib_fg = to_raylib_colour(fg_colour);

    // Draw the background cell colour
    DrawRectangle(
        dest_x,
        dest_y,
        renderer_state.glyph_width,
        renderer_state.glyph_height,
        raylib_bg);

    // Look up the source rectangle for the glyph from our atlas
    Rectangle source_rect = renderer_state.glyph_atlas[(unsigned char)glyph];

    // Draw the glyph texture itself
    DrawTextureRec(
        renderer_state.font_texture,
        source_rect,
        (Vector2){dest_x, dest_y},
        raylib_fg);
}

void renderer_draw_text(
    int pixel_x,
    int pixel_y,
    const char *text,
    Colour colour)
{
    // This is a simple wrapper around Raylib's default font drawing,
    // not our bitmap font. Useful for debug text.
    DrawText(text, pixel_x, pixel_y, 20, to_raylib_colour(colour));
}

bool renderer_should_close(void)
{
    return WindowShouldClose();
}
