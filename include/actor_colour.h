#ifndef ACTOR_COLOUR_H
#define ACTOR_COLOUR_H

typedef struct actor_colour
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} ActorColour;

ActorColour actor_colour_create(
    unsigned char r,
    unsigned char g,
    unsigned char b,
    unsigned char a);

#endif // ACTOR_COLOUR_H
