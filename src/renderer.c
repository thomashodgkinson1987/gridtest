#include "renderer.h"
#include "world.h"
#include "raylib.h"

#include <stdbool.h>
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

    int virtual_width;
    int virtual_height;
    RenderTexture2D virtual_screen;
    bool is_dirty;
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

// This is the core of the new system. It draws the entire game world
// to the off-screen render texture.
static void redraw_virtual_screen(const World *world)
{
    // Activate drawing to our off-screen buffer
    BeginTextureMode(renderer_state.virtual_screen);
    ClearBackground(BLACK); // Clear the buffer

    world_render(world);

    // --- THIS IS WHERE world_render() WILL GO ---
    // We will need to modify world_render to draw the world here.
    // For now, we'll just draw a test pattern.



    // for (int y = 0; y < 50; ++y)
    // {
    //     for (int x = 0; x < 80; ++x)
    //     {
    //         renderer_draw_glyph(x, y, 'A' + (x + y) % 26, (Colour){255, 255, 255, 255}, (Colour){20, 20, 20, 255});
    //     }
    // }



    // --- END OF PLACEHOLDER ---

    // Deactivate drawing to the off-screen buffer
    EndTextureMode();

    // Mark the screen as clean
    renderer_state.is_dirty = false;
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

    // Calculate virtual screen dimensions and create the render texture
    // renderer_state.virtual_width = 80 * renderer_state.glyph_width;   // Example: 80 columns
    // renderer_state.virtual_height = 50 * renderer_state.glyph_height; // Example: 50 rows
    renderer_state.virtual_width = 128;   // Example: 80 columns
    renderer_state.virtual_height = 128; // Example: 50 rows
    renderer_state.virtual_screen = LoadRenderTexture(
        renderer_state.virtual_width,
        renderer_state.virtual_height);

    // Force an initial draw on the first frame
    renderer_state.is_dirty = true;
}

void renderer_shutdown(void)
{
    UnloadRenderTexture(renderer_state.virtual_screen);
    UnloadTexture(renderer_state.font_texture);
    CloseWindow();
}

void renderer_begin_frame(const World *world)
{
    if (renderer_state.is_dirty)
    {
        redraw_virtual_screen(world);
    }

    BeginDrawing();
    ClearBackground(BLACK);
}

void renderer_end_frame(void)
{
    // Draw the entire virtual screen texture to the window in one go.
    // This is where scaling happens. We use DrawTexturePro for flexibility.
    Rectangle source_rect = {
        0.0f,
        0.0f,
        (float)renderer_state.virtual_screen.texture.width,
        // Inverting the height is necessary because OpenGL textures are upside-down.
        -(float)renderer_state.virtual_screen.texture.height};

    Rectangle dest_rect = {
        0.0f,
        0.0f,
        (float)renderer_state.screen_width,
        (float)renderer_state.screen_height};

    DrawTexturePro(
        renderer_state.virtual_screen.texture,
        source_rect,
        dest_rect,
        (Vector2){0, 0}, // Origin
        0.0f,            // Rotation
        WHITE);          // Tint

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
    const Color raylib_bg = to_raylib_colour(bg_colour);
    const Color raylib_fg = to_raylib_colour(fg_colour);

    // Draw the background cell colour
    DrawRectangle(
        dest_x,
        dest_y,
        renderer_state.glyph_width,
        renderer_state.glyph_height,
        raylib_bg);

    // Look up the source rectangle for the glyph from our atlas
    const Rectangle source_rect = renderer_state.glyph_atlas[(unsigned char)glyph];
    const Rectangle dest_rect = (Rectangle){
        .x = dest_x,
        .y = dest_y,
        .width = (float)renderer_state.glyph_width,
        .height = (float)renderer_state.glyph_height
    };
    const Vector2 origin = (Vector2){0.0f, 0.0f};
    const float rotation = 0.0f;

    // Draw the glyph texture itself
    if (source_rect.width > 0) // Don't draw empty glyphs like space
    {
        // DrawTextureRec(
        //     renderer_state.font_texture,
        //     source_rect,
        //     (Vector2){dest_x, dest_y},
        //     raylib_fg);
        DrawTexturePro(
            renderer_state.font_texture,
            source_rect,
            dest_rect,
            origin,
            rotation,
            raylib_fg);
    }
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

// --- State Management ---

void renderer_set_dirty(void)
{
    renderer_state.is_dirty = true;
}
