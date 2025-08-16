#ifndef TILE_H
#define TILE_H

#include <stdbool.h>

#include "tile_colour.h"
#include "tile_flags.h"

typedef struct tile
{
    TileFlags flags;
    TileColour colour;
} Tile;

Tile tile_create(TileFlags flags, TileColour colour);

bool tile_is_walkable(const Tile *tile);
bool tile_is_solid(const Tile *tile);

#endif // TILE_H
