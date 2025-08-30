#include "world.h"

#include <stdbool.h>
#include <stdint.h> // For SIZE_MAX
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "actor.h"
#include "actor_array.h"
#include "command.h"
#include "log.h"
#include "renderer.h"

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
        log_fatal(
            "%s: Invalid world dimensions (%d x %d). Must be at least 1x1.\n",
            __func__,
            width,
            height);
    }

    World *world = malloc(sizeof(*world));
    if (!world)
    {
        log_perror("World allocation failure");
        log_fatal(
            "%s: Fatal error due to world allocation failure",
            __func__);
    }

    world->width = width;
    world->height = height;

    // Defensively check for integer overflow before calculating tile_count.
    if ((size_t)width > SIZE_MAX / (size_t)height)
    {
        log_message(
            LOG_LEVEL_ERROR,
            "%s: Map dimensions (%d x %d) would cause size_t overflow",
            __func__,
            width,
            height);
        free(world);
        log_fatal("%s: Fatal error due to world dimensions");
    }
    const size_t tile_count = (size_t)width * (size_t)height;

    // The second, more robust check you identified: ensure the final
    // allocation size for the malloc call does not overflow.
    if (tile_count > SIZE_MAX / sizeof(*world->tiles))
    {
        log_message(
            LOG_LEVEL_ERROR,
            "%s: Total tile memory allocation size would overflow",
            __func__);
        free(world);
        log_fatal("%s: Fatal error due to catching overflow", __func__);
    }

    // Allocate memory for the map tiles
    world->tiles = malloc(tile_count * sizeof(*world->tiles));
    if (!world->tiles)
    {
        log_perror("World tiles allocation failure");
        free(world);
        log_fatal(
            "%s: Fatal error due to world tiles allocation failure",
            __func__);
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
    // Free all the actors stored in the dynamic array
    for (size_t i = 0; i < actor_array_get_count(&world->actors); ++i)
    {
        Actor *actor = actor_array_get(&world->actors, i);
        actor_free(actor);
    }

    // Free the dynamic array's internal data
    actor_array_free(&world->actors);

    // Free the map tiles
    free(world->tiles);

    // Free the world struct itself
    free(world);
}

// -- World Getters ---

int world_get_width(const World *world)
{
    return world->width;
}
int world_get_height(const World *world)
{
    return world->height;
}

// --- World Management ---

void world_add_actor(World *world, Actor *actor)
{
    actor_array_push(&world->actors, actor);
}

void world_remove_actor(World *world, Actor *actor)
{
    size_t index = 0;
    bool was_found = false;

    for (size_t i = 0; i < actor_array_get_count(&world->actors); ++i)
    {
        Actor *_actor = actor_array_get(&world->actors, i);
        if (_actor == actor)
        {
            index = i;
            was_found = true;
            break;
        }
    }

    if (!was_found)
    {
        log_fatal("%s: Actor not in array", __func__);
    }

    actor_array_remove(&world->actors, index);
    actor_free(actor);
}

void world_update_actors(World *world)
{
    // This is the core of the monster turn logic.
    for (size_t i = 0; i < actor_array_get_count(&world->actors); ++i)
    {
        Actor *actor = actor_array_get(&world->actors, i);
        if (actor_get_component(actor, COMPONENT_TYPE_AI))
        {
            log_message(LOG_LEVEL_INFO, "AI actor takes its turn.");
        }
    }
}

Command world_actor_attack_actor(
    World *world,
    Actor *attacker,
    Actor *defender)
{
    const Component *combat_component = actor_get_component(
        attacker,
        COMPONENT_TYPE_COMBAT);

    if (!combat_component)
    {
        log_fatal(
            "%s: Attacker '%s' does not have [%s] component",
            __func__,
            actor_get_name(attacker),
            component_get_name_from_type(COMPONENT_TYPE_COMBAT));
    }

    Command command = command_actor_translate_health_create(
        defender,
        -combat_component->params.combat.attack_power);

    return command;
}

// --- World Queries ---

const Actor *world_get_actor_at(World *world, int x, int y)
{
    for (size_t i = 0; i < actor_array_get_count(&world->actors); ++i)
    {
        const Actor *actor = actor_array_get(&world->actors, i);
        int actor_x, actor_y;
        actor_get_position(actor, &actor_x, &actor_y);
        if (actor_x == x && actor_y == y)
        {
            return actor;
        }
    }
    return NULL;
}

Actor *world_get_actor_at_mut(World *world, int x, int y)
{
    for (size_t i = 0; i < actor_array_get_count(&world->actors); ++i)
    {
        Actor *actor = actor_array_get(&world->actors, i);
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

Tile *world_get_tile_at_mut(World *world, int x, int y)
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
