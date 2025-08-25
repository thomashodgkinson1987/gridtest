#ifndef ACTOR_H
#define ACTOR_H

#include "colour.h"
#include "components.h"

// Opaque pointer type for an Actor. The struct is defined in actor.c.
typedef struct actor Actor;

// --- Actor Creation/Destruction ---

Actor *actor_create(int x, int y, char glyph, Colour colour, const char *name);
void actor_free(Actor *actor);

// --- Actor Component Management ---

void actor_add_health_component(Actor *actor, int max_hp);
void actor_add_combat_component(Actor *actor, int attack_power);
void actor_add_ai_component(Actor *actor);

void actor_remove_health_component(Actor *actor);
void actor_remove_combat_component(Actor *actor);
void actor_remove_ai_component(Actor *actor);

const HealthComponent *actor_get_health_component(const Actor *actor);
const CombatComponent *actor_get_combat_component(const Actor *actor);
const AIComponent *actor_get_ai_component(const Actor *actor);

HealthComponent *actor_get_health_component_mut(Actor *actor);
CombatComponent *actor_get_combat_component_mut(Actor *actor);
AIComponent *actor_get_ai_component_mut(Actor *actor);

// --- Actor Getters/Setters ---

int actor_get_x(const Actor *actor);
int actor_get_y(const Actor *actor);
void actor_get_position(const Actor *actor, int *x, int *y);
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
