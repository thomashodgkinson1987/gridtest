#include "tile_prototype.h"

#include "tile.h"

#include "tile_colour.h"
#include "tile_flags.h"

TilePrototype tile_prototype_create(
    const TileFlags flags,
    const TileColour colour)
{
    TilePrototype prototype = {0};

    prototype.flags = flags;
    prototype.colour = colour;

    return prototype;
}
