#ifndef COLOUR_H
#define COLOUR_H

// A simple colour struct to avoid coupling Raylib's Color throughout the game logic.
typedef struct colour
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} Colour;

#endif // COLOUR_H
