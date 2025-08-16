#ifndef TILE_COLOUR_H
#define TILE_COLOUR_H

typedef struct tile_colour
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} TileColour;

TileColour tile_colour_create(
    unsigned char r,
    unsigned char g,
    unsigned char b,
    unsigned char a);

#endif // TILE_COLOUR_H
