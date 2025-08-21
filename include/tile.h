#ifndef TILE_H
#define TILE_H

#include "colour.h"

// A simple enum for our two tile types.
typedef enum tile_type
{
    TILE_TYPE_FLOOR,
    TILE_TYPE_WALL
} TileType;


// The struct representing a single tile on the map.
typedef struct tile
{
    TileType type;
    Colour fg_colour; // Foreground colour
    Colour bg_colour; // Background colour
    // We can add more properties later, like visibility, explored status, etc.
} Tile;

#endif // TILE_H
