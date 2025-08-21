#include "world.h"
#include "actor.h"
#include "renderer.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h> // For SIZE_MAX

// The concrete definition of the world struct. This makes the type "complete"
// within this file, allowing us to access its members.
struct world
{
    int width;
    int height;
    Tile *tiles;       // A 1D array representing the 2D map
    ActorArray actors; // The dynamic array of actors from actor_array.h
};

// --- World Creation/Destruction ---

World *world_create(int width, int height)
{
    // Enforce a minimum world size.
    if (width < 1 || height < 1)
    {
        fprintf(
            stderr,
            "%s: Invalid world dimensions (%d x %d). Must be at least 1x1.\n",
            __func__,
            width,
            height);
        exit(EXIT_FAILURE);
    }

    World *world = malloc(sizeof(*world));
    if (!world)
    {
        char error_msg[100];
        snprintf(
            error_msg,
            sizeof(error_msg),
            "%s: Failed to allocate memory for world",
            __func__);
        perror(error_msg);
        exit(EXIT_FAILURE);
    }

    world->width = width;
    world->height = height;

    // Defensively check for integer overflow before calculating tile_count.
    if ((size_t)width > SIZE_MAX / (size_t)height)
    {
        fprintf(
            stderr,
            "%s: Map dimensions (%d x %d) would cause size_t overflow\n",
            __func__,
            width,
            height);
        free(world);
        exit(EXIT_FAILURE);
    }
    const size_t tile_count = (size_t)width * (size_t)height;

    // The second, more robust check you identified: ensure the final
    // allocation size for the malloc call does not overflow.
    if (tile_count > SIZE_MAX / sizeof(*world->tiles))
    {
        fprintf(
            stderr,
            "%s: Total tile memory allocation size would overflow\n",
            __func__);
        free(world);
        exit(EXIT_FAILURE);
    }

    // Allocate memory for the map tiles
    world->tiles = malloc(tile_count * sizeof(*world->tiles));
    if (!world->tiles)
    {
        char error_msg[100];
        snprintf(
            error_msg,
            sizeof(error_msg),
            "%s: Failed to allocate memory for tiles",
            __func__);
        perror(error_msg);
        free(world);
        exit(EXIT_FAILURE);
    }

    // Initialize all tiles to be walls by default
    for (size_t i = 0; i < tile_count; ++i)
    {
        world->tiles[i].type = TILE_TYPE_WALL;
    }

    // Create the dynamic array for actors with an initial capacity of 8.
    world->actors = actor_array_create(8);

    return world;
}

void world_free(World *world)
{
    if (!world)
    {
        return;
    }

    // Free all the actors stored in the dynamic array
    for (size_t i = 0; i < actor_array_get_count(&world->actors); ++i)
    {
        actor_free(*actor_array_get(&world->actors, i));
    }

    // Free the dynamic array's internal data
    actor_array_free(&world->actors);

    // Free the map tiles
    free(world->tiles);

    // Free the world struct itself
    free(world);
}

// --- World Management ---

void world_add_actor(World *world, Actor *actor)
{
    actor_array_push(&world->actors, actor);
}

void world_update_actors(World *world)
{
    // This is the core of the monster turn logic.
    for (size_t i = 0; i < actor_array_get_count(&world->actors); ++i)
    {
        Actor *actor = *actor_array_get(&world->actors, i);
        if (actor_get_ai_component(actor))
        {
            printf("AI actor takes its turn.\n");
        }
    }
}

void world_render(const World *world)
{
    // This is a simple console renderer for now.
    for (int y = 0; y < world->height; ++y)
    {
        for (int x = 0; x < world->width; ++x)
        {
            const Actor *actor = world_get_actor_at(world, x, y);
            if (actor)
            {
                const char glyph = actor_get_glyph(actor);
                const Colour fg_colour = actor_get_colour(actor);
                const Colour bg_colour = (Colour){0, 0, 0, 255};
                renderer_draw_glyph(x, y, glyph, fg_colour, bg_colour);
            }
            else
            {
                const Tile *tile = world_get_tile_at(world, x, y);
                switch (tile->type)
                {
                case TILE_TYPE_FLOOR:
                    renderer_draw_glyph(
                        x,
                        y,
                        '.',
                        (Colour){255, 255, 255, 255},
                        (Colour){0, 0, 0, 255});
                    break;
                case TILE_TYPE_WALL:
                    renderer_draw_glyph(
                        x,
                        y,
                        '#',
                        (Colour){255, 255, 255, 255},
                        (Colour){0, 0, 0, 255});
                    break;
                default:
                    renderer_draw_glyph(
                        x,
                        y,
                        '?',
                        (Colour){255, 255, 255, 255},
                        (Colour){0, 0, 0, 255});
                    break;
                }
            }
        }
    }
}

// --- World Queries ---

const Actor *world_get_actor_at(const World *world, int x, int y)
{
    for (size_t i = 0; i < actor_array_get_count(&world->actors); ++i)
    {
        const Actor *actor = *actor_array_get_const(&world->actors, i);
        int actor_x, actor_y;
        actor_get_position(actor, &actor_x, &actor_y);
        if (actor_x == x && actor_y == y)
        {
            return actor;
        }
    }
    return NULL;
}

Actor *world_get_mutable_actor_at(World *world, int x, int y)
{
    for (size_t i = 0; i < actor_array_get_count(&world->actors); ++i)
    {
        Actor *actor = *actor_array_get(&world->actors, i);
        int actor_x, actor_y;
        actor_get_position(actor, &actor_x, &actor_y);
        if (actor_x == x && actor_y == y)
        {
            return actor;
        }
    }
    return NULL;
}

const Tile *world_get_tile_at(const World *world, int x, int y)
{
    if (x < 0 || x >= world->width || y < 0 || y >= world->height)
    {
        return NULL;
    }
    return &world->tiles[y * world->width + x];
}

Tile *world_get_mutable_tile_at(World *world, int x, int y)
{
    if (x < 0 || x >= world->width || y < 0 || y >= world->height)
    {
        return NULL;
    }
    return &world->tiles[y * world->width + x];
}

bool world_is_tile_walkable(const World *world, int x, int y)
{
    const Tile *tile = world_get_tile_at(world, x, y);
    if (!tile)
    {
        return false;
    }
    return tile->type == TILE_TYPE_FLOOR;
}
