#ifndef TILE_RROTOTYPE_H
#define TILE_RROTOTYPE_H

#include "tile.h"

#include "tile_colour.h"
#include "tile_flags.h"

typedef struct tile_prototype
{
    TileFlags flags;
    TileColour colour;
} TilePrototype;

TilePrototype tile_prototype_create(
    TileFlags flags,
    TileColour colour);

#endif // TILE_RROTOTYPE_H
