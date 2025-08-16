#include "actor_colour.h"

ActorColour actor_colour_create(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    ActorColour colour = {0};

    colour.r = r;
    colour.g = g;
    colour.b = b;
    colour.a = a;

    return colour;
}
