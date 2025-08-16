#include "tile_colour.h"

TileColour tile_colour_create(
    const unsigned char r,
    const unsigned char g,
    const unsigned char b,
    const unsigned char a)
{
    TileColour tile_colour = {0};

    tile_colour.r = r;
    tile_colour.g = g;
    tile_colour.b = b;
    tile_colour.a = a;

    return tile_colour;
}
