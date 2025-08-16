#ifndef TILE_FLAGS_H
#define TILE_FLAGS_H

typedef enum tile_flags
{
    TILE_FLAG_NONE = 0,
    TILE_FLAG_WALKABLE = 1 << 0,
    TILE_FLAG_SOLID = 1 << 1,
    TILE_FLAG_LAST_BIT = 1 << 2
} TileFlags;

#endif // TILE_FLAGS_H
