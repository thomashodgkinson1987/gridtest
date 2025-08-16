#include "world.h"

#include <stdlib.h>
#include <string.h>

#include "actor.h"
#include "tile.h"
#include "tile_map.h"
#include "actor_array.h"

World *world_create(
    int width,
    int height,
    TilePrototypeRepository *tile_prototype_repository)
{
    World *world = malloc(sizeof(World));
    if (!world)
    {
        return NULL;
    }

    world->tile_map = malloc(sizeof(TileMap));
    if (!world->tile_map)
    {
        free(world);
        return NULL;
    }
    *world->tile_map = tile_map_create(width, height);

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            TileFlags flags = TILE_FLAG_WALKABLE;
            TileColour colour = tile_colour_create(0, 255, 0, 255);
            const Tile tile = tile_create(flags, colour);
            tile_map_set_tile(world->tile_map, x, y, tile);
        }
    }

    world->actors = malloc(sizeof(ActorArray));
    if (!world->actors)
    {
        tile_map_free(world->tile_map);
        free(world->tile_map);
        free(world);
        return NULL;
    }
    *world->actors = actor_array_create(1);

    return world;
}

void world_free(
    World *world)
{
    if (!world)
    {
        return;
    }

    if (world->actors)
    {
        for (size_t i = 0; i < world->actors->count; ++i)
        {
            actor_free(world->actors->data[i]);
        }
        actor_array_free(world->actors);
    }

    if (world->tile_map)
    {
        tile_map_free(world->tile_map);
        free(world->tile_map);
    }

    free(world);
}

void world_add_actor(
    World *world,
    Actor *actor)
{
    if (!world || !world->actors || !actor)
    {
        return;
    }
    actor_array_push(world->actors, actor);
}

bool world_move_actor(
    World *world,
    Actor *actor,
    int dx,
    int dy)
{
    if (!world || !actor)
    {
        return false;
    }

    int new_x = actor_get_x(actor) + dx;
    int new_y = actor_get_y(actor) + dy;

    if (new_x < 0 ||
        new_x >= world->tile_map->width ||
        new_y < 0 ||
        new_y >= world->tile_map->height)
    {
        return false;
    }

    const Tile *destination_tile = world_get_tile(world, new_x, new_y);
    if (!destination_tile || !tile_is_walkable(destination_tile))
    {
        return false;
    }

    if (world_get_actor_at(world, new_x, new_y))
    {
        return false;
    }

    actor_set_position(actor, new_x, new_y);
    return true;
}

Tile *world_get_tile(
    World *world,
    int x,
    int y)
{
    if (!world || !world->tile_map)
    {
        return NULL;
    }
    return tile_map_get_tile(world->tile_map, x, y);
}

Actor *world_get_actor_at(
    World *world,
    int x,
    int y)
{
    if (!world || !world->actors)
    {
        return NULL;
    }

    for (size_t i = 0; i < world->actors->count; ++i)
    {
        Actor *actor = world->actors->data[i];
        if (actor_get_x(actor) == x && actor_get_y(actor) == y)
        {
            return actor;
        }
    }

    return NULL;
}