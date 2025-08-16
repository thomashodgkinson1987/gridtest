#include "tile_map.h"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tile_array.h"

TileMap tile_map_create(int width, int height)
{
    if (width <= 0 || height <= 0)
    {
        fprintf(
            stderr,
            "tile_map_create: width (%d) and height (%d) must be positive\n",
            width,
            height);
        exit(EXIT_FAILURE);
    }

    if ((size_t)width > SIZE_MAX / (size_t)height)
    {
        fprintf(
            stderr,
            "tile_map_create: total capacity (elements) cannot exceed %zu\n",
            SIZE_MAX);
        exit(EXIT_FAILURE);
    }

    TileMap tile_map = {0};

    tile_map.tiles = tile_array_create((size_t)width * (size_t)height);

    for (size_t i = 0; i < tile_map.tiles.capacity; ++i)
    {
        const TileFlags flags = TILE_FLAG_NONE;
        const TileColour colour = tile_colour_create(0, 0, 0, 255);

        const Tile tile = tile_create(flags, colour);

        tile_array_push(&tile_map.tiles, tile);
    }

    tile_map.width = width;
    tile_map.height = height;

    return tile_map;
}

void tile_map_free(TileMap *tile_map)
{
    tile_array_free(&tile_map->tiles);
    tile_map->width = 0;
    tile_map->height = 0;
}

int tile_map_get_width(const TileMap *tile_map)
{
    return tile_map->width;
}

int tile_map_get_height(const TileMap *tile_map)
{
    return tile_map->height;
}

Tile *tile_map_get_data(TileMap *tile_map)
{
    Tile *tile = tile_array_get_data(&tile_map->tiles);

    return tile;
}

Tile *tile_map_get_tile(TileMap *tile_map, int x, int y)
{
    if (x < 0 || x >= tile_map->width || y < 0 || y >= tile_map->height)
    {
        fprintf(
            stderr,
            "tile_map_get_tile: either x (%d) or y (%d) is out of bounds "
            "(width=%d height=%d)\n",
            x,
            y,
            tile_map->width,
            tile_map->height);
        exit(EXIT_FAILURE);
    }

    const size_t index = (size_t)y * (size_t)tile_map->width + (size_t)x;

    Tile *tile = tile_array_get(&tile_map->tiles, index);

    return tile;
}

void tile_map_set_tile(TileMap *tile_map, int x, int y, Tile tile)
{
    if (x < 0 || x >= tile_map->width || y < 0 || y >= tile_map->height)
    {
        fprintf(
            stderr,
            "tile_map_set_tile: either x (%d) or y (%d) is out of bounds "
            "(width=%d height=%d)\n",
            x,
            y,
            tile_map->width,
            tile_map->height);
        exit(EXIT_FAILURE);
    }

    const size_t index = (size_t)y * (size_t)tile_map->width + (size_t)x;

    tile_array_set(&tile_map->tiles, index, tile);
}
