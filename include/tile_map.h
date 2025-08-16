#ifndef TILE_MAP_H
#define TILE_MAP_H

#include "tile.h"
#include "tile_array.h"

typedef struct tile_map
{
    TileArray tiles;
    int width;
    int height;
} TileMap;

TileMap tile_map_create(int width, int height);
void tile_map_free(TileMap *tile_map);

int tile_map_get_width(const TileMap *tile_map);
int tile_map_get_height(const TileMap *tile_map);

Tile *tile_map_get_data(TileMap *tile_map);

Tile *tile_map_get_tile(TileMap *tile_map, int x, int y);

void tile_map_set_tile(TileMap *tile_map, int x, int y, Tile tile);

#endif // TILE_MAP_H
