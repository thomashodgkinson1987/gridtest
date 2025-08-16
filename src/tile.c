#include "tile.h"

#include <stdbool.h>

#include "tile_colour.h"
#include "tile_flags.h"

Tile tile_create(const TileFlags flags, const TileColour colour)
{
    Tile tile = {0};

    tile.flags = flags;
    tile.colour = colour;

    return tile;
}

bool tile_is_walkable(const Tile *tile)
{
    return tile->flags & TILE_FLAG_WALKABLE;
}

bool tile_is_solid(const Tile *tile)
{
    return tile->flags & TILE_FLAG_SOLID;
}
