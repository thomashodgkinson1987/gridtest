#include "renderer.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "raylib.h"

#include "actor.h"
#include "log.h"
#include "world.h"

// --- Module-Private State ---

struct renderer
{
    // --- Window Properties ---
    int screen_width;
    int screen_height;
    char *screen_title;
    int target_fps;

    // --- Font & Glyph Atlas ---
    Texture2D font_texture;
    int glyph_width;
    int glyph_height;
    Rectangle glyph_atlas[256];

    // --- Virtual Screen (Off-screen Buffer) ---
    RenderTexture2D virtual_screen;
    int virtual_width;
    int virtual_height;
    bool is_dirty;
};

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
static void build_glyph_atlas(Renderer *renderer)
{
    // Define the characters in the order they appear in the font texture.
    const char *chars_row0 = "abcdefghijklmnopqrstuvwxyz ";
    const char *chars_row1 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const char *chars_row2 = "1234567890";
    const char *chars_row3 = "()[]{}<>+-?!^:#_@%~$\"'&*=`|/\\.,;";

    // Process row 0 (lowercase)
    for (int i = 0; chars_row0[i] != '\0'; ++i)
    {
        char c = chars_row0[i];
        renderer->glyph_atlas[(unsigned char)c] = (Rectangle){
            .x = i * renderer->glyph_width,
            .y = 0 * renderer->glyph_height,
            .width = renderer->glyph_width,
            .height = renderer->glyph_height};
    }

    // Process row 1 (uppercase)
    for (int i = 0; chars_row1[i] != '\0'; ++i)
    {
        char c = chars_row1[i];
        renderer->glyph_atlas[(unsigned char)c] = (Rectangle){
            .x = i * renderer->glyph_width,
            .y = 1 * renderer->glyph_height,
            .width = renderer->glyph_width,
            .height = renderer->glyph_height};
    }

    // Process row 2 (numbers)
    for (int i = 0; chars_row2[i] != '\0'; ++i)
    {
        char c = chars_row2[i];
        renderer->glyph_atlas[(unsigned char)c] = (Rectangle){
            .x = i * renderer->glyph_width,
            .y = 2 * renderer->glyph_height,
            .width = renderer->glyph_width,
            .height = renderer->glyph_height};
    }

    // Process row 3 (symbols)
    for (int i = 0; chars_row3[i] != '\0'; ++i)
    {
        char c = chars_row3[i];
        renderer->glyph_atlas[(unsigned char)c] = (Rectangle){
            .x = i * renderer->glyph_width,
            .y = 3 * renderer->glyph_height,
            .width = renderer->glyph_width,
            .height = renderer->glyph_height};
    }
}

static void draw_world(const Renderer *renderer, World *world)
{
    for (int y = 0; y < world_get_height(world); ++y)
    {
        for (int x = 0; x < world_get_width(world); ++x)
        {
            const Actor *actor = world_get_actor_at(world, x, y);
            if (actor)
            {
                const char glyph = actor_get_glyph(actor);
                const Colour fg_colour = actor_get_colour(actor);
                const Colour bg_colour = (Colour){0, 0, 0, 255};
                renderer_draw_glyph(
                    renderer,
                    x,
                    y,
                    glyph,
                    fg_colour,
                    bg_colour);
            }
            else
            {
                const Tile *tile = world_get_tile_at(world, x, y);
                char glyph = '?';
                switch (tile->type)
                {
                case TILE_TYPE_FLOOR:
                    glyph = '.';
                    break;
                case TILE_TYPE_WALL:
                    glyph = '#';
                    break;
                default:
                    glyph = '?';
                    break;
                }
                const Colour fg_colour = {255, 255, 255, 255};
                const Colour bg_colour = {0, 0, 0, 255};
                renderer_draw_glyph(
                    renderer,
                    x,
                    y,
                    glyph,
                    fg_colour,
                    bg_colour);
            }
        }
    }
}

// This is the core of the new system. It draws the entire game world
// to the off-screen render texture.
static void redraw_virtual_screen(Renderer *renderer, World *world)
{
    // Activate drawing to our off-screen buffer
    BeginTextureMode(renderer->virtual_screen);
    ClearBackground(BLACK); // Clear the buffer

    // Render current world state to off-screen buffer
    draw_world(renderer, world);

    // Deactivate drawing to the off-screen buffer
    EndTextureMode();

    // Mark the screen as clean
    renderer->is_dirty = false;
}

// --- Public API Implementation ---

Renderer *renderer_create(
    int screen_width,
    int screen_height,
    const char *screen_title)
{
    Renderer *renderer = malloc(sizeof(*renderer));
    if (!renderer)
    {
        log_perror("Renderer allocation failure");
        log_fatal(
            "%s: Fatal error due to renderer allocation failure",
            __func__);
    }

    renderer->screen_width = screen_width;
    renderer->screen_height = screen_height;
    renderer->screen_title = strdup(screen_title);
    if (!renderer->screen_title)
    {
        log_perror("Screen title allocation failure");
        log_fatal(
            "%s: Fatal error due to screen title allocation failure",
            __func__);
    }
    renderer->target_fps = 60;

    InitWindow(
        renderer->screen_width,
        renderer->screen_height,
        renderer->screen_title);
    SetTargetFPS(renderer->target_fps);

    // Load the font texture
    renderer->font_texture = LoadTexture("res/bitmap_font_0001.png");
    if (renderer->font_texture.id == 0)
    {
        // A simple way to handle the error if the texture is not found
        log_fatal(
            "%s: Failed to load font texture 'res/bitmap_font_0001.png'\n",
            __func__);
    }

    // Build the lookup table
    renderer->glyph_width = 12;
    renderer->glyph_height = 12;
    build_glyph_atlas(renderer);

    // Calculate virtual screen dimensions and create the render texture
    renderer->virtual_width = 256;  // manually linked with screen size
    renderer->virtual_height = 256; // in game.c
    renderer->virtual_screen = LoadRenderTexture(
        renderer->virtual_width,
        renderer->virtual_height);

    // Force an initial draw on the first frame
    renderer->is_dirty = true;
}

void renderer_free(Renderer *renderer)
{
    UnloadRenderTexture(renderer->virtual_screen);
    UnloadTexture(renderer->font_texture);

    free(renderer->screen_title);
    free(renderer);

    CloseWindow();
}

void renderer_begin_frame(Renderer *renderer, World *world)
{
    if (renderer->is_dirty)
    {
        redraw_virtual_screen(renderer, world);
    }

    BeginDrawing();
    ClearBackground(BLACK);
}

void renderer_end_frame(const Renderer *renderer)
{
    // Draw the entire virtual screen texture to the window in one go.
    // This is where scaling happens. We use DrawTexturePro for flexibility.
    Rectangle source_rect = {
        0.0f,
        0.0f,
        (float)renderer->virtual_screen.texture.width,
        // Inverting height is needed because OpenGL textures are upside-down.
        -(float)renderer->virtual_screen.texture.height};

    Rectangle dest_rect = {
        0.0f,
        0.0f,
        (float)renderer->screen_width,
        (float)renderer->screen_height};

    DrawTexturePro(
        renderer->virtual_screen.texture,
        source_rect,
        dest_rect,
        (Vector2){0, 0}, // Origin
        0.0f,            // Rotation
        WHITE);          // Tint

    EndDrawing();
}

void renderer_draw_glyph(
    const Renderer *renderer,
    int grid_x,
    int grid_y,
    char glyph,
    Colour fg_colour,
    Colour bg_colour)
{
    // Calculate the destination pixel position on the screen
    const float dest_x = (float)grid_x * renderer->glyph_width;
    const float dest_y = (float)grid_y * renderer->glyph_height;

    // Convert our custom Colour to Raylib Color
    const Color raylib_bg = to_raylib_colour(bg_colour);
    const Color raylib_fg = to_raylib_colour(fg_colour);

    // Draw the background cell colour
    DrawRectangle(
        dest_x,
        dest_y,
        renderer->glyph_width,
        renderer->glyph_height,
        raylib_bg);

    // Look up the source rectangle for the glyph from our atlas
    const Rectangle source_rect = renderer->glyph_atlas[(unsigned char)glyph];
    const Rectangle dest_rect = (Rectangle){
        .x = dest_x,
        .y = dest_y,
        .width = (float)renderer->glyph_width,
        .height = (float)renderer->glyph_height};
    const Vector2 origin = (Vector2){0.0f, 0.0f};
    const float rotation = 0.0f;

    // Draw the glyph texture itself
    if (source_rect.width > 0) // Don't draw empty glyphs like space
    {
        DrawTexturePro(
            renderer->font_texture,
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
    Colour colour,
    int size)
{
    // This is a simple wrapper around Raylib's default font drawing,
    // not our bitmap font. Useful for debug text.
    DrawText(text, pixel_x, pixel_y, size, to_raylib_colour(colour));
}

bool renderer_should_close(void)
{
    return WindowShouldClose();
}

// --- State Management ---

void renderer_set_dirty(Renderer *renderer)
{
    renderer->is_dirty = true;
}
