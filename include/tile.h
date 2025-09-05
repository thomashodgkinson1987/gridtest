#ifndef TILE_H
#define TILE_H

#include "colour.h"

// --- Type Definitions ---
typedef enum tile_type
{
    TILE_TYPE_FLOOR,
    TILE_TYPE_WALL
} TileType;

typedef struct tile
{
    TileType type;
    Colour fg_colour;
    Colour bg_colour;
} Tile;

#endif // TILE_H
