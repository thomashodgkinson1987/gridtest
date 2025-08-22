#ifndef ACTOR_H
#define ACTOR_H

#include <stdbool.h>
#include "colour.h"
#include "components.h"

// Opaque pointer type for an Actor. The struct is defined in actor.c.
typedef struct actor Actor;

// --- Actor Creation/Destruction ---

Actor *actor_create(int x, int y, char glyph, Colour colour);
void actor_free(Actor *actor);

// --- Actor Component Management ---

void actor_add_health_component(Actor *actor, HealthComponent *component);
void actor_add_combat_component(Actor *actor, CombatComponent *component);
void actor_add_ai_component(Actor *actor, AIComponent *component);
void actor_add_name_component(Actor *actor, NameComponent *component);

HealthComponent *actor_get_health_component(const Actor *actor);
CombatComponent *actor_get_combat_component(const Actor *actor);
AIComponent *actor_get_ai_component(const Actor *actor);
NameComponent *actor_get_name_component(const Actor *actor);

// --- Actor Getters/Setters ---

void actor_get_position(const Actor *actor, int *x, int *y);
void actor_set_position(Actor *actor, int x, int y);

char actor_get_glyph(const Actor *actor);
Colour actor_get_colour(const Actor *actor);

#endif // ACTOR_H
