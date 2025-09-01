#ifndef ACTOR_H
#define ACTOR_H

#include <stdint.h>

#include "colour.h"
#include "component.h"

// --- Forward Declarations ---
typedef struct actor Actor;

// --- Public Function Prototypes ---
Actor *actor_create(int x, int y, char glyph, Colour colour, const char *name);
void actor_free(Actor *actor);

void actor_add_component(Actor *actor, Component *component);
void actor_remove_component(Actor *actor, ComponentType type);
const Component *actor_get_component(Actor *actor, ComponentType type);
Component *actor_get_component_mut(Actor *actor, ComponentType type);

uint64_t actor_get_id(const Actor *actor);

int actor_get_x(const Actor *actor);
int actor_get_y(const Actor *actor);
void actor_get_position(const Actor *actor, int *out_x, int *out_y);
char actor_get_glyph(const Actor *actor);
Colour actor_get_colour(const Actor *actor);
unsigned char actor_get_r(const Actor *actor);
unsigned char actor_get_g(const Actor *actor);
unsigned char actor_get_b(const Actor *actor);
unsigned char actor_get_a(const Actor *actor);
const char *actor_get_name(const Actor *actor);

void actor_set_x(Actor *actor, int x);
void actor_set_y(Actor *actor, int y);
void actor_set_position(Actor *actor, int x, int y);
void actor_set_glyph(Actor *actor, char glyph);
void actor_set_colour(Actor *actor, Colour colour);
void actor_set_r(Actor *actor, unsigned char r);
void actor_set_g(Actor *actor, unsigned char g);
void actor_set_b(Actor *actor, unsigned char b);
void actor_set_a(Actor *actor, unsigned char a);
void actor_set_name(Actor *actor, const char *name);

#endif // ACTOR_H
