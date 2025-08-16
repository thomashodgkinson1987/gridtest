#ifndef ACTOR_ARRAY_H
#define ACTOR_ARRAY_H

#include "array_macros.h"

#include "actor.h"

DECLARE_ARRAY_STRUCT(actor, Actor, Actor *);

DECLARE_ARRAY_FUNCTIONS(actor, Actor, Actor *);

#endif // ACTOR_ARRAY_H
