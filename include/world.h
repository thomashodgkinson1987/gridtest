#ifndef WORLD_H
#define WORLD_H

#include "actor_array.h"
#include "tile.h"

#include <stdbool.h>

// Opaque pointer type for a World.
typedef struct world World;


// --- World Creation/Destruction ---

World* world_create(int width, int height);
void world_free(World* world);


// --- World Management ---

void world_add_actor(World* world, Actor* actor);
void world_update_actors(World* world);
void world_render(const World* world);


// --- World Queries ---

const Actor* world_get_actor_at(const World* world, int x, int y);
const Tile* world_get_tile_at(const World* world, int x, int y);

Actor* world_get_mutable_actor_at(World* world, int x, int y);
Tile* world_get_mutable_tile_at(World* world, int x, int y);

bool world_is_tile_walkable(const World* world, int x, int y);

#endif // WORLD_H
