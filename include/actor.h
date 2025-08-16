#ifndef ACTOR_H
#define ACTOR_H

#include <stdbool.h>

#include "actor_colour.h"

typedef struct actor Actor;

Actor *actor_create(int x, int y, ActorColour colour, const char *name);
void actor_free(Actor *actor);

int actor_get_x(const Actor *actor);
int actor_get_y(const Actor *actor);
ActorColour actor_get_colour(const Actor *actor);
const char *actor_get_name(const Actor *actor);

void actor_set_x(Actor *actor, int x);
void actor_set_y(Actor *actor, int y);
void actor_set_position(Actor *actor, int x, int y);
void actor_set_colour(Actor *actor, ActorColour colour);
bool actor_set_name(Actor *actor, const char *name);

void actor_translate_x(Actor *actor, int translation_x);
void actor_translate_y(Actor *actor, int translation_y);
void actor_translate_position(
    Actor *actor,
    int translation_x,
    int translation_y);

#endif // ACTOR_H
